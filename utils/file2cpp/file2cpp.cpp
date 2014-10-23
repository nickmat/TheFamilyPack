/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        file2cpp.cpp
 * Project:     file2cpp: Convert text and binary files to C/C++ code
 * Purpose:     Application main and supporting functions
 * Author:      Nick Matthews
 * Created:     9th December 2005
 * Copyright:   Copyright (c) 2005 - 2014, Nick Matthews.
 * Licence:     GNU GPLv3
 *
 *  file2cpp is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  file2cpp is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with file2cpp.  If not, see <http://www.gnu.org/licenses/>.
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

*/

#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include <wx/filename.h>
#include <wx/ffile.h>
#include <wx/textfile.h>
#include <wx/cmdline.h>
#include <wx/tokenzr.h>

#define VERSION   "0.4.1"
#define PROGNAME  "file2cpp"
#define COPYRIGHT "Copyright (c) 2009 - 2014 Nick Matthews"
#ifdef _DEBUG
#define STATUS    " Debug"
#else
#define STATUS
#endif

const wxString g_version = VERSION;
const wxString g_progName = PROGNAME;
const wxString g_title = PROGNAME " - Version " VERSION STATUS "\n" COPYRIGHT "\n\n";

bool g_verbose = false;
bool g_quiet   = false;
bool g_svn     = false;
wxArrayString g_incPaths;

enum SkipType {
    SKIP_NONE,
    SKIP_DATA,
    SKIP_TEXT_BEG,
    SKIP_TEXT_END,
    SKIP_TEXT_POST
};

typedef wxString::const_iterator cit_t;

int ProccessInFile( wxTextFile& inFile, wxFFile& outFile );

enum FileComment {
    FCOMMENT_NONE,
    FCOMMENT_C,
    FCOMMENT_CPP,
    FCOMMENT_XML,
    FCOMMENT_TCL
};

struct TextMod {
    bool        trimR;
    bool        trimL;
    bool        mline;
    bool        compact;
    FileComment remove;
    wxString    prefix;
    wxString    postfix;
};

SkipType DoAtCommand( wxFFile& outFile, cit_t it, cit_t end );
void OutputData( wxString& filename, wxFFile& outFile );
void OutputText( wxString& filename, wxFFile& outFile, TextMod& modify );
bool IsPostfixTerminator( wxChar ch );
bool Compare( cit_t it, cit_t end, const wxString& str );
void AddToIncPaths( wxString& incPath );
bool FindFile( wxFileName& name );
void DisableSvnId( wxString* line );

/*#*************************************************************************
 **  main
 **  ~~~~
 */

int main( int argc, char** argv )
{
    static const wxCmdLineEntryDesc desc[] = {
        { wxCMD_LINE_SWITCH, "h", "help", "show this help message",
            wxCMD_LINE_VAL_NONE, wxCMD_LINE_OPTION_HELP },
        { wxCMD_LINE_SWITCH, "v", "verbose", "be verbose" },
        { wxCMD_LINE_SWITCH, "q", "quiet",   "be quiet" },
        { wxCMD_LINE_SWITCH, "s", "svn",     "svn friendly" },
        { wxCMD_LINE_OPTION, "o", "output",  "output file" },
        { wxCMD_LINE_OPTION, "I", "include", "include paths" },
        { wxCMD_LINE_PARAM,  NULL, NULL, "format file",
            wxCMD_LINE_VAL_STRING, wxCMD_LINE_OPTION_MANDATORY },
        { wxCMD_LINE_NONE }
    };

    wxInitializer initializer;
    if( !initializer )
    {
        fprintf( stderr, "Failed to initialize the wxWidgets library, aborting." );
        return EXIT_FAILURE;
    }

    wxCmdLineParser parser( desc, argc, argv );
    parser.SetLogo( g_title );

    int cmd = parser.Parse();
    if( cmd < 0 ) {
        return EXIT_SUCCESS;
    }
    if( cmd > 0 ) {
        return EXIT_FAILURE;
    }

    if( parser.Found( "q" ) ) g_quiet = true;
    if( parser.Found( "v" ) ) g_verbose = true;
    if( parser.Found( "s" ) ) g_svn = true;

    if( ! g_quiet ) wxPrintf( g_title );

    wxFileName inName( parser.GetParam() );
    if( !inName.FileExists() ) {
        wxPrintf( "Input file \"%s\" not found.\n", inName.GetFullPath() );
        return EXIT_FAILURE;
    }
    wxTextFile inFile;
    if( !inFile.Open( inName.GetFullPath() ) ) {
        wxPrintf( "Can not read input file \"%s\".\n", inName.GetFullPath() );
        return EXIT_FAILURE;
    }
    if( g_verbose ) {
        wxPrintf( "Reading format file \"%s\".\n", inName.GetFullPath() );
    }

    // Get a list of paths to look for included files
    g_incPaths.Add( inName.GetPath() );
    wxString incPath;
    parser.Found("I", &incPath );
    if( !incPath.empty() ) {
        AddToIncPaths( incPath );
    }

    // Form the output file name
    wxString outNameStr;
    parser.Found( "o", &outNameStr );
    wxFileName outName;
    if( outNameStr.IsEmpty() ) {
        outName = inName;
        outName.SetExt( "cpp" );
    } else {
        outName = outNameStr;
        if( outName.HasExt() == false ) {
            outName.SetExt( "cpp" );
        }
    }
    wxFFile outFile;
    if( ! outFile.Open( outName.GetFullPath(), "w" ) ) {
        wxPrintf( "Can not open output file \"%s\".\n", outName.GetFullPath() );
        return EXIT_FAILURE;
    }
    if( g_verbose ) {
        wxPrintf( "Writing output file \"%s\".\n", outName.GetFullPath() );
    }
    wxString heading = wxString::Format(
        "/* %s - File created by %s */\n\n",
        outName.GetFullPath(),
        g_progName
    );
    outFile.Write( heading );

    int ret = ProccessInFile( inFile, outFile );

    g_incPaths.Clear();
    return ret;
}

