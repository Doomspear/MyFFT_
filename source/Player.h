#pragma once
#include "Character.h"
#include "Defines.h"

typedef class CPlayer :	public CCharacter
{
private:
	_BOOL		m_bLocomo;
	_FLOAT		m_fAngleTemp;		//temp

	CObj*		m_pRobe;
public:
	void TurnMotion	();									//빠른이동 치트키
	void PlayerMove	();									//플레이어의 이동	
	//void Move		(POINT ptDir);						//캐릭터의 이동에 쓰이는 이동함수 
	//void CheckDir	(DIRECTION_ID DI, _BOOL bReverse);	//캐릭터가 이동할때 방향을 바라봄에따라 이동
	void CheckKey	();
	void CheckState	();									//only for player 상태 체크
	void MotionSet	();									//only for player 상태에 따른 모션 셋팅

public:
	void Init		();
	void Progress	();
	void Render		();
	void Release	();

public:
	CPlayer(void);
	CPlayer(_INT ix, _INT iy);
	~CPlayer(void);
}PLAYER, *PPLAYER;
