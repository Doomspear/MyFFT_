#pragma once
#include "character.h"

class CBladeSpirits : public CCharacter
{
public:
	void Init		();
	void Progress	();
	void Render		();
	void Release	();

public:
	CBladeSpirits(void);
	CBladeSpirits(_INT ix, _INT iy);
	virtual ~CBladeSpirits(void);
};
