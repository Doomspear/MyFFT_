#pragma once
#include "item.h"

typedef class CRobe : public CItem
{
public:
	void KeyCheck();

public:
	void Init();
	void Progress();
	void Render();
	void Release();

public:
	CRobe(void);
	CRobe(CObj* pOwner);
	virtual ~CRobe(void);
}ROBE, *PROBE;
