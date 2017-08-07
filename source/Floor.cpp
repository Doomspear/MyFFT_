#include "StdAfx.h"
#include "Floor.h"
#include "Includes.h"

CFloor::CFloor(void)
{
}

CFloor::CFloor(_INT ix, _INT iy)
{
	ZeroMemory(this, 0);
	//���� �ٴ��� ������ ��ġ (Complete House�� ���� �����ð�)
	m_pt.x		= ix;
	m_pt.y		= iy;
	m_iAlpha	= 255;
}

CFloor::~CFloor(void)
{
	Release();
}

void CFloor::Init()
{
	//��� ��ü���� ��ġ�� ����ָ鼭 ���Ϳ� �����Ѵ�
	for ( _INT i = 0; i < 6; ++i )
	{
		for ( _INT j = 0; j < 6; ++j )
		{
			m_listFloor.push_back( CObjFactory<POSTSTONE>::CreateObj( m_pt.x + i, m_pt.y + j ) );
		}
	}

	m_listFloor.push_back( CObjFactory<WOODENBOARD>::CreateObj( m_pt.x + 0, m_pt.y + 0, 8) );
	m_listFloor.push_back( CObjFactory<WOODENBOARD>::CreateObj( m_pt.x + 5, m_pt.y + 5, 5) );
	m_listFloor.push_back( CObjFactory<WOODENBOARD>::CreateObj( m_pt.x + 5, m_pt.y + 0, 6) );
	m_listFloor.push_back( CObjFactory<WOODENBOARD>::CreateObj( m_pt.x + 0, m_pt.y + 5, 7) );

	//sideline
	for ( _INT i = 1; i < 5; ++i ) 
	{
		m_listFloor.push_back( CObjFactory<WOODENBOARD>::CreateObj( m_pt.x, m_pt.y + i, 4) );	
	}
	for ( _INT i = 1; i < 5; ++i ) 
	{
		m_listFloor.push_back( CObjFactory<WOODENBOARD>::CreateObj( m_pt.x + i, m_pt.y, 1) );	
	}
	for ( _INT i = 1; i < 5; ++i ) 
	{
		m_listFloor.push_back( CObjFactory<WOODENBOARD>::CreateObj( m_pt.x + 5, m_pt.y + i, 2) );	
	}
	for ( _INT i = 1; i < 5; ++i ) 
	{
		m_listFloor.push_back( CObjFactory<WOODENBOARD>::CreateObj( m_pt.x + i, m_pt.y + 5, 3) );	
	}
	
	//center
	for ( _INT i = 1; i < 5; ++i ) 
	{
		m_listFloor.push_back( CObjFactory<WOODENBOARD>::CreateObj( m_pt.x + 1, m_pt.y + i, 0) );	
	}
	for ( _INT i = 1; i < 5; ++i ) 
	{
		m_listFloor.push_back( CObjFactory<WOODENBOARD>::CreateObj( m_pt.x + 2, m_pt.y + i, 0) );	
	}
	for ( _INT i = 1; i < 5; ++i ) 
	{
		m_listFloor.push_back( CObjFactory<WOODENBOARD>::CreateObj( m_pt.x + 3, m_pt.y + i, 0) );	
	}
	for ( _INT i = 1; i < 5; ++i ) 
	{
		m_listFloor.push_back( CObjFactory<WOODENBOARD>::CreateObj( m_pt.x + 4, m_pt.y + i, 0) );	
	}

	m_listFloor.push_back( CObjFactory<POSTSTONE>::CreateObj( m_pt.x + 6, m_pt.y + 1, 1) );	
	m_listFloor.push_back( CObjFactory<POSTSTONE>::CreateObj( m_pt.x + 6, m_pt.y + 2, 2) );	
	m_listFloor.push_back( CObjFactory<POSTSTONE>::CreateObj( m_pt.x + 6, m_pt.y + 3, 3) );	
}

void CFloor::Progress()
{
	//��ü���� ��ġ�� ��ũ�Ѱ��� ���δ�
	for ( m_iter = m_listFloor.begin(); m_iter != m_listFloor.end(); ++m_iter )
	{
		(*m_iter)->Progress();
	}
}

void CFloor::Render()
{
	//��ü���� �Ѹ���
	for ( m_iter = m_listFloor.begin(); m_iter != m_listFloor.end(); ++m_iter )
	{
		PSTATICOBJ( (*m_iter) )->SetAlpha( m_iAlpha );
		(*m_iter)->Render();
	}

}

void CFloor::Release()
{
	//��ü���� �����
	for ( m_iter = m_listFloor.begin(); m_iter != m_listFloor.end(); ++m_iter )
	{
		delete (*m_iter);	
		(*m_iter) = NULL;
	}	
	m_listFloor.clear();
}

list< POBJ >* CFloor::GetFloorList()
{
	return &m_listFloor;
}