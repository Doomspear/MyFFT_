#include "StdAfx.h"
#include "AstarNode.h"

CAstarNode::CAstarNode(void)
{
}

CAstarNode::~CAstarNode(void)
{
}

_FLOAT CAstarNode::GetCost()
{
	return m_fCost;
}

POBJ CAstarNode::GetTile()
{
	return m_pTile;
}

POBJ CAstarNode::GetParent()
{
	return m_pParent;
}	

void CAstarNode::CalculateCost()
{
	D3DXVECTOR3 vTemp	= m_pDestination->GetvPos() - m_pTile->GetvPos();

	//이 부분을 진짜 거리비용으로 바꾸면 아마 뻘짓이 줄어들것 같음
	m_fCost				= D3DXVec3Length( &vTemp );
}


