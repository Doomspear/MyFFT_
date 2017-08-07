#include "StdAfx.h"
#include "EditBtn.h"
#include "Includes.h"

CEditBtn::CEditBtn(void)
: m_bSelected( false )
, m_iColor		( 255 )
{
}

CEditBtn::~CEditBtn(void)
{
}

void CEditBtn::Init()
{
	m_fSizeX	= 243.0f;
	m_fSizeY	= 80.0f;

	m_pvecTex	= _GETINST(CTextureLoader)->GetTextureVector( );	
	m_vCenter	= D3DXVECTOR3( 243.0f / 2.0f, 80.0f / 2.0f, 0.0f );
	m_vPos		= D3DXVECTOR3( (WINSIZEX >> 1) - 250, (WINSIZEY >> 1) + 100, 0.0f );

	D3DXMatrixIdentity( &m_matWorld );
}

void CEditBtn::Progress()
{
	D3DXMATRIXA16	matTrans;
	D3DXMatrixTranslation( &matTrans, m_vPos.x, m_vPos.y, m_vPos.z );
	
	m_matWorld = matTrans;

	SetColRect( m_fSizeX, m_fSizeY );
	
	if ( m_bSelected == true ) 
	{
		m_iColor = 255;
	}
	else
		m_iColor = 100;
}

void CEditBtn::Render()
{
	_GETINST(CDevice)->GetSprite()->SetTransform( &m_matWorld );
	_GETINST(CDevice)->GetSprite()->Draw( (*m_pvecTex)[TI_UI][UI_BUTTON][BTN_EDIT][0]->pTex, NULL, &m_vCenter, NULL, D3DCOLOR_ARGB(m_iColor, 255, 255, 255) ); 
}

void CEditBtn::Selected()
{
	m_bSelected	= true;
}
void CEditBtn::NotSelected()
{	
	m_bSelected	= false;
}


void CEditBtn::Release()
{
	
}
