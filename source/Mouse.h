#pragma once
#include "obj.h"
#include "Defines.h"

typedef class CMouse : public CObj
{
private:
	POBJ		m_pSelectBox;
	
	_BOOL		m_bSelecting;
	_BOOL		m_bEqual;
	
	_BOOL		m_bButton;
	_BOOL		m_bLButton;
	
	_BOOL		m_bDrop;

	_BOOL		m_bInvenColi;
	
	POINT		m_ptNow;
	POINT		m_ptPast;
	POINT		m_ptDist;

public:
	void	KeyCheck		();
	void	InvenColiCheck	();
	void	ScrollMove		();
	void	SelectBox		();
	POBJ	GetSelectBox	();
	_BOOL	GetSelecting	();
	_BOOL	GetPastPt		();
	POINT	GetPtNow		();
	POINT	GetPtPast		();
	POINT	GetPtDistance	();

public:
	inline _BOOL GetInvenColi() { return m_bInvenColi; }
	inline _BOOL GetDrop()	{ return m_bDrop; }

public:
	void Init();
	void Progress();
	void Render();
	void Release();

public:
	CMouse(void);
	~CMouse(void);
}MOUSE, *PMOUSE;
