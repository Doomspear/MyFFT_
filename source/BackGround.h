#pragma once
#include "obj.h"

#include "Defines.h"

typedef class CBackGround : public CObj
{
public:
	void Init();
	void Progress();
	void Render();
	void Release();

public:
	CBackGround(void);
	~CBackGround(void);
}BACKGROUND, *PBACKGROUND;
