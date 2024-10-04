#include "EnemyBase.h"

namespace
{
	//�V���O���g��
	auto& handle = HandleManager::GetInstance();
}

EnemyBase::EnemyBase():
	m_bossModelHandle(-1),
	m_core(0),
	m_baseCore(0),
	m_bossSize(0.0f),
	m_searchRadius(0.0f),
	m_distanceRadius(0.0f),
	m_attackRadius(0.0f),
	m_enemyDeath(false)
{
	for (int i = 0; i < ENEMY_NOW; i++)
	{
		m_enemySearchFlag[i] = false;
		m_enemyWait[i] = false;
		m_randomAction[i] = 0;
		m_moveTurning[i] = 0.0f;
		m_moveReverseTurning[i] = 0.0f;
		m_randomNextActionTime[i] = 0.0f;
		m_weakAnimBlend[i] = 1.0f;

		for (int j = 0; j < ANIMATION; j++)
		{
			m_weakAnimOne[j][i] = false;
		}
	}

	//�G�̃��f���ǂݍ���
	m_handle = handle.GetModelHandle("Data/Enemy/EnemyModel.mv1");
	m_bossModelHandle = handle.GetModelHandle("Data/Enemy/BossEnemy.mv1");

	//�G�̃A�j���[�V�����ǂݍ���
	m_animStand = MV1LoadModel("Data/EnemyAnimation/WeakEnemyAnimation/WeakEnemyStand1.mv1");
	m_animWalk = MV1LoadModel("Data/EnemyAnimation/WeakEnemyAnimation/WeakEnemyAnimWalking.mv1");
	m_animHit = MV1LoadModel("Data/EnemyAnimation/WeakEnemyAnimation/WeakEnemyAnimHit.mv1");
	m_animDeath = MV1LoadModel("Data/EnemyAnimation/WeakEnemyAnimation/WeakEnemyAnimDeath.mv1");
	m_animLeftWalking = MV1LoadModel("Data/EnemyAnimation/WeakEnemyAnimation/WeakEnemyWalkingLeft.mv1");
	m_animRightWalking = MV1LoadModel("Data/EnemyAnimation/WeakEnemyAnimation/WeakEnemyWalkingRight.mv1");
	m_animAttack1 = MV1LoadModel("Data/EnemyAnimation/WeakEnemyAnimation/WeakEnemyAnimAttack1.mv1");
	m_bossAnimStand = MV1LoadModel("Data/EnemyAnimation/BossEnemyAnimation/BossEnemyAnimStand.mv1");
	m_bossAnimDeath = MV1LoadModel("Data/EnemyAnimation/BossEnemyAnimation/BossEnemyAnimDeath.mv1");
	m_bossAnimWalk = MV1LoadModel("Data/EnemyAnimation/BossEnemyAnimation/BossEnemyAnimWalk.mv1");
	m_bossAnimTurn = MV1LoadModel("Data/EnemyAnimation/BossEnemyAnimation/BossEnemyAnimRightTurn.mv1");
	m_bossAnimAttack1 = MV1LoadModel("Data/EnemyAnimation/BossEnemyAnimation/BossEnemyAnimAttack1.mv1");
	m_bossAnimAttack2 = MV1LoadModel("Data/EnemyAnimation/BossEnemyAnimation/BossEnemyAnimAttack2.mv1");
	m_bossAnimAttack3 = MV1LoadModel("Data/EnemyAnimation/BossEnemyAnimation/BossEnemyAnimAttack3.mv1");

	//�A�j���[�V�����A�^�b�`
	m_bossAnimation[0] = MV1AttachAnim(m_bossModelHandle, 0, m_bossAnimStand, TRUE);
	m_bossAnimation[1] = MV1AttachAnim(m_bossModelHandle, 0, m_bossModelHandle, TRUE);
	m_bossAnimation[2] = MV1AttachAnim(m_bossModelHandle, 0, m_bossAnimDeath, TRUE);
	m_bossAnimation[3] = MV1AttachAnim(m_bossModelHandle, 0, m_bossAnimWalk, TRUE);
	m_bossAnimation[4] = MV1AttachAnim(m_bossModelHandle, 0, m_bossAnimAttack1, TRUE);
	m_bossAnimation[5] = MV1AttachAnim(m_bossModelHandle, 0, m_bossAnimAttack2, TRUE);
	m_bossAnimation[6] = MV1AttachAnim(m_bossModelHandle, 0, m_bossAnimAttack3, TRUE);
	m_bossAnimation[7] = MV1AttachAnim(m_bossModelHandle, 0, m_bossAnimTurn, TRUE);

	//�A�^�b�`�����A�j���[�V�����̑��Đ����Ԃ��擾����
	for (int i = 0; i < 8; i++)
	{
		m_bossTotalAnimTime[i] = MV1GetAttachAnimTotalTime(m_bossModelHandle, m_bossAnimation[i]);
	}
	//m_bossTotalAnimTime[0] = MV1GetAttachAnimTotalTime(m_bossModelHandle, m_bossAnimation[0]);
	//m_bossTotalAnimTime[1] = MV1GetAttachAnimTotalTime(m_bossModelHandle, m_bossAnimation[1]);
	//m_bossTotalAnimTime[2] = MV1GetAttachAnimTotalTime(m_bossModelHandle, m_bossAnimation[2]);
	//m_bossTotalAnimTime[3] = MV1GetAttachAnimTotalTime(m_bossModelHandle, m_bossAnimation[3]);
	//m_bossTotalAnimTime[4] = MV1GetAttachAnimTotalTime(m_bossModelHandle, m_bossAnimation[4]);
	//m_bossTotalAnimTime[5] = MV1GetAttachAnimTotalTime(m_bossModelHandle, m_bossAnimation[5]);
	//m_bossTotalAnimTime[6] = MV1GetAttachAnimTotalTime(m_bossModelHandle, m_bossAnimation[6]);



	//��U�ҋ@�ȊO�̃A�j���[�V�������f�^�b�`����
	MV1DetachAnim(m_bossModelHandle, m_bossAnimation[1]);
	MV1DetachAnim(m_bossModelHandle, m_bossAnimation[2]);
	MV1DetachAnim(m_bossModelHandle, m_bossAnimation[3]);
	MV1DetachAnim(m_bossModelHandle, m_bossAnimation[4]);
	MV1DetachAnim(m_bossModelHandle, m_bossAnimation[5]);
	MV1DetachAnim(m_bossModelHandle, m_bossAnimation[6]);
	m_bossAnimation[1] = -1;
	m_bossAnimation[2] = -1;
	m_bossAnimation[3] = -1;
	m_bossAnimation[4] = -1;
	m_bossAnimation[5] = -1;
	m_bossAnimation[6] = -1;

	//�A�j���[�V�����u�����h��0�ɂ���
	MV1SetAttachAnimBlendRate(m_bossModelHandle, m_bossAnimation[7], 0.0f);


	//�G�̃T�C�Y�ύX
	m_modelSize = 0.4f;
	m_bossSize = 0.7f;
	MV1SetScale(m_bossModelHandle, VGet(m_bossSize, m_bossSize, m_bossSize));
}

