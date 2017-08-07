#include "StdAfx.h"
#include "Character.h"
#include "Includes.h"

CCharacter::CCharacter(void)
{
}

CCharacter::~CCharacter(void)
{
}

//for monster
void CCharacter::CheckState()
{
	if ( m_bMove == false )
	{
		DelFlag( ST_WALK );
		DelFlag( ST_RUN );
		AddFlag( ST_STAND );
	}
	else
	{
		AddFlag( ST_WALK );
		DelFlag( ST_RUN );
		DelFlag( ST_STAND );
	}
	MotionSet();
}

void CCharacter::MotionSet()
{
	if ( m_dwState & ST_STAND )
		m_dwMidID = MI_STAND;
								
	if ( m_dwState & ST_WALK )
		m_dwMidID = MI_WALK_UNARMED;
}

void CCharacter::Die()
{
	CObj* Corpse = new CCorpse( this );
	Corpse->Init();

	list<CObj*>*	plistCorpse = _GETINST(CObjStorage)->GetObjList( OI_CORPSE );
	plistCorpse->push_back( Corpse );

	plistCorpse = _GETINST(CObjStorage)->GetSortList();
	plistCorpse->push_back( Corpse );

	m_bDead	= true;
}

void CCharacter::BestMove()
{
	//����ִٸ� ������
	if ( m_listBestTile.empty() == true )
		return;

	//ó�� ����� Ÿ�� ��ġ�� �޾ƿ���
	list<POBJ>::iterator it;

	it			= m_listBestTile.begin();
	m_ptDest	= (*it)->GetIndexPt();
	
	//�̵���������
	m_bMove = true;
	
	//��ĭ �̵��ߴٸ�
	if ( m_pt.x == m_ptDest.x && m_pt.y == m_ptDest.y )
	{
		//����Ʈ���� ����������
		/*m_pt.x = (*it)->GetIndexPt().x;
		m_pt.y = (*it)->GetIndexPt().y;*/

		it = m_listBestTile.erase( it );

		//�ݺ��ڰ� ���������� �Դٸ�
		if ( it == m_listBestTile.end() )
		{
			m_listBestTile.clear();
			return;
		}
		else
		{
			m_ptDest	= (*it)->GetIndexPt();
			m_bMove		= true;
		}
	}
}

void CCharacter::MoveToDest()
{
	if ( m_bMove == true )
	{
		if ( m_pt.x != m_ptDest.x || m_pt.y != m_ptDest.y )
		{
			POINT pt;
			pt.x = m_ptDest.x - m_pt.x;
			pt.y = m_ptDest.y - m_pt.y;

			TurnToDest( pt );
			if ( m_dwTexID != TI_WOMAN )
			{
				m_dwMidID = MI_WALK_UNARMED;
			}

			m_pt.x = m_ptDest.x;
			m_pt.y = m_ptDest.y;
			
		}
		else
		{
			m_bMove = false;
			return;
		}
	}
}

void CCharacter::TurnToDest(POINT pt)
{
	if ( (pt.x == PT_LEFT.x) && (pt.y == PT_LEFT.y) )
	{
		m_dwDir		= DI_LEFT;
		m_bReverse	= false;
	}
	else if ( (pt.x == PT_RIGHT.x) && (pt.y == PT_RIGHT.y) )
	{
		m_dwDir		= DI_LEFT;
		m_bReverse	= true;
	}		
	else if ( (pt.x == PT_UP.x) && (pt.y == PT_UP.y) )
	{
		m_dwDir		= DI_UP;
		m_bReverse	= false;
	}
	else if ( (pt.x == PT_DOWN.x) && (pt.y == PT_DOWN.y) )
	{
		m_dwDir		= DI_DOWN;
		m_bReverse	= false;
	}
	else if ( (pt.x == PT_DOWNLEFT.x) && (pt.y == PT_DOWNLEFT.y) )
	{
		m_dwDir		= DI_DOWNLEFT;
		m_bReverse	= false;
	}
	else if ( (pt.x == PT_DOWNRIGHT.x) && (pt.y == PT_DOWNRIGHT.y) )
	{
		m_dwDir		= DI_DOWNLEFT;
		m_bReverse	= true;
	}
	else if ( (pt.x == PT_UPLEFT.x) && (pt.y == PT_UPLEFT.y) )
	{
		m_dwDir		= DI_UPLEFT;
		m_bReverse	= false;
	}
	else if ( (pt.x == PT_UPRIGHT.x) && (pt.y == PT_UPRIGHT.y) )
	{
		m_dwDir		= DI_UPLEFT;
		m_bReverse	= true;
	}
}


void CCharacter::CallAstar()
{
	if ( m_listBestTile.empty() == false )
		return;
	_GETINST( CAstarHandler )->AstarStart( this, m_pTarget/*_GETINST( CObjStorage )->GetPlayer()*/ );
}

void CCharacter::SetTileList(list<POBJ> listBestTile)
{
	m_listBestTile = listBestTile;
}

void CCharacter::ClearTileList()
{
	m_listBestTile.clear();
}