int ProccessInFile( wxTextFile& inFile, wxFFile& outFile )
{
    bool inLComment = false, inCComment = false, inSQuote = false, inDQuote = false;
    bool extendLine = false;
    SkipType skip = SKIP_NONE;
    wxString line;
    wxString out;
    cit_t it, end;
    for( line = inFile.GetFirstLine() ; !inFile.Eof() ; line = inFile.GetNextLine() ) {
        if( g_svn && line.find( "RCS-ID" ) != wxString::npos ) {
            DisableSvnId( &line );
        }
        skip = SKIP_NONE;
        end = line.end();
        for( it = line.begin() ; it != end ; it++ ) {
            if( skip != SKIP_NONE ) {
                if( skip == SKIP_DATA && *it == '}' ) skip = SKIP_NONE;
                if( skip == SKIP_TEXT_POST && IsPostfixTerminator(*it) ) {
                    out += *it;
                    skip = SKIP_NONE;
                }
                if( skip == SKIP_TEXT_END && *it == '"' ) skip = SKIP_TEXT_POST;
                if( skip == SKIP_TEXT_BEG && *it == '"' ) skip = SKIP_TEXT_END;
                continue;
            }
            if( *it == '\\' && it+1 == end ) {
                out += *it;
                extendLine = true;
                break;
            }
            if( inLComment ) {
                out += *it;
                continue;
            }
            if( inCComment ) {
                if( *it == '*' && it+1 != end && *(it+1) == '/' ) {
                    out += "*/";
                    inCComment = false;
                    it++;
                    continue;
                }
                out += *it;
                continue;
            }
            if( inSQuote ) {
                if( *it == '\\' ) {         // already tested for \newline
                    if( *(it+1) == '\\' ) {
                        out += "\\\\";
                        it++;
                        continue;
                    }
                    if( *(it+1) == '\'' ) {
                        out += "\\'";
                        it++;
                        continue;
                    }
                }
                if( *it == '\'' ) {
                    inSQuote = false;
                }
                out += *it;
                continue;
            }
            if( inDQuote ) {
                if( *it == '\\' ) {         // already tested for \newline
                    if( *(it+1) == '\\' ) {
                        out += "\\\\";
                        it++;
                        continue;
                    }
                    if( *(it+1) == '"' ) {
                        out += "\\\"";
                        it++;
                        continue;
                    }
                }
                if( *it == '"' ) {
                    inDQuote = false;
                }
                out += *it;
                continue;
            }
            if( *it == '@' ) {
                outFile.Write( out );
                out = wxEmptyString;
                skip = DoAtCommand( outFile, it, end );
                continue;
            }
            if( *it == '/' && it+1 != end && *(it+1) == '*' ) {
                out += "/*";
                inCComment = true;
                it++;
                continue;
            }
            if( *it == '/' && it+1 != end && *(it+1) == '/' ) {
                out += "//";
                inLComment = true;
                it++;
                continue;
            }
            out += *it;
            if( *it == '\'' ) {
                inSQuote = true;
            }
            if( *it == '"' ) {
                inDQuote = true;
            }
        }
        out += '\n';
        outFile.Write( out );
        out = wxEmptyString;
        if( extendLine ) {
            extendLine = false;
        } else {
            inLComment = false;
        }
    }
    return EXIT_SUCCESS;
}

