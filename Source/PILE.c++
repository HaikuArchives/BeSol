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


#include "PILE.h"


void PILE::AllRuleCheck() //this is a debugging tool function... not used by actual program... check validity of 2-D list
{
list< list<TRANSRULES*> >::iterator toiter = allrules->begin();
list<TRANSRULES*>::iterator fromiter;

list< list<TRANSRULES*> >::iterator footoiter;
list<TRANSRULES*>::iterator foofromiter;

TRANSRULES* rules;
int32 to = 0, from = 0;
int total = 0;

while (toiter != allrules->end())
{
	fromiter = toiter->begin();
	while (fromiter != toiter->end())
	{
		rules = *fromiter;		
		get_rules (to, from, footoiter, foofromiter, (from == 0 ? to - 1 : to), from - 1);
total++;
//		if ((fromiter == foofromiter) && (toiter == footoiter) && (rules->maxcards == from) && (rules->mincards == to) ) beep();
//beep();
//		snooze(500000);

		fromiter++;
		from++;


	};
	from = 0;
	toiter++;
	to++;
};

total = total;
};


BBitmap* PILE::empty = NULL;
BBitmap* PILE::cont = NULL;
BBitmap* PILE::stop = NULL;
PileEditor* PILE::peditor = NULL;
TransmissionRuleEditor* PILE::reditor = NULL;
int32 PILE::editing = 0;
list< list<TRANSRULES*> >* PILE::allrules;
int16 PILE::numpiles = 0;
list< BView* > PILE::orderinallrules;
deck_info thedeckinfo;

void PILE::Set_Editing(int32 typeedit, bool editstate, PILE* firstpile)
{
	BMenuItem* item;
	BWindow* editwindow = NULL;
	
	switch (typeedit)
	{
		case IE_BESOLWINDOW_SOLMENU_EDIT_EDIT_CURRENT_LAYOUT:
		{
			editing = editstate;
			if (peditor == NULL) peditor = new PileEditor();

			editwindow = peditor;
		
			if (!editstate) 
			{
				peditor->CleanUp();
				
				list <BView*>::iterator piter1 = peditor->targets.begin();
				list <BView*>::iterator piter2 = piter1;
				while (piter1 != peditor->targets.end())
				{
					item = (static_cast <PILE*> (*piter1))->popmenu->FindItem(POP_EDIT);
					item->SetMarked(false);
					piter2++;
					static_cast <PILE*> (*piter1)->isbeingedited = false;
					peditor->Remove_Target(*piter1);
					piter1 = piter2;				
				};
			};
			break;
		};
		case IE_BESOLWINDOW_SOLMENU_EDIT_EDIT_CURRENT_RULES:
		{
			if (reditor == NULL) reditor = new TransmissionRuleEditor();
		
			editwindow = reditor;
			reditor->Set_Target(firstpile);
			
			if (!editstate) 
			{
				reditor->CleanUp();
			};
			break;
		};
	};
		
	if (editstate) 
	{			
		PILE* currentpile = firstpile;
		BMessage* msg = new BMessage(LAYOUT_DATA);
		deck_info dinfo;
		if (thedeck != NULL) dinfo = *(thedeck->get_info());
		else
		{
			dinfo.num_suits = 0;
			dinfo.num_values = 0;
			dinfo.cardsize = BPoint(10, 10);
		};
		msg->AddData("deck info", 'DkDt', (void**) &(dinfo), sizeof(deck_info));
		while (currentpile)
		{
			currentpile->Clear();
			msg->AddString("IDstring", currentpile->properties->IDstring);
	
			currentpile = static_cast <PILE*> (currentpile->NextSibling());
		};
		
		editwindow->PostMessage(msg);
		editwindow->Show();
	}
	else
	{
		editwindow->Hide();
		if (firstpile) 
		{	
			firstpile->Window()->Lock();
			firstpile->Window()->ChildAt(2)->Invalidate();
			firstpile->Window()->Unlock();
		};
	};
};

BArchivable* PILE::Instantiate(BMessage *archive)
{
    if ( validate_instantiation(archive, "PILE") ) return new PILE(archive);
    else return NULL; 	
};

