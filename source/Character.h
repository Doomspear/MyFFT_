#pragma once
#include "obj.h"

class CCorpse;
//class CInventory;
typedef class CCharacter : public CObj
{
protected:
	CObj*			m_pInven;

	list<POBJ>		m_listBestTile;
	D3DXVECTOR3		m_vDest;
	POINT			m_ptDest;
	_INT			m_iSelect;

protected:
	_DWORD			m_dwMoveTime;
	_DWORD			m_dwAttTime;
	_DWORD			m_dwAstarTime;
	_DWORD			m_dwSavedMotion;
	

	_BOOL			m_bClicked;			//?
	_BOOL			m_bAttMotion;
	_BOOL			m_bMove;
	_BOOL			m_bArmed;
	_BOOL			m_bDead;
	_BOOL			m_bAstarOn;

	_BOOL			m_bPressed[BI_END];

protected:
	void CheckState				();
	void MotionSet				();

	void SelectCheck			();
	void Select					();
	void DeSelect				();
	
	void Attack					();
	
	void Move					(POINT ptDir);						//ptDir을 향해 이동
	void CheckDir				(DIRECTION_ID DI, _BOOL bReverse);	//이동할때 방향을 바라봄에따라 이동

	_BOOL CheckTargetNeer		();
	_BOOL CheckTargetDistance	();

	void FrameMove				();
	void CallAstar				();
	void TurnToDest				(POINT pt);
	void MoveToDest				();
	void BestMove				();
	void Die					();

public:
	void SetTileList			(list<POBJ> listBestTile);
	void SetDamage				(_INT iAtt);
	void ClearTileList			();
	
//inline
public:
	inline _BOOL	GetDead		() { return m_bDead; }
	inline	CObj*	GetInven	() { return m_pInven; }
	
public:
	CCharacter(void);
	virtual ~CCharacter(void);
}CHARACTER, *PCHARACTER;
