#pragma once

#include "Defines.h"
#include "Obj.h"

typedef class CMediator
{
/*-singleton-*/
private:
	static CMediator*	m_pInst;
public:
	inline static CMediator* GetInst()
	{
		if ( m_pInst == NULL )
		{
			m_pInst = new CMediator;
		}
		return m_pInst;
	}
	inline void DestroyInst()
	{
		if ( m_pInst != NULL )
		{
			delete m_pInst;
			m_pInst = NULL;
		}
	}
private:
	CMediator(void);
	~CMediator(void);
/*-singleton-*/
}MEDIATOR, *PMEDIATOR;
