#include "Character/Player/Player.h"
#include "WeakEnemy.h"

WeakEnemy::WeakEnemy()
{
	for (int i = 0; i < ENEMY_NOW; i++)
	{
		m_weakEnemyHp[i] = 0;
		m_weakEnemyPos[i] = VGet(0.0f, 0.0f, 0.0f);
		m_weakPlayTime[i] = 0.0f;
		m_weakEnemyMove[i] = VGet(0.0f, 0.0f, 0.0f);
		m_weakEnemyMoveAttack[i] = false;
		m_weakEnemyAngle[i] = 0.0f;
	}
}

WeakEnemy::~WeakEnemy()
{
}

void WeakEnemy::Init(int max)
{
	//�G��HP������
	m_weakEnemyHp[max] = 200.0f;

	//�G�̍U���͏�����
	m_attack = 10.0f;

	//�G�̃X�s�[�h������
	m_speed = 0.01f;

	m_weakPlayTime[max] = 0.0f;

	m_posX = 100.0f;
	m_posY = 0.0f;
	m_posZ = 0.0f;

	m_weakEnemyPos[0] = VGet(500.0f, m_posY, m_posZ);
	m_weakEnemyPos[1] = VGet(300.0f, m_posY, -500.0f);
	m_weakEnemyPos[2] = VGet(700.0f, m_posY, -400.0f);
	m_weakEnemyPos[3] = VGet(650.0f, m_posY, -200.0f);
	m_weakEnemyPos[4] = VGet(300.0f, m_posY, 100.0f);


	m_weakEnemyMoveAttack[max] = false;

	//��񂾂����s
	if (m_oneInit == false)
	{
		//���f������
		m_weakEnemyHandle[max] = MV1DuplicateModel(m_handle);
	}
	

	//�T�C�Y�ύX
	MV1SetScale(m_weakEnemyHandle[max], VGet(m_modelSize, m_modelSize, m_modelSize));

	//�����蔻��
	m_weakColPos[max] = Pos3(m_weakEnemyPos[max].x - 2.0f, m_weakEnemyPos[max].y + 35.0f, m_weakEnemyPos[max].z);
	m_colDeathPos = Pos3(0.0f, -1000.0f, 0.0f);
	m_colSearchPos[max] = Pos3(m_weakEnemyPos[max].x, m_weakEnemyPos[max].y + 35.0f, m_weakEnemyPos[max].z);
	m_colDistancePos[max] = Pos3(m_weakEnemyPos[max].x, m_weakEnemyPos[max].y + 35.0f, m_weakEnemyPos[max].z);
	m_colAttackPos[max] = Pos3(m_weakEnemyPos[max].x - 50.0f, m_weakEnemyPos[max].y + 35.0f, m_weakEnemyPos[max].z);
	m_initializationPos = Pos3(0.0f, -1000.0f, 0.0f);
	m_vec = Vec3(0.0f, m_weakEnemyPos[max].y + 2.0f, 0.0f);
	m_deathVec = Vec3(0.0f, 0.0f, 0.0f);
	m_len = 40.0f;
	m_capsuleRadius = 14.0f;
	m_searchRadius = 120.0f;
	m_distanceRadius = 80.0f;
	m_attackRadius = 18.0f;
	m_weakCapsuleCol[max].Init(m_weakColPos[max], m_vec, m_len, m_capsuleRadius);
	m_colSearch[max].Init(m_colSearchPos[max], m_searchRadius);
	m_colDistance[max].Init(m_colDistancePos[max], m_distanceRadius);
	m_colAttack[max].Init(m_colAttackPos[max], m_attackRadius);


	//�A�j���[�V�����A�^�b�`
	m_weakEnemyAnimation[0][max] = MV1AttachAnim(m_weakEnemyHandle[max], 0, m_animStand, TRUE);

	//�G�l�~�[�����񂾃A�j���[�V�����������ꍇ
	if (m_weakEnemyAnimation[2][max] != -1)
	{
		//�A�j���[�V�����f�^�b�`
		MV1DetachAnim(m_weakEnemyHandle[max], m_weakEnemyAnimation[2][max]);

		m_weakPlayTime[max] = 0.0f;

		m_weakEnemyAnimation[2][max] = -1;
	}
	

}

