#include "StdAfx.h"
#include "SelectBox.h"
#include "Includes.h"	

CSelectBox::CSelectBox(void)
{
}

CSelectBox::CSelectBox(D3DXVECTOR3 vPos)
{
	m_vStartPos	= vPos;
 	m_vCenter	= vPos;
}

CSelectBox::~CSelectBox(void)
{
}

void CSelectBox::Init()
{
	m_pvecTex = _GETINST(CTextureLoader)->GetTextureVector();
	D3DXMatrixIdentity( &m_matWorld );
}

void CSelectBox::Progress()
{
	m_vEndPos = _GETINST(CObjStorage)->GetMouse()->GetvPos();

	//충돌 렉트를 마우스가 움직이는 방향에 따라 설정하는 부분
	if ( m_vStartPos.x < m_vEndPos.x && m_vStartPos.y < m_vEndPos.y )
	{
		m_dwMidID = DT_LEFTTOP;
		SetRect( &m_rcColi
			   , int( m_vStartPos.x )
			   , int( m_vStartPos.y )
			   , int( m_vEndPos.x )
			   , int( m_vEndPos.y ) );
	}
	else if ( m_vStartPos.x < m_vEndPos.x && m_vStartPos.y > m_vEndPos.y )
	{
		m_dwMidID = DT_LEFTBOT;
		SetRect( &m_rcColi
			   , int( m_vStartPos.x )
			   , int( m_vEndPos.y )
			   , int( m_vEndPos.x )
			   , int( m_vStartPos.y ) );
	}
	else if ( m_vStartPos.x > m_vEndPos.x && m_vStartPos.y < m_vEndPos.y )
	{
		m_dwMidID = DT_RIGHTTOP;
		SetRect( &m_rcColi
			   , int( m_vEndPos.x )
			   , int( m_vStartPos.y )
			   , int( m_vStartPos.x )
			   , int( m_vEndPos.y ) );
	}
	else if ( m_vStartPos.x > m_vEndPos.x && m_vStartPos.y > m_vEndPos.y )
	{
		m_dwMidID = DT_RIGHTBOT;
		SetRect( &m_rcColi
			   , int( m_vEndPos.x )
			   , int( m_vEndPos.y )
			   , int( m_vStartPos.x )
			   , int( m_vStartPos.y ) );
	}
}

void CSelectBox::Render()
{
	RECT m_rcView;
	
	//마우스의 움직이는 방향에 따라 셀렉트박스 이미지를 
	//어느 위치에서부터 읽어올지를 정하는 부분
	switch ( m_dwMidID ) 
	{
	case DT_LEFTTOP:
		SetRect( &m_rcView
			   , int( 0 )
			   , int( 0 )
			   , int( abs(m_vStartPos.x - m_vEndPos.x) )
			   , int( abs(m_vStartPos.y - m_vEndPos.y) ) );
		break;

	case DT_LEFTBOT:
		SetRect( &m_rcView
			   , int( 0 )
			   , int( WINSIZEY )
			   , int( abs(m_vStartPos.x - m_vEndPos.x) )
			   , int( WINSIZEY - abs(m_vStartPos.y - m_vEndPos.y) ) );
		break;

	case DT_RIGHTTOP:
		SetRect( &m_rcView
			   , int( WINSIZEX )
			   , int( 0 )
			   , int( WINSIZEX - abs(m_vStartPos.x - m_vEndPos.x) )
			   , int( abs(m_vStartPos.y - m_vEndPos.y) ) );
		break;

	case DT_RIGHTBOT:
		SetRect( &m_rcView
			   , int( WINSIZEX )
			   , int( WINSIZEY )
			   , int( WINSIZEX - abs(m_vStartPos.x - m_vEndPos.x) )
			   , int( WINSIZEY - abs(m_vStartPos.y - m_vEndPos.y) ) );
		break;
	}

	CDevice::GetInst()->GetSprite()->SetTransform( &m_matWorld );
	_GETINST(CDevice)->GetSprite()->Draw( (*m_pvecTex)[TI_UI][UI_SELECTBOX][0][0]->pTex
										, &m_rcView
										, NULL
										, &m_vStartPos
										, D3DCOLOR_ARGB(100, 255, 255, 255) );
}

void CSelectBox::SetStartPos(D3DXVECTOR3 vPos)
{ 
	m_vStartPos = vPos;
}

void CSelectBox::Release()
{
}