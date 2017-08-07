#include "StdAfx.h"
#include "Mouse.h"
#include "Includes.h"

CMouse::CMouse(void)
{
}

CMouse::~CMouse(void)
{
}

void CMouse::Init()
{
	GetCursorPos( &m_ptNow );
	ScreenToClient( g_hWnd, &m_ptNow );
	ShowCursor( FALSE );

	m_ptPast		= m_ptNow;

	m_dwTexID		= TI_UI;
	m_dwMidID		= UI_MOUSE;
	m_dwDir			= CI_PEACE_UP_LEFT;

	m_fSizeX		= 5.0f;
	m_fSizeY		= 5.0f;
	m_fDegree		= 45.0f;

	m_pvecTex		= CTextureLoader::GetInst()->GetTextureVector();
	m_vCenter		= D3DXVECTOR3( m_fSizeX / 2.0f, m_fSizeY / 2.0f, 0.0f );
	
	m_vPos.x 		= float(m_ptNow.x);
	m_vPos.y 		= float(m_ptNow.y);
	m_vPos.z 		= 0.0f;

	m_pTarget		= NULL;

	m_pSelectBox	= NULL; 
	m_bSelecting	= false;
	m_bEqual		= false;
	m_bButton		= false;
	m_bDrop			= false;

	SetColRect();
	D3DXMatrixIdentity( &m_matWorld );
}

void CMouse::Progress()
{
	GetCursorPos( &m_ptNow );
	ScreenToClient( g_hWnd, &m_ptNow );
		
	if ( _GETINST( CObjStorage )->GetPlayer()->GetState() & ST_WAR )
		m_dwDir = CI_WAR_UP_LEFT;
	else 
		m_dwDir = CI_PEACE_UP_LEFT;

	m_vPos.x = float(m_ptNow.x);
	m_vPos.y = float(m_ptNow.y);
	
	D3DXVECTOR3 vTemp = m_vPos;
	vTemp.x -= m_vScroll.x;
	vTemp.y -= m_vScroll.y;
	
	//RevisionPos();

	if ( m_ptNow.x == m_ptPast.x && m_ptNow.y == m_ptPast.y )
	{
		m_bEqual = true;
	}
	else
		m_bEqual = false;
	
	//SelectBox Create & Progress
	//SelectBox();

	m_ptDist.x = m_ptPast.x - m_ptNow.x;
	m_ptDist.y = m_ptPast.y - m_ptNow.y;

	m_ptPast = m_ptNow;

	KeyCheck();

	SetColRect();
}

void CMouse::Render()
{
	TCHAR szBuf[128];
	
	wsprintf( szBuf, L"[%d,%d]", int(m_pt.x), int(m_pt.y) );
	
	RECT* m_rcView = CDevice::GetInst()->GetRect();
	RECT rcView = { int(m_vPos.x + m_rcView->left + 30)
				  , int(m_vPos.y + m_rcView->top + 30)
				  , int(m_vPos.x + m_rcView->right)
				  , int(m_vPos.y + m_rcView->bottom) };
	
	
	CDevice::GetInst()->GetSprite()->SetTransform( &m_matWorld );
	D3DXVECTOR3		vPosTemp( float(rcView.left), float(rcView.top), 0.0f );

	if ( m_pTarget != NULL )
	{
		D3DXVECTOR3 vTemp = m_vPos;

		vTemp.x -= 20; 
		vTemp.y -= 20; 

		CDevice::GetInst()->GetSprite()->Draw( (*m_pvecTex)[m_pTarget->GetTexID()][MI_ICON][DI_DOWN][0]->pTex
										 , NULL, &m_vCenter, &vTemp
										 , D3DCOLOR_ARGB(255, 255, 255, 255));
	}

	CDevice::GetInst()->GetSprite()->Draw( (*m_pvecTex)[m_dwTexID][m_dwMidID][m_dwDir][0]->pTex
										 , NULL, &m_vCenter, &m_vPos
										 , D3DCOLOR_ARGB(255, 255, 255, 255));


	CDevice::GetInst()->GetFont()->DrawTextW( CDevice::GetInst()->GetSprite()
											, szBuf
											, lstrlen(szBuf)
											, &rcView
											, DT_NOCLIP
											, D3DCOLOR_ARGB(255, 255, 255, 255) ); 

	//wsprintf( szBuf, L"[%d,%d]", int(m_vPos.x), int(m_vPos.y) );
	
	_INT iIndex = m_pt.x * AMOUNTY + m_pt.y;
	
	if ( iIndex >= 0 && iIndex < AMOUNTX * AMOUNTY )
		wsprintf( szBuf, L"[%d]", (*_GETINST( CObjStorage )->GetTileVec())[iIndex]->GetDepth() );

	rcView.top		+= 10;
	rcView.bottom	+= 10;
	CDevice::GetInst()->GetFont()->DrawTextW( CDevice::GetInst()->GetSprite()
											, szBuf
											, lstrlen(szBuf)
											, &rcView
											, DT_NOCLIP
											, D3DCOLOR_ARGB(255, 255, 255, 255) ); 

	if ( m_pSelectBox != NULL )
		m_pSelectBox->Render();
}