void WeakEnemy::Update(Player& player, int max)
{
	m_oneInit = true;
	
	m_weakColPos[max] = Pos3(m_weakEnemyPos[max].x - 2.0f, m_weakEnemyPos[max].y + 35.0f, m_weakEnemyPos[max].z);
	//m_colSearchPos[max] = Pos3(m_weakEnemyPos[max].x, m_weakEnemyPos[max].y + 35.0f, m_weakEnemyPos[max].z);
	m_colDistancePos[max] = Pos3(m_weakEnemyPos[max].x, m_weakEnemyPos[max].y + 35.0f, m_weakEnemyPos[max].z);

	m_weakPlayTime[max] += 0.5f;

	//���G�Ŕ������ꂽ����&�G���U�����ĂȂ���
	if (m_enemySearchFlag[max] == true && m_weakEnemyMoveAttack[max] == false)
	{
		float X = m_weakEnemyPos[max].x - player.GetPosX();
		float Z = m_weakEnemyPos[max].z - player.GetPosZ();

		//�v���C���[�̕�������
		m_weakEnemyAngle[max] = atan2f(X, Z);

		//�@���x�N�g��
		m_moveTurning[max] = atan2f(-X, Z);
		m_moveReverseTurning[max] = atan2f(X, -Z);
	}

	//�U�����ĂȂ��Ȃ�
	if (m_weakEnemyMoveAttack[max] == false)
	{
		//�G���ړ�����
		m_weakEnemyPos[max] = VAdd(m_weakEnemyPos[max], m_weakEnemyMove[max]);
	}

	//�U������𐳖ʂɎ����Ă���
	m_colAttackPos[max].x = m_weakEnemyPos[max].x + sinf(m_weakEnemyAngle[max]) * -25.0f;
	m_colAttackPos[max].z = m_weakEnemyPos[max].z - cosf(m_weakEnemyAngle[max]) * 25.0f;

	//�G�����S������
	if (m_weakEnemyHp[max] <= 0.0f)
	{
		DrawFormatString(0, 240, 0xffffff, "�G������");

		m_weakCapsuleCol[max].Update(m_colDeathPos, m_deathVec);

		m_colSearch[max].Update(m_colDeathPos);
	}
	else
	{
		m_weakCapsuleCol[max].Update(m_weakColPos[max], m_vec);

		//�Ƃ肠�����u���Ƃ�
		m_colSearch[max].Update(m_colSearchPos[max]);
		m_colDistance[max].Update(m_colDistancePos[max]);
	}

	//���G�̓����蔻��𐳖ʂɎ����Ă���
	m_colSearchPos[max].x = m_weakEnemyPos[max].x + sinf(m_weakEnemyAngle[max]) * -80.0f;
	m_colSearchPos[max].z = m_weakEnemyPos[max].z - cosf(m_weakEnemyAngle[max]) * 80.0f;

	Action(player, max);

	Animation(m_weakPlayTime[max], max);
}

