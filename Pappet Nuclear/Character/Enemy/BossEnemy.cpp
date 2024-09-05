#include "BossEnemy.h"
#include "Character/Player/Player.h"
#include "Map/Map.h"

BossEnemy::BossEnemy() :
	m_gameClear(false),
	m_bossDistance(false),
	m_bossBattle(false),
	m_bossMoveAttack(false),
	m_bossMoveAttackPattern(false),
	m_bossAttack1(false),
	m_bossAttack2(false),
	m_bossAttack3(false),
	m_bossAttack(-1),
	m_one(false),
	m_bossAttackRadius1(0.0f),
	m_bossAttackRadius2(0.0f),
	m_bossAttackRadius3(0.0f),
	m_outPush(VGet(0.0f, 0.0f, 0.0f)),
	m_effectActivation(false),
	m_effect(0),
	m_outVec(VGet(0.0f, 0.0f, 0.0f)),
	m_distanceVec(VGet(0.0f,0.0f,0.0f)),
	m_length(0.0f)
{
}

BossEnemy::~BossEnemy()
{
}

void BossEnemy::Init()
{
	//�G��HP������
	m_hp = 1200.0f;

	//�G�̍U���͏�����
	m_attack = 30.0f;

	//�G�̃X�s�[�h����
	m_speed = 0.01f;

	m_posX = -600.0f;
	m_posY = 0.0f;
	m_posZ = 0.0f;

	m_pos = VGet(m_posX, m_posY, m_posZ);

	m_bossBattle = false;

	m_bossMoveAttack = false;
	m_bossAttack = -1;

	m_bossAttack1 = false;
	m_bossAttack2 = false;
	m_bossAttack3 = false;

	//�����蔻��
	m_colPos = Pos3(m_pos.x - 2.0f, m_pos.y + 35.0f, m_pos.z);
	m_colBossAttackPos1 = Pos3(m_pos.x - 50.0f, m_pos.y + 35.0f, m_pos.z);
	m_colBossAttackPos2 = Pos3(m_pos.x - 50.0f, m_pos.y + 35.0f, m_pos.z);
	m_colBossAttackPos3 = Pos3(m_pos.x, m_pos.y + 35.0f, m_pos.z);
	m_initializationPos = Pos3(0.0f, -1000.0f, 0.0f);
	m_vec = Vec3(0.0f, m_pos.y + 2.0f, 0.0f);
	m_len = 40.0f;
	m_capsuleRadius = 35.0f;
	m_sphereRadius = 120.0f;
	m_bossAttackRadius1 = 60.0f;
	m_bossAttackRadius2 = 40.0f;
	m_bossAttackRadius3 = 130.0f;
	m_capsuleCol.Init(m_colPos, m_vec, m_len, m_capsuleRadius);
	m_colDistance.Init(m_colPos, m_sphereRadius);
	m_colBossAttackSphere1.Init(m_initializationPos, m_bossAttackRadius1);
	m_colBossAttackSphere2.Init(m_initializationPos, m_bossAttackRadius2);
	m_colBossAttackSphere3.Init(m_initializationPos, m_bossAttackRadius3);

	//��񂾂�����������
	if (m_one == false)
	{
		effect->BossInit();

		m_one = true;
	}
	
}

