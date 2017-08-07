#include "StdAfx.h"
#include "Inventory.h"
#include "Includes.h"

CInventory::CInventory(void)
{
}

CInventory::CInventory(CObj* pOwner)
{
	m_pInvenOwner = pOwner;
}

CInventory::~CInventory(void)
{
}

void CInventory::Init()
{
	//from CObj
	m_pvecTex		= _GETINST( CTextureLoader )->GetTextureVector();
	D3DXMatrixIdentity( &m_matWorld );									//m_matWorld setting
	
	m_pt.x			= 0;			//MoveToIndex();					//m_vPos setting
	m_pt.y			= 0;

	m_vPos			= D3DXVECTOR3( WINSIZEX / 2, WINSIZEY / 2, 0.0f );
	m_vLook			= D3DXVECTOR3( 1.0f, 0.0f, 0.0f );

	D3DXMatrixScaling( &m_matScale, 1.0f, 1.0f, 0.0f );					//m_matScale setting
	D3DXMatrixTranslation( &m_matTrans, m_vPos.x, m_vPos.y, 0.0f );		//m_matTras setting
	
	m_pCloth		= NULL;
	m_pWeapon		= NULL;
	m_pTarget		= NULL;

	m_dwTexID		= TI_UI;
	m_dwMidID		= UI_INVEN;
	m_dwMidIDPast	= m_dwMidID;
	m_dwDir			= DI_DOWN;
	
	m_iTileIndex	= 0;		//SetTileIndex();	//m_iTileIndex setting
	m_iDepth		= 0;

	m_dwState		= 0x00000000;

	m_iFrame		= 0;
	m_bReverse		= false;
	m_bDecay		= false;
	
	m_dwTime		= 0;
	m_dwTick		= 0;
	
	m_fSizeX		= 160.0f;
	m_fSizeY		= 204.0f;
	
	m_fSpeed		= 0.0f;		
	m_fDegree		= 0.0f;
	
	m_iLocomotive	= 0;
	
	//for char stat
	m_iAction		= 0;

	m_iHP			= 0;
	m_iMP			= 0;	
	
	m_iSTR			= 0;
	m_iDEX			= 0;
	m_iINT			= 0;

	m_iATT			= 0;
	m_iAR			= 0;	

	m_iWeight		= 0;

	m_ptPast		= m_pt;
	SetColRect();			//m_rcColi setting;

	//
	m_bDrag			= false;
	m_bShow			= false;
	m_bLoot			= false;
}

void CInventory::Progress()
{
	KeyCheck();
	//인벤토리 이동
	if ( m_bLoot == true )
	{
		m_dwMidID		= UI_LOOT;
	}
	else
		m_dwMidID		= UI_INVEN;
		
	if ( m_bDrag == true )
	{
		m_vPos = _GETINST( CObjStorage )->GetMouse()->GetvPos() + m_vDist;
	}
	D3DXMatrixTranslation( &m_matTrans, m_vPos.x, m_vPos.y, 0.0f );		//m_matTras setting
	SetColRect();
	
	//인벤토리 아이템에 대한 Progress
	for ( m_iter = m_listItem.begin(); m_iter != m_listItem.end(); ++m_iter )
	{
		(*m_iter)->SetvPos( m_vPos - (*m_iter)->GetInvenPos() );
		(*m_iter)->Progress();
	}
}

void CInventory::Insert(CObj* pItem)
{
	PITEM( pItem )->SetOwner( m_pInvenOwner );

	pItem->SetInvenPos( rand()%int( m_fSizeX / 2 ), rand()%int( m_fSizeY / 2 ) );	//임시

	PITEM( pItem )->SetShrink();
	m_listItem.push_back( pItem );
}

