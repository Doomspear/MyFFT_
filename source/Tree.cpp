#include "StdAfx.h"
#include "Tree.h"
#include "Includes.h"

CTree::CTree(void)
{
}

CTree::CTree(TEXTURE_ID ID, _INT ix, _INT iy)
{
	m_dwTexID		= ID;
	m_pt.x			= ix;
	m_pt.y			= iy;
}

CTree::~CTree(void)
{
}

void CTree::Init()
{
	m_dwMidID		= MI_TREE;
	m_dwDir			= DI_DOWN;

	m_pvecTex		= _GETINST( CTextureLoader )->GetTextureVector();

	m_iFrame		= 0;
	m_iAlpha		= 255;
	m_iDepth		= 0;	

	m_fDegree		= 45.0f;

	m_vCenter		= (*m_pvecTex)[m_dwTexID][m_dwMidID][m_dwDir][0]->vCen;
	m_fSizeX		= m_vCenter.x;
	m_fSizeY		= m_vCenter.y;
	m_vLeafCenter	= (*m_pvecTex)[m_dwTexID][m_dwMidID][m_dwDir][1]->vCen;

	//������ �ö� Ÿ���� �̵��Ұ� Ÿ�Ϸ�
	_INT iIndex		= m_pt.x * AMOUNTY + m_pt.y;
	PTILE((* _GETINST( CObjStorage )->GetTileVec() )[iIndex])->SetStatic();
}

void CTree::Progress()
{
	MoveToIndex();
	RevisionPos();
	
	m_vLeafPos.x	= m_vPos.x + 10;
	m_vLeafPos.y	= m_vPos.y + 10;
	m_vLeafPos.z	= 0.0f;

	D3DXVECTOR3		vTemp = m_vPos;

	vTemp.y -= m_vLeafCenter.y / 2.0f;

	SetColRect(vTemp, m_vLeafCenter.x, m_vLeafCenter.y);
	//SetColRect();
	//SetColRectLeaf();

	RECT rcTemp;
	//�÷��̾ ���̶� �浹�ϸ� ���� �����ϵ���
	if ( IntersectRect( &rcTemp, &m_rcColi, &_GETINST( CObjStorage )->GetPlayer()->GetColRect() ) )
	{
		m_iAlpha = 100;	
	}
	else
		m_iAlpha = 255;
}

void CTree::Render()
{
	//����
	D3DXMatrixTranslation( &m_matTrans, m_vPos.x, m_vPos.y, m_vPos.z );
	
	//shadow
	D3DXMatrixRotationZ( &m_matRotateZ, D3DXToRadian( 15 ) );
	m_matWorld = m_matRotateZ * m_matTrans;
	_GETINST( CDevice )->GetSprite()->SetTransform( &m_matWorld );
	_GETINST( CDevice )->GetSprite()->Draw( (*m_pvecTex)[m_dwTexID][m_dwMidID][m_dwDir][0]->pTex, NULL, &m_vCenter, NULL, D3DCOLOR_ARGB(100, 0, 0, 0) );

	m_matWorld = m_matTrans;

	_GETINST( CDevice )->GetSprite()->SetTransform( &m_matWorld );
	_GETINST( CDevice )->GetSprite()->Draw( (*m_pvecTex)[m_dwTexID][m_dwMidID][m_dwDir][0]->pTex
										  , NULL, &m_vCenter, NULL
										  , D3DCOLOR_ARGB(255, 255, 255, 255) );

		
	

	//��
	D3DXMatrixTranslation( &m_matTrans, m_vLeafPos.x, m_vLeafPos.y, m_vLeafPos.z );
	D3DXMatrixRotationZ( &m_matRotateZ, D3DXToRadian( 15 ) );
	m_matWorld = m_matRotateZ * m_matTrans;
	_GETINST( CDevice )->GetSprite()->SetTransform( &m_matWorld );
	_GETINST( CDevice )->GetSprite()->Draw( (*m_pvecTex)[m_dwTexID][m_dwMidID][m_dwDir][1]->pTex, NULL, &m_vLeafCenter, NULL, D3DCOLOR_ARGB(100, 0, 0, 0) );

	m_matWorld = m_matTrans;

	_GETINST( CDevice )->GetSprite()->SetTransform( &m_matWorld );
	_GETINST( CDevice )->GetSprite()->Draw( (*m_pvecTex)[m_dwTexID][m_dwMidID][m_dwDir][1]->pTex
										  , NULL, &m_vLeafCenter, NULL
										  , D3DCOLOR_ARGB(m_iAlpha, 255, 255, 255) );

	//DrawColiBox();
}

void CTree::Release()
{

}

