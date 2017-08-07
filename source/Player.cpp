#include "StdAfx.h"
#include "Player.h"
#include "Includes.h"

CPlayer::CPlayer(void)
{
	m_pt.x			= 5;
	m_pt.y			= 5;
}

CPlayer::CPlayer(_INT ix, _INT iy)
{
	m_pt.x			= ix;
	m_pt.y			= iy;
}

CPlayer::~CPlayer(void)
{
	Release();
}

void CPlayer::Init()
{	
	//from CObj
	m_pvecTex		= _GETINST( CTextureLoader )->GetTextureVector();
	D3DXMatrixIdentity( &m_matWorld );									//m_matWorld setting
	
	m_vCenter		= D3DXVECTOR3( sqrtf(m_fSizeX), m_fSizeY, 0.0f );
	
	MoveToIndex();														//m_vPos setting

	m_vLook			= D3DXVECTOR3( 1.0f, 0.0f, 0.0f );

	D3DXMatrixScaling( &m_matScale, 1.0f, 1.0f, 0.0f );					//m_matScale setting
	D3DXMatrixTranslation( &m_matTrans, m_vPos.x, m_vPos.y, 0.0f );		//m_matTras setting
	
	m_pCloth		= new ROBE( this );
	m_pCloth		->Init();

	m_pWeapon		= new HALBERD( this );
	m_pWeapon		->Init();

	m_pInven		= new INVENTORY( this );
	m_pInven		->Init();

	m_pRobe			= new ROBE( this );
	m_pRobe			->Init();

	PINVENTORY( m_pInven )->Insert( m_pRobe );
	
	_GETINST( CObjStorage )->SetInventoUI( m_pInven );

	/*PINVENTORY( m_pInven )->Insert( m_pCloth );
	PINVENTORY( m_pInven )->Insert( m_pWeapon );*/
	
	m_pTarget		= NULL;

	m_dwTexID		= TI_WOMAN;
	m_dwMidID		= MI_WALK_ARMED;
	m_dwMidIDPast	= m_dwMidID;
	m_dwDir			= DI_DOWNLEFT;
	
	SetTileIndex();														//m_iTileIndex setting
	//m_iDepth;

	m_dwState		= ST_STAND | ST_PEACE;

	m_iFrame		= 0;
	m_bReverse		= false;
	m_bDecay		= false;
	
	m_dwTime		= GetTickCount();
	m_dwTick		= 100;
	
	m_fSizeX		= 25.0f;
	m_fSizeY		= 65.0f;
	
	m_fSpeed		= 150.0f;
	m_fDegree		= 45.0f;
	
	m_iLocomotive	= 3;
	
	//for char stat
	m_iAction		= 0;

	m_iHP			= 300;
	m_iMP			= 100;	
	
	m_iSTR			= 100;
	m_iDEX			= 100;
	m_iINT			= 100;

	m_iATT			= 15;
	m_iAR			= 0;	

	m_iWeight		= 0;

	m_ptPast		= m_pt;
	SetColRect();														//m_rcColi setting;
 

	//from CCharacter
		//m_vecInven;
		//m_listBestTile;
	ZeroMemory( &m_vDest, sizeof(m_vDest) );	//m_vDest setting
	//m_ptDest;		
	m_iSelect		= 0;						//???

	m_dwMoveTime	= GetTickCount();
	m_dwAttTime		= GetTickCount();
	m_bMove			= false;
	m_bArmed		= true;
	m_bDead			= false;
	m_bAttMotion	= false;

	m_bPressed[BI_END];
	
	//private member
	m_bLocomo		= false;
	m_fAngleTemp	= 0.0f;						//temp
}

