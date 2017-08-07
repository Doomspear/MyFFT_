#include "StdAfx.h"
#include "Item.h"

CItem::CItem(void)
{
}

CItem::~CItem(void)
{
}

void CItem::SetIconColi(void)
{
	POINT ptCenter = { long( (*m_pvecTex)[m_dwTexID][MI_ICON][0][0]->vCen.x )
					 , long( (*m_pvecTex)[m_dwTexID][MI_ICON][0][0]->vCen.y ) };

	SetRect( &m_rcIcon, int( m_vPos.x - ( ptCenter.x / 2 ) )
					  , int( m_vPos.y - ( ptCenter.y) )
					  , int( m_vPos.x + ( ptCenter.x / 2 ) )
					  , int( m_vPos.y + ( ptCenter.y) ) );
 }

void CItem::SetIconColi(_INT i)
{
	SetRect( &m_rcIcon, 0, 0, 0, 0 );
}