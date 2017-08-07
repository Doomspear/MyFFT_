#include "StdAfx.h"
#include "TextureLoader.h"
#include "Includes.h"

CTextureLoader* CTextureLoader::m_pInst = NULL;

CTextureLoader::CTextureLoader(void)
{
	m_pTexLoad			= new TEXTURE;
	m_pTexLoad->vCen	= D3DXVECTOR3( WINSIZEX / 2, WINSIZEY / 2, 0.0f );

	D3DXIMAGE_INFO	Info;
	D3DXGetImageInfoFromFile( L"../Texture/View/Logo/Logo2.png", &Info );

	D3DXCreateTextureFromFileEx( CDevice::GetInst()->GetDevice()
							   , L"../Texture/View/Logo/Logo2.png"
				  			   , Info.Width
				  			   , Info.Height
							   , Info.MipLevels
							   , 0
							   , Info.Format
							   , D3DPOOL_MANAGED
							   , D3DX_FILTER_NONE
							   , D3DX_FILTER_NONE
							   , 0//D3DCOLOR_XRGB(255, 255, 255)
							   , &Info
							   , NULL
							   , &m_pTexLoad->pTex );
}

CTextureLoader::~CTextureLoader(void)
{
	Release();
}

PTEXTURE CTextureLoader::LoadTexture(TCHAR* pFileName, D3DXVECTOR3 vCenter = D3DXVECTOR3(0.0f, 0.0f, 0.0f))
{
	D3DXMATRIXA16	matWorld;
	D3DXMATRIXA16	matTrans;

	D3DXMatrixTranslation( &matWorld, WINSIZEX / 2, WINSIZEY / 2, 0.0f );
	D3DXMatrixIdentity( &matWorld );
		
	matWorld = matTrans;

	CDevice::GetInst()->GetSprite()->SetTransform( &matWorld );
	CDevice::GetInst()->GetSprite()->Draw( m_pTexLoad->pTex
										 , NULL
										 , &m_pTexLoad->vCen
										 , NULL
										 , D3DCOLOR_ARGB(255, 255, 255, 255) );
	
	//matWorld = matTrans;

	//CDevice::GetInst()->GetSprite()->SetTransform( &matWorld );
	//CDevice::GetInst()->GetFont()->DrawTextW( CDevice::GetInst()->GetSprite()
	//										, pFileName
	//										, lstrlen(pFileName)
	//										, NULL
	//										, DT_NOCLIP
	//										, D3DCOLOR_ARGB( 255, 255, 255, 0 ) );
	
	PTEXTURE	pTexture = new TEXTURE;
	
	TCHAR	szFailed[128] = { L"Load Failed : " };

	lstrcat(szFailed, pFileName);
	
	D3DXIMAGE_INFO	Info;
	D3DXGetImageInfoFromFile( pFileName, &Info );

	if ( FAILED( D3DXCreateTextureFromFileEx( CDevice::GetInst()->GetDevice()
											, pFileName
							  				, Info.Width
							  				, Info.Height
							  				, Info.MipLevels
							  				, 0
							  				, Info.Format
							  				, D3DPOOL_MANAGED
							  				, D3DX_FILTER_NONE
											, D3DX_FILTER_NONE
							  				, 0//D3DCOLOR_XRGB(255, 255, 255)
							  				, &Info
							  				, NULL
											, &pTexture->pTex ) ) )
	{
		MessageBox(g_hWnd, szFailed, L"SYSTEM ERROR", MB_OK);
		return NULL;
	}
	
	pTexture->vCen.x = vCenter.x / 2.0f;
	pTexture->vCen.y = vCenter.y;
	pTexture->vCen.z = 0.0f;
	
	return pTexture;
}

vector<PTEXTURE> (*CTextureLoader::GetTextureVector())[TI_END][MI_END][DI_END]
{
	return &m_vecTex;
}

HRESULT CTextureLoader::Init()
{
	//그냥 대충 여기서 사운드 로딩해버림
	//사운드 버려
	/*CSoundDevice::GetInst()->LoadWave(L"../Sound/dragon2.wav");
	CSoundDevice::GetInst()->SoundPlay(0, 1);*/

	//단일 이미지 벡터 이미지셋팅

	//Logo, Menu
	m_vecTex[TI_VIEW][VI_LOGO][DEFAULT].push_back( LoadTexture( L"../Texture/View/Logo/UO_Logo.png" ) );
	m_vecTex[TI_VIEW][VI_MENU][DEFAULT].push_back( LoadTexture( L"../Texture/View/Menu/UO_Menu.png" ) );
	
	//Start Button 
	m_vecTex[TI_UI][UI_BUTTON][BTN_START].push_back( LoadTexture( L"../Texture/View/Menu/Button/Britania_0.png") );
	m_vecTex[TI_UI][UI_BUTTON][BTN_START].push_back( LoadTexture( L"../Texture/View/Menu/Button/Britania_1.png") );
	m_vecTex[TI_UI][UI_BUTTON][BTN_START].push_back( LoadTexture( L"../Texture/View/Menu/Button/Britania_2.png") );

	//Tile
	m_vecTex[TI_OBJ][OI_TILE][TT_DEFAULT].push_back( LoadTexture( L"../Texture/Static Object/Tile/Tile_Default.png" ) );
	m_vecTex[TI_OBJ][OI_TILE][TT_GRASS].push_back( LoadTexture( L"../Texture/Static Object/Tile/Grass.png" ) );
	m_vecTex[TI_OBJ][OI_TILE][TT_DUNGEON].push_back( LoadTexture( L"../Texture/Static Object/Tile/Dungeon_floor.png" ) );

	//Mouse Cursor
	m_vecTex[TI_UI][UI_MOUSE][CI_PEACE_UP_LEFT].push_back( LoadTexture( L"../Texture/UI/Mouse/Cursor Peace Up-Left.png") );
	m_vecTex[TI_UI][UI_MOUSE][CI_WAR_UP_LEFT].push_back( LoadTexture( L"../Texture/UI/Mouse/Cursor War Up-Left.png") );

	//SelectBox
	m_vecTex[TI_UI][UI_SELECTBOX][DEFAULT].push_back( LoadTexture( L"../Texture/UI/SelectBox/SelectBox.png" ) );
	m_vecTex[TI_UI][UI_COLIBOX][DEFAULT].push_back( LoadTexture( L"../Texture/UI/ColiBox.png" ) );
		
	//Character
	LoadStaticObj();
	LoadCharacter();	
	LoadItem();
	LoadUI();
	
	return S_OK;
}

void CTextureLoader::LoadStaticObj()
{
	Small_Wood_and_Plaster_House();
	Trees();
	Bloods();
}

void CTextureLoader::LoadCharacter()
{
	Woman();
	//Vendor();
	//Chicken();
	Daemon();
	Troll();
	BladeSprits();
	Dragon();
	Titan();
}

void CTextureLoader::LoadItem()
{
	//DeathShroud();
	Robe();
	Halberd();
}

void CTextureLoader::LoadUI()
{
	//UI
	m_vecTex[TI_UI][UI_INVEN][0].push_back( LoadTexture( L"../Texture/UI/BackPack.png", D3DXVECTOR3(230.0f, 204.0f, 0.0f) ) );
	m_vecTex[TI_UI][UI_LOOT][0].push_back( LoadTexture( L"../Texture/UI/Loot.png", D3DXVECTOR3(144.0f, 212.0f, 0.0f) ) );
}

void CTextureLoader::Halberd()
{
	//MI_ATTACK_TWOHAND_DOWN
	//MI_ATTACK_TWOHAND_WIDE
	//MI_DIE
	//MI_RUN_ARMED
	//MI_STAND
	//MI_STAND_TWOHAND_ATTACK
	//MI_TAKE_HIT
	//MI_WALK_ARMED
	//MI_WALK_ATTACKPOS

	TCHAR szBuf[128];
	
	//MI_ICON
	wsprintf(szBuf, L"../Texture/Object/Halberd/Icon/halberd.png");
	m_vecTex[TI_HALBERD][MI_ICON][DI_DOWN].push_back( LoadTexture( szBuf, D3DXVECTOR3(54.0f, 45.0f, 0.0f) ) );

	//MI_ATTACK_TWOHAND_DOWN
	m_vecTex[TI_HALBERD][MI_ATTACK_TWOHAND_DOWN][DI_DOWN].reserve( 7 );
	for ( int i = 0; i < 7; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Halberd/Attack.Two handed.Down/Down0%d.png", i);
		m_vecTex[TI_HALBERD][MI_ATTACK_TWOHAND_DOWN][DI_DOWN].push_back( LoadTexture( szBuf, D3DXVECTOR3(98.0f, 88.0f, 0.0f) ) );
	}
	m_vecTex[TI_HALBERD][MI_ATTACK_TWOHAND_DOWN][DI_DOWNLEFT].reserve( 7 );
	for ( int i = 0; i < 7; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Halberd/Attack.Two handed.Down/Down-Left0%d.png", i);
		m_vecTex[TI_HALBERD][MI_ATTACK_TWOHAND_DOWN][DI_DOWNLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(120.0f, 94.0f, 0.0f) ) );
	}
	m_vecTex[TI_HALBERD][MI_ATTACK_TWOHAND_DOWN][DI_LEFT].reserve( 7 );
	for ( int i = 0; i < 7; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Halberd/Attack.Two handed.Down/Left0%d.png", i);
		m_vecTex[TI_HALBERD][MI_ATTACK_TWOHAND_DOWN][DI_LEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(115.0f, 98.0f, 0) ) );
	}
	m_vecTex[TI_HALBERD][MI_ATTACK_TWOHAND_DOWN][DI_UP].reserve( 7 );
	for ( int i = 0; i < 7; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Halberd/Attack.Two handed.Down/Up0%d.png", i);
		m_vecTex[TI_HALBERD][MI_ATTACK_TWOHAND_DOWN][DI_UP].push_back( LoadTexture( szBuf, D3DXVECTOR3(38.0f, 82.0f, 0) ) );
	}
	m_vecTex[TI_HALBERD][MI_ATTACK_TWOHAND_DOWN][DI_UPLEFT].reserve( 7 );
	for ( int i = 0; i < 7; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Halberd/Attack.Two handed.Down/Up-Left0%d.png", i);
		m_vecTex[TI_HALBERD][MI_ATTACK_TWOHAND_DOWN][DI_UPLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(50.0f, 94.0f, 0) ) );
	}

	//MI_ATTACK_TWOHAND_WIDE
	m_vecTex[TI_HALBERD][MI_ATTACK_TWOHAND_WIDE][DI_DOWN].reserve( 7 );
	for ( int i = 0; i < 7; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Halberd/Attack.Two handed.Wide/Down0%d.png", i);
		m_vecTex[TI_HALBERD][MI_ATTACK_TWOHAND_WIDE][DI_DOWN].push_back( LoadTexture( szBuf, D3DXVECTOR3(124.0f, 72.0f, 0.0f) ) );
	}
	m_vecTex[TI_HALBERD][MI_ATTACK_TWOHAND_WIDE][DI_DOWNLEFT].reserve( 7 );
	for ( int i = 0; i < 7; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Halberd/Attack.Two handed.Wide/Down-Left0%d.png", i);
		m_vecTex[TI_HALBERD][MI_ATTACK_TWOHAND_WIDE][DI_DOWNLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(112.0f, 74.0f, 0.0f) ) );
	}
	m_vecTex[TI_HALBERD][MI_ATTACK_TWOHAND_WIDE][DI_LEFT].reserve( 7 );
	for ( int i = 0; i < 7; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Halberd/Attack.Two handed.Wide/Left0%d.png", i);
		m_vecTex[TI_HALBERD][MI_ATTACK_TWOHAND_WIDE][DI_LEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(136.0f, 70.0f, 0) ) );
	}
	m_vecTex[TI_HALBERD][MI_ATTACK_TWOHAND_WIDE][DI_UP].reserve( 7 );
	for ( int i = 0; i < 7; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Halberd/Attack.Two handed.Wide/Up0%d.png", i);
		m_vecTex[TI_HALBERD][MI_ATTACK_TWOHAND_WIDE][DI_UP].push_back( LoadTexture( szBuf, D3DXVECTOR3(56.0f, 74.0f, 0) ) );
	}
	m_vecTex[TI_HALBERD][MI_ATTACK_TWOHAND_WIDE][DI_UPLEFT].reserve( 7 );
	for ( int i = 0; i < 7; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Halberd/Attack.Two handed.Wide/Up-Left0%d.png", i);
		m_vecTex[TI_HALBERD][MI_ATTACK_TWOHAND_WIDE][DI_UPLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(84.0f, 68.0f, 0) ) );
	}

	//MI_DIE
	m_vecTex[TI_HALBERD][MI_DIE][DI_DOWN].reserve( 6 );
	for ( int i = 0; i < 6; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Halberd/die/Down0%d.png", i);
		m_vecTex[TI_HALBERD][MI_DIE][DI_DOWN].push_back( LoadTexture( szBuf, D3DXVECTOR3(1.0f, 36.0f, 0.0f) ) );
	}
	m_vecTex[TI_HALBERD][MI_DIE][DI_DOWNLEFT].reserve( 6 );
	for ( int i = 0; i < 6; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Halberd/die/Down-Left0%d.png", i);
		m_vecTex[TI_HALBERD][MI_DIE][DI_DOWNLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(110.0f, 36.0f, 0.0f) ) );
	}
	m_vecTex[TI_HALBERD][MI_DIE][DI_LEFT].reserve( 6 );
	for ( int i = 0; i < 6; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Halberd/die/Left0%d.png", i);
		m_vecTex[TI_HALBERD][MI_DIE][DI_LEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(169.0f, 52.0f, 0) ) );
	}
	m_vecTex[TI_HALBERD][MI_DIE][DI_UP].reserve( 6 );
	for ( int i = 0; i < 6; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Halberd/die/Up0%d.png", i);
		m_vecTex[TI_HALBERD][MI_DIE][DI_UP].push_back( LoadTexture( szBuf, D3DXVECTOR3(82.0f, 72.0f, 0) ) );
	}
	m_vecTex[TI_HALBERD][MI_DIE][DI_UPLEFT].reserve( 6 );
	for ( int i = 0; i < 6; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Halberd/die/Up-Left0%d.png", i);
		m_vecTex[TI_HALBERD][MI_DIE][DI_UPLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(150.0f, 66.0f, 0) ) );
	}

	//MI_RUN_ARMED
	m_vecTex[TI_HALBERD][MI_RUN_ARMED][DI_DOWN].reserve( 10 );
	for ( int i = 0; i < 10; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Halberd/Run armed/Down0%d.png", i);
		m_vecTex[TI_HALBERD][MI_RUN_ARMED][DI_DOWN].push_back( LoadTexture( szBuf, D3DXVECTOR3(2.0f, 70.0f, 0.0f) ) );
	}
	m_vecTex[TI_HALBERD][MI_RUN_ARMED][DI_DOWNLEFT].reserve( 10 );
	for ( int i = 0; i < 10; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Halberd/Run armed/Down-Left0%d.png", i);
		m_vecTex[TI_HALBERD][MI_RUN_ARMED][DI_DOWNLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(40.0f, 68.0f, 0.0f) ) );
	}
	m_vecTex[TI_HALBERD][MI_RUN_ARMED][DI_LEFT].reserve( 10 );
	for ( int i = 0; i < 10; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Halberd/Run armed/Left0%d.png", i);
		m_vecTex[TI_HALBERD][MI_RUN_ARMED][DI_LEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(58.0f, 68.0f, 0) ) );
	}
	m_vecTex[TI_HALBERD][MI_RUN_ARMED][DI_UP].reserve( 10 );
	for ( int i = 0; i < 10; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Halberd/Run armed/Up0%d.png", i);
		m_vecTex[TI_HALBERD][MI_RUN_ARMED][DI_UP].push_back( LoadTexture( szBuf, D3DXVECTOR3(36.0f, 84.0f, 0) ) );
	}
	m_vecTex[TI_HALBERD][MI_RUN_ARMED][DI_UPLEFT].reserve( 10 );
	for ( int i = 0; i < 10; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Halberd/Run armed/Up-Left0%d.png", i);
		m_vecTex[TI_HALBERD][MI_RUN_ARMED][DI_UPLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(52.0f, 80.0f, 0) ) );
	}

	//MI_STAND
	m_vecTex[TI_HALBERD][MI_STAND][DI_DOWN].reserve( 1 );
	for ( int i = 0; i < 1; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Halberd/Stand/Down0%d.png", i);
		m_vecTex[TI_HALBERD][MI_STAND][DI_DOWN].push_back( LoadTexture( szBuf, D3DXVECTOR3(-15.0f, 65.0f, 0.0f) ) );
	}
	m_vecTex[TI_HALBERD][MI_STAND][DI_DOWNLEFT].reserve( 1 );
	for ( int i = 0; i < 1; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Halberd/Stand/Down-Left0%d.png", i);
		m_vecTex[TI_HALBERD][MI_STAND][DI_DOWNLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(16.0f, 65.0f, 0.0f) ) );
	}
	m_vecTex[TI_HALBERD][MI_STAND][DI_LEFT].reserve( 1 );
	for ( int i = 0; i < 1; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Halberd/Stand/Left0%d.png", i);
		m_vecTex[TI_HALBERD][MI_STAND][DI_LEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(37.0f, 65.0f, 0) ) );
	}
	m_vecTex[TI_HALBERD][MI_STAND][DI_UP].reserve( 1 );
	for ( int i = 0; i < 1; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Halberd/Stand/Up0%d.png", i);
		m_vecTex[TI_HALBERD][MI_STAND][DI_UP].push_back( LoadTexture( szBuf, D3DXVECTOR3(28.0f, 68.0f, 0) ) );
	}
	m_vecTex[TI_HALBERD][MI_STAND][DI_UPLEFT].reserve( 1 );
	for ( int i = 0; i < 1; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Halberd/Stand/Up-Left0%d.png", i);
		m_vecTex[TI_HALBERD][MI_STAND][DI_UPLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(40.0f, 70.0f, 0) ) );
	}

	//MI_STAND_TWOHAND_ATTACK
	m_vecTex[TI_HALBERD][MI_STAND_TWOHAND_ATTACK][DI_DOWN].reserve( 1 );
	for ( int i = 0; i < 1; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Halberd/Stand for two handed attack/Down0%d.png", i);
		m_vecTex[TI_HALBERD][MI_STAND_TWOHAND_ATTACK][DI_DOWN].push_back( LoadTexture( szBuf, D3DXVECTOR3(66.0f, 70.0f, 0.0f) ));
	}
	m_vecTex[TI_HALBERD][MI_STAND_TWOHAND_ATTACK][DI_DOWNLEFT].reserve( 1 );
	for ( int i = 0; i < 1; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Halberd/Stand for two handed attack/Down-Left0%d.png", i);
		m_vecTex[TI_HALBERD][MI_STAND_TWOHAND_ATTACK][DI_DOWNLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(24.0f, 80.0f, 0.0f) ) );
	}
	m_vecTex[TI_HALBERD][MI_STAND_TWOHAND_ATTACK][DI_LEFT].reserve( 1 );
	for ( int i = 0; i < 1; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Halberd/Stand for two handed attack/Left0%d.png", i);
		m_vecTex[TI_HALBERD][MI_STAND_TWOHAND_ATTACK][DI_LEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(30.0f, 70.0f, 0) ) );
	}
	m_vecTex[TI_HALBERD][MI_STAND_TWOHAND_ATTACK][DI_UP].reserve( 1 );
	for ( int i = 0; i < 1; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Halberd/Stand for two handed attack/Up0%d.png", i);
		m_vecTex[TI_HALBERD][MI_STAND_TWOHAND_ATTACK][DI_UP].push_back( LoadTexture( szBuf, D3DXVECTOR3(10.0f, 44.0f, 0) ) );
	}
	m_vecTex[TI_HALBERD][MI_STAND_TWOHAND_ATTACK][DI_UPLEFT].reserve( 1 );
	for ( int i = 0; i < 1; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Halberd/Stand for two handed attack/Up-Left0%d.png", i);
		m_vecTex[TI_HALBERD][MI_STAND_TWOHAND_ATTACK][DI_UPLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(36.0f, 54.0f, 0) ) );
	}

	//MI_TAKE_HIT
	m_vecTex[TI_HALBERD][MI_TAKE_HIT][DI_DOWN].reserve( 5 );
	for ( int i = 0; i < 5; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Halberd/Take Hit/Down0%d.png", i);
		m_vecTex[TI_HALBERD][MI_TAKE_HIT][DI_DOWN].push_back( LoadTexture( szBuf, D3DXVECTOR3(0.0f, 82.0f, 0.0f) ) );
	}
	m_vecTex[TI_HALBERD][MI_TAKE_HIT][DI_DOWNLEFT].reserve( 5 );
	for ( int i = 0; i < 5; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Halberd/Take Hit/Down-Left0%d.png", i);
		m_vecTex[TI_HALBERD][MI_TAKE_HIT][DI_DOWNLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(30.0f, 78.0f, 0.0f) ) );
	}
	m_vecTex[TI_HALBERD][MI_TAKE_HIT][DI_LEFT].reserve( 5 );
	for ( int i = 0; i < 5; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Halberd/Take Hit/Left0%d.png", i);
		m_vecTex[TI_HALBERD][MI_TAKE_HIT][DI_LEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(60.0f, 72.0f, 0) ) );
	}
	m_vecTex[TI_HALBERD][MI_TAKE_HIT][DI_UP].reserve( 5 );
	for ( int i = 0; i < 5; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Halberd/Take Hit/Up0%d.png", i);
		m_vecTex[TI_HALBERD][MI_TAKE_HIT][DI_UP].push_back( LoadTexture( szBuf, D3DXVECTOR3(40.0f, 80.0f, 0) ) );
	}
	m_vecTex[TI_HALBERD][MI_TAKE_HIT][DI_UPLEFT].reserve( 5 );
	for ( int i = 0; i < 5; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Halberd/Take Hit/Up-Left0%d.png", i);
		m_vecTex[TI_HALBERD][MI_TAKE_HIT][DI_UPLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(62.0f, 74.0f, 0) ) );
	}

	//MI_WALK_ARMED
	m_vecTex[TI_HALBERD][MI_WALK_ARMED][DI_DOWN].reserve( 10 );
	for ( int i = 0; i < 10; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Halberd/Walk armed/Down0%d.png", i);
		m_vecTex[TI_HALBERD][MI_WALK_ARMED][DI_DOWN].push_back( LoadTexture( szBuf, D3DXVECTOR3(-10.0f, 82.0f, 0.0f) ) );
	}
	m_vecTex[TI_HALBERD][MI_WALK_ARMED][DI_DOWNLEFT].reserve( 10 );
	for ( int i = 0; i < 10; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Halberd/Walk armed/Down-Left0%d.png", i);
		m_vecTex[TI_HALBERD][MI_WALK_ARMED][DI_DOWNLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(14.0f, 70.0f, 0.0f) ) );
	}
	m_vecTex[TI_HALBERD][MI_WALK_ARMED][DI_LEFT].reserve( 10 );
	for ( int i = 0; i < 10; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Halberd/Walk armed/Left0%d.png", i);
		m_vecTex[TI_HALBERD][MI_WALK_ARMED][DI_LEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(48.0f, 72.0f, 0) ) );
	}
	m_vecTex[TI_HALBERD][MI_WALK_ARMED][DI_UP].reserve( 10 );
	for ( int i = 0; i < 10; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Halberd/Walk armed/Up0%d.png", i);
		m_vecTex[TI_HALBERD][MI_WALK_ARMED][DI_UP].push_back( LoadTexture( szBuf, D3DXVECTOR3(34.0f, 84.0f, 0) ) );
	}
	m_vecTex[TI_HALBERD][MI_WALK_ARMED][DI_UPLEFT].reserve( 10 );
	for ( int i = 0; i < 10; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Halberd/Walk armed/Up-Left0%d.png", i);
		m_vecTex[TI_HALBERD][MI_WALK_ARMED][DI_UPLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(50.0f, 80.0f, 0) ) );
	}

	//MI_WALK_ATTACKPOS
	m_vecTex[TI_HALBERD][MI_WALK_ATTACKPOS][DI_DOWN].reserve( 10 );
	for ( int i = 0; i < 10; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Halberd/Walk in attack position/Down0%d.png", i);
		m_vecTex[TI_HALBERD][MI_WALK_ATTACKPOS][DI_DOWN].push_back( LoadTexture( szBuf, D3DXVECTOR3(50.0f, 80.0f, 0.0f) ) );
	}

	m_vecTex[TI_HALBERD][MI_WALK_ATTACKPOS][DI_DOWNLEFT].reserve( 10 );
	for ( int i = 0; i < 10; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Halberd/Walk in attack position/Down-Left0%d.png", i);
		m_vecTex[TI_HALBERD][MI_WALK_ATTACKPOS][DI_DOWNLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(50.0f, 80.0f, 0.0f) ) );
	}

	m_vecTex[TI_HALBERD][MI_WALK_ATTACKPOS][DI_LEFT].reserve( 10 );
	for ( int i = 0; i < 10; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Halberd/Walk in attack position/Left0%d.png", i);
		m_vecTex[TI_HALBERD][MI_WALK_ATTACKPOS][DI_LEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(50.0f, 66.0f, 0) ) );
	}

	m_vecTex[TI_HALBERD][MI_WALK_ATTACKPOS][DI_UP].reserve( 10 );
	for ( int i = 0; i < 10; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Halberd/Walk in attack position/Up0%d.png", i);
		m_vecTex[TI_HALBERD][MI_WALK_ATTACKPOS][DI_UP].push_back( LoadTexture( szBuf, D3DXVECTOR3(10.0f, 52.0f, 0) ) );
	}

	m_vecTex[TI_HALBERD][MI_WALK_ATTACKPOS][DI_UPLEFT].reserve( 10 );
	for ( int i = 0; i < 10; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Halberd/Walk in attack position/Up-Left0%d.png", i);
		m_vecTex[TI_HALBERD][MI_WALK_ATTACKPOS][DI_UPLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(32.0f, 58.0f, 0) ) );
	}
}