SkipType DoAtCommand( wxFFile& outFile, cit_t it, cit_t end )
{
    TextMod  mod = { false, false, false, false, FCOMMENT_NONE };
    wxString fname;
    wxString outf;
    wxChar exitch;
    wxString out;

    if( ++it == end ) return SKIP_NONE;
    if( *it == '{' ) {
        exitch = '}';
        outf = "{ /* %s */\n";
    } else {
        if( *it == '(' ) {
            // Trim text file content specifier
            while( ++it != end ) {
                if( *it == ')' ) {
                    it++;
                    break;
                }
                switch( (wxChar) *it ) {
                case 'r':
                    mod.trimR = true;
                    break;
                case 'l':
                    mod.trimL = true;
                    break;
                case 'm':
                    mod.mline = true;
                    break;
                case 'c':
                    mod.compact = true;
                    break;
                case '.':
                    if( Compare( it, end, ".c" ) ) {
                        mod.remove = FCOMMENT_C;
                        it++;
                    } else if( Compare( it, end, ".cpp" ) ) {
                        mod.remove = FCOMMENT_CPP;
                        it += 3;
                    } else if( Compare( it, end, ".xml" ) ) {
                        mod.remove = FCOMMENT_XML;
                        it += 3;
                    } else if( Compare( it, end, ".tcl" ) ) {
                        mod.remove = FCOMMENT_TCL;
                        it += 3;
                    }
                    break;
                }
            }
        }
        while( it != end ) {
            if( *it == '"' ) break;
            mod.prefix += *it;
            it++;
        }
        if( it == end ) return SKIP_NONE;
        exitch = '"';
        outf = " /* %s */";
    }

    while( ++it != end ) {
        if( wxIsspace( *it ) ) continue;
        if( *it == exitch ) break;
        fname += *it;
    }
    outFile.Write( wxString::Format( outf, fname.c_str() ) );
    if( exitch == '}' ) {
        OutputData( fname, outFile );
        outFile.Write( "\n}" );
        return SKIP_DATA;
    }
    while( ++it != end ) {
        if( IsPostfixTerminator( *it ) ) break;
        mod.postfix += *it;
    }

    OutputText( fname, outFile, mod );
    return SKIP_TEXT_BEG;
}

void OutputData( wxString& filename, wxFFile& outFile )
{
    wxFileName dataName = filename; // TODO: use Include path to find file
    wxFFile dataFile;
    if( !dataFile.Open( dataName.GetFullPath(), "rb" ) ) {
        wxPrintf( "Can not open data file \"%s\".\n", dataName.GetFullPath() );
        exit( EXIT_FAILURE );
    }
    if( g_verbose ) {
        wxPrintf( "Formating data file \"%s\".\n", dataName.GetFullPath() );
    }

    int ch, i;
    FILE* fp = dataFile.fp();
    FILE* fpOut = outFile.fp();
    ch = fgetc( fp );
    if( ch == EOF ) return;
    fprintf( fpOut, " %d", ch );
    for( i = 1 ; ; i++ ) {
        ch = fgetc( fp );
        if( ch == EOF ) break;
        if( i % 20 ) {
            fprintf( fpOut, ",%d", ch );
        } else {
            fprintf( fpOut, ",\n %d", ch );
        }
    }
}

