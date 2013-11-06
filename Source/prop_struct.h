//Jason Wrinkle - Solitaire Game 
//Copyright (C) 1999  Jason Wrinkle (jwrinkle@utdallas.edu)
//
//This program is free software; you can redistribute it and/or 
//modify it under the terms of the GNU General Public License 
//as published by the Free Software Foundation; either version 2 
//of the License, or (at your option) any later version. 
//
//This program is distributed in the hope that it will be useful, 
//but WITHOUT ANY WARRANTY; without even the implied warranty of 
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
//GNU General Public License for more details. 
//
//You should have received a copy of the GNU General Public License 
//along with this program; if not, write to the Free Software 
//Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA. 


#include <Point.h>
#include <Message.h>
#include <list.h>

#ifndef PEDITDEFS
#define PEDITDEFS
#include "PileEditorDefs.h"
#endif

#include "order_struct.h"
#include "pop_struct.h"
#include "misc.h"

#ifndef PILEPROPS
#define PILEPROPS

class pile_props
{
	friend class PILE;
	friend class PileEditor;
	friend class BESOL_APP;

	pile_props();
	~pile_props();
	pile_props(pile_props& old);
	
	BMessage* Encapsulate() const;
	void UnEncapsulate(BMessage* props);
	
	char* IDstring;	
	char* dealstring;
	
	int32 req_orient;
	bool flip_to_orient;
	BPoint offsetup;
	BPoint offsetdown;
	
	list <int32> emptyacceptvalue;
	list <int32> emptyacceptsuit;

	bool emptyonwin;
	int32 ptaddcards, ptremovecards;	
	
	card_pop_prop* popping;	
	order_props* ordering;
};

#endif