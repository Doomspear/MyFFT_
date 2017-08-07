#include "StdAfx.h"
#include "EditMap.h"
#include "Includes.h"

CEditMap::CEditMap(void)
{
}

CEditMap::~CEditMap(void)
{
	//Release();
}

HRESULT	CEditMap::Init()
{
	_GETINST(CObjStorage)->Tile_Init(AMOUNTX, AMOUNTY);
	return S_OK;
}

void CEditMap::Progress()
{
	_DWORD	dwKey = _GETINST(CKeyChecker)->GetKeyState();

	if ( dwKey & KEY_BACKSPACE )
	{
		_GETINST(CViewHandle)->SetView( VI_MENU );	
	}

	if ( dwKey & KEY_RETURN )
	{
		SaveTileData();
		MessageBox( g_hWnd, L"Tile data save Complete.", L"SYSTEM MESSAGE", MB_OK );
	}

	if ( dwKey & KEY_SPACE ) 
	{
		LoadTileData();
		MessageBox( g_hWnd, L"Tile Data load Complete.", L"SYSTEM MESSAGE", MB_OK );
			
		POINT pt = { WINSIZEX / 2, WINSIZEY / 2 };
		ClientToScreen( g_hWnd, &pt );
		SetCursorPos( pt.x, pt.y );
	}
	
	
	//_GETINST(CObjStorage)->GetMouse()->Progress();
	_GETINST(CObjStorage)->Tile_Progress( true );
	_GETINST(CObjStorage)->Progress();
}

void CEditMap::Render()
{
	//_GETINST(CObjStorage)->GetMouse()->Render();
	_GETINST(CObjStorage)->Tile_Render();
	_GETINST(CObjStorage)->Render();
}

void CEditMap::Release()
{
	
}

void CEditMap::SaveTileData()
{
	HANDLE hFile;
	DWORD dwByte;

	hFile = CreateFile( L"../File/map.sdf"
					  , GENERIC_WRITE
					  , 0
					  , NULL
					  , CREATE_ALWAYS
					  , FILE_ATTRIBUTE_NORMAL
					  , NULL );

	vector<CObj*>*		pvecTile = _GETINST(CObjStorage)->GetTileVec();

	for ( _UINT i = 0; i < pvecTile->size(); ++i )
	{
		WriteFile( hFile, (*pvecTile)[i], sizeof(TILE), &dwByte, NULL );
	}

	CloseHandle( hFile );
}

void CEditMap::LoadTileData()
{
	HANDLE	hFile;
	DWORD	dwByte;

	POBJ	pTile = NULL;

	hFile	= CreateFile( L"../File/map.sdf"
						, GENERIC_READ
						, 0
						, NULL
						, OPEN_EXISTING
						, FILE_ATTRIBUTE_NORMAL
						, NULL );

	_GETINST(CObjStorage)->Tile_Release();

	vector<CObj*>*		pvecTile = _GETINST(CObjStorage)->GetTileVec();

	for ( _UINT i = 0; i < AMOUNTX * AMOUNTY; ++i )
	{		
		pTile = new TILE;
		ReadFile( hFile, pTile, sizeof(TILE), &dwByte, NULL );
		
		pTile->Init();

		(*pvecTile).push_back( pTile );
	}		

	CloseHandle( hFile );
}