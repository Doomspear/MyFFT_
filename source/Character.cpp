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
	//비어있다면 나간다
	if ( m_listBestTile.empty() == true )
		return;

	//처음 요소의 타일 위치를 받아오고
	list<POBJ>::iterator it;

	it			= m_listBestTile.begin();
	m_ptDest	= (*it)->GetIndexPt();
	
	//이동가능으로
	m_bMove = true;
	
	//한칸 이동했다면
	if ( m_pt.x == m_ptDest.x && m_pt.y == m_ptDest.y )
	{
		//리스트에서 날려버리고
		/*m_pt.x = (*it)->GetIndexPt().x;
		m_pt.y = (*it)->GetIndexPt().y;*/

		it = m_listBestTile.erase( it );

		//반복자가 마지막까지 왔다면
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
			//더블클릭인가
			if ( CKeyChecker::GetInst()->CheckDbClick() == true )
			{
				//그럼 선택
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
		//틱 수정 요망
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
			//모션을 하나로 셋팅해서 그거만 나오게
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
	//현재 위치를 임시변수에 과거 위치로 저장
	POINT	ptPast = { m_pt.x, m_pt.y };

	//현재 위치에 이동할 방향 위치를 일단 더함
	m_pt.x += ptDir.x;
	m_pt.y += ptDir.y;
	
	//타일 인덱스를 계산하고
	_INT iIndex = m_pt.x * AMOUNTY + m_pt.y;
		
	//인덱스가 예외이면 예외처리 (여기 성능향상을 위해 계산 순서를 바꿀 필요 있음 일단 나중에 손댐)
	//벡터 인덱스를 벗어났다면
	if ( iIndex < 0 || iIndex > AMOUNTX * AMOUNTY - 1 )
	{
		m_pt.x -= ptDir.x;
		m_pt.y -= ptDir.y;
		return;
	}

	//가려는 곳이 이동불가 지역이라면
	if( PTILE((*_GETINST( CObjStorage )->GetTileVec())[iIndex])->GetStatic() == true )
	{
		m_pt.x -= ptDir.x;
		m_pt.y -= ptDir.y;
		return;
	}	
	
	//이건 뭐지
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
	
	//과거 좌표
	D3DXVECTOR3 vPast = D3DXVECTOR3( (BACKBUFSIZEX >> 1) + m_fDegree / 2.0f * int(ptPast.y - ptPast.x)
								   , (BACKBUFSIZEY >> 3) + m_fDegree / 2.0f * int(ptPast.y + ptPast.x)
								   , 0.0f );
	
	//현재 좌표
	D3DXVECTOR3 vNow = D3DXVECTOR3( (BACKBUFSIZEX >> 1) + m_fDegree / 2.0f * int(m_pt.y - m_pt.x)
								  , (BACKBUFSIZEY >> 3) + m_fDegree / 2.0f * int(m_pt.y + m_pt.x)
								  , 0.0f );

	//과거에서 현재를 뺀 만큼 스크롤을 적용
	SetScroll( vPast - vNow );
}

void CCharacter::CheckDir(DIRECTION_ID DI, _BOOL bReverse)
{
	//파라미터로 받은 바라봐야 할 방향과 현재 바라보는 방향이 같다면 
	if ( m_dwDir == DI && m_bReverse == bReverse )
	{
		switch ( DI )
		{
		case DI_LEFT:
			if ( m_bReverse == false )
			{
				//이동한다 
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
		//같지 않다면 같게 만든다
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





