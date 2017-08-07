#include "StdAfx.h"
#include "DeathShroud.h"
#include "Includes.h"

CDeathShroud::CDeathShroud(void)
{
}

CDeathShroud::CDeathShroud(CObj* pOwner)
{
	m_pOwner	= pOwner;
	m_iFrame	= 0;
}

CDeathShroud::~CDeathShroud(void)
{
}

void CDeathShroud::Init()
{
	m_dwTexID		= TI_DEATHSHROUD;
	m_pvecTex		= _GETINST( CTextureLoader )->GetTextureVector();
}

void CDeathShroud::Progress()
{
	if ( m_pOwner != NULL )
	{
		//주인이 있다면(착용한 상태)
		m_vPos		= m_pOwner->GetvPos();
		m_dwMidID	= m_pOwner->GetMidID();
		m_dwDir		= m_pOwner->GetDirection();
		m_iFrame	= m_pOwner->GetFrame();
		m_bReverse	= m_pOwner->GetReverse();
	}
	else
	{
		//주인이 없다면 (땅에 떨어져 있거나 인벤토리에 들고있는 상태)
		m_dwMidID	= MI_ICON;
	}

	CheckReverse();
	D3DXMatrixTranslation( &m_matTrans, m_vPos.x, m_vPos.y, m_vPos.z );
	m_matWorld = m_matScale * m_matTrans;

}
void CDeathShroud::Render()
{
	m_vCenter = (*m_pvecTex)[m_dwTexID][m_dwMidID][m_dwDir][m_iFrame]->vCen;

	_GETINST( CDevice )->GetSprite()->SetTransform( &m_matWorld );
	_GETINST( CDevice )->GetSprite()->Draw( (*m_pvecTex)[m_dwTexID][m_dwMidID][m_dwDir][m_iFrame]->pTex, NULL, &m_vCenter, NULL, D3DCOLOR_ARGB(255, 255, 255, 255) );

	/*if ( m_dwTime + 100 < GetTickCount() )
	{
		m_dwTime = GetTickCount();
		++m_iFrame;
	}

	if ( m_iFrame == (*m_pvecTex)[TI_DEATHSHROUD][m_dwMidID][m_dwDir].size() )
	{
		m_iFrame = 0;	
	}*/
}
void CDeathShroud::Release()
{

}
