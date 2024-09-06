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
	for (int i = 0; i < max; i++)
	{
		//�G��HP������
		m_weakEnemyHp[i] = 200.0f;

		//�G�̍U���͏�����
		m_attack = 10.0f;

		//�G�̃X�s�[�h������
		m_speed = 0.01f;

		m_weakPlayTime[i] = 0.0f;

		m_posX = 100.0f;
		m_posY = 0.0f;
		m_posZ = 0.0f;

		m_weakEnemyPos[i] = VGet(m_posX * i + 1, m_posY, m_posZ);

		m_weakEnemyMoveAttack[i] = false;

		//�����蔻��
		m_weakColPos[i] = Pos3(m_weakEnemyPos[i].x - 2.0f, m_weakEnemyPos[i].y + 35.0f, m_weakEnemyPos[i].z);
		m_colDeathPos = Pos3(0.0f, -1000.0f, 0.0f);
		m_colSearchPos[i] = Pos3(m_weakEnemyPos[i].x, m_weakEnemyPos[i].y + 35.0f, m_weakEnemyPos[i].z);
		m_colDistancePos[i] = Pos3(m_weakEnemyPos[i].x, m_weakEnemyPos[i].y + 35.0f, m_weakEnemyPos[i].z);
		m_colAttackPos[i] = Pos3(m_weakEnemyPos[i].x - 50.0f, m_weakEnemyPos[i].y + 35.0f, m_weakEnemyPos[i].z);
		m_initializationPos = Pos3(0.0f, -1000.0f, 0.0f);
		m_vec = Vec3(0.0f, m_weakEnemyPos[i].y + 2.0f, 0.0f);
		m_deathVec = Vec3(0.0f, 0.0f, 0.0f);
		m_len = 40.0f;
		m_capsuleRadius = 14.0f;
		m_searchRadius = 120.0f;
		m_distanceRadius = 80.0f;
		m_attackRadius = 18.0f;
		m_weakCapsuleCol[i].Init(m_weakColPos[i], m_vec, m_len, m_capsuleRadius);
		m_colSearch[i].Init(m_colSearchPos[i], m_searchRadius);
		m_colDistance[i].Init(m_colDistancePos[i], m_distanceRadius);
		m_colAttack[i].Init(m_colAttackPos[i], m_attackRadius);

		//�G�l�~�[�����񂾃A�j���[�V�����������ꍇ
		if (m_animation[2] != -1)
		{
			//�A�j���[�V�����f�^�b�`
			MV1DetachAnim(m_handle, m_animation[2]);

			//�A�j���[�V�����A�^�b�`
			m_animation[0] = MV1AttachAnim(m_handle, 0, m_animStand, TRUE);

			m_weakPlayTime[i] = 0.0f;

			m_animation[2] = -1;
		}
	}
	

}