void OutputText( wxString& filename, wxFFile& outFile, TextMod& mod )
{
    wxFileName textName = filename; // TODO: use Include path to find file
    if( FindFile( textName ) == false ) {
        wxPrintf( "Can not find text file \"%s\".\n", textName.GetFullPath() );
        exit( EXIT_FAILURE );
    }
    wxTextFile textFile;
    if( !textFile.Open( textName.GetFullPath() ) ) {
        wxPrintf( "Can not read text file \"%s\".\n", textName.GetFullPath() );
        exit( EXIT_FAILURE );
    }
    if( g_verbose ) {
        wxPrintf( "Formating text file \"%s\".\n", textName.GetFullPath() );
    }

    bool emptyblock = true;
    bool lookDQuote = false, lookSQuote = false;
    bool inDQuote = false, inSQuote = false;
    bool ignoreC = false, skipC = false;
    bool ignoreXml = false, skipXml = false;
    bool ignoreCpp = false, ignoreTcl = false;
    switch( mod.remove ) {
    case FCOMMENT_C:
        ignoreC = true;
        lookDQuote = true;
        lookSQuote = true;
        break;
    case FCOMMENT_CPP:
        ignoreC = true;
        ignoreCpp = true;
        lookDQuote = true;
        lookSQuote = true;
        break;
    case FCOMMENT_XML:
        ignoreXml = true;
        break;
    case FCOMMENT_TCL:
        ignoreTcl = true;
        lookDQuote = true;
        lookSQuote = true;
        break;
    }

    wxString line;
    wxString out;
    cit_t it, end;
    for( line = textFile.GetFirstLine() ; !textFile.Eof() ; line = textFile.GetNextLine() ) {
        end = line.end();
        out.Empty();
        for( it = line.begin() ; it != end ; it++ ) {
            if( skipC ) {
                if( *it == '*' && Compare( it, end, "*/" ) ) {
                    it++; // step over second character
                    skipC = false;
                }
                continue;
            }
            if( skipXml ) {
                if( *it == '-' && Compare( it, end, "-->" ) ) {
                    it++;it++; // step over 2nd & 3rd character
                    skipXml = false;
                }
                continue;
            }
            if( *it == '\"' || *it == '\\' ) {
                out += '\\';
            }
            if( *it == '\t' ) {
                out += "\\t";
                continue;
            }
            if( lookSQuote && !inDQuote && *it == '\'' ) {
                inSQuote = inSQuote ? false : true;
            }
            if( lookDQuote && !inSQuote && *it == '"' ) {
                inDQuote = inDQuote ? false : true;
            }
            if( ignoreC && *it == '/' && !inDQuote && !inSQuote ) {
                if( Compare( it, end, "/*" ) == true ) {
                    skipC = true;
                    continue;
                }
                if( Compare( it, end, "//" ) == true ) {
                    break;
                }
            }
            if( ignoreXml && *it == '<' && !inDQuote && !inSQuote ) {
                if( Compare( it, end, "<!--" ) == true ) {
                    skipXml = true;
                    continue;
                }
            }
            if( ignoreTcl && *it == '#' && !inDQuote && !inSQuote ) {
                break;
            }
            out += *it;
       }
        if( mod.trimR ) out.Trim();
        if( mod.compact && out.IsEmpty() ) {
            continue;
        }
        if( mod.mline && out.IsEmpty() ) {
            if( emptyblock ) continue;
            emptyblock = true;
        } else {
            emptyblock = false;
        }
        if( mod.trimL ) out.Trim( false );
        outFile.Write(
            "\n " + mod.prefix + "\""
            + out
            + "\\n\"" + mod.postfix
        );
    }
}

bool IsPostfixTerminator( wxChar ch )
{
    return wxIsspace( ch ) || ch == ';' || ch == ',';
}

bool Compare( cit_t it, cit_t end, const wxString& str )
{
    for( cit_t sit = str.begin() ; sit != str.end() ; sit++, it++  ) {
        if( it == end ) return false;
        if( *sit != *it ) return false;
    }
    return true;
}

void AddToIncPaths( wxString& incPath )
{
    wxStringTokenizer tkz( incPath, ";", wxTOKEN_STRTOK );
    while( tkz.HasMoreTokens() ) {
        g_incPaths.Add( tkz.GetNextToken() );
    }
}

bool FindFile( wxFileName& name )
{
    if( name.IsFileReadable() ) return true;
    if( name.IsAbsolute() ) return false; /* nothing much we can do */
    wxString file = name.GetFullPath();
    wxFileName test;
    wxString path;
    for( size_t i = 0 ; i < g_incPaths.GetCount() ; i++ ) {
        test = wxFileName( g_incPaths[i], wxEmptyString );
        path = test.GetPathWithSep() + file;
        test = wxFileName( path );
        if( test.IsFileReadable() ) {
            name = test;
            return true;
        }
    }
    return false;
}

void DisableSvnId( wxString* line )
{
    size_t pos = line->find( "$Id:" );
    if( pos != wxString::npos ) {
        *line = line->Mid(0,pos) + line->Mid(pos+1);
    }
}

/* End of file2cpp.cpp file */