void BossEnemy::Update(Player& player, Map& map)
{
	m_colPos = Pos3(m_pos.x - 2.0f, m_pos.y + 35.0f, m_pos.z);
	m_colDistance.Update(m_colPos);

	//�A�j���[�V�����Đ����x
	if (m_bossAttack1 == true || m_bossAttack2 == true)
	{
		m_playTime += 0.1f;
	}
	else
	{
		m_playTime += 0.5f;
	}

	//�{�X�̕����ɓ�����
	if (map.GetRoomEntered() == true)
	{
		if (m_bossDistance == false || m_bossMoveAttackPattern == true)
		{

			float X = m_pos.x - player.GetPosX();
			float Z = m_pos.z - player.GetPosZ();

			//�{�X����v���C���[�̃x�N�g�����Z�o
			m_distanceVec = VSub(m_pos, player.GetPos());

			//Y����0
			m_distanceVec.y = 0.0f;

			//2�l�̋������Z�o
			m_length = VSize(m_distanceVec);

			//�x�N�g���𐳋K������
			m_outVec = VScale(m_distanceVec, 1.0f / m_length);

			//�U���p�^�[��1�̎��̓v���C���[�̕�������
			if (m_bossBattle == true && m_bossMoveAttack == false || m_bossMoveAttackPattern == true)
			{
				//�v���C���[�̕�������
				m_angle = atan2f(X, Z);

			}

			//�{�X�̐퓬��Ԉڍs
			m_bossBattle = true;
		}
	}

	if (m_bossDistance == false && m_bossBattle == true && m_bossMoveAttack == false)
	{
		//�G���ړ�����
		m_pos = VAdd(m_pos, m_move);
	}

	//�G�����S������
	if (m_hp <= 0.0f)
	{
	}
	else
	{
		m_capsuleCol.Update(m_colPos, m_vec);
	}

	if (m_bossAttack == -1)
	{
		m_colBossAttackSphere1.Update(m_initializationPos);
		m_colBossAttackSphere2.Update(m_initializationPos);
		m_colBossAttackSphere3.Update(m_initializationPos);
	}

	//�U������𐳖ʂɎ����Ă���
	m_colBossAttackPos1.x = m_pos.x + sinf(m_angle) * -75.0f;
	m_colBossAttackPos1.z = m_pos.z - cosf(m_angle) * 75.0f;
	m_colBossAttackPos2.x = m_pos.x + sinf(m_angle) * -75.0f;
	m_colBossAttackPos2.z = m_pos.z - cosf(m_angle) * 75.0f;
	m_colBossAttackPos3 = Pos3(m_pos.x, m_pos.y + 35.0f, m_pos.z);

	Action(player);

	Animation(m_playTime);
}

void BossEnemy::Action(Player& player)
{
	//�v���C���[�ƓG�̑��΋������Z�o
	VECTOR tracking = VSub(player.GetPos(), m_pos);

	//�{�X�̐퓬���
	if (m_bossBattle == true && m_bossDistance == false && m_bossMoveAttack == false)
	{
		m_speed = 0.01f;

		m_move = VScale(tracking, m_speed);
	}
	//�˒������ɓ�����
	if (m_bossDistance == true)
	{
		//�s�����I���܂ň����s
		if (m_bossMoveAttack == false)
		{
			m_bossAttack = GetRand(2);

			m_bossMoveAttack = true;
		}
		//�U���̓����蔻��
		if (m_bossAttack == 0 && m_bossAttack1 == true)
		{
			

			//��莞�Ԃ�������ƌ����Ȃ�
			if (m_playTime >= 30.0f)
			{
				m_bossMoveAttackPattern = false;
			}

			if (m_playTime >= 38.0f && m_playTime <= 43.0f)
			{
				m_colBossAttackSphere1.Update(m_colBossAttackPos1);
			}
			else
			{
				m_colBossAttackSphere1.Update(m_initializationPos);
			}
		}
		if (m_bossAttack == 1 && m_bossAttack2 == true)
		{
			

			//��莞�Ԃ�������ƌ����Ȃ�
			if (m_playTime >= 1.0f)
			{
				m_bossMoveAttackPattern = false;
			}

			if (m_playTime >= 7.0f && m_playTime <= 11.0f)
			{
				m_colBossAttackSphere2.Update(m_colBossAttackPos2);
			}
			else
			{
				m_colBossAttackSphere2.Update(m_initializationPos);
			}
		}
		if (m_bossAttack == 2 && m_bossAttack3 == true)
		{
			if (m_effectActivation == false)
			{
				m_effect = PlayEffekseer3DEffect(effect->GetBossAttackEffect3());

				SetPosPlayingEffekseer3DEffect(m_effect, m_pos.x, 0.0f, m_pos.z);

				m_effectActivation = true;
			}
			

			if (m_playTime >= 58.0f && m_playTime <= 63.0f)
			{
				m_colBossAttackSphere3.Update(m_colBossAttackPos3);
			}
			else
			{
				m_colBossAttackSphere3.Update(m_initializationPos);
			}
		}
	}

	//�G�t�F�N�g�X�V
	effect->Update();
}