void CTextureLoader::Robe()
{
	//MI_ATTACK_TWOHAND_DOWN
	//MI_ATTACK_TWOHAND_WIDE
	//MI_ATTACK_UNARMED
	//MI_CAST_DIRECT
	//MI_CAST_SUMMON
	//MI_DIE
	//MI_RUN_ARMED
	//MI_RUN_UNARMED
	//MI_STAND
	//MI_STAND_TWOHAND_ATTACK
	//MI_TAKE_HIT
	//MI_WALK_ARMED
	//MI_WALK_UNARMED
	//MI_WALK_ATTACKPOS

	TCHAR szBuf[128];

	//MI_ICON
	m_vecTex[TI_ROBE][MI_ICON][DI_DOWN].push_back( LoadTexture( L"../Texture/Object/Robe/Icon/robe.png", D3DXVECTOR3(46.0f, 47.0f, 0.0f) ) );

	//MI_ATTACK_TWOHAND_DOWN
	m_vecTex[TI_ROBE][MI_ATTACK_TWOHAND_DOWN][DI_DOWN].reserve( 7 );
	for ( int i = 0; i < 7; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Robe/Attack.Two handed.Down/Down0%d.png", i);
		m_vecTex[TI_ROBE][MI_ATTACK_TWOHAND_DOWN][DI_DOWN].push_back( LoadTexture( szBuf, D3DXVECTOR3(30.0f, 57.0f, 0.0f) ) );
	}
	m_vecTex[TI_ROBE][MI_ATTACK_TWOHAND_DOWN][DI_DOWNLEFT].reserve( 7 );
	for ( int i = 0; i < 7; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Robe/Attack.Two handed.Down/Down-Left0%d.png", i);
		m_vecTex[TI_ROBE][MI_ATTACK_TWOHAND_DOWN][DI_DOWNLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(26.0f, 56.0f, 0.0f) ) );
	}
	m_vecTex[TI_ROBE][MI_ATTACK_TWOHAND_DOWN][DI_LEFT].reserve( 7 );
	for ( int i = 0; i < 7; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Robe/Attack.Two handed.Down/Left0%d.png", i);
		m_vecTex[TI_ROBE][MI_ATTACK_TWOHAND_DOWN][DI_LEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(36.0f, 57.0f, 0) ) );
	}
	m_vecTex[TI_ROBE][MI_ATTACK_TWOHAND_DOWN][DI_UP].reserve( 7 );
	for ( int i = 0; i < 7; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Robe/Attack.Two handed.Down/Up0%d.png", i);
		m_vecTex[TI_ROBE][MI_ATTACK_TWOHAND_DOWN][DI_UP].push_back( LoadTexture( szBuf, D3DXVECTOR3(38.0f, 60.0f, 0) ) );
	}
	m_vecTex[TI_ROBE][MI_ATTACK_TWOHAND_DOWN][DI_UPLEFT].reserve( 7 );
	for ( int i = 0; i < 7; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Robe/Attack.Two handed.Down/Up-Left0%d.png", i);
		m_vecTex[TI_ROBE][MI_ATTACK_TWOHAND_DOWN][DI_UPLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(44.0f, 58.0f, 0) ) );
	}

	//MI_ATTACK_TWOHAND_WIDE
	m_vecTex[TI_ROBE][MI_ATTACK_TWOHAND_WIDE][DI_DOWN].reserve( 7 );
	for ( int i = 0; i < 7; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Robe/Attack.Two handed.Wide/Down0%d.png", i);
		m_vecTex[TI_ROBE][MI_ATTACK_TWOHAND_WIDE][DI_DOWN].push_back( LoadTexture( szBuf, D3DXVECTOR3(42.0f, 52.0f, 0.0f) ) );
	}
	m_vecTex[TI_ROBE][MI_ATTACK_TWOHAND_WIDE][DI_DOWNLEFT].reserve( 7 );
	for ( int i = 0; i < 7; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Robe/Attack.Two handed.Wide/Down-Left0%d.png", i);
		m_vecTex[TI_ROBE][MI_ATTACK_TWOHAND_WIDE][DI_DOWNLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(34.0f, 52.0f, 0.0f) ) );
	}
	m_vecTex[TI_ROBE][MI_ATTACK_TWOHAND_WIDE][DI_LEFT].reserve( 7 );
	for ( int i = 0; i < 7; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Robe/Attack.Two handed.Wide/Left0%d.png", i);
		m_vecTex[TI_ROBE][MI_ATTACK_TWOHAND_WIDE][DI_LEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(40.0f, 51.0f, 0) ) );
	}
	m_vecTex[TI_ROBE][MI_ATTACK_TWOHAND_WIDE][DI_UP].reserve( 7 );
	for ( int i = 0; i < 7; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Robe/Attack.Two handed.Wide/Up0%d.png", i);
		m_vecTex[TI_ROBE][MI_ATTACK_TWOHAND_WIDE][DI_UP].push_back( LoadTexture( szBuf, D3DXVECTOR3(34.0f, 54.0f, 0) ) );
	}
	m_vecTex[TI_ROBE][MI_ATTACK_TWOHAND_WIDE][DI_UPLEFT].reserve( 7 );
	for ( int i = 0; i < 7; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Robe/Attack.Two handed.Wide/Up-Left0%d.png", i);
		m_vecTex[TI_ROBE][MI_ATTACK_TWOHAND_WIDE][DI_UPLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(39.0f, 52.0f, 0) ) );
	}

	//MI_ATTACK_UNARMED
	m_vecTex[TI_ROBE][MI_ATTACK_UNARMED][DI_DOWN].reserve( 7 );
	for ( int i = 0; i < 7; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Robe/Attack.Unarmed/Down0%d.png", i);
		m_vecTex[TI_ROBE][MI_ATTACK_UNARMED][DI_DOWN].push_back( LoadTexture( szBuf, D3DXVECTOR3(32.0f, 62.0f, 0.0f) ) );
	}
	m_vecTex[TI_ROBE][MI_ATTACK_UNARMED][DI_DOWNLEFT].reserve( 7 );
	for ( int i = 0; i < 7; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Robe/Attack.Unarmed/Down-Left0%d.png", i);
		m_vecTex[TI_ROBE][MI_ATTACK_UNARMED][DI_DOWNLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(45.0f, 62.0f, 0.0f) ) );
	}
	m_vecTex[TI_ROBE][MI_ATTACK_UNARMED][DI_LEFT].reserve( 7 );
	for ( int i = 0; i < 7; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Robe/Attack.Unarmed/Left0%d.png", i);
		m_vecTex[TI_ROBE][MI_ATTACK_UNARMED][DI_LEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(38.0f, 57.0f, 0) ) );
	}
	m_vecTex[TI_ROBE][MI_ATTACK_UNARMED][DI_UP].reserve( 7 );
	for ( int i = 0; i < 7; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Robe/Attack.Unarmed/Up0%d.png", i);
		m_vecTex[TI_ROBE][MI_ATTACK_UNARMED][DI_UP].push_back( LoadTexture( szBuf, D3DXVECTOR3(38.0f, 55.0f, 0) ) );
	}
	m_vecTex[TI_ROBE][MI_ATTACK_UNARMED][DI_UPLEFT].reserve( 7 );
	for ( int i = 0; i < 7; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Robe/Attack.Unarmed/Up-Left0%d.png", i);
		m_vecTex[TI_ROBE][MI_ATTACK_UNARMED][DI_UPLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(50.0f, 55.0f, 0) ) );
	}

	//MI_CAST_DIRECT
	m_vecTex[TI_ROBE][MI_CAST_DIRECT][DI_DOWN].reserve( 7 );
	for ( int i = 0; i < 7; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Robe/Cast.Directed/Down0%d.png", i);
		m_vecTex[TI_ROBE][MI_CAST_DIRECT][DI_DOWN].push_back( LoadTexture( szBuf, D3DXVECTOR3(34.0f, 56.0f, 0.0f) ) );
	}
	m_vecTex[TI_ROBE][MI_CAST_DIRECT][DI_DOWNLEFT].reserve( 7 );
	for ( int i = 0; i < 7; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Robe/Cast.Directed/Down-Left0%d.png", i);
		m_vecTex[TI_ROBE][MI_CAST_DIRECT][DI_DOWNLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(68.0f, 56.0f, 0.0f) ) );
	}
	m_vecTex[TI_ROBE][MI_CAST_DIRECT][DI_LEFT].reserve( 7 );
	for ( int i = 0; i < 7; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Robe/Cast.Directed/Left0%d.png", i);
		m_vecTex[TI_ROBE][MI_CAST_DIRECT][DI_LEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(68.0f, 60.0f, 0) ) );
	}
	m_vecTex[TI_ROBE][MI_CAST_DIRECT][DI_UP].reserve( 7 );
	for ( int i = 0; i < 7; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Robe/Cast.Directed/Up0%d.png", i);
		m_vecTex[TI_ROBE][MI_CAST_DIRECT][DI_UP].push_back( LoadTexture( szBuf, D3DXVECTOR3(41.0f, 55.0f, 0) ) );
	}
	m_vecTex[TI_ROBE][MI_CAST_DIRECT][DI_UPLEFT].reserve( 7 );
	for ( int i = 0; i < 7; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Robe/Cast.Directed/Up-Left0%d.png", i);
		m_vecTex[TI_ROBE][MI_CAST_DIRECT][DI_UPLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(48.0f, 54.0f, 0) ) );
	}

	//MI_CAST_SUMMON
	m_vecTex[TI_ROBE][MI_CAST_SUMMON][DI_DOWN].reserve( 7 );
	for ( int i = 0; i < 7; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Robe/Cast.Summon/Down0%d.png", i);
		m_vecTex[TI_ROBE][MI_CAST_SUMMON][DI_DOWN].push_back( LoadTexture( szBuf, D3DXVECTOR3(42.0f, 60.0f, 0.0f) ) );
	}
	m_vecTex[TI_ROBE][MI_CAST_SUMMON][DI_DOWNLEFT].reserve( 7 );
	for ( int i = 0; i < 7; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Robe/Cast.Summon/Down-Left0%d.png", i);
		m_vecTex[TI_ROBE][MI_CAST_SUMMON][DI_DOWNLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(35.0f, 63.0f, 0.0f) ) );
	}
	m_vecTex[TI_ROBE][MI_CAST_SUMMON][DI_LEFT].reserve( 7 );
	for ( int i = 0; i < 7; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Robe/Cast.Summon/Left0%d.png", i);
		m_vecTex[TI_ROBE][MI_CAST_SUMMON][DI_LEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(28.0f, 68.0f, 0) ) );
	}
	m_vecTex[TI_ROBE][MI_CAST_SUMMON][DI_UP].reserve( 7 );
	for ( int i = 0; i < 7; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Robe/Cast.Summon/Up0%d.png", i);
		m_vecTex[TI_ROBE][MI_CAST_SUMMON][DI_UP].push_back( LoadTexture( szBuf, D3DXVECTOR3(47.0f, 61.0f, 0) ) );
	}
	m_vecTex[TI_ROBE][MI_CAST_SUMMON][DI_UPLEFT].reserve( 7 );
	for ( int i = 0; i < 7; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Robe/Cast.Summon/Up-Left0%d.png", i);
		m_vecTex[TI_ROBE][MI_CAST_SUMMON][DI_UPLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(36.0f, 64.0f, 0) ) );
	}
	
	//MI_DIE
	m_vecTex[TI_ROBE][MI_DIE][DI_DOWN].reserve( 6 );
	for ( int i = 0; i < 6; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Robe/die/Down0%d.png", i);
		m_vecTex[TI_ROBE][MI_DIE][DI_DOWN].push_back( LoadTexture( szBuf, D3DXVECTOR3(39.0f, 53.0f, 0.0f) ) );
	}
	m_vecTex[TI_ROBE][MI_DIE][DI_DOWNLEFT].reserve( 6 );
	for ( int i = 0; i < 6; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Robe/die/Down-Left0%d.png", i);
		m_vecTex[TI_ROBE][MI_DIE][DI_DOWNLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(108.0f, 54.0f, 0.0f) ) );
	}
	m_vecTex[TI_ROBE][MI_DIE][DI_LEFT].reserve( 6 );
	for ( int i = 0; i < 6; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Robe/die/Left0%d.png", i);
		m_vecTex[TI_ROBE][MI_DIE][DI_LEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(109.0f, 55.0f, 0) ) );
	}
	m_vecTex[TI_ROBE][MI_DIE][DI_UP].reserve( 6 );
	for ( int i = 0; i < 6; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Robe/die/Up0%d.png", i);
		m_vecTex[TI_ROBE][MI_DIE][DI_UP].push_back( LoadTexture( szBuf, D3DXVECTOR3(49.0f, 46.0f, 0) ) );
	}
	m_vecTex[TI_ROBE][MI_DIE][DI_UPLEFT].reserve( 6 );
	for ( int i = 0; i < 6; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Robe/die/Up-Left0%d.png", i);
		m_vecTex[TI_ROBE][MI_DIE][DI_UPLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(110.0f, 51.0f, 0) ) );
	}

	//MI_RUN_ARMED
	m_vecTex[TI_ROBE][MI_RUN_ARMED][DI_DOWN].reserve( 10 );
	for ( int i = 0; i < 10; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Robe/Run armed/Down0%d.png", i);
		m_vecTex[TI_ROBE][MI_RUN_ARMED][DI_DOWN].push_back( LoadTexture( szBuf, D3DXVECTOR3(32.0f, 58.0f, 0.0f) ) );
	}
	m_vecTex[TI_ROBE][MI_RUN_ARMED][DI_DOWNLEFT].reserve( 10 );
	for ( int i = 0; i < 10; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Robe/Run armed/Down-Left0%d.png", i);
		m_vecTex[TI_ROBE][MI_RUN_ARMED][DI_DOWNLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(46.0f, 56.0f, 0.0f) ) );
	}
	m_vecTex[TI_ROBE][MI_RUN_ARMED][DI_LEFT].reserve( 10 );
	for ( int i = 0; i < 10; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Robe/Run armed/Left0%d.png", i);
		m_vecTex[TI_ROBE][MI_RUN_ARMED][DI_LEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(54.0f, 56.0f, 0) ) );
	}
	m_vecTex[TI_ROBE][MI_RUN_ARMED][DI_UP].reserve( 10 );
	for ( int i = 0; i < 10; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Robe/Run armed/Up0%d.png", i);
		m_vecTex[TI_ROBE][MI_RUN_ARMED][DI_UP].push_back( LoadTexture( szBuf, D3DXVECTOR3(30.0f, 60.0f, 0) ) );
	}
	m_vecTex[TI_ROBE][MI_RUN_ARMED][DI_UPLEFT].reserve( 10 );
	for ( int i = 0; i < 10; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Robe/Run armed/Up-Left0%d.png", i);
		m_vecTex[TI_ROBE][MI_RUN_ARMED][DI_UPLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(46.0f, 58.0f, 0) ) );
	}

	//MI_RUN_UNARMED
	m_vecTex[TI_ROBE][MI_RUN_UNARMED][DI_DOWN].reserve( 10 );
	for ( int i = 0; i < 10; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Robe/Run unarmed/Down0%d.png", i);
		m_vecTex[TI_ROBE][MI_RUN_UNARMED][DI_DOWN].push_back( LoadTexture( szBuf, D3DXVECTOR3(32.0f, 58.0f, 0.0f) ) );
	}
	m_vecTex[TI_ROBE][MI_RUN_UNARMED][DI_DOWNLEFT].reserve( 10 );
	for ( int i = 0; i < 10; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Robe/Run unarmed/Down-Left0%d.png", i);
		m_vecTex[TI_ROBE][MI_RUN_UNARMED][DI_DOWNLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(48.0f, 56.0f, 0.0f) ) );
	}
	m_vecTex[TI_ROBE][MI_RUN_UNARMED][DI_LEFT].reserve( 10 );
	for ( int i = 0; i < 10; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Robe/Run unarmed/Left0%d.png", i);
		m_vecTex[TI_ROBE][MI_RUN_UNARMED][DI_LEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(54.0f, 56.0f, 0) ) );
	}
	m_vecTex[TI_ROBE][MI_RUN_UNARMED][DI_UP].reserve( 10 );
	for ( int i = 0; i < 10; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Robe/Run unarmed/Up0%d.png", i);
		m_vecTex[TI_ROBE][MI_RUN_UNARMED][DI_UP].push_back( LoadTexture( szBuf, D3DXVECTOR3(30.0f, 60.0f, 0) ) );
	}
	m_vecTex[TI_ROBE][MI_RUN_UNARMED][DI_UPLEFT].reserve( 10 );
	for ( int i = 0; i < 10; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Robe/Run unarmed/Up-Left0%d.png", i);
		m_vecTex[TI_ROBE][MI_RUN_UNARMED][DI_UPLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(48.0f, 58.0f, 0) ) );
	}

	//MI_STAND
	m_vecTex[TI_ROBE][MI_STAND][DI_DOWN].reserve( 1 );
	for ( int i = 0; i < 1; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Robe/Stand/Down0%d.png", i);
		m_vecTex[TI_ROBE][MI_STAND][DI_DOWN].push_back( LoadTexture( szBuf, D3DXVECTOR3(22.0f, 56.0f, 0.0f) ) );
	}
	m_vecTex[TI_ROBE][MI_STAND][DI_DOWNLEFT].reserve( 1 );
	for ( int i = 0; i < 1; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Robe/Stand/Down-Left0%d.png", i);
		m_vecTex[TI_ROBE][MI_STAND][DI_DOWNLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(21.0f, 58.0f, 0.0f) ) );
	}
	m_vecTex[TI_ROBE][MI_STAND][DI_LEFT].reserve( 1 );
	for ( int i = 0; i < 1; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Robe/Stand/Left0%d.png", i);
		m_vecTex[TI_ROBE][MI_STAND][DI_LEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(15.0f, 57.0f, 0) ) );
	}
	m_vecTex[TI_ROBE][MI_STAND][DI_UP].reserve( 1 );
	for ( int i = 0; i < 1; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Robe/Stand/Up0%d.png", i);
		m_vecTex[TI_ROBE][MI_STAND][DI_UP].push_back( LoadTexture( szBuf, D3DXVECTOR3(28.0f, 56.0f, 0) ) );
	}
	m_vecTex[TI_ROBE][MI_STAND][DI_UPLEFT].reserve( 1 );
	for ( int i = 0; i < 1; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Robe/Stand/Up-Left0%d.png", i);
		m_vecTex[TI_ROBE][MI_STAND][DI_UPLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(24.0f, 57.0f, 0) ) );
	}

	//MI_STAND_TWOHAND_ATTACK
	m_vecTex[TI_ROBE][MI_STAND_TWOHAND_ATTACK][DI_DOWN].reserve( 1 );
	for ( int i = 0; i < 1; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Robe/Stand for two handed attack/Down0%d.png", i);
		m_vecTex[TI_ROBE][MI_STAND_TWOHAND_ATTACK][DI_DOWN].push_back( LoadTexture( szBuf, D3DXVECTOR3(24.0f, 50.0f, 0.0f) ));
	}
	m_vecTex[TI_ROBE][MI_STAND_TWOHAND_ATTACK][DI_DOWNLEFT].reserve( 1 );
	for ( int i = 0; i < 1; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Robe/Stand for two handed attack/Down-Left0%d.png", i);
		m_vecTex[TI_ROBE][MI_STAND_TWOHAND_ATTACK][DI_DOWNLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(24.0f, 50.0f, 0.0f) ) );
	}
	m_vecTex[TI_ROBE][MI_STAND_TWOHAND_ATTACK][DI_LEFT].reserve( 1 );
	for ( int i = 0; i < 1; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Robe/Stand for two handed attack/Left0%d.png", i);
		m_vecTex[TI_ROBE][MI_STAND_TWOHAND_ATTACK][DI_LEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(28.0f, 48.0f, 0) ) );
	}
	m_vecTex[TI_ROBE][MI_STAND_TWOHAND_ATTACK][DI_UP].reserve( 1 );
	for ( int i = 0; i < 1; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Robe/Stand for two handed attack/Up0%d.png", i);
		m_vecTex[TI_ROBE][MI_STAND_TWOHAND_ATTACK][DI_UP].push_back( LoadTexture( szBuf, D3DXVECTOR3(40.0f, 46.0f, 0) ) );
	}
	m_vecTex[TI_ROBE][MI_STAND_TWOHAND_ATTACK][DI_UPLEFT].reserve( 1 );
	for ( int i = 0; i < 1; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Robe/Stand for two handed attack/Up-Left0%d.png", i);
		m_vecTex[TI_ROBE][MI_STAND_TWOHAND_ATTACK][DI_UPLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(36.0f, 46.0f, 0) ) );
	}

	//MI_TAKE_HIT
	m_vecTex[TI_ROBE][MI_TAKE_HIT][DI_DOWN].reserve( 5 );
	for ( int i = 0; i < 5; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Robe/Take Hit/Down0%d.png", i);
		m_vecTex[TI_ROBE][MI_TAKE_HIT][DI_DOWN].push_back( LoadTexture( szBuf, D3DXVECTOR3(34.0f, 52.0f, 0.0f) ) );
	}
	m_vecTex[TI_ROBE][MI_TAKE_HIT][DI_DOWNLEFT].reserve( 5 );
	for ( int i = 0; i < 5; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Robe/Take Hit/Down-Left0%d.png", i);
		m_vecTex[TI_ROBE][MI_TAKE_HIT][DI_DOWNLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(36.0f, 54.0f, 0.0f) ) );
	}
	m_vecTex[TI_ROBE][MI_TAKE_HIT][DI_LEFT].reserve( 5 );
	for ( int i = 0; i < 5; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Robe/Take Hit/Left0%d.png", i);
		m_vecTex[TI_ROBE][MI_TAKE_HIT][DI_LEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(30.0f, 52.0f, 0) ) );
	}
	m_vecTex[TI_ROBE][MI_TAKE_HIT][DI_UP].reserve( 5 );
	for ( int i = 0; i < 5; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Robe/Take Hit/Up0%d.png", i);
		m_vecTex[TI_ROBE][MI_TAKE_HIT][DI_UP].push_back( LoadTexture( szBuf, D3DXVECTOR3(38.0f, 54.0f, 0) ) );
	}
	m_vecTex[TI_ROBE][MI_TAKE_HIT][DI_UPLEFT].reserve( 5 );
	for ( int i = 0; i < 5; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Robe/Take Hit/Up-Left0%d.png", i);
		m_vecTex[TI_ROBE][MI_TAKE_HIT][DI_UPLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(38.0f, 54.0f, 0) ) );
	}

	//MI_WALK_ARMED
	m_vecTex[TI_ROBE][MI_WALK_ARMED][DI_DOWN].reserve( 10 );
	for ( int i = 0; i < 10; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Robe/Walk armed/Down0%d.png", i);
		m_vecTex[TI_ROBE][MI_WALK_ARMED][DI_DOWN].push_back( LoadTexture( szBuf, D3DXVECTOR3(30.0f, 62.0f, 0.0f) ) );
	}
	m_vecTex[TI_ROBE][MI_WALK_ARMED][DI_DOWNLEFT].reserve( 10 );
	for ( int i = 0; i < 10; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Robe/Walk armed/Down-Left0%d.png", i);
		m_vecTex[TI_ROBE][MI_WALK_ARMED][DI_DOWNLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(34.0f, 62.0f, 0.0f) ) );
	}
	m_vecTex[TI_ROBE][MI_WALK_ARMED][DI_LEFT].reserve( 10 );
	for ( int i = 0; i < 10; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Robe/Walk armed/Left0%d.png", i);
		m_vecTex[TI_ROBE][MI_WALK_ARMED][DI_LEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(42.0f, 58.0f, 0) ) );
	}
	m_vecTex[TI_ROBE][MI_WALK_ARMED][DI_UP].reserve( 10 );
	for ( int i = 0; i < 10; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Robe/Walk armed/Up0%d.png", i);
		m_vecTex[TI_ROBE][MI_WALK_ARMED][DI_UP].push_back( LoadTexture( szBuf, D3DXVECTOR3(28.0f, 60.0f, 0) ) );
	}
	m_vecTex[TI_ROBE][MI_WALK_ARMED][DI_UPLEFT].reserve( 10 );
	for ( int i = 0; i < 10; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Robe/Walk armed/Up-Left0%d.png", i);
		m_vecTex[TI_ROBE][MI_WALK_ARMED][DI_UPLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(33.0f, 60.0f, 0) ) );
	}

	//MI_WALK_UNARMED
	m_vecTex[TI_ROBE][MI_WALK_UNARMED][DI_DOWN].reserve( 10 );
	for ( int i = 0; i < 10; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Robe/Walk unarmed/Down0%d.png", i);
		m_vecTex[TI_ROBE][MI_WALK_UNARMED][DI_DOWN].push_back( LoadTexture( szBuf, D3DXVECTOR3(30.0f, 62.0f, 0.0f) ) );
	}
	m_vecTex[TI_ROBE][MI_WALK_UNARMED][DI_DOWNLEFT].reserve( 10 );
	for ( int i = 0; i < 10; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Robe/Walk unarmed/Down-Left0%d.png", i);
		m_vecTex[TI_ROBE][MI_WALK_UNARMED][DI_DOWNLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(32.0f, 62.0f, 0.0f) ) );
	}
	m_vecTex[TI_ROBE][MI_WALK_UNARMED][DI_LEFT].reserve( 10 );
	for ( int i = 0; i < 10; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Robe/Walk unarmed/Left0%d.png", i);
		m_vecTex[TI_ROBE][MI_WALK_UNARMED][DI_LEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(42.0f, 58.0f, 0) ) );
	}
	m_vecTex[TI_ROBE][MI_WALK_UNARMED][DI_UP].reserve( 10 );
	for ( int i = 0; i < 10; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Robe/Walk unarmed/Up0%d.png", i);
		m_vecTex[TI_ROBE][MI_WALK_UNARMED][DI_UP].push_back( LoadTexture( szBuf, D3DXVECTOR3(26.0f, 58.0f, 0) ) );
	}
	m_vecTex[TI_ROBE][MI_WALK_UNARMED][DI_UPLEFT].reserve( 10 );
	for ( int i = 0; i < 10; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Robe/Walk unarmed/Up-Left0%d.png", i);
		m_vecTex[TI_ROBE][MI_WALK_UNARMED][DI_UPLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(36.0f, 58.0f, 0) ) );
	}

	//MI_WALK_ATTACKPOS
	m_vecTex[TI_ROBE][MI_WALK_ATTACKPOS][DI_DOWN].reserve( 10 );
	for ( int i = 0; i < 10; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Robe/Walk in attack position/Down0%d.png", i);
		m_vecTex[TI_ROBE][MI_WALK_ATTACKPOS][DI_DOWN].push_back( LoadTexture( szBuf, D3DXVECTOR3(20.0f, 60.0f, 0.0f) ) );
	}

	m_vecTex[TI_ROBE][MI_WALK_ATTACKPOS][DI_DOWNLEFT].reserve( 10 );
	for ( int i = 0; i < 10; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Robe/Walk in attack position/Down-Left0%d.png", i);
		m_vecTex[TI_ROBE][MI_WALK_ATTACKPOS][DI_DOWNLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(36.0f, 56.0f, 0.0f) ) );
	}

	m_vecTex[TI_ROBE][MI_WALK_ATTACKPOS][DI_LEFT].reserve( 10 );
	for ( int i = 0; i < 10; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Robe/Walk in attack position/Left0%d.png", i);
		m_vecTex[TI_ROBE][MI_WALK_ATTACKPOS][DI_LEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(44.0f, 50.0f, 0) ) );
	}

	m_vecTex[TI_ROBE][MI_WALK_ATTACKPOS][DI_UP].reserve( 10 );
	for ( int i = 0; i < 10; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Robe/Walk in attack position/Up0%d.png", i);
		m_vecTex[TI_ROBE][MI_WALK_ATTACKPOS][DI_UP].push_back( LoadTexture( szBuf, D3DXVECTOR3(40.0f, 56.0f, 0) ) );
	}

	m_vecTex[TI_ROBE][MI_WALK_ATTACKPOS][DI_UPLEFT].reserve( 10 );
	for ( int i = 0; i < 10; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/Robe/Walk in attack position/Up-Left0%d.png", i);
		m_vecTex[TI_ROBE][MI_WALK_ATTACKPOS][DI_UPLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(42.0f, 52.0f, 0) ) );
	}
}

