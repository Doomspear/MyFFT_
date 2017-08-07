#include "StdAfx.h"
#include "Robe.h"
#include "Includes.h"

CRobe::CRobe(void)
{
}

CRobe::CRobe(CObj* pOwner)
{
	m_pOwner	= pOwner;
	m_iFrame	= 0;
}

CRobe::~CRobe(void)
{
}

void CRobe::Init()
{
	m_dwTexID		= TI_ROBE;
	m_pvecTex		= _GETINST( CTextureLoader )->GetTextureVector();
	m_bShrink		= false;
	m_bClick		= false;
	m_bInInven		= false;
	m_iAlpha		= 255;
}

void CRobe::Progress()
{
	if ( m_pOwner != NULL )
	{
		//������ �ִٸ�(������ ����)
		if ( m_bShrink == false )
		{
			m_vPos		= m_pOwner->GetvPos();
			m_dwMidID	= m_pOwner->GetMidID();
			m_dwDir		= m_pOwner->GetDirection();
			m_iFrame	= m_pOwner->GetFrame();
			m_bReverse	= m_pOwner->GetReverse();
		}
		else if ( m_bShrink == true )
		{
			m_dwMidID	= MI_ICON;
			//SetIconColi();
		}
	}
	else
	{
		//������ ���ٸ� (���� ������ �ְų� �κ��丮�� ����ִ� ����)
		m_dwMidID	= MI_ICON;
		m_bShrink	= true;
	}

	//if ( m_bClick == false )
		SetIconColi();

	KeyCheck();
	CheckReverse();
	D3DXMatrixTranslation( &m_matTrans, m_vPos.x, m_vPos.y, m_vPos.z );
	m_matWorld = m_matScale * m_matTrans;

	if ( _GETINST( CObjStorage )->GetMouse()->GetTarget() != this )
		m_iAlpha = 255;

}
void CRobe::Render()
{
	if ( m_bShrink == false )
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
	}
	else if ( m_bShrink == true )
	{

		//D3DXMatrixTranslation( &m_matTrans, m_vInvenPos.x, m_vInvenPos.y, 0.0f );
		m_matWorld = m_matScale * m_matTrans;

		_GETINST( CDevice )->GetSprite()->SetTransform( &m_matWorld );
		_GETINST( CDevice )->GetSprite()->Draw( (*m_pvecTex)[m_dwTexID][MI_ICON][0][0]->pTex
											  , NULL
											  , &( (*m_pvecTex)[m_dwTexID][MI_ICON][0][0]->vCen )
											  , NULL
											  , D3DCOLOR_ARGB(m_iAlpha, 255, 255, 255) );
	}

	D3DXMATRIXA16		matTemp;
	
	D3DXMatrixIdentity( &matTemp );
	
	D3DXVECTOR3 vCenter( float(m_rcIcon.right - m_rcIcon.left) / 2
					   , float(m_rcIcon.bottom - m_rcIcon.top) / 2, 0.0f );

	D3DXVECTOR3 vTemp = m_vPos;
	vTemp.y = vTemp.y - m_fSizeY / 2.0f;

	_GETINST( CDevice )->GetSprite()->SetTransform( &matTemp );
	_GETINST( CDevice )->GetSprite()->Draw( (*m_pvecTex)[TI_UI][UI_COLIBOX][DEFAULT][0]->pTex
										  , &m_rcIcon, &vCenter, &vTemp
										  , D3DCOLOR_ARGB(100, 255, 255, 255) );

	DrawColiBox();

}

void CRobe::KeyCheck()
{
	_DWORD dwKey = _GETINST( CKeyChecker )->GetKeyState();
	
	POINT pt;
	GetCursorPos( &pt );
	ScreenToClient( g_hWnd, &pt );

	//�޹�ư�� ������ ��
	/*if ( _GETINST( CObjStorage )->GetMouse()->GetTarget() == this )
	{
		return;
	}*/

	if ( dwKey & KEY_LBUTTON )
	{
		if ( m_bClick == true )
			return;
		
		m_bClick = true;

		if ( false == PINVENTORY( PCHARACTER( _GETINST( CObjStorage )->GetPlayer() )->GetInven() )->GetState() )
		{
			if ( m_bInInven == true )
				return;
		}

		//����ũ ���¶��
		if ( m_bShrink == true )
		{
			//�׸��� ������ ��Ʈ�� ���콺�� �浹���̶�� 
			if ( PtInRect( &m_rcIcon, pt ) )
			{
				//���콺�� Ÿ���� NULL�� �ƴ϶��
				if ( _GETINST( CObjStorage )->GetMouse()->GetTarget() != NULL )
				{
					m_bSelected = false;	
					if ( _GETINST( CObjStorage )->GetMouse()->GetTarget() == this )
					{
						
					}
					//���⼭ �� �Ұ� ����
					return;
				}
				//���콺 Ÿ���� NULL�̸�
				else
				{
					//Ÿ���� �ڽ��� �ƴҶ�
					/*if ( _GETINST( CObjStorage )->GetMouse()->GetTarget() != this )
					{*/
					m_bSelected = true;
					_GETINST( CObjStorage )->GetMouse()->SetTarget( this );
					SetAlpha( 0 );
					//}
				}
			}
		}
	}
	else
	{
		m_bClick = false;
		m_bSelected = false;	
	}
}

void CRobe::Release()
{

}
