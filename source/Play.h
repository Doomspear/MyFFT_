#pragma once
#include "viewobj.h"
#include "Obj.h"

typedef class CPlay : public CViewObj
{
public:
	HRESULT	Init();
	void	Progress();
	void	Render();
	void	Release();

public:
	CPlay(void);
	~CPlay(void);
}PLAY, *PPLAY;
