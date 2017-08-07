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
	//���̷�Ʈ ���� �������̽�
	LPDIRECTSOUND				m_pSound;
	vector<LPDIRECTSOUNDBUFFER> m_vecSoundBuff;
public:
	HRESULT Init(void);
	HRESULT LoadWave(TCHAR* pFileName);	//���ϰ�θ� ���� ������ �о� �帮�ڴ�.
	void SoundPlay(unsigned int iIndex, DWORD dwFlag); //������ ��� �ϰڴ�.
	void SoundStop(unsigned int iIndex);
	bool SoundPlaying(int iIndex);
public:
	CSoundDevice(void);
	~CSoundDevice(void);
};