/// <summary>
/// �v���C���[�ւ̍U����ԍ����̎����Ȃǂ��܂Ƃ߂�֐�
/// </summary>
/// <param name="player"></param>
void WeakEnemy::Action(Player& player, int max)
{
	//�G�ɔ������ꂽ�ꍇ
	if (m_enemySearchFlag[max] == true)
	{
		//�v���C���[�ƓG�̑��΋������Z�o
		VECTOR tracking = VSub(player.GetPos(), m_weakEnemyPos[max]);

		//�p�x���o���v���C���[�̎�������^��������
		MATRIX mtx = MGetRotY(D2R(m_moveTurning[max]) + DX_PI_F / 2);
		MATRIX mtxR = MGetRotY(D2R(m_moveReverseTurning[max]) - DX_PI_F / 2);

		if (m_enemyWait[max] == false && m_weakEnemyMoveAttack[max] == false)
		{
			m_speed = 0.01f;

			m_weakEnemyMove[max] = VScale(tracking, m_speed);
		}
		//�G���߂��ɂ������̏���
		else
		{
			m_weakEnemyMove[max] = VNorm(tracking);

			m_speed = 0.3f;

			m_weakEnemyMove[max] = VScale(m_weakEnemyMove[max], m_speed);

			//�����_����0���o���獶����
			if (m_randomAction[max] == 0)
			{
				m_weakEnemyMove[max] = VTransform(m_weakEnemyMove[max], mtx);

				m_weakEnemyMoveAttack[max] = false;
			}
			//�����_����1���o����E����
			if (m_randomAction[max] == 1)
			{
				m_weakEnemyMove[max] = VTransform(m_weakEnemyMove[max], mtxR);

				m_weakEnemyMoveAttack[max] = false;
			}
			//�����_����2���o����U��
			if (m_randomAction[max] == 2)
			{
				//�A�j���[�V�����t���[�����ɍU�����������
				if (m_weakPlayTime[max] >= 22 && m_weakPlayTime[max] <= 35)
				{
					m_colAttack[max].Update(m_colAttackPos[max]);
				}
				else
				{
					m_colAttack[max].Update(m_initializationPos);
				}

				m_weakEnemyMoveAttack[max] = true;
			}
		}

	}
	//�G�ɔ�������ĂȂ��Ƃ�
	else
	{
		//�G�������Ȃ��悤�ɂ���
		m_weakEnemyMove[max] = VGet(0.0f, 0.0f, 0.0f);
	}

	m_randomNextActionTime[max] += 0.1f;

	if (m_randomNextActionTime[max] >= 50.0f)
	{
		m_randomAction[max] = GetRand(2);

		m_randomNextActionTime[max] = 0.0f;
	}

}

