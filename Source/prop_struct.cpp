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


#include "prop_struct.h"

pile_props::pile_props(pile_props& old) :
	req_orient(old.req_orient), flip_to_orient(old.flip_to_orient),
	offsetup(old.offsetup), offsetdown(old.offsetdown), emptyonwin(old.emptyonwin), ptaddcards(old.ptaddcards),
	ptremovecards(old.ptremovecards)
{
	dealstring = mystrconcat (old.dealstring, "");
	IDstring = mystrconcat (old.IDstring, "");

	copy (old.emptyacceptvalue.begin(), old.emptyacceptvalue.end(), emptyacceptvalue.begin());
	copy (old.emptyacceptsuit.begin(), old.emptyacceptsuit.end(), emptyacceptsuit.begin());
	
	if (old.popping != NULL)
	{
		popping = new card_pop_prop;
		popping->toID = mystrconcat (old.popping->toID, "");
		popping->numtimes = old.popping->numtimes;
		popping->numcards = old.popping->numcards;
	}
	else popping = NULL;
		
	if (old.ordering != NULL)
	{
		ordering = new order_props;
		*ordering = *(old.ordering);
	}
	else ordering = NULL;
};

pile_props::pile_props() :
	IDstring("untitled"), dealstring (""), req_orient(IE_PILEEDITOR_NEWCARDSORIENTATION_NO_PREF_),
	flip_to_orient(false), offsetup( BPoint(10, 10) ), offsetdown( BPoint(2, 3) ), emptyonwin(false), 
	ptaddcards(0), ptremovecards(0),  
	popping(NULL), ordering(NULL)
{};

pile_props::~pile_props()
{
	if (popping != NULL) 
	{
		delete popping->toID;
		delete popping;
	};
	if (ordering != NULL) delete ordering;
	if (dealstring != NULL) delete [] dealstring;
	if (IDstring != NULL) delete [] IDstring;	
};

BMessage* pile_props::Encapsulate() const
{
	BMessage* props = new BMessage();
	
	props->AddString("IDstring", IDstring);
	props->AddString("dealstring", dealstring);	
	props->AddInt32("req_orient", req_orient);
	props->AddBool("flip_to_orient", flip_to_orient);
	props->AddPoint("offsetup", offsetup);
	props->AddPoint("offsetdown", offsetdown);

	list <int32>::const_iterator iter;

	iter = emptyacceptvalue.begin();
	while (iter != emptyacceptvalue.end())
	{
		props->AddInt32("emptyacceptvalue", *(iter++));
	};

	iter = emptyacceptsuit.begin();
	while (iter != emptyacceptsuit.end())
	{
		props->AddInt32("emptyacceptsuit", *(iter++));
	};

	props->AddBool("emptyonwin", emptyonwin);
	props->AddInt32("ptaddcards", ptaddcards);
	props->AddInt32("ptremovecards", ptremovecards);
	
	if (popping) 
	{
		BMessage* poppingmsg = new BMessage();
		poppingmsg->AddInt32("numtimes", popping->numtimes);
		poppingmsg->AddInt32("numcards", popping->numcards);
		poppingmsg->AddString("toID", popping->toID);
		
		props->AddMessage("popping", poppingmsg);
	};

	if (ordering)
	{
		BMessage* tempmsg = ordering->Encapsulate();
		props->AddMessage("ordering", tempmsg );		
	};
	
	return props;
};

void pile_props::UnEncapsulate(BMessage* props)
{
	props->FindString("IDstring", (const char**) &IDstring);
	props->FindString("dealstring", (const char**) &dealstring);
	props->FindInt32("req_orient", &req_orient);
	props->FindBool("flip_to_orient", &flip_to_orient);
	props->FindPoint("offsetup", &offsetup);
	props->FindPoint("offsetdown", &offsetdown);
	
	props->FindBool("emptyonwin", &emptyonwin);
	props->FindInt32("ptaddcards", &ptaddcards);
	props->FindInt32("ptremovecards", &ptremovecards);
	
	int32 tempval;
	status_t errcode;

	tempval = 0;
	int index = 0;
	errcode = B_OK;
	emptyacceptvalue.clear();
	while (errcode == B_OK)
	{
		errcode = props->FindInt32("emptyacceptvalue", index++, &tempval);
		if (errcode == B_OK) emptyacceptvalue.push_back(tempval);	
	};

	tempval = 0;
	index = 0;
	errcode = B_OK;
	emptyacceptsuit.clear();
	while (errcode == B_OK)
	{
		errcode = props->FindInt32("emptyacceptsuit", index++, &tempval);
		if (errcode == B_OK) emptyacceptsuit.push_back(tempval);	
	};
	
	BMessage* poppingmsg = new BMessage();
	errcode = props->FindMessage("popping", poppingmsg);
	if (errcode == B_OK) 
	{
		popping = new card_pop_prop;
		poppingmsg->FindInt32("numtimes", &(popping->numtimes));
		poppingmsg->FindInt32("numcards", &(popping->numcards));
		poppingmsg->FindString("toID", (const char**) &(popping->toID));
	}
	else popping = NULL;

	BMessage* orderingmsg = new BMessage();
	errcode = props->FindMessage("ordering", orderingmsg);		
	if (errcode == B_OK)
	{
		ordering = new order_props();
		ordering->UnEncapsulate(orderingmsg);
	}
	else ordering = NULL;
};
