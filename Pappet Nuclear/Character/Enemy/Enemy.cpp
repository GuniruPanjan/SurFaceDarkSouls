#include "Enemy.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
Enemy::Enemy()
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Enemy::~Enemy()
{
}

/// <summary>
/// ����������
/// </summary>
/// <param name="max">�ő吔</param>
void Enemy::Init(int max)
{
	enemy->Init(max);	
}

/// <summary>
/// �{�X�̏���������
/// </summary>
void Enemy::BossInit()
{
	boss->Init();
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="player">�v���C���[�Ăяo��</param>
/// <param name="map">�}�b�v�Ăяo��</param>
/// <param name="max">�ő吔</param>
/// <param name="volume">����</param>
void Enemy::Update(Player& player, Map& map, int max, int volume)
{
	enemy->Update(player, max, volume);
}

/// <summary>
/// �{�X�̍X�V����
/// </summary>
/// <param name="player">�v���C���[�Ăяo��</param>
/// <param name="map">�}�b�v�Ăяo��</param>
/// <param name="volume">����</param>
void Enemy::BossUpdate(Player& player, Map& map, int volume)
{
	boss->Update(player, map, volume);
}

/// <summary>
/// �}�b�v���菈��
/// </summary>
/// <param name="map">�}�b�v�Ăяo��</param>
/// <param name="max">�ő吔</param>
void Enemy::MapHitWenemy(Map& map, int max)
{
	enemy->HitMap(map, max);
}

/// <summary>
/// �}�b�v�Ăяo��
/// </summary>
/// <param name="map">�}�b�v�Ăяo��</param>
void Enemy::MapHitBoss(Map& map)
{
	boss->MapHit(map);
}

/// <summary>
/// �`�揈��
/// </summary>
/// <param name="max">�ő吔</param>
void Enemy::Draw(int max)
{
	enemy->Draw(max);
}

/// <summary>
/// �{�X�̕`�揈��
/// </summary>
void Enemy::BossDraw()
{
	boss->Draw();
}

/// <summary>
/// �I������
/// </summary>
/// <param name="max">�ő吔</param>
void Enemy::End(int max)
{
	for (int i = 0; i < max; i++)
	{
		enemy->End(i);
	}
	

	boss->End();
}

//�G�l�~�[�̍U������
SphereCol Enemy::GetAttackCol(int max)
{
	return enemy->GetAttackCol(max);
	
}
