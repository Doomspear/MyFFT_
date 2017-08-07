#pragma once

#include "Defines.h"
#include "ViewObj.h"

typedef class CViewHandle
{
private:
	 CViewObj*		m_pViewObj;

public:
	void		SetView	(MIDDLE_ID ID);
	CViewObj*	GetView	() const;

/*-singleton-*/
private:
	static CViewHandle*	m_pInst;
public:
	inline static CViewHandle*	GetInst()
	{
		if ( m_pInst == NULL )
		{
			m_pInst = new CViewHandle;
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
	CViewHandle(void);
	~CViewHandle(void);
/*-singleton-*/
}VIEWHANDLE, *PVIEWHANDLE;
