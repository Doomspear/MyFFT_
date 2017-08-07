#pragma once
#include "staticobj.h"

typedef class CWallSet : public CStaticObj
{
private:
	list< POBJ >		m_listWall;

public:
	list<POBJ>* GetWallList();

public:
	void Init();
	void Progress();
	void Render();
	void Release();

public:
	CWallSet(void);
	CWallSet(_INT ix, _INT iy);
	virtual ~CWallSet(void);
}WALLSET, *PWALLSET;
