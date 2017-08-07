#pragma once
#include "obj.h"

typedef class CStaticObj :	public CObj
{
protected:
	_INT	m_iAlpha;
	_INT	m_iDepth;

public:
	inline void SetAlpha(_INT iAlpha)
	{
		if ( iAlpha < 0 || iAlpha > 255 )
		{
			//m_iAlpha = 255;
			//MessageBox(g_hWnd, L"���İ��� �ùٸ��� �ʽ��ϴ�.", L"SYSTEM ERROR", MB_OK);
			return;
		}
		else
			m_iAlpha = iAlpha; 
	}

public:
	CStaticObj(void);
	virtual ~CStaticObj(void);
}STATICOBJ, *PSTATICOBJ;
