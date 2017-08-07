#pragma once
#include "item.h"

typedef class CDeathShroud : public CItem
{
public:
	void Init();
	void Progress();
	void Render();
	void Release();

public:
	CDeathShroud(void);
	CDeathShroud(CObj* pOwner);
	virtual ~CDeathShroud(void);
}DEATHSHROUD, *PDEATHSHROUD;
