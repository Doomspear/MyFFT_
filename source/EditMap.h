#pragma once
#include "viewobj.h"
#include "Defines.h"

typedef class CEditMap : public CViewObj
{
private:
	void SaveTileData();
	void LoadTileData();

public:
	HRESULT	Init();
	void	Progress();
	void	Render();
	void	Release();

public:
	CEditMap(void);
	~CEditMap(void);
}EDITMAP, *PEDITMAP;
