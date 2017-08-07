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

	//�� �κ��� ��¥ �Ÿ�������� �ٲٸ� �Ƹ� ������ �پ��� ����
	m_fCost				= D3DXVec3Length( &vTemp );
}


