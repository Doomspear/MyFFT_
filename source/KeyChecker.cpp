#include "StdAfx.h"
#include "KeyChecker.h"
#include "Includes.h"

CKeyChecker* CKeyChecker::m_pInst = NULL;

CKeyChecker::CKeyChecker(void)
{
	m_DbClickTime	= GetTickCount();
	m_bPressed		= false;
}

CKeyChecker::~CKeyChecker(void)
{
}

_DWORD CKeyChecker::GetKeyState()
{
	if ( m_DbClickTime + 400 < GetTickCount() )
	{
		m_DbClickTime = GetTickCount();
		m_listDbClick.clear();
	}

	_DWORD dwKey		= 0x00000000;

	if ( GetAsyncKeyState( VK_SPACE ) & 0x8000 )
	{
		dwKey |= KEY_SPACE; 
	}
	if ( GetAsyncKeyState( VK_LBUTTON ) & 0x8000 )
	{
		dwKey |= KEY_LBUTTON;
		if ( m_bPressed == true )
		{	
			//do nothing
		}
		else
		{
			m_bPressed = true;
			if ( m_listDbClick.empty() == true )
			{
				m_listDbClick.push_back( 0 );
			}
			else
			{
				if ( PMOUSE( _GETINST( CObjStorage )->GetMouse() )->GetPastPt() == true )
					m_listDbClick.push_back( 0 );
			}
		}
	}
	else
		m_bPressed = false;

	if ( GetAsyncKeyState( VK_LEFT ) & 0x8000 )
	{
		dwKey |= KEY_LEFT;
	}
	if ( GetAsyncKeyState( VK_RIGHT ) & 0x8000 )
	{
		dwKey |= KEY_RIGHT;
	}
	if ( GetAsyncKeyState( VK_UP ) & 0x8000 )
	{
		dwKey |= KEY_UP;
	}
	if ( GetAsyncKeyState( VK_DOWN ) & 0x8000 )
	{
		dwKey |= KEY_DOWN;
	}	
	if ( GetAsyncKeyState( VK_BACK ) & 0x8000 )
	{
		dwKey |= KEY_BACKSPACE;
	}
	if ( GetAsyncKeyState( VK_RETURN ) & 0x8000 )
	{
		dwKey |= KEY_RETURN;
	}
	if ( GetAsyncKeyState( VK_RBUTTON ) & 0x8000 )
	{
		dwKey |= KEY_RBUTTON;
	}
	if ( GetAsyncKeyState( VK_DELETE ) & 0x8000 )
	{
		dwKey |= KEY_DELETE;
	}
	if ( GetAsyncKeyState( VK_PRIOR ) & 0x8000 )
	{
		dwKey |= KEY_PGUP;
	}
	if ( GetAsyncKeyState( VK_NEXT ) & 0x8000 )
	{
		dwKey |= KEY_PGDN;
	}
	if ( GetAsyncKeyState( VK_CONTROL ) & 0x8000 )
	{
		dwKey |= KEY_CTRL;
	}	
	if ( GetAsyncKeyState( VK_MENU ) & 0x8000 )
	{
		dwKey |= KEY_ALT;
	}	
	if ( GetAsyncKeyState( 'C' ) & 0x8000 )
	{
		dwKey |= KEY_C;
	}
	if ( GetAsyncKeyState( VK_TAB ) & 0x8000 )
	{
		dwKey |= KEY_TAB;
	}
	if ( GetAsyncKeyState( 'I' ) & 0x8000 )
	{
		dwKey |= KEY_I;
	}

	return dwKey;
}

_BOOL CKeyChecker::CheckDbClick()
{
	if ( m_listDbClick.size() >= 2 )
	{
		return true;
	}
	else
		return false;
}