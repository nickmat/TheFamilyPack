/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rg/rgRefTemplate.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Use template to input reference data dialog.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     13 Aug 2021
 * Copyright:   Copyright (c) 2021, Nick Matthews.
 * Licence:     GNU GPLv3
 *
 *  The Family Pack is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  The Family Pack is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with The Family Pack.  If not, see <http://www.gnu.org/licenses/>.
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

*/

#include "wx/wxprec.h"

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "rgRefTemplate.h"

#include <hxml5/pugixml.hpp>

using namespace pugi;
using std::string;
using std::vector;

namespace {

    void process_block( xml_node& node, rgDataEntryVec& entries )
    {
        for( xml_node next = node.first_child(); next; next = next.next_sibling() ) {
            if( next.type() != node_element ) {
                continue;
            }
            xml_attribute entry_attr = next.attribute( "data-entry" );
            if( entry_attr ) {
                rgDataEntry entry;
                entry.m_node = next;
                entry.m_prompt = entry_attr.value();
                entry.m_default = next.child_value();
                entries.push_back( entry );
                continue;
            }
            process_block( next, entries );
        }
    }

    void find_next_block_node( xml_node& node, rgRefData& data )
    {
        for( xml_node next = node.first_child(); next; next = next.next_sibling() ) {
            if( next.type() != node_element ) {
                continue;
            }
            xml_attribute block_attr = next.attribute( "data-block" );
            if( block_attr ) {
                rgDataBlock block;
                block.m_node = next;
                block.m_title = block_attr.value();
                process_block( next, block.m_entries );
                data.m_blocks.push_back( block );
                continue;
            }
            block_attr = next.attribute( "data-title" );
            if( block_attr ) {
                data.m_h1_node = next;
                data.m_title = block_attr.value();
            }
            find_next_block_node( next, data );
        }
    }

    void enter_block_data( rgDataBlock& block ) {
        wxMessageBox( block.m_title, "rgEnterTemplateData" );
    }
}
#if 0
bool rgEnterTemplateData( 
    wxWindow* parent, const wxString& reftemplate, rgRefData& data )
{
    xml_document doc;
    xml_parse_result result = doc.load_file( reftemplate.ToUTF8() );
    if( !result ) {
        return false;
    }
    find_next_block_node( doc.document_element(), data );

    for( auto block : data.m_blocks ) {
        rgEditRefTemplate dialog( parent, block, data.m_ref_id );
        if( dialog.ShowModal() == wxID_OK ) {
            enter_block_data( block );
        }
        else {
            return false;
        }
    }
    return true;
}
#endif

//============================================================================
//-------------------------[ rgEditRefTemplate ]------------------------------
//============================================================================

rgEditRefTemplate::rgEditRefTemplate( wxWindow* parent, rgDataBlock& block, idt refID )
    : wxDialog( 
        parent, wxID_ANY, block.m_title, wxDefaultPosition, wxDefaultSize,
        wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER ), m_block(block), m_ref_id(refID)
{
    this->SetSizeHints( wxDefaultSize, wxDefaultSize );

    wxBoxSizer* sizer1;
    sizer1 = new wxBoxSizer( wxVERTICAL );

    wxFlexGridSizer* sizer2;
    sizer2 = new wxFlexGridSizer( 0, 2, 0, 0 );
    sizer2->SetFlexibleDirection( wxBOTH );
    sizer2->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

    for( auto line : block.m_entries ) {
        rgEntryPair pair;
        pair.m_static = new wxStaticText( this, wxID_ANY, line.m_prompt + ":", wxDefaultPosition, wxDefaultSize, 0 );
        pair.m_static->Wrap( -1 );
        sizer2->Add( pair.m_static, 0, wxALL | wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL, 5 );

        pair.m_value = new wxTextCtrl( this, wxID_ANY, line.m_default, wxDefaultPosition, wxSize( 250, -1 ), 0 );
        sizer2->Add( pair.m_value, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5 );
        m_entryPairs.push_back( pair );
    }

    sizer1->Add( sizer2, 0, wxEXPAND, 5 );

    wxStaticLine* staticline = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
    sizer1->Add( staticline, 0, wxALL | wxEXPAND, 0 );

    wxBoxSizer* sizer3;
    sizer3 = new wxBoxSizer( wxHORIZONTAL );

    m_staticRefID = new wxStaticText(
        this, wxID_ANY, recReference::GetIdStr( m_ref_id ), wxDefaultPosition, wxDefaultSize, 0 );
    m_staticRefID->Wrap( -1 );
    m_staticRefID->SetFont(
        wxFont( wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT( "Times New Roman" ) ) );

    sizer3->Add( m_staticRefID, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5 );

    sizer3->Add( 0, 0, 1, wxEXPAND, 5 );

    m_buttonSave = new wxButton( this, wxID_OK, _( "Save" ), wxDefaultPosition, wxDefaultSize, 0 );
    sizer3->Add( m_buttonSave, 0, wxALIGN_CENTER_VERTICAL | wxTOP | wxBOTTOM | wxLEFT, 5 );

    m_buttonCancel = new wxButton( this, wxID_CANCEL, _( "Cancel" ), wxDefaultPosition, wxDefaultSize, 0 );
    sizer3->Add( m_buttonCancel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    sizer1->Add( sizer3, 1, wxEXPAND, 5 );

    SetSizer( sizer1 );
    Layout();
    sizer1->Fit( this );

    this->Centre( wxBOTH );
}

rgEditRefTemplate::~rgEditRefTemplate()
{
}

bool rgEditRefTemplate::TransferDataToWindow()
{
    for( size_t i = 0; i < m_entryPairs.size(); i++ ) {
        m_entryPairs[i].m_value->SetValue( m_block.m_entries[i].m_default );
    }
    return true;
}

bool rgEditRefTemplate::TransferDataFromWindow()
{
    for( size_t i = 0; i < m_entryPairs.size(); i++ ) {
        m_block.m_entries[i].m_value = m_entryPairs[i].m_value->GetValue();
    }
    return true;
}