void CInventory::Insert(CObj* pItem, D3DXVECTOR3 vPos)
{
	//PITEM( pItem )->SetAlpha( 255 );
	PITEM( pItem )->SetOwner( m_pInvenOwner );
	
	D3DXVECTOR3 vDist = m_vPos - _GETINST( CObjStorage )->GetMouse()->GetvPos();		
	pItem->SetInvenPos( int( vDist.x ), int( vDist.y ) );	//임시
	pItem->SetvPos( vPos );	//임시
	
	PITEM( pItem )->SetShrink();
	m_listItem.push_back( pItem );
}

void CInventory::Render()
{
	if ( m_bShow == true )
	{
		m_vCenter = (*m_pvecTex)[m_dwTexID][m_dwMidID][m_dwDir][m_iFrame]->vCen;

		m_matWorld = m_matScale * m_matTrans;
		_GETINST( CDevice )->GetSprite()->SetTransform( &m_matWorld );
		_GETINST( CDevice )->GetSprite()->Draw( (*m_pvecTex)[m_dwTexID][m_dwMidID][m_dwDir][m_iFrame]->pTex, NULL, &m_vCenter, NULL, D3DCOLOR_ARGB(255, 255, 255, 255) );
		
		//인벤토리 랜더
		for ( m_iter = m_listItem.begin(); m_iter != m_listItem.end(); ++m_iter )
		{
			(*m_iter)->Render();
		}

		/*TCHAR szBuf[128];
		wsprintf( szBuf, L"bDrag : %d, bShow : %d", m_bDrag, m_bShow );
		
		_GETINST( CDevice )->GetFont()->DrawTextW( _GETINST( CDevice )->GetSprite()
												 , szBuf
												 , lstrlen( szBuf )
												 , NULL
												 , DT_NOCLIP
												 , D3DCOLOR_ARGB( 255, 255, 255, 0 ) );*/

		//DrawColiBox();
	}
	else
	{
		//do nothing
	}

	
}

void CInventory::KeyCheck()
{
	_DWORD dwKey = _GETINST( CKeyChecker )->GetKeyState();

	POINT pt;
	GetCursorPos( &pt );
	ScreenToClient( g_hWnd, &pt );

	if ( PtInRect( &m_rcColi, pt ) )
	{
		if ( dwKey & KEY_LBUTTON )
		{
			if ( m_bShow == false )
				return;
			
			//마우스에 달린 아이템이 없으면
			if ( _GETINST( CObjStorage )->GetMouse()->GetTarget() == NULL )
			{
				if ( m_bDrag == false )
					m_vDist = m_vPos - _GETINST( CObjStorage )->GetMouse()->GetvPos();		
		
				m_bDrag = true;
			}
			//마우스에 달린 아이템이 있으면
			else if ( _GETINST( CObjStorage )->GetMouse()->GetTarget() != NULL )
			{
				POBJ pTarget = _GETINST( CObjStorage )->GetMouse()->GetTarget();
				
				if ( m_pInvenOwner->GetTexID() != TI_WOMAN )
				{
					list<POBJ>* plistItem = PCHARACTER( PITEM( pTarget )->GetOwner() )->GetInven()->GetItemList();

					//그 아이템의 주인의 인벤의 아이템리스트에서 그 아이템을 제거하고
					
					if ( false == plistItem->empty() )
					{
						for ( m_iter = plistItem->begin(); m_iter != plistItem->end(); ++m_iter )
						{
							if ( (*m_iter) == pTarget )
							{
								plistItem->erase( m_iter );
								break;
							}
						}
					}

					//이 인벤의 아이템리스트에 추가
					m_listItem.push_back( pTarget );
					PITEM( pTarget )->SetOwner( m_pInvenOwner );
					_GETINST( CObjStorage )->GetMouse()->SetTarget( NULL );
				}
				m_bDrag = false;
			}
		}
		else
			m_bDrag = false;

		if ( dwKey & KEY_RBUTTON )
		{
			if ( _GETINST( CObjStorage )->GetMouse()->GetTarget() == NULL )
			{
				HideInven();
			}
		}
	}
}

void CInventory::Release()
{

}