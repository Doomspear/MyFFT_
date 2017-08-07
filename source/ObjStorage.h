#pragma once

#include "Obj.h"
#include "Defines.h"

class CObjStorage
{
private:
	list<CObj*>				m_listUI;	//temp
	list<CObj*>				m_listObj[OI_END];
	list<CObj*>				m_listSort;
	list<CObj*>				m_listNotSort;
	list<CObj*>::iterator	m_iter;
	vector<CObj*>			m_vecTile;

	CObj*					m_pMouse;
	
public:
	list<CObj*>*	GetObjList		();
	list<CObj*>*	GetObjList		(OBJ_ID ID);
	list<CObj*>*	GetSortList		();
	CObj*			GetPlayer		();
	CObj*			GetMouse		();
	CObj*			GetBackGround	();

	vector<CObj*>*	GetTileVec		();

public:
	inline list<CObj*>*	GetUIList	()				{ return &m_listUI; }
	inline void			SetInventoUI(POBJ pInven)	{ m_listUI.push_back( pInven ); }

//for tile
public:
	void Tile_Init		(_UINT ix = 5, _UINT iy = 5);
	void Tile_Progress	(_BOOL bEdit);
	void Tile_Render	();
	void Tile_Release	();

//for all object
public:
	void Progress();
	void Render();
	void Release();

/*-singleton-*/
private:
	static CObjStorage* m_pInst;
private:
	void Init();
public:
	inline static CObjStorage* GetInst()
	{
		if ( m_pInst == NULL )
		{
			m_pInst = new CObjStorage;
			m_pInst->Init();
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
	CObjStorage(void);
	~CObjStorage(void);
/*-singleton-*/
};

class CYSort
{
public:
	_BOOL operator() (const CObj& rObj1, const CObj& rObj2)
	{
		return rObj1.GetvPos().y < rObj2.GetvPos().y;
	}

	_BOOL operator() (const CObj* pObj1, const CObj* pObj2)
	{
		return pObj1->GetvPos().y < pObj2->GetvPos().y;
	}
};