void CTextureLoader::DeathShroud()
{
	TCHAR szBuf[128];

	//MI_STAND
	m_vecTex[TI_DEATHSHROUD][MI_STAND][DI_DOWN].reserve( 1 );
	for ( int i = 0; i < 1; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/DeathShroud/Stand/Down0%d.png", i);
		m_vecTex[TI_DEATHSHROUD][MI_STAND][DI_DOWN].push_back( LoadTexture( szBuf, D3DXVECTOR3(20.0f, 63.0f, 0.0f) ) );
	}
	m_vecTex[TI_DEATHSHROUD][MI_STAND][DI_DOWNLEFT].reserve( 1 );
	for ( int i = 0; i < 1; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/DeathShroud/Stand/Down-Left0%d.png", i);
		m_vecTex[TI_DEATHSHROUD][MI_STAND][DI_DOWNLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(20.0f, 63.0f, 0.0f) ) );
	}
	m_vecTex[TI_DEATHSHROUD][MI_STAND][DI_LEFT].reserve( 1 );
	for ( int i = 0; i < 1; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/DeathShroud/Stand/Left0%d.png", i);
		m_vecTex[TI_DEATHSHROUD][MI_STAND][DI_LEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(20.0f, 63.0f, 0.0f) ) );
	}
	m_vecTex[TI_DEATHSHROUD][MI_STAND][DI_UP].reserve( 1 );
	for ( int i = 0; i < 1; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/DeathShroud/Stand/Up0%d.png", i);
		m_vecTex[TI_DEATHSHROUD][MI_STAND][DI_UP].push_back( LoadTexture( szBuf, D3DXVECTOR3(27.0f, 65.0f, 0.0f) ) );
	}
	m_vecTex[TI_DEATHSHROUD][MI_STAND][DI_UPLEFT].reserve( 1 );
	for ( int i = 0; i < 1; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/DeathShroud/Stand/Up-Left0%d.png", i);
		m_vecTex[TI_DEATHSHROUD][MI_STAND][DI_UPLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(22.0f, 64.0f, 0.0f) ) );
	}

	//MI_WALK_UNARMED
	m_vecTex[TI_DEATHSHROUD][MI_WALK_UNARMED][DI_DOWN].reserve( 10 );
	for ( int i = 0; i < 10; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/DeathShroud/Walk unarmed/Down0%d.png", i);
		m_vecTex[TI_DEATHSHROUD][MI_WALK_UNARMED][DI_DOWN].push_back( LoadTexture( szBuf, D3DXVECTOR3(30.0f, 67.0f, 0.0f) ) );
	}
	m_vecTex[TI_DEATHSHROUD][MI_WALK_UNARMED][DI_DOWNLEFT].reserve( 10 );
	for ( int i = 0; i < 10; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/DeathShroud/Walk unarmed/Down-Left0%d.png", i);
		m_vecTex[TI_DEATHSHROUD][MI_WALK_UNARMED][DI_DOWNLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(36.0f, 67.0f, 0.0f) ) );
	}
	m_vecTex[TI_DEATHSHROUD][MI_WALK_UNARMED][DI_LEFT].reserve( 10 );
	for ( int i = 0; i < 10; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/DeathShroud/Walk unarmed/Left0%d.png", i);
		m_vecTex[TI_DEATHSHROUD][MI_WALK_UNARMED][DI_LEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(42.0f, 63.0f, 0.0f) ) );
	}
	m_vecTex[TI_DEATHSHROUD][MI_WALK_UNARMED][DI_UP].reserve( 10 );
	for ( int i = 0; i < 10; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/DeathShroud/Walk unarmed/Up0%d.png", i);
		m_vecTex[TI_DEATHSHROUD][MI_WALK_UNARMED][DI_UP].push_back( LoadTexture( szBuf, D3DXVECTOR3(29.0f, 68.0f, 0.0f) ) );
	}
	m_vecTex[TI_DEATHSHROUD][MI_WALK_UNARMED][DI_UPLEFT].reserve( 10 );
	for ( int i = 0; i < 10; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/DeathShroud/Walk unarmed/Up-Left0%d.png", i);
		m_vecTex[TI_DEATHSHROUD][MI_WALK_UNARMED][DI_UPLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(36.0f, 64.0f, 0.0f) ) );
	}

	//MI_RUN_UNARMED
	m_vecTex[TI_DEATHSHROUD][MI_RUN_UNARMED][DI_DOWN].reserve( 10 );
	for ( int i = 0; i < 10; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/DeathShroud/Run unarmed/Down0%d.png", i);
		m_vecTex[TI_DEATHSHROUD][MI_RUN_UNARMED][DI_DOWN].push_back( LoadTexture( szBuf, D3DXVECTOR3(30.0f, 64.0f, 0.0f) ) );
	}
	m_vecTex[TI_DEATHSHROUD][MI_RUN_UNARMED][DI_DOWNLEFT].reserve( 10 );
	for ( int i = 0; i < 10; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/DeathShroud/Run unarmed/Down-Left0%d.png", i);
		m_vecTex[TI_DEATHSHROUD][MI_RUN_UNARMED][DI_DOWNLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(50.0f, 63.0f, 0.0f) ) );
	}
	m_vecTex[TI_DEATHSHROUD][MI_RUN_UNARMED][DI_LEFT].reserve( 10 );
	for ( int i = 0; i < 10; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/DeathShroud/Run unarmed/Left0%d.png", i);
		m_vecTex[TI_DEATHSHROUD][MI_RUN_UNARMED][DI_LEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(52.0f, 63.0f, 0.0f) ) );
	}
	m_vecTex[TI_DEATHSHROUD][MI_RUN_UNARMED][DI_UP].reserve( 10 );
	for ( int i = 0; i < 10; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/DeathShroud/Run unarmed/Up0%d.png", i);
		m_vecTex[TI_DEATHSHROUD][MI_RUN_UNARMED][DI_UP].push_back( LoadTexture( szBuf, D3DXVECTOR3(30.0f, 69.0f, 0.0f) ) );
	}
	m_vecTex[TI_DEATHSHROUD][MI_RUN_UNARMED][DI_UPLEFT].reserve( 10 );
	for ( int i = 0; i < 10; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Object/DeathShroud/Run unarmed/Up-Left0%d.png", i);
		m_vecTex[TI_DEATHSHROUD][MI_RUN_UNARMED][DI_UPLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(50.0f, 67.0f, 0.0f) ) );
	}
}

