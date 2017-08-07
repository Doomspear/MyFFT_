#include "StdAfx.h"
#include "WoodenBoard.h"
#include "Includes.h"

CWoodenBoard::CWoodenBoard(void)
{
}

CWoodenBoard::CWoodenBoard(_INT ix, _INT iy, _INT iNum)
{
	m_dwTexID		= TI_SMALLHOUSE;
	m_dwMidID		= MI_WOODENBOARDS;
	m_dwDir			= DI_DOWN;
	m_pt.x			= ix;
	m_pt.y			= iy;
	m_iAlpha		= 255;
	m_iFrame		= iNum;
}

CWoodenBoard::~CWoodenBoard(void)
{
}

void CWoodenBoard::Init()
{
	m_pvecTex		= _GETINST( CTextureLoader )->GetTextureVector();
	m_iAlpha		= 255;
	m_fDegree		= 45.0f;
	m_vCenter		= (*m_pvecTex)[m_dwTexID][m_dwMidID][m_dwDir][m_iFrame]->vCen;

}

void CWoodenBoard::Progress()
{
	MoveToIndex();
	RevisionPos();
}

void CWoodenBoard::Render()
{
	D3DXMatrixTranslation( &m_matTrans, m_vPos.x, m_vPos.y, m_vPos.z );
	m_matWorld = m_matTrans;

	_GETINST( CDevice )->GetSprite()->SetTransform( &m_matWorld );
	_GETINST( CDevice )->GetSprite()->Draw( (*m_pvecTex)[m_dwTexID][m_dwMidID][m_dwDir][m_iFrame]->pTex
										  , NULL, &m_vCenter, NULL
										  , D3DCOLOR_ARGB(m_iAlpha, 255, 255, 255) );
}

void CWoodenBoard::Release()
{
}