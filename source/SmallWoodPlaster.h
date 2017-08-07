#pragma once
#include "staticobj.h"

typedef class CSmallWoodPlaster : public CStaticObj
{
private:
	list<POBJ>			m_listHouse;

	POBJ				m_pFloor;
	POBJ				m_pWall;
	POBJ				m_pRoof;

public:
	void CheckPlayer();
	list<POBJ>* GetHouseList();
	list<POBJ>* GetFloorList();

public:
	void Init();
	void Progress();
	void Render();
	void Release();
	
public:
	CSmallWoodPlaster(void);
	CSmallWoodPlaster(_INT ix, _INT iy);
	virtual ~CSmallWoodPlaster(void);
}SMALLWOODPLASTER, *PSMALLWOODPLASTER;
