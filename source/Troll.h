#pragma once
#include "Character.h"

typedef class CTroll : public CCharacter
{
public:
	void Init		();
	void Progress	();
	void Render		();
	void Release	();

public:
	CTroll(void);
	CTroll(_INT ix, _INT iy);
	virtual ~CTroll(void);
}TROLL, *PTROLL;
