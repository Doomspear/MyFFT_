#include "StdAfx.h"
#include "ViewHandle.h"
#include "Includes.h"

CViewHandle*	CViewHandle::m_pInst = NULL;

CViewHandle::CViewHandle(void)
: m_pViewObj ( NULL )
{
}

CViewHandle::~CViewHandle(void)
{
	delete m_pViewObj;
	m_pViewObj = NULL;
}

void CViewHandle::SetView( MIDDLE_ID ID )
{
	delete m_pViewObj;
	m_pViewObj = NULL;
	
	switch( ID )
	{
	case VI_LOGO:
		m_pViewObj = new LOGO;
		break;

	case VI_MENU:
		m_pViewObj = new MYMENU;
		break;

	case VI_EDIT:
		m_pViewObj = new EDITMAP;
		break;

	case VI_PLAY:
		m_pViewObj = new PLAY;
		break;
	}

	m_pViewObj->Init();
}

CViewObj* CViewHandle::GetView() const
{
	return m_pViewObj;
}