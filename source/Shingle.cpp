#include "StdAfx.h"
#include "Shingle.h"
#include "Includes.h"

CShingle::CShingle(void)
{
}
CShingle::CShingle(_INT ix, _INT iy, _INT iNum, _INT iDepth)
{
	m_dwTexID		= TI_SMALLHOUSE;
	m_dwMidID	= MI_SHINGLE;
	m_dwDir			= DI_DOWN;
	m_pt.x			= ix;
	m_pt.y			= iy;
	m_iAlpha		= 255;
	m_iFrame		= iNum;
	m_iDepth		= iDepth;
}

CShingle::~CShingle(void)
{
}

void CShingle::Init()
{
	m_pvecTex		= _GETINST( CTextureLoader )->GetTextureVector();
	m_iAlpha		= 255;
	m_fDegree		= 45.0f;
	m_vCenter		= (*m_pvecTex)[m_dwTexID][m_dwMidID][m_dwDir][m_iFrame]->vCen;
	
}

void CShingle::Progress()
{
	MoveToIndex();
	RevisionPos();
}

void CShingle::Render()
{
	D3DXMatrixTranslation( &m_matTrans, m_vPos.x, m_vPos.y, m_vPos.z );
	m_matWorld = m_matTrans;

	
	////³ôÀÌ
	m_vCenter		= (*m_pvecTex)[m_dwTexID][m_dwMidID][m_dwDir][m_iFrame]->vCen;

	if ( m_iFrame == 2 )
	{
		m_vCenter.x		+= 1 * m_iDepth;
		m_vCenter.y		+= 13 * m_iDepth;
	}
	else if ( m_iFrame == 1 )
	{
		m_vCenter.x		-= 1 * m_iDepth;
		m_vCenter.y		+= 12 * m_iDepth;
	}
	else
		m_vCenter.y		+= 13 * m_iDepth;
	
	_GETINST( CDevice )->GetSprite()->SetTransform( &m_matWorld );
	_GETINST( CDevice )->GetSprite()->Draw( (*m_pvecTex)[m_dwTexID][m_dwMidID][m_dwDir][m_iFrame]->pTex
										  , NULL, &m_vCenter, NULL
										  , D3DCOLOR_ARGB(m_iAlpha, 255, 255, 255) );

	/*m_vCenter = (*m_pvecTex)[TI_OBJ][OI_TILE][TT_DEFAULT][0]->vCen;
	D3DXMATRIXA16	matRotateZ;
	D3DXMatrixRotationZ( &matRotateZ, D3DXToRadian(45.0f) );
	m_matWorld = matRotateZ * m_matTrans ;
	_GETINST( CDevice )->GetSprite()->SetTransform( &m_matWorld );
	_GETINST( CDevice )->GetSprite()->Draw( (*m_pvecTex)[TI_OBJ][OI_TILE][TT_DEFAULT][0]->pTex
										  , NULL, &m_vCenter, NULL
										  , D3DCOLOR_ARGB(50, 255, 255, 255) );*/
}

void CShingle::Release()
{

}
