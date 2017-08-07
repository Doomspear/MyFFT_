#pragma once
#include "obj.h"

typedef class CInventory : public CObj
{
private:
	CObj*			m_pInvenOwner;

	//list<CObj*>		m_listItem;
	D3DXVECTOR3		m_vDist;

	_BOOL			m_bLoot;
	_BOOL			m_bDrag;
	_BOOL			m_bShow;
	_BOOL			m_bOwnerDead;

public:
	void Insert(CObj* pItem);
	void Insert(CObj* pItem, D3DXVECTOR3 vPos);
	void KeyCheck();

public:
	inline list<CObj*>* GetInvenItemList	()					{ return &m_listItem; }
	inline void			ShowInven			()					{ m_bShow = true; }
	inline void			HideInven			()					{ m_bShow = false; }
	inline void			SetLoot				()					{ m_bLoot = true; }
	inline void			ResLoot				()					{ m_bLoot = false; }
	inline _BOOL		GetState			()					{ return m_bShow; }
	inline CObj*		GetInvenOwner		()					{ return m_pInvenOwner; }
	inline void			SetInvenOwner		(CObj* pInvenOwner)	{ m_pInvenOwner = pInvenOwner; }

public:
	void Init();
	void Progress();
	void Render();
	void Release();

public:
	CInventory(void);
	CInventory(CObj* pOwner);
	virtual ~CInventory(void);
}INVENTORY, *PINVENTORY;
