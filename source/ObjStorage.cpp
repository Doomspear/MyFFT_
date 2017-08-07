#include "StdAfx.h"
#include "ObjStorage.h"
#include "Includes.h"

CObjStorage* CObjStorage::m_pInst = NULL;

CObjStorage::CObjStorage(void)
{
}

CObjStorage::~CObjStorage(void)
{
	Tile_Release();
	Release();
}

void CObjStorage::Init()
{
	m_listObj[OI_BACKGROUND].push_back( CObjFactory<BACKGROUND>::CreateObj() );
	m_listObj[OI_PLAYER].push_back( CObjFactory<PLAYER>::CreateObj() );
	
	m_listObj[OI_MONSTER].push_back( CObjFactory<TROLL>::CreateObj( 1, 1 ) );
	m_listObj[OI_MONSTER].push_back( CObjFactory<DRAGON>::CreateObj( 10, 3 ) );
	m_listObj[OI_MONSTER].push_back( CObjFactory<TITAN>::CreateObj( 10, 7 ) );
	m_listObj[OI_MONSTER].push_back( CObjFactory<DAEMON>::CreateObj( 7, 10 ) );
	
	for ( int i = 0; i < 5; ++i )
	{
		m_listObj[OI_TREE].push_back( CObjFactory<TREE>::CreateObj( TI_TREEPEAR, i, 5 ) );		
	}
	for ( int i = 0; i < 5; ++i )
	{
		m_listObj[OI_TREE].push_back( CObjFactory<TREE>::CreateObj( TI_TREEPEAR, 5, i ) );		
	}
	
	m_listObj[OI_TREE].push_back( CObjFactory<TREE>::CreateObj( TI_TREEPEAR, 15, 15 ) );		
	m_listObj[OI_TREE].push_back( CObjFactory<TREE>::CreateObj( TI_TREEBIGAPPLE, 1, 7 ) );		
	m_listObj[OI_TREE].push_back( CObjFactory<TREE>::CreateObj( TI_TREEPEAR, 10, 26 ) );
	
	m_listObj[OI_TREE].push_back( CObjFactory<TREE>::CreateObj( TI_TREEAPPLE, 2, 22 ) );
	m_listObj[OI_TREE].push_back( CObjFactory<TREE>::CreateObj( TI_TREEPEAR, 13, 12 ) );		
	m_listObj[OI_TREE].push_back( CObjFactory<TREE>::CreateObj( TI_TREEPEAR, 12, 20 ) );		
	m_listObj[OI_TREE].push_back( CObjFactory<TREE>::CreateObj( TI_TREEBIGAPPLE, 6, 24 ) );

	for ( int i = 0; i < 20; ++i )
	{
		m_listObj[OI_TREE].push_back( CObjFactory<TREE>::CreateObj( TI_TREEPEAR, 18, i ) );		
	}

	for ( int i = 5; i < 25; ++i )
	{
		m_listObj[OI_TREE].push_back( CObjFactory<TREE>::CreateObj( TI_TREEPEAR, 23, i ) );		
	}
	
	m_listObj[OI_HOUSE].push_back( CObjFactory<SMALLWOODPLASTER>::CreateObj( 2, 12 ) );
	
	for ( _UINT i = 0; i < OI_END; ++i )
	{
		for ( m_iter = m_listObj[i].begin(); m_iter != m_listObj[i].end(); ++m_iter )
		{
			if ( i == OI_HOUSE )
			{
				list<POBJ>::iterator		iter;
				for ( iter = PSMALLWOODPLASTER(*m_iter)->GetHouseList()->begin();
					iter != PSMALLWOODPLASTER(*m_iter)->GetHouseList()->end();
					++iter)
				{
					m_listSort.push_back( (*iter) );
				}
				for ( iter = PSMALLWOODPLASTER(*m_iter)->GetFloorList()->begin();
					iter != PSMALLWOODPLASTER(*m_iter)->GetFloorList()->end();
					++iter)
				{
					m_listNotSort.push_back( (*iter) );
				}
			}
			else
				m_listSort.push_back( (*m_iter) );
		}
	}
	//따로 이거 수정해야 함
	m_pMouse = CObjFactory<MOUSE>::CreateObj();
	//m_listUI.push_back( PCHARACTER( _GETINST( CObjStorage )->GetPlayer() )->GetInven() );
}

