#pragma once
#include "obj.h"

typedef class CTile : public CObj
{
private:
	_BOOL	m_bEdit;

	_BOOL	m_bClosed;		//for astar
	_BOOL	m_bLocoDraw;	//for locomo draw
	_BOOL	m_bStatic;
	
public:
	_DWORD	GetType		();
	_BOOL	GetClosed	();
	_BOOL	GetLocomo	();
	_BOOL	GetStatic	();

private:
	void GetItemFromMouse();

public:
	void SetType(TILE_TYPE TT);
	void SetEdit(_BOOL bEdit);
		
	void SetStatic();	//true = cant move
	void RelStatic();	//false = move
	
	//for locomo draw
	void SetLocomo();
	void SetUnLocomo();	
	
	//for astar
	void SetClosed();
	void SetOpen();

public:
	virtual void Init();
	virtual void Progress();
	virtual void Render();
	virtual void Release();

public:
	CTile(void);
	CTile(POINT pt);
	CTile(CTile& rtile);
	CTile(D3DXVECTOR3 vPos);
	virtual ~CTile(void);
}TILE, *PTILE; 

