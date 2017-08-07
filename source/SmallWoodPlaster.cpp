#include "StdAfx.h"
#include "SmallWoodPlaster.h"
#include "Includes.h"

CSmallWoodPlaster::CSmallWoodPlaster(void)
{
}

CSmallWoodPlaster::CSmallWoodPlaster(_INT ix, _INT iy)
{
	m_pt.x 		= ix;
	m_pt.y 		= iy;
	
	m_pFloor 	= CObjFactory<FLOOR>::CreateObj( m_pt.x, m_pt.y );
	m_pRoof 	= CObjFactory<ROOF>::CreateObj( m_pt.x, m_pt.y );
	m_pWall		= CObjFactory<WALLSET>::CreateObj( m_pt.x, m_pt.y );
}

CSmallWoodPlaster::~CSmallWoodPlaster(void)
{
	Release();
}

void CSmallWoodPlaster::Init()
{
	/*for ( m_iter = PFLOOR(m_pFloor)->GetFloorList()->begin(); 
		m_iter != PFLOOR(m_pFloor)->GetFloorList()->end(); ++m_iter )
	{
		m_listHouse.push_back( (*m_iter) );
	}*/

	for ( m_iter = PWALLSET(m_pWall)->GetWallList()->begin(); 
		m_iter != PWALLSET(m_pWall)->GetWallList()->end(); ++m_iter )
	{
		m_listHouse.push_back( (*m_iter) );
	}

	for ( m_iter = PROOF(m_pRoof)->GetRoofList()->begin(); 
		m_iter != PROOF(m_pRoof)->GetRoofList()->end(); ++m_iter )
	{
		m_listHouse.push_back( (*m_iter) );
	}	
}

void CSmallWoodPlaster::Progress()
{
	CheckPlayer();
	
	m_pFloor->Progress();
	m_pWall->Progress();	
	m_pRoof->Progress();
}

void CSmallWoodPlaster::Render()
{
	m_pFloor->Render();
	m_pWall->Render();	
	m_pRoof->Render();

	/*for ( m_iter = m_listHouse.begin(); m_iter != m_listHouse.end(); ++m_iter )
	{
		(*m_iter)->Render();
	}*/
}

void CSmallWoodPlaster::Release()
{
	delete m_pFloor;
	m_pFloor = NULL;
	
	delete m_pWall;
	m_pWall = NULL;
	
	delete m_pRoof;
	m_pRoof = NULL;
}

void CSmallWoodPlaster::CheckPlayer()
{
	POINT pt = _GETINST( CObjStorage )->GetPlayer()->GetIndexPt();

	if ( pt.x >= m_pt.x && pt.x <= m_pt.x + 5 )
	{
		if ( pt.y >= m_pt.y && pt.y <= m_pt.y + 5 )
		{
			PROOF(m_pRoof)->SetAlpha( 0 );
		}
	}
	else
		PROOF(m_pRoof)->SetAlpha( 255 );
}

list<POBJ>* CSmallWoodPlaster::GetHouseList()
{
	return &m_listHouse;
}

list<POBJ>* CSmallWoodPlaster::GetFloorList()
{
	return PFLOOR(m_pFloor)->GetFloorList();
}