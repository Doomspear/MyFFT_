#pragma once
#include "staticobj.h"

typedef class CRoof : public CStaticObj
{
private:
	list<POBJ>	m_listRoof;

public:
	list<POBJ>*	 GetRoofList();

public:
	void Init();
	void Progress();
	void Render();
	void Release();

public:
	CRoof(void);
	CRoof(_INT ix, _INT iy);
	virtual ~CRoof(void);
}ROOF, *PROOF;