void BossEnemy::Animation(float& time)
{
	//�G�����񂾂Ƃ��̃A�j���[�V����
	if (m_hp <= 0.0f)
	{
		if (m_bossAnimation[0] != -1 || m_bossAnimation[3] != -1 || m_bossAnimation[4] != -1 ||
			m_bossAnimation[5] != -1 || m_bossAnimation[6] != -1)
		{
			m_bossAttack1 = false;
			m_bossAttack2 = false;
			m_bossAttack3 = false;


			//�A�j���[�V�����f�^�b�`
			MV1DetachAnim(m_bossModelHandle, m_bossAnimation[0]);
			MV1DetachAnim(m_bossModelHandle, m_bossAnimation[3]);
			MV1DetachAnim(m_bossModelHandle, m_bossAnimation[4]);
			MV1DetachAnim(m_bossModelHandle, m_bossAnimation[5]);
			MV1DetachAnim(m_bossModelHandle, m_bossAnimation[6]);


			//�A�j���[�V�����A�^�b�`
			m_bossAnimation[2] = MV1AttachAnim(m_bossModelHandle, 0, m_bossAnimDeath, TRUE);

			time = 0.0f;

			m_bossAnimation[0] = -1;
			m_bossAnimation[3] = -1;
			m_bossAnimation[4] = -1;
			m_bossAnimation[5] = -1;
			m_bossAnimation[6] = -1;

		}
	}
	if (m_bossBattle == true)
	{
		//�G���U�����ĂȂ���
		if (m_bossMoveAttack == false)
		{
			if (m_bossAnimation[0] != -1 || m_bossAnimation[4] != -1 || m_bossAnimation[5] != -1 ||
				m_bossAnimation[6] != -1)
			{
				m_bossAttack1 = false;
				m_bossAttack2 = false;
				m_bossAttack3 = false;

				//�A�j���[�V�����f�^�b�`
				MV1DetachAnim(m_bossModelHandle, m_bossAnimation[0]);
				MV1DetachAnim(m_bossModelHandle, m_bossAnimation[4]);
				MV1DetachAnim(m_bossModelHandle, m_bossAnimation[5]);
				MV1DetachAnim(m_bossModelHandle, m_bossAnimation[6]);

				//�A�j���[�V�����A�^�b�`
				m_bossAnimation[3] = MV1AttachAnim(m_bossModelHandle, 0, m_bossAnimWalk, TRUE);

				time = 0.0f;

				m_bossAnimation[0] = -1;
				m_bossAnimation[4] = -1;
				m_bossAnimation[5] = -1;
				m_bossAnimation[6] = -1;

			}
		}
		//�U���p�^�[��1
		if (m_bossAttack == 0 && m_bossMoveAttack == true)
		{
			if (m_bossAnimation[0] != -1 || m_bossAnimation[3] != -1 || m_bossAnimation[5] != -1 ||
				m_bossAnimation[6] != -1)
			{
				m_bossAttack1 = true;
				m_bossAttack2 = false;
				m_bossAttack3 = false;

				m_bossMoveAttackPattern = true;

				//�A�j���[�V�����f�^�b�`
				MV1DetachAnim(m_bossModelHandle, m_bossAnimation[0]);
				MV1DetachAnim(m_bossModelHandle, m_bossAnimation[3]);
				MV1DetachAnim(m_bossModelHandle, m_bossAnimation[5]);
				MV1DetachAnim(m_bossModelHandle, m_bossAnimation[6]);

				//�A�j���[�V�����A�^�b�`
				m_bossAnimation[4] = MV1AttachAnim(m_bossModelHandle, 0, m_bossAnimAttack1, TRUE);

				//�U����
				m_attack = 50.0f;

				time = 0.0f;

				m_bossAnimation[0] = -1;
				m_bossAnimation[3] = -1;
				m_bossAnimation[5] = -1;
				m_bossAnimation[6] = -1;

			}
		}
		//�U���p�^�[��2
		if (m_bossAttack == 1 && m_bossMoveAttack == true)
		{
			if (m_bossAnimation[0] != -1 || m_bossAnimation[3] != -1 || m_bossAnimation[4] != -1 ||
				m_bossAnimation[6] != -1)
			{
				m_bossAttack1 = false;
				m_bossAttack2 = true;
				m_bossAttack3 = false;

				m_bossMoveAttackPattern = true;

				//�A�j���[�V�����f�^�b�`
				MV1DetachAnim(m_bossModelHandle, m_bossAnimation[0]);
				MV1DetachAnim(m_bossModelHandle, m_bossAnimation[3]);
				MV1DetachAnim(m_bossModelHandle, m_bossAnimation[4]);
				MV1DetachAnim(m_bossModelHandle, m_bossAnimation[6]);

				//�A�j���[�V�����A�^�b�`
				m_bossAnimation[5] = MV1AttachAnim(m_bossModelHandle, 0, m_bossAnimAttack2, TRUE);

				//�U����
				m_attack = 30.0f;

				time = 0.0f;

				m_bossAnimation[0] = -1;
				m_bossAnimation[3] = -1;
				m_bossAnimation[4] = -1;
				m_bossAnimation[6] = -1;
			}
		}
		//�U���p�^�[��3
		if (m_bossAttack == 2 && m_bossMoveAttack == true)
		{
			if (m_bossAnimation[0] != -1 || m_bossAnimation[3] != -1 || m_bossAnimation[4] != -1 ||
				m_bossAnimation[5] != -1)
			{
				m_bossAttack1 = false;
				m_bossAttack2 = false;
				m_bossAttack3 = true;

				//�A�j���[�V�����f�^�b�`
				MV1DetachAnim(m_bossModelHandle, m_bossAnimation[0]);
				MV1DetachAnim(m_bossModelHandle, m_bossAnimation[3]);
				MV1DetachAnim(m_bossModelHandle, m_bossAnimation[4]);
				MV1DetachAnim(m_bossModelHandle, m_bossAnimation[5]);

				//�A�j���[�V�����A�^�b�`
				m_bossAnimation[6] = MV1AttachAnim(m_bossModelHandle, 0, m_bossAnimAttack3, TRUE);

				//�U����
				m_attack = 80.0f;

				time = 0.0f;

				m_bossAnimation[0] = -1;
				m_bossAnimation[3] = -1;
				m_bossAnimation[4] = -1;
				m_bossAnimation[5] = -1;
			}

		}
		
	}

	//�Đ����Ԃ��A�j���[�V�����̑��Đ����ԂɒB������Đ����Ԃ�0�ɖ߂�
	if (time >= m_bossTotalAnimTime[0] && m_bossAnimation[0] != -1)
	{
		time = 0.0f;
	}
	if (time >= m_bossTotalAnimTime[2] && m_bossAnimation[2] != -1)
	{
		//�{�X��|������Q�[���N���A
		m_gameClear = true;

		time = 120.0f;
	}
	if (time >= m_bossTotalAnimTime[3] && m_bossAnimation[3] != -1)
	{
		time = 0.0f;
	}
	if (time >= m_bossTotalAnimTime[4] && m_bossAnimation[4] != -1)
	{
		m_bossMoveAttack = false;

		m_bossAttack1 = false;

		m_effectActivation = false;

		time = 0.0f;
	}
	if (time >= m_bossTotalAnimTime[5] && m_bossAnimation[5] != -1)
	{
		m_bossMoveAttack = false;

		m_bossAttack2 = false;

		m_effectActivation = false;

		time = 0.0f;
	}
	if (time >= m_bossTotalAnimTime[6] && m_bossAnimation[6] != -1)
	{
		m_bossMoveAttack = false;

		m_bossAttack3 = false;

		m_effectActivation = false;

		time = 0.0f;
	}
	//�Đ����Ԃ��Z�b�g����
	if (m_bossAnimation[0] != -1)
	{
		MV1SetAttachAnimTime(m_bossModelHandle, m_bossAnimation[0], time);
	}
	if (m_bossAnimation[2] != -1)
	{
		MV1SetAttachAnimTime(m_bossModelHandle, m_bossAnimation[2], time);
	}
	if (m_bossAnimation[3] != -1)
	{
		MV1SetAttachAnimTime(m_bossModelHandle, m_bossAnimation[3], time);
	}
	if (m_bossAnimation[4] != -1)
	{
		MV1SetAttachAnimTime(m_bossModelHandle, m_bossAnimation[4], time);
	}
	if (m_bossAnimation[5] != -1)
	{
		MV1SetAttachAnimTime(m_bossModelHandle, m_bossAnimation[5], time);
	}
	if (m_bossAnimation[6] != -1)
	{
		MV1SetAttachAnimTime(m_bossModelHandle, m_bossAnimation[6], time);
	}
}

