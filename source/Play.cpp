#include "StdAfx.h"
#include "Play.h"
#include "Includes.h"

CPlay::CPlay(void)
{
}

CPlay::~CPlay(void)
{
	Release();
}

HRESULT	CPlay::Init()
{
	return S_OK;
}

void CPlay::Progress()
{
	/*_DWORD	dwKey = _GETINST(CKeyChecker)->GetKeyState();
	if ( dwKey & KEY_BACKSPACE )
	{
		_GETINST(CViewHandle)->SetView( VI_MENU );	
	}*/
	
	CObjStorage::GetInst()->Progress();
	//_GETINST(CObjStorage)->Tile_Progress( false );
}

void CPlay::Render()
{
	CObjStorage::GetInst()->Render();
}

void CPlay::Release()
{
	
}
