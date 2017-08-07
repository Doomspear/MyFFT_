#include "StdAfx.h"
#include "Obj.h"
#include "Includes.h"

D3DXVECTOR3 CObj::m_vScroll(0.0f, 0.0f, 0.0f);
POINT CObj::m_ptStatic = {0, 0};

CObj::CObj(void)
: m_pCloth( NULL )
, m_pWeapon( NULL )
{
}

CObj::~CObj(void)
{
}

void CObj::SetColRect()
{
	D3DXVECTOR3 vTemp = m_vPos;

	vTemp.y -= m_fSizeY / 2.0f;

	SetRect( &m_rcColi,	int(vTemp.x - m_fSizeX / 2.0f)
					  ,	int(vTemp.y - m_fSizeY / 2.0f)
					  ,	int(vTemp.x + m_fSizeX / 2.0f)
					  ,	int(vTemp.y + m_fSizeY / 2.0f) );
}

void CObj::SetColRectTile()
{
	SetRect( &m_rcColi,	int(m_vPos.x - m_fSizeX / 2.0f)
					  ,	int(m_vPos.y - m_fSizeY / 2.0f)
					  ,	int(m_vPos.x + m_fSizeX / 2.0f)
					  ,	int(m_vPos.y + m_fSizeY / 2.0f) );
}

void CObj::SetColRectLeaf()
{
	SetRect( &m_rcColi,	int(m_vPos.x - m_fSizeX / 2.0f)
					  ,	int(m_vPos.y - m_fSizeY / 2.0f)
					  ,	int(m_vPos.x + m_fSizeX / 2.0f)
					  ,	int(m_vPos.y + m_fSizeY / 2.0f) );
}


void CObj::SetColRect(_FLOAT fSizeX, _FLOAT fSizeY)
{
	SetRect( &m_rcColi,	int(m_vPos.x - fSizeX / 2.0f)
					  ,	int(m_vPos.y - fSizeY / 2.0f)
					  ,	int(m_vPos.x + fSizeX / 2.0f)
					  ,	int(m_vPos.y + fSizeY / 2.0f) );
}

void CObj::SetColRect(D3DXVECTOR3 vPos, _FLOAT fSizeX, _FLOAT fSizeY)
{
	//¿ÏÀü ÂïÀ½
	fSizeY /= 2.0f;
	
	SetRect( &m_rcColi,	int(m_vPos.x - fSizeX / 2.0f)
					  ,	int(m_vPos.y - fSizeY * 1.5f)
					  ,	int(m_vPos.x + fSizeX / 2.0f)
					  ,	int(m_vPos.y - fSizeY / 2) );
}

RECT CObj::GetColRect() const
{
	return m_rcColi;
}

D3DXVECTOR3	CObj::GetvPos() const
{
	return m_vPos;
}

POINT CObj::GetIndexPt() const
{
	return m_pt;
}

void CObj::ScrollSet()
{
	m_vPos.x += m_vScroll.x;
	m_vPos.y += m_vScroll.y;
}

void CObj::ScrollSet(D3DXVECTOR3* vpPos)
{
	(*vpPos).x += m_vScroll.x;
	(*vpPos).y += m_vScroll.y;
}

_BOOL CObj::SightCheck()
{
	MoveToIndex();
	RevisionPos();

	if ( m_vPos.x + m_fSizeX < 0 
	  || m_vPos.x - m_fSizeX > WINSIZEX
	  || m_vPos.y + m_fSizeY < 0 
	  || m_vPos.y - m_fSizeY > WINSIZEY)
	{
		return false;
	}
	else
		return true;
}	

void CObj::RevisionPos()
{
	D3DXVECTOR3 vScroll( m_vScroll.x, m_vScroll.y, 0.0f );
	m_vPos += vScroll;
}

void CObj::SetScroll(D3DXVECTOR3 vPos)
{
	m_vScroll.x += vPos.x;
	m_vScroll.y += vPos.y;
}

void CObj::SetIndexPt(POINT pt)
{
	m_pt = pt;
}

_FLOAT CObj::GetSizeX() const
{
	return m_fSizeX;
}
_FLOAT CObj::GetSizeY() const
{
	return m_fSizeY;
}	

