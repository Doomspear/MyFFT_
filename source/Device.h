#pragma once

#include "Defines.h"

typedef class CDevice
{
private:
	LPDIRECT3D9			m_pD3D;
	LPDIRECT3DDEVICE9	m_pD3DDevice9;
	LPD3DXSPRITE		m_pD3DXSprite;
	LPD3DXFONT			m_pFont;
	
	RECT				m_rcView;

public:
	HRESULT Init	(WIN_MODE MODE);
	void	Release	();

public:
	LPDIRECT3DDEVICE9	GetDevice	() const;
	LPD3DXSPRITE		GetSprite	() const;
	LPD3DXFONT			GetFont		() const;
	RECT*				GetRect		();


/*-singleton-*/
private:
	static CDevice*	m_pInst;
public:
	inline static	CDevice* GetInst()
	{
		if ( m_pInst == NULL )
		{
			m_pInst = new CDevice;
		}
		return m_pInst;
	}
	inline void DestroyInst()
	{
		if ( m_pInst != NULL )
		{
			delete m_pInst;
			m_pInst = NULL;
		}
	}
private:
	CDevice(void);
	~CDevice(void);
/*-singleton-*/
}DEVICE, *PDEVICE;
