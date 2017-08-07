#pragma once
#include "staticobj.h"

typedef class CDoor : public CStaticObj
{
private:
	_BOOL	m_bClicked;

public:
	void DoorMove();

public:
	void Init();
	void Progress();
	void Render();
	void Release();

public:
	CDoor(void);
	CDoor(_INT ix, _INT iy, _INT iNum = 0);
	virtual ~CDoor(void);
}DOOR, *PDOOR;
