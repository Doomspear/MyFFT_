#pragma once
#include "viewobj.h"

#include "Defines.h"
#include "Obj.h"

typedef class CMyMenu :	public CViewObj
{
private:
	CObj*	m_pStartBtn;
	CObj*	m_pEditBtn;

public:
	HRESULT	Init();
	void	Progress();
	void	Render();
	void	Release();

public:
	CMyMenu(void);
	~CMyMenu(void);
}MYMENU, *PMYMENU;
