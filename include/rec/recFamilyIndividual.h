/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        include/rec/recFamilyIndividual.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage SQLite3 FamilyIndividual record.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     8th January 2022
 * Copyright:   Copyright (c) 2022, Nick Matthews.
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

#ifndef RECFAMILYINDIVIDUAL_H
#define RECFAMILYINDIVIDUAL_H

#include <vector>

#include <rec/recDatabase.h>
#include <rec/recEvent.h>
#include <rec/recFamEvent.h>
#include <rec/recPersona.h>

class recFamilyIndividual;
typedef std::vector< recFamilyIndividual >  recFamIndVec;

//============================================================================
//-------------------------[ recFamilyIndividual ]----------------------------
//============================================================================

class recFamilyIndividual : public recDbT< recFamilyIndividual>
{
public:
    static constexpr const char* s_tablename = "FamilyIndividual";

    idt f_fam_id;
    idt f_ind_id;
    int f_seq_child;
    int f_seq_parent;

    recFamilyIndividual() : f_fam_id(0), f_ind_id(0),
        f_seq_child(0), f_seq_parent(0) {}
    recFamilyIndividual( idt id ) : recDbT(id) { Read(); }
    recFamilyIndividual( const recFamilyIndividual& fi );

    void Clear();
    void Save();
    bool Read();
    bool Equivalent( const recFamilyIndividual& r2 ) const;

    idt FGetFamID() const { return f_fam_id; }
    idt FGetIndID() const { return f_ind_id; }
    int FGetSeqChild() const { return f_seq_child; }
    int FSetSeqParent() const { return f_seq_parent; }

    void FSetFamID( idt famID ) { f_fam_id = famID; }
    void FSetIndID( idt indID ) { f_ind_id = indID; }
    void FSetSeqChild( int seq ) { f_seq_child = seq; }
    void FSetSeqParent( int seq ) { f_seq_parent = seq; }

    bool Find();
};


#endif // RECFAMILYINDIVIDUAL_H
