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


#include "misc.h"

char* AnyToStr (const long double data, const int32 maxdecimal = 5/*, bool scientific = false*/){
	char* str = NULL;
	uint32 strindex = 0;
	uint32 maxdigit = 0; 
	int8 digit;
	long double tempdata;
		
	while (pow(10, maxdigit) <= data) maxdigit++;
	
	if (data < 0){
		str = new char[1 + 1 + maxdigit + ( (maxdecimal > 0) ? 1 + maxdecimal : 0)];
		str[strindex++] = '-';
		str[strindex++] = '0';
	}
	else if (data == 0) {
		str = new char [1];
		str[strindex++] = '0';
	}
	else str = new char[1 + maxdigit + ( (maxdecimal > 0) ? 1 + maxdecimal : 0)];

	tempdata = (data >= 0 ? data/pow(10, maxdigit) : -1*data/pow(10, maxdigit) );
	for (uint32 loopindex = maxdigit; loopindex > 0; loopindex--){
		tempdata *= 10;
		digit = (int8) floor(tempdata);
		if (digit < 0) digit = 0;
		tempdata -= digit;		
		str[strindex++] = '0' + digit;
	};
	if (maxdecimal > 0) {
		str[strindex++] = '.';
		for (int32 loopindex = -1; loopindex >= -maxdecimal; loopindex--){
			tempdata *= 10;
			digit = (int8) floor(tempdata);
 			if (digit < 0) digit = 0;
			tempdata -= digit;		
			str[strindex++] = '0' + digit;
		};
	};
	
	str[strindex] = '\0';
	
	return str;
};

char* DoubleToStr (const double data);
char* DoubleToStr (const double data){
	int temp;
	char *value, *integral_part, *decimal_part, *tempstr;
	
	temp = (int32) (data);
	integral_part = Int32ToStr(temp);
	
	temp = (int32) (10000*(data - temp)); //limit to accuracy by the size of an int
	decimal_part = Int32ToStr(abs(temp));

	tempstr = new char[1];
	tempstr[0] = '.';
	tempstr[1] = '\0';
	
	value = mystrconcat(integral_part, tempstr);
	value = mystrconcat(value, decimal_part);
	
	return value;
};

void StrToNum(const char *str,long double &r)
{
	long double num;
	long t;
	char temp[100];
	int x=0,y=0;
	while(str[x]!='\0' && str[x]!='.')
	{
		temp[x]=str[x];
		x++;
	}
	temp[x]='\0';
	t = StrToInt(temp);
	num=t;
	while(str[x]!='\0')
	{
		temp[y]=str[x];
		x++;
		y++;
	}
	temp[y]='\0';
	if(y!=0)
	{
		t = StrToInt(temp);
		num+=t/pow(10,y-1);
	}
	r=num;
}

int32 StrToInt(const char *str)
{
	int32 r;
	int32 num=0;
	int8 x=0,y,m=1;
	while(str[x]!='\0')
		x++;
	if(str[0]=='-'){
		m=-1;
		x--;
	};
	for(y=0;y<x;y++)
	{
		if(!(str[y]>'9' || str[y]<'0'))
			num+= (int32) pow(10,x-y-1)*(str[y]-'0');
	}
	r=num*m;
	return r;
}

char* IntToStr (const int16 r)
{
	char* str = NULL;
	int numdigits = 1;
	int control = 9;
	int strindex = 0;
	int tempnum2, tempnum1 = abs(r);
	int min_numindex = 0;
	
	while (control < abs(r)) 
	{
		numdigits++;
		control += 9* (int) pow(10, numdigits - 1);
	};
	if (r < 0) {
		str = new char[numdigits+2];
		str[0] = '-';
		str[numdigits+1] = '\0';
		min_numindex++;
	}
	else{
		str = new char[numdigits+1];
		str[numdigits] = '\0';
	};

	for (strindex = numdigits; strindex >= 1; strindex--)
	{
		tempnum2 = (int) tempnum1 / (int) pow(10, (strindex - 1));
		str[numdigits - strindex + min_numindex] = '0' + tempnum2;
		tempnum1 -= tempnum2* (int) pow(10, (strindex - 1));
	};
	return str;
};

