#pragma once

#include "Defines.h"

typedef class CKeyChecker
{
private:
	list<_INT>	m_listDbClick;
	
	_DWORD		m_DbClickTime;
	_BOOL		m_bPressed;

public:
	_DWORD GetKeyState();

public:
	_BOOL CheckDbClick();

/*-singleton-*/
private:
	static CKeyChecker*	m_pInst;
public:
	inline static CKeyChecker*	GetInst()
	{
		if ( m_pInst == NULL )
		{
			m_pInst = new CKeyChecker;
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
	CKeyChecker(void);
	~CKeyChecker(void);
/*-singleton-*/
}KEYCHECKER, *PKEYCHECKER;
