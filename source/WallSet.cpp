#include "StdAfx.h"
#include "WallSet.h"
#include "Includes.h"

CWallSet::CWallSet(void)
{
}

CWallSet::CWallSet(_INT ix, _INT iy)
{
	//���� �ٴ��� ������ ��ġ (Complete House�� ���� �����ð�)
	m_pt.x		= ix;
	m_pt.y		= iy;
	m_iAlpha	= 255;
}

CWallSet::~CWallSet(void)
{
	Release();
}

void CWallSet::Init()
{
	//��� ��ü���� ��ġ�� ����ָ鼭 ���Ϳ� �����Ѵ�
	//sideline (left, top, right, bottom)
	
	//0, 0
	m_listWall.push_back( CObjFactory<WALL>::CreateObj( m_pt.x, m_pt.y, 12) );	
	m_listWall.push_back( CObjFactory<WALL>::CreateObj( m_pt.x, m_pt.y, 9) );
	m_listWall.push_back( CObjFactory<WALL>::CreateObj( m_pt.x, m_pt.y, 15) );
		
	//x, 0 (left)
	for ( _INT i = 1; i < 5; ++i ) 
	{
		m_listWall.push_back( CObjFactory<WALL>::CreateObj( m_pt.x + i, m_pt.y, 10) );	
	}
	m_listWall.push_back( CObjFactory<WALL>::CreateObj( m_pt.x, m_pt.y + 1, 14) );	
	m_listWall.push_back( CObjFactory<WALL>::CreateObj( m_pt.x, m_pt.y + 2, 13) );	
	m_listWall.push_back( CObjFactory<WALL>::CreateObj( m_pt.x, m_pt.y + 3, 14) );	
	m_listWall.push_back( CObjFactory<WALL>::CreateObj( m_pt.x, m_pt.y + 4, 14) );	
	m_listWall.push_back( CObjFactory<WALL>::CreateObj( m_pt.x, m_pt.y + 5, 14) );	
	m_listWall.push_back( CObjFactory<WALL>::CreateObj( m_pt.x, m_pt.y + 5, 6) );	
	m_listWall.push_back( CObjFactory<WALL>::CreateObj( m_pt.x + 1, m_pt.y + 5, 3) );
	m_listWall.push_back( CObjFactory<WALL>::CreateObj( m_pt.x + 2, m_pt.y + 5, 7) );
	m_listWall.push_back( CObjFactory<WALL>::CreateObj( m_pt.x + 3, m_pt.y + 5, 3) );
	m_listWall.push_back( CObjFactory<WALL>::CreateObj( m_pt.x + 4, m_pt.y + 5, 3) );
	
	m_listWall.push_back( CObjFactory<WALL>::CreateObj( m_pt.x + 5, m_pt.y + 0, 11) );
	m_listWall.push_back( CObjFactory<WALL>::CreateObj( m_pt.x + 5, m_pt.y + 0, 4) );
	m_listWall.push_back( CObjFactory<WALL>::CreateObj( m_pt.x + 5, m_pt.y + 1, 1) );

	m_listWall.push_back( CObjFactory<DOOR>::CreateObj( m_pt.x + 5, m_pt.y + 2, 0 ) );

	m_listWall.push_back( CObjFactory<WALL>::CreateObj( m_pt.x + 5, m_pt.y + 3, 4) );
	m_listWall.push_back( CObjFactory<WALL>::CreateObj( m_pt.x + 5, m_pt.y + 4, 2) );
	m_listWall.push_back( CObjFactory<WALL>::CreateObj( m_pt.x + 5, m_pt.y + 5, 0) );
		
}

void CWallSet::Progress()
{
	_DWORD dwKey = _GETINST( CKeyChecker )->GetKeyState();
	
	if ( dwKey & KEY_PGUP )
	{
		m_iAlpha -= 1;
	}
	if ( dwKey & KEY_PGDN )
	{
		m_iAlpha += 1;
	}

	//��ü���� ��ġ�� ��ũ�Ѱ��� ���δ�
	for ( m_iter = m_listWall.begin(); m_iter != m_listWall.end(); ++m_iter )
	{
		(*m_iter)->Progress();
	}
}

void CWallSet::Render()
{
	//��ü���� �Ѹ���
	for ( m_iter = m_listWall.begin(); m_iter != m_listWall.end(); ++m_iter )
	{
		PSTATICOBJ( (*m_iter) )->SetAlpha( m_iAlpha );
		(*m_iter)->Render();
	}
}

void CWallSet::Release()
{
	//��ü���� �����
	for ( m_iter = m_listWall.begin(); m_iter != m_listWall.end(); ++m_iter )
	{
		delete (*m_iter);
		(*m_iter) = NULL;
	}
	m_listWall.clear();
}

list<POBJ>* CWallSet::GetWallList()
{
	return &m_listWall;
}