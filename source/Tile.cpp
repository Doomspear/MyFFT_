#include "StdAfx.h"
#include "Tile.h"
#include "Includes.h"

CTile::CTile(void)
: m_bEdit( false )
, m_bStatic( false )
{
	m_dwTexID		= TI_OBJ;
	m_dwMidID		= OI_TILE;
	m_dwDir			= TT_DUNGEON;
	m_vPos			= D3DXVECTOR3( BACKBUFSIZEX >> 1, BACKBUFSIZEY >> 1, 0.0f );
}

CTile::CTile(CTile& rtile)
{
}	

CTile::CTile(POINT pt)
: m_bEdit( false )
, m_bStatic( false )
{
	//기본적으로 깔릴 타일의 타입
	
	m_dwTexID		= TI_OBJ;
	m_dwMidID		= OI_TILE;
	m_dwDir			= TT_GRASS;
	//m_dwDir			= TT_DEFAULT;
	
	m_fDegree		= 45.0f;
	m_pt			= pt;

	//타일을 인덱스에 맞게 화면에 배치함
}

CTile::~CTile(void)
{
	Release();
}

void CTile::Init()
{	
	D3DXMatrixIdentity( &m_matWorld );

	m_pvecTex	= CTextureLoader::GetInst()->GetTextureVector();
	
	m_iDepth	= 0;
	m_iFrame	= 0;

	m_vCenter	= D3DXVECTOR3( 16.0f, 16.0f, 0.0f );
	m_vLook		= D3DXVECTOR3( 1.0f, 0.0f, 0.0f );
	
	m_fSizeX	= sqrtf( powf(32.0f, 2) + powf(32.0f, 2) );
	m_fSizeY	= sqrtf( powf(32.0f, 2) + powf(32.0f, 2) );
		
	m_bClosed	= false;

	MoveToIndex();
	SetColRectTile();
}
void CTile::Progress()
{
	if ( SightCheck() == false ) 
	{
		return;
	}

	MoveToIndex();
	
	D3DXVECTOR3	vTemp = CObjStorage::GetInst()->GetMouse()->GetvPos();

	_DWORD	dwKey = _GETINST(CKeyChecker)->GetKeyState();

	if ( (m_rcColi.left < vTemp.x) && ((m_rcColi.left + m_fSizeX / 2.0f) > vTemp.x) )
	{
		//1사분면 ( wn )
		if ( (m_rcColi.top < vTemp.y) && (m_rcColi.top + m_fSizeY / 2.0f) > vTemp.y) 
		{
			_FLOAT fMouse = ((m_rcColi.top + m_fSizeY / 2) - vTemp.y) / (vTemp.x - m_rcColi.left);
			
			if ( fMouse < 1.0f )
			{
				_GETINST( CObjStorage )->GetMouse()->SetIndexPt( m_pt );
				if ( dwKey & KEY_LBUTTON )
				{
					//GetItemFromMouse();
					//m_dwDir = TT_DUNGEON;
				}
			}
		}
		//4사분면 ( ws )
		else if ( ((m_rcColi.bottom - m_fSizeY / 2.0f) < vTemp.y) && (m_rcColi.bottom > vTemp.y) )
		{
			_FLOAT fMouse = (vTemp.y - (m_rcColi.top + m_fSizeY / 2.0f)) / (vTemp.x - m_rcColi.left);
			
			if ( fMouse < 1.0f )
			{
				_GETINST( CObjStorage )->GetMouse()->SetIndexPt( m_pt );
				if ( dwKey & KEY_LBUTTON )
				{
					//GetItemFromMouse();
					//m_dwDir = TT_DUNGEON;
				}
			}
		}
	}
	else if ( (m_rcColi.right > vTemp.x) && ((m_rcColi.right - m_fSizeX / 2.0f) < vTemp.x) )
	{
		if ( (m_rcColi.top < vTemp.y) && (m_rcColi.top + m_fSizeY / 2.0f) > vTemp.y) 
		{
			_FLOAT fMouse = ((m_rcColi.top + m_fSizeY / 2) - vTemp.y) / (m_rcColi.right - vTemp.x);
			if ( fMouse < 1.0f )
			{
				_GETINST( CObjStorage )->GetMouse()->SetIndexPt( m_pt );
				if ( dwKey & KEY_LBUTTON )
				{
					//GetItemFromMouse();
					//m_dwDir = TT_DUNGEON;
				}
			}
		}
		else if ( ((m_rcColi.bottom - m_fSizeY / 2.0f) < vTemp.y) && (m_rcColi.bottom > vTemp.y) )
		{
			_FLOAT fMouse = (vTemp.y - (m_rcColi.top + m_fSizeY / 2.0f)) / (m_rcColi.right - vTemp.x);
			if ( fMouse < 1.0f )
			{
				_GETINST( CObjStorage )->GetMouse()->SetIndexPt( m_pt );
				if ( dwKey & KEY_LBUTTON )
				{
					//GetItemFromMouse();
					//m_dwDir = TT_DUNGEON;
				}
			}
		}
	}
		
	//에디트 모드가 아닐 때
	if ( m_bEdit == false )
	{
		//Drag and fillup
		//일단 여기부터 수정
		if ( true == PMOUSE(_GETINST(CObjStorage)->GetMouse())->GetSelecting() )
		{
			RECT rc = { 0, 0, 0, 0 };
		
			RECT rcTemp;
			
			//일단 이정도 충돌로 간다
			SetRect( &rcTemp, static_cast<int>( m_rcColi.left + m_fSizeX / 4.0f )
							, static_cast<int>( m_rcColi.top + m_fSizeY / 4.0f )
							, static_cast<int>( m_rcColi.right - m_fSizeX / 4.0f )
							, static_cast<int>( m_rcColi.bottom - m_fSizeY / 4.0f ) );
	
			if ( IntersectRect( &rc, &( PMOUSE(_GETINST(CObjStorage)->GetMouse())->GetSelectBox()->GetColRect() ), &rcTemp) )
			{
				m_dwDir = TT_DUNGEON;
			}
		}
	}
	
	RevisionPos();

	D3DXMATRIXA16		matTrans;
	D3DXMatrixTranslation( &matTrans, m_vPos.x, m_vPos.y, m_vPos.z );

	D3DXMATRIXA16		matRotateZ;
	D3DXMatrixRotationZ( &matRotateZ, D3DXToRadian( m_fDegree ) );

	D3DXMATRIXA16		matScale;
	D3DXMatrixScaling( &matScale, 1.0f, 1.0f, 0.0f );
	
	m_matWorld = matScale * matRotateZ * matTrans;

	for ( m_iter = m_listItem.begin(); m_iter != m_listItem.end(); ++m_iter )
	{
		(*m_iter)->SetvPos( m_vPos );
		(*m_iter)->Progress();
	}

	SetColRectTile();
}