void WeakEnemy::Update(Player& player, int max)
{
	
	for (int i = 0; i < max; i++)
	{
		m_weakColPos[i] = Pos3(m_weakEnemyPos[i].x - 2.0f, m_weakEnemyPos[i].y + 35.0f, m_weakEnemyPos[i].z);
		m_colSearchPos[i] = Pos3(m_weakEnemyPos[i].x, m_weakEnemyPos[i].y + 35.0f, m_weakEnemyPos[i].z);
		m_colDistancePos[i] = Pos3(m_weakEnemyPos[i].x, m_weakEnemyPos[i].y + 35.0f, m_weakEnemyPos[i].z);

		m_weakPlayTime[i] += 0.5f;

		//���G�Ŕ������ꂽ����&�G���U�����ĂȂ���
		if (m_enemySearchFlag[i] == true && m_weakEnemyMoveAttack[i] == false)
		{
			float X = m_weakEnemyPos[i].x - player.GetPosX();
			float Z = m_weakEnemyPos[i].z - player.GetPosZ();

			//�v���C���[�̕�������
			m_weakEnemyAngle[i] = atan2f(X, Z);

			//�@���x�N�g��
			m_moveTurning[i] = atan2f(-X, Z);
			m_moveReverseTurning[i] = atan2f(X, -Z);
		}

		//�U�����ĂȂ��Ȃ�
		if (m_weakEnemyMoveAttack[i] == false)
		{
			//�G���ړ�����
			m_weakEnemyPos[i] = VAdd(m_weakEnemyPos[i], m_weakEnemyMove[i]);
		}

		//�U������𐳖ʂɎ����Ă���
		m_colAttackPos[i].x = m_weakEnemyPos[i].x + sinf(m_weakEnemyAngle[i]) * -25.0f;
		m_colAttackPos[i].z = m_weakEnemyPos[i].z - cosf(m_weakEnemyAngle[i]) * 25.0f;

		//�G�����S������
		if (m_weakEnemyHp[i] <= 0.0f)
		{
			DrawFormatString(0, 240, 0xffffff, "�G������");

			m_weakCapsuleCol[i].Update(m_colDeathPos, m_deathVec);

			m_colSearch[i].Update(m_colDeathPos);
		}
		else
		{
			m_weakCapsuleCol[i].Update(m_weakColPos[i], m_vec);

			//�Ƃ肠�����u���Ƃ�
			m_colSearch[i].Update(m_colSearchPos[i]);
			m_colDistance[i].Update(m_colDistancePos[i]);
		}

		//���G�̓����蔻��𐳖ʂɎ����Ă���
		m_colSearchPos[i].x = m_weakEnemyPos[i].x + sinf(m_weakEnemyAngle[i]) * -80.0f;
		m_colSearchPos[i].z = m_weakEnemyPos[i].z - cosf(m_weakEnemyAngle[i]) * 80.0f;

		Action(player, max);

		Animation(m_weakPlayTime[i], max);
	}
	
}

/// <summary>
/// �v���C���[�ւ̍U����ԍ����̎����Ȃǂ��܂Ƃ߂�֐�
/// </summary>
/// <param name="player"></param>
void WeakEnemy::Action(Player& player, int max)
{
	for (int i = 0; i < max; i++)
	{
		//�G�ɔ������ꂽ�ꍇ
		if (m_enemySearchFlag[i] == true)
		{
			//�v���C���[�ƓG�̑��΋������Z�o
			VECTOR tracking = VSub(player.GetPos(), m_weakEnemyPos[i]);

			//�p�x���o���v���C���[�̎�������^��������
			MATRIX mtx = MGetRotY(D2R(m_moveTurning[i]) + DX_PI_F / 2);
			MATRIX mtxR = MGetRotY(D2R(m_moveReverseTurning[i]) - DX_PI_F / 2);

			if (m_enemyWait[i] == false && m_weakEnemyMoveAttack[i] == false)
			{
				m_speed = 0.01f;

				m_weakEnemyMove[i] = VScale(tracking, m_speed);
			}
			//�G���߂��ɂ������̏���
			else
			{
				m_weakEnemyMove[i] = VNorm(tracking);

				m_speed = 0.3f;

				m_weakEnemyMove[i] = VScale(m_weakEnemyMove[i], m_speed);

				//�����_����0���o���獶����
				if (m_randomAction[i] == 0)
				{
					m_weakEnemyMove[i] = VTransform(m_weakEnemyMove[i], mtx);

					m_weakEnemyMoveAttack[i] = false;
				}
				//�����_����1���o����E����
				if (m_randomAction[i] == 1)
				{
					m_weakEnemyMove[i] = VTransform(m_weakEnemyMove[i], mtxR);

					m_weakEnemyMoveAttack[i] = false;
				}
				//�����_����2���o����U��
				if (m_randomAction[i] == 2)
				{
					//�A�j���[�V�����t���[�����ɍU�����������
					if (m_weakPlayTime[i] >= 22 && m_weakPlayTime[i] <= 35)
					{
						m_colAttack[i].Update(m_colAttackPos[i]);
					}
					else
					{
						m_colAttack[i].Update(m_initializationPos);
					}

					m_weakEnemyMoveAttack[i] = true;
				}
			}

		}
		//�G�ɔ�������ĂȂ��Ƃ�
		else
		{
			//�G�������Ȃ��悤�ɂ���
			m_weakEnemyMove[i] = VGet(0.0f, 0.0f, 0.0f);
		}

		m_randomNextActionTime[i] += 0.1f;

		if (m_randomNextActionTime[i] >= 50.0f)
		{
			m_randomAction[i] = GetRand(2);

			m_randomNextActionTime[i] = 0.0f;
		}
	}
	

}

