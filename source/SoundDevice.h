#pragma once

#include "Defines.h"

class CSoundDevice
{
private:
	static CSoundDevice* m_pInst;
public:
	static inline CSoundDevice* GetInst(void)
	{
		if(!m_pInst)
			m_pInst = new CSoundDevice;

		return m_pInst;
	}
public:
	inline void DestroyInst(void)
	{
		if(m_pInst)
		{
			delete m_pInst;
			m_pInst = NULL;
		}
	}
private:
	//다이렉트 사운드 인터페이스
	LPDIRECTSOUND				m_pSound;
	vector<LPDIRECTSOUNDBUFFER> m_vecSoundBuff;
public:
	HRESULT Init(void);
	HRESULT LoadWave(TCHAR* pFileName);	//파일경로를 통해 파일을 읽어 드리겠다.
	void SoundPlay(unsigned int iIndex, DWORD dwFlag); //파일을 재생 하겠다.
	void SoundStop(unsigned int iIndex);
	bool SoundPlaying(int iIndex);
public:
	CSoundDevice(void);
	~CSoundDevice(void);
};