void CMouse::ScrollMove()
{
	_INT iGap = 10;

	D3DXVECTOR3	vPos(0.0f, 0.0f, 0.0f);

	//스크롤락이 걸리는 조건을 어떻게 줄것인가?
	if ( (m_vPos.x < 0 + iGap) )	//&& (m_vPos.x > 0) )
	{
		vPos.x = 7;
	}
	if ( (m_vPos.x > WINSIZEX - iGap) )	//&& (m_vPos.x < WINSIZEX) )
	{
		vPos.x = -7;
	}
	if ( (m_vPos.y < 0 + iGap) )	//&& (m_vPos.y > 0) )
	{
		vPos.y = 7;
	}

	if ( (m_vPos.y > WINSIZEY - iGap) )	//&& (m_vPos.y < WINSIZEY) )
	{
		vPos.y = -7;
	}

	SetScroll( vPos );
}

POBJ CMouse::GetSelectBox()
{
	return m_pSelectBox;
}
	
_BOOL CMouse::GetSelecting()
{
	return m_bSelecting;
}

_BOOL CMouse::GetPastPt()
{
	return m_bEqual;
}

POINT CMouse::GetPtNow()
{
	return m_ptNow;
}

POINT CMouse::GetPtPast()
{
	return m_ptNow;
}

POINT CMouse::GetPtDistance()
{
	return m_ptDist;
}

void CMouse::SelectBox()
{
	_DWORD	dwKey = _GETINST(CKeyChecker)->GetKeyState();
	if ( dwKey & KEY_LBUTTON )
	{
		if ( m_bSelecting == true )
		{
			m_pSelectBox->Progress();
			return;
		}
		m_bSelecting = true;
		
		m_pSelectBox = CObjFactory<SELECTBOX>::CreateObj( m_vPos );
		m_pSelectBox->Init();
	}
	else
	{
		m_bSelecting = false;
		delete m_pSelectBox;
		m_pSelectBox = NULL;
	}	
}

