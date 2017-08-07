#include "StdAfx.h"
#include "Corpse.h"
#include "Includes.h"

CCorpse::CCorpse(void)
{
}

CCorpse::CCorpse(CObj* pOwner)
{
	//��ü���� �ʿ��Ѱ�
	m_pvecTex		= _GETINST( CTextureLoader )->GetTextureVector();

	//�� �ؽ��� ����, ���� ����
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

	//��ġ
	m_pt.x			= pOwner->GetIndexPt().x;
	m_pt.y			= pOwner->GetIndexPt().y;
		
	//������ ����
	m_pInven		= PCHARACTER( pOwner )->GetInven();
	PINVENTORY( m_pInven )->SetLoot();
	PINVENTORY( m_pInven )->SetInvenOwner( this );

	_GETINST( CObjStorage )->SetInventoUI( m_pInven );

	//���� ����
	m_bDecay		= false;
}

CCorpse::~CCorpse(void)
{
	//MessageBox();
	//Release();
}

void CCorpse::Init()
{
	//Ÿ�̸� ����		
	m_dwTime	= GetTickCount();
	m_fDegree	= 45.0f;
	m_iTimer	= 10000;

	m_vLook		= D3DXVECTOR3( 1.0f, 0.0f, 0.0f );
	MoveToIndex();
}

void CCorpse::Progress()
{
	//Ÿ�̸Ӱ� ����
	if ( m_dwTime + 1000 < GetTickCount() )
	{
		m_dwTime = GetTickCount();
		--m_iTimer;

	}
	//Ÿ�̸� 0�� �Ǹ� �����θ� ����
	if ( m_iTimer == 0 ) 
	{
		Release();
		return;
	}

	//Ÿ�̸Ӱ� 0�� �ƴҶ� �̵��ؼ� ��ġ ǥ��
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

	//�׸��� �ڱ��ڽ��� ��������(����)
	m_bDecay = true;
}