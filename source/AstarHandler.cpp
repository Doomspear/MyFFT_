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
			
	//�ʱ⼳�� (�̺κ��� �մ�� ��)
	SetUser( pUser );
	SetVecTile( _GETINST( CObjStorage )->GetTileVec() );
	m_pStartTile				= pStartTile;
	m_pDestTile					= pDestTile;

	//���� AstarNode ����
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
			
	//�ʱ⼳�� (�̺κ��� �մ�� ��)
	SetUser( pUser );
	SetVecTile( _GETINST( CObjStorage )->GetTileVec() );

	m_pStartTile				= (*_GETINST(CObjStorage)->GetTileVec())[iStartIndex];
	m_pDestTile					= (*_GETINST(CObjStorage)->GetTileVec())[iDestIndex];

	//���� AstarNode ����
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
	//���� Tracker�� ��ġ�� Ÿ��(�θ�Ÿ��)�� �ε����� �޾Ƴ���

	_INT iIndex = PTILE(m_Tracker.m_pTile)->GetIndexPt().x
				* AMOUNTY 
				+ PTILE(m_Tracker.m_pTile)->GetIndexPt().y;

	PTILE(m_Tracker.m_pTile)->SetClosed();
	
	//���� ���� �ʾ��� ��
	//��
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
	
	//������ ���� �ʰ� ���� ������ ���� �ʾ��� ��
	if ( ((iIndex - AMOUNTY) >= 0) && (iIndex % AMOUNTY != AMOUNTY - 1) )
	{
		//��
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
	
	//���� ���� ���� �ʾ��� ��
	if ( iIndex%AMOUNTY != AMOUNTY - 1 )
	{
		//��
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

	//���� ������ ���� �ʰ� �Ʒ����� ���� �ʾ��� ��
	if ( (iIndex%AMOUNTY != AMOUNTY - 1) && (unsigned(iIndex + AMOUNTY) < m_pvecPTile->size()) )
	{
		//��
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

	//�Ʒ��� ���� �ʾ��� ��
	//��
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

	//�Ʒ����� ���� �ʰ� ���ʿ��� ���� �ʾ��� ��
	
	//���� �̻�
	
	if ( (unsigned(iIndex + AMOUNTY) < m_pvecPTile->size()) && (iIndex % AMOUNTY) != 0 )
	{
		//��
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

	//�޿� ���� �ʾ��� ��
	//��
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

	//���ʿ��� ���� �ʰ� ������ ���� �ʾ��� ��
	if ( (iIndex % AMOUNTY) != 0 && (iIndex - AMOUNTY) != 0 )
	{
		//�� 
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

	//���� ������ Ÿ���� ���� �Դٸ�
	if ( false == m_listAstTemp.empty() )
	{
		//sorting ����
		m_listAstTemp.sort( CCostSort() );
		
		it = m_listAstTemp.begin();
		m_Tracker = (*(*it));
		
		//PTILE((*it)->m_pTile)->SetTileID(TI_CLOSE);
		//sort�� ���� �������� close�� �ְ�
		m_listAstClose.push_back( (*it) );

		//templist���� ���� �������� �� ���� ��������
		m_listAstTemp.erase( it );

		//�������� open�� ����
		for ( it = m_listAstTemp.begin(); it != m_listAstTemp.end(); ++it )
		{
			//PTILE((*it)->m_pTile)->SetTileID(TI_OPEN);
			m_listAstOpen.push_back( (*it) );
		}
		
		//��������Ʈ ���ֹ�����
		m_listAstTemp.clear();
	}
	else
	//Ÿ���� �������� ���ߴٸ�
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
		//Ʈ��Ŀ�� Ÿ�Ͽ� �������� ���ߴٸ� ���ȣ��
		CheckTracker();
	}
	//Ʈ��Ŀ�� Ÿ�Ͽ� �����ϸ� �÷��̾�� ����
	else
	{
		//closelist�� �������� ���� �θ�ã��
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
		
		//����ƮŸ���� ������
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