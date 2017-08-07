#pragma once
#include "obj.h"

typedef class CEditBtn : public CObj
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
	CEditBtn(void);
	~CEditBtn(void);
}EDITBTN, *PEDITBTN;