PILE::PILE(BRect frame, pile_props* props = NULL) : BView (frame, "Pile View", B_FOLLOW_NONE, B_WILL_DRAW),
	isbeingedited(false), action_on_MD(EDITING)
{
	numpiles++;
	
	construction_helper(props);
	Show();
};
  
PILE::PILE(BMessage* archive) : BView (BRect(0, 0, 1, 1), "Pile View", B_FOLLOW_NONE, B_WILL_DRAW),
	isbeingedited(false), action_on_MD(WAITFOREDIT)
{
	numpiles++;
	
	BRect frame;
	pile_props* props = new pile_props();	
	BMessage* pilemsg = new BMessage();
	status_t errcode;

	errcode = archive->FindMessage("pile props", pilemsg);
	if (errcode == B_OK) props->UnEncapsulate(pilemsg);
	
	archive->FindRect("frame", &frame);
	if (thedeck != NULL) frame = BRect (frame.LeftTop(), BPoint(frame.LeftTop().x + thedeck->get_info()->cardsize.x, frame.LeftTop().y + thedeck->get_info()->cardsize.y) );
	
	construction_helper(props);
	MoveTo(frame.LeftTop());
	ResizeTo(frame.Width(), frame.Height());
	Show();
};

void PILE::construction_helper(pile_props* props)
{
	SetViewColor(0, 0, 0, 255);

	if (allrules == NULL) allrules = new list< list<TRANSRULES*> >;
	list< list<TRANSRULES*> >::iterator iter1 = allrules->begin();
	list<TRANSRULES*> templist;
	
	templist.push_back(new TRANSRULES());
	while (iter1 != allrules->end()) 
	{
		iter1->push_back(new TRANSRULES());
		templist.push_back(new TRANSRULES());
		iter1++;
	};
	allrules->push_back(templist);
	orderinallrules.push_back( (BView*) this );	

	if (peditor != NULL)
	{
		BMessage* msg = new BMessage();
		msg->AddString("IDstring", props->IDstring);
		peditor->piles_added(msg);	
	};

	properties = props;

	popmenu = new BPopUpMenu("StackPile Pop-up");
	BMenuItem* item;
	
	item = new BMenuItem("Copy", new BMessage(POP_COPY));
	item->SetTarget(be_app);
	popmenu->AddItem(item);
	
	item = new BMenuItem("Move", new BMessage(POP_MOVE)); 		
	item->SetTarget(be_app);
	popmenu->AddItem(item);
	
	item = new BMenuItem("Edit", new BMessage(POP_EDIT)); 		
	item->SetTarget(be_app);
	popmenu->AddItem(item);

	item = new BMenuItem("Delete", new BMessage(POP_DELETE)); 		
	item->SetTarget(be_app);
	popmenu->AddItem(item);
};

PILE::~PILE()
{
	BMenuItem* item = popmenu->FindItem(POP_EDIT);
	if ( item->IsMarked() ) peditor->Remove_Target(cast_as(this, BView));

	list< list<TRANSRULES*> >::iterator itert = allrules->begin();
	list<TRANSRULES*>::iterator iterf;
	list<BView*>::iterator oinalliter = orderinallrules.begin();
	int32 index = 0;
			
	while ((index < numpiles) && (*oinalliter != (BView*) this))
	{
		oinalliter++;
		index++;
		itert++;
	};
	
	numpiles--;
	orderinallrules.remove((BView*)this);
	iterf = itert->begin();
	while (iterf != itert->end())
	{
		if (*iterf) delete (*iterf);
		iterf++;
	};
	allrules->erase(itert);

	itert = allrules->begin();
	for (int32 t = 0; t < numpiles; t++)
	{
		itert->remove( get_rules(t, index, itert, iterf, t - 1) );
	};
	
	
	if (peditor != NULL) peditor->pile_removed(index);
};

status_t PILE::Archive(BMessage* archive, bool deep) const
{
	BView::Archive(archive, deep);
		 
	archive->AddString("class", "PILE");

	BMessage* pilemsg = properties->Encapsulate();
	archive->AddMessage("pile props", pilemsg);	
	archive->AddRect("frame", Frame());
	
	return B_OK;
};