_DWORD	CObj::GetTexID() const
{
	return m_dwTexID;
}

_DWORD	CObj::GetMidID() const
{
	return m_dwMidID;
}

_DWORD	CObj::GetDirection() const
{
	return m_dwDir;
}

_DWORD	CObj::GetState() const
{
	return m_dwState;
}

_INT CObj::GetFrame() const
{
	return m_iFrame;
}

_BOOL CObj::GetReverse() const
{
	return m_bReverse;
}

CObj* CObj::GetCloth() const
{
	return m_pCloth;
}

CObj* CObj::GetWeapon() const
{
	return m_pWeapon;
}

void CObj::CheckReverse()
{
	if ( m_bReverse == true )
	{
		D3DXMatrixScaling( &m_matScale, -1.0f, 1.0f, 0.0f );
	}
	else
		D3DXMatrixScaling( &m_matScale, 1.0f, 1.0f, 0.0f );
}

_BOOL CObj::GetDecay() const
{
	return m_bDecay;
}

void CObj::SetClothOff()
{
	m_pCloth = NULL;
}
void CObj::SetDisarm()
{
	m_pWeapon = NULL;
}

void CObj::DrawPos() const
{
	TCHAR szBuf[128];
	swprintf_s(szBuf, L"[%.2f,%.2f]", m_vPos.x, m_vPos.y);
	
	RECT rcPos = { -30, -5, 0, 0 };
	
	_GETINST( CDevice )->GetFont()->DrawTextW( CDevice::GetInst()->GetSprite()
											, szBuf, lstrlen(szBuf), &rcPos, DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 0) );
}

void CObj::DrawIndex() const
{
	TCHAR szBuf[128];
	swprintf_s(szBuf, L"[%d,%d]", m_pt.x, m_pt.y);
	
	RECT rcPos = { -16, -5, 0, 0 };
	
	_GETINST( CDevice )->GetFont()->DrawTextW( CDevice::GetInst()->GetSprite()
											, szBuf, lstrlen(szBuf), &rcPos, DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 0) );
}

void CObj::DrawDepth() const
{
	TCHAR szBuf[128];
	swprintf_s(szBuf, L"[%d]", m_iDepth);
	
	RECT rcPos = { -16, -5, 0, 0 };
	
	_GETINST( CDevice )->GetFont()->DrawTextW( CDevice::GetInst()->GetSprite()
											, szBuf, lstrlen(szBuf), &rcPos, DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 0) );
}

void CObj::DrawHP() const
{
	TCHAR szBuf[128];
	swprintf_s(szBuf, L"[%d]", m_iHP);
	
	RECT rcPos = { -16, -5, 0, 0 };
	
	D3DXMATRIXA16		matTemp, matTrans;
	D3DXMatrixIdentity( &matTemp );
	D3DXMatrixTranslation( &matTrans, m_vPos.x, m_vPos.y, m_vPos.z );

	matTemp = matTrans;

	_GETINST( CDevice )->GetSprite()->SetTransform( &matTemp );
	_GETINST( CDevice )->GetFont()->DrawTextW( CDevice::GetInst()->GetSprite()
											, szBuf, lstrlen(szBuf), &rcPos, DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 0) );
}


void CObj::MoveToIndex()
{
	m_vPos	= D3DXVECTOR3( (BACKBUFSIZEX >> 1) + m_fDegree / 2.0f * int(m_pt.y - m_pt.x)
						 , (BACKBUFSIZEY >> 3) + m_fDegree / 2.0f * int(m_pt.y + m_pt.x)
						 , 0.0f );
}

void CObj::PosToIndex()
{
	m_pt.x = (( ( 2 * ((long)m_vPos.y - (BACKBUFSIZEY >> 3))) / (long)m_fDegree) - ( (2 * ((long)m_vPos.x - (BACKBUFSIZEX >> 1))) / (long)m_fDegree) ) / 2;
	m_pt.y = (( ( 2 * ((long)m_vPos.y - (BACKBUFSIZEY >> 3))) / (long)m_fDegree) + ( (2 * ((long)m_vPos.x - (BACKBUFSIZEX >> 1))) / (long)m_fDegree) ) / 2;
}

