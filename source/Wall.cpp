#include "StdAfx.h"
#include "Wall.h"
#include "Includes.h"

CWall::CWall(void)
{
}

CWall::CWall(_INT ix, _INT iy, _INT iNum)
{
	m_dwTexID		= TI_SMALLHOUSE;
	m_dwMidID	= MI_PLASTERWALL;
	m_dwDir			= DI_DOWN;
	m_pt.x			= ix;
	m_pt.y			= iy;
	m_iAlpha		= 255;
	m_iFrame		= iNum;
}

CWall::~CWall(void)
{
}

void CWall::Init()
{
	m_pvecTex		= _GETINST( CTextureLoader )->GetTextureVector();
	m_iAlpha		= 255;
	m_fDegree		= 45.0f;
	m_vCenter		= (*m_pvecTex)[m_dwTexID][m_dwMidID][m_dwDir][m_iFrame]->vCen;

	SetTileIndex();
	PTILE((* _GETINST( CObjStorage )->GetTileVec() )[m_iTileIndex])->SetStatic();
}

void CWall::Progress()
{
	MoveToIndex();
	RevisionPos();
}

void CWall::Render()
{
	D3DXMatrixTranslation( &m_matTrans, m_vPos.x, m_vPos.y, m_vPos.z );
	m_matWorld = m_matTrans;

	_GETINST( CDevice )->GetSprite()->SetTransform( &m_matWorld );
	_GETINST( CDevice )->GetSprite()->Draw( (*m_pvecTex)[m_dwTexID][m_dwMidID][m_dwDir][m_iFrame]->pTex
										  , NULL, &m_vCenter, NULL
										  , D3DCOLOR_ARGB(m_iAlpha, 255, 255, 255) );
	// 	0 = ¡é
	// 	1 = ¢Ù
	// 	2 = ¡¬
	// 	3 = £¯
	// 	4 = ¢Ø
	// 	5 = ¢×
	// 	6 = ¢Ö
	// 	7 = £¯window
	// 	8 = ¡¬window

	//	6 4 2 8 2 1			
	//	3 0 0 0 0 6
	//	3 0 0 0 0 7
	//	3 0 0 0 0 3
	//	3 0 0 0 0 3 
	//	2 1 D 4 2 0
}

void CWall::Release()
{
	SetTileIndex();
	PTILE((* _GETINST( CObjStorage )->GetTileVec() )[m_iTileIndex])->RelStatic();
}