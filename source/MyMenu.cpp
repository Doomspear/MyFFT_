#include "StdAfx.h"
#include "MyMenu.h"
#include "Includes.h"

CMyMenu::CMyMenu(void)
: m_pStartBtn	( NULL )
, m_pEditBtn	( NULL )
{
}

CMyMenu::~CMyMenu(void)
{
	Release();
}

HRESULT	CMyMenu::Init()
{
	D3DXMatrixIdentity( &m_matWorld );
	m_pvecTex	= CTextureLoader::GetInst()->GetTextureVector();
	m_vCenter	= D3DXVECTOR3( WINSIZEX / 2.0f, WINSIZEY / 2.0f, 0.0f );
	m_vPos		= m_vCenter;
	m_dwTime	= GetTickCount();
	m_iAlpha	= 0;
	m_bShow		= true;

	m_pStartBtn	= new STARTBTN;
	m_pStartBtn->Init();

	return S_OK;
}

void CMyMenu::Progress()
{	
	D3DXMATRIXA16		matTrans;
	D3DXMatrixTranslation( &matTrans, m_vPos.x, m_vPos.y, m_vPos.z );

	m_matWorld = matTrans;

	vector<CObj*>* pvecTile	= _GETINST(CObjStorage)->GetTileVec();

	if ( m_bShow == true )
	{
		if ( m_dwTime + 10 < GetTickCount() )
		{
			m_dwTime = GetTickCount();
			m_iAlpha += 3;
			if ( m_iAlpha >= 255 )
			{
				m_iAlpha	= 255;
				m_bShow		= false;
			}
		}
	}
	else if ( m_bShow == false )
	{
		_DWORD dwKey = CKeyChecker::GetInst()->GetKeyState();
		
		POINT pt;
		GetCursorPos( &pt );
		ScreenToClient( g_hWnd, &pt );

		if ( PtInRect( &m_pStartBtn->GetColRect(), pt ) )
		{
			PSTARTBTN(m_pStartBtn)->Selected();
			if ( dwKey & KEY_LBUTTON )
			{
				CViewHandle::GetInst()->SetView( VI_PLAY );
				return;
			}
		}	
		else
		{
			PSTARTBTN(m_pStartBtn)->NotSelected();
		}

		
	}

	m_pStartBtn->Progress();
}

void CMyMenu::Render()
{
	CDevice::GetInst()->GetSprite()->SetTransform( &m_matWorld );
 	CDevice::GetInst()->GetSprite()->Draw( (*m_pvecTex)[TI_VIEW][VI_MENU][0][0]->pTex, NULL, &m_vCenter, NULL, D3DCOLOR_ARGB(m_iAlpha, 255, 255, 255) );

	if ( m_bShow == false )
	{
		m_pStartBtn->Render();
	}
}

void CMyMenu::Release()
{
	delete m_pStartBtn;
	m_pStartBtn	= NULL;
}