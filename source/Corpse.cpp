#include "StdAfx.h"
#include "Corpse.h"
#include "Includes.h"

CCorpse::CCorpse(void)
{
}

CCorpse::CCorpse(CObj* pOwner)
{
	//시체한테 필요한것
	m_pvecTex		= _GETINST( CTextureLoader )->GetTextureVector();

	//모델 텍스쳐 정보, 센터 정보
	m_dwTexID		= pOwner->GetTexID();
	m_dwMidID		= MI_DIE;
	m_dwDir			= pOwner->GetDirection();
	m_bReverse		= pOwner->GetReverse();
	m_iFrame		= (*m_pvecTex)[m_dwTexID][MI_DIE][m_dwDir].size() - 1;
	m_vCenter		= (*m_pvecTex)[m_dwTexID][MI_DIE][m_dwDir][m_iFrame]->vCen;

	m_fSizeX		= (*m_pvecTex)[m_dwTexID][MI_DIE][m_dwDir][m_iFrame]->vCen.x;
	m_fSizeY		= (*m_pvecTex)[m_dwTexID][MI_DIE][m_dwDir][m_iFrame]->vCen.y / 2;

	m_pCloth		= pOwner->GetCloth();
	if ( m_pCloth != NULL )
	{
		pOwner			->SetClothOff();
		PITEM( m_pCloth )->SetOwner( this );
	}

	m_pWeapon		= pOwner->GetWeapon();
	
	if ( m_pWeapon != NULL )
	{
		pOwner			->SetDisarm();
		PITEM( m_pWeapon )->SetOwner( this );
	}

	//위치
	m_pt.x			= pOwner->GetIndexPt().x;
	m_pt.y			= pOwner->GetIndexPt().y;
		
	//아이템 정보
	m_pInven		= PCHARACTER( pOwner )->GetInven();
	PINVENTORY( m_pInven )->SetLoot();
	PINVENTORY( m_pInven )->SetInvenOwner( this );

	_GETINST( CObjStorage )->SetInventoUI( m_pInven );

	//썩음 여부
	m_bDecay		= false;
}

CCorpse::~CCorpse(void)
{
	//MessageBox();
	//Release();
}

void CCorpse::Init()
{
	//타이머 셋팅		
	m_dwTime	= GetTickCount();
	m_fDegree	= 45.0f;
	m_iTimer	= 10000;

	m_vLook		= D3DXVECTOR3( 1.0f, 0.0f, 0.0f );
	MoveToIndex();
}

void CCorpse::Progress()
{
	//타이머가 간다
	if ( m_dwTime + 1000 < GetTickCount() )
	{
		m_dwTime = GetTickCount();
		--m_iTimer;

	}
	//타이머 0이 되면 스스로를 지움
	if ( m_iTimer == 0 ) 
	{
		Release();
		return;
	}

	//타이머가 0이 아닐땐 이동해서 위치 표시
	MoveToIndex();
	RevisionPos();
	CheckReverse();

	D3DXMatrixTranslation( &m_matTrans, m_vPos.x, m_vPos.y, m_vPos.z );
	m_matWorld = m_matScale * m_matTrans;

	if ( m_pCloth != NULL )
		m_pCloth->Progress();

	if ( m_pWeapon != NULL )
		m_pWeapon->Progress();

	if ( TRUE == PtInRect( &m_rcColi, PMOUSE( _GETINST( CObjStorage )->GetMouse() )->GetPtNow() ) )
	{
		if ( _GETINST( CKeyChecker )->CheckDbClick() )
		{
			PINVENTORY( m_pInven )->ShowInven();
		}
	}
	SetColRect();
}

void CCorpse::Render()
{
	_GETINST( CDevice )->GetSprite()->SetTransform( &m_matWorld );
	_GETINST( CDevice )->GetSprite()->Draw( (*m_pvecTex)[m_dwTexID][m_dwMidID][m_dwDir][m_iFrame]->pTex
										  , NULL
										  , &m_vCenter, NULL
										  , D3DCOLOR_ARGB(255, 255, 255, 255) );
	if ( m_pCloth != NULL )
		m_pCloth->Render();

	if ( m_pWeapon != NULL )
		m_pWeapon->Render();
	
	//DrawColiBox();
}

void CCorpse::Release()
{
	delete m_pCloth;
	m_pCloth = NULL;

	delete m_pWeapon;
	m_pWeapon = NULL;

	/*delete m_pInven;
	m_pInven = NULL;*/
	PINVENTORY( m_pInven )->SetInvenOwner( NULL );

	//그리고 자기자신을 동적해제(수정)
	m_bDecay = true;
}