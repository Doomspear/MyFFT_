#include "StdAfx.h"
#include "Device.h"

CDevice* CDevice::m_pInst = NULL;

CDevice::CDevice(void)
: m_pD3D		( NULL )
, m_pD3DDevice9	( NULL )
, m_pD3DXSprite	( NULL )
, m_pFont		( NULL )
{
	m_rcView.left	= 0;
	m_rcView.right	= WINSIZEX;
	m_rcView.top	= 0;
	m_rcView.bottom	= WINSIZEY;
}

CDevice::~CDevice(void)
{
	Release();
}

HRESULT CDevice::Init(WIN_MODE MODE)
{
	m_pD3D = Direct3DCreate9( D3D_SDK_VERSION );
	
	D3DCAPS9	Caps;
	ZeroMemory( &Caps, sizeof(Caps) );
	
	if ( FAILED( m_pD3D->GetDeviceCaps( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &Caps ) ) )
	{
		MessageBox(g_hWnd, L"장치 초기화 실패 (SDK 버젼 정보 일치하지 않음)", L"SYSTEM ERROR", MB_OK);
		return E_FAIL;
	}

	_DWORD	vp	= 0x00000000;

	if ( Caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT )
	{
		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	}
	else
	{
		vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	}

	D3DPRESENT_PARAMETERS	d3dpp;
	ZeroMemory( &d3dpp, sizeof(D3DPRESENT_PARAMETERS) );
	
	d3dpp.BackBufferCount				= 1;
	d3dpp.BackBufferWidth				= WINSIZEX; 
	d3dpp.BackBufferHeight				= WINSIZEY;
	d3dpp.BackBufferFormat				= D3DFMT_A8R8G8B8;
	
	d3dpp.MultiSampleType				= D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality			= 0;

	d3dpp.SwapEffect					= D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow					= g_hWnd;
	d3dpp.Windowed						= MODE;
	
	d3dpp.EnableAutoDepthStencil		= true;
	d3dpp.AutoDepthStencilFormat		= D3DFMT_D24S8;

	d3dpp.Flags							= 0;

	d3dpp.FullScreen_RefreshRateInHz	= D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval			= D3DPRESENT_INTERVAL_IMMEDIATE;

	D3DXFONT_DESC	d3dFont;
	ZeroMemory( &d3dFont, sizeof(d3dFont) );

	d3dFont.Width			= 8;
	d3dFont.Height			= 8;
	d3dFont.Quality			= 1;
	d3dFont.PitchAndFamily	= 0x0004;
	
	lstrcpy( d3dFont.FaceName, L"굴림" );
	d3dFont.CharSet	= HANGUL_CHARSET;

	if ( FAILED( m_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_hWnd, vp, &d3dpp, &m_pD3DDevice9 ) ) )
	{
		MessageBox( g_hWnd, L"장치 생성 실패", L"SYSTEM ERROR", MB_OK );
		return E_FAIL;
	}

	if ( FAILED( D3DXCreateSprite( m_pD3DDevice9, &m_pD3DXSprite) ) )
	{
		MessageBox( g_hWnd, L"스프라이트 생성 실패", L"SYSTEM ERROR", MB_OK);
		return E_FAIL;
	}

	if ( FAILED( D3DXCreateFontIndirect( m_pD3DDevice9, &d3dFont, &m_pFont ) ) )
	{
		MessageBox( g_hWnd, L"폰트 생성 실패", L"SYSTEM ERROR", MB_OK );
		return E_FAIL;
	}

	return S_OK;
}

LPDIRECT3DDEVICE9 CDevice::GetDevice() const
{
	return m_pD3DDevice9;
}

LPD3DXSPRITE CDevice::GetSprite() const
{
	return m_pD3DXSprite;
}

LPD3DXFONT	CDevice::GetFont() const
{
	return m_pFont;
}

RECT* CDevice::GetRect()
{
	return &m_rcView;
}

void CDevice::Release()
{
	m_pFont->Release();
	m_pD3DXSprite->Release();
	m_pD3DDevice9->Release();
	m_pD3D->Release();
}

