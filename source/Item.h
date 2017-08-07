#pragma once
#include "obj.h"

typedef class CItem : public CObj
{
protected:
	_DWORD	m_IconID;
	CObj*	m_pOwner;
	_BOOL	m_bShrink;
	_INT	m_iAlpha;
	RECT	m_rcIcon;

	_BOOL	m_bClick;
	_BOOL	m_bSelected;
	_BOOL	m_bInInven;

public:
	void SetIconColi();
	void SetIconColi(_INT i);
	
	inline void SetInInven() { m_bInInven = true; }
	inline void SetPopInven() { m_bInInven = false; }

	inline void SetAlpha(_INT iAlpha)
	{
		if ( iAlpha < 0 || iAlpha > 255 )
		{
			//m_iAlpha = 255;
			//MessageBox(g_hWnd, L"알파값이 올바르지 않습니다.", L"SYSTEM ERROR", MB_OK);
			return;
		}
		else
			m_iAlpha = iAlpha; 
	}

	inline void SetShrink()	{ m_bShrink = true; }	
	inline void DelShrink() { m_bShrink = false; }
	inline void SetOwner(CObj* pOwner) { m_pOwner = pOwner; }
	inline POBJ GetOwner() { return m_pOwner; }
	inline _BOOL GetSelected() { return m_bSelected; }

public:
	CItem(void);
	virtual ~CItem(void);
}ITEM, *PITEM;
