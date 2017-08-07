#pragma once
#include "StaticObj.h"

typedef class CWoodenBoard : public CStaticObj
{
public:
	void Init();
	void Progress();
	void Render();
	void Release();

public:
	CWoodenBoard(void);
	CWoodenBoard(_INT ix, _INT iy, _INT iNum);
	~CWoodenBoard(void);
} WOODENBOARD, *PWOODENBOARD;