void CPlayer::Progress()
{
	CheckKey();

	//TurnMotion();
	
	PlayerMove();
		
	MoveToIndex();
	RevisionPos();
	SetDepthPos();

	CheckReverse();

	D3DXMatrixTranslation( &m_matTrans, m_vPos.x, m_vPos.y, m_vPos.z );
	m_matWorld = m_matScale * m_matTrans;

	SetColRect();

	//플레이어 클릭 체크
	POINT pt = { static_cast<long> ( _GETINST( CObjStorage )->GetMouse()->GetvPos().x )
			   , static_cast<long> ( _GETINST( CObjStorage )->GetMouse()->GetvPos().y ) }; 
	
	CheckState();

	Attack();

	FrameMove();
	
	if( m_pCloth != NULL )
	{
		m_pCloth->Progress();
	}

	if ( m_pWeapon != NULL )
	{
		m_pWeapon->Progress();
	}
	
	m_ptPast = m_pt;
}

void CPlayer::Render()
{	
	m_vCenter = (*m_pvecTex)[m_dwTexID][m_dwMidID][m_dwDir][m_iFrame]->vCen;

	//shadow
	D3DXMatrixRotationZ( &m_matRotateZ, D3DXToRadian( 15 ) );
	m_matWorld = m_matScale * m_matRotateZ * m_matTrans;
	_GETINST( CDevice )->GetSprite()->SetTransform( &m_matWorld );
	_GETINST( CDevice )->GetSprite()->Draw( (*m_pvecTex)[m_dwTexID][m_dwMidID][m_dwDir][m_iFrame]->pTex, NULL, &m_vCenter, NULL, D3DCOLOR_ARGB(100, 0, 0, 0) );

	m_matWorld = m_matScale * m_matTrans;
	_GETINST( CDevice )->GetSprite()->SetTransform( &m_matWorld );
	_GETINST( CDevice )->GetSprite()->Draw( (*m_pvecTex)[m_dwTexID][m_dwMidID][m_dwDir][m_iFrame]->pTex, NULL, &m_vCenter, NULL, D3DCOLOR_ARGB(255, 255, 255, 255) );

	if( m_pCloth != NULL )
	{
		m_pCloth->Render();
	}

	if ( m_pWeapon != NULL )
	{
		m_pWeapon->Render();
	}

	//DrawPos();
	//DrawColiBox();
	//DrawDepth();
	DrawHP();
}

void CPlayer::TurnMotion()
{
	_DWORD dwKey = _GETINST( CKeyChecker )->GetKeyState();
	
	if ( dwKey & KEY_LEFT )
	{
		m_dwDir		= DI_LEFT;
		Move( PT_LEFT );
		m_bReverse	= false;
	}
	
	if ( dwKey & KEY_RIGHT )
	{
		m_dwDir		= DI_LEFT;
		Move( PT_RIGHT );
		m_bReverse	= true;
	}

	if ( dwKey & KEY_UP )
	{
		m_dwDir		= DI_UP;
		Move( PT_UP );
		m_bReverse	= false;
	}
	if ( dwKey & KEY_DOWN )
	{
		m_dwDir		= DI_DOWN;	
		Move( PT_DOWN );
		m_bReverse	= false;
	}

	if ( (dwKey & KEY_UP) && (dwKey & KEY_LEFT) )
	{
		m_dwDir		= DI_UPLEFT;
		Move( PT_UPLEFT );
		m_bReverse	= false;
	}

	if ( (dwKey & KEY_UP) && (dwKey & KEY_RIGHT) )
	{
		m_dwDir		= DI_UPLEFT;
		Move( PT_UPRIGHT );
		m_bReverse	= true;
	}
	
	if ( (dwKey & KEY_DOWN) && (dwKey & KEY_LEFT) )
	{
		m_dwDir		= DI_DOWNLEFT;
		Move( PT_DOWNLEFT );
		m_bReverse	= false;
	}

	if ( (dwKey & KEY_DOWN) && (dwKey & KEY_RIGHT) )
	{
		m_dwDir		= DI_DOWNLEFT;
		Move( PT_DOWNRIGHT );
		m_bReverse	= true; 
	}
}