char* Int32ToStr (const int32 r)
{
	char* str = NULL;
	int numdigits = 1;
	int control = 9;
	int strindex = 0;
	int32 tempnum2, tempnum1 = abs(r);
	int min_numindex = 0;
	
	while (control < abs(r)) 
	{
		numdigits++;
		control += 9* (int) pow(10, numdigits - 1);
	};
	if (r < 0) {
		str = new char[numdigits+2];
		str[0] = '-';
		str[numdigits+1] = '\0';
		min_numindex++;
	}
	else{
		str = new char[numdigits+1];
		str[numdigits] = '\0';
	};

	for (strindex = numdigits; strindex >= 1; strindex--)
	{
		tempnum2 = (int32) tempnum1 / (int32) pow(10, (strindex - 1));
		str[numdigits - strindex + min_numindex] = '0' + tempnum2;
		tempnum1 -= tempnum2* (int32) pow(10, (strindex - 1));
	};
	return str;
};

char* IntArrayToStr (const int16* r, const int numnums)
{
	char* str = (IntToStr (r[0]));
	char *concatstr = NULL, *convertstr = NULL;
	int convertstrindex, concatindex, strindex = 0;

	for (int index = 1; index < numnums; index++){ //first conversion already done
		convertstr = (IntToStr (r[index]));
		convertstrindex = 0;
		while (str[strindex] != '\0') strindex++;			
		while (convertstr[convertstrindex] != '\0') convertstrindex++;
		concatstr = new char[strindex + convertstrindex - 1 + 1 + 1];
		strindex = 0; convertstrindex = 0;
		while (str[strindex] != '\0') {concatstr[strindex] = str[strindex]; strindex++;};			
		concatstr[concatindex = strindex] = ',';
		concatstr[++concatindex] = ' ';
		while (convertstr[convertstrindex] != '\0') {concatstr[concatindex++] = convertstr[convertstrindex++];};
		concatstr[concatindex] = '\0';
		delete [] str;
		delete [] convertstr;
		str = concatstr;
		concatstr = NULL;
	};
	return str;
};

int16* StrToIntArray(const char *str, int16 *numpt)
{
	int numindex = 0;
	int strindex = 0, tempstrindex = 0;
	int16* r = NULL;
	int32 num;
	int8 x, y, m;
	int numbers = 1;
	
	while (str[strindex] != '\0'){if (str[strindex] == ',') numbers++; strindex++;};
	strindex = 0;
	r = new int16[numbers];

	while (str[strindex] != '\0') {
		while (((str[strindex]>'9') || (str[strindex] < '0')) && (str[strindex] != '-') && (str[strindex] != '\0')) strindex++;
		if (str[strindex] == '\0') {/*printf ("null found"); */break;};
		
		num=0;
		x=0; 
		m=1;
		if(str[strindex]=='-'){
			m=-1;
			strindex++;
		};

		tempstrindex = strindex;
		while((str[strindex]<='9') && (str[strindex] >= '0')) {x++; strindex++;};
		for(y=0;y<x;y++, tempstrindex++)
		{
				num+= (int32) pow(10,x-y-1)*(str[tempstrindex]-'0');
		};
		
		if (numindex < numbers) {r[numindex++]=num*m;}
		else {
//			beep();
			printf ("Numeric Data must be comma separated!");
			break;
		};
	};
	if (numindex < numbers) {/*beep(); */printf ("Extra commas in data... possible errors!");};

	*numpt = numindex;

	return r;
}

char* BPointToStr (BPoint data){
	char* tempstr;
	
	int16* dataarray = new int16[2];
	dataarray[0] = (short int) data.x;
	dataarray[1] = (short int) data.y;
	tempstr = IntArrayToStr(dataarray, 2);
	delete [] dataarray;

	return tempstr;
};
	
char* mystrconcat (const char *first, const char *second){
	int firstindex = 0, secondindex = 0, finalindex = 0;
	char *temp = NULL;
		
	while (first[firstindex] != '\0') firstindex++;
	while (second[secondindex] != '\0') secondindex++;

	temp = new char[firstindex + secondindex + 1];
	
	firstindex = secondindex = 0;
	
	while (first[firstindex] != '\0') {temp[firstindex] = first[firstindex]; firstindex++;}
	finalindex = firstindex;

	while (second[secondindex] != '\0') temp[finalindex++] = second[secondindex++];	
	temp[finalindex] = '\0';

	return temp;
};