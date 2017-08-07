#pragma once

#include "SingleTon.h"

class CSound : public CSingleTon<CSound>
{
private:
	//���̷�Ʈ ���� �������̽�
	LPDIRECTSOUND				m_pSound;
	vector<LPDIRECTSOUNDBUFFER> m_vecSoundBuff;
public:
	HRESULT Init(void);
	HRESULT LoadWave(TCHAR* pFileName);	//���ϰ�θ� ���� ������ �о� �帮�ڴ�.
	void SoundPlay(_INT iIndex, DWORD dwFlag); //������ ��� �ϰڴ�.
	void SoundStop(_INT iIndex);
	bool SoundPlaying(_INT iIndex);
	void Release(void);

public:
	CSound(void);
	virtual ~CSound(void);
};
