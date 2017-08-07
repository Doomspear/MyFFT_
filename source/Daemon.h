#pragma once
#include "character.h"

typedef class CDaemon : public CCharacter
{
public:
	void Init		();
	void Progress	();
	void Render		();
	void Release	();

public:
	CDaemon(void);
	CDaemon(_INT ix, _INT iy);
	virtual ~CDaemon(void);
}DAEMON, *PDAEMON;
