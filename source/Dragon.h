#pragma once
#include "character.h"

typedef class CDragon : public CCharacter
{
public:
	void Init		();
	void Progress	();
	void Render		();
	void Release	();

public:
	CDragon(void);
	CDragon(_INT ix, _INT iy);
	virtual ~CDragon(void);
}DRAGON, *PDRAGON;