void WeakEnemy::Animation(float& time, int max)
{
	//�G���v���C���[�������ĂȂ��Ƃ�
	if (m_enemySearchFlag[max] == false)
	{
		if (m_weakEnemyAnimation[3][max] != -1 || m_weakEnemyAnimation[4][max] != -1 || m_weakEnemyAnimation[5][max] != -1 ||
			m_weakEnemyAnimation[6][max] != -1)
		{
			//�A�j���[�V�����f�^�b�`
			MV1DetachAnim(m_weakEnemyHandle[max], m_weakEnemyAnimation[3][max]);
			MV1DetachAnim(m_weakEnemyHandle[max], m_weakEnemyAnimation[4][max]);
			MV1DetachAnim(m_weakEnemyHandle[max], m_weakEnemyAnimation[5][max]);
			MV1DetachAnim(m_weakEnemyHandle[max], m_weakEnemyAnimation[6][max]);


			//�A�j���[�V�����A�^�b�`
			m_weakEnemyAnimation[0][max] = MV1AttachAnim(m_weakEnemyHandle[max], 0, m_animStand, TRUE);

			time = 0.0f;

			m_weakEnemyAnimation[3][max] = -1;
			m_weakEnemyAnimation[4][max] = -1;
			m_weakEnemyAnimation[5][max] = -1;
			m_weakEnemyAnimation[6][max] = -1;

		}
	}
	//�G���v���C���[����������(�Ր�Ԑ�)
	if (m_enemySearchFlag[max] == true && m_enemyWait[max] == false && m_weakEnemyMoveAttack[max] == false)
	{
		if (m_weakEnemyAnimation[0][max] != -1 || m_weakEnemyAnimation[4][max] != -1 || m_weakEnemyAnimation[5][max] != -1 ||
			m_weakEnemyAnimation[6][max] != -1)
		{
			//�A�j���[�V�����f�^�b�`
			MV1DetachAnim(m_weakEnemyHandle[max], m_weakEnemyAnimation[0][max]);
			MV1DetachAnim(m_weakEnemyHandle[max], m_weakEnemyAnimation[4][max]);
			MV1DetachAnim(m_weakEnemyHandle[max], m_weakEnemyAnimation[5][max]);
			MV1DetachAnim(m_weakEnemyHandle[max], m_weakEnemyAnimation[6][max]);


			//�A�j���[�V�����A�^�b�`
			m_weakEnemyAnimation[3][max] = MV1AttachAnim(m_weakEnemyHandle[max], 0, m_animWalk, TRUE);

			time = 0.0f;

			m_weakEnemyAnimation[0][max] = -1;
			m_weakEnemyAnimation[4][max] = -1;
			m_weakEnemyAnimation[5][max] = -1;
			m_weakEnemyAnimation[6][max] = -1;

		}
	}
	//�G�̎˒������ɓ������Ƃ�
	//������
	if (m_randomAction[max] == 0 && m_enemyWait[max] == true)
	{
		if (m_weakEnemyAnimation[0][max] != -1 || m_weakEnemyAnimation[3][max] != -1 || m_weakEnemyAnimation[5][max] != -1 ||
			m_weakEnemyAnimation[6][max] != -1)
		{
			//�A�j���[�V�����f�^�b�`
			MV1DetachAnim(m_weakEnemyHandle[max], m_weakEnemyAnimation[0][max]);
			MV1DetachAnim(m_weakEnemyHandle[max], m_weakEnemyAnimation[3][max]);
			MV1DetachAnim(m_weakEnemyHandle[max], m_weakEnemyAnimation[5][max]);
			MV1DetachAnim(m_weakEnemyHandle[max], m_weakEnemyAnimation[6][max]);

			//�A�j���[�V�����A�^�b�`
			m_weakEnemyAnimation[4][max] = MV1AttachAnim(m_weakEnemyHandle[max], 0, m_animLeftWalking, TRUE);

			time = 0.0f;

			m_weakEnemyAnimation[0][max] = -1;
			m_weakEnemyAnimation[3][max] = -1;
			m_weakEnemyAnimation[5][max] = -1;
			m_weakEnemyAnimation[6][max] = -1;

		}
	}
	//�E����
	if (m_randomAction[max] == 1 && m_enemyWait[max] == true)
	{
		if (m_weakEnemyAnimation[0][max] != -1 || m_weakEnemyAnimation[3][max] != -1 || m_weakEnemyAnimation[4][max] != -1 ||
			m_weakEnemyAnimation[6][max] != -1)
		{
			//�A�j���[�V�����f�^�b�`
			MV1DetachAnim(m_weakEnemyHandle[max], m_weakEnemyAnimation[0][max]);
			MV1DetachAnim(m_weakEnemyHandle[max], m_weakEnemyAnimation[3][max]);
			MV1DetachAnim(m_weakEnemyHandle[max], m_weakEnemyAnimation[4][max]);
			MV1DetachAnim(m_weakEnemyHandle[max], m_weakEnemyAnimation[6][max]);

			//�A�j���[�V�����A�^�b�`
			m_weakEnemyAnimation[5][max] = MV1AttachAnim(m_weakEnemyHandle[max], 0, m_animRightWalking, TRUE);

			time = 0.0f;

			m_weakEnemyAnimation[0][max] = -1;
			m_weakEnemyAnimation[3][max] = -1;
			m_weakEnemyAnimation[4][max] = -1;
			m_weakEnemyAnimation[6][max] = -1;

		}
	}
	//�U�����[�V����
	if (m_randomAction[max] == 2 && m_enemyWait[max] == true)
	{
		if (m_weakEnemyAnimation[0][max] != -1 || m_weakEnemyAnimation[3][max] != -1 || m_weakEnemyAnimation[4][max] != -1 ||
			m_weakEnemyAnimation[5][max] != -1)
		{
			//�A�j���[�V�����f�^�b�`
			MV1DetachAnim(m_weakEnemyHandle[max], m_weakEnemyAnimation[0][max]);
			MV1DetachAnim(m_weakEnemyHandle[max], m_weakEnemyAnimation[3][max]);
			MV1DetachAnim(m_weakEnemyHandle[max], m_weakEnemyAnimation[4][max]);
			MV1DetachAnim(m_weakEnemyHandle[max], m_weakEnemyAnimation[5][max]);

			//�A�j���[�V�����A�^�b�`
			m_weakEnemyAnimation[6][max] = MV1AttachAnim(m_weakEnemyHandle[max], 0, m_animAttack1, TRUE);

			time = 0.0f;

			m_weakEnemyAnimation[0][max] = -1;
			m_weakEnemyAnimation[3][max] = -1;
			m_weakEnemyAnimation[4][max] = -1;
			m_weakEnemyAnimation[5][max] = -1;
		}
	}

	//�G�����񂾂玀�ʃA�j���[�V����������
	if (m_weakEnemyHp[max] <= 0.0f)
	{
		if (m_weakEnemyAnimation[0][max] != -1 || m_weakEnemyAnimation[1][max] != -1 || m_weakEnemyAnimation[3][max] != -1 ||
			m_weakEnemyAnimation[4][max] != -1 || m_weakEnemyAnimation[5][max] != -1 || m_weakEnemyAnimation[6][max] != -1)
		{
			//�A�j���[�V�����f�^�b�`
			MV1DetachAnim(m_weakEnemyHandle[max], m_weakEnemyAnimation[0][max]);
			MV1DetachAnim(m_weakEnemyHandle[max], m_weakEnemyAnimation[1][max]);
			MV1DetachAnim(m_weakEnemyHandle[max], m_weakEnemyAnimation[3][max]);
			MV1DetachAnim(m_weakEnemyHandle[max], m_weakEnemyAnimation[4][max]);
			MV1DetachAnim(m_weakEnemyHandle[max], m_weakEnemyAnimation[5][max]);
			MV1DetachAnim(m_weakEnemyHandle[max], m_weakEnemyAnimation[6][max]);

			//�A�j���[�V�����A�^�b�`
			m_weakEnemyAnimation[2][max] = MV1AttachAnim(m_weakEnemyHandle[max], 0, m_animDeath, TRUE);

			time = 0.0f;

			m_weakEnemyAnimation[0][max] = -1;
			m_weakEnemyAnimation[1][max] = -1;
			m_weakEnemyAnimation[3][max] = -1;
			m_weakEnemyAnimation[4][max] = -1;
			m_weakEnemyAnimation[5][max] = -1;
			m_weakEnemyAnimation[6][max] = -1;

		}
	}

	//�Đ����Ԃ��A�j���[�V�����̑��Đ����ԂɒB������Đ����Ԃ�0�ɖ߂�
	if (time >= m_weakEnemyTotalAnimationTime[0][max] && m_weakEnemyAnimation[0][max] != -1)
	{
		time = 0.0f;
	}
	if (time >= m_weakEnemyTotalAnimationTime[2][max] && m_weakEnemyAnimation[2][max] != -1)
	{
		time = 120.0f;
	}
	if (time >= m_weakEnemyTotalAnimationTime[3][max] && m_weakEnemyAnimation[3][max] != -1)
	{
		time = 0.0f;
	}
	if (time >= m_weakEnemyTotalAnimationTime[4][max] && m_weakEnemyAnimation[4][max] != -1)
	{
		time = 0.0f;
	}
	if (time >= m_weakEnemyTotalAnimationTime[5][max] && m_weakEnemyAnimation[5][max] != -1)
	{
		time = 0.0f;
	}
	if (time >= m_weakEnemyTotalAnimationTime[6][max] && m_weakEnemyAnimation[6][max] != -1)
	{
		m_weakEnemyMoveAttack[max] = false;

		m_randomNextActionTime[max] = 50.0f;

		time = 0.0f;
	}

	//�Đ����Ԃ��Z�b�g����
	if (m_weakEnemyAnimation[0][max] != -1)
	{
		MV1SetAttachAnimTime(m_weakEnemyHandle[max], m_weakEnemyAnimation[0][max], time);
	}
	if (m_weakEnemyAnimation[2][max] != -1)
	{
		MV1SetAttachAnimTime(m_weakEnemyHandle[max], m_weakEnemyAnimation[2][max], time);
	}
	if (m_weakEnemyAnimation[3][max] != -1)
	{
		MV1SetAttachAnimTime(m_weakEnemyHandle[max], m_weakEnemyAnimation[3][max], time);
	}
	if (m_weakEnemyAnimation[4][max] != -1)
	{
		MV1SetAttachAnimTime(m_weakEnemyHandle[max], m_weakEnemyAnimation[4][max], time);
	}
	if (m_weakEnemyAnimation[5][max] != -1)
	{
		MV1SetAttachAnimTime(m_weakEnemyHandle[max], m_weakEnemyAnimation[5][max], time);
	}
	if (m_weakEnemyAnimation[6][max] != -1)
	{
		MV1SetAttachAnimTime(m_weakEnemyHandle[max], m_weakEnemyAnimation[6][max], time);
	}
}