void CTile::GetItemFromMouse()
{
	//왼클릭을 하면 마우스의 타겟이 어떤지를 체크하고 
	if ( _GETINST( CObjStorage )->GetMouse()->GetTarget() != NULL )
	{
		//
		POBJ pItem = _GETINST( CObjStorage )->GetMouse()->GetTarget();
		m_listItem.push_back( pItem/*(*m_iter)*/ );
		_GETINST( CObjStorage )->GetMouse()->SetTarget( NULL );
		
		pItem/*(*m_iter)*/->SetvPos( m_vPos );
		PITEM( pItem/*(*m_iter)*/ )->SetAlpha( 255 );
		PITEM( pItem/*(*m_iter)*/ )->SetOwner( this );
		
		
		//플레이어의 인벤토리의 아이템리스트를 받아옴
		list<CObj*>* plistPlayerItem = PINVENTORY( PCHARACTER( _GETINST( CObjStorage )->GetPlayer() )->GetInven() )->GetItemList();

		//거기서 같은게 있으면 지우고, 마우스의 타겟을 NULL로 만듬
		for ( m_iter = plistPlayerItem->begin(); m_iter != plistPlayerItem->end(); ++m_iter )
		{
			if ( (*m_iter) == pItem )
			{
				plistPlayerItem->erase( m_iter );
				
				break;
			}
		}
	}
}

void CTile::Render()
{
	if ( SightCheck() == false ) 
	{
		return;
	}

	CDevice::GetInst()->GetSprite()->SetTransform( &m_matWorld );
	CDevice::GetInst()->GetSprite()->Draw( (*m_pvecTex)[m_dwTexID][m_dwMidID][m_dwDir][m_iFrame]->pTex, NULL, &m_vCenter, NULL, D3DCOLOR_ARGB(255, 255, 255, 255) );
	
	for ( m_iter = m_listItem.begin(); m_iter != m_listItem.end(); ++m_iter )
	{
		(*m_iter)->Render();
	}

	//DrawIndex();
	//DrawPos();
	//DrawDepth();
	
	/*if ( m_pt.x == 29 && m_pt.y == 29 )
	{
		DrawColiBox();
	}*/
}

_DWORD CTile::GetType()
{
	return m_dwMidID;
}

_BOOL CTile::GetLocomo()
{
	return m_bLocoDraw;
}

void CTile::SetType(TILE_TYPE TT)
{
	m_dwMidID = TT;
}

void CTile::SetEdit(_BOOL bEdit)
{
	m_bEdit = bEdit;
}

void CTile::SetLocomo()
{
	m_bLocoDraw = true;
}

void CTile::SetUnLocomo()
{
	m_bLocoDraw = false;
}

void CTile::SetClosed()
{
	m_bClosed = true;
}

void CTile::SetOpen()
{
	m_bClosed = false;
}

_BOOL CTile::GetClosed()
{
	return m_bClosed;
}

void CTile::Release()
{
}

void CTile::SetStatic()
{
	m_bStatic = true;
}

void CTile::RelStatic()
{
	m_bStatic = false;
}

_BOOL CTile::GetStatic()
{
	return m_bStatic;
}