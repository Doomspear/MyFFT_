#pragma once

#include "Defines.h"

typedef class CButtonObj
{
protected:
	vector<LPDIRECT3DTEXTURE9>*		m_pvecTex;
	D3DXVECTOR3						m_vPos;
	D3DXVECTOR3						m_vCenter;

	D3DXMATRIXA16					m_matWorld;

public:
	virtual void Init()		= 0;
	virtual void Progress()	= 0;
	virtual void Render()	= 0;
	virtual void Release()	= 0;

public:
	CButtonObj(void);
	virtual ~CButtonObj(void);
}BUTTONOBJ, *PBUTTONOBJ;
