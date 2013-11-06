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


#include <Bitmap.h>
#include <View.h>
#include "other project defs.h"

#ifndef CARD_CLASS
#define CARD_CLASS

struct card_data 
{
	BBitmap* front;
	BBitmap* back;
	int32 suit;
	int32 value;
	BPoint size;
};

class CARD : public BView
{
	public:
		CARD(card_data* data, bool fup);
		card_data get_data();
		virtual void Draw(BRect updateRect);
		bool face_up;
	private:
		card_data* card;
		virtual void MouseDown (BPoint location);
};

#endif
