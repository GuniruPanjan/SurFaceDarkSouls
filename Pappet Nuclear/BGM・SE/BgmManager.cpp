#include "BgmManager.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
BgmManager::BgmManager():
	m_titleBGM(0),
	m_gameBGM(0),
	m_bossBGM(0),
	m_clearBGM(0),
	m_volumePal(0)
{
	
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
BgmManager::~BgmManager()
{
	//���������
	//BGM
	DeleteSoundMem(m_titleBGM);
	DeleteSoundMem(m_gameBGM);
	DeleteSoundMem(m_bossBGM);
	DeleteSoundMem(m_clearBGM);

	
}

/// <summary>
/// �^�C�g��BGM�̏���������
/// </summary>
void BgmManager::TitleInit()
{
	//BGM�ǂݍ���
	m_titleBGM = LoadSoundMem("Data/BGM/TitleBGM.mp3");
}

/// <summary>
/// �Q�[��BGM�̏���������
/// </summary>
void BgmManager::GameInit()
{
	//BGM�ǂݍ���
	m_gameBGM = LoadSoundMem("Data/BGM/GameBGM.mp3");
	m_bossBGM = LoadSoundMem("Data/BGM/BossBGM.mp3");
}

/// <summary>
/// �N���ABGM�̏���������
/// </summary>
void BgmManager::ClearInit()
{
	//BGM�ǂݍ���
	m_clearBGM = LoadSoundMem("Data/BGM/ClearBGM.mp3");
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="volume">����</param>
void BgmManager::Update(int volume)
{
	m_volumePal = volume;

	//���ʂ�ς���
	//BGM
	ChangeVolumeSoundMem(m_volumePal, m_titleBGM);
	ChangeVolumeSoundMem(m_volumePal, m_gameBGM);
	ChangeVolumeSoundMem(m_volumePal, m_bossBGM);
	ChangeVolumeSoundMem(m_volumePal, m_clearBGM);

}

/// <summary>
/// �^�C�g��BGM�X�V����
/// </summary>
void BgmManager::TitleBGM()
{
	PlaySoundMem(m_titleBGM, DX_PLAYTYPE_LOOP, true);
}

/// <summary>
/// �Q�[��BGM�X�V����
/// </summary>
void BgmManager::GameBGM()
{
	PlaySoundMem(m_gameBGM, DX_PLAYTYPE_LOOP, true);
}

/// <summary>
/// �{�XBGM�X�V����
/// </summary>
void BgmManager::BossBGM()
{
	StopSoundMem(m_gameBGM);   //�T�E���h���~�߂�

	PlaySoundMem(m_bossBGM, DX_PLAYTYPE_LOOP, true);
}

/// <summary>
/// �N���ABGM�X�V����
/// </summary>
void BgmManager::ClearBGM()
{
	PlaySoundMem(m_clearBGM, DX_PLAYTYPE_LOOP, true);
}

/// <summary>
/// �I������
/// </summary>
void BgmManager::End()
{
	//���������
	//BGM
	DeleteSoundMem(m_titleBGM);
	DeleteSoundMem(m_gameBGM);
	DeleteSoundMem(m_bossBGM);
	DeleteSoundMem(m_clearBGM);
}
