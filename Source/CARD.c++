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


#include "CARD.h"

CARD::CARD(card_data* data, bool fup) : BView(BRect(0, 0, data->size.x, data->size.y), "card view", B_FOLLOW_NONE, B_WILL_DRAW),
	face_up(fup), card(data)
{
	SetViewColor(B_TRANSPARENT_COLOR);
	Show();
};

card_data CARD::get_data() //note doesn't return bmps... add in a copy constructor maybe
{
	card_data tempdata = *card;
	tempdata.front = tempdata.back = NULL;
	return tempdata;
};

void CARD::Draw(BRect updateRect)
{
	if (Bounds().Contains(updateRect))
	{
		SetViewColor(200, 200, 150, 0);
	
		if (face_up) DrawBitmapAsync(card->front, BPoint(0, 0));
		else DrawBitmapAsync(card->back, BPoint(0, 0));
	};
};

void CARD::MouseDown(BPoint location)
{
	BMessage* message;
	message = new BMessage(CARD_MSG);

	BPoint parentloc = ConvertToParent(location);
	BView* currentview = this;
	BView* prevview = NULL;	
	bool cont = true;
	BRect dragregion;
	int32 numpilecards = Parent()->CountChildren(), numdrgcards = 0;

	message->AddInt32 ("numcards in pile", numpilecards);
	message->AddPointer("from", Parent());
	
	while ((currentview) && (cont))
	{
		prevview = currentview;
		currentview = currentview->NextSibling();				
		if (currentview) cont = currentview->Frame().Contains(parentloc);
	};
	
	message->AddPointer("card", prevview);
	numdrgcards++;
	dragregion = prevview->Frame();
	
	while (currentview) 
	{
		message->AddPointer("card", currentview);
		numdrgcards++;
		dragregion = dragregion|currentview->Frame();
		currentview = currentview->NextSibling();
	};
	
	message->AddInt32 ("numcards dragged", numdrgcards);
//this needs to be changed to DragBitmap(), but bitmap passed needs to be a copy of the current one (and include all cards etc...)	
	DragMessage(message, ConvertFromParent(dragregion));
};