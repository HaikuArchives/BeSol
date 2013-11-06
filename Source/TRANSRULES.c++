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


#include "TRANSRULES.h"

TRANSRULES::TRANSRULES(TRANSRULES &old) : enable(old.enable), 
	behavior(old.behavior), mincards(old.mincards), maxcards(old.maxcards), 
	orderingtype(old.orderingtype)
{
	if (old.ordering) 
	{	
		ordering = new order_props;
		*ordering = *(old.ordering);
	}
	else ordering = NULL;
};

TRANSRULES::TRANSRULES() : enable(true), behavior(BLOCK_DRAG), 
	mincards(0), maxcards(-1), 
	orderingtype(ORDERINGNONE), ordering(NULL)
{};

BMessage* TRANSRULES::Encapsulate()
{
	BMessage* message = new BMessage();
	
	message->AddBool("enable", enable);
	message->AddInt32("behavior", behavior);
	message->AddInt32("mincards", mincards);
	message->AddInt32("maxcards", maxcards);
	
	if (orderingtype == ORDERINGSOME) message->AddMessage("ordering", ordering->Encapsulate());
	message->AddInt32("orderingtype", orderingtype);
	
	return message;
};

void TRANSRULES::UnEncapsulate(BMessage* rules)
{
	rules->FindBool("enable", &enable);
	rules->FindInt32("behavior", &behavior);
	rules->FindInt32("mincards", &mincards);
	rules->FindInt32("maxcards", &maxcards);
	
	status_t errcode;
	BMessage* orderingmsg = new BMessage();
	errcode = rules->FindMessage("ordering", orderingmsg);		
	if (errcode == B_OK)
	{
		ordering = new order_props();
		ordering->UnEncapsulate(orderingmsg);
	}
	rules->FindInt32("orderingtype", &orderingtype);
};