void CCharacter::FrameMove()
{
	if ( m_dwMidIDPast != m_dwMidID )
	{
		m_dwMidIDPast = m_dwMidID;
		m_iFrame = 0;
	}

	if ( m_dwTime + /*m_fSpeed*/m_dwTick < GetTickCount() )
	{
		m_dwTime = GetTickCount();
		++m_iFrame;
	}

	if ( m_iFrame == (*m_pvecTex)[m_dwTexID][m_dwMidID][m_dwDir].size() )
	{
		m_iFrame = 0;	
	}
}

void CCharacter::Select()
{
	m_iSelect = 0;
}

void CCharacter::DeSelect()
{
	m_iSelect = 255;
}

void CCharacter::SelectCheck()
{
	if ( _GETINST( CObjStorage )->GetPlayer()->GetTarget() != this )
		DeSelect();
	
	if ( _GETINST( CObjStorage )->GetPlayer()->GetState() & ST_WAR )
	{
		POINT pt = { static_cast<long>( _GETINST( CObjStorage )->GetMouse()->GetvPos().x )
				   , static_cast<long>( _GETINST( CObjStorage )->GetMouse()->GetvPos().y ) };
		if ( PtInRect( &m_rcColi, pt ) )
		{
			//����Ŭ���ΰ�
			if ( CKeyChecker::GetInst()->CheckDbClick() == true )
			{
				//�׷� ����
				Select();
				_GETINST( CObjStorage )->GetPlayer()->SetTarget( this );
				_GETINST( CObjStorage )->GetPlayer()->SetAction( 3 );
			}
		}
	}
	else
	{
		DeSelect();
		_GETINST( CObjStorage )->GetPlayer()->ClearTarget();
	}
}

_BOOL CCharacter::CheckTargetDistance()
{
	POINT ptTarget	= m_pTarget->GetIndexPt();
	POINT ptDistance = { ptTarget.x - m_pt.x
					   , ptTarget.y - m_pt.y };
	
	if ( abs( ptDistance.x )+ abs( ptDistance.y ) <= 1 )
	{
		TurnToDest( ptDistance );
		return true;
	}
	else if ( abs( ptDistance.x ) == 1 && abs( ptDistance.y ) == 1 )
	{
		TurnToDest( ptDistance );
		return true;
	}
	else
	{
		return false;
	}
}

void CCharacter::Attack()
{
	if ( m_pTarget == NULL )
		return;

	if ( m_pTarget->GetHP() <= 0 )
	{
		m_pTarget = NULL;
		return;
	}

	if ( m_dwTexID != TI_WOMAN )
	{
		//ƽ ���� ���
		if ( m_dwAstarTime + 100 < GetTickCount() )
		{
			m_dwAstarTime = GetTickCount();
			if ( CheckTargetNeer() == false )
			{
				CallAstar();
			}
		}
	}
		
	if ( m_iAction == 0 )
	{
		if ( true == CheckTargetDistance() )
		{
			//����� �ϳ��� �����ؼ� �װŸ� ������
			if ( m_bAttMotion == false )
			{
				if ( m_dwTexID == TI_WOMAN )
				{
					switch ( rand()%2 )
					{
					case 0:
						m_dwSavedMotion = MI_ATTACK_TWOHAND_WIDE;
						break;
					case 1:
						m_dwSavedMotion = MI_ATTACK_TWOHAND_DOWN;
						break;
					}
				}
				else if ( m_dwTexID == TI_DRAGON )
				{
					switch ( rand()%2 )
					{
					case 0:
						m_dwSavedMotion = MI_ATTACK1;
						break;
					case 1:
						m_dwSavedMotion = MI_MISC;
						break;
					}
				}
				else
				{
					m_dwSavedMotion = MI_ATTACK1;
				}
				m_bAttMotion = true;
			}

			m_dwMidID = m_dwSavedMotion;
			
			if ( m_iFrame == (*m_pvecTex)[m_dwTexID][m_dwMidID][m_dwDir].size() - 1 )
			{
				m_bAttMotion = false;
				PCHARACTER( m_pTarget )->SetDamage( m_iATT );
				m_iAction = 3;
			}
		}
	}
	else
	{
		if ( m_dwAttTime + 1000 < GetTickCount() )
		{
			m_dwAttTime = GetTickCount();
			if ( m_iAction > 0 )
				--m_iAction;
		}
	}
}

void CCharacter::SetDamage(_INT iATT)
{
	//m_dwMidID = MI_TAKE_HIT;
	if ( m_dwTexID != TI_WOMAN )
	{
		if ( m_pTarget == NULL )
			m_pTarget	= _GETINST( CObjStorage )->GetPlayer();
		//m_iAction	= 0;
	}
	m_iHP -= (iATT - m_iAR);
}