void WeakEnemy::Animation(float& time, int max)
{
	for (int i = 0; i < max; i++)
	{
		//�G���v���C���[�������ĂȂ��Ƃ�
		if (m_enemySearchFlag[i] == false)
		{
			if (m_animation[3] != -1 || m_animation[4] != -1 || m_animation[5] != -1 ||
				m_animation[6] != -1)
			{
				//�A�j���[�V�����f�^�b�`
				MV1DetachAnim(m_handle, m_animation[3]);
				MV1DetachAnim(m_handle, m_animation[4]);
				MV1DetachAnim(m_handle, m_animation[5]);
				MV1DetachAnim(m_handle, m_animation[6]);


				//�A�j���[�V�����A�^�b�`
				m_animation[0] = MV1AttachAnim(m_handle, 0, m_animStand, TRUE);

				time = 0.0f;

				m_animation[3] = -1;
				m_animation[4] = -1;
				m_animation[5] = -1;
				m_animation[6] = -1;

			}
		}
		//�G���v���C���[����������(�Ր�Ԑ�)
		if (m_enemySearchFlag[i] == true && m_enemyWait[i] == false && m_weakEnemyMoveAttack[i] == false)
		{
			if (m_animation[0] != -1 || m_animation[4] != -1 || m_animation[5] != -1 ||
				m_animation[6] != -1)
			{
				//�A�j���[�V�����f�^�b�`
				MV1DetachAnim(m_handle, m_animation[0]);
				MV1DetachAnim(m_handle, m_animation[4]);
				MV1DetachAnim(m_handle, m_animation[5]);
				MV1DetachAnim(m_handle, m_animation[6]);


				//�A�j���[�V�����A�^�b�`
				m_animation[3] = MV1AttachAnim(m_handle, 0, m_animWalk, TRUE);

				time = 0.0f;

				m_animation[0] = -1;
				m_animation[4] = -1;
				m_animation[5] = -1;
				m_animation[6] = -1;

			}
		}
		//�G�̎˒������ɓ������Ƃ�
		//������
		if (m_randomAction == 0 && m_enemyWait[i] == true)
		{
			if (m_animation[0] != -1 || m_animation[3] != -1 || m_animation[5] != -1 ||
				m_animation[6] != -1)
			{
				//�A�j���[�V�����f�^�b�`
				MV1DetachAnim(m_handle, m_animation[0]);
				MV1DetachAnim(m_handle, m_animation[3]);
				MV1DetachAnim(m_handle, m_animation[5]);
				MV1DetachAnim(m_handle, m_animation[6]);

				//�A�j���[�V�����A�^�b�`
				m_animation[4] = MV1AttachAnim(m_handle, 0, m_animLeftWalking, TRUE);

				time = 0.0f;

				m_animation[0] = -1;
				m_animation[3] = -1;
				m_animation[5] = -1;
				m_animation[6] = -1;

			}
		}
		//�E����
		if (m_randomAction[i] == 1 && m_enemyWait[i] == true)
		{
			if (m_animation[0] != -1 || m_animation[3] != -1 || m_animation[4] != -1 ||
				m_animation[6] != -1)
			{
				//�A�j���[�V�����f�^�b�`
				MV1DetachAnim(m_handle, m_animation[0]);
				MV1DetachAnim(m_handle, m_animation[3]);
				MV1DetachAnim(m_handle, m_animation[4]);
				MV1DetachAnim(m_handle, m_animation[6]);

				//�A�j���[�V�����A�^�b�`
				m_animation[5] = MV1AttachAnim(m_handle, 0, m_animRightWalking, TRUE);

				time = 0.0f;

				m_animation[0] = -1;
				m_animation[3] = -1;
				m_animation[4] = -1;
				m_animation[6] = -1;

			}
		}
		//�U�����[�V����
		if (m_randomAction[i] == 2 && m_enemyWait[i] == true)
		{
			if (m_animation[0] != -1 || m_animation[3] != -1 || m_animation[4] != -1 ||
				m_animation[5] != -1)
			{
				//�A�j���[�V�����f�^�b�`
				MV1DetachAnim(m_handle, m_animation[0]);
				MV1DetachAnim(m_handle, m_animation[3]);
				MV1DetachAnim(m_handle, m_animation[4]);
				MV1DetachAnim(m_handle, m_animation[5]);

				//�A�j���[�V�����A�^�b�`
				m_animation[6] = MV1AttachAnim(m_handle, 0, m_animAttack1, TRUE);

				time = 0.0f;

				m_animation[0] = -1;
				m_animation[3] = -1;
				m_animation[4] = -1;
				m_animation[5] = -1;
			}
		}

		//�G�����񂾂玀�ʃA�j���[�V����������
		if (m_weakEnemyHp[i] <= 0.0f)
		{
			if (m_animation[0] != -1 || m_animation[1] != -1 || m_animation[3] != -1 ||
				m_animation[4] != -1 || m_animation[5] != -1 || m_animation[6] != -1)
			{
				//�A�j���[�V�����f�^�b�`
				MV1DetachAnim(m_handle, m_animation[0]);
				MV1DetachAnim(m_handle, m_animation[1]);
				MV1DetachAnim(m_handle, m_animation[3]);
				MV1DetachAnim(m_handle, m_animation[4]);
				MV1DetachAnim(m_handle, m_animation[5]);
				MV1DetachAnim(m_handle, m_animation[6]);

				//�A�j���[�V�����A�^�b�`
				m_animation[2] = MV1AttachAnim(m_handle, 0, m_animDeath, TRUE);

				time = 0.0f;

				m_animation[0] = -1;
				m_animation[1] = -1;
				m_animation[3] = -1;
				m_animation[4] = -1;
				m_animation[5] = -1;
				m_animation[6] = -1;

			}
		}

		//�Đ����Ԃ��A�j���[�V�����̑��Đ����ԂɒB������Đ����Ԃ�0�ɖ߂�
		if (time >= m_totalAnimTime[0] && m_animation[0] != -1)
		{
			time = 0.0f;
		}
		if (time >= m_totalAnimTime[2] && m_animation[2] != -1)
		{
			time = 120.0f;
		}
		if (time >= m_totalAnimTime[3] && m_animation[3] != -1)
		{
			time = 0.0f;
		}
		if (time >= m_totalAnimTime[4] && m_animation[4] != -1)
		{
			time = 0.0f;
		}
		if (time >= m_totalAnimTime[5] && m_animation[5] != -1)
		{
			time = 0.0f;
		}
		if (time >= m_totalAnimTime[6] && m_animation[6] != -1)
		{
			m_weakEnemyMoveAttack[i] = false;

			m_randomNextActionTime[i] = 50.0f;

			time = 0.0f;
		}

		//�Đ����Ԃ��Z�b�g����
		if (m_animation[0] != -1)
		{
			MV1SetAttachAnimTime(m_handle, m_animation[0], time);
		}
		if (m_animation[2] != -1)
		{
			MV1SetAttachAnimTime(m_handle, m_animation[2], time);
		}
		if (m_animation[3] != -1)
		{
			MV1SetAttachAnimTime(m_handle, m_animation[3], time);
		}
		if (m_animation[4] != -1)
		{
			MV1SetAttachAnimTime(m_handle, m_animation[4], time);
		}
		if (m_animation[5] != -1)
		{
			MV1SetAttachAnimTime(m_handle, m_animation[5], time);
		}
		if (m_animation[6] != -1)
		{
			MV1SetAttachAnimTime(m_handle, m_animation[6], time);
		}
	}
}

