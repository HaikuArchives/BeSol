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


#ifndef IEWINDOW
#define IEWINDOW
#include <IEWindow.h>
#endif

#ifndef SOLWINDOWDEFS
#define SOLWINDOWDEFS
#include "BesolWindowDefs.h"
#endif

#ifndef RULEEDITWINDOWDEFS
#define RULEEDITWINDOWDEFS
#include "TransmissionRuleEditor.h"
#endif

#ifndef PILE_CLASS
#define PILE_CLASS

#include <Menu.h>
#include <PopUpMenu.h>
#include <View.h>
#include <MenuItem.h>
#include <list.h>

#include "TRANSRULES.h"
#include "PileEditor.h"
#include "other project defs.h"
#include "deck_struct.h"

#include "prop_struct.h"
#include "CARD.h"
#include "DECK.h"


class PILE : public BView
{
	public:

void AllRuleCheck();




		PILE(BRect frame, pile_props* props);
		PILE(BMessage* archive);
		~PILE();
		virtual void MessageReceived(BMessage* message);
		void construction_helper(pile_props* props);
		void AddCard(CARD* card);
		void RemoveCard(CARD* card);
		void Deal();
		void Clear();
		virtual status_t Archive(BMessage* archive, bool deep = false) const;
		static BArchivable* Instantiate(BMessage *archive);
		static void Set_Editing(int32 typeedit, bool editstate, PILE* firstpile);
		static void Set_Deck(DECK* dck);
		static BBitmap* empty;
		static BBitmap* cont;	
		static BBitmap* stop;	
		virtual void Draw(BRect updateRect);
		TRANSRULES* get_rules(int32 findx, int32 findy, list< list<TRANSRULES*> >::iterator &toiter, 
			list<TRANSRULES*>::iterator &fromiter, int startx = -1, int starty = -1);
	private:
		static int16 numpiles;
		static list< list<TRANSRULES*> >* allrules;
		static list< BView* > orderinallrules;
		static deck_info thedeckinfo;//put this in GUI later... ver2, will help err check deck loading... find all instances that getinfo from deck
		static DECK* thedeck;
		static int32 editing;
		static TransmissionRuleEditor* reditor;
		static PileEditor* peditor;
		bool isbeingedited;
		bool cardmatch(CARD* incumbent, CARD* card, order_props* ordering, pile_props* newpileprops);
		uint32 action_on_MD;
		pile_props* properties;
		BPopUpMenu* popmenu;
		virtual void MouseDown(BPoint location);
};

#endif