void CObj::SetTileIndex()
{
	m_iTileIndex		= m_pt.x * AMOUNTY + m_pt.y;
}

_BOOL CObj::CheckSumIndex(_INT ix, _INT iy)
{
	_INT iIndex = ix * AMOUNTY + iy;
	
	if ( iIndex < 0 || iIndex > AMOUNTX * AMOUNTY - 1 )
	{
		return FALSE;
	}
	else
	{
		m_iTileIndex = iIndex;
		return TRUE;
	}
}

void CObj::DrawColiBox() const
{
	D3DXMATRIXA16		matTemp;
	
	D3DXMatrixIdentity( &matTemp );
	
	D3DXVECTOR3 vCenter( float(m_rcColi.right - m_rcColi.left) / 2
					   , float(m_rcColi.bottom - m_rcColi.top) / 2, 0.0f );

	D3DXVECTOR3 vTemp = m_vPos;
	vTemp.y = vTemp.y - m_fSizeY / 2.0f;

	_GETINST( CDevice )->GetSprite()->SetTransform( &matTemp );
	_GETINST( CDevice )->GetSprite()->Draw( (*m_pvecTex)[TI_UI][UI_COLIBOX][DEFAULT][0]->pTex
										  , &m_rcColi, &vCenter, &vTemp
										  , D3DCOLOR_ARGB(100, 255, 255, 255) );
}

void CObj::DrawColiBoxF(D3DXVECTOR3 vCenter)
{
	D3DXMATRIXA16		matTemp;
	D3DXMatrixIdentity( &matTemp );

	D3DXVECTOR3 vTemp;
	vTemp.x = float(m_rcColi.right - m_rcColi.left) / 2;
	vTemp.y = float(m_rcColi.bottom - m_rcColi.top) / 2;

	_GETINST( CDevice )->GetSprite()->SetTransform( &matTemp );
	_GETINST( CDevice )->GetSprite()->Draw( (*m_pvecTex)[TI_UI][UI_COLIBOX][DEFAULT][0]->pTex
										  , &m_rcColi, &m_vCenter, &m_vPos
										  , D3DCOLOR_ARGB(100, 255, 255, 255) );
}

void CObj::DrawColiBox(RECT* prc) const
{
	D3DXMATRIXA16		matTemp;
	
	D3DXMatrixIdentity( &matTemp );
	
	D3DXVECTOR3 vCenter( (*m_pvecTex)[m_dwTexID][MI_ICON][0][0]->vCen.x
					   , (*m_pvecTex)[m_dwTexID][MI_ICON][0][0]->vCen.y, 0.0f );

	_GETINST( CDevice )->GetSprite()->SetTransform( &matTemp );
	_GETINST( CDevice )->GetSprite()->Draw( (*m_pvecTex)[TI_UI][UI_COLIBOX][DEFAULT][0]->pTex
										  , prc, &vCenter, &m_vInvenPos
										  , D3DCOLOR_ARGB(100, 255, 255, 255) );
}

void CObj::SetDepth(_INT iDepth)
{
	m_iDepth += iDepth;
}

_INT CObj::GetDepth() const
{
	return m_iDepth;
}

void CObj::DelFlag(STATE_ID ID)
{
	m_dwState &= ~ID;
}

void CObj::AddFlag(STATE_ID ID)
{
	m_dwState |= ID;
}

void CObj::SetDepthPos()
{
	_INT iIndex = m_pt.x * AMOUNTY + m_pt.y;	
	m_vPos.y -= 13 * (*_GETINST( CObjStorage )->GetTileVec())[iIndex]->GetDepth();
}

void CObj::SetTarget(CObj* pTarget)
{
	m_pTarget = pTarget;
}

void CObj::ClearTarget()
{
	m_pTarget = NULL;
}

void CObj::SetAction(_INT iAction)
{
	m_iAction = iAction;
}

void CObj::SetInvenPos(_INT ix, _INT iy)
{
	m_vInvenPos.x = float( ix );
	m_vInvenPos.y = float( iy ); 
	m_vInvenPos.z = 0.0f;
}