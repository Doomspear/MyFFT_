#pragma once
#include "item.h"

typedef class CHalberd : public CItem
{
public:
	void Init();
	void Progress();
	void Render();
	void Release();

public:
	CHalberd(void);
	CHalberd(CObj* pOwner);
	virtual ~CHalberd(void);
}HALBERD, *PHALBERD;