void CTextureLoader::Woman()
{
	//MI_ATTACK_TWOHAND_DOWN
	//MI_ATTACK_TWOHAND_WIDE
	//MI_ATTACK_UNARMED
	//MI_CAST_DIRECT
	//MI_CAST_SUMMON
	//MI_DIE
	//MI_RUN_ARMED
	//MI_RUN_UNARMED
	//MI_STAND
	//MI_STAND_TWOHAND_ATTACK
	//MI_TAKE_HIT
	//MI_WALK_ARMED
	//MI_WALK_UNARMED
	//MI_WALK_ATTACKPOS

	TCHAR szBuf[128];
	
	//MI_ATTACK_TWOHAND_DOWN
	m_vecTex[TI_WOMAN][MI_ATTACK_TWOHAND_DOWN][DI_DOWN].reserve( 7 );
	for ( int i = 0; i < 7; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Woman/Attack.Two handed.Down/Down0%d.png", i);
		m_vecTex[TI_WOMAN][MI_ATTACK_TWOHAND_DOWN][DI_DOWN].push_back( LoadTexture( szBuf, D3DXVECTOR3(33.0f, 62.0f, 0.0f) ) );
	}
	m_vecTex[TI_WOMAN][MI_ATTACK_TWOHAND_DOWN][DI_DOWNLEFT].reserve( 7 );
	for ( int i = 0; i < 7; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Woman/Attack.Two handed.Down/Down-Left0%d.png", i);
		m_vecTex[TI_WOMAN][MI_ATTACK_TWOHAND_DOWN][DI_DOWNLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(32.0f, 63.0f, 0.0f) ) );
	}
	m_vecTex[TI_WOMAN][MI_ATTACK_TWOHAND_DOWN][DI_LEFT].reserve( 7 );
	for ( int i = 0; i < 7; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Woman/Attack.Two handed.Down/Left0%d.png", i);
		m_vecTex[TI_WOMAN][MI_ATTACK_TWOHAND_DOWN][DI_LEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(33.0f, 60.0f, 0) ) );
	}
	m_vecTex[TI_WOMAN][MI_ATTACK_TWOHAND_DOWN][DI_UP].reserve( 7 );
	for ( int i = 0; i < 7; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Woman/Attack.Two handed.Down/Up0%d.png", i);
		m_vecTex[TI_WOMAN][MI_ATTACK_TWOHAND_DOWN][DI_UP].push_back( LoadTexture( szBuf, D3DXVECTOR3(33.0f, 60.0f, 0) ) );
	}
	m_vecTex[TI_WOMAN][MI_ATTACK_TWOHAND_DOWN][DI_UPLEFT].reserve( 7 );
	for ( int i = 0; i < 7; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Woman/Attack.Two handed.Down/Up-Left0%d.png", i);
		m_vecTex[TI_WOMAN][MI_ATTACK_TWOHAND_DOWN][DI_UPLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(34.0f, 60.0f, 0) ) );
	}

	//MI_ATTACK_TWOHAND_WIDE
	m_vecTex[TI_WOMAN][MI_ATTACK_TWOHAND_WIDE][DI_DOWN].reserve( 7 );
	for ( int i = 0; i < 7; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Woman/Attack.Two handed.Wide/Down0%d.png", i);
		m_vecTex[TI_WOMAN][MI_ATTACK_TWOHAND_WIDE][DI_DOWN].push_back( LoadTexture( szBuf, D3DXVECTOR3(42.0f, 56.0f, 0.0f) ) );
	}
	m_vecTex[TI_WOMAN][MI_ATTACK_TWOHAND_WIDE][DI_DOWNLEFT].reserve( 7 );
	for ( int i = 0; i < 7; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Woman/Attack.Two handed.Wide/Down-Left0%d.png", i);
		m_vecTex[TI_WOMAN][MI_ATTACK_TWOHAND_WIDE][DI_DOWNLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(38.0f, 56.0f, 0.0f) ) );
	}
	m_vecTex[TI_WOMAN][MI_ATTACK_TWOHAND_WIDE][DI_LEFT].reserve( 7 );
	for ( int i = 0; i < 7; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Woman/Attack.Two handed.Wide/Left0%d.png", i);
		m_vecTex[TI_WOMAN][MI_ATTACK_TWOHAND_WIDE][DI_LEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(46.0f, 55.0f, 0) ) );
	}
	m_vecTex[TI_WOMAN][MI_ATTACK_TWOHAND_WIDE][DI_UP].reserve( 7 );
	for ( int i = 0; i < 7; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Woman/Attack.Two handed.Wide/Up0%d.png", i);
		m_vecTex[TI_WOMAN][MI_ATTACK_TWOHAND_WIDE][DI_UP].push_back( LoadTexture( szBuf, D3DXVECTOR3(42.0f, 61.0f, 0) ) );
	}
	m_vecTex[TI_WOMAN][MI_ATTACK_TWOHAND_WIDE][DI_UPLEFT].reserve( 7 );
	for ( int i = 0; i < 7; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Woman/Attack.Two handed.Wide/Up-Left0%d.png", i);
		m_vecTex[TI_WOMAN][MI_ATTACK_TWOHAND_WIDE][DI_UPLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(45.0f, 58.0f, 0) ) );
	}

	//MI_ATTACK_UNARMED
	m_vecTex[TI_WOMAN][MI_ATTACK_UNARMED][DI_DOWN].reserve( 7 );
	for ( int i = 0; i < 7; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Woman/Attack.Unarmed/Down0%d.png", i);
		m_vecTex[TI_WOMAN][MI_ATTACK_UNARMED][DI_DOWN].push_back( LoadTexture( szBuf, D3DXVECTOR3(37.0f, 64.0f, 0.0f) ) );
	}
	m_vecTex[TI_WOMAN][MI_ATTACK_UNARMED][DI_DOWNLEFT].reserve( 7 );
	for ( int i = 0; i < 7; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Woman/Attack.Unarmed/Down-Left0%d.png", i);
		m_vecTex[TI_WOMAN][MI_ATTACK_UNARMED][DI_DOWNLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(45.0f, 62.0f, 0.0f) ) );
	}
	m_vecTex[TI_WOMAN][MI_ATTACK_UNARMED][DI_LEFT].reserve( 7 );
	for ( int i = 0; i < 7; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Woman/Attack.Unarmed/Left0%d.png", i);
		m_vecTex[TI_WOMAN][MI_ATTACK_UNARMED][DI_LEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(45.0f, 61.0f, 0) ) );
	}
	m_vecTex[TI_WOMAN][MI_ATTACK_UNARMED][DI_UP].reserve( 7 );
	for ( int i = 0; i < 7; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Woman/Attack.Unarmed/Up0%d.png", i);
		m_vecTex[TI_WOMAN][MI_ATTACK_UNARMED][DI_UP].push_back( LoadTexture( szBuf, D3DXVECTOR3(38.0f, 61.0f, 0) ) );
	}
	m_vecTex[TI_WOMAN][MI_ATTACK_UNARMED][DI_UPLEFT].reserve( 7 );
	for ( int i = 0; i < 7; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Woman/Attack.Unarmed/Up-Left0%d.png", i);
		m_vecTex[TI_WOMAN][MI_ATTACK_UNARMED][DI_UPLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(50.0f, 59.0f, 0) ) );
	}

	//MI_CAST_DIRECT
	m_vecTex[TI_WOMAN][MI_CAST_DIRECT][DI_DOWN].reserve( 7 );
	for ( int i = 0; i < 7; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Woman/Cast.Directed/Down0%d.png", i);
		m_vecTex[TI_WOMAN][MI_CAST_DIRECT][DI_DOWN].push_back( LoadTexture( szBuf, D3DXVECTOR3(38.0f, 60.0f, 0.0f) ) );
	}
	m_vecTex[TI_WOMAN][MI_CAST_DIRECT][DI_DOWNLEFT].reserve( 7 );
	for ( int i = 0; i < 7; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Woman/Cast.Directed/Down-Left0%d.png", i);
		m_vecTex[TI_WOMAN][MI_CAST_DIRECT][DI_DOWNLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(71.0f, 60.0f, 0.0f) ) );
	}
	m_vecTex[TI_WOMAN][MI_CAST_DIRECT][DI_LEFT].reserve( 7 );
	for ( int i = 0; i < 7; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Woman/Cast.Directed/Left0%d.png", i);
		m_vecTex[TI_WOMAN][MI_CAST_DIRECT][DI_LEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(76.0f, 62.0f, 0) ) );
	}
	m_vecTex[TI_WOMAN][MI_CAST_DIRECT][DI_UP].reserve( 7 );
	for ( int i = 0; i < 7; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Woman/Cast.Directed/Up0%d.png", i);
		m_vecTex[TI_WOMAN][MI_CAST_DIRECT][DI_UP].push_back( LoadTexture( szBuf, D3DXVECTOR3(44.0f, 62.0f, 0) ) );
	}
	m_vecTex[TI_WOMAN][MI_CAST_DIRECT][DI_UPLEFT].reserve( 7 );
	for ( int i = 0; i < 7; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Woman/Cast.Directed/Up-Left0%d.png", i);
		m_vecTex[TI_WOMAN][MI_CAST_DIRECT][DI_UPLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(50.0f, 59.0f, 0) ) );
	}

	//MI_CAST_SUMMON
	m_vecTex[TI_WOMAN][MI_CAST_SUMMON][DI_DOWN].reserve( 7 );
	for ( int i = 0; i < 7; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Woman/Cast.Summon/Down0%d.png", i);
		m_vecTex[TI_WOMAN][MI_CAST_SUMMON][DI_DOWN].push_back( LoadTexture( szBuf, D3DXVECTOR3(52.0f, 65.0f, 0.0f) ) );
	}
	m_vecTex[TI_WOMAN][MI_CAST_SUMMON][DI_DOWNLEFT].reserve( 7 );
	for ( int i = 0; i < 7; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Woman/Cast.Summon/Down-Left0%d.png", i);
		m_vecTex[TI_WOMAN][MI_CAST_SUMMON][DI_DOWNLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(42.0f, 70.0f, 0.0f) ) );
	}
	m_vecTex[TI_WOMAN][MI_CAST_SUMMON][DI_LEFT].reserve( 7 );
	for ( int i = 0; i < 7; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Woman/Cast.Summon/Left0%d.png", i);
		m_vecTex[TI_WOMAN][MI_CAST_SUMMON][DI_LEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(29.0f, 73.0f, 0) ) );
	}
	m_vecTex[TI_WOMAN][MI_CAST_SUMMON][DI_UP].reserve( 7 );
	for ( int i = 0; i < 7; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Woman/Cast.Summon/Up0%d.png", i);
		m_vecTex[TI_WOMAN][MI_CAST_SUMMON][DI_UP].push_back( LoadTexture( szBuf, D3DXVECTOR3(56.0f, 67.0f, 0) ) );
	}
	m_vecTex[TI_WOMAN][MI_CAST_SUMMON][DI_UPLEFT].reserve( 7 );
	for ( int i = 0; i < 7; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Woman/Cast.Summon/Up-Left0%d.png", i);
		m_vecTex[TI_WOMAN][MI_CAST_SUMMON][DI_UPLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(47.0f, 70.0f, 0) ) );
	}
	
	//MI_DIE
	m_vecTex[TI_WOMAN][MI_DIE][DI_DOWN].reserve( 6 );
	for ( int i = 0; i < 6; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Woman/die/Down0%d.png", i);
		m_vecTex[TI_WOMAN][MI_DIE][DI_DOWN].push_back( LoadTexture( szBuf, D3DXVECTOR3(48.0f, 60.0f, 0.0f) ) );
	}
	m_vecTex[TI_WOMAN][MI_DIE][DI_DOWNLEFT].reserve( 6 );
	for ( int i = 0; i < 6; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Woman/die/Down-Left0%d.png", i);
		m_vecTex[TI_WOMAN][MI_DIE][DI_DOWNLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(119.0f, 60.0f, 0.0f) ) );
	}
	m_vecTex[TI_WOMAN][MI_DIE][DI_LEFT].reserve( 6 );
	for ( int i = 0; i < 6; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Woman/die/Left0%d.png", i);
		m_vecTex[TI_WOMAN][MI_DIE][DI_LEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(119.0f, 60.0f, 0) ) );
	}
	m_vecTex[TI_WOMAN][MI_DIE][DI_UP].reserve( 6 );
	for ( int i = 0; i < 6; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Woman/die/Up0%d.png", i);
		m_vecTex[TI_WOMAN][MI_DIE][DI_UP].push_back( LoadTexture( szBuf, D3DXVECTOR3(56.0f, 53.0f, 0) ) );
	}
	m_vecTex[TI_WOMAN][MI_DIE][DI_UPLEFT].reserve( 6 );
	for ( int i = 0; i < 6; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Woman/die/Up-Left0%d.png", i);
		m_vecTex[TI_WOMAN][MI_DIE][DI_UPLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(119.0f, 58.0f, 0) ) );
	}

	//MI_RUN_ARMED
	m_vecTex[TI_WOMAN][MI_RUN_ARMED][DI_DOWN].reserve( 10 );
	for ( int i = 0; i < 10; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Woman/Run armed/Down0%d.png", i);
		m_vecTex[TI_WOMAN][MI_RUN_ARMED][DI_DOWN].push_back( LoadTexture( szBuf, D3DXVECTOR3(27.0f, 63.0f, 0.0f) ) );
	}
	m_vecTex[TI_WOMAN][MI_RUN_ARMED][DI_DOWNLEFT].reserve( 10 );
	for ( int i = 0; i < 10; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Woman/Run armed/Down-Left0%d.png", i);
		m_vecTex[TI_WOMAN][MI_RUN_ARMED][DI_DOWNLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(40.0f, 61.0f, 0.0f) ) );
	}
	m_vecTex[TI_WOMAN][MI_RUN_ARMED][DI_LEFT].reserve( 10 );
	for ( int i = 0; i < 10; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Woman/Run armed/Left0%d.png", i);
		m_vecTex[TI_WOMAN][MI_RUN_ARMED][DI_LEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(50.0f, 60.0f, 0) ) );
	}
	m_vecTex[TI_WOMAN][MI_RUN_ARMED][DI_UP].reserve( 10 );
	for ( int i = 0; i < 10; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Woman/Run armed/Up0%d.png", i);
		m_vecTex[TI_WOMAN][MI_RUN_ARMED][DI_UP].push_back( LoadTexture( szBuf, D3DXVECTOR3(27.0f, 68.0f, 0) ) );
	}
	m_vecTex[TI_WOMAN][MI_RUN_ARMED][DI_UPLEFT].reserve( 10 );
	for ( int i = 0; i < 10; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Woman/Run armed/Up-Left0%d.png", i);
		m_vecTex[TI_WOMAN][MI_RUN_ARMED][DI_UPLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(42.0f, 64.0f, 0) ) );
	}

	//MI_RUN_UNARMED
	m_vecTex[TI_WOMAN][MI_RUN_UNARMED][DI_DOWN].reserve( 10 );
	for ( int i = 0; i < 10; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Woman/Run unarmed/Down0%d.png", i);
		m_vecTex[TI_WOMAN][MI_RUN_UNARMED][DI_DOWN].push_back( LoadTexture( szBuf, D3DXVECTOR3(27.0f, 63.0f, 0.0f) ) );
	}
	m_vecTex[TI_WOMAN][MI_RUN_UNARMED][DI_DOWNLEFT].reserve( 10 );
	for ( int i = 0; i < 10; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Woman/Run unarmed/Down-Left0%d.png", i);
		m_vecTex[TI_WOMAN][MI_RUN_UNARMED][DI_DOWNLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(40.0f, 61.0f, 0.0f) ) );
	}
	m_vecTex[TI_WOMAN][MI_RUN_UNARMED][DI_LEFT].reserve( 10 );
	for ( int i = 0; i < 10; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Woman/Run unarmed/Left0%d.png", i);
		m_vecTex[TI_WOMAN][MI_RUN_UNARMED][DI_LEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(50.0f, 60.0f, 0) ) );
	}
	m_vecTex[TI_WOMAN][MI_RUN_UNARMED][DI_UP].reserve( 10 );
	for ( int i = 0; i < 10; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Woman/Run unarmed/Up0%d.png", i);
		m_vecTex[TI_WOMAN][MI_RUN_UNARMED][DI_UP].push_back( LoadTexture( szBuf, D3DXVECTOR3(27.0f, 68.0f, 0) ) );
	}
	m_vecTex[TI_WOMAN][MI_RUN_UNARMED][DI_UPLEFT].reserve( 10 );
	for ( int i = 0; i < 10; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Woman/Run unarmed/Up-Left0%d.png", i);
		m_vecTex[TI_WOMAN][MI_RUN_UNARMED][DI_UPLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(42.0f, 64.0f, 0) ) );
	}

	//MI_STAND
	m_vecTex[TI_WOMAN][MI_STAND][DI_DOWN].reserve( 1 );
	for ( int i = 0; i < 1; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Woman/Stand/Down0%d.png", i);
		m_vecTex[TI_WOMAN][MI_STAND][DI_DOWN].push_back( LoadTexture( szBuf, D3DXVECTOR3(20.0f, 60.0f, 0.0f) ) );
	}
	m_vecTex[TI_WOMAN][MI_STAND][DI_DOWNLEFT].reserve( 1 );
	for ( int i = 0; i < 1; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Woman/Stand/Down-Left0%d.png", i);
		m_vecTex[TI_WOMAN][MI_STAND][DI_DOWNLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(21.0f, 62.0f, 0.0f) ) );
	}
	m_vecTex[TI_WOMAN][MI_STAND][DI_LEFT].reserve( 1 );
	for ( int i = 0; i < 1; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Woman/Stand/Left0%d.png", i);
		m_vecTex[TI_WOMAN][MI_STAND][DI_LEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(17.0f, 61.0f, 0) ) );
	}
	m_vecTex[TI_WOMAN][MI_STAND][DI_UP].reserve( 1 );
	for ( int i = 0; i < 1; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Woman/Stand/Up0%d.png", i);
		m_vecTex[TI_WOMAN][MI_STAND][DI_UP].push_back( LoadTexture( szBuf, D3DXVECTOR3(25.0f, 62.0f, 0) ) );
	}
	m_vecTex[TI_WOMAN][MI_STAND][DI_UPLEFT].reserve( 1 );
	for ( int i = 0; i < 1; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Woman/Stand/Up-Left0%d.png", i);
		m_vecTex[TI_WOMAN][MI_STAND][DI_UPLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(24.0f, 62.0f, 0) ) );
	}

	//MI_STAND_TWOHAND_ATTACK
	m_vecTex[TI_WOMAN][MI_STAND_TWOHAND_ATTACK][DI_DOWN].reserve( 1 );
	for ( int i = 0; i < 1; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Woman/Stand for two handed attack/Down0%d.png", i);
		m_vecTex[TI_WOMAN][MI_STAND_TWOHAND_ATTACK][DI_DOWN].push_back( LoadTexture( szBuf, D3DXVECTOR3(28.0f, 55.0f, 0.0f) ) );
	}
	m_vecTex[TI_WOMAN][MI_STAND_TWOHAND_ATTACK][DI_DOWNLEFT].reserve( 1 );
	for ( int i = 0; i < 1; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Woman/Stand for two handed attack/Down-Left0%d.png", i);
		m_vecTex[TI_WOMAN][MI_STAND_TWOHAND_ATTACK][DI_DOWNLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(25.0f, 55.0f, 0.0f) ) );
	}
	m_vecTex[TI_WOMAN][MI_STAND_TWOHAND_ATTACK][DI_LEFT].reserve( 1 );
	for ( int i = 0; i < 1; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Woman/Stand for two handed attack/Left0%d.png", i);
		m_vecTex[TI_WOMAN][MI_STAND_TWOHAND_ATTACK][DI_LEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(32.0f, 53.0f, 0) ) );
	}
	m_vecTex[TI_WOMAN][MI_STAND_TWOHAND_ATTACK][DI_UP].reserve( 1 );
	for ( int i = 0; i < 1; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Woman/Stand for two handed attack/Up0%d.png", i);
		m_vecTex[TI_WOMAN][MI_STAND_TWOHAND_ATTACK][DI_UP].push_back( LoadTexture( szBuf, D3DXVECTOR3(28.0f, 53.0f, 0) ) );
	}
	m_vecTex[TI_WOMAN][MI_STAND_TWOHAND_ATTACK][DI_UPLEFT].reserve( 1 );
	for ( int i = 0; i < 1; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Woman/Stand for two handed attack/Up-Left0%d.png", i);
		m_vecTex[TI_WOMAN][MI_STAND_TWOHAND_ATTACK][DI_UPLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(32.0f, 53.0f, 0) ) );
	}

	//MI_TAKE_HIT
	m_vecTex[TI_WOMAN][MI_TAKE_HIT][DI_DOWN].reserve( 5 );
	for ( int i = 0; i < 5; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Woman/Take Hit/Down0%d.png", i);
		m_vecTex[TI_WOMAN][MI_TAKE_HIT][DI_DOWN].push_back( LoadTexture( szBuf, D3DXVECTOR3(34.0f, 57.0f, 0.0f) ) );
	}
	m_vecTex[TI_WOMAN][MI_TAKE_HIT][DI_DOWNLEFT].reserve( 5 );
	for ( int i = 0; i < 5; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Woman/Take Hit/Down-Left0%d.png", i);
		m_vecTex[TI_WOMAN][MI_TAKE_HIT][DI_DOWNLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(40.0f, 60.0f, 0.0f) ) );
	}
	m_vecTex[TI_WOMAN][MI_TAKE_HIT][DI_LEFT].reserve( 5 );
	for ( int i = 0; i < 5; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Woman/Take Hit/Left0%d.png", i);
		m_vecTex[TI_WOMAN][MI_TAKE_HIT][DI_LEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(39.0f, 57.0f, 0) ) );
	}
	m_vecTex[TI_WOMAN][MI_TAKE_HIT][DI_UP].reserve( 5 );
	for ( int i = 0; i < 5; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Woman/Take Hit/Up0%d.png", i);
		m_vecTex[TI_WOMAN][MI_TAKE_HIT][DI_UP].push_back( LoadTexture( szBuf, D3DXVECTOR3(34.0f, 62.0f, 0) ) );
	}
	m_vecTex[TI_WOMAN][MI_TAKE_HIT][DI_UPLEFT].reserve( 5 );
	for ( int i = 0; i < 5; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Woman/Take Hit/Up-Left0%d.png", i);
		m_vecTex[TI_WOMAN][MI_TAKE_HIT][DI_UPLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(36.0f, 61.0f, 0) ) );
	}

	//MI_WALK_ARMED
	m_vecTex[TI_WOMAN][MI_WALK_ARMED][DI_DOWN].reserve( 10 );
	for ( int i = 0; i < 10; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Woman/Walk armed/Down0%d.png", i);
		m_vecTex[TI_WOMAN][MI_WALK_ARMED][DI_DOWN].push_back( LoadTexture( szBuf, D3DXVECTOR3(25.0f, 65.0f, 0.0f) ) );
	}
	m_vecTex[TI_WOMAN][MI_WALK_ARMED][DI_DOWNLEFT].reserve( 10 );
	for ( int i = 0; i < 10; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Woman/Walk armed/Down-Left0%d.png", i);
		m_vecTex[TI_WOMAN][MI_WALK_ARMED][DI_DOWNLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(32.0f, 65.0f, 0.0f) ) );
	}
	m_vecTex[TI_WOMAN][MI_WALK_ARMED][DI_LEFT].reserve( 10 );
	for ( int i = 0; i < 10; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Woman/Walk armed/Left0%d.png", i);
		m_vecTex[TI_WOMAN][MI_WALK_ARMED][DI_LEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(40.0f, 62.0f, 0) ) );
	}
	m_vecTex[TI_WOMAN][MI_WALK_ARMED][DI_UP].reserve( 10 );
	for ( int i = 0; i < 10; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Woman/Walk armed/Up0%d.png", i);
		m_vecTex[TI_WOMAN][MI_WALK_ARMED][DI_UP].push_back( LoadTexture( szBuf, D3DXVECTOR3(26.0f, 66.0f, 0) ) );
	}
	m_vecTex[TI_WOMAN][MI_WALK_ARMED][DI_UPLEFT].reserve( 10 );
	for ( int i = 0; i < 10; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Woman/Walk armed/Up-Left0%d.png", i);
		m_vecTex[TI_WOMAN][MI_WALK_ARMED][DI_UPLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(33.0f, 64.0f, 0) ) );
	}

	//MI_WALK_UNARMED
	m_vecTex[TI_WOMAN][MI_WALK_UNARMED][DI_DOWN].reserve( 10 );
	for ( int i = 0; i < 10; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Woman/Walk unarmed/Down0%d.png", i);
		m_vecTex[TI_WOMAN][MI_WALK_UNARMED][DI_DOWN].push_back( LoadTexture( szBuf, D3DXVECTOR3(25.0f, 65.0f, 0.0f) ) );
	}
	m_vecTex[TI_WOMAN][MI_WALK_UNARMED][DI_DOWNLEFT].reserve( 10 );
	for ( int i = 0; i < 10; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Woman/Walk unarmed/Down-Left0%d.png", i);
		m_vecTex[TI_WOMAN][MI_WALK_UNARMED][DI_DOWNLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(32.0f, 65.0f, 0.0f) ) );
	}
	m_vecTex[TI_WOMAN][MI_WALK_UNARMED][DI_LEFT].reserve( 10 );
	for ( int i = 0; i < 10; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Woman/Walk unarmed/Left0%d.png", i);
		m_vecTex[TI_WOMAN][MI_WALK_UNARMED][DI_LEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(40.0f, 62.0f, 0) ) );
	}
	m_vecTex[TI_WOMAN][MI_WALK_UNARMED][DI_UP].reserve( 10 );
	for ( int i = 0; i < 10; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Woman/Walk unarmed/Up0%d.png", i);
		m_vecTex[TI_WOMAN][MI_WALK_UNARMED][DI_UP].push_back( LoadTexture( szBuf, D3DXVECTOR3(25.0f, 66.0f, 0) ) );
	}
	m_vecTex[TI_WOMAN][MI_WALK_UNARMED][DI_UPLEFT].reserve( 10 );
	for ( int i = 0; i < 10; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Woman/Walk unarmed/Up-Left0%d.png", i);
		m_vecTex[TI_WOMAN][MI_WALK_UNARMED][DI_UPLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(31.0f, 64.0f, 0) ) );
	}

	//MI_WALK_ATTACKPOS
	m_vecTex[TI_WOMAN][MI_WALK_ATTACKPOS][DI_DOWN].reserve( 10 );
	for ( int i = 0; i < 10; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Woman/Walk in attack position/Down0%d.png", i);
		m_vecTex[TI_WOMAN][MI_WALK_ATTACKPOS][DI_DOWN].push_back( LoadTexture( szBuf, D3DXVECTOR3(26.0f, 64.0f, 0.0f) ) );
	}

	m_vecTex[TI_WOMAN][MI_WALK_ATTACKPOS][DI_DOWNLEFT].reserve( 10 );
	for ( int i = 0; i < 10; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Woman/Walk in attack position/Down-Left0%d.png", i);
		m_vecTex[TI_WOMAN][MI_WALK_ATTACKPOS][DI_DOWNLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(40.0f, 61.0f, 0.0f) ) );
	}

	m_vecTex[TI_WOMAN][MI_WALK_ATTACKPOS][DI_LEFT].reserve( 10 );
	for ( int i = 0; i < 10; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Woman/Walk in attack position/Left0%d.png", i);
		m_vecTex[TI_WOMAN][MI_WALK_ATTACKPOS][DI_LEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(48.0f, 55.0f, 0) ) );
	}

	m_vecTex[TI_WOMAN][MI_WALK_ATTACKPOS][DI_UP].reserve( 10 );
	for ( int i = 0; i < 10; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Woman/Walk in attack position/Up0%d.png", i);
		m_vecTex[TI_WOMAN][MI_WALK_ATTACKPOS][DI_UP].push_back( LoadTexture( szBuf, D3DXVECTOR3(26.0f, 61.0f, 0) ) );
	}

	m_vecTex[TI_WOMAN][MI_WALK_ATTACKPOS][DI_UPLEFT].reserve( 10 );
	for ( int i = 0; i < 10; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Woman/Walk in attack position/Up-Left0%d.png", i);
		m_vecTex[TI_WOMAN][MI_WALK_ATTACKPOS][DI_UPLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(41.0f, 59.0f, 0) ) );
	}
}

