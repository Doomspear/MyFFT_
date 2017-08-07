#include "StdAfx.h"
#include "PostStone.h"
#include "Includes.h"

CPostStone::CPostStone(void)
{
}

CPostStone::CPostStone(_INT ix, _INT iy, _INT iNum)
{
	m_dwTexID		= TI_SMALLHOUSE;
	m_dwMidID	= MI_STONESTAIR;
	m_dwDir			= DI_DOWN;
	m_iFrame		= iNum;
	m_pt.x			= ix;
	m_pt.y			= iy;
}

CPostStone::~CPostStone(void)
{
}

void CPostStone::Init()
{
	m_pvecTex		= _GETINST( CTextureLoader )->GetTextureVector();
	m_iDepth		= 0;
	m_iAlpha		= 255;
	m_fDegree		= 45.0f;
	m_vCenter		= (*m_pvecTex)[m_dwTexID][m_dwMidID][m_dwDir][m_iFrame]->vCen;

	_INT iIndex		= m_pt.x * AMOUNTY + m_pt.y;
	(* _GETINST( CObjStorage )->GetTileVec() )[iIndex]->SetDepth( 1 );
}

void CPostStone::Progress()
{
	MoveToIndex();
	RevisionPos();
}

void CPostStone::Render()
{
	D3DXMatrixTranslation( &m_matTrans, m_vPos.x, m_vPos.y, m_vPos.z );
	m_matWorld = m_matTrans;

	_GETINST( CDevice )->GetSprite()->SetTransform( &m_matWorld );
	_GETINST( CDevice )->GetSprite()->Draw( (*m_pvecTex)[m_dwTexID][m_dwMidID][m_dwDir][m_iFrame]->pTex
										  , NULL, &m_vCenter, NULL
										  , D3DCOLOR_ARGB(m_iAlpha, 255, 255, 255) );
}

void CPostStone::Release()
{
}