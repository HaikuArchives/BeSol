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


#ifndef DECK_CLASS
#define DECK_CLASS

#include <vector.h>
#include <Resources.h>
#include <TranslationUtils.h>
#include <Beep.h>

#include "CARD.h"
#include "deck_struct.h"

class DECK
{
	public:
		DECK(BResources* deckresources, BBitmap* &pempty, BBitmap* &pcont, BBitmap* &pstop);
		~DECK();
		deck_info* get_info();
//	private: //BAD enginering... this needs to be replaced with set and get functions, I was just too lazy at the time
		deck_info info;
		vector <card_data> deck;
		vector <card_data>::iterator deckiter;
};
#endif