void CTextureLoader::Vendor()
{
	//MI_ATTACK_UNARMED
	//MI_DIE
	//MI_RUN_UNARMED
	//MI_STAND
	//MI_TAKE_HIT
	//MI_WALK_UNARMED
	//MI_WALK_ATTACKPOS

	TCHAR szBuf[128];
	//MI_ATTACK_UNARMED
	m_vecTex[TI_VENDOR][MI_ATTACK_UNARMED][DI_DOWN].reserve( 7 );
	for ( int i = 0; i < 7; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Vendor/Attack.Unarmed/Down0%d.png", i);
		m_vecTex[TI_VENDOR][MI_ATTACK_UNARMED][DI_DOWN].push_back( LoadTexture( szBuf, D3DXVECTOR3(39.0f, 66.0f, 0.0f) ) );
	}
	m_vecTex[TI_VENDOR][MI_ATTACK_UNARMED][DI_DOWNLEFT].reserve( 7 );
	for ( int i = 0; i < 7; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Vendor/Attack.Unarmed/Down-Left0%d.png", i);
		m_vecTex[TI_VENDOR][MI_ATTACK_UNARMED][DI_DOWNLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(47.0f, 64.0f, 0.0f) ) );
	}
	m_vecTex[TI_VENDOR][MI_ATTACK_UNARMED][DI_LEFT].reserve( 7 );
	for ( int i = 0; i < 7; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Vendor/Attack.Unarmed/Left0%d.png", i);
		m_vecTex[TI_VENDOR][MI_ATTACK_UNARMED][DI_LEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(50.0f, 64.0f, 0) ) );
	}
	m_vecTex[TI_VENDOR][MI_ATTACK_UNARMED][DI_UP].reserve( 7 );
	for ( int i = 0; i < 7; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Vendor/Attack.Unarmed/Up0%d.png", i);
		m_vecTex[TI_VENDOR][MI_ATTACK_UNARMED][DI_UP].push_back( LoadTexture( szBuf, D3DXVECTOR3(39.0f, 64.0f, 0) ) );
	}
	m_vecTex[TI_VENDOR][MI_ATTACK_UNARMED][DI_UPLEFT].reserve( 7 );
	for ( int i = 0; i < 7; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Vendor/Attack.Unarmed/Up-Left0%d.png", i);
		m_vecTex[TI_VENDOR][MI_ATTACK_UNARMED][DI_UPLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(50.0f, 63.0f, 0) ) );
	}

	//MI_DIE
	m_vecTex[TI_VENDOR][MI_DIE][DI_DOWN].reserve( 6 );
	for ( int i = 0; i < 6; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Vendor/Die/Down0%d.png", i);
		m_vecTex[TI_VENDOR][MI_DIE][DI_DOWN].push_back( LoadTexture( szBuf, D3DXVECTOR3(52.0f, 61.0f, 0.0f) ) );
	}
	m_vecTex[TI_VENDOR][MI_DIE][DI_DOWNLEFT].reserve( 6 );
	for ( int i = 0; i < 6; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Vendor/Die/Down-Left0%d.png", i);
		m_vecTex[TI_VENDOR][MI_DIE][DI_DOWNLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(119.0f, 60.0f, 0.0f) ) );
	}
	m_vecTex[TI_VENDOR][MI_DIE][DI_LEFT].reserve( 6 );
	for ( int i = 0; i < 6; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Vendor/Die/Left0%d.png", i);
		m_vecTex[TI_VENDOR][MI_DIE][DI_LEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(119.0f, 69.0f, 0) ) );
	}
	m_vecTex[TI_VENDOR][MI_DIE][DI_UP].reserve( 6 );
	for ( int i = 0; i < 6; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Vendor/Die/Up0%d.png", i);
		m_vecTex[TI_VENDOR][MI_DIE][DI_UP].push_back( LoadTexture( szBuf, D3DXVECTOR3(56.0f, 64.0f, 0) ) );
	}
	m_vecTex[TI_VENDOR][MI_DIE][DI_UPLEFT].reserve( 6 );
	for ( int i = 0; i < 6; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Vendor/Die/Up-Left0%d.png", i);
		m_vecTex[TI_VENDOR][MI_DIE][DI_UPLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(119.0f, 64.0f, 0) ) );
	}

	//MI_RUN_UNARMED
	m_vecTex[TI_VENDOR][MI_RUN_UNARMED][DI_DOWN].reserve( 10 );
	for ( int i = 0; i < 10; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Vendor/Run unarmed/Down0%d.png", i);
		m_vecTex[TI_VENDOR][MI_RUN_UNARMED][DI_DOWN].push_back( LoadTexture( szBuf, D3DXVECTOR3(30.0f, 64.0f, 0.0f) ) );
	}
	m_vecTex[TI_VENDOR][MI_RUN_UNARMED][DI_DOWNLEFT].reserve( 10 );
	for ( int i = 0; i < 10; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Vendor/Run unarmed/Down-Left0%d.png", i);
		m_vecTex[TI_VENDOR][MI_RUN_UNARMED][DI_DOWNLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(50.0f, 63.0f, 0.0f) ) );
	}
	m_vecTex[TI_VENDOR][MI_RUN_UNARMED][DI_LEFT].reserve( 10 );
	for ( int i = 0; i < 10; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Vendor/Run unarmed/Left0%d.png", i);
		m_vecTex[TI_VENDOR][MI_RUN_UNARMED][DI_LEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(59.0f, 63.0f, 0) ) );
	}
	m_vecTex[TI_VENDOR][MI_RUN_UNARMED][DI_UP].reserve( 10 );
	for ( int i = 0; i < 10; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Vendor/Run unarmed/Up0%d.png", i);
		m_vecTex[TI_VENDOR][MI_RUN_UNARMED][DI_UP].push_back( LoadTexture( szBuf, D3DXVECTOR3(30.0f, 71.0f, 0) ) );
	}
	m_vecTex[TI_VENDOR][MI_RUN_UNARMED][DI_UPLEFT].reserve( 10 );
	for ( int i = 0; i < 10; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Vendor/Run unarmed/Up-Left0%d.png", i);
		m_vecTex[TI_VENDOR][MI_RUN_UNARMED][DI_UPLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(53.0f, 67.0f, 0) ) );
	}

	//MI_STAND
	m_vecTex[TI_VENDOR][MI_STAND][DI_DOWN].reserve( 1 );
	for ( int i = 0; i < 1; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Vendor/Stand/Down0%d.png", i);
		m_vecTex[TI_VENDOR][MI_STAND][DI_DOWN].push_back( LoadTexture( szBuf, D3DXVECTOR3(28.0f, 62.0f, 0.0f) ) );
	}
	m_vecTex[TI_VENDOR][MI_STAND][DI_DOWNLEFT].reserve( 1 );
	for ( int i = 0; i < 1; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Vendor/Stand/Down-Left0%d.png", i);
		m_vecTex[TI_VENDOR][MI_STAND][DI_DOWNLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(24.0f, 62.0f, 0.0f) ) );
	}
	m_vecTex[TI_VENDOR][MI_STAND][DI_LEFT].reserve( 1 );
	for ( int i = 0; i < 1; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Vendor/Stand/Left0%d.png", i);
		m_vecTex[TI_VENDOR][MI_STAND][DI_LEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(19.0f, 62.0f, 0) ) );
	}
	m_vecTex[TI_VENDOR][MI_STAND][DI_UP].reserve( 1 );
	for ( int i = 0; i < 1; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Vendor/Stand/Up0%d.png", i);
		m_vecTex[TI_VENDOR][MI_STAND][DI_UP].push_back( LoadTexture( szBuf, D3DXVECTOR3(29.0f, 65.0f, 0) ) );
	}
	m_vecTex[TI_VENDOR][MI_STAND][DI_UPLEFT].reserve( 1 );
	for ( int i = 0; i < 1; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Vendor/Stand/Up-Left0%d.png", i);
		m_vecTex[TI_VENDOR][MI_STAND][DI_UPLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(28.0f, 64.0f, 0) ) );
	}

	//MI_TAKE_HIT
	m_vecTex[TI_VENDOR][MI_TAKE_HIT][DI_DOWN].reserve( 5 );
	for ( int i = 0; i < 5; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Vendor/Take Hit/Down0%d.png", i);
		m_vecTex[TI_VENDOR][MI_TAKE_HIT][DI_DOWN].push_back( LoadTexture( szBuf, D3DXVECTOR3(38.0f, 66.0f, 0.0f) ) );
	}
	m_vecTex[TI_VENDOR][MI_TAKE_HIT][DI_DOWNLEFT].reserve( 5 );
	for ( int i = 0; i < 5; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Vendor/Take Hit/Down-Left0%d.png", i);
		m_vecTex[TI_VENDOR][MI_TAKE_HIT][DI_DOWNLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(48.0f, 68.0f, 0.0f) ) );
	}
	m_vecTex[TI_VENDOR][MI_TAKE_HIT][DI_LEFT].reserve( 5 );
	for ( int i = 0; i < 5; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Vendor/Take Hit/Left0%d.png", i);
		m_vecTex[TI_VENDOR][MI_TAKE_HIT][DI_LEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(48.0f, 65.0f, 0) ) );
	}
	m_vecTex[TI_VENDOR][MI_TAKE_HIT][DI_UP].reserve( 5 );
	for ( int i = 0; i < 5; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Vendor/Take Hit/Up0%d.png", i);
		m_vecTex[TI_VENDOR][MI_TAKE_HIT][DI_UP].push_back( LoadTexture( szBuf, D3DXVECTOR3(38.0f, 67.0f, 0) ) );
	}
	m_vecTex[TI_VENDOR][MI_TAKE_HIT][DI_UPLEFT].reserve( 5 );
	for ( int i = 0; i < 5; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Vendor/Take Hit/Up-Left0%d.png", i);
		m_vecTex[TI_VENDOR][MI_TAKE_HIT][DI_UPLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(38.0f, 67.0f, 0) ) );
	}

	//MI_WALK_UNARMED
	m_vecTex[TI_VENDOR][MI_WALK_UNARMED][DI_DOWN].reserve( 10 );
	for ( int i = 0; i < 10; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Vendor/Walk unarmed/Down0%d.png", i);
		m_vecTex[TI_VENDOR][MI_WALK_UNARMED][DI_DOWN].push_back( LoadTexture( szBuf, D3DXVECTOR3(28.0f, 68.0f, 0.0f) ) );
	}
	m_vecTex[TI_VENDOR][MI_WALK_UNARMED][DI_DOWNLEFT].reserve( 10 );
	for ( int i = 0; i < 10; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Vendor/Walk unarmed/Down-Left0%d.png", i);
		m_vecTex[TI_VENDOR][MI_WALK_UNARMED][DI_DOWNLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(36.0f, 66.0f, 0.0f) ) );
	}
	m_vecTex[TI_VENDOR][MI_WALK_UNARMED][DI_LEFT].reserve( 10 );
	for ( int i = 0; i < 10; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Vendor/Walk unarmed/Left0%d.png", i);
		m_vecTex[TI_VENDOR][MI_WALK_UNARMED][DI_LEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(42.0f, 63.0f, 0) ) );
	}
	m_vecTex[TI_VENDOR][MI_WALK_UNARMED][DI_UP].reserve( 10 );
	for ( int i = 0; i < 10; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Vendor/Walk unarmed/Up0%d.png", i);
		m_vecTex[TI_VENDOR][MI_WALK_UNARMED][DI_UP].push_back( LoadTexture( szBuf, D3DXVECTOR3(27.0f, 69.0f, 0) ) );
	}
	m_vecTex[TI_VENDOR][MI_WALK_UNARMED][DI_UPLEFT].reserve( 10 );
	for ( int i = 0; i < 10; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Vendor/Walk unarmed/Up-Left0%d.png", i);
		m_vecTex[TI_VENDOR][MI_WALK_UNARMED][DI_UPLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(37.0f, 66.0f, 0) ) );
	}

	//MI_WALK_ATTACKPOS
	m_vecTex[TI_VENDOR][MI_WALK_ATTACKPOS][DI_DOWN].reserve( 10 );
	for ( int i = 0; i < 10; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Vendor/Walk in attack position/Down0%d.png", i);
		m_vecTex[TI_VENDOR][MI_WALK_ATTACKPOS][DI_DOWN].push_back( LoadTexture( szBuf, D3DXVECTOR3(34.0f, 66.0f, 0.0f) ) );
	}
	m_vecTex[TI_VENDOR][MI_WALK_ATTACKPOS][DI_DOWNLEFT].reserve( 10 );
	for ( int i = 0; i < 10; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Vendor/Walk in attack position/Down-Left0%d.png", i);
		m_vecTex[TI_VENDOR][MI_WALK_ATTACKPOS][DI_DOWNLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(44.0f, 64.0f, 0.0f) ) );
	}
	m_vecTex[TI_VENDOR][MI_WALK_ATTACKPOS][DI_LEFT].reserve( 10 );
	for ( int i = 0; i < 10; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Vendor/Walk in attack position/Left0%d.png", i);
		m_vecTex[TI_VENDOR][MI_WALK_ATTACKPOS][DI_LEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(55.0f, 60.0f, 0) ) );
	}
	m_vecTex[TI_VENDOR][MI_WALK_ATTACKPOS][DI_UP].reserve( 10 );
	for ( int i = 0; i < 10; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Vendor/Walk in attack position/Up0%d.png", i);
		m_vecTex[TI_VENDOR][MI_WALK_ATTACKPOS][DI_UP].push_back( LoadTexture( szBuf, D3DXVECTOR3(34.0f, 64.0f, 0) ) );
	}
	m_vecTex[TI_VENDOR][MI_WALK_ATTACKPOS][DI_UPLEFT].reserve( 10 );
	for ( int i = 0; i < 10; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Vendor/Walk in attack position/Up-Left0%d.png", i);
		m_vecTex[TI_VENDOR][MI_WALK_ATTACKPOS][DI_UPLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(45.0f, 63.0f, 0) ) );
	}
}