void PILE::Clear()
{
	Window()->Lock();
	int numkids = CountChildren();
	CARD* tempcard;
	
	for (int i = 0; i < numkids; i++)
	{
		tempcard = static_cast <CARD*> (ChildAt(0));
		RemoveCard(tempcard);
		delete tempcard;
	};
	Window()->Unlock();
};

TRANSRULES* PILE::get_rules(int32 findx, int32 findy, list< list<TRANSRULES*> >::iterator &toiter, 
	list<TRANSRULES*>::iterator &fromiter, int startx, int starty)
{
	if (startx == -1) 
	{
		toiter = allrules->begin();
		startx = 0;
	};
	for (int t = startx; t < findx; t++) toiter++;
	if (starty == -1)
	{
		fromiter = toiter->begin();
		starty = 0;
	};
	for (int f = starty; f < findy; f++) fromiter++;

	return *fromiter;
};

void PILE::Deal()
{
	int index = 0;
	int num = -1;

	bool fup = false;
	bool get = false;
	CARD* card;
		
	while (properties->dealstring[index] != '\0')
	{
		switch (properties->dealstring[index])
		{
			case 'u' :
			case 'd' :
			{
				fup = (properties->dealstring[index] == 'u');
				get = true;
				if (num < 0) num = 1;
				break;
			};
			case '#' :
			{
				num = 0;
				break;
			};
			case '0': case '1': case '2': case '3': case '4':
			case '5': case '6': case '7': case '8': case '9':
			{
				if (num > -1) num = 10*num + (properties->dealstring[index] - '0');
				break;
			};
			default:
			{
				get = false;
				num = -1;
				break;
			};
		};
		
		if (get)
		{			
			for (int i = 0; i < num; i++)
			{
				card = new CARD(thedeck->deckiter++, fup);
				AddCard(card);
			};
			num = -1;
			get = false;
		};
		index++;
	};
};

DECK* PILE::thedeck;

void PILE::Set_Deck(DECK* dck)
{
	thedeck = dck;
};

bool PILE::cardmatch(CARD* incumbent, CARD* card, order_props* ordering, pile_props* newpileprops)
{
	bool qualify = true;

	if ((qualify) && !(newpileprops->flip_to_orient))
		switch (newpileprops->req_orient)
		{
			case IE_PILEEDITOR_NEWCARDSORIENTATION_FACE_UP:
				qualify = (card->face_up == true);
				break;
			case IE_PILEEDITOR_NEWCARDSORIENTATION_FACE_DOWN:
				qualify = (card->face_up == false);
				break;
			case IE_PILEEDITOR_NEWCARDSORIENTATION_NO_PREF_:
				break;
		};
	
	if (qualify)
	{	
		if (incumbent)
		{
			if (ordering)
			{
				list <int32>::iterator vstepfnd, sstepfnd;
				int32 actvstep, actsstep;

				actvstep = card->get_data().value - incumbent->get_data().value;
				actsstep = card->get_data().suit - incumbent->get_data().suit;
				if (ordering->cyclevalues) 
				{
					actvstep += thedeck->get_info()->num_values;
					actvstep = actvstep % thedeck->get_info()->num_values;
				};
				if (ordering->cyclesuits)
				{
					actsstep += thedeck->get_info()->num_suits;
 					actsstep = actsstep % thedeck->get_info()->num_suits;
 				};
				
				vstepfnd = find(ordering->valuesteps.begin(), ordering->valuesteps.end(), actvstep);
				sstepfnd = find(ordering->suitsteps.begin(), ordering->suitsteps.end(), actsstep);
				qualify = ( (ordering->valuesteps.end() != vstepfnd) && (ordering->suitsteps.end() != sstepfnd) );
				
				if (!qualify)
				{
					if (ordering->cyclevalues) 
					{
						actvstep -= thedeck->get_info()->num_values;
					};
					if (ordering->cyclesuits)
					{
						actsstep -= thedeck->get_info()->num_suits;
	 				};
					vstepfnd = find(ordering->valuesteps.begin(), ordering->valuesteps.end(), actvstep);
					sstepfnd = find(ordering->suitsteps.begin(), ordering->suitsteps.end(), actsstep);
					qualify = ( (ordering->valuesteps.end() != vstepfnd) && (ordering->suitsteps.end() != sstepfnd) );
				};
			};
		}
		else
		{
			list <int32>::iterator vaoefnd, saoefnd;
			
			vaoefnd = find(newpileprops->emptyacceptvalue.begin(), newpileprops->emptyacceptvalue.end(), card->get_data().value);
			saoefnd = find(newpileprops->emptyacceptsuit.begin(), newpileprops->emptyacceptsuit.end(), card->get_data().suit);
	
			qualify = ( (newpileprops->emptyacceptvalue.end() != vaoefnd) && (newpileprops->emptyacceptsuit.end() != saoefnd) );		
		};
	};
	return qualify;
};

