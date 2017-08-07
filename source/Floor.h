#pragma once

#include "staticobj.h"

typedef class CFloor : public CStaticObj
{
private:
	list< POBJ >		m_listFloor;

public:
	list< POBJ >* GetFloorList();		

public:
	void Init();
	void Progress();
	void Render();
	void Release();

public:
	CFloor(void);
	CFloor(_INT ix, _INT iy);
	virtual ~CFloor(void);
} FLOOR, *PFLOOR; 
