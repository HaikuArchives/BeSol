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


#include "order_struct.h"

BMessage* order_props::Encapsulate()
{
	BMessage* orderingmsg = new BMessage();
	orderingmsg->AddBool("cyclesuits", cyclesuits);
	orderingmsg->AddBool("cyclevalues", cyclevalues);

	list <int32>::iterator iter;
	iter = valuesteps.begin();
	while (iter != valuesteps.end())
	{
		orderingmsg->AddInt32("valuesteps", *(iter++));
	};

	iter = suitsteps.begin();
	while (iter != suitsteps.end())
	{
		orderingmsg->AddInt32("suitsteps", *(iter++));
	};
	
	return orderingmsg;
};

void order_props::UnEncapsulate(BMessage* orderingmsg)
{
	orderingmsg->FindBool("cyclesuits", &cyclesuits);
	orderingmsg->FindBool("cyclevalues", &cyclevalues);

	int32 tempval = 0;
	int index = 0;
	status_t errcode;
	errcode = B_OK;
	valuesteps.clear();
	while (errcode == B_OK)
	{
		errcode = orderingmsg->FindInt32("valuesteps", index++, &tempval);
		if (errcode == B_OK) valuesteps.push_back(tempval);	
	};

	tempval = 0;
	index = 0;
	errcode = B_OK;
	suitsteps.clear();
	while (errcode == B_OK)
	{
		errcode = orderingmsg->FindInt32("suitsteps", index++, &tempval);
		if (errcode == B_OK) suitsteps.push_back(tempval);	
	};
};