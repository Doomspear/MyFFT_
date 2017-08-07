#include "StdAfx.h"
#include "AstarHandler.h"
#include "Includes.h"

CAstarHandler* CAstarHandler::m_pInst = NULL;

CAstarHandler::CAstarHandler(void)
: m_pvecPTile	(NULL)
, m_pUser		(NULL)
, m_pStartTile	(NULL)
, m_pDestTile	(NULL)
, m_iAmount		(0)
{
	
}

CAstarHandler::~CAstarHandler(void)
{
	m_listTileBest.clear();
	ClearTemp();
	ClearClose();
	ClearOpen();
	ClearBest();
}

void CAstarHandler::Progress()
{
}

void CAstarHandler::SetUser(POBJ pUser)
{
	m_pUser = pUser;
}

void CAstarHandler::SetVecTile(vector<POBJ>* pvec)
{
	m_pvecPTile	= pvec;
}

void CAstarHandler::AstarStart(POBJ pUser, POBJ pStartTile, POBJ pDestTile)
{
	if ( pStartTile == pDestTile )
		return;
		
	PCHARACTER( pUser )->ClearTileList();
	m_listTileBest.clear();
	ClearTemp();
	ClearClose();
	ClearOpen();
	ClearBest();
			
	//초기설정 (이부분을 손대야 함)
	SetUser( pUser );
	SetVecTile( _GETINST( CObjStorage )->GetTileVec() );
	m_pStartTile				= pStartTile;
	m_pDestTile					= pDestTile;

	//추적 AstarNode 셋팅
	m_Tracker.m_pTile			= m_pStartTile;
	m_Tracker.m_pDestination	= m_pDestTile;
	m_Tracker.m_pParent			= NULL;
	m_Tracker.CalculateCost();

	CheckTracker();
}

void CAstarHandler::AstarStart(POBJ pUser, POBJ pTarget)
{
	_INT iStartIndex	= pUser->GetIndexPt().x * AMOUNTY + pUser->GetIndexPt().y;

	_INT iDestIndex		= pTarget->GetIndexPt().x * AMOUNTY + pTarget->GetIndexPt().y;

	if ( iStartIndex == iDestIndex )
		return;
		
	PCHARACTER( pUser )->ClearTileList();
	
	m_listTileBest.clear();
	ClearTemp();
	ClearClose();
	ClearOpen();
	ClearBest();
			
	//초기설정 (이부분을 손대야 함)
	SetUser( pUser );
	SetVecTile( _GETINST( CObjStorage )->GetTileVec() );

	m_pStartTile				= (*_GETINST(CObjStorage)->GetTileVec())[iStartIndex];
	m_pDestTile					= (*_GETINST(CObjStorage)->GetTileVec())[iDestIndex];

	//추적 AstarNode 셋팅
	m_Tracker.m_pTile			= m_pStartTile;
	m_Tracker.m_pDestination	= m_pDestTile;
	m_Tracker.m_pParent			= NULL;
	m_Tracker.CalculateCost();
	
	CheckTracker();
}

list< POBJ >* CAstarHandler::GetBest()
{
	return &m_listTileBest;
}

PASTARNODE CAstarHandler::CreateNode(POBJ pTile, POBJ pParent, POBJ pDest)
{
	PASTARNODE astNode = new ASTARNODE;

	astNode->m_pTile		= pTile;
	astNode->m_pParent		= pParent;
	astNode->m_pDestination	= pDest;
	astNode->CalculateCost();

	return astNode;
}

