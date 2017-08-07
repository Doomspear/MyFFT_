#pragma once

#include "Defines.h"

class CTextureLoader
{
private:
	//map test
	map< TEXTURE_ID, vector<LPDIRECT3DTEXTURE9>* >	m_mapTex;
	
	//3차원 이미지벡터	[텍스쳐ID] [미들ID] [다이렉션ID]
	//vector<LPDIRECT3DTEXTURE9>						m_vecTex[TI_END][MI_END][DI_END];
	vector<PTEXTURE>						m_vecTex[TI_END][MI_END][DI_END];

	PTEXTURE		m_pTexLoad;

private:
	//LPDIRECT3DTEXTURE9 LoadTexture(TCHAR* pFileName);
	PTEXTURE LoadTexture(TCHAR* pFileName, D3DXVECTOR3 vCenter);
		
public:
	vector<PTEXTURE> (*CTextureLoader::GetTextureVector())[TI_END][MI_END][DI_END];

//Sprite Load
public:
	//set
	void LoadStaticObj	();
	void LoadCharacter	();
	void LoadItem		();
	void LoadUI			();

	//Character
	void Woman			();
	void Vendor			();
	void Chicken		();
	void BladeSprits	();
	void Daemon			();
	void Troll			();
	void Dragon			();
	void Titan			();
		
	//Item
	void DeathShroud	();
	void Robe			();
	void Halberd		();
	
	//static object
	void Small_Wood_and_Plaster_House();
	void Trees();
	void Bloods();

	/*void firecolumn();
	void fieldoffire();
	
	void Smoke();
	
	void MiscItems();*/

	//UI
	//void BodyPart();
	//void InGameButton();
	//void MouseCursor();
	//void ProfileImage();
	//void VendorUI();
	//void EtcUI();

public:
	HRESULT Init();
	void Release();

/*-singleton-*/
private:
	static CTextureLoader*		m_pInst;
public:
	inline static CTextureLoader* GetInst()
	{
		if ( m_pInst == NULL )
		{
			m_pInst = new CTextureLoader;
		}
		return m_pInst;
	}

	inline void DestroyInst()
	{
		if ( m_pInst != NULL )
		{
			delete m_pInst;
			m_pInst = NULL;
		}
	}
private:
	CTextureLoader(void);
	~CTextureLoader(void);
/*-singleton-*/
};

