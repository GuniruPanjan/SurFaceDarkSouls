#include "LevelUp.h"
#include "Player.h"
#include "Character/Enemy/Enemy.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
LevelUp::LevelUp() :
	m_lHp(1),
	m_lStamina(1),
	m_lMuscle(1),
	m_lSkill(1),
	m_lAll(m_lHp + m_lStamina + m_lMuscle + m_lSkill),
	m_lCore(0),
	m_lUseCore(100)
{

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
LevelUp::~LevelUp()
{
}

/// <summary>
/// ����������
/// </summary>
/// <param name="player">�v���C���[���Ăяo��</param>
/// <param name="enemy">�G�l�~�[���Ăяo��</param>
void LevelUp::Init(Player& player, Enemy& enemy)
{
	//�v���C���[�̃��x���ɑ������
	player.m_levelStatus.sl_hp = m_lHp;
	player.m_levelStatus.sl_stamina = m_lStamina;
	player.m_levelStatus.sl_muscle = m_lMuscle;
	player.m_levelStatus.sl_skill = m_lSkill;
	player.m_levelStatus.sl_all = m_lAll;

	//�R�A������������
	m_lCore = enemy.GetCore();
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="player">�v���C���[���Ăяo��</param>
/// <param name="enemy">�G�l�~�[���Ăяo��</param>
void LevelUp::Update(Player& player, Enemy& enemy)
{
	//���x�����グ��
	if (m_lCore >= m_lUseCore * m_lAll)
	{


		//�グ���������炷
		m_lCore = m_lCore - (m_lUseCore * m_lAll);
	}

	//�S�Ẵ��x���ƍ��킹��
	m_lAll = m_lHp + m_lStamina + m_lMuscle + m_lSkill;
}

/// <summary>
/// �v���C���[�����񂾎��̏���
/// </summary>
/// <param name="player">�v���C���[���Ăяo��</param>
void LevelUp::PlayerDeath(Player& player)
{
}

/// <summary>
/// �`�揈��
/// </summary>
void LevelUp::Draw()
{
}

/// <summary>
/// �I������
/// </summary>
void LevelUp::End()
{
}