void WeakEnemy::Draw(int max)
{
	for (int i = 0; i < max; i++)
	{
		//�����x�N�g��
		Vec3 vec = m_vec.GetNormalized() * m_len * 0.5f;

		Pos3 pos1 = m_weakColPos[i] + vec;
		Pos3 pos2 = m_weakColPos[i] - vec;

		if (m_weakEnemyHp[i] > 0.0f)
		{
			DrawCapsule3D(pos1.GetVector(), pos2.GetVector(), m_capsuleRadius, 16, m_color, 0, false);

			//���G�͈͉~��3D�`��
			DrawSphere3D(m_colSearchPos[i].GetVector(), m_searchRadius, 16, m_seachColor, m_seachColor, false);

			//��苗���͈͕̔`��
			DrawSphere3D(m_colDistancePos[i].GetVector(), m_distanceRadius, 16, m_distanceColor, m_distanceColor, false);

			//�U������`��
			DrawSphere3D(m_colAttackPos[i].GetVector(), m_attackRadius, 16, 0xffffff, 0xffffff, false);
		}

		//3D���f���|�W�V�����ݒ�
		MV1SetPosition(m_handle, m_weakEnemyPos[i]);

		//3D���f���`��
		MV1DrawModel(m_handle);

		//3D���f���̉�]�n���Z�b�g����
		MV1SetRotationXYZ(m_handle, VGet(0.0f, m_weakEnemyAngle[i], 0.0f));

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
	
}

void WeakEnemy::End(int max)
{
}

bool WeakEnemy::isSphereHit(const SphereCol& col, float damage, int max)
{
	for (int i = 0; i < max; i++)
	{
		bool isHit = m_weakCapsuleCol[i].IsHitSphere(col);

		//�_���[�W���󂯂�����
		if (isHit)
		{
			m_color = 0xffff00;

			//�_���[�W����񂾂��^����
			if (m_damageReceived == false)
			{
				m_weakEnemyHp[i] = m_weakEnemyHp[i] - damage;

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
}

bool WeakEnemy::isSeachHit(const CapsuleCol& col, int max)
{
	for (int i = 0; i < max; i++)
	{
		bool isHit = m_colSearch[i].IsHitCapsule(col);

		//�v���C���[������������
		if (isHit)
		{
			m_seachColor = 0xffff00;

			m_enemySearchFlag[i] = true;
		}
		else
		{
			m_seachColor = 0xffffff;

			m_enemySearchFlag[i] = false;
		}

		return isHit;
	}
}

bool WeakEnemy::isDistanceHit(const CapsuleCol& col, int max)
{
	for (int i = 0; i < max; i++)
	{
		bool isHit = m_colDistance[i].IsHitCapsule(col);

		//���͈͓��Ƀv���C���[����������
		if (isHit)
		{
			m_distanceColor = 0xffff00;

			m_enemyWait[i] = true;
		}
		else
		{
			m_distanceColor = 0xffffff;

			m_enemyWait[i] = false;
		}

		return isHit;
	}
	
}

VECTOR WeakEnemy::GetPos(int max)
{
	for (int i = 0; i < max; i++)
	{
		return m_weakEnemyPos[i];
	}
}

float WeakEnemy::GetPosX(int max)
{
	for (int i = 0; i < max; i++)
	{
		return m_weakEnemyPos[i].x;
	}
	
}

float WeakEnemy::GetPosY(int max)
{
	for (int i = 0; i < max; i++)
	{
		return m_weakEnemyPos[i].y;
	}
}

float WeakEnemy::GetPosZ(int max)
{
	for (int i = 0; i < max; i++)
	{
		return m_weakEnemyPos[i].z;
	}
}

const CapsuleCol WeakEnemy::GetCol(int max)
{
	for (int i = 0; i < max; i++)
	{
		return m_weakCapsuleCol[i];
	}
	
}

const SphereCol WeakEnemy::GetAttackCol(int max)
{
	for (int i = 0; i < max; i++)
	{
		return m_colAttack[i];
	}
	
}