void WeakEnemy::Draw(int max)
{
	//�����x�N�g��
	Vec3 vec = m_vec.GetNormalized() * m_len * 0.5f;

	Pos3 pos1 = m_weakColPos[max] + vec;
	Pos3 pos2 = m_weakColPos[max] - vec;

	if (m_weakEnemyHp[max] > 0.0f)
	{
		DrawCapsule3D(pos1.GetVector(), pos2.GetVector(), m_capsuleRadius, 16, m_color, 0, false);

		//���G�͈͉~��3D�`��
		DrawSphere3D(m_colSearchPos[max].GetVector(), m_searchRadius, 16, m_seachColor, m_seachColor, false);

		//��苗���͈͕̔`��
		DrawSphere3D(m_colDistancePos[max].GetVector(), m_distanceRadius, 16, m_distanceColor, m_distanceColor, false);

		//�U������`��
		DrawSphere3D(m_colAttackPos[max].GetVector(), m_attackRadius, 16, 0xffffff, 0xffffff, false);
	}

	//3D���f���|�W�V�����ݒ�
	MV1SetPosition(m_weakEnemyHandle[max], m_weakEnemyPos[max]);

	//3D���f���`��
	MV1DrawModel(m_weakEnemyHandle[max]);

	//3D���f���̉�]�n���Z�b�g����
	MV1SetRotationXYZ(m_weakEnemyHandle[max], VGet(0.0f, m_weakEnemyAngle[max], 0.0f));

	//DrawFormatString(0, 320, 0xffffff, "m_colposX : %f m_colposY : %f m_colposZ : %f", m_colPos.x, m_colPos.y, m_colPos.z);
	//DrawFormatString(0, 220, 0xffffff, "m_EnemyHp : %f", m_hp);
	//DrawFormatString(0, 180, 0xffffff, "m_randomTime : %f", m_randomNextActionTime);
	//DrawFormatString(0, 160, 0xffffff, "m_randomAction : %f", m_randomAction);
	//DrawFormatString(0, 140, 0xffffff, "m_playTime : %f", m_playTime);

	//if (m_enemySearchFlag == true)
	//{
	//	DrawFormatString(0, 250, 0xffffff, "�������ꂽ");
	//}
}