void CMouse::KeyCheck()
{
	_DWORD dwKey = _GETINST( CKeyChecker )->GetKeyState();
	
	if ( dwKey & KEY_LBUTTON )
	{
		if ( m_bLButton == true )
			return;
		
		m_bLButton = true;
		
		//마우스에 걸린 아이템이 있을 때
		if ( m_pTarget != NULL )
		{
			if ( true == PITEM( m_pTarget )->GetSelected() )
				return;

			//인벤에 넣었을 때
			if ( TRUE == PtInRect( &PCHARACTER( _GETINST( CObjStorage )->GetPlayer() )->GetInven()->GetColRect(), m_ptNow ) )
			{	
				if ( PITEM( m_pTarget )->GetOwner()->GetTexID() == TI_WOMAN )
				{
					list<POBJ>* plistItem = PCHARACTER( PITEM( m_pTarget )->GetOwner() )->GetInven()->GetItemList();

					for ( m_iter = plistItem->begin(); m_iter != plistItem->end(); ++m_iter )
					{
						if ( (*m_iter) == m_pTarget )
						{
							plistItem->erase( m_iter );
							break;
						}
					}
				}
				else if ( PITEM( m_pTarget )->GetOwner()->GetMidID() == OI_TILE )
				{
					list<POBJ>* plistItem = PCHARACTER( PITEM( m_pTarget )->GetOwner() )->GetItemList();

					for ( m_iter = plistItem->begin(); m_iter != plistItem->end(); ++m_iter )
					{
						if ( (*m_iter) == m_pTarget )
						{
							plistItem->erase( m_iter );
							break;
						}
					}
				}

				PINVENTORY( PCHARACTER( _GETINST( CObjStorage )->GetPlayer() )->GetInven() )->Insert( m_pTarget, m_vPos );
				PITEM( m_pTarget )->SetInInven();
				m_pTarget = NULL;

				return;
			}
			else
			{
				//현재 마우스가 위치한 타일을 찾고
				_INT iIndex = m_pt.x * AMOUNTY + m_pt.y;
				vector<CObj*>*	pvecTemp = _GETINST( CObjStorage )->GetTileVec();

				//그 타일의 아이템리스트에 마우스에 걸린 아이템을 넣음
				PITEM( (*pvecTemp)[iIndex] )->GetItemList()->push_back( m_pTarget );
				
				//아이템의 위치를 타겟으로 옮기고 
				m_pTarget->SetvPos( (*pvecTemp)[iIndex]->GetvPos() );
				
				/*--------- 타겟(아이템)의 주인의 아이템 리스트를 받아와서 체크후에 제거 ---------*/
				if ( PITEM( m_pTarget )->GetOwner()->GetTexID() == TI_WOMAN )
				{
					list<POBJ>* plistItem = PCHARACTER( PITEM( m_pTarget )->GetOwner() )->GetInven()->GetItemList();

					for ( m_iter = plistItem->begin(); m_iter != plistItem->end(); ++m_iter )
					{
						if ( (*m_iter) == m_pTarget )
						{
							plistItem->erase( m_iter );
							break;
						}
					}
				}
				else if ( PITEM( m_pTarget )->GetOwner()->GetMidID() == OI_TILE )
				{
					list<POBJ>* plistItem = PCHARACTER( PITEM( m_pTarget )->GetOwner() )->GetItemList();

					for ( m_iter = plistItem->begin(); m_iter != plistItem->end(); ++m_iter )
					{
						if ( (*m_iter) == m_pTarget )
						{
							plistItem->erase( m_iter );
							break;
						}
					}
				}
				/*----------------------------------------------*/

				//아이템의 주인을 타일로
				PITEM( m_pTarget )->SetOwner( (*pvecTemp)[iIndex] );

				PITEM( m_pTarget )->SetPopInven();
				//PITEM( m_pTarget )->SetInInven();
				//그리고 마우스의 타겟을 비움
				m_pTarget = NULL;
			}
		}
	}
	else
	{
		m_bLButton	= false;
	}


	if ( (dwKey & KEY_LBUTTON) || (dwKey & KEY_RBUTTON ) )
	{
		if ( m_bButton == true )
			return;

		m_bButton = true;
		InvenColiCheck();
	}
	else
	{
		m_bButton		= false;
		m_bInvenColi	= false;
	}	

	if ( dwKey & KEY_RBUTTON )
	{
		if ( m_pTarget != NULL )
		{
			PITEM( m_pTarget ) ->SetAlpha( 255 );
			m_pTarget = NULL;
		}
	}
}

void CMouse::InvenColiCheck()
{
	if (  TRUE == PtInRect( &PCHARACTER( _GETINST(CObjStorage)->GetPlayer() )->GetInven()->GetColRect()
							  , m_ptNow ) )
	{
		m_bInvenColi = true;
	}
	else
		m_bInvenColi = false;
}

void CMouse::Release()
{

}