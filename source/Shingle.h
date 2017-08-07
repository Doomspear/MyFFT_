#pragma once
#include "staticobj.h"

typedef class CShingle : public CStaticObj
{
private:
	void Init();
	void Progress();
	void Render();
	void Release();

public:
	CShingle(void);
	CShingle(_INT ix, _INT iy, _INT iNum = 0, _INT iDepth = 0);
	~CShingle(void);
}SHINGLE, *PSHINGLE;
