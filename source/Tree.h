#pragma once
#include "StaticObj.h"

typedef class CTree : public CStaticObj
{
private:
	D3DXVECTOR3		m_vLeafCenter;
	D3DXVECTOR3		m_vLeafPos;

public:
	void Init();
	void Progress();
	void Render();
	void Release();

public:
	CTree(void);
	CTree(TEXTURE_ID ID, _INT ix, _INT iy);
	virtual ~CTree(void);
}TREE, *PTREE;
