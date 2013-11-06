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


#include <Point.h>
#include <math.h>
#include <Debug.h>

#ifndef JWMISC
#define JWMISC

char* mystrconcat (const char *first, const char *second);

void StrToNum(const char *str, long double &r);
int32 StrToInt(const char *str);
char* BPointToStr (BPoint data);
int16* StrToIntArray(const char *str, int16 *numpt);
char* IntArrayToStr (const int16* r, const int numnums);
char* IntToStr (const int16 r);
char* Int32ToStr (const int32 r);

char* AnyToStr (const long double data, const int32 maxdecimal);

#endif
