#include "StdAfx.h"
#include "Roof.h"
#include "Includes.h"

CRoof::CRoof(void)
{
}

CRoof::CRoof(_INT ix, _INT iy)
{
	m_pt.x	 	= ix;
	m_pt.y	 	= iy;	
	m_iAlpha	= 255;
}

CRoof::~CRoof(void)
{
	Release();
}

void CRoof::Init()
{
	for ( _UINT i = 0; i < 7; ++i )
	{
		m_listRoof.push_back( CObjFactory<SHINGLE>::CreateObj( m_pt.x + i, m_pt.y + 0, 2, 0) );
	}

	for ( _UINT i = 0; i < 7; ++i )
	{
		m_listRoof.push_back( CObjFactory<SHINGLE>::CreateObj( m_pt.x + i, m_pt.y + 1, 2, 1 ) );
	}

	for ( _UINT i = 0; i < 7; ++i )
	{
		m_listRoof.push_back( CObjFactory<SHINGLE>::CreateObj( m_pt.x + i, m_pt.y + 2, 2, 2 ) );
	}

	for ( _UINT i = 0; i < 7; ++i )
	{
		m_listRoof.push_back( CObjFactory<SHINGLE>::CreateObj( m_pt.x + i, m_pt.y + 3, 0, 3 ) );
	}

	for ( _UINT i = 0; i < 7; ++i )
	{
		m_listRoof.push_back( CObjFactory<SHINGLE>::CreateObj( m_pt.x + i, m_pt.y + 4, 1, 2 ) );
	}

	for ( _UINT i = 0; i < 7; ++i )
	{
		m_listRoof.push_back( CObjFactory<SHINGLE>::CreateObj( m_pt.x + i, m_pt.y + 5, 1, 1 ) );
	}

	for ( _UINT i = 0; i < 7; ++i )
	{
		m_listRoof.push_back( CObjFactory<SHINGLE>::CreateObj( m_pt.x + i, m_pt.y + 6, 1, 0 ) );
	}
}

void CRoof::Progress()
{
	for ( m_iter = m_listRoof.begin(); m_iter != m_listRoof.end(); ++m_iter )
	{
		PSHINGLE(*m_iter)->SetAlpha( m_iAlpha );
		(*m_iter)->Progress();
	}
}

void CRoof::Render()
{
	for ( m_iter = m_listRoof.begin(); m_iter != m_listRoof.end(); ++m_iter )
	{
		(*m_iter)->Render();
	}
}

void CRoof::Release()
{
	for ( m_iter = m_listRoof.begin(); m_iter != m_listRoof.end(); ++m_iter )
	{
		delete (*m_iter);
		(*m_iter) = NULL;
	}
	m_listRoof.clear();
}

list<POBJ>* CRoof::GetRoofList()
{
	return &m_listRoof;
}