void BossEnemy::Draw()
{
	//�����x�N�g��
	Vec3 vec = m_vec.GetNormalized() * m_len * 0.5f;

	Pos3 pos1 = m_colPos + vec;
	Pos3 pos2 = m_colPos - vec;

	//�G�������Ă��鎞�͕`��
	if (m_hp > 0.0f)
	{
		//DrawCapsule3D(pos1.GetVector(), pos2.GetVector(), m_capsuleRadius, 16, m_color, 0, false);

		////�U���͈͕̔`��
		//DrawSphere3D(m_colPos.GetVector(), m_sphereRadius, 16, m_distanceColor, m_distanceColor, false);

		////�U������`��
		//DrawSphere3D(m_colBossAttackPos1.GetVector(), m_bossAttackRadius1, 16, 0xffffff, 0xffffff, false);
		//DrawSphere3D(m_colBossAttackPos2.GetVector(), m_bossAttackRadius2, 16, 0xffffff, 0xffffff, false);
		//DrawSphere3D(m_colBossAttackPos3.GetVector(), m_bossAttackRadius3, 16, 0xffffff, 0xffffff, false);
	}

	DrawFormatString(150, 300, 0xffffff, "�G�t�F�N�g : %d", IsEffekseer3DEffectPlaying(effect->GetBossAttackEffect3()));

	//3D���f���|�W�V�����ݒ�
	MV1SetPosition(m_bossModelHandle, m_pos);

	//3D���f���`��
	MV1DrawModel(m_bossModelHandle);

	//3D���f���̉�]�n���Z�b�g����
	MV1SetRotationXYZ(m_bossModelHandle, VGet(0.0f, m_angle, 0.0f));

	//�G�t�F�N�g�̕`��
	effect->Draw();
}

