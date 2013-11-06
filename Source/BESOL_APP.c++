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

#include "BESOL_APP.h"

IEResourceHandler *resourcehandler;

int main()
{
	BESOL_APP besol(0);//have no clue why this constructor needs an argument... won't compile without
	besol.Run();

	return 0;
};

BESOL_APP::BESOL_APP(int WTF) : IEApplication ("application/x-vnd.RunTime_Productions-BeSol"),
	thedeck(NULL)
{
	mainwindow = new BesolWindow();
};

void BESOL_APP::AboutRequested()
{
	char* string = "Run-Time Productions presents: Be Solitaire	by: Jason Wrinkle (jwrinkle@utdallas.edu)";
	BAlert*	alert = new BAlert ("about window", string, "cool!");
	alert->Go();
};

void BESOL_APP::MessageReceived(BMessage* message)
{
	switch (message->what)
	{
		case IE_BESOLWINDOW_SOLMENU_EDIT_EDIT_CURRENT_RULES:
		case IE_BESOLWINDOW_SOLMENU_EDIT_EDIT_CURRENT_LAYOUT:
		{
			bool editmode;
			message->FindBool ("editmode", &editmode);
			mainwindow->Lock();
			PILE* first = static_cast<PILE*> (mainwindow->ChildAt(2)->ChildAt(0));
			mainwindow->Unlock();
			PILE::Set_Editing (message->what, editmode, first);
			break;
		};
		case IE_BESOLWINDOW_SOLMENU_GAME_NEW:
		{
//FEATURE: let user enter seed!!!
			random_shuffle(thedeck->deck.begin(), thedeck->deck.end());
			thedeck->deckiter = thedeck->deck.begin();
			mainwindow->Lock();
			BView* tempview = mainwindow->ChildAt(2);
			PILE* pile;
			for (int i = 0; i < tempview->CountChildren(); i++)
			{
				pile = static_cast<PILE*>( tempview->ChildAt(i) );
				pile->Clear();
				pile->Deal();	
			};
			mainwindow->Unlock();
			break;
		};
		case NEW_PILE:
		{
			status_t errcode;
			pile_props* props = new pile_props();
			BMessage* pilemsg = new BMessage();
			errcode = message->FindMessage("pile props", pilemsg);

			BPoint location;
			message->FindPoint("location", &location);
			mainwindow->Lock();
			if (location == GET_CURSOR_POINT)
			{
				uint32 buttons;			
				mainwindow->ChildAt(2)->GetMouse(&location, &buttons, false);
			};

			if (errcode == B_OK) props->UnEncapsulate(pilemsg);
			BRect frame;
			if (thedeck != NULL) frame = BRect(location, BPoint(location.x + thedeck->get_info()->cardsize.x, location.y + thedeck->get_info()->cardsize.y) );			
			else frame = BRect(location, BPoint(location.x + 50, location.y + 50) );
			PILE* newpile = new PILE(frame, props);

			mainwindow->ChildAt(2)->AddChild(newpile);
			newpile->MoveTo(location);
			mainwindow->Unlock();
			break;
		};
		case DECK_REF_RECEIVED:
		{
			entry_ref resourceref;
			message->FindRef("refs", &resourceref);		
			BFile deckfile (&resourceref, B_READ_ONLY);
			BResources* deckresources = new BResources(&deckfile, false);		

			if (thedeck != NULL) delete (thedeck);

			thedeck = new DECK(deckresources, PILE::empty, PILE::cont, PILE::stop);
			
			PILE::Set_Deck(thedeck);
			break;
		};
		default:
		{
			IEApplication::MessageReceived(message);
			break;
		};
	};
};
