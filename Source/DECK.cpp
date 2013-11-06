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


#include "DECK.h"

DECK::DECK(BResources* deckresources, BBitmap* &pempty, BBitmap* &pcont, BBitmap* &pstop)
{
	size_t lengthlong = 4;
	int* tempint;
	
	tempint = (static_cast<int*> (deckresources->FindResource('LONG', (int32) 0, &lengthlong)));
	info.num_values = *tempint;
	delete (tempint);
	
	tempint = (static_cast<int*> (deckresources->FindResource('LONG', 1, &lengthlong)));
	info.num_suits = *tempint;
	delete (tempint);

	tempint = (static_cast<int*> (deckresources->FindResource('LONG', 2, &lengthlong)));
	info.cardsize.x = *tempint;
	delete(tempint);

 	tempint = (static_cast<int*> (deckresources->FindResource('LONG', 3, &lengthlong)));
	info.cardsize.y = *tempint;
	delete(tempint);
	
	int32 cardID;
	void* temp = NULL;
	BBitmap* back = NULL;
	card_data* card;
	size_t lengthfound;

//back isn't deleted anywhere
	temp = deckresources->FindResource('CBck', (int32) 0, &lengthfound);
	back = BTranslationUtils::GetBitmap (&BMemoryIO (temp, lengthfound));

	temp = deckresources->FindResource('PBck', (int32) 0, &lengthfound);
	pempty = BTranslationUtils::GetBitmap (&BMemoryIO (temp, lengthfound));

	temp = deckresources->FindResource('PBck', (int32) 1, &lengthfound);
	pcont = BTranslationUtils::GetBitmap (&BMemoryIO (temp, lengthfound));

	temp = deckresources->FindResource('PBck', (int32) 2, &lengthfound);
	pstop = BTranslationUtils::GetBitmap (&BMemoryIO (temp, lengthfound));

//	deckresources.PreloadResourceType(B_RAW_TYPE); //this might speed up performance... not sure if I am using it right
	for (int s = 0; s < info.num_suits; s++)
	{
		for (int v = 0; v < info.num_values; v++)
		{
			cardID = s*info.num_values + v;
			temp = deckresources->FindResource(B_RAW_TYPE, cardID, &lengthfound);
			
			card = new card_data;
			card->size = info.cardsize;
			card->back = back;
			card->front = BTranslationUtils::GetBitmap (&BMemoryIO (temp, lengthfound));
			card->suit = s;
			card->value = v;
			deck.push_back(*card);
			delete (temp);										
		};
	};
};

DECK::~DECK()
{
	deckiter = deck.begin();
	while (deckiter != deck.end())
	{
		if (deckiter->front) delete deckiter->front;
		if (deckiter->back) delete deckiter->back;
		deckiter++;
	};
	deck.clear();
};

deck_info* DECK::get_info()
{
	deck_info* returninfo = new deck_info;
	returninfo->num_values = info.num_values;
	returninfo->num_suits = info.num_suits;
	returninfo->cardsize = info.cardsize;	
	return returninfo;
};