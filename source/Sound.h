#pragma once

#include "SingleTon.h"

class CSound : public CSingleTon<CSound>
{
private:
	//다이렉트 사운드 인터페이스
	LPDIRECTSOUND				m_pSound;
	vector<LPDIRECTSOUNDBUFFER> m_vecSoundBuff;
public:
	HRESULT Init(void);
	HRESULT LoadWave(TCHAR* pFileName);	//파일경로를 통해 파일을 읽어 드리겠다.
	void SoundPlay(_INT iIndex, DWORD dwFlag); //파일을 재생 하겠다.
	void SoundStop(_INT iIndex);
	bool SoundPlaying(_INT iIndex);
	void Release(void);

public:
	CSound(void);
	virtual ~CSound(void);
};
