#include "SEManager.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
SEManager::SEManager():
	m_buttonSE(0),
	m_selectSE(0),
	m_hitSE(0),
	m_playerHitSE(0),
	m_attackSE(0),
	m_walkSE(0),
	m_playerHeelSE(0),
	m_playerRestSE(0),
	m_bossVoiceSE(0),
	m_bossWalkSE(0),
	m_diedSE(0),
	m_volumePal(0)
{
	for (int i = 0; i < 3; i++)
	{
		m_bossAttackSE[i] = 0;
	}
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
SEManager::~SEManager()
{
	//���������
	//SE
	DeleteSoundMem(m_buttonSE);
	DeleteSoundMem(m_selectSE);
	DeleteSoundMem(m_hitSE);
	DeleteSoundMem(m_playerHitSE);
	DeleteSoundMem(m_attackSE);
	DeleteSoundMem(m_walkSE);
	DeleteSoundMem(m_playerHeelSE);
	DeleteSoundMem(m_playerRestSE);
	DeleteSoundMem(m_bossVoiceSE);
	DeleteSoundMem(m_bossAttackSE[0]);
	DeleteSoundMem(m_bossAttackSE[1]);
	DeleteSoundMem(m_bossAttackSE[2]);
	DeleteSoundMem(m_bossWalkSE);
	DeleteSoundMem(m_diedSE);
}

/// <summary>
/// �V�[��SE�̏���������
/// </summary>
void SEManager::SceneInit()
{
	//SE�ǂݍ���
	m_buttonSE = LoadSoundMem("Data/SE/ButtonSE.mp3");
	m_selectSE = LoadSoundMem("Data/SE/SelectSE.mp3");
}

/// <summary>
/// �L����SE�̏���������
/// </summary>
void SEManager::CharaInit()
{
	//SE�ǂݍ���
	m_hitSE = LoadSoundMem("Data/SE/HitSE.mp3");
	m_playerHitSE = LoadSoundMem("Data/SE/PlayerToBossHitSE.mp3");
	m_attackSE = LoadSoundMem("Data/SE/AttackSE.mp3");
	m_walkSE = LoadSoundMem("Data/SE/WalkSE.mp3");
	m_playerHeelSE = LoadSoundMem("Data/SE/HeelSE.mp3");
	m_playerRestSE = LoadSoundMem("Data/SE/RestSE.mp3");
	m_diedSE = LoadSoundMem("Data/SE/DiedSE.mp3");
	
}

/// <summary>
/// �{�XSE�̏���������
/// </summary>
void SEManager::BossInit()
{
	//SE�ǂݍ���
	m_bossVoiceSE = LoadSoundMem("Data/SE/BossVoiceSE.mp3");
	m_bossAttackSE[0] = LoadSoundMem("Data/SE/BossAttack1SE.mp3");
	m_bossAttackSE[1] = LoadSoundMem("Data/SE/BossAttack2SE.mp3");
	m_bossAttackSE[2] = LoadSoundMem("Data/SE/BossAttack3SE.mp3");
	m_bossWalkSE = LoadSoundMem("Data/SE/BossWalkSE.mp3");
	m_diedSE = LoadSoundMem("Data/SE/DiedSE.mp3");
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="volume">����</param>
void SEManager::Update(int volume)
{
	m_volumePal = volume;

	//SE
	ChangeVolumeSoundMem(m_volumePal, m_buttonSE);
	ChangeVolumeSoundMem(m_volumePal, m_selectSE);
	ChangeVolumeSoundMem(m_volumePal, m_hitSE);
	ChangeVolumeSoundMem(m_volumePal, m_playerHitSE);
	ChangeVolumeSoundMem(m_volumePal, m_attackSE);
	ChangeVolumeSoundMem(m_volumePal, m_walkSE);
	ChangeVolumeSoundMem(m_volumePal, m_playerHeelSE);
	ChangeVolumeSoundMem(m_volumePal, m_playerRestSE);
	ChangeVolumeSoundMem(m_volumePal, m_bossVoiceSE);
	ChangeVolumeSoundMem(m_volumePal, m_bossAttackSE[0]);
	ChangeVolumeSoundMem(m_volumePal, m_bossAttackSE[1]);
	ChangeVolumeSoundMem(m_volumePal, m_bossAttackSE[2]);
	ChangeVolumeSoundMem(m_volumePal, m_bossWalkSE);
	ChangeVolumeSoundMem(m_volumePal, m_diedSE);
}

/// <summary>
/// �I������
/// </summary>
void SEManager::End()
{
	//SE
	DeleteSoundMem(m_buttonSE);
	DeleteSoundMem(m_selectSE);
	DeleteSoundMem(m_hitSE);
	DeleteSoundMem(m_playerHitSE);
	DeleteSoundMem(m_attackSE);
	DeleteSoundMem(m_walkSE);
	DeleteSoundMem(m_playerHeelSE);
	DeleteSoundMem(m_playerRestSE);
	DeleteSoundMem(m_bossVoiceSE);
	DeleteSoundMem(m_bossAttackSE[0]);
	DeleteSoundMem(m_bossAttackSE[1]);
	DeleteSoundMem(m_bossAttackSE[2]);
	DeleteSoundMem(m_bossWalkSE);
	DeleteSoundMem(m_diedSE);
}