void CTextureLoader::Chicken()
{
	//MI_ATTACK1
	//MI_ATTACK2
	//MI_DIE
	//MI_RUN_UNARMED
	//MI_STAND

	TCHAR szBuf[128];

	//MI_ATTACK1
	m_vecTex[TI_CHICKEN][MI_ATTACK1][DI_DOWN].reserve( 5 );
	for ( int i = 0; i < 5; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Chicken/Attack1/Down0%d.png", i);
		m_vecTex[TI_CHICKEN][MI_ATTACK1][DI_DOWN].push_back( LoadTexture( szBuf, D3DXVECTOR3(26.0f, 28.0f, 0.0f) ) );
	}
	m_vecTex[TI_CHICKEN][MI_ATTACK1][DI_DOWNLEFT].reserve( 5 );
	for ( int i = 0; i < 5; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Chicken/Attack1/Down-Left0%d.png", i);
		m_vecTex[TI_CHICKEN][MI_ATTACK1][DI_DOWNLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(27.0f, 28.0f, 0.0f) ) );
	}
	m_vecTex[TI_CHICKEN][MI_ATTACK1][DI_LEFT].reserve( 5 );
	for ( int i = 0; i < 5; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Chicken/Attack1/Left0%d.png", i);
		m_vecTex[TI_CHICKEN][MI_ATTACK1][DI_LEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(26.0f, 30.0f, 0) ) );
	}
	m_vecTex[TI_CHICKEN][MI_ATTACK1][DI_UP].reserve( 5 );
	for ( int i = 0; i < 5; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Chicken/Attack1/Up0%d.png", i);
		m_vecTex[TI_CHICKEN][MI_ATTACK1][DI_UP].push_back( LoadTexture( szBuf, D3DXVECTOR3(26.0f, 31.0f, 0) ) );
	}
	m_vecTex[TI_CHICKEN][MI_ATTACK1][DI_UPLEFT].reserve( 5 );
	for ( int i = 0; i < 5; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Chicken/Attack1/Up-Left0%d.png", i);
		m_vecTex[TI_CHICKEN][MI_ATTACK1][DI_UPLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(26.0f, 30.0f, 0) ) );
	}

	//MI_ATTACK2
	m_vecTex[TI_CHICKEN][MI_ATTACK2][DI_DOWN].reserve( 5 );
	for ( int i = 0; i < 5; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Chicken/Attack2/Down0%d.png", i);
		m_vecTex[TI_CHICKEN][MI_ATTACK2][DI_DOWN].push_back( LoadTexture( szBuf, D3DXVECTOR3(27.0f, 25.0f, 0.0f) ) );
	}
	m_vecTex[TI_CHICKEN][MI_ATTACK2][DI_DOWNLEFT].reserve( 5 );
	for ( int i = 0; i < 5; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Chicken/Attack2/Down-Left0%d.png", i);
		m_vecTex[TI_CHICKEN][MI_ATTACK2][DI_DOWNLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(26.0f, 24.0f, 0.0f) ) );
	}
	m_vecTex[TI_CHICKEN][MI_ATTACK2][DI_LEFT].reserve( 5 );
	for ( int i = 0; i < 5; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Chicken/Attack2/Left0%d.png", i);
		m_vecTex[TI_CHICKEN][MI_ATTACK2][DI_LEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(26.0f, 27.0f, 0) ) );
	}
	m_vecTex[TI_CHICKEN][MI_ATTACK2][DI_UP].reserve( 5 );
	for ( int i = 0; i < 5; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Chicken/Attack2/Up0%d.png", i);
		m_vecTex[TI_CHICKEN][MI_ATTACK2][DI_UP].push_back( LoadTexture( szBuf, D3DXVECTOR3(27.0f, 28.0f, 0) ) );
	}
	m_vecTex[TI_CHICKEN][MI_ATTACK2][DI_UPLEFT].reserve( 5 );
	for ( int i = 0; i < 5; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Chicken/Attack2/Up-Left0%d.png", i);
		m_vecTex[TI_CHICKEN][MI_ATTACK2][DI_UPLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(25.0f, 28.0f, 0) ) );
	}
	
	//MI_DIE
	m_vecTex[TI_CHICKEN][MI_DIE][DI_DOWN].reserve( 6 );
	for ( int i = 0; i < 6; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Chicken/Die/Down0%d.png", i);
		m_vecTex[TI_CHICKEN][MI_DIE][DI_DOWN].push_back( LoadTexture( szBuf, D3DXVECTOR3(26.0f, 26.0f, 0.0f) ) );
	}
	m_vecTex[TI_CHICKEN][MI_DIE][DI_DOWNLEFT].reserve( 6 );
	for ( int i = 0; i < 6; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Chicken/Die/Down-Left0%d.png", i);
		m_vecTex[TI_CHICKEN][MI_DIE][DI_DOWNLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(29.0f, 27.0f, 0.0f) ) );
	}
	m_vecTex[TI_CHICKEN][MI_DIE][DI_LEFT].reserve( 6 );
	for ( int i = 0; i < 6; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Chicken/Die/Left0%d.png", i);
		m_vecTex[TI_CHICKEN][MI_DIE][DI_LEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(25.0f, 28.0f, 0) ) );
	}
	m_vecTex[TI_CHICKEN][MI_DIE][DI_UP].reserve( 6 );
	for ( int i = 0; i < 6; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Chicken/Die/Up0%d.png", i);
		m_vecTex[TI_CHICKEN][MI_DIE][DI_UP].push_back( LoadTexture( szBuf, D3DXVECTOR3(26.0f, 28.0f, 0) ) );
	}
	m_vecTex[TI_CHICKEN][MI_DIE][DI_UPLEFT].reserve( 6 );
	for ( int i = 0; i < 6; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Chicken/Die/Up-Left0%d.png", i);
		m_vecTex[TI_CHICKEN][MI_DIE][DI_UPLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(25.0f, 27.0f, 0) ) );
	}

	//MI_RUN_UNARMED
	m_vecTex[TI_CHICKEN][MI_RUN_UNARMED][DI_DOWN].reserve( 5 );
	for ( int i = 0; i < 5; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Chicken/Run/Down0%d.png", i);
		m_vecTex[TI_CHICKEN][MI_RUN_UNARMED][DI_DOWN].push_back( LoadTexture( szBuf, D3DXVECTOR3(26.0f, 23.0f, 0.0f) ) );
	}
	m_vecTex[TI_CHICKEN][MI_RUN_UNARMED][DI_DOWNLEFT].reserve( 5 );
	for ( int i = 0; i < 5; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Chicken/Run/Down-Left0%d.png", i);
		m_vecTex[TI_CHICKEN][MI_RUN_UNARMED][DI_DOWNLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(22.0f, 21.0f, 0.0f) ) );
	}
	m_vecTex[TI_CHICKEN][MI_RUN_UNARMED][DI_LEFT].reserve( 5 );
	for ( int i = 0; i < 5; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Chicken/Run/Left0%d.png", i);
		m_vecTex[TI_CHICKEN][MI_RUN_UNARMED][DI_LEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(26.0f, 21.0f, 0) ) );
	}
	m_vecTex[TI_CHICKEN][MI_RUN_UNARMED][DI_UP].reserve( 5 );
	for ( int i = 0; i < 5; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Chicken/Run/Up0%d.png", i);
		m_vecTex[TI_CHICKEN][MI_RUN_UNARMED][DI_UP].push_back( LoadTexture( szBuf, D3DXVECTOR3(27.0f, 24.0f, 0) ) );
	}
	m_vecTex[TI_CHICKEN][MI_RUN_UNARMED][DI_UPLEFT].reserve( 5 );
	for ( int i = 0; i < 5; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Chicken/Run/Up-Left0%d.png", i);
		m_vecTex[TI_CHICKEN][MI_RUN_UNARMED][DI_UPLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(22.0f, 23.0f, 0) ) );
	}
	
	//MI_STAND
	m_vecTex[TI_CHICKEN][MI_STAND][DI_DOWN].reserve( 1 );
	for ( int i = 0; i < 1; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Chicken/Stand/Down0%d.png", i);
		m_vecTex[TI_CHICKEN][MI_STAND][DI_DOWN].push_back( LoadTexture( szBuf, D3DXVECTOR3(12.0f, 20.0f, 0.0f) ) );
	}
	m_vecTex[TI_CHICKEN][MI_STAND][DI_DOWNLEFT].reserve( 1 );
	for ( int i = 0; i < 1; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Chicken/Stand/Down-Left0%d.png", i);
		m_vecTex[TI_CHICKEN][MI_STAND][DI_DOWNLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(17.0f, 20.0f, 0.0f) ) );
	}
	m_vecTex[TI_CHICKEN][MI_STAND][DI_LEFT].reserve( 1 );
	for ( int i = 0; i < 1; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Chicken/Stand/Left0%d.png", i);
		m_vecTex[TI_CHICKEN][MI_STAND][DI_LEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(22.0f, 23.0f, 0) ) );
	}
	m_vecTex[TI_CHICKEN][MI_STAND][DI_UP].reserve( 1 );
	for ( int i = 0; i < 1; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Chicken/Stand/Up0%d.png", i);
		m_vecTex[TI_CHICKEN][MI_STAND][DI_UP].push_back( LoadTexture( szBuf, D3DXVECTOR3(12.0f, 26.0f, 0) ) );
	}
	m_vecTex[TI_CHICKEN][MI_STAND][DI_UPLEFT].reserve( 1 );
	for ( int i = 0; i < 1; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Chicken/Stand/Up-Left0%d.png", i);
		m_vecTex[TI_CHICKEN][MI_STAND][DI_UPLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(17.0f, 25.0f, 0) ) );
	}

	//MI_WALK_UNARMED
	m_vecTex[TI_CHICKEN][MI_WALK_UNARMED][DI_DOWN].reserve( 5 );
	for ( int i = 0; i < 5; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Chicken/Walk/Down0%d.png", i);
		m_vecTex[TI_CHICKEN][MI_WALK_UNARMED][DI_DOWN].push_back( LoadTexture( szBuf, D3DXVECTOR3(12.0f, 22.0f, 0.0f) ) );
	}
	m_vecTex[TI_CHICKEN][MI_WALK_UNARMED][DI_DOWNLEFT].reserve( 5 );
	for ( int i = 0; i < 5; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Chicken/Walk/Down-Left0%d.png", i);
		m_vecTex[TI_CHICKEN][MI_WALK_UNARMED][DI_DOWNLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(18.0f, 23.0f, 0.0f) ) );
	}
	m_vecTex[TI_CHICKEN][MI_WALK_UNARMED][DI_LEFT].reserve( 5 );
	for ( int i = 0; i < 5; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Chicken/Walk/Left0%d.png", i);
		m_vecTex[TI_CHICKEN][MI_WALK_UNARMED][DI_LEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(22.0f, 25.0f, 0) ) );
	}
	m_vecTex[TI_CHICKEN][MI_WALK_UNARMED][DI_UP].reserve( 5 );
	for ( int i = 0; i < 5; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Chicken/Walk/Up0%d.png", i);
		m_vecTex[TI_CHICKEN][MI_WALK_UNARMED][DI_UP].push_back( LoadTexture( szBuf, D3DXVECTOR3(12.0f, 28.0f, 0) ) );
	}
	m_vecTex[TI_CHICKEN][MI_WALK_UNARMED][DI_UPLEFT].reserve( 5 );
	for ( int i = 0; i < 5; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Chicken/Walk/Up-Left0%d.png", i);
		m_vecTex[TI_CHICKEN][MI_WALK_UNARMED][DI_UPLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(18.0f, 27.0f, 0) ) );
	}
}

void CTextureLoader::Daemon()
{
	//MI_ATTACK1
	//MI_DIE
	//MI_STAND
	//MI_TAKE_HIT
	//MI_WALK_UNARMED

	TCHAR szBuf[128];

	//MI_ATTACK1
	m_vecTex[TI_DAEMON][MI_ATTACK1][DI_DOWN].reserve( 4 );
	for ( int i = 0; i < 4; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Daemon/Attack1/Down0%d.png", i);
		m_vecTex[TI_DAEMON][MI_ATTACK1][DI_DOWN].push_back( LoadTexture( szBuf, D3DXVECTOR3(129.0f, 190.0f, 0.0f) ) );
	}
	m_vecTex[TI_DAEMON][MI_ATTACK1][DI_DOWNLEFT].reserve( 4 );
	for ( int i = 0; i < 4; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Daemon/Attack1/Down-Left0%d.png", i);
		m_vecTex[TI_DAEMON][MI_ATTACK1][DI_DOWNLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(112.0f, 190.0f, 0.0f) ) );
	}
	m_vecTex[TI_DAEMON][MI_ATTACK1][DI_LEFT].reserve( 4 );
	for ( int i = 0; i < 4; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Daemon/Attack1/Left0%d.png", i);
		m_vecTex[TI_DAEMON][MI_ATTACK1][DI_LEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(135.0f, 180.0f, 0) ) );
	}
	m_vecTex[TI_DAEMON][MI_ATTACK1][DI_UP].reserve( 4 );
	for ( int i = 0; i < 4; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Daemon/Attack1/Up0%d.png", i);
		m_vecTex[TI_DAEMON][MI_ATTACK1][DI_UP].push_back( LoadTexture( szBuf, D3DXVECTOR3(145.0f, 160.0f, 0) ) );
	}
	m_vecTex[TI_DAEMON][MI_ATTACK1][DI_UPLEFT].reserve( 4 );
	for ( int i = 0; i < 4; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Daemon/Attack1/Up-Left0%d.png", i);
		m_vecTex[TI_DAEMON][MI_ATTACK1][DI_UPLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(155.0f, 170.0f, 0) ) );
	}
	
	//MI_DIE
	m_vecTex[TI_DAEMON][MI_DIE][DI_DOWN].reserve( 4 );
	for ( int i = 0; i < 4; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Daemon/Die/Down0%d.png", i);
		m_vecTex[TI_DAEMON][MI_DIE][DI_DOWN].push_back( LoadTexture( szBuf, D3DXVECTOR3(315.0f, 187.0f, 0.0f) ) );
	}
	m_vecTex[TI_DAEMON][MI_DIE][DI_DOWNLEFT].reserve( 4 );
	for ( int i = 0; i < 4; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Daemon/Die/Down-Left0%d.png", i);
		m_vecTex[TI_DAEMON][MI_DIE][DI_DOWNLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(134.0f, 194.0f, 0.0f) ) );
	}
	m_vecTex[TI_DAEMON][MI_DIE][DI_LEFT].reserve( 4 );
	for ( int i = 0; i < 4; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Daemon/Die/Left0%d.png", i);
		m_vecTex[TI_DAEMON][MI_DIE][DI_LEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(80.0f, 188.0f, 0) ) );
	}
	m_vecTex[TI_DAEMON][MI_DIE][DI_UP].reserve( 4 );
	for ( int i = 0; i < 4; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Daemon/Die/Up0%d.png", i);
		m_vecTex[TI_DAEMON][MI_DIE][DI_UP].push_back( LoadTexture( szBuf, D3DXVECTOR3(325.0f, 158.0f, 0) ) );
	}
	m_vecTex[TI_DAEMON][MI_DIE][DI_UPLEFT].reserve( 4 );
	for ( int i = 0; i < 4; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Daemon/Die/Up-Left0%d.png", i);
		m_vecTex[TI_DAEMON][MI_DIE][DI_UPLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(80.0f, 168.0f, 0) ) );
	}

	//MI_STAND
	m_vecTex[TI_DAEMON][MI_STAND][DI_DOWN].reserve( 1 );
	for ( int i = 0; i < 1; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Daemon/Stand/Down0%d.png", i);
		m_vecTex[TI_DAEMON][MI_STAND][DI_DOWN].push_back( LoadTexture( szBuf, D3DXVECTOR3(80.0f, 186.0f, 0.0f) ) );
	}
	m_vecTex[TI_DAEMON][MI_STAND][DI_DOWNLEFT].reserve( 1 );
	for ( int i = 0; i < 1; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Daemon/Stand/Down-Left0%d.png", i);
		m_vecTex[TI_DAEMON][MI_STAND][DI_DOWNLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(80.0f, 192.0f, 0.0f) ) );
	}
	m_vecTex[TI_DAEMON][MI_STAND][DI_LEFT].reserve( 1 );
	for ( int i = 0; i < 1; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Daemon/Stand/Left0%d.png", i);
		m_vecTex[TI_DAEMON][MI_STAND][DI_LEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(86.0f, 183.0f, 0) ) );
	}
	m_vecTex[TI_DAEMON][MI_STAND][DI_UP].reserve( 1 );
	for ( int i = 0; i < 1; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Daemon/Stand/Up0%d.png", i);
		m_vecTex[TI_DAEMON][MI_STAND][DI_UP].push_back( LoadTexture( szBuf, D3DXVECTOR3(90.0f, 162.0f, 0) ) );
	}
	m_vecTex[TI_DAEMON][MI_STAND][DI_UPLEFT].reserve( 1 );
	for ( int i = 0; i < 1; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Daemon/Stand/Up-Left0%d.png", i);
		m_vecTex[TI_DAEMON][MI_STAND][DI_UPLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(74.0f, 174.0f, 0) ) );
	}

	//MI_TAKE_HIT
	m_vecTex[TI_DAEMON][MI_TAKE_HIT][DI_DOWN].reserve( 7 );
	for ( int i = 0; i < 7; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Daemon/Take Hit/Down0%d.png", i);
		m_vecTex[TI_DAEMON][MI_TAKE_HIT][DI_DOWN].push_back( LoadTexture( szBuf, D3DXVECTOR3(275.0f, 186.0f, 0.0f) ) );
	}
	m_vecTex[TI_DAEMON][MI_TAKE_HIT][DI_DOWNLEFT].reserve( 7 );
	for ( int i = 0; i < 7; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Daemon/Take Hit/Down-Left0%d.png", i);
		m_vecTex[TI_DAEMON][MI_TAKE_HIT][DI_DOWNLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(125.0f, 199.0f, 0.0f) ) );
	}
	m_vecTex[TI_DAEMON][MI_TAKE_HIT][DI_LEFT].reserve( 7 );
	for ( int i = 0; i < 7; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Daemon/Take Hit/Left0%d.png", i);
		m_vecTex[TI_DAEMON][MI_TAKE_HIT][DI_LEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(135.0f, 195.0f, 0) ) );
	}
	m_vecTex[TI_DAEMON][MI_TAKE_HIT][DI_UP].reserve( 7 );
	for ( int i = 0; i < 7; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Daemon/Take Hit/Up0%d.png", i);
		m_vecTex[TI_DAEMON][MI_TAKE_HIT][DI_UP].push_back( LoadTexture( szBuf, D3DXVECTOR3(245.0f, 165.0f, 0) ) );
	}
	m_vecTex[TI_DAEMON][MI_TAKE_HIT][DI_UPLEFT].reserve( 7 );
	for ( int i = 0; i < 7; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Daemon/Take Hit/Up-Left0%d.png", i);
		m_vecTex[TI_DAEMON][MI_TAKE_HIT][DI_UPLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(133.0f, 198.0f, 0) ) );
	}

	//MI_WALK_UNARMED
	m_vecTex[TI_DAEMON][MI_WALK_UNARMED][DI_DOWN].reserve( 10 );
	for ( int i = 0; i < 10; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Daemon/Walk/Down0%d.png", i);
		m_vecTex[TI_DAEMON][MI_WALK_UNARMED][DI_DOWN].push_back( LoadTexture( szBuf, D3DXVECTOR3(85.0f, 199.0f, 0.0f) ) );
	}
	m_vecTex[TI_DAEMON][MI_WALK_UNARMED][DI_DOWNLEFT].reserve( 10 );
	for ( int i = 0; i < 10; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Daemon/Walk/Down-Left0%d.png", i);
		m_vecTex[TI_DAEMON][MI_WALK_UNARMED][DI_DOWNLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(88.0f, 197.0f, 0.0f) ) );
	}
	m_vecTex[TI_DAEMON][MI_WALK_UNARMED][DI_LEFT].reserve( 10 );
	for ( int i = 0; i < 10; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Daemon/Walk/Left0%d.png", i);
		m_vecTex[TI_DAEMON][MI_WALK_UNARMED][DI_LEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(116.0f, 183.0f, 0) ) );
	}
	m_vecTex[TI_DAEMON][MI_WALK_UNARMED][DI_UP].reserve( 10 );
	for ( int i = 0; i < 10; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Daemon/Walk/Up0%d.png", i);
		m_vecTex[TI_DAEMON][MI_WALK_UNARMED][DI_UP].push_back( LoadTexture( szBuf, D3DXVECTOR3(87.0f, 183.0f, 0) ) );
	}
	m_vecTex[TI_DAEMON][MI_WALK_UNARMED][DI_UPLEFT].reserve( 10 );
	for ( int i = 0; i < 10; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Daemon/Walk/Up-Left0%d.png", i);
		m_vecTex[TI_DAEMON][MI_WALK_UNARMED][DI_UPLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(76.0f, 185.0f, 0) ) );
	}
}

