#pragma once
#include "staticobj.h"

typedef class CWall : public CStaticObj
{
public:
	void Init();
	void Progress();
	void Render();
	void Release();

public:
	CWall(void);
	CWall::CWall(_INT ix, _INT iy, _INT iNum);
	virtual ~CWall(void);
} WALL, *PWALL;
