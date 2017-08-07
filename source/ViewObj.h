#pragma once

#include "Defines.h"

typedef class CViewObj
{
protected:
	D3DXMATRIXA16					m_matWorld;
	vector<PTEXTURE>		(*m_pvecTex)[TI_END][MI_END][DI_END];

	D3DXVECTOR3						m_vCenter;
	D3DXVECTOR3						m_vPos;
	D3DXVECTOR3						m_vLook;

protected:
	_DWORD							m_dwTime;
	_INT							m_iAlpha;
	_BOOL							m_bShow;
public:
	virtual HRESULT	Init()		= 0;
	virtual void	Progress()	= 0;
	virtual void	Render()	= 0;
	virtual void	Release()	= 0;

public:
	CViewObj(void);
	virtual ~CViewObj(void);
}VIEWOBJ, *PVIEWOBJ;
