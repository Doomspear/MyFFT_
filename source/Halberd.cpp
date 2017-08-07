#include "StdAfx.h"
#include "Halberd.h"
#include "Includes.h"

CHalberd::CHalberd(void)
{
}

CHalberd::CHalberd(CObj* pOwner)
{
	m_pOwner	= pOwner;
	m_iFrame	= 0;
}

CHalberd::~CHalberd(void)
{
}

void CHalberd::Init()
{
	m_dwTexID		= TI_HALBERD;
	m_pvecTex		= _GETINST( CTextureLoader )->GetTextureVector();
	m_bShrink		= false;
}

void CHalberd::Progress()
{
	if ( m_pOwner != NULL )
	{
		//주인이 있다면(착용한 상태)
		if ( m_bShrink == false )
		{
			m_vPos		= m_pOwner->GetvPos();
			m_dwMidID	= m_pOwner->GetMidID();
			m_dwDir		= m_pOwner->GetDirection();
			m_iFrame	= m_pOwner->GetFrame();
			m_bReverse	= m_pOwner->GetReverse();
		}
		else if ( m_bShrink == true )
		{
			m_dwMidID	= MI_ICON;
		}
	}
	else
	{
		//주인이 없다면 (땅에 떨어져 있거나 인벤토리에 들고있는 상태)
		m_dwMidID	= MI_ICON;
		m_bShrink	= true;
	}

	CheckReverse();
	D3DXMatrixTranslation( &m_matTrans, m_vPos.x, m_vPos.y, m_vPos.z );
	m_matWorld = m_matScale * m_matTrans;
}
void CHalberd::Render()
{
	if ( m_bShrink == false )
	{
		m_vCenter = (*m_pvecTex)[m_dwTexID][m_dwMidID][m_dwDir][m_iFrame]->vCen;

		//shadow
		D3DXMatrixRotationZ( &m_matRotateZ, D3DXToRadian( 15 ) );
		
		m_matWorld = m_matScale * m_matRotateZ * m_matTrans;
		_GETINST( CDevice )->GetSprite()->SetTransform( &m_matWorld );
		_GETINST( CDevice )->GetSprite()->Draw( (*m_pvecTex)[m_dwTexID][m_dwMidID][m_dwDir][m_iFrame]->pTex, NULL, &m_vCenter, NULL, D3DCOLOR_ARGB(100, 0, 0, 0) );

		m_matWorld = m_matScale * m_matTrans;
		_GETINST( CDevice )->GetSprite()->SetTransform( &m_matWorld );
		_GETINST( CDevice )->GetSprite()->Draw( (*m_pvecTex)[m_dwTexID][m_dwMidID][m_dwDir][m_iFrame]->pTex, NULL, &m_vCenter, NULL, D3DCOLOR_ARGB(255, 255, 255, 255) );

	}
	else if ( m_bShrink == true )
	{
		//D3DXMatrixTranslation( &m_matTrans, m_vInvenPos.x, m_vInvenPos.y, 0.0f );
		m_matWorld = m_matScale * m_matTrans;

		_GETINST( CDevice )->GetSprite()->SetTransform( &m_matWorld );
		_GETINST( CDevice )->GetSprite()->Draw( (*m_pvecTex)[m_dwTexID][MI_ICON][0][0]->pTex
											  , NULL
											  , &( (*m_pvecTex)[m_dwTexID][MI_ICON][0][0]->vCen )
											  , NULL
											  , D3DCOLOR_ARGB(255, 255, 255, 255) );
	}
}
void CHalberd::Release()
{

}