void PILE::MessageReceived(BMessage* message)
{
	switch (message->what)
	{
		case RULES_LOAD:
		{		
			list< list<TRANSRULES*> >::iterator toiter = allrules->begin();
			list<TRANSRULES*>::iterator fromiter;
			TRANSRULES *oldrules, *newrules;
			BMessage* rulemsg = new BMessage();
			int16 nmpls;
			status_t errcode;
						
			toiter = allrules->begin();
			message->FindInt16("numpiles", &nmpls);
			for (int t = 0; t < nmpls; t++)
			{
				for (int f = 0; f < nmpls; f++)
				{
					errcode = message->FindMessage("rule", nmpls*t + f, rulemsg);
					if (errcode == B_OK)
					{
						newrules = new TRANSRULES();
						newrules->UnEncapsulate(rulemsg);
						oldrules = get_rules(t, f, toiter, fromiter, (f == 0 ? t - 1 : t), f - 1);
						*fromiter = newrules;
						delete oldrules;
					};
				};
			};	
//AllRuleCheck();		
			break;
		};
		case RULES_SAVE:
		{
			list < list <TRANSRULES*> >::iterator toiter;
			list <TRANSRULES*>::iterator fromiter;
			BMessage* rulemsg;
			TRANSRULES* temprules;

			for (int t = 0; t < numpiles; t++)
			{
				for (int f = 0; f < numpiles; f++)
				{
//Ugh... shot self in foot... maybe change Encapsulate behavior (uniformly) later so that it doesn't allocate its own BMessage
					temprules = get_rules(t, f, toiter, fromiter, (f == 0 ? t - 1 : t), f - 1);
					if (temprules)
					{
						rulemsg = temprules->Encapsulate();
						message->AddMessage("rule", rulemsg);
						delete rulemsg;
					};
				};
			};	
			break;
		};
		case RULES_UPDATE:
		{
			BMessage* rulemsg = new BMessage();
			bool makesym = false;

			int32 to, from;
			message->FindInt32("to", &to);
			message->FindInt32("from", &from);
//AllRuleCheck();		
			message->FindMessage("rules", rulemsg);	
			message->FindBool("makesym", &makesym);
			TRANSRULES* newrules;
			TRANSRULES* oldrules;
			list< list<TRANSRULES*> >::iterator toiter; 
			list<TRANSRULES*>::iterator fromiter;	

			newrules = new TRANSRULES();
			newrules->UnEncapsulate(rulemsg);
			oldrules = get_rules (to, from, toiter, fromiter);
			*fromiter = newrules;
			if (oldrules) delete oldrules;
			break;
		};
		case RULES_REQUEST:
		{
			list < list <TRANSRULES*> >::iterator toiter;
			list <TRANSRULES*>::iterator fromiter;
			int32 to, from;
			
			message->FindInt32("to", &to);
			message->FindInt32("from", &from);
			message->MakeEmpty();
			TRANSRULES* temprules = get_rules(to, from, toiter, fromiter);
			if (temprules)
			{
				message->AddMessage("rules", temprules->Encapsulate());
				reditor->PostMessage(message);
			};
			break;
		};
		case CARD_MSG:
		{
			CARD* crd;
			status_t errcode;
			TRANSRULES* activerules = NULL;
			order_props* firstordering = NULL;
			PILE* frompile;
			list < list <TRANSRULES*> >::iterator toiter = allrules->begin();
			list <TRANSRULES*>::iterator fromiter;
			list<BView*>::iterator oinalliter = orderinallrules.begin();
			int to = -1, from = -1;
			int index;
			bool transvalid = true;
			
			message->FindPointer("from", (void**) &frompile);
			for (int i = 0; i < numpiles; i++)
			{
				if (*oinalliter == this) to = i;
				if (*oinalliter == frompile) from = i;
				oinalliter++;
				toiter++;
			};
			activerules = get_rules(to, from, toiter, fromiter);
			if (this != frompile) firstordering = properties->ordering;
			else firstordering = activerules->ordering;
						
			if (activerules) 
			{
				switch (activerules->orderingtype)
				{
					case ORDERINGNONE:	// 'Ordering - None' is pressed...
						activerules->ordering = NULL;
						break;
					case ORDERINGSEND:	// 'Ordering - sender' is pressed...
						activerules->ordering = frompile->properties->ordering;
						break;
					case ORDERINGRECV:	// 'Ordering - receiver' is pressed...
						activerules->ordering = properties->ordering;
						break;
					case ORDERINGSOME:	// 'Ordering - Some' is pressed...
						break;
				}; 
				
				transvalid = activerules->enable;
				if (transvalid)
				{
					CARD* incumbent = static_cast <CARD*> (ChildAt(CountChildren() - 1));
					index = 0;
					int32 numdrgcards, numpilecards;				
					
					message->FindInt32 ("numcards dragged", &numdrgcards);
					message->FindInt32 ("numcards in pile", &numpilecards);//there seems to be a slight bug in here somewhere... see the deck and deck:1 transmissions in solitaire for example
					if (activerules->mincards != -1) transvalid = (activerules->mincards <= numdrgcards);
					else transvalid = (numdrgcards == numpilecards);//maybe add a prohibition variable that prevents this "leniency"
					if ((activerules->maxcards != -1) && (transvalid)) transvalid = (numdrgcards <= activerules->maxcards);

					errcode = message->FindPointer("card", index++, (void**) &crd);
					if (errcode == B_OK)
					{
						transvalid = cardmatch(incumbent, crd, firstordering, this->properties);
						incumbent = crd;
						errcode = message->FindPointer("card", index++, (void**) &crd);
					};
					while ( (errcode == B_OK) && (transvalid) )
					{//this behavior is "block drag"... userfriendly will need to move cards around... might be best to do this for block drag also
						transvalid = cardmatch(incumbent, crd, activerules->ordering, this->properties);
						incumbent = crd;
						errcode = message->FindPointer("card", index++, (void**) &crd);
					};
				};
			}

			if (transvalid)
			{
				index = 0;
				errcode = message->FindPointer("card", index++, (void**) &crd);
				while (errcode == B_OK)
				{
					AddCard(crd);
		
					errcode = message->FindPointer("card", index++, (void**) &crd);
				};
			}
			else beep(); //dialog box goes here
			break;
		};
		case IE_PILEEDITOR_UPDATE:
		{
			status_t errcode;
			BMessage* pilemsg = new BMessage();
			int32 number;
			
			message->FindInt32("number", &number);
			errcode = message->FindMessage("pile props", pilemsg);
			if (errcode == B_OK) 
			{
				properties->UnEncapsulate(pilemsg);
				if (number > 0) 
				{
					properties->IDstring = mystrconcat(properties->IDstring, " : ");
					properties->IDstring = mystrconcat(properties->IDstring, IntToStr(number));					
				};
			}
			else beep();

			break;
		};
		case GAME_SAVE:
		{
			BMessage* archive = new BMessage();
			Archive(archive, true);
			
			message->AddMessage("Pile", archive);
			break;
		};
		case LAYOUT_SAVE:
		{
			BMessage* archive = new BMessage();
			Archive(archive, false);
			
			message->AddMessage("Pile", archive);
			break;
		};
		case POP_COPY :
		{
			action_on_MD = POP_COPY;
			break;
		};
		case POP_MOVE :
		{
			action_on_MD = POP_MOVE;
			break;
		};
		case POP_EDIT : 
		{
			BMenuItem* item = popmenu->FindItem(POP_EDIT);
			item->SetMarked( !(item->IsMarked()) );
			BView* temp = cast_as (this, BView);
			isbeingedited = !isbeingedited;
			Invalidate(Bounds());
			
			message->MakeEmpty();
			
			if ( item->IsMarked() )
			{
				peditor->Add_Target(temp);
				if (properties != NULL)
				{
					BMessage* pilemsg = properties->Encapsulate();
					message->AddMessage("pile props", pilemsg);	
					peditor->PostMessage(message);
				}
				else beep();
			}
			else peditor->Remove_Target(temp);
			
			
			break;
		};
		case POP_DELETE : 
		{	
			RemoveSelf();
			delete (this);
			break;
		};
	};
};