void CTextureLoader::Troll()
{
	//MI_ATTACK1
	//MI_DIE
	//MI_STAND
	//MI_TAKE_HIT
	//MI_WALK_UNARMED

	TCHAR szBuf[128];

	//MI_ATTACK1
	m_vecTex[TI_TROLL][MI_ATTACK1][DI_DOWN].reserve( 4 );
	for ( int i = 0; i < 4; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Troll/Attack1/Down0%d.png", i);
		m_vecTex[TI_TROLL][MI_ATTACK1][DI_DOWN].push_back( LoadTexture( szBuf, D3DXVECTOR3(142.0f, 131.0f, 0.0f) ) );
	}
	m_vecTex[TI_TROLL][MI_ATTACK1][DI_DOWNLEFT].reserve( 4 );
	for ( int i = 0; i < 4; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Troll/Attack1/Down-Left0%d.png", i);
		m_vecTex[TI_TROLL][MI_ATTACK1][DI_DOWNLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(117.0f, 129.0f, 0.0f) ) );
	}
	m_vecTex[TI_TROLL][MI_ATTACK1][DI_LEFT].reserve( 4 );
	for ( int i = 0; i < 4; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Troll/Attack1/Left0%d.png", i);
		m_vecTex[TI_TROLL][MI_ATTACK1][DI_LEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(126.0f, 135.0f, 0) ) );
	}
	m_vecTex[TI_TROLL][MI_ATTACK1][DI_UP].reserve( 4 );
	for ( int i = 0; i < 4; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Troll/Attack1/Up0%d.png", i);
		m_vecTex[TI_TROLL][MI_ATTACK1][DI_UP].push_back( LoadTexture( szBuf, D3DXVECTOR3(83.0f, 120.0f, 0) ) );
	}
	m_vecTex[TI_TROLL][MI_ATTACK1][DI_UPLEFT].reserve( 4 );
	for ( int i = 0; i < 4; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Troll/Attack1/Up-Left0%d.png", i);
		m_vecTex[TI_TROLL][MI_ATTACK1][DI_UPLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(113.0f, 126.0f, 0) ) );
	}

	//MI_DIE
	m_vecTex[TI_TROLL][MI_DIE][DI_DOWN].reserve( 4 );
	for ( int i = 0; i < 4; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Troll/Die/Down0%d.png", i);
		m_vecTex[TI_TROLL][MI_DIE][DI_DOWN].push_back( LoadTexture( szBuf, D3DXVECTOR3(92.0f, 79.0f, 0.0f) ) );
	}
	m_vecTex[TI_TROLL][MI_DIE][DI_DOWNLEFT].reserve( 4 );
	for ( int i = 0; i < 4; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Troll/Die/Down-Left0%d.png", i);
		m_vecTex[TI_TROLL][MI_DIE][DI_DOWNLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(155.0f, 78.0f, 0.0f) ) );
	}
	m_vecTex[TI_TROLL][MI_DIE][DI_LEFT].reserve( 4 );
	for ( int i = 0; i < 4; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Troll/Die/Left0%d.png", i);
		m_vecTex[TI_TROLL][MI_DIE][DI_LEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(202.0f, 89.0f, 0) ) );
	}
	m_vecTex[TI_TROLL][MI_DIE][DI_UP].reserve( 4 );
	for ( int i = 0; i < 4; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Troll/Die/Up0%d.png", i);
		m_vecTex[TI_TROLL][MI_DIE][DI_UP].push_back( LoadTexture( szBuf, D3DXVECTOR3(150.0f, 92.0f, 0) ) );
	}
	m_vecTex[TI_TROLL][MI_DIE][DI_UPLEFT].reserve( 4 );
	for ( int i = 0; i < 4; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Troll/Die/Up-Left0%d.png", i);
		m_vecTex[TI_TROLL][MI_DIE][DI_UPLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(198.0f, 92.0f, 0) ) );
	}

	//MI_STAND
	m_vecTex[TI_TROLL][MI_STAND][DI_DOWN].reserve( 1 );
	for ( int i = 0; i < 1; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Troll/Stand/Down0%d.png", i);
		m_vecTex[TI_TROLL][MI_STAND][DI_DOWN].push_back( LoadTexture( szBuf, D3DXVECTOR3(50.0f, 92.0f, 0.0f) ) );
	}
	m_vecTex[TI_TROLL][MI_STAND][DI_DOWNLEFT].reserve( 1 );
	for ( int i = 0; i < 1; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Troll/Stand/Down-Left0%d.png", i);
		m_vecTex[TI_TROLL][MI_STAND][DI_DOWNLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(100.0f, 92.0f, 0.0f) ) );
	}
	m_vecTex[TI_TROLL][MI_STAND][DI_LEFT].reserve( 1 );
	for ( int i = 0; i < 1; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Troll/Stand/Left0%d.png", i);
		m_vecTex[TI_TROLL][MI_STAND][DI_LEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(110.0f, 102.0f, 0) ) );
	}
	m_vecTex[TI_TROLL][MI_STAND][DI_UP].reserve( 1 );
	for ( int i = 0; i < 1; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Troll/Stand/Up0%d.png", i);			//
		m_vecTex[TI_TROLL][MI_STAND][DI_UP].push_back( LoadTexture( szBuf, D3DXVECTOR3(50.0f, 102.0f, 0) ) );
	}
	m_vecTex[TI_TROLL][MI_STAND][DI_UPLEFT].reserve( 1 );
	for ( int i = 0; i < 1; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Troll/Stand/Up-Left0%d.png", i);
		m_vecTex[TI_TROLL][MI_STAND][DI_UPLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(74.0f, 102.0f, 0) ) );
	}

	//MI_TAKE_HIT
	m_vecTex[TI_TROLL][MI_TAKE_HIT][DI_DOWN].reserve( 3 );
	for ( int i = 0; i < 3; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Troll/Take Hit/Down0%d.png", i);
		m_vecTex[TI_TROLL][MI_TAKE_HIT][DI_DOWN].push_back( LoadTexture( szBuf, D3DXVECTOR3(65.0f, 99.0f, 0.0f) ) );
	}
	m_vecTex[TI_TROLL][MI_TAKE_HIT][DI_DOWNLEFT].reserve( 3 );
	for ( int i = 0; i < 3; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Troll/Take Hit/Down-Left0%d.png", i);
		m_vecTex[TI_TROLL][MI_TAKE_HIT][DI_DOWNLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(77.0f, 93.0f, 0.0f) ) );
	}
	m_vecTex[TI_TROLL][MI_TAKE_HIT][DI_LEFT].reserve( 3 );
	for ( int i = 0; i < 3; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Troll/Take Hit/Left0%d.png", i);
		m_vecTex[TI_TROLL][MI_TAKE_HIT][DI_LEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(83.0f, 105.0f, 0) ) );
	}
	m_vecTex[TI_TROLL][MI_TAKE_HIT][DI_UP].reserve( 3 );
	for ( int i = 0; i < 3; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Troll/Take Hit/Up0%d.png", i);
		m_vecTex[TI_TROLL][MI_TAKE_HIT][DI_UP].push_back( LoadTexture( szBuf, D3DXVECTOR3(72.0f, 108.0f, 0) ) );
	}
	m_vecTex[TI_TROLL][MI_TAKE_HIT][DI_UPLEFT].reserve( 3 );
	for ( int i = 0; i < 3; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Troll/Take Hit/Up-Left0%d.png", i);
		m_vecTex[TI_TROLL][MI_TAKE_HIT][DI_UPLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(103.0f, 108.0f, 0) ) );
	}

	//MI_WALK_UNARMED
	m_vecTex[TI_TROLL][MI_WALK_UNARMED][DI_DOWN].reserve( 10 );
	for ( int i = 0; i < 10; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Troll/Walk/Down0%d.png", i);
		m_vecTex[TI_TROLL][MI_WALK_UNARMED][DI_DOWN].push_back( LoadTexture( szBuf, D3DXVECTOR3(65.0f, 100.0f, 0.0f) ) );
	}
	m_vecTex[TI_TROLL][MI_WALK_UNARMED][DI_DOWNLEFT].reserve( 10 );
	for ( int i = 0; i < 10; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Troll/Walk/Down-Left0%d.png", i);
		m_vecTex[TI_TROLL][MI_WALK_UNARMED][DI_DOWNLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(115.0f, 97.0f, 0.0f) ) );
	}
	m_vecTex[TI_TROLL][MI_WALK_UNARMED][DI_LEFT].reserve( 10 );
	for ( int i = 0; i < 10; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Troll/Walk/Left0%d.png", i);
		m_vecTex[TI_TROLL][MI_WALK_UNARMED][DI_LEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(136.0f, 100.0f, 0) ) );
	}
	m_vecTex[TI_TROLL][MI_WALK_UNARMED][DI_UP].reserve( 10 );
	for ( int i = 0; i < 10; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Troll/Walk/Up0%d.png", i);
		m_vecTex[TI_TROLL][MI_WALK_UNARMED][DI_UP].push_back( LoadTexture( szBuf, D3DXVECTOR3(65.0f, 110.0f, 0) ) );
	}
	m_vecTex[TI_TROLL][MI_WALK_UNARMED][DI_UPLEFT].reserve( 10 );
	for ( int i = 0; i < 10; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Troll/Walk/Up-Left0%d.png", i);
		m_vecTex[TI_TROLL][MI_WALK_UNARMED][DI_UPLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(116.0f, 105.0f, 0) ) );
	}
}

void CTextureLoader::BladeSprits()
{
	TCHAR szBuf[128];

	m_vecTex[TI_BLADE][MI_WALK_UNARMED][DI_DOWN].reserve( 10 );
	for ( int i = 0; i < 10; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Blade Sprits/Walk unarmed/Down0%d.png", i);
		m_vecTex[TI_BLADE][MI_WALK_UNARMED][DI_DOWN].push_back( LoadTexture( szBuf, D3DXVECTOR3(114.0f, 72.0f, 0.0f) ) );
	}
}

void CTextureLoader::Dragon()
{
	//MI_ATTACK1
	//MI_DIE
	//MI_MISC
	//MI_STAND
	//MI_TAKE_HIT
	//MI_WALK_UNARMED

	TCHAR szBuf[128];

	//MI_ATTACK1
	m_vecTex[TI_DRAGON][MI_ATTACK1][DI_DOWN].reserve( 4 );
	for ( int i = 0; i < 4; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Dragon/Attack1/Down0%d.png", i);
		m_vecTex[TI_DRAGON][MI_ATTACK1][DI_DOWN].push_back( LoadTexture( szBuf, D3DXVECTOR3(178.0f, 152.0f, 0.0f) ) );
	}
	m_vecTex[TI_DRAGON][MI_ATTACK1][DI_DOWNLEFT].reserve( 4 );
	for ( int i = 0; i < 4; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Dragon/Attack1/Down-Left0%d.png", i);
		m_vecTex[TI_DRAGON][MI_ATTACK1][DI_DOWNLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(175.0f, 159.0f, 0.0f) ) );
	}
	m_vecTex[TI_DRAGON][MI_ATTACK1][DI_LEFT].reserve( 4 );
	for ( int i = 0; i < 4; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Dragon/Attack1/Left0%d.png", i);
		m_vecTex[TI_DRAGON][MI_ATTACK1][DI_LEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(178.0f, 163.0f, 0.0f) ) );
	}
	m_vecTex[TI_DRAGON][MI_ATTACK1][DI_UP].reserve( 4 );
	for ( int i = 0; i < 4; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Dragon/Attack1/Up0%d.png", i);
		m_vecTex[TI_DRAGON][MI_ATTACK1][DI_UP].push_back( LoadTexture( szBuf, D3DXVECTOR3(180.0f, 156.0f, 0.0f) ) );
	}
	m_vecTex[TI_DRAGON][MI_ATTACK1][DI_UPLEFT].reserve( 4 );
	for ( int i = 0; i < 4; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Dragon/Attack1/Up-Left0%d.png", i);
		m_vecTex[TI_DRAGON][MI_ATTACK1][DI_UPLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(144.0f, 160.0f, 0.0f) ) );
	}
	
	//MI_DIE
	m_vecTex[TI_DRAGON][MI_DIE][DI_DOWN].reserve( 4 );
	for ( int i = 0; i < 4; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Dragon/Die/Down0%d.png", i);
		m_vecTex[TI_DRAGON][MI_DIE][DI_DOWN].push_back( LoadTexture( szBuf, D3DXVECTOR3(196.0f, 130.0f, 0.0f) ) );
	}
	m_vecTex[TI_DRAGON][MI_DIE][DI_DOWNLEFT].reserve( 4 );
	for ( int i = 0; i < 4; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Dragon/Die/Down-Left0%d.png", i);
		m_vecTex[TI_DRAGON][MI_DIE][DI_DOWNLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(189.0f, 128.0f, 0.0f) ) );
	}
	m_vecTex[TI_DRAGON][MI_DIE][DI_LEFT].reserve( 4 );
	for ( int i = 0; i < 4; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Dragon/Die/Left0%d.png", i);
		m_vecTex[TI_DRAGON][MI_DIE][DI_LEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(236.0f, 150.0f, 0.0f) ) );
	}
	m_vecTex[TI_DRAGON][MI_DIE][DI_UP].reserve( 4 );
	for ( int i = 0; i < 4; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Dragon/Die/Up0%d.png", i);
		m_vecTex[TI_DRAGON][MI_DIE][DI_UP].push_back( LoadTexture( szBuf, D3DXVECTOR3(169.0f, 146.0f, 0.0f) ) );
	}
	m_vecTex[TI_DRAGON][MI_DIE][DI_UPLEFT].reserve( 4 );
	for ( int i = 0; i < 4; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Dragon/Die/Up-Left0%d.png", i);
		m_vecTex[TI_DRAGON][MI_DIE][DI_UPLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(210.0f, 150.0f, 0.0f) ) );
	}

	//MI_MISC
	m_vecTex[TI_DRAGON][MI_MISC][DI_DOWN].reserve( 15 );
	for ( int i = 0; i < 15; ++i )
	{	
		if ( i < 10 )
			wsprintf(szBuf, L"../Texture/Character/Dragon/Misc/Down0%d.png", i);
		else
			wsprintf(szBuf, L"../Texture/Character/Dragon/Misc/Down%d.png", i);
		m_vecTex[TI_DRAGON][MI_MISC][DI_DOWN].push_back( LoadTexture( szBuf, D3DXVECTOR3(436.0f, 217.0f, 0.0f) ) );
	}
	m_vecTex[TI_DRAGON][MI_MISC][DI_DOWNLEFT].reserve( 15 );
	for ( int i = 0; i < 15; ++i )
	{	
		if ( i < 10 )
			wsprintf(szBuf, L"../Texture/Character/Dragon/Misc/Down-Left0%d.png", i);
		else
			wsprintf(szBuf, L"../Texture/Character/Dragon/Misc/Down-Left%d.png", i);

		m_vecTex[TI_DRAGON][MI_MISC][DI_DOWNLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(391.0f, 265.0f, 0.0f) ) );
	}
	m_vecTex[TI_DRAGON][MI_MISC][DI_LEFT].reserve( 15 );
	for ( int i = 0; i < 15; ++i )
	{	
		if ( i < 10 )
			wsprintf(szBuf, L"../Texture/Character/Dragon/Misc/Left0%d.png", i);
		else
			wsprintf(szBuf, L"../Texture/Character/Dragon/Misc/Left%d.png", i);

		m_vecTex[TI_DRAGON][MI_MISC][DI_LEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(340.0f, 270.0f, 0.0f) ) );
	}
	m_vecTex[TI_DRAGON][MI_MISC][DI_UP].reserve( 15 );
	for ( int i = 0; i < 15; ++i )
	{	
		if ( i < 10 )
			wsprintf(szBuf, L"../Texture/Character/Dragon/Misc/Up0%d.png", i);
		else
			wsprintf(szBuf, L"../Texture/Character/Dragon/Misc/Up%d.png", i);

		m_vecTex[TI_DRAGON][MI_MISC][DI_UP].push_back( LoadTexture( szBuf, D3DXVECTOR3(431.0f, 228.0f, 0.0f) ) );
	}
	m_vecTex[TI_DRAGON][MI_MISC][DI_UPLEFT].reserve( 15 );
	for ( int i = 0; i < 15; ++i )
	{	
		if ( i < 10 )
			wsprintf(szBuf, L"../Texture/Character/Dragon/Misc/Up-Left0%d.png", i);
		else
			wsprintf(szBuf, L"../Texture/Character/Dragon/Misc/Up-Left%d.png", i);

		m_vecTex[TI_DRAGON][MI_MISC][DI_UPLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(414.0f, 265.0f, 0.0f) ) );
	}

	//MI_STAND
	m_vecTex[TI_DRAGON][MI_STAND][DI_DOWN].reserve( 1 );
	for ( int i = 0; i < 1; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Dragon/Stand/Down0%d.png", i);
		m_vecTex[TI_DRAGON][MI_STAND][DI_DOWN].push_back( LoadTexture( szBuf, D3DXVECTOR3(94.0f, 148.0f, 0.0f) ) );
	}
	m_vecTex[TI_DRAGON][MI_STAND][DI_DOWNLEFT].reserve( 1 );
	for ( int i = 0; i < 1; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Dragon/Stand/Down-Left0%d.png", i);
		m_vecTex[TI_DRAGON][MI_STAND][DI_DOWNLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(137.0f, 153.0f, 0.0f) ) );
	}
	m_vecTex[TI_DRAGON][MI_STAND][DI_LEFT].reserve( 1 );
	for ( int i = 0; i < 1; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Dragon/Stand/Left0%d.png", i);
		m_vecTex[TI_DRAGON][MI_STAND][DI_LEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(140.0f, 166.0f, 0.0f) ) );
	}
	m_vecTex[TI_DRAGON][MI_STAND][DI_UP].reserve( 1 );
	for ( int i = 0; i < 1; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Dragon/Stand/Up0%d.png", i);
		m_vecTex[TI_DRAGON][MI_STAND][DI_UP].push_back( LoadTexture( szBuf, D3DXVECTOR3(77.0f, 154.0f, 0.0f) ) );
	}
	m_vecTex[TI_DRAGON][MI_STAND][DI_UPLEFT].reserve( 1 );
	for ( int i = 0; i < 1; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Dragon/Stand/Up-Left0%d.png", i);
		m_vecTex[TI_DRAGON][MI_STAND][DI_UPLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(104.0f, 160.0f, 0.0f) ) );
	}

	//MI_TAKE_HIT
	m_vecTex[TI_DRAGON][MI_TAKE_HIT][DI_DOWN].reserve( 3 );
	for ( int i = 0; i < 3; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Dragon/Walk/Down0%d.png", i);
		m_vecTex[TI_DRAGON][MI_TAKE_HIT][DI_DOWN].push_back( LoadTexture( szBuf, D3DXVECTOR3(102.0f, 152.0f, 0.0f) ) );
	}
	m_vecTex[TI_DRAGON][MI_TAKE_HIT][DI_DOWNLEFT].reserve( 3 );
	for ( int i = 0; i < 3; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Dragon/Walk/Down-Left0%d.png", i);
		m_vecTex[TI_DRAGON][MI_TAKE_HIT][DI_DOWNLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(136.0f, 153.0f, 0.0f) ) );
	}
	m_vecTex[TI_DRAGON][MI_TAKE_HIT][DI_LEFT].reserve( 3 );
	for ( int i = 0; i < 3; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Dragon/Walk/Left0%d.png", i);
		m_vecTex[TI_DRAGON][MI_TAKE_HIT][DI_LEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(164.0f, 166.0f, 0.0f) ) );
	}
	m_vecTex[TI_DRAGON][MI_TAKE_HIT][DI_UP].reserve( 3 );
	for ( int i = 0; i < 3; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Dragon/Walk/Up0%d.png", i);
		m_vecTex[TI_DRAGON][MI_TAKE_HIT][DI_UP].push_back( LoadTexture( szBuf, D3DXVECTOR3(96.0f, 153.0f, 0.0f) ) );
	}
	m_vecTex[TI_DRAGON][MI_TAKE_HIT][DI_UPLEFT].reserve( 3 );
	for ( int i = 0; i < 3; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Dragon/Walk/Up-Left0%d.png", i);
		m_vecTex[TI_DRAGON][MI_TAKE_HIT][DI_UPLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(148.0f, 160.0f, 0.0f) ) );
	}

	//MI_WALK_UNARMED
	m_vecTex[TI_DRAGON][MI_WALK_UNARMED][DI_DOWN].reserve( 10 );
	for ( int i = 0; i < 10; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Dragon/Walk/Down0%d.png", i);
		m_vecTex[TI_DRAGON][MI_WALK_UNARMED][DI_DOWN].push_back( LoadTexture( szBuf, D3DXVECTOR3(89.0f, 143.0f, 0.0f) ) );
	}
	m_vecTex[TI_DRAGON][MI_WALK_UNARMED][DI_DOWNLEFT].reserve( 10 );
	for ( int i = 0; i < 10; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Dragon/Walk/Down-Left0%d.png", i);
		m_vecTex[TI_DRAGON][MI_WALK_UNARMED][DI_DOWNLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(137.0f, 153.0f, 0.0f) ) );
	}
	m_vecTex[TI_DRAGON][MI_WALK_UNARMED][DI_LEFT].reserve( 10 );
	for ( int i = 0; i < 10; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Dragon/Walk/Left0%d.png", i);
		m_vecTex[TI_DRAGON][MI_WALK_UNARMED][DI_LEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(180.0f, 166.0f, 0.0f) ) );
	}
	m_vecTex[TI_DRAGON][MI_WALK_UNARMED][DI_UP].reserve( 10 );
	for ( int i = 0; i < 10; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Dragon/Walk/Up0%d.png", i);
		m_vecTex[TI_DRAGON][MI_WALK_UNARMED][DI_UP].push_back( LoadTexture( szBuf, D3DXVECTOR3(109.0f, 157.0f, 0.0f) ) );
	}
	m_vecTex[TI_DRAGON][MI_WALK_UNARMED][DI_UPLEFT].reserve( 10 );
	for ( int i = 0; i < 10; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Dragon/Walk/Up-Left0%d.png", i);
		m_vecTex[TI_DRAGON][MI_WALK_UNARMED][DI_UPLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(144.0f, 160.0f, 0.0f) ) );
	}
}

