/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rg/rgRefTemplate.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Use template to input reference data dialog header.
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

#ifndef SRC_RG_RGREFTEMPLATE_H
#define SRC_RG_RGREFTEMPLATE_H

#include <wx/button.h>
#include <wx/statline.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <hxml5/pugixml.hpp>

#include <rec/recReference.h>

class rgDataEntry
{
public:
	pugi::xml_node m_node;
    std::string   m_prompt;
	std::string   m_default;
	std::string   m_value;
};

using rgDataEntryVec = std::vector<rgDataEntry>;

class rgDataBlock
{
public:
	pugi::xml_node m_node;
	std::string    m_title;
    rgDataEntryVec m_entries;
};

using rgDataBlockVec = std::vector<rgDataBlock>;

class rgRefData
{
public:
	idt            m_ref_id;
	pugi::xml_node m_h1_node;
	std::string    m_title;
	rgDataBlockVec m_blocks;
};

//============================================================================
//-------------------------[ rgEditRefTemplate ]------------------------------
//============================================================================

class rgEntryPair
{
public:
	rgEntryPair() : m_static( nullptr ), m_value( nullptr ) {}

	wxStaticText* m_static;
	wxTextCtrl*   m_value;
};

using rgEntryPairVec = std::vector<rgEntryPair>;

class rgEditRefTemplate : public wxDialog
{
public:
	rgEditRefTemplate( wxWindow* parent, rgDataBlock& block, idt refID );
	~rgEditRefTemplate();

private:
	rgEntryPairVec m_entryPairs;
	wxStaticText*  m_staticRefID;
	wxButton*      m_buttonSave;
	wxButton*      m_buttonCancel;

	rgDataBlock&   m_block;
	idt            m_ref_id;

	bool TransferDataToWindow();
	bool TransferDataFromWindow();
};

#endif // SRC_RG_RGREFTEMPLATE_H