EnemyBase::~EnemyBase()
{
	//���������
	MV1DeleteModel(m_handle);
	MV1DeleteModel(m_bossModelHandle);
	MV1DeleteModel(m_animStand);
	MV1DeleteModel(m_animHit);
	MV1DeleteModel(m_animDeath);
	MV1DeleteModel(m_animWalk);
	MV1DeleteModel(m_animLeftWalking);
	MV1DeleteModel(m_animRightWalking);
	MV1DeleteModel(m_animAttack1);
	MV1DeleteModel(m_bossAnimStand);
	MV1DeleteModel(m_bossAnimDeath);
	MV1DeleteModel(m_bossAnimWalk);
	MV1DeleteModel(m_bossAnimAttack1);
	MV1DeleteModel(m_bossAnimAttack2);
	MV1DeleteModel(m_bossAnimAttack3);

	//�������폜
	handle.Clear();

}

void EnemyBase::End()
{
	//���������
	MV1DeleteModel(m_handle);
	MV1DeleteModel(m_bossModelHandle);
	MV1DeleteModel(m_animStand);
	MV1DeleteModel(m_animHit);
	MV1DeleteModel(m_animDeath);
	MV1DeleteModel(m_animWalk);
	MV1DeleteModel(m_animLeftWalking);
	MV1DeleteModel(m_animRightWalking);
	MV1DeleteModel(m_animAttack1);
	MV1DeleteModel(m_bossAnimStand);
	MV1DeleteModel(m_bossAnimDeath);
	MV1DeleteModel(m_bossAnimWalk);
	MV1DeleteModel(m_bossAnimAttack1);
	MV1DeleteModel(m_bossAnimAttack2);
	MV1DeleteModel(m_bossAnimAttack3);

	//�������폜
	handle.Clear();
}
