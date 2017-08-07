#pragma once

#include "Obj.h"
#include "Defines.h"

typedef class CGameHandle
{
public:
	void Init();
	void Progress();
	void Render();
	void Release();

public:
	CGameHandle(void);
	~CGameHandle(void);
}GAMEHANDLE, *PGAMEHANDLE;


