#include "StdAfx.h"
#include "BackGround.h"
#include "Includes.h"

CBackGround::CBackGround(void)
{
}

CBackGround::~CBackGround(void)
{
	Release();
}

void CBackGround::Init()
{
	CObjStorage::GetInst()->Tile_Init(AMOUNTX, AMOUNTY);
}

void CBackGround::Progress()
{
	CObjStorage::GetInst()->Tile_Progress( false );
}

void CBackGround::Render()
{
	CObjStorage::GetInst()->Tile_Render();
}

void CBackGround::Release()
{
	//CObjStorage::GetInst()->Tile_Release();
}