void WeakEnemy::End(int max)
{
}

bool WeakEnemy::isSphereHit(const SphereCol& col, float damage, int max)
{
	bool isHit = m_weakCapsuleCol[max].IsHitSphere(col);

	//�_���[�W���󂯂�����
	if (isHit)
	{
		m_color = 0xffff00;

		//�_���[�W����񂾂��^����
		if (m_damageReceived == false)
		{
			m_weakEnemyHp[max] = m_weakEnemyHp[max] - damage;

			m_damageReceived = true;
		}

	}
	else
	{
		m_damageReceived = false;

		m_color = 0xffffff;
	}

	return isHit;
}

bool WeakEnemy::isSeachHit(const CapsuleCol& col, int max)
{
	bool isHit = m_colSearch[max].IsHitCapsule(col);

	//�v���C���[������������
	if (isHit)
	{
		m_seachColor = 0xffff00;

		m_enemySearchFlag[max] = true;
	}
	else
	{
		m_seachColor = 0xffffff;

		m_enemySearchFlag[max] = false;
	}

	return isHit;
}

bool WeakEnemy::isDistanceHit(const CapsuleCol& col, int max)
{
	bool isHit = m_colDistance[max].IsHitCapsule(col);

	//���͈͓��Ƀv���C���[����������
	if (isHit)
	{
		m_distanceColor = 0xffff00;

		m_enemyWait[max] = true;
	}
	else
	{
		m_distanceColor = 0xffffff;

		m_enemyWait[max] = false;
	}

	return isHit;
}