void PILE::RemoveCard(CARD* card)
{
	BPoint temp(0, 0);

	CARD* prevcard = static_cast <CARD*> (card->PreviousSibling());
	CARD* nextcard = static_cast <CARD*> (card->NextSibling());	
	
	if (nextcard) 
	{
		if (card->face_up) temp -= properties->offsetup;
		else temp -= properties->offsetdown;

		nextcard->MoveTo(card->LeftTop());
	}
	else if (prevcard)
	{
		if (prevcard->face_up) temp -= properties->offsetup;
		else temp -= properties->offsetdown;
	};

	ResizeBy(temp.x, temp.y);

	RemoveChild(card);
	Invalidate();
};

void PILE::AddCard(CARD* card)
{
	PILE* parentpile = static_cast<PILE*> (card->Parent());

	if (parentpile != this) 
	{
		if (parentpile) parentpile->RemoveCard(card);

		AddChild(card);
		CARD* prevcard = static_cast <CARD*> (card->PreviousSibling());
		BPoint offset(0, 0);
	
		if (CountChildren() > 1)
		{
			if (prevcard->face_up) offset = BPoint(properties->offsetup);
			else offset = BPoint(properties->offsetdown);

			ResizeBy(offset.x, offset.y);
	
			offset += prevcard->Frame().LeftTop();
		};
		card->MoveTo(offset);
	};

	if (parentpile)
	{
		if (properties->flip_to_orient) 
		{
			switch (properties->req_orient)
			{
				case IE_PILEEDITOR_NEWCARDSORIENTATION_FACE_UP:
					card->face_up = true;			
					break;
				case IE_PILEEDITOR_NEWCARDSORIENTATION_FACE_DOWN:
					card->face_up = false;
					break;
				case IE_PILEEDITOR_NEWCARDSORIENTATION_NO_PREF_:
					break;
			};	
		};
	};
	card->Invalidate();
};

