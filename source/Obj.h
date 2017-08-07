#pragma once

#include "Defines.h"

typedef class CObj
{ 
protected:
	static D3DXVECTOR3		m_vScroll;
	static POINT			m_ptStatic;

protected:
	vector<PTEXTURE>(*		m_pvecTex)[TI_END][MI_END][DI_END];
	list<CObj*>::iterator	m_iter;

	list<CObj*>				m_listItem;

protected:
	D3DXMATRIXA16		m_matWorld;
	
	D3DXMATRIXA16		m_matScale;
	D3DXMATRIXA16		m_matRotateZ;
	D3DXMATRIXA16		m_matTrans;

	D3DXVECTOR3			m_vCenter;
	D3DXVECTOR3			m_vPos;
	D3DXVECTOR3			m_vInvenPos;
	D3DXVECTOR3			m_vLook;

protected:
	//temp
	CObj*	m_pCloth;
	CObj*	m_pWeapon;

	CObj*	m_pTarget;

protected:
	//for status
	_DWORD	m_dwTexID;
	_DWORD	m_dwMidID;
	_DWORD	m_dwMidIDPast;
	_DWORD	m_dwDir;
		
	_INT	m_iTileIndex;
	_INT	m_iDepth;

	_DWORD	m_dwState;

	_INT	m_iFrame;
	_BOOL	m_bReverse;
	_BOOL	m_bDecay;
		
	_DWORD	m_dwTime;
	_DWORD	m_dwTick;
	
	_FLOAT	m_fSizeX;
	_FLOAT	m_fSizeY;
	
	_FLOAT	m_fSpeed;
	_FLOAT	m_fDegree;
	
	_INT	m_iLocomotive;
	
	//for char stat
	_INT	m_iAction;

	_INT	m_iHP;
	_INT	m_iMP;
	
	_INT	m_iSTR;
	_INT	m_iDEX;
	_INT	m_iINT;

	_INT	m_iATT;
	_INT	m_iAR;

	_INT	m_iWeight;

	//Tile Index
	POINT	m_pt;
	POINT	m_ptPast;
	RECT	m_rcColi;

public:
	void	MoveToIndex		();
	void	PosToIndex		();

	void	DrawHP			() const;
	void	DrawPos			() const; 
	void	DrawIndex		() const;
	void	DrawDepth		() const; 
	void	DrawColiBox		() const;
	void	DrawColiBox		(RECT* prc) const;
	void	DrawColiBoxF	(D3DXVECTOR3 vCenter = D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	void	ScrollSet		();
	void	ScrollSet		(D3DXVECTOR3* vpPos);
	_BOOL	SightCheck		();
	void	RevisionPos		();
	void	ClearTarget		();

	void	CheckReverse	();
	void	CheckActive		();
	_BOOL	CheckSumIndex	(_INT ix, _INT iy);
	
public:
	void 	SetColRect		();
	void 	SetColRect		(_FLOAT fSizeX, _FLOAT fSizeY);
	void 	SetColRect		(D3DXVECTOR3 vPos, _FLOAT fSizeX, _FLOAT fSizeY);
	void 	SetColRectTile	();
	void 	SetColRectLeaf	();
	
	void 	SetTarget		(CObj* pTarget);
	void 	SetScroll		(D3DXVECTOR3 vPos);
	void 	SetIndexPt		(POINT pt);
	void 	SetTileIndex	();
	void 	SetDepth		(_INT iDepth);
	void 	SetDepthPos		();
	void 	SetAction		(_INT iAction);
	void	SetInvenPos		(_INT ix, _INT iy);
			
	void 	SetClothOff		();
	void 	SetDisarm		();

public:
	void DelFlag(STATE_ID ID);
	void AddFlag(STATE_ID ID);
	
public:
	RECT		GetColRect	() const;
	D3DXVECTOR3	GetvPos		() const;
	_FLOAT		GetSizeX	() const;
	_FLOAT		GetSizeY	() const;
	POINT		GetIndexPt	() const;
	_INT		GetDepth	() const;

	_DWORD	GetTexID		() const;
	_DWORD	GetMidID		() const;
	_DWORD	GetDirection	() const;
	_DWORD	GetState		() const;
	_INT	GetFrame		() const;
	_BOOL	GetReverse		() const;
	_BOOL	GetDecay		() const;

	CObj*	GetCloth		() const;
	CObj*	GetWeapon		() const;

//inline	
public:
	inline CObj*		GetTarget	() const			{ return m_pTarget; }
	inline _INT			GetHP		() const			{ return m_iHP;	}
	inline D3DXVECTOR3	GetInvenPos	() const			{ return m_vInvenPos; }
	inline void			SetvPos		(D3DXVECTOR3 vPos)	{ m_vPos = vPos; }
	inline list<CObj*>*	GetItemList	()					{ return &m_listItem; }

public:
	virtual void Init		() = 0;
	virtual void Progress	() = 0;
	virtual void Render		() = 0;
	virtual void Release	() = 0;

public:
	CObj(void);
	virtual ~CObj(void);
}OBJ, *POBJ;

