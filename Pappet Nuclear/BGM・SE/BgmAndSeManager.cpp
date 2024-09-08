#include "BgmAndSeManager.h"

BgmAndSeManager::BgmAndSeManager():
	m_titleBGM(0),
	m_gameBGM(0),
	m_bossBGM(0),
	m_clearBGM(0),
	m_volumePal(0)
{
	
}

BgmAndSeManager::~BgmAndSeManager()
{
	//���������
	//BGM
	DeleteSoundMem(m_titleBGM);
	DeleteSoundMem(m_gameBGM);
	DeleteSoundMem(m_bossBGM);
	DeleteSoundMem(m_clearBGM);

	
}

void BgmAndSeManager::TitleInit()
{
	//BGM�ǂݍ���
	m_titleBGM = LoadSoundMem("Data/BGM/TitleBGM.mp3");
}

void BgmAndSeManager::GameInit()
{
	//BGM�ǂݍ���
	m_gameBGM = LoadSoundMem("Data/BGM/GameBGM.mp3");
	m_bossBGM = LoadSoundMem("Data/BGM/BossBGM.mp3");
}

void BgmAndSeManager::ClearInit()
{
	//BGM�ǂݍ���
	m_clearBGM = LoadSoundMem("Data/BGM/ClearBGM.mp3");
}

void BgmAndSeManager::Update(int volume)
{
	m_volumePal = volume;

	//���ʂ�ς���
	//BGM
	ChangeVolumeSoundMem(m_volumePal, m_titleBGM);
	ChangeVolumeSoundMem(m_volumePal, m_gameBGM);
	ChangeVolumeSoundMem(m_volumePal, m_bossBGM);
	ChangeVolumeSoundMem(m_volumePal, m_clearBGM);

}

void BgmAndSeManager::TitleBGM()
{
	PlaySoundMem(m_titleBGM, DX_PLAYTYPE_LOOP, true);
}

void BgmAndSeManager::GameBGM()
{
	PlaySoundMem(m_gameBGM, DX_PLAYTYPE_LOOP, true);
}

void BgmAndSeManager::BossBGM()
{
	StopSoundMem(m_gameBGM);   //�T�E���h���~�߂�

	PlaySoundMem(m_bossBGM, DX_PLAYTYPE_LOOP, true);
}

void BgmAndSeManager::ClearBGM()
{
	PlaySoundMem(m_clearBGM, DX_PLAYTYPE_LOOP, true);
}

void BgmAndSeManager::End()
{
	//���������
	//BGM
	DeleteSoundMem(m_titleBGM);
	DeleteSoundMem(m_gameBGM);
	DeleteSoundMem(m_bossBGM);
	DeleteSoundMem(m_clearBGM);
}
