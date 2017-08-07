#pragma once
#include "StaticObj.h"

typedef class CPostStone : public CStaticObj
{
public:
	void Init();
	void Progress();
	void Render();
	void Release();

public:
	CPostStone(void);
	CPostStone(_INT ix, _INT iy, _INT iNum = 0);
	~CPostStone(void);
} POSTSTONE, *PPOSTSTONE;