void CCharacter::Move(POINT ptDir)
{
	//���� ��ġ�� �ӽú����� ���� ��ġ�� ����
	POINT	ptPast = { m_pt.x, m_pt.y };

	//���� ��ġ�� �̵��� ���� ��ġ�� �ϴ� ����
	m_pt.x += ptDir.x;
	m_pt.y += ptDir.y;
	
	//Ÿ�� �ε����� ����ϰ�
	_INT iIndex = m_pt.x * AMOUNTY + m_pt.y;
		
	//�ε����� �����̸� ����ó�� (���� ��������� ���� ��� ������ �ٲ� �ʿ� ���� �ϴ� ���߿� �մ�)
	//���� �ε����� ����ٸ�
	if ( iIndex < 0 || iIndex > AMOUNTX * AMOUNTY - 1 )
	{
		m_pt.x -= ptDir.x;
		m_pt.y -= ptDir.y;
		return;
	}

	//������ ���� �̵��Ұ� �����̶��
	if( PTILE((*_GETINST( CObjStorage )->GetTileVec())[iIndex])->GetStatic() == true )
	{
		m_pt.x -= ptDir.x;
		m_pt.y -= ptDir.y;
		return;
	}	
	
	//�̰� ����
	if ( iIndex < 0 || iIndex > (AMOUNTX * AMOUNTY) - 1 ) 
	{
		m_pt.x -= ptDir.x;
		m_pt.y -= ptDir.y;
		return;
	}
	else if ( m_pt.x < 0 || m_pt.y < 0 || m_pt.x >= AMOUNTX || m_pt.y >= AMOUNTX )
	{
		m_pt.x -= ptDir.x;
		m_pt.y -= ptDir.y;
		return;
	}
	
	//���� ��ǥ
	D3DXVECTOR3 vPast = D3DXVECTOR3( (BACKBUFSIZEX >> 1) + m_fDegree / 2.0f * int(ptPast.y - ptPast.x)
								   , (BACKBUFSIZEY >> 3) + m_fDegree / 2.0f * int(ptPast.y + ptPast.x)
								   , 0.0f );
	
	//���� ��ǥ
	D3DXVECTOR3 vNow = D3DXVECTOR3( (BACKBUFSIZEX >> 1) + m_fDegree / 2.0f * int(m_pt.y - m_pt.x)
								  , (BACKBUFSIZEY >> 3) + m_fDegree / 2.0f * int(m_pt.y + m_pt.x)
								  , 0.0f );

	//���ſ��� ���縦 �� ��ŭ ��ũ���� ����
	SetScroll( vPast - vNow );
}

void CCharacter::CheckDir(DIRECTION_ID DI, _BOOL bReverse)
{
	//�Ķ���ͷ� ���� �ٶ���� �� ����� ���� �ٶ󺸴� ������ ���ٸ� 
	if ( m_dwDir == DI && m_bReverse == bReverse )
	{
		switch ( DI )
		{
		case DI_LEFT:
			if ( m_bReverse == false )
			{
				//�̵��Ѵ� 
				Move( PT_LEFT );
			}
			else
			{
				Move( PT_RIGHT );
			}
			break;

		case DI_UPLEFT:
			if ( m_bReverse == false )
			{
				Move( PT_UPLEFT );
			}
			else
			{
				Move( PT_UPRIGHT );
			}
			break;

		case DI_DOWNLEFT:
			if ( m_bReverse == false )
			{
				Move( PT_DOWNLEFT );
			}
			else
			{
				Move( PT_DOWNRIGHT );
			}
			break;

		case DI_UP:
			Move( PT_UP );
			break;

		case DI_DOWN:
			Move( PT_DOWN );
			break;
		}
	}
	else	
	{	
		//���� �ʴٸ� ���� �����
		m_dwDir		= DI;
		m_bReverse	= bReverse;
	}		
}

_BOOL CCharacter::CheckTargetNeer()
{
	if ( m_pTarget == NULL )
		return false;

	POINT pt = m_pTarget->GetIndexPt();

	if ( m_pt.x == pt.x && m_pt.y == pt.y )
		return true;
	else if ( (m_pt.x + PT_LEFT.x == pt.x) && (m_pt.y + PT_LEFT.y) == pt.y )
		return true;
	else if ( (m_pt.x + PT_RIGHT.x == pt.x) && (m_pt.y + PT_RIGHT.y) == pt.y )
		return true;
	else if ( (m_pt.x + PT_UP.x == pt.x) && (m_pt.y + PT_UP.y) == pt.y )
		return true;
	else if ( (m_pt.x + PT_DOWN.x == pt.x) && (m_pt.y + PT_DOWN.y) == pt.y )
		return true;
	else if ( (m_pt.x + PT_DOWNLEFT.x == pt.x) && (m_pt.y + PT_DOWNLEFT.y) == pt.y )
		return true;
	else if ( (m_pt.x + PT_DOWNRIGHT.x == pt.x) && (m_pt.y + PT_DOWNRIGHT.y) == pt.y )
		return true;
	else if ( (m_pt.x + PT_UPLEFT.x == pt.x) && (m_pt.y + PT_UPLEFT.y) == pt.y )
		return true;
	else if ( (m_pt.x + PT_UPRIGHT.x == pt.x) && (m_pt.y + PT_UPRIGHT.y) == pt.y )
		return true;
	else
		return false;
}





