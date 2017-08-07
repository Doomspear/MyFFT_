#include "StdAfx.h"
#include "GameHandle.h"
#include "Includes.h"

CGameHandle::CGameHandle(void)
{
}

CGameHandle::~CGameHandle(void)
{
	Release();
}

void CGameHandle::Init()
{
	srand( (unsigned)GetTickCount() );

	/*---------------------------------------*/
	CDevice::GetInst()->Init(WM_WIN);
	//CSoundDevice::GetInst()->Init();
	/*---------------------------------------*/

	CTextureLoader::GetInst()->Init();

	/*---------------------------------------*/
	CViewHandle::GetInst()->SetView( VI_PLAY );
	/*---------------------------------------*/
}

void CGameHandle::Progress()
{
	CViewHandle::GetInst()->GetView()->Progress();

	Render();
}

void CGameHandle::Render()
{
	CDevice::GetInst()->GetDevice()->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL
										  , D3DCOLOR_XRGB(58, 110, 165), 0.0f, 0 );

	_GETINST(CDevice)->GetDevice()->BeginScene();
	_GETINST(CDevice)->GetSprite()->Begin(D3DXSPRITE_ALPHABLEND);

	_GETINST(CViewHandle)->GetView()->Render();
	
	_GETINST(CDevice)->GetSprite()->End();
	_GETINST(CDevice)->GetDevice()->EndScene();

	_GETINST(CDevice)->GetDevice()->Present(NULL, NULL, g_hWnd, NULL);

	/*test*/
	/*RECT m_rcView = { 320 - WINSIZEX / 2, 285 - WINSIZEY / 2, 320 + WINSIZEX / 2, 285 + WINSIZEY / 2 };
	_GETINST(CDevice)->GetDevice()->Present(NULL, &m_rcView, g_hWnd, NULL);*/
}

void CGameHandle::Release()
{
	_DESTINST( CDevice );
	_DESTINST( CTextureLoader );
	_DESTINST( CViewHandle );
	_DESTINST( CKeyChecker );
	_DESTINST( CObjStorage );
	_DESTINST( CAstarHandler );
}
