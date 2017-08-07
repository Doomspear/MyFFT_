#include "StdAfx.h"
#include "StartBtn.h"
#include "Includes.h"

CStartBtn::CStartBtn(void)
: m_bSelected	( false )
, m_iColor		( 255 )
{
}

CStartBtn::~CStartBtn(void)
{
}

void CStartBtn::Init()
{
	m_dwDir		= 0;

	m_fSizeX	= 190.0f;
	m_fSizeY	= 90.0f;
	
	m_pvecTex	= _GETINST(CTextureLoader)->GetTextureVector( );
	m_vCenter	= D3DXVECTOR3( m_fSizeX / 2.0f, m_fSizeY / 2.0f, 0.0f );
	m_vPos		= D3DXVECTOR3( (WINSIZEX >> 1), (WINSIZEY >> 1), 0.0f );

	D3DXMatrixIdentity( &m_matWorld );
}

void CStartBtn::Progress()
{
	D3DXMATRIXA16	matTrans;
	D3DXMatrixTranslation( &matTrans, m_vPos.x, m_vPos.y, m_vPos.z );

	m_matWorld = matTrans;

	SetColRect( m_fSizeX, m_fSizeY );

	/*if ( m_bSelected == true ) 
	{
		m_dwDir = 1;
		m_vCenter	= D3DXVECTOR3( 127.0f / 2.0f, 78.0f / 2.0f, 0.0f );
	}
	else
	{
		m_dwDir	= 0;
		m_vCenter	= D3DXVECTOR3( m_fSizeX / 2.0f, m_fSizeY / 2.0f, 0.0f );
	}*/
}

void CStartBtn::Render()
{	
	_GETINST(CDevice)->GetSprite()->SetTransform( &m_matWorld );
	_GETINST(CDevice)->GetSprite()->Draw( (*m_pvecTex)[TI_UI][UI_BUTTON][BTN_START][0]->pTex, NULL, &m_vCenter, NULL, D3DCOLOR_ARGB(255, 255, 255, 255) ); 

	if ( m_bSelected == true )
	{
		D3DXVECTOR3 vCenter	= D3DXVECTOR3( 128.0f / 2.0f, 80.0f / 2.0f, 0.0f );
		_GETINST(CDevice)->GetSprite()->Draw( (*m_pvecTex)[TI_UI][UI_BUTTON][BTN_START][1]->pTex, NULL, &vCenter, NULL, D3DCOLOR_ARGB(255, 255, 255, 255) ); 
	}
}

void CStartBtn::Selected()
{
	//ERRORCHECK;
	m_bSelected	= true;
}
void CStartBtn::NotSelected()
{	
	m_bSelected	= false;
}

void CStartBtn::Release()
{
	
}