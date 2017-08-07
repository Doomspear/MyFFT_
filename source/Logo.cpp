#include "StdAfx.h"
#include "Logo.h"
#include "Includes.h"

CLogo::CLogo(void)
{
}

CLogo::~CLogo(void)
{
}

HRESULT	CLogo::Init()
{
	D3DXMatrixIdentity( &m_matWorld );

	m_pvecTex	= CTextureLoader::GetInst()->GetTextureVector();
	m_vCenter	= D3DXVECTOR3( WINSIZEX / 2.0f, WINSIZEY / 2.0f, 0.0f );
	m_vPos		= m_vCenter;
	m_dwTime	= GetTickCount();
	m_iAlpha	= 0;
	m_bShow		= true;

	return S_OK;
}

void CLogo::Progress()
{
	D3DXMATRIXA16		matTrans;
	D3DXMatrixTranslation( &matTrans, m_vPos.x, m_vPos.y, m_vPos.z );

	m_matWorld	= matTrans;

	if ( m_bShow == true )
	{
		if ( m_dwTime + 10 < GetTickCount() )
		{
			m_dwTime	= GetTickCount();
			m_iAlpha	+= 3;
			
			if ( m_iAlpha >= 255 )
			{
				m_iAlpha = 255;
				m_bShow = false;
			}
		}
	}
	else if ( m_bShow == false )
	{
		_DWORD	dwKey = CKeyChecker::GetInst()->GetKeyState();

 		if ( dwKey & KEY_SPACE )
		{
 			CViewHandle::GetInst()->SetView( VI_MENU );
			return;
		}
	}
}

void CLogo::Render()
{
	RECT	rc = { 0, 0, WINSIZEX, WINSIZEY };

	CDevice::GetInst()->GetSprite()->SetTransform( &m_matWorld );
	CDevice::GetInst()->GetSprite()->Draw( (*m_pvecTex)[TI_VIEW][VI_LOGO][0][0]->pTex, &rc, &m_vCenter, NULL, D3DCOLOR_ARGB(m_iAlpha, 255, 255, 255));
}

void CLogo::Release()
{

}