#pragma once
#include "obj.h"
#include "Defines.h"

typedef class CSelectBox : public CObj
{
private:
	enum DRAW_TYPE	{ DT_LEFTTOP
					, DT_RIGHTTOP
					, DT_LEFTBOT
					, DT_RIGHTBOT };

	D3DXVECTOR3		m_vStartPos;
	D3DXVECTOR3		m_vEndPos;

	_DWORD			m_dwMidID;

public:
	void SetStartPos(D3DXVECTOR3 vPos);

public:
	void Init();
	void Progress();
	void Render();
	void Release();

public:
	CSelectBox(void);
	CSelectBox(D3DXVECTOR3 vPos);
	~CSelectBox(void);
}SELECTBOX, *PSELECTBOX;
