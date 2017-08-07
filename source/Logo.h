#pragma once
#include "viewobj.h"

typedef class CLogo : public CViewObj
{
public:	
	HRESULT	Init();
	void	Progress();
	void	Render();
	void	Release();

public:
	CLogo(void);
	~CLogo(void);
}LOGO, *PLOGO;
