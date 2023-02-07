/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        include/rec/recHelper.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     General defines
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     5th February 2023
 * Copyright:   Copyright (c) 2023, Nick Matthews.
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

#ifndef INCLUDE_REC_RECDEFS_H
#define INCLUDE_REC_RECDEFS_H

#include <cstdint>
#include <cstdlib>
#include <cinttypes>
#include <map>
#include <string>
#include <vector>

using idt = int64_t;

#define ID "%" PRId64 

using  StdStrVec = std::vector< std::string >;
using  StdStrMap = std::map< std::string, std::string >;
using  IntVec = std::vector< int >;
using  DoubleVec = std::vector< double >;
using  BoolVec = std::vector< bool >;

using  IdStringMap = std::map< idt, std::string >;
using  IdVec = std::vector< idt >;

inline idt GetID( const std::string& str )
{
    if( str.empty() ) {
        return 0;
    }
    return strtoll( str.c_str(), nullptr, 10 );
}


#endif // INCLUDE_REC_RECDEFS_H