void PILE::MouseDown(BPoint location)
{
	if (editing)
	{
		switch (action_on_MD)
		{
			case POP_COPY:
			{
				BMessage* message;
				message = new BMessage(NEW_PILE);
				BMessage* pilemsg = properties->Encapsulate();
				message->AddMessage("pile props", pilemsg);	
				message->AddPoint("location", GET_CURSOR_POINT);
				DragMessage(message, Bounds());//change to drag bitmap later			
				action_on_MD = EDITING;	
				break;
			};
			case POP_MOVE:
			{
				Hide();
				BMessage message(MOVE_PILE);
				message.AddPointer("pile", this);
				DragMessage(&message, Bounds());//change to drag bitmap later			
				action_on_MD = EDITING;	
				break;	
			};
			default:
			{
				BPoint cursor;
				uint32 buttons;
				GetMouse(&cursor, &buttons, false);
				if (buttons == B_SECONDARY_MOUSE_BUTTON )
				{
					BMenuItem* selected = NULL;
					
					ConvertToScreen(&location);
					selected = popmenu->Go(location, false);
					ConvertFromScreen(&location);
					ConvertToParent(&location);
					if (selected) 
					{
						BMessage* response = new BMessage(selected->Message()->what);
						response->AddPoint("location", location);
						this->MessageReceived(response);
					};
				};
			};
		};
	};
};

void PILE::Draw(BRect updateRect)
{
	if ((Bounds().Contains(updateRect)) && (CountChildren() == 0))
	{
		DrawBitmapAsync(empty, BPoint(0, 0));
		if (isbeingedited) InvertRect(Bounds());
	};
};
