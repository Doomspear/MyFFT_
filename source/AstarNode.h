#pragma once

#include "Defines.h"
#include "Obj.h"
#include "Tile.h"

typedef class CAstarNode
{
//일단 편하게 public으로 품
public:
	POBJ	m_pTile;
	POBJ	m_pParent;
	POBJ	m_pDestination;
	
	_FLOAT	m_fCost;

public:
	_FLOAT	GetCost();
	POBJ	GetTile();
	POBJ	GetParent();

public:
	void CalculateCost();

public:
	CAstarNode(void);
	~CAstarNode(void);
}ASTARNODE, *PASTARNODE;

class CCostSort
{
public:
	_BOOL operator() (const CAstarNode& rNode1, const CAstarNode& rNode2)
	{
		return rNode1.m_fCost < rNode2.m_fCost;
	}

	_BOOL operator() (const CAstarNode* pNode1, const CAstarNode* pNode2)
	{
		return pNode1->m_fCost < pNode2->m_fCost;
	}
};