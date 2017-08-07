#pragma once

#include "Obj.h"
#include "Defines.h"

template <typename T>
class CObjFactory
{
public:
	static CObj* CreateObj()
	{
		CObj*	pObj = new T;
		pObj->Init();

		return pObj;
	}
	
	static CObj* CreateObj(POINT pt)
	{
		CObj*	pObj = new T(pt);
		pObj->Init();

		return pObj;
	}

	static CObj* CreateObj(_INT ix, _INT iy)
	{
		CObj*	pObj = new T(ix, iy);
		pObj->Init();

		return pObj;
	}

	static CObj* CreateObj(D3DXVECTOR3 vPos)
	{
		CObj*	pObj = new T(vPos);
		pObj->Init();

		return pObj;
	}

	static CObj* CreateObj( CObj* pOwner )
	{
		CObj*	pObj = new T( pOwner );
		pObj->Init();

		return pObj;
	}

	//for trees
	static CObj* CreateObj(TEXTURE_ID ID, _INT ix, _INT iy)
	{
		CObj*	pObj = new T( ID, ix, iy );
		pObj->Init();

		return pObj;
	}

	//for house static obj
	static CObj* CreateObj(_INT ix, _INT iy, _INT iNum)
	{
		CObj*	pObj = new T( ix, iy, iNum );
		pObj->Init();

		return pObj;
	}
	
	static CObj* CreateObj(_INT ix, _INT iy, _INT iNum, _INT iDepth)
	{
		CObj*	pObj = new T( ix, iy, iNum, iDepth );
		pObj->Init();

		return pObj;
	}

public:
	CObjFactory(void) { }
	~CObjFactory(void) { }
};
