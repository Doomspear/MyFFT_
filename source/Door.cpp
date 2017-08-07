#include "StdAfx.h"
#include "Door.h"
#include "Includes.h"

CDoor::CDoor(void)
{
}

CDoor::CDoor(_INT ix, _INT iy, _INT iNum)
: m_bClicked( false )
{	
	m_pt.x			= ix;
	m_pt.y			= iy;
	m_iFrame		= iNum;
}

CDoor::~CDoor(void)
{

}

void CDoor::Init()
{
	m_dwTexID		= TI_SMALLHOUSE;
	m_dwMidID		= MI_DOOR;
	m_dwDir			= DI_DOWN;
	m_iAlpha		= 255;

	m_pvecTex		= _GETINST( CTextureLoader )->GetTextureVector();
	m_iAlpha		= 255;
	m_fDegree		= 45.0f;
	m_vCenter		= (*m_pvecTex)[m_dwTexID][m_dwMidID][m_dwDir][m_iFrame]->vCen;
	m_fSizeX		= m_vCenter.x;
	m_fSizeY		= m_vCenter.y;

	SetTileIndex();
	PTILE((* _GETINST( CObjStorage )->GetTileVec() )[m_iTileIndex])->SetStatic();
}

void CDoor::Progress()
{
	_DWORD dwKey = CKeyChecker::GetInst()->GetKeyState();

	MoveToIndex();
	RevisionPos();
	SetColRect();
	
	RECT rcTemp;
	RECT rcMouse = _GETINST( CObjStorage )->GetMouse()->GetColRect();

	if ( TRUE == IntersectRect( &rcTemp, &m_rcColi, &rcMouse) )
	{
		if ( dwKey & KEY_LBUTTON )
		{
			if ( m_bClicked == true )
				return;

			m_bClicked = true;

			DoorMove();
		}
		else
			m_bClicked = false;
	}

	/*if ( m_iFrame == 0 )
	{
		
	}
	else if ( m_iFrame == 1 )
	{

	}*/
}

void CDoor::DoorMove()
{
	if ( m_iFrame == 0 )
	{
		m_iFrame = 1;
		PTILE((* _GETINST( CObjStorage )->GetTileVec() )[m_iTileIndex])->RelStatic();
	}
	else if ( m_iFrame == 1 )
	{
		m_iFrame = 0;
		PTILE((* _GETINST( CObjStorage )->GetTileVec() )[m_iTileIndex])->SetStatic();
	}
}

void CDoor::Render()
{
	D3DXMatrixTranslation( &m_matTrans, m_vPos.x, m_vPos.y, m_vPos.z );
	m_matWorld = m_matTrans;
	
	m_vCenter		= (*m_pvecTex)[m_dwTexID][m_dwMidID][m_dwDir][m_iFrame]->vCen;

	_GETINST( CDevice )->GetSprite()->SetTransform( &m_matWorld );
	_GETINST( CDevice )->GetSprite()->Draw( (*m_pvecTex)[m_dwTexID][m_dwMidID][m_dwDir][m_iFrame]->pTex
										  , NULL, &m_vCenter, NULL
										  , D3DCOLOR_ARGB(m_iAlpha, 255, 255, 255) );
	//DrawColiBox();
}

void CDoor::Release()
{
	SetTileIndex();
	PTILE((* _GETINST( CObjStorage )->GetTileVec() )[m_iTileIndex])->RelStatic();
}