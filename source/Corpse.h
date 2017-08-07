#pragma once
#include "Character.h"

typedef class CCorpse : public CCharacter
{
private:
	PTEXTURE		m_pTexture;
	_INT			m_iTimer;

public:
	void Init		();
	void Progress	();
	void Render		();
	void Release	();

public:
	CCorpse(void);
	CCorpse(CObj* pOwner);
	virtual ~CCorpse(void);
}CORPSE, *PCORPSE;
