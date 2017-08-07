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
	void TurnMotion	();									//�����̵� ġƮŰ
	void PlayerMove	();									//�÷��̾��� �̵�	
	//void Move		(POINT ptDir);						//ĳ������ �̵��� ���̴� �̵��Լ� 
	//void CheckDir	(DIRECTION_ID DI, _BOOL bReverse);	//ĳ���Ͱ� �̵��Ҷ� ������ �ٶ󺽿����� �̵�
	void CheckKey	();
	void CheckState	();									//only for player ���� üũ
	void MotionSet	();									//only for player ���¿� ���� ��� ����

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
