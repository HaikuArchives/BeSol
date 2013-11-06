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

//this file is extremely ugly as far as dependencies go... probably should be 
//sorted out into many separate files so that changes made won't force practically a total recompile
#ifndef otherdefs
#define otherdefs

const int32 BLOCK_DRAG = 'BlkD';
const int32 UF_MESSY_DRAG = 'UFMD'; 
const int32 UF_CLEAN_DRAG = 'UFCD';
const int32 ORDERINGNONE = 'ONne';
const int32 ORDERINGSOME = 'OSme';
const int32 ORDERINGSEND = 'OSnd';
const int32 ORDERINGRECV = 'ORcv';

const uint32 BESOL_PILE_PROP_TYPE = 'PPTp'; 
const uint32 NEW_PILE = 'NewP'; 
const uint32 MOVE_PILE = 'MovP';
const uint32 DECK_REF_RECEIVED = 'DkRR';
const uint32 GAME_OPENREF_RECEIVED = 'GORR';
const uint32 LAYOUT_OPENREF_RECEIVED = 'LORR';
const uint32 GAME_SAVEREF_RECEIVED = 'GSRR';
const uint32 LAYOUT_SAVEREF_RECEIVED = 'LSRR';
const uint32 GAME_SAVE = 'GmSv';
const uint32 LAYOUT_SAVE = 'LySv';
const uint32 POP_COPY = 'PpCp'; 
const uint32 POP_MOVE = 'PpMv'; 
const uint32 POP_EDIT = 'PpEd'; 
const uint32 POP_DELETE = 'PpDl';
const uint32 CARD_MSG = 'GFUC';

const uint32 LAYOUT_DATA = 'LyDt';
const uint32 TRANS_BOX_CHECKED = 'TBCk';
const uint32 EDITING = 'Edtg';
const uint32 WAITFOREDIT = 'WFEd';
const uint32 RULES_REQUEST = 'RlRq';
const uint32 RULES_UPDATE = 'RlUp';
const uint32 POP_TO_CHANGED = 'PTCh';
const uint32 VALUE_STEPS_CHANGED = 'VSCh';
const uint32 SUIT_STEPS_CHANGED = 'SSCh';
const uint32 AOE_SUIT_CHANGED = 'AESC';
const uint32 AOE_VALUE_CHANGED = 'AEVC';
const uint32 RULES_LOAD = 'RlLd';
const uint32 RULES_SAVE = 'RlSv';

const BPoint GET_CURSOR_POINT = BPoint(-1, -1); 

#endif