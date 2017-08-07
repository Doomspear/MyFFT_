#pragma once

#include "stdafx.h"
using namespace std;

//define list
#define		ERRORCHECK		MessageBox(g_hWnd, L"", L"", MB_OK)
#define		_GETINST(p)		p::GetInst()
#define		_DESTINST(p)	p::GetInst()->DestroyInst()

//typedef list
typedef signed		int				_INT;
typedef unsigned	int				_UINT;
typedef				DWORD			_DWORD;
typedef				bool			_BOOL;
typedef				float			_FLOAT;

//const list
//const signed int	WINSIZEX		= 640;	
//const signed int	WINSIZEY		= 480;	
const signed int	WINSIZEX		= 800;	
const signed int	WINSIZEY		= 600;	
const signed int	BACKBUFSIZEX	= WINSIZEX;
const signed int	BACKBUFSIZEY	= WINSIZEY;

//const signed int	TILEAMOUNT		= 100;
const signed int	AMOUNTX			= 30;
const signed int	AMOUNTY			= 30;
//const signed int	AMOUNTX			= 100;
//const signed int	AMOUNTY			= 100;
const signed int	DEFAULT			= 0;

const D3DXVECTOR3	VEC3_ZERO		(0.0f, 0.0f, 0.0f);
const D3DXVECTOR3	VEC3_LEFT		(1.0f, 0.0f, 0.0f);
const D3DXVECTOR3	VEC3_RIGHT		(-1.0f, 0.0f, 0.0f);
const D3DXVECTOR3	VEC3_UP			(0.0f, 1.0f, 0.0f);
const D3DXVECTOR3	VEC3_DOWN		(0.0f, -1.0f, 0.0f);
const D3DXVECTOR3	VEC3_DOWNLEFT	(1.0f, -1.0f, 0.0f);
const D3DXVECTOR3	VEC3_DOWNRIGHT	(-1.0f, -1.0f, 0.0f);
const D3DXVECTOR3	VEC3_UPLEFT		(1.0f, 1.0f, 0.0f);
const D3DXVECTOR3	VEC3_UPRIGHT	(-1.0f, 1.0f, 0.0f);

const POINT			PT_LEFT		= { 1, -1 };
const POINT			PT_RIGHT	= { -1, 1 };
const POINT			PT_UP		= { -1, -1 };
const POINT			PT_DOWN 	= { 1, 1 };

const POINT			PT_DOWNLEFT = { 1, 0 };
const POINT			PT_DOWNRIGHT= { 0, 1 };
const POINT			PT_UPLEFT 	= { 0, -1 };
const POINT			PT_UPRIGHT 	= { -1, 0 };


//struct list
typedef struct tagTexture
{
	D3DXVECTOR3			vCen;
	LPDIRECT3DTEXTURE9	pTex;
}TEXTURE, *PTEXTURE;

//enum list
enum WIN_MODE		{ WM_FULL		//false
					, WM_WIN };		//true

enum SINGLE_TEX_ID	{ STI_LOGO
					, STI_MENU
					, STI_END};

enum TEXTURE_ID		{ TI_VIEW			
					, TI_OBJ
					, TI_UI
					
					//CHAR
					, TI_WOMAN
					, TI_VENDOR
					, TI_CHICKEN
					, TI_DAEMON
					, TI_TROLL
					, TI_BLADE
					, TI_DRAGON
					, TI_TITAN

					//Item
					, TI_DEATHSHROUD
					, TI_ROBE
					, TI_HALBERD

					//static object
					, TI_SMALLHOUSE
					, TI_TREEAPPLE
					, TI_TREEBIGAPPLE
					, TI_TREEPEAR
					, TI_BLOOD

					, TI_END };

enum MIDDLE_ID		{ VI_LOAD
					, VI_LOGO
					, VI_MENU
					, VI_EDIT
					, VI_PLAY
					
					//UI
					, UI_MOUSE
					, UI_SELECTBOX
					, UI_COLIBOX
					, UI_BUTTON
					
					, UI_INVEN
					, UI_LOOT

					//MOTION
					//for people
					, MI_ATTACK_TWOHAND_DOWN
					, MI_ATTACK_TWOHAND_WIDE
					, MI_ATTACK_UNARMED
										
					, MI_CAST_DIRECT
					, MI_CAST_SUMMON

					, MI_DIE

					, MI_RUN_ARMED
					, MI_RUN_UNARMED
					
					, MI_STAND
					, MI_STAND_TWOHAND_ATTACK

					, MI_TAKE_HIT

					, MI_WALK_ARMED
					, MI_WALK_UNARMED
					, MI_WALK_ATTACKPOS
					
					//for creature
					, MI_ATTACK1
					, MI_ATTACK2
					, MI_MISC
							
					//for Item
					, MI_ICON

					//for static object
					, MI_PLASTERWALL
					, MI_STONESTAIR
					, MI_WOODENBOARDS
					, MI_DOOR
					, MI_SHINGLE
					, MI_TREE
					, MI_BLOOD
					, MI_END };

enum DIRECTION_ID	{ DI_DOWN
					, DI_DOWNLEFT
					, DI_DOWNRIGHT
					, DI_LEFT
					, DI_RIGHT
					, DI_UP
					, DI_UPLEFT
					, DI_UPRIGHT
				
					//for cursor
					, CI_PEACE_UP_LEFT
					, CI_WAR_UP_LEFT
				
					//for button
					, BTN_START
					, BTN_EDIT
					
					, DI_END };

enum OBJ_ID			{ OI_BACKGROUND
					, OI_MOUSE
					, OI_SELECTBOX
					, OI_TILE
					, OI_HOUSE
					, OI_CORPSE
					, OI_MONSTER
					, OI_PLAYER
					, OI_TREE
					
					, OI_END };

enum STATE_ID	:DWORD	{ ST_STAND			= 0x00000001
						, ST_WALK		 	= 0x00000002
						, ST_WALK_IN_ATT	= 0x00000004
						, ST_RUN			= 0x00000008

						, ST_ATTACK			= 0x00000010
						, ST_TAKEHIT		= 0x00000020
						, ST_DIE			= 0x00000040
						, ST_CAST			= 0x00000080
						
						, ST_ARM			= 0x01000000
						, ST_UNARM			= 0x02000000
						, ST_WAR			= 0x04000000
						, ST_PEACE			= 0x08000000 };	

enum KEY_ID			{ KEY_SPACE		= 0x00000001 
					, KEY_LBUTTON	= 0x00000002 
					, KEY_LEFT		= 0x00000004
					, KEY_RIGHT		= 0x00000008
					, KEY_UP		= 0x00000010
					, KEY_DOWN		= 0x00000020
					, KEY_BACKSPACE	= 0x00000040
					, KEY_RETURN	= 0x00000080
					, KEY_RBUTTON	= 0x00000100
					, KEY_DELETE	= 0x00000200
					, KEY_PGUP		= 0x00000400
					, KEY_PGDN		= 0x00000800
					, KEY_CTRL		= 0x00001000 
					, KEY_ALT		= 0x00002000
					, KEY_C			= 0x00004000
					, KEY_TAB		= 0x00008000
					, KEY_I			= 0x00010000 };

enum TILE_TYPE		{ TT_DEFAULT
					, TT_GRASS		
					, TT_DUNGEON	
					, TT_END };

enum MOVE_TYPE		{ MOVE		
					, CANTMOVE };

enum BULL_ID		{ BI_WARPEACE
					, BI_END };

//extern list
extern HWND		g_hWnd;

