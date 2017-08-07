#pragma once
#include "obj.h"

#include "Defines.h"

typedef class CStartBtn : public CObj
{
private:
	_BOOL	m_bSelected;
	_INT	m_iColor;

public:
	void Selected();
	void NotSelected();

public:
	void Init();
	void Progress();
	void Render();
	void Release();

public:
	CStartBtn(void);
	~CStartBtn(void);
}STARTBTN, *PSTARTBTN;