void CPlayer::PlayerMove()
{
	_DWORD dwKey			= _GETINST( CKeyChecker )->GetKeyState();
	
	//Move
	if ( (dwKey & KEY_RBUTTON) )
	{
		//스피드당 한번씩 이동
		if ( m_dwMoveTime + m_fSpeed < GetTickCount() )
		{
			m_dwMoveTime			= GetTickCount();
			
			//이동중으로
			m_bMove					= true;
	
			//마우스 위치를 잡아와서 그 위치에 따라 갈 방향을 결정하기 위해
			D3DXVECTOR3 vMousePos	= _GETINST( CObjStorage )->GetMouse()->GetvPos();
			D3DXVECTOR3	vTemp		= vMousePos - m_vPos;
			_FLOAT fLength			= D3DXVec3Length( &vTemp );
		
			//거리가 가까우면 걷고 멀면 뜀
			if ( fLength < 250 ) 
			{
				DelFlag( ST_STAND );
				DelFlag( ST_RUN );
				AddFlag( ST_WALK );
				m_fSpeed = 180;
				//m_fSpeed = 100;
			}
			else if ( fLength >= 250 )
			{
				DelFlag( ST_STAND );
				DelFlag( ST_WALK );
				AddFlag( ST_RUN );
				m_fSpeed = 100;
			}
			
			//마우스 각도 계산
			_FLOAT	fWidth			= fabs( vMousePos.x - WINSIZEX / 2 );
			_FLOAT	fHeight			= fabs( vMousePos.y - WINSIZEY / 2 );
			_FLOAT	fGrade			= powf( fWidth, 2 ) + powf( fHeight, 2 );
			fGrade					= sqrtf( fGrade );
				
			_FLOAT	fAngle			= acos( fWidth / fGrade );
			fAngle					= fAngle * 180.0f / D3DX_PI;
			
			//temp
			m_fAngleTemp			= fAngle;
			
			// 1 2
			// 4 3	각 분면별 마우스 각도에 따라 이동방향 결정

			//1
			if ( (vMousePos.x < WINSIZEX / 2) && (vMousePos.y < WINSIZEY / 2) )
			{
				if ( fAngle >= 0.0f && fAngle < 22.5f )
				{
					//방향 체크
					CheckDir( DI_LEFT, false );
				}
				else if ( fAngle >= 22.5 && fAngle <= 67.5f )
				{
					CheckDir( DI_UPLEFT, false );
				}
				else if ( fAngle > 67.5f && fAngle <= 90.0f )
				{
					CheckDir( DI_UP, false );
				}
			}
			//2
			else if ( (vMousePos.x > WINSIZEX / 2) && (vMousePos.y < WINSIZEY / 2) )
			{
				if ( fAngle >= 0.0f && fAngle < 22.5f )
				{
					CheckDir( DI_LEFT, true );
				}
				else if ( fAngle >= 22.5 && fAngle <= 67.5f )
				{
					CheckDir( DI_UPLEFT, true );
				}
				else if ( fAngle > 67.5f && fAngle <= 90.0f )
				{
					CheckDir( DI_UP, false );
				}
			}
			//3
			else if ( (vMousePos.x > WINSIZEX / 2) && (vMousePos.y > WINSIZEY / 2) )
			{
				if ( fAngle >= 0.0f && fAngle < 22.5f )
				{
					CheckDir( DI_LEFT, true );
				}
				else if ( fAngle >= 22.5 && fAngle <= 67.5f )
				{
					CheckDir( DI_DOWNLEFT, true );
				}
				else if ( fAngle > 67.5f && fAngle <= 90.0f )
				{
					CheckDir( DI_DOWN, false );
				}
			}
			//4
			else if ( (vMousePos.x < WINSIZEX / 2) && (vMousePos.y > WINSIZEY / 2) )
			{
				if ( fAngle >= 0.0f && fAngle < 22.5f )
				{
					CheckDir( DI_LEFT, false );
				}
				else if ( fAngle >= 22.5 && fAngle <= 67.5f )
				{
					CheckDir( DI_DOWNLEFT, false );
				}
				else if ( fAngle > 67.5f && fAngle <= 90.0f )
				{
					CheckDir( DI_DOWN, false );
				}
			}
			else
			{
				if ( (vMousePos.x == WINSIZEX / 2) && (vMousePos.y < WINSIZEY / 2) )
				{
					CheckDir( DI_UP, false );
				}
				else if ( (vMousePos.x == WINSIZEX / 2) && (vMousePos.y > WINSIZEY / 2) )
				{
					CheckDir( DI_DOWN, false );
				}
				else if ( (vMousePos.x < WINSIZEX / 2) && (vMousePos.y == WINSIZEY / 2) )
				{
					CheckDir( DI_LEFT, false );
				}
				else if ( (vMousePos.x > WINSIZEX / 2) && (vMousePos.y == WINSIZEY / 2) )
				{
					CheckDir( DI_LEFT, true );
				}
				else if ( (vMousePos.x == WINSIZEX / 2) && (vMousePos.y == WINSIZEY / 2) )
				{
					MessageBox( g_hWnd, L"잘도 중간을 찍었군.", L"sdf", MB_OK );
				}
			}
		}
	}
	else
	{
		m_bMove = false;
	}
}