void CAstarHandler::CheckTracker()
{
	//현재 Tracker가 위치한 타일(부모타일)의 인덱스를 받아놓음

	_INT iIndex = PTILE(m_Tracker.m_pTile)->GetIndexPt().x
				* AMOUNTY 
				+ PTILE(m_Tracker.m_pTile)->GetIndexPt().y;

	PTILE(m_Tracker.m_pTile)->SetClosed();
	
	//위에 붙지 않았을 때
	//↑
	if ( (iIndex - AMOUNTY) >= 0 )
	{
		if ( PTILE((*m_pvecPTile)[iIndex - AMOUNTY])->GetStatic() == false )
		{
			if ( PTILE((*m_pvecPTile)[iIndex - AMOUNTY])->GetClosed() == false )
			{
				PTILE((*m_pvecPTile)[iIndex - AMOUNTY])->SetClosed();
				m_listAstTemp.push_back( CreateNode((*m_pvecPTile)[iIndex - AMOUNTY], m_Tracker.m_pTile, m_pDestTile) );
			}
		}
	}
	
	//위에도 붙지 않고 왼쪽 벽에도 붙지 않았을 때
	if ( ((iIndex - AMOUNTY) >= 0) && (iIndex % AMOUNTY != AMOUNTY - 1) )
	{
		//↗
		if ( unsigned(iIndex - (AMOUNTY + 1)) < m_pvecPTile->size() )
		{
			if ( PTILE((*m_pvecPTile)[iIndex - AMOUNTY + 1])->GetStatic() == false )
			{
				if ( PTILE((*m_pvecPTile)[iIndex - AMOUNTY + 1])->GetClosed() == false )
				{
					PTILE((*m_pvecPTile)[iIndex - AMOUNTY + 1])->SetClosed();
					m_listAstTemp.push_back( CreateNode((*m_pvecPTile)[iIndex - AMOUNTY + 1], m_Tracker.m_pTile, m_pDestTile) );
				}
			}
		}
	}
	
	//왼쪽 벽에 붙지 않았을 때
	if ( iIndex%AMOUNTY != AMOUNTY - 1 )
	{
		//→
		if ( unsigned(iIndex + 1) < m_pvecPTile->size() )
		{
			if ( PTILE((*m_pvecPTile)[iIndex + 1])->GetStatic() == false )
			{
				if ( PTILE((*m_pvecPTile)[iIndex + 1])->GetClosed() == false )
				{
					PTILE((*m_pvecPTile)[iIndex + 1])->SetClosed();
					m_listAstTemp.push_back( CreateNode((*m_pvecPTile)[iIndex + 1], m_Tracker.m_pTile, m_pDestTile) );
				}
			}
		}
	}

	//왼쪽 벽에도 붙지 않고 아래에도 붙지 않았을 때
	if ( (iIndex%AMOUNTY != AMOUNTY - 1) && (unsigned(iIndex + AMOUNTY) < m_pvecPTile->size()) )
	{
		//↘
		if ( unsigned(iIndex + AMOUNTY + 1) < m_pvecPTile->size() )
		{
			if ( PTILE((*m_pvecPTile)[iIndex + AMOUNTY + 1])->GetStatic() == false )
			{
				if ( PTILE((*m_pvecPTile)[iIndex + AMOUNTY + 1])->GetClosed() == false )
				{
					PTILE((*m_pvecPTile)[iIndex + AMOUNTY + 1])->SetClosed();
					m_listAstTemp.push_back( CreateNode((*m_pvecPTile)[iIndex + AMOUNTY + 1], m_Tracker.m_pTile, m_pDestTile) );
				}
			}
		}
	}

	//아래에 붙지 않았을 때
	//↓
	if ( unsigned(iIndex + AMOUNTY) < m_pvecPTile->size() )
	{
		if ( PTILE((*m_pvecPTile)[iIndex + AMOUNTY])->GetStatic() == false )
		{
			if ( PTILE((*m_pvecPTile)[iIndex + AMOUNTY])->GetClosed() == false )
			{
				PTILE((*m_pvecPTile)[iIndex + AMOUNTY])->SetClosed();
				m_listAstTemp.push_back( CreateNode((*m_pvecPTile)[iIndex + AMOUNTY], m_Tracker.m_pTile, m_pDestTile) );
			}
		}
	}

	//아래에도 붙지 않고 왼쪽에도 붙지 않았을 때
	
	//여기 이상
	
	if ( (unsigned(iIndex + AMOUNTY) < m_pvecPTile->size()) && (iIndex % AMOUNTY) != 0 )
	{
		//↙
		if ( unsigned(iIndex + AMOUNTY - 1) < m_pvecPTile->size() )
		{
			if ( PTILE((*m_pvecPTile)[iIndex + AMOUNTY - 1])->GetStatic() == false )
			{
				if ( PTILE((*m_pvecPTile)[iIndex + AMOUNTY - 1])->GetClosed() == false )
				{
					PTILE((*m_pvecPTile)[iIndex + AMOUNTY - 1])->SetClosed();
					m_listAstTemp.push_back( CreateNode((*m_pvecPTile)[iIndex + AMOUNTY - 1], m_Tracker.m_pTile, m_pDestTile) );
				}
			}
		}
	}

	//왼에 붙지 않았을 때
	//←
	if ( (iIndex % AMOUNTY) != 0 )
	{
		if ( (iIndex - 1) >= 0 )
		{	
			if ( PTILE((*m_pvecPTile)[iIndex - 1])->GetStatic() == false )
			{
				if ( PTILE((*m_pvecPTile)[iIndex - 1])->GetClosed() == false )
				{
					PTILE((*m_pvecPTile)[iIndex - 1])->SetClosed();
					m_listAstTemp.push_back( CreateNode((*m_pvecPTile)[iIndex - 1], m_Tracker.m_pTile, m_pDestTile) );
				}
			}
		}
	}

	//왼쪽에도 붙지 않고 위에도 붙지 않았을 때
	if ( (iIndex % AMOUNTY) != 0 && (iIndex - AMOUNTY) != 0 )
	{
		//↖ 
		if ( (iIndex - AMOUNTY - 1) >= 0 )
		{
			if ( PTILE((*m_pvecPTile)[iIndex - AMOUNTY - 1])->GetStatic() == false )
			{
				if ( PTILE((*m_pvecPTile)[iIndex - AMOUNTY - 1])->GetClosed() == false )
				{
					PTILE((*m_pvecPTile)[iIndex - AMOUNTY - 1])->SetClosed();
					m_listAstTemp.push_back( CreateNode((*m_pvecPTile)[iIndex - AMOUNTY - 1], m_Tracker.m_pTile, m_pDestTile) );
				}
			}
		}
	}

	//만약 위에서 타일을 가져 왔다면
	if ( false == m_listAstTemp.empty() )
	{
		//sorting 성공
		m_listAstTemp.sort( CCostSort() );
		
		it = m_listAstTemp.begin();
		m_Tracker = (*(*it));
		
		//PTILE((*it)->m_pTile)->SetTileID(TI_CLOSE);
		//sort된 가장 작은것을 close에 넣고
		m_listAstClose.push_back( (*it) );

		//templist에서 가장 작은것중 맨 앞을 지워버림
		m_listAstTemp.erase( it );

		//나머지는 open에 넣음
		for ( it = m_listAstTemp.begin(); it != m_listAstTemp.end(); ++it )
		{
			//PTILE((*it)->m_pTile)->SetTileID(TI_OPEN);
			m_listAstOpen.push_back( (*it) );
		}
		
		//템프리스트 없애버리고
		m_listAstTemp.clear();
	}
	else
	//타일을 가져오지 못했다면
	{
		if ( m_listAstOpen.empty() )
		{
			//Release();
			for ( _UINT i = 0; i < (*m_pvecPTile).size(); ++i )
			{
				PTILE( (*m_pvecPTile)[i] )->SetOpen();
			}
			return;
		}
		m_listAstOpen.sort( CCostSort() );	
		it = m_listAstOpen.begin();
		m_Tracker = (*(*it));

		m_listAstClose.push_back( (*it) );

		m_listAstOpen.erase( it );
	}

	if ( m_Tracker.m_pTile != m_pDestTile )
	{
		//트랙커가 타일에 도착하지 못했다면 재귀호출
		CheckTracker();
	}
	//트랙커가 타일에 도착하면 플레이어에게 보냄
	else
	{
		//closelist의 마지막놈 부터 부모찾기
		m_listAstClose.reverse();
		it = m_listAstClose.begin();

		m_listTileBest.push_back( (*it)->m_pTile );
		m_listTileBest.push_back( (*it)->m_pParent );

		POBJ pTempParent = (*it)->m_pParent;

		for( ; it != m_listAstClose.end(); ++it )
		{
			if ( (*it)->m_pTile == pTempParent )
			{
				pTempParent = (*it)->m_pParent;
				m_listTileBest.push_back( (*it)->m_pParent );
			}
		}

		list<POBJ>::iterator iter;
		iter = m_listTileBest.end();
		m_listTileBest.erase( --iter );
		m_listTileBest.reverse();

		m_listTileBest.erase( --m_listTileBest.end() ) ;
		
		//베스트타일을 셋팅함
		PCHARACTER(m_pUser)->SetTileList( m_listTileBest );

		for ( _UINT i = 0; i < (*m_pvecPTile).size(); ++i )
		{
			PTILE( (*m_pvecPTile)[i] )->SetOpen();
			//PTILE( (*m_pvecPTile)[i] )->SetUnLocomo();
		}
		ZeroMemory( &m_Tracker, 0 );

		/*ClearClose();
		ClearTemp();
		ClearOpen();
		ClearBest();*/
	}
}

void CAstarHandler::ClearTemp()
{
	for ( it = m_listAstTemp.begin(); it != m_listAstTemp.end(); ++it )
	{
		delete (*it);
		(*it) = NULL;
	}
	m_listAstTemp.clear();
}

void CAstarHandler::ClearClose()
{
	for ( it = m_listAstClose.begin(); it != m_listAstClose.end(); ++it )
	{
		delete (*it);
		(*it) = NULL;
	}
	m_listAstClose.clear();
}

void CAstarHandler::ClearOpen()
{
	for ( it = m_listAstOpen.begin(); it != m_listAstOpen.end(); ++it )
	{
		delete (*it);
		(*it) = NULL;
	}
	m_listAstOpen.clear();
}

void CAstarHandler::ClearBest()
{
	for ( it = m_listAstBest.begin(); it != m_listAstBest.end(); ++it )
	{
		delete (*it);
		(*it) = NULL;
	}
	m_listAstBest.clear();
}

void CAstarHandler::Release()
{
	m_listTileBest.clear();
	ClearTemp();
	ClearClose();
	ClearOpen();
	ClearBest();
}