void CObjStorage::Progress()
{
	/*for ( m_iter = m_listNotSort.begin(); m_iter != m_listNotSort.end(); )
	{
		(*m_iter)->Progress();
		++m_iter;
	}	

	for ( m_iter = m_listSort.begin(); m_iter != m_listSort.end(); )
	{
		if ( PCHARACTER(*m_iter)->GetDead() == true )
		{
			delete (*m_iter);
			(*m_iter) = NULL;
			m_iter = m_listSort.erase( m_iter );
		}
		else
		{
			(*m_iter)->Progress();
			++m_iter;
		}
	}*/

	for ( _UINT i = 0; i < OI_END; ++i )
	{
		for ( m_iter = m_listObj[i].begin(); m_iter != m_listObj[i].end(); )
		{
			if ( (*m_iter) == NULL )
			{
				++m_iter;
			}

			if ( i == OI_CORPSE )
			{
				/*if ( (*m_iter)->GetDecay() == true )
				{
					delete (*m_iter);
					(*m_iter) = NULL;

					m_iter = m_listObj[i].erase( m_iter );
				}
				else
				{
					(*m_iter)->Progress();
					++m_iter;
					continue;
				}*/
			}

			//죽었으면 지움
			if ( (PCHARACTER(*m_iter)->GetDead() == true) || ((*m_iter)->GetDecay() == true) )
			{
				delete (*m_iter);
				(*m_iter) = NULL;
				m_iter = m_listObj[i].erase( m_iter );
			}
			else
			{
				(*m_iter)->Progress();
				++m_iter;
			}
		}	
	}

	for ( m_iter = m_listUI.begin(); m_iter != m_listUI.end(); )
	{
		if ( (*m_iter)->GetMidID() == UI_INVEN || (*m_iter)->GetMidID() == UI_LOOT )
		{
			if ( PINVENTORY(*m_iter)->GetInvenOwner() == NULL )
			{
				delete (*m_iter);
				(*m_iter) = NULL;

				m_iter = m_listUI.erase( m_iter );
			}
			else
			{
				(*m_iter)->Progress();
				++m_iter;
			}
		}
		else
		{
			(*m_iter)->Progress();
			++m_iter;
		}
	}

	m_pMouse->Progress();
}

void CObjStorage::Render()
{
	/*for ( _UINT i = 0; i < OI_END; ++i )
	{
		for ( m_iter = m_listObj[i].begin(); m_iter != m_listObj[i].end(); ++m_iter )
		{
			(*m_iter)->Render();
		}
	}*/
	for ( _UINT i = 0; i < m_vecTile.size(); ++i )
	{
		m_vecTile[i]->Render();
	}

	for ( m_iter = m_listNotSort.begin(); m_iter != m_listNotSort.end(); ++m_iter )
	{
		(*m_iter)->Render();
	}

	m_listSort.sort( CYSort() );
	for ( m_iter = m_listSort.begin(); m_iter != m_listSort.end(); )
	{
		if ( (*m_iter) == NULL )
		{
			++m_iter;
			continue;
		}
		
		if ( (PCHARACTER(*m_iter)->GetDead() == true) || ((*m_iter)->GetDecay() == true))
		{
			m_iter = m_listSort.erase( m_iter );
		}
		else
		{
			(*m_iter)->Render();
			++m_iter;
		}
	}
		
	for ( m_iter = m_listUI.begin(); m_iter != m_listUI.end(); ++m_iter )
	{
		(*m_iter)->Render();
	}

	m_pMouse->Render();
}

CObj* CObjStorage::GetPlayer()
{
	return *( m_listObj[OI_PLAYER].begin() );
}

CObj* CObjStorage::GetMouse()
{
	//return *( m_listUI[0].begin() );
	return m_pMouse;
}

CObj* CObjStorage::GetBackGround()
{	
	return *( m_listObj[OI_BACKGROUND].begin() );
}	

void CObjStorage::Tile_Init(_UINT ix, _UINT iy)
{
	if ( m_vecTile.empty() == true ) 
	{
 		for ( _UINT i = 0; i < ix; ++i )
		{
			for ( _UINT j = 0; j < iy; ++j )
			{
				POINT pt = { i, j };
				m_vecTile.push_back( CObjFactory<CTile>::CreateObj(pt) );
			}
		}
	}
}

void CObjStorage::Tile_Progress(_BOOL bEdit)
{
	for ( _UINT i = 0; i < m_vecTile.size(); ++i )
	{
		PTILE(m_vecTile[i])->SetEdit( bEdit );
		m_vecTile[i]->Progress();
	}
}

void CObjStorage::Tile_Render()
{
	/*for ( _UINT i = 0; i < m_vecTile.size(); ++i )
	{
		m_vecTile[i]->Render();
	}*/
}

void CObjStorage::Tile_Release()
{
	for ( _UINT i = 0; i < m_vecTile.size(); ++i )
	{
		delete m_vecTile[i];
		m_vecTile[i] = NULL;
	}
	m_vecTile.clear();
}

list<CObj*>* CObjStorage::GetObjList()
{
	return m_listObj;
}

list<CObj*>* CObjStorage::GetObjList(OBJ_ID ID)
{
	return &( m_listObj[ID] );
}

list<CObj*>* CObjStorage::GetSortList()
{
	return &m_listSort;
}

vector<CObj*>* CObjStorage::GetTileVec()
{
	return &m_vecTile;
}

void CObjStorage::Release()
{
	for ( _UINT i = 0; i < OI_END; ++i )
	{
		for ( m_iter = m_listObj[i].begin(); m_iter != m_listObj[i].end(); ++m_iter )
		{
			delete (*m_iter);
			(*m_iter) = NULL;
		}
		m_listObj[i].clear();
	}

	/*for ( m_iter = m_listSort.begin(); m_iter != m_listSort.end(); ++m_iter )
	{
		delete (*m_iter);
		(*m_iter) = NULL;
	}
	m_listSort.clear();

	for ( m_iter = m_listNotSort.begin(); m_iter != m_listNotSort.end(); ++m_iter )
	{
		delete (*m_iter);
		(*m_iter) = NULL;
	}
	m_listNotSort.clear();*/

	for ( m_iter = m_listUI.begin(); m_iter != m_listUI.end(); ++m_iter )
	{
		delete (*m_iter);
	}
	
	delete m_pMouse;
	m_pMouse = NULL;
}