void CPlayer::CheckState()
{
	_DWORD dwKey = _GETINST( CKeyChecker )->GetKeyState();

	if ( m_pWeapon == NULL )
	{
		m_dwState &= ~ST_ARM;
		m_dwState |= ST_UNARM;
	}
	else
	{
		m_dwState &= ~ST_UNARM;
		m_dwState |= ST_ARM;
	}

	if ( m_bMove == false && !(m_dwState & ST_ATTACK) )
	{
		DelFlag( ST_WALK );
		DelFlag( ST_RUN );
		AddFlag( ST_STAND );
	}
	
	if ( (dwKey & KEY_ALT) && (dwKey & KEY_C) )
	{
		if ( m_bPressed[BI_WARPEACE] == true )
			return;
		m_bPressed[BI_WARPEACE] = true;

		if ( m_dwState & ST_WAR )
		{
			m_dwState &= ~ST_WAR;
			m_dwState |= ST_PEACE;
		}
		else
		{
			m_dwState &= ~ST_PEACE;
			m_dwState |= ST_WAR;
		}
	}
	else
		m_bPressed[BI_WARPEACE] = false;

	if ( (dwKey & KEY_TAB) )
	{
		m_dwState &= ~ST_WAR;
		m_dwState |= ST_PEACE;
	}

	MotionSet();
}

void CPlayer::MotionSet()
{
	//무기를 들었을 때
	if ( m_dwState & ST_ARM )
	{
		//워
		if ( m_dwState & ST_WAR )
		{
			//서 있다면
			if ( m_dwState & ST_STAND )
				m_dwMidID = MI_STAND_TWOHAND_ATTACK;
					
			//걷고 있다면
			if ( m_dwState & ST_WALK )
				m_dwMidID = MI_WALK_ATTACKPOS;
		}
		//피스
		if ( m_dwState & ST_PEACE )
		{
			//서 있다면
			if ( m_dwState & ST_STAND )
				m_dwMidID = MI_STAND;
			
			//걷고 있다면
			if ( m_dwState & ST_WALK )
				m_dwMidID = MI_WALK_ARMED;
		}

		//뛰고 있다면
		if ( m_dwState & ST_RUN )
			m_dwMidID = MI_RUN_ARMED;
	}
}

void CPlayer::Release()
{
	delete m_pCloth;
	m_pCloth = NULL;

	delete m_pWeapon;
	m_pWeapon = NULL;

	//temp
	delete m_pRobe;
	m_pRobe = NULL;
}

void CPlayer::CheckKey()
{
	_DWORD dwKey = _GETINST( CKeyChecker )->GetKeyState();
	if ( dwKey & KEY_DELETE )
	{
		if ( m_pTarget != NULL )
			PCHARACTER( m_pTarget )->SetDamage( 100000 );
	}
	
	if ( (dwKey & KEY_ALT) && (dwKey & KEY_I) )
	{
		PINVENTORY( m_pInven )->ShowInven();
	}
}