void CTextureLoader::Titan()
{
	//MI_ATTACK1
	//MI_DIE
	//MI_STAND
	//MI_TAKE_HIT
	//MI_WALK_UNARMED

	TCHAR szBuf[128];

	//MI_ATTACK1
	m_vecTex[TI_TITAN][MI_ATTACK1][DI_DOWN].reserve( 4 );
	for ( int i = 0; i < 4; ++i )
	{		
		wsprintf(szBuf, L"../Texture/Character/Titan/Attack1/Down0%d.png", i);
		m_vecTex[TI_TITAN][MI_ATTACK1][DI_DOWN].push_back( LoadTexture( szBuf, D3DXVECTOR3(223.0f, 210.0f, 0.0f) ) );
	}
	m_vecTex[TI_TITAN][MI_ATTACK1][DI_DOWNLEFT].reserve( 4 );
	for ( int i = 0; i < 4; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Titan/Attack1/Down-Left0%d.png", i);
		m_vecTex[TI_TITAN][MI_ATTACK1][DI_DOWNLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(217.0f, 210.0f, 0.0f) ) );
	}
	m_vecTex[TI_TITAN][MI_ATTACK1][DI_LEFT].reserve( 4 );
	for ( int i = 0; i < 4; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Titan/Attack1/Left0%d.png", i);
		m_vecTex[TI_TITAN][MI_ATTACK1][DI_LEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(201.0f, 201.0f, 0.0f) ) );
	}
	m_vecTex[TI_TITAN][MI_ATTACK1][DI_UP].reserve( 4 );
	for ( int i = 0; i < 4; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Titan/Attack1/Up0%d.png", i);
		m_vecTex[TI_TITAN][MI_ATTACK1][DI_UP].push_back( LoadTexture( szBuf, D3DXVECTOR3(127.0f, 164.0f, 0.0f) ) );
	}
	m_vecTex[TI_TITAN][MI_ATTACK1][DI_UPLEFT].reserve( 4 );
	for ( int i = 0; i < 4; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Titan/Attack1/Up-Left0%d.png", i);
		m_vecTex[TI_TITAN][MI_ATTACK1][DI_UPLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(128.0f, 181.0f, 0.0f) ) );
	}
	
	//MI_DIE
	m_vecTex[TI_TITAN][MI_DIE][DI_DOWN].reserve( 4 );
	for ( int i = 0; i < 4; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Titan/Die/Down0%d.png", i);
		m_vecTex[TI_TITAN][MI_DIE][DI_DOWN].push_back( LoadTexture( szBuf, D3DXVECTOR3(75.0f, 122.0f, 0.0f) ) );
	}
	m_vecTex[TI_TITAN][MI_DIE][DI_DOWNLEFT].reserve( 4 );
	for ( int i = 0; i < 4; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Titan/Die/Down-Left0%d.png", i);
		m_vecTex[TI_TITAN][MI_DIE][DI_DOWNLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(220.0f, 125.0f, 0.0f) ) );
	}
	m_vecTex[TI_TITAN][MI_DIE][DI_LEFT].reserve( 4 );
	for ( int i = 0; i < 4; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Titan/Die/Left0%d.png", i);
		m_vecTex[TI_TITAN][MI_DIE][DI_LEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(246.0f, 130.0f, 0.0f) ) );
	}
	m_vecTex[TI_TITAN][MI_DIE][DI_UP].reserve( 4 );
	for ( int i = 0; i < 4; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Titan/Die/Up0%d.png", i);
		m_vecTex[TI_TITAN][MI_DIE][DI_UP].push_back( LoadTexture( szBuf, D3DXVECTOR3(180.0f, 140.0f, 0.0f) ) );
	}
	m_vecTex[TI_TITAN][MI_DIE][DI_UPLEFT].reserve( 4 );
	for ( int i = 0; i < 4; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Titan/Die/Up-Left0%d.png", i);
		m_vecTex[TI_TITAN][MI_DIE][DI_UPLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(240.0f, 132.0f, 0.0f) ) );
	}
	
	//MI_STAND
	m_vecTex[TI_TITAN][MI_STAND][DI_DOWN].reserve( 1 );
	for ( int i = 0; i < 1; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Titan/Stand/Down0%d.png", i);
		m_vecTex[TI_TITAN][MI_STAND][DI_DOWN].push_back( LoadTexture( szBuf, D3DXVECTOR3(79.0f, 139.0f, 0.0f) ) );
	}
	m_vecTex[TI_TITAN][MI_STAND][DI_DOWNLEFT].reserve( 1 );
	for ( int i = 0; i < 1; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Titan/Stand/Down-Left0%d.png", i);
		m_vecTex[TI_TITAN][MI_STAND][DI_DOWNLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(150.0f, 145.0f, 0.0f) ) );
	}
	m_vecTex[TI_TITAN][MI_STAND][DI_LEFT].reserve( 1 );
	for ( int i = 0; i < 1; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Titan/Stand/Left0%d.png", i);
		m_vecTex[TI_TITAN][MI_STAND][DI_LEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(168.0f, 147.0f, 0.0f) ) );
	}
	m_vecTex[TI_TITAN][MI_STAND][DI_UP].reserve( 1 );
	for ( int i = 0; i < 1; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Titan/Stand/Up0%d.png", i);
		m_vecTex[TI_TITAN][MI_STAND][DI_UP].push_back( LoadTexture( szBuf, D3DXVECTOR3(78.0f, 148.0f, 0.0f) ) );
	}
	m_vecTex[TI_TITAN][MI_STAND][DI_UPLEFT].reserve( 1 );
	for ( int i = 0; i < 1; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Titan/Stand/Up-Left0%d.png", i);
		m_vecTex[TI_TITAN][MI_STAND][DI_UPLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(126.0f, 150.0f, 0.0f) ) );
	}

	//MI_TAKE_HIT
	m_vecTex[TI_TITAN][MI_TAKE_HIT][DI_DOWN].reserve( 3 );
	for ( int i = 0; i < 3; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Titan/Walk/Down0%d.png", i);
		m_vecTex[TI_TITAN][MI_TAKE_HIT][DI_DOWN].push_back( LoadTexture( szBuf, D3DXVECTOR3(136.0f, 168.0f, 0.0f) ) );
	}
	m_vecTex[TI_TITAN][MI_TAKE_HIT][DI_DOWNLEFT].reserve( 3 );
	for ( int i = 0; i < 3; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Titan/Walk/Down-Left0%d.png", i);
		m_vecTex[TI_TITAN][MI_TAKE_HIT][DI_DOWNLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(116.0f, 169.0f, 0.0f) ) );
	}
	m_vecTex[TI_TITAN][MI_TAKE_HIT][DI_LEFT].reserve( 3 );
	for ( int i = 0; i < 3; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Titan/Walk/Left0%d.png", i);
		m_vecTex[TI_TITAN][MI_TAKE_HIT][DI_LEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(129.0f, 177.0f, 0.0f) ) );
	}
	m_vecTex[TI_TITAN][MI_TAKE_HIT][DI_UP].reserve( 3 );
	for ( int i = 0; i < 3; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Titan/Walk/Up0%d.png", i);
		m_vecTex[TI_TITAN][MI_TAKE_HIT][DI_UP].push_back( LoadTexture( szBuf, D3DXVECTOR3(97.0f, 190.0f, 0.0f) ) );
	}
	m_vecTex[TI_TITAN][MI_TAKE_HIT][DI_UPLEFT].reserve( 3 );
	for ( int i = 0; i < 3; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Titan/Walk/Up-Left0%d.png", i);
		m_vecTex[TI_TITAN][MI_TAKE_HIT][DI_UPLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(90.0f, 190.0f, 0.0f) ) );
	}

	//MI_WALK_UNARMED
	m_vecTex[TI_TITAN][MI_WALK_UNARMED][DI_DOWN].reserve( 10 );
	for ( int i = 0; i < 10; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Titan/Walk/Down0%d.png", i);
		m_vecTex[TI_TITAN][MI_WALK_UNARMED][DI_DOWN].push_back( LoadTexture( szBuf, D3DXVECTOR3(109.0f, 143.0f, 0.0f) ) );
	}
	m_vecTex[TI_TITAN][MI_WALK_UNARMED][DI_DOWNLEFT].reserve( 10 );
	for ( int i = 0; i < 10; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Titan/Walk/Down-Left0%d.png", i);
		m_vecTex[TI_TITAN][MI_WALK_UNARMED][DI_DOWNLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(150.0f, 150.0f, 0.0f) ) );
	}
	m_vecTex[TI_TITAN][MI_WALK_UNARMED][DI_LEFT].reserve( 10 );
	for ( int i = 0; i < 10; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Titan/Walk/Left0%d.png", i);
		m_vecTex[TI_TITAN][MI_WALK_UNARMED][DI_LEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(200.0f, 147.0f, 0.0f) ) );
	}
	m_vecTex[TI_TITAN][MI_WALK_UNARMED][DI_UP].reserve( 10 );
	for ( int i = 0; i < 10; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Titan/Walk/Up0%d.png", i);
		m_vecTex[TI_TITAN][MI_WALK_UNARMED][DI_UP].push_back( LoadTexture( szBuf, D3DXVECTOR3(109.0f, 158.0f, 0.0f) ) );
	}
	m_vecTex[TI_TITAN][MI_WALK_UNARMED][DI_UPLEFT].reserve( 10 );
	for ( int i = 0; i < 10; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Character/Titan/Walk/Up-Left0%d.png", i);
		m_vecTex[TI_TITAN][MI_WALK_UNARMED][DI_UPLEFT].push_back( LoadTexture( szBuf, D3DXVECTOR3(150.0f, 146.0f, 0.0f) ) );
	}
}

void CTextureLoader::Small_Wood_and_Plaster_House()
{
	TCHAR szBuf[128];

	//wall & window wall
	m_vecTex[TI_SMALLHOUSE][MI_PLASTERWALL][DI_DOWN].reserve( 15 );
	for ( int i = 0; i < 15; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Static Object/Multi/Small Wood and Plaster House/plaster wall_%d.png", i);
		if ( i >= 9 )
		{
			m_vecTex[TI_SMALLHOUSE][MI_PLASTERWALL][DI_DOWN].push_back( LoadTexture( szBuf, D3DXVECTOR3(44.0f, 122.0f, 0.0f) ) );
		}
		else
		{
			m_vecTex[TI_SMALLHOUSE][MI_PLASTERWALL][DI_DOWN].push_back( LoadTexture( szBuf, D3DXVECTOR3(44.0f, 106.0f, 0.0f) ) );
		}
	}
	wsprintf(szBuf, L"../Texture/Static Object/Multi/Small Wood and Plaster House/wooden post.png");
	m_vecTex[TI_SMALLHOUSE][MI_PLASTERWALL][DI_DOWN].push_back( LoadTexture( szBuf, D3DXVECTOR3(44.0f, 122.0f, 0.0f) ) );
	
	//stone floor & stairs
	m_vecTex[TI_SMALLHOUSE][MI_STONESTAIR][DI_DOWN].reserve( 4 );
	wsprintf(szBuf, L"../Texture/Static Object/Multi/Small Wood and Plaster House/stone stairs_0.png");
	m_vecTex[TI_SMALLHOUSE][MI_STONESTAIR][DI_DOWN].push_back( LoadTexture( szBuf, D3DXVECTOR3(44.0f, 44.0f, 0.0f) ) );
	wsprintf(szBuf, L"../Texture/Static Object/Multi/Small Wood and Plaster House/stone stairs_1.png");
	m_vecTex[TI_SMALLHOUSE][MI_STONESTAIR][DI_DOWN].push_back( LoadTexture( szBuf, D3DXVECTOR3(44.0f, 30.0f, 0.0f) ) );
	wsprintf(szBuf, L"../Texture/Static Object/Multi/Small Wood and Plaster House/stone stairs_2.png");
	m_vecTex[TI_SMALLHOUSE][MI_STONESTAIR][DI_DOWN].push_back( LoadTexture( szBuf, D3DXVECTOR3(44.0f, 44.0f, 0.0f) ) );
	wsprintf(szBuf, L"../Texture/Static Object/Multi/Small Wood and Plaster House/stone stairs_3.png");
	m_vecTex[TI_SMALLHOUSE][MI_STONESTAIR][DI_DOWN].push_back( LoadTexture( szBuf, D3DXVECTOR3(44.0f, 42.0f, 0.0f) ) );
	
	//wooden board
	m_vecTex[TI_SMALLHOUSE][MI_WOODENBOARDS][DI_DOWN].reserve( 9 );
	for ( int i = 0; i < 9; ++i )
	{	
		wsprintf(szBuf, L"../Texture/Static Object/Multi/Small Wood and Plaster House/wooden boards_%d.png", i);
		m_vecTex[TI_SMALLHOUSE][MI_WOODENBOARDS][DI_DOWN].push_back( LoadTexture( szBuf, D3DXVECTOR3(44.0f, 44.0f, 0.0f) ) );
	}

	//door
	m_vecTex[TI_SMALLHOUSE][MI_DOOR][DI_DOWN].reserve( 3 );
	wsprintf(szBuf, L"../Texture/Static Object/Multi/Small Wood and Plaster House/wooden door_0.png");
	m_vecTex[TI_SMALLHOUSE][MI_DOOR][DI_DOWN].push_back( LoadTexture( szBuf, D3DXVECTOR3(44.0f, 102.0f, 0.0f) ) );
	wsprintf(szBuf, L"../Texture/Static Object/Multi/Small Wood and Plaster House/wooden door_1.png");
	m_vecTex[TI_SMALLHOUSE][MI_DOOR][DI_DOWN].push_back( LoadTexture( szBuf, D3DXVECTOR3(132.0f, 116.0f, 0.0f) ) );
	wsprintf(szBuf, L"../Texture/Static Object/Multi/Small Wood and Plaster House/wooden post.png");
	m_vecTex[TI_SMALLHOUSE][MI_DOOR][DI_DOWN].push_back( LoadTexture( szBuf, D3DXVECTOR3(44.0f, 90.0f, 0.0f) ) );

	//shingle
	m_vecTex[TI_SMALLHOUSE][MI_SHINGLE][DI_DOWN].reserve( 3 );
	wsprintf(szBuf, L"../Texture/Static Object/Multi/Small Wood and Plaster House/wooden shingle_0.png");
	m_vecTex[TI_SMALLHOUSE][MI_SHINGLE][DI_DOWN].push_back( LoadTexture( szBuf, D3DXVECTOR3(50.0f, 142.0f, 0.0f) ) );
	wsprintf(szBuf, L"../Texture/Static Object/Multi/Small Wood and Plaster House/wooden shingle_1.png");
	m_vecTex[TI_SMALLHOUSE][MI_SHINGLE][DI_DOWN].push_back( LoadTexture( szBuf, D3DXVECTOR3(54.0f, 158.0f, 0.0f) ) );
	wsprintf(szBuf, L"../Texture/Static Object/Multi/Small Wood and Plaster House/wooden shingle_2.png");
	m_vecTex[TI_SMALLHOUSE][MI_SHINGLE][DI_DOWN].push_back( LoadTexture( szBuf, D3DXVECTOR3(44.0f, 144.0f, 0.0f) ) );
	
}

void CTextureLoader::Trees()
{
	TCHAR szBuf[128];
	//apple tree
	m_vecTex[TI_TREEAPPLE][MI_TREE][DI_DOWN].reserve( 2 );
	wsprintf(szBuf, L"../Texture/Static Object/apple tree/apple tree.png");
	m_vecTex[TI_TREEAPPLE][MI_TREE][DI_DOWN].push_back( LoadTexture( szBuf, D3DXVECTOR3(113.0f, 129.0f, 0.0f) ) );
	wsprintf(szBuf, L"../Texture/Static Object/apple tree/apple leaves.png");
	m_vecTex[TI_TREEAPPLE][MI_TREE][DI_DOWN].push_back( LoadTexture( szBuf, D3DXVECTOR3(143.0f, 170.0f, 0.0f) ) );
	
	//big apple tree
	m_vecTex[TI_TREEBIGAPPLE][MI_TREE][DI_DOWN].reserve( 2 );
	wsprintf(szBuf, L"../Texture/Static Object/big apple tree/big apple tree.png");
	m_vecTex[TI_TREEBIGAPPLE][MI_TREE][DI_DOWN].push_back( LoadTexture( szBuf, D3DXVECTOR3(132.0f, 146.0f, 0.0f) ) );
	wsprintf(szBuf, L"../Texture/Static Object/big apple tree/big apple leaves.png");
	m_vecTex[TI_TREEBIGAPPLE][MI_TREE][DI_DOWN].push_back( LoadTexture( szBuf, D3DXVECTOR3(152.0f, 189.0f, 0.0f) ) );

	//pear tree
	m_vecTex[TI_TREEPEAR][MI_TREE][DI_DOWN].reserve( 2 );
	wsprintf(szBuf, L"../Texture/Static Object/pear tree/pear tree.png");
	m_vecTex[TI_TREEPEAR][MI_TREE][DI_DOWN].push_back( LoadTexture( szBuf, D3DXVECTOR3(98.0f, 139.0f, 0.0f) ) );
	wsprintf(szBuf, L"../Texture/Static Object/pear tree/pear leaves.png");
	m_vecTex[TI_TREEPEAR][MI_TREE][DI_DOWN].push_back( LoadTexture( szBuf, D3DXVECTOR3(118.0f, 168.0f, 0.0f) ) );
}

void CTextureLoader::Bloods()
{
	m_vecTex[TI_BLOOD][MI_BLOOD][DI_DOWN].reserve( 3 );	
	m_vecTex[TI_BLOOD][MI_BLOOD][DI_DOWN].push_back( LoadTexture( L"../Texture/UI/blood00.png"
																, D3DXVECTOR3(44.0f, 35.0f, 0.0f) ) );
	m_vecTex[TI_BLOOD][MI_BLOOD][DI_DOWN].push_back( LoadTexture( L"../Texture/UI/blood01.png"
																, D3DXVECTOR3(43.0f, 37.0f, 0.0f) ) );
	m_vecTex[TI_BLOOD][MI_BLOOD][DI_DOWN].push_back( LoadTexture( L"../Texture/UI/blood02.png"
																, D3DXVECTOR3(44.0f, 42.0f, 0.0f) ) );
}

void CTextureLoader::Release()
{
	for ( _INT i = 0; i < TI_END; ++i )
	{
		for ( _INT j = 0; j < MI_END; ++j )
		{
			for ( _INT k = 0; k < DI_END; ++k )
			{
				for ( _UINT l = 0; l < m_vecTex[i][j][k].size(); ++l )
				{
					m_vecTex[i][j][k][l]->pTex->Release();
					delete m_vecTex[i][j][k][l];
				}
				m_vecTex[i][j][k].clear();
			}
		}
	}

	m_pTexLoad->pTex->Release();
	delete m_pTexLoad;
	m_pTexLoad = NULL;
}






