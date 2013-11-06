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

#include <IEResourceHandler.h>

#ifndef IEAPP
#define IEAPP
#include <IEApplication.h>
#endif

#ifndef IEWINDOW
#define IEWINDOW
#include <IEWindow.h>
#endif

#include "BesolWindow.h"
#include "DECK.h"
#include "PILE.h"

#ifndef BESOL_APP_CLASS
#define BESOL_APP_CLASS



class BESOL_APP : public IEApplication
{
	public:
		BesolWindow* mainwindow;
		BESOL_APP (int WTF);
		virtual void MessageReceived(BMessage* message);	
	private:
		virtual void AboutRequested();
		DECK* thedeck;
};
#endif