void BossEnemy::End()
{
	//���������
	effect->End();
}

bool BossEnemy::isSphereHit(const SphereCol& col, float damage)
{
	bool isHit = m_capsuleCol.IsHitSphere(col);

	//�_���[�W���󂯂�����
	if (isHit)
	{
		m_color = 0xffff00;

		//�_���[�W����񂾂��^����
		if (m_damageReceived == false)
		{
			m_hp = m_hp - damage;

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

bool BossEnemy::isPlayerHit(const CapsuleCol& col, VECTOR vec, float bounce)
{
	bool isHit = m_capsuleCol.IsHitCapsule(col);

	//�v���C���[�Ɠ���������
	if (isHit)
	{
		m_color = 0xffff00;

		//�@���x�N�g�����Ƃ��悤�ɂ��Ă���
		m_outPush = VAdd(m_outPush, VScale(vec, 1.0f));
	}
	else
	{
		m_outPush = VGet(0.0f, 0.0f, 0.0f);

		m_color = 0xffffff;
	}

	return isHit;
}

bool BossEnemy::isCapsuleHit(const CapsuleCol& col)
{
	bool isHit = m_colDistance.IsHitCapsule(col);

	//���͈͓��Ƀv���C���[����������
	if (isHit)
	{
		m_distanceColor = 0xffff00;

		m_bossDistance = true;
	}
	else
	{
		m_distanceColor = 0xffffff;

		m_bossDistance = false;
	}

	return isHit;
}
