#pragma once
#include "character.h"

typedef class CTitan : public CCharacter
{
private:
	_BOOL			m_bClicked;			//?
public:
	void Init		();
	void Progress	();
	void Render		();
	void Release	();
public:
	CTitan(void);
	CTitan(_INT ix, _INT iy);
	virtual ~CTitan(void);
}TITAN, *PTITAN;
