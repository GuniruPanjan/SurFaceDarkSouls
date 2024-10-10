#include "BossEnemy.h"
#include "Character/Player/Player.h"
#include "Map/Map.h"

namespace
{
	bool attack;    //�U��SE�̔���
	bool patternOne;    //pattern�ϐ�����񂾂��ύX����
	int walkTime;   //����SE�Ԋu
	float difPSize;   //�v���C���[�Ƃ̋���
	float difSSize;   //���Ƃ̋���
	float correctionAngle;    //�G���v���C���[�̈ʒu�ɂ���ĕ�����␳���邽�߂̕ϐ�
}

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
	m_bounceAngle(0.0f),
	m_outPush(VGet(0.0f, 0.0f, 0.0f)),
	m_playerHit(false),
	m_turnLeft(false),
	m_turnRight(false)
{
}

BossEnemy::~BossEnemy()
{
}

void BossEnemy::Init()
{
	//�G��HP������
	m_hp = 1000.0f;

	//�G�̍U���͏�����
	m_attack = 30.0f;

	//�G�̃X�s�[�h����
	m_speed = 0.01f;

	m_posX = -600.0f;
	m_posY = 0.0f;
	m_posZ = 0.0f;

	//�R�A������
	m_core = 2500;

	//���S���������������
	m_death = false;

	m_pos = VGet(m_posX, m_posY, m_posZ);

	m_bossBattle = false;

	m_bossMoveAttack = false;
	m_bossAttack = -1;

	m_bossAttack1 = false;
	m_bossAttack2 = false;
	m_bossAttack3 = false;
	patternOne = false;

	//�����蔻��
	m_colPos = Pos3(m_pos.x - 2.0f, m_pos.y + 35.0f, m_pos.z);
	m_colBossAttackPos1 = Pos3(m_pos.x - 50.0f, m_pos.y + 35.0f, m_pos.z);
	m_colBossAttackPos2 = Pos3(m_pos.x - 50.0f, m_pos.y + 35.0f, m_pos.z);
	m_colBossAttackPos3 = Pos3(m_pos.x, m_pos.y + 35.0f, m_pos.z);
	m_initializationPos = Pos3(1000.0f, -1000.0f, 1000.0f);
	m_vec = Vec3(0.0f, m_pos.y + 2.0f, 0.0f);
	m_len = 40.0f;
	m_capsuleRadius = 35.0f;
	m_sphereRadius = 120.0f;
	m_bossAttackRadius1 = 60.0f;
	m_bossAttackRadius2 = 40.0f;
	m_bossAttackRadius3 = 130.0f;
	m_capsuleCol.Init(m_colPos, m_vec, m_len, m_capsuleRadius);
	m_bossColDistance.Init(m_colPos, m_sphereRadius);
	m_colBossAttackSphere1.Init(m_initializationPos, m_bossAttackRadius1);
	m_colBossAttackSphere2.Init(m_initializationPos, m_bossAttackRadius2);
	m_colBossAttackSphere3.Init(m_initializationPos, m_bossAttackRadius3);

	m_effectActivation = false;

	walkTime = 0;

	//��񂾂�����������
	if (m_one == false)
	{
		effect->BossInit();

		se->BossInit();

		m_one = true;
		
	}
	
	attack = false;

	//se->Init();
}

void BossEnemy::Update(Player& player, Map& map, int volume)
{
	m_colPos = Pos3(m_pos.x - 2.0f, m_pos.y + 35.0f, m_pos.z);
	m_bossColDistance.Update(m_colPos);

	//�G�ƃv���C���[�̑��΋���
	m_playerDif = VSub(player.GetPos(), m_pos);
	//�G�Ə��̑��΋���
	m_shieldDif = VSub(player.GetShieldPos(), m_pos);

	difPSize = VSize(m_playerDif);
	difSSize = VSize(m_shieldDif);

	//�A�j���[�V�����Đ����x
	if (m_bossAttack1 == true)
	{
		m_playTime += 0.3f;

	}
	else if (m_bossAttack2 == true)
	{
		m_playTime += 0.2f;

	}
	else
	{
		m_playTime += 0.5f;
	}

	//�v���C���[�������o�������Z�o
	float bounceX = m_pos.x - player.GetPosX();
	float bounceZ = m_pos.z - player.GetPosZ();

	m_bounceAngle = atan2f(bounceX, bounceZ);


	//�{�X�̕����ɓ�����
	if (map.GetRoomEntered() == true)
	{
		//�G���v���C���[�̈ʒu�ɂ���ĕ�����␳����
		float Cx = m_pos.x - player.GetPosX();
		float Cz = m_pos.z - player.GetPosZ();

		correctionAngle = atan2f(Cx, Cz);

		
		if (m_bossMoveAttack == false)
		{
			//���ɉ�]����
			if (m_angle > correctionAngle + 0.8f)
			{
				m_turnLeft = true;
				m_turnRight = false;
			}
			//else if (0.0f <= correctionAngle && correctionAngle <= 4.0f && m_angle <= 0.0f)
			//{
			//	m_turnLeft = true;
			//	m_turnRight = false;
			//}
			//�E�ɉ�]����
			if (m_angle < correctionAngle - 0.8f)
			{
				m_turnRight = true;
				m_turnLeft = false;
			}
			//else if (0.0f > correctionAngle && correctionAngle >= -4.0f && m_angle > 0.0f)
			//{
			//	m_turnRight = true;
			//	m_turnLeft = false;
			//}
		}

		if (m_bossDistance == false || m_bossMoveAttackPattern == true)
		{
			float X = m_pos.x - player.GetPosX();
			float Z = m_pos.z - player.GetPosZ();

			//�U���p�^�[��1�̎��̓v���C���[�̕�������
			if (m_bossBattle == true && m_bossMoveAttack == false || m_bossMoveAttackPattern == true)
			{
				if (m_turnLeft == false && m_turnRight == false)
				{
					//�v���C���[�̕�������
					m_angle = atan2f(X, Z);
				}
			}

			//�{�X�̐퓬��Ԉڍs
			m_bossBattle = true;
		}
	}
	if (m_bossDistance == false && m_bossBattle == true && m_bossMoveAttack == false && m_turnLeft == false && m_turnRight == false)
	{
		walkTime++;

		//�G���ړ�����
		m_pos = VAdd(m_pos, m_move);

		if (walkTime >= 30.0f)
		{
			PlaySoundMem(se->GetBossWalkSE(), DX_PLAYTYPE_BACK, true);

			walkTime = 0;
		}
	}
	else
	{
		walkTime = 0;
	}

	for (int i = 7; i < 9; i++)
	{
		//���[�V�����I����A���O��������
		if (m_playTime >= m_bossTotalAnimTime[i] && m_bossAnimOne[i] == true)
		{
			if (i == 7)
			{
				m_angle = correctionAngle;
			}
			if (i == 8)
			{
				m_angle = correctionAngle;
			}
		}
	}

	//�G�����S������
	if (m_hp <= 0.0f)
	{
		//��񂾂����s
		if (m_death == false)
		{
			m_baseCore = m_baseCore + m_core;

			m_death = true;
		}
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

	//�����v���C���[�̕����߂�������
	if (difPSize < difSSize)
	{
		m_playerHit = true;
	}
	else
	{
		m_playerHit = false;
	}


	//�}�b�v�Ƃ̓����蔻��p
	m_mapHitColl = VGet(m_colPos.x, m_colPos.y, m_colPos.z);

	//�U������𐳖ʂɎ����Ă���
	m_colBossAttackPos1.x = m_pos.x + sinf(m_angle) * -75.0f;
	m_colBossAttackPos1.z = m_pos.z - cosf(m_angle) * 75.0f;
	m_colBossAttackPos2.x = m_pos.x + sinf(m_angle) * -75.0f;
	m_colBossAttackPos2.z = m_pos.z - cosf(m_angle) * 75.0f;
	m_colBossAttackPos3 = Pos3(m_pos.x, m_pos.y + 35.0f, m_pos.z);

	Action(player);

	Animation(m_playTime);

	se->Update(volume);
}

void BossEnemy::Action(Player& player)
{
	//�v���C���[�ƓG�̑��΋������Z�o
	VECTOR tracking = VSub(player.GetPos(), m_pos);

	//�{�X�̐퓬���
	if (m_bossBattle == true && m_bossDistance == false && m_bossMoveAttack == false && m_turnLeft == false && m_turnRight == false)
	{
		m_speed = 0.01f;

		m_move = VScale(tracking, m_speed);
	}
	//�˒������ɓ�����
	if (m_bossDistance == true && m_turnLeft == false && m_turnRight == false)
	{
		//�s�����I���܂ň����s
		if (m_bossMoveAttack == false)
		{
			//�U���̓����蔻���������
			m_colBossAttackSphere1.Update(m_initializationPos);
			m_colBossAttackSphere2.Update(m_initializationPos);
			m_colBossAttackSphere3.Update(m_initializationPos);

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

			if (m_playTime >= 38.0f && m_playTime <= 45.0f)
			{
				if (attack == false)
				{
					PlaySoundMem(se->GetBossAttackSE1(), DX_PLAYTYPE_BACK, true);

					attack = true;
				}

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

			if (m_playTime >= 7.0f && m_playTime <= 12.0f)
			{
				if (attack == false)
				{
					PlaySoundMem(se->GetBossAttackSE2(), DX_PLAYTYPE_BACK, true);

					attack = true;
				}

				m_colBossAttackSphere2.Update(m_colBossAttackPos2);
			}	
			else
			{
				m_colBossAttackSphere2.Update(m_initializationPos);
			}
		}
		if (m_bossAttack == 2 && m_bossAttack3 == true)
		{	

			if (m_playTime >= 5.0f)
			{

				if (m_effectActivation == false)
				{
					m_effect = PlayEffekseer3DEffect(effect->GetBossAttackEffect3());

					m_effectActivation = true;
				}
			}
			if (m_playTime >= 25.0f)
			{

					if (attack == false)
					{
						PlaySoundMem(se->GetBossAttackSE3(), DX_PLAYTYPE_BACK, true);

						attack = true;
					}
	
			}
			if (m_playTime >= 58.0f && m_playTime <= 68.0f)
			{
				m_colBossAttackSphere3.Update(m_colBossAttackPos3);
			}
			else
			{
				m_colBossAttackSphere3.Update(m_initializationPos);
			}
		}
	}

	//�G�t�F�N�g�|�W�V�����X�V
	SetPosPlayingEffekseer3DEffect(m_effect, m_pos.x, 0.0f, m_pos.z);

	//�G�t�F�N�g�X�V
	//effect->Update();
}

void BossEnemy::Animation(float& time)
{
	if (m_bossAnimBlend < 1.0f)
	{
		m_bossAnimBlend += 0.1f;
	}
	//�G�����񂾂Ƃ��̃A�j���[�V����
	if (m_hp <= 0.0f)
	{
		pAnim->AnimationBlend(time, m_bossModelHandle, m_bossAnimation[2], m_bossAnimation[0], m_bossAnimBlend, m_bossAnimOne[0], m_bossAnimOne[2], m_bossAnimBlendOne);
		pAnim->AnimationBlend(time, m_bossModelHandle, m_bossAnimation[2], m_bossAnimation[3], m_bossAnimBlend, m_bossAnimOne[3], m_bossAnimOne[2], m_bossAnimBlendOne);
		pAnim->AnimationBlend(time, m_bossModelHandle, m_bossAnimation[2], m_bossAnimation[4], m_bossAnimBlend, m_bossAnimOne[4], m_bossAnimOne[2], m_bossAnimBlendOne);
		pAnim->AnimationBlend(time, m_bossModelHandle, m_bossAnimation[2], m_bossAnimation[5], m_bossAnimBlend, m_bossAnimOne[5], m_bossAnimOne[2], m_bossAnimBlendOne);
		pAnim->AnimationBlend(time, m_bossModelHandle, m_bossAnimation[2], m_bossAnimation[6], m_bossAnimBlend, m_bossAnimOne[6], m_bossAnimOne[2], m_bossAnimBlendOne);
		pAnim->AnimationBlend(time, m_bossModelHandle, m_bossAnimation[2], m_bossAnimation[7], m_bossAnimBlend, m_bossAnimOne[7], m_bossAnimOne[2], m_bossAnimBlendOne);
		pAnim->AnimationBlend(time, m_bossModelHandle, m_bossAnimation[2], m_bossAnimation[8], m_bossAnimBlend, m_bossAnimOne[8], m_bossAnimOne[2], m_bossAnimBlendOne);
	}
	if (m_bossBattle == true)
	{
		//�G���U�����ĂȂ���
		if (m_bossMoveAttack == false && m_turnRight == false && m_turnLeft == false)
		{

			m_bossAttack1 = false;
			m_bossAttack2 = false;
			m_bossAttack3 = false;

			pAnim->AnimationBlend(time, m_bossModelHandle, m_bossAnimation[3], m_bossAnimation[0], m_bossAnimBlend, m_bossAnimOne[0], m_bossAnimOne[3], m_bossAnimBlendOne);
			pAnim->AnimationBlend(time, m_bossModelHandle, m_bossAnimation[3], m_bossAnimation[4], m_bossAnimBlend, m_bossAnimOne[4], m_bossAnimOne[3], m_bossAnimBlendOne);
			pAnim->AnimationBlend(time, m_bossModelHandle, m_bossAnimation[3], m_bossAnimation[5], m_bossAnimBlend, m_bossAnimOne[5], m_bossAnimOne[3], m_bossAnimBlendOne);
			pAnim->AnimationBlend(time, m_bossModelHandle, m_bossAnimation[3], m_bossAnimation[6], m_bossAnimBlend, m_bossAnimOne[6], m_bossAnimOne[3], m_bossAnimBlendOne);
			pAnim->AnimationBlend(time, m_bossModelHandle, m_bossAnimation[3], m_bossAnimation[7], m_bossAnimBlend, m_bossAnimOne[7], m_bossAnimOne[3], m_bossAnimBlendOne);
			pAnim->AnimationBlend(time, m_bossModelHandle, m_bossAnimation[3], m_bossAnimation[8], m_bossAnimBlend, m_bossAnimOne[8], m_bossAnimOne[3], m_bossAnimBlendOne);
		}
		//�E���
		if (m_turnRight == true)
		{
			pAnim->AnimationBlend(time, m_bossModelHandle, m_bossAnimation[7], m_bossAnimation[0], m_bossAnimBlend, m_bossAnimOne[0], m_bossAnimOne[7], m_bossAnimBlendOne);
			pAnim->AnimationBlend(time, m_bossModelHandle, m_bossAnimation[7], m_bossAnimation[3], m_bossAnimBlend, m_bossAnimOne[3], m_bossAnimOne[7], m_bossAnimBlendOne);
			pAnim->AnimationBlend(time, m_bossModelHandle, m_bossAnimation[7], m_bossAnimation[4], m_bossAnimBlend, m_bossAnimOne[4], m_bossAnimOne[7], m_bossAnimBlendOne);
			pAnim->AnimationBlend(time, m_bossModelHandle, m_bossAnimation[7], m_bossAnimation[5], m_bossAnimBlend, m_bossAnimOne[5], m_bossAnimOne[7], m_bossAnimBlendOne);
			pAnim->AnimationBlend(time, m_bossModelHandle, m_bossAnimation[7], m_bossAnimation[6], m_bossAnimBlend, m_bossAnimOne[6], m_bossAnimOne[7], m_bossAnimBlendOne);
			pAnim->AnimationBlend(time, m_bossModelHandle, m_bossAnimation[7], m_bossAnimation[8], m_bossAnimBlend, m_bossAnimOne[8], m_bossAnimOne[7], m_bossAnimBlendOne);

		}
		//�����
		if (m_turnLeft == true)
		{
			pAnim->AnimationBlend(time, m_bossModelHandle, m_bossAnimation[8], m_bossAnimation[0], m_bossAnimBlend, m_bossAnimOne[0], m_bossAnimOne[8], m_bossAnimBlendOne);
			pAnim->AnimationBlend(time, m_bossModelHandle, m_bossAnimation[8], m_bossAnimation[3], m_bossAnimBlend, m_bossAnimOne[3], m_bossAnimOne[8], m_bossAnimBlendOne);
			pAnim->AnimationBlend(time, m_bossModelHandle, m_bossAnimation[8], m_bossAnimation[4], m_bossAnimBlend, m_bossAnimOne[4], m_bossAnimOne[8], m_bossAnimBlendOne);
			pAnim->AnimationBlend(time, m_bossModelHandle, m_bossAnimation[8], m_bossAnimation[5], m_bossAnimBlend, m_bossAnimOne[5], m_bossAnimOne[8], m_bossAnimBlendOne);
			pAnim->AnimationBlend(time, m_bossModelHandle, m_bossAnimation[8], m_bossAnimation[6], m_bossAnimBlend, m_bossAnimOne[6], m_bossAnimOne[8], m_bossAnimBlendOne);
			pAnim->AnimationBlend(time, m_bossModelHandle, m_bossAnimation[8], m_bossAnimation[7], m_bossAnimBlend, m_bossAnimOne[7], m_bossAnimOne[8], m_bossAnimBlendOne);

		}
		//�U���p�^�[��1
		if (m_bossAttack == 0 && m_bossMoveAttack == true && m_turnRight == false && m_turnLeft == false)
		{

			m_bossAttack1 = true;
			m_bossAttack2 = false;
			m_bossAttack3 = false;

			if (patternOne == false)
			{
				m_bossMoveAttackPattern = true;

				patternOne = true;
			}

			//�U����
			m_attack = 50.0f;

			pAnim->AnimationBlend(time, m_bossModelHandle, m_bossAnimation[4], m_bossAnimation[0], m_bossAnimBlend, m_bossAnimOne[0], m_bossAnimOne[4], m_bossAnimBlendOne);
			pAnim->AnimationBlend(time, m_bossModelHandle, m_bossAnimation[4], m_bossAnimation[3], m_bossAnimBlend, m_bossAnimOne[3], m_bossAnimOne[4], m_bossAnimBlendOne);
			pAnim->AnimationBlend(time, m_bossModelHandle, m_bossAnimation[4], m_bossAnimation[5], m_bossAnimBlend, m_bossAnimOne[5], m_bossAnimOne[4], m_bossAnimBlendOne);
			pAnim->AnimationBlend(time, m_bossModelHandle, m_bossAnimation[4], m_bossAnimation[6], m_bossAnimBlend, m_bossAnimOne[6], m_bossAnimOne[4], m_bossAnimBlendOne);
			pAnim->AnimationBlend(time, m_bossModelHandle, m_bossAnimation[4], m_bossAnimation[7], m_bossAnimBlend, m_bossAnimOne[7], m_bossAnimOne[4], m_bossAnimBlendOne);
			pAnim->AnimationBlend(time, m_bossModelHandle, m_bossAnimation[4], m_bossAnimation[8], m_bossAnimBlend, m_bossAnimOne[8], m_bossAnimOne[4], m_bossAnimBlendOne);

		}
		//�U���p�^�[��2
		if (m_bossAttack == 1 && m_bossMoveAttack == true && m_turnRight == false && m_turnLeft == false)
		{
			m_bossAttack1 = false;
			m_bossAttack2 = true;
			m_bossAttack3 = false;

			if (patternOne == false)
			{
				m_bossMoveAttackPattern = true;

				patternOne = true;
			}

			//�U����
			m_attack = 30.0f;

			pAnim->AnimationBlend(time, m_bossModelHandle, m_bossAnimation[5], m_bossAnimation[0], m_bossAnimBlend, m_bossAnimOne[0], m_bossAnimOne[5], m_bossAnimBlendOne);
			pAnim->AnimationBlend(time, m_bossModelHandle, m_bossAnimation[5], m_bossAnimation[3], m_bossAnimBlend, m_bossAnimOne[3], m_bossAnimOne[5], m_bossAnimBlendOne);
			pAnim->AnimationBlend(time, m_bossModelHandle, m_bossAnimation[5], m_bossAnimation[4], m_bossAnimBlend, m_bossAnimOne[4], m_bossAnimOne[5], m_bossAnimBlendOne);
			pAnim->AnimationBlend(time, m_bossModelHandle, m_bossAnimation[5], m_bossAnimation[6], m_bossAnimBlend, m_bossAnimOne[6], m_bossAnimOne[5], m_bossAnimBlendOne);
			pAnim->AnimationBlend(time, m_bossModelHandle, m_bossAnimation[5], m_bossAnimation[7], m_bossAnimBlend, m_bossAnimOne[7], m_bossAnimOne[5], m_bossAnimBlendOne);
			pAnim->AnimationBlend(time, m_bossModelHandle, m_bossAnimation[5], m_bossAnimation[8], m_bossAnimBlend, m_bossAnimOne[8], m_bossAnimOne[5], m_bossAnimBlendOne);

		}
		//�U���p�^�[��3
		if (m_bossAttack == 2 && m_bossMoveAttack == true && m_turnRight == false && m_turnLeft == false)
		{
			m_bossAttack1 = false;
			m_bossAttack2 = false;
			m_bossAttack3 = true;

			//�U����
			m_attack = 80.0f;

			pAnim->AnimationBlend(time, m_bossModelHandle, m_bossAnimation[6], m_bossAnimation[0], m_bossAnimBlend, m_bossAnimOne[0], m_bossAnimOne[6], m_bossAnimBlendOne);
			pAnim->AnimationBlend(time, m_bossModelHandle, m_bossAnimation[6], m_bossAnimation[3], m_bossAnimBlend, m_bossAnimOne[3], m_bossAnimOne[6], m_bossAnimBlendOne);
			pAnim->AnimationBlend(time, m_bossModelHandle, m_bossAnimation[6], m_bossAnimation[4], m_bossAnimBlend, m_bossAnimOne[4], m_bossAnimOne[6], m_bossAnimBlendOne);
			pAnim->AnimationBlend(time, m_bossModelHandle, m_bossAnimation[6], m_bossAnimation[5], m_bossAnimBlend, m_bossAnimOne[5], m_bossAnimOne[6], m_bossAnimBlendOne);
			pAnim->AnimationBlend(time, m_bossModelHandle, m_bossAnimation[6], m_bossAnimation[7], m_bossAnimBlend, m_bossAnimOne[7], m_bossAnimOne[6], m_bossAnimBlendOne);
			pAnim->AnimationBlend(time, m_bossModelHandle, m_bossAnimation[6], m_bossAnimation[8], m_bossAnimBlend, m_bossAnimOne[8], m_bossAnimOne[6], m_bossAnimBlendOne);

		}
		
	}
	//�o�O�C���p
	if (m_bossMoveAttack == true && m_bossAttack1 == false && m_bossAttack2 == false && m_bossAttack3 == false)
	{
		m_bossAttack = -1;

		PlaySoundMem(se->GetBossVoiceSE(), DX_PLAYTYPE_BACK, true);

		pAnim->AnimationBlend(time, m_bossModelHandle, m_bossAnimation[0], m_bossAnimation[4], m_bossAnimBlend, m_bossAnimOne[4], m_bossAnimOne[0], m_bossAnimBlendOne);
		pAnim->AnimationBlend(time, m_bossModelHandle, m_bossAnimation[0], m_bossAnimation[5], m_bossAnimBlend, m_bossAnimOne[5], m_bossAnimOne[0], m_bossAnimBlendOne);
		pAnim->AnimationBlend(time, m_bossModelHandle, m_bossAnimation[0], m_bossAnimation[6], m_bossAnimBlend, m_bossAnimOne[6], m_bossAnimOne[0], m_bossAnimBlendOne);

	}


	//�Đ����Ԃ��A�j���[�V�����̑��Đ����ԂɒB������Đ����Ԃ�0�ɖ߂�

	for (int i = 0; i < 9; i++)
	{
		if (time >= m_bossTotalAnimTime[i] && m_bossAnimOne[i] == true)
		{
			if (i == 0)
			{
				m_bossMoveAttack = false;

				time = 0.0f;
			}
			if (i == 2)
			{
				//�{�X��|������Q�[���N���A
				m_gameClear = true;

				time = 120.0f;
			}
			if (i == 3)
			{
				time = 0.0f;
			}
			if (i == 4)
			{
				m_bossMoveAttack = false;

				m_bossAttack1 = false;

				attack = false;

				time = 0.0f;
			}
			if (i == 5)
			{
				m_bossMoveAttack = false;

				m_bossAttack2 = false;

				attack = false;

				time = 0.0f;
			}
			if (i == 6)
			{
				m_bossMoveAttack = false;

				m_bossAttack3 = false;

				m_effectActivation = false;

				attack = false;

				time = 0.0f;
			}
			if (i == 7)
			{
				if (correctionAngle > m_angle + 0.8f)
				{
					m_turnRight = true;

					time = 0.0f;
				}
				else if (0.0f >= correctionAngle && correctionAngle >= -4.0f && m_angle >= 0.0f)
				{
					m_turnRight = true;

					time = 0.0f;
				}
				else   //�E��]���Ȃ��Ȃ�
				{
					m_turnRight = false;
				}
			}
			if (i == 8)
			{
				if (correctionAngle < m_angle - 0.8f)
				{
					m_turnLeft = true;

					time = 0.0f;
				}
				//�A���O�������̐����琳�̐��ɂȂ������p
				else if (0.0f <= correctionAngle && correctionAngle <= 4.0f && m_angle <= 0.0f)
				{
					m_turnLeft = true;

					time = 0.0f;
				}
				else   //����]���Ȃ��Ȃ�
				{
					m_turnLeft = false;
				}
			}

			patternOne = false;
		}
	}
	//�Đ����Ԃ��Z�b�g����
	for (int i = 0; i < 9; i++)
	{
		if (m_bossAnimOne[i] == true)
		{
			MV1SetAttachAnimTime(m_bossModelHandle, m_bossAnimation[i], time);

			//�E���
			if (i == 7)
			{
				if (m_angle < correctionAngle - 0.8f)
				{
					m_angle += 0.05f;
				}
			}
			//�����
			if (i == 8)
			{
				if (m_angle > correctionAngle + 0.8f)
				{
					m_angle -= 0.05f;
				}
			}
		}
	}
}

void BossEnemy::MapHit(Map& map)
{
	int j;

	//�v���C���[�̎��͂ɂ���R���W�����̃|���S�����擾����
	HitDim = MV1CollCheck_Sphere(map.GetCollisionMap(), -1, map.GetVectorMapPos(), 1500.0f);

	//���o���ꂽ�|���S�����ǃ|���S��(XZ���ʂɐ����ȃ|���S��)�����|���S��(XZ���ʂɐ����ł͂Ȃ��|���S��)���𔻒f����
	for (int i = 0; i < HitDim.HitNum; i++)
	{
		//XZ���ʂɐ������ǂ����̓|���S���̖@����Y������0�Ɍ���Ȃ��߂����ǂ����Ŕ��f����
		if (HitDim.Dim[i].Normal.y < 0.000001f && HitDim.Dim[i].Normal.y > -0.0000001f)
		{
			if (HitDim.Dim[i].Position[0].y > m_pos.y + 1.0f ||
				HitDim.Dim[i].Position[1].y > m_pos.y + 1.0f ||
				HitDim.Dim[i].Position[2].y > m_pos.y + 1.0f)
			{
				//�|���S���̐����񋓂ł�����E���ɒB���Ă��Ȃ�������|���S����z��ɒǉ�
				if (m_WallNum < PLAYER_MAX_HITCOLL)
				{
					//�|���S���̍\���̂̃A�h���X��ǃ|���S���|�C���^�z��ɕۑ�����
					m_Wall[m_WallNum] = &HitDim.Dim[i];

					//�ǃ|���S���̐������Z����
					m_WallNum++;
				}
			}
		}
	}

	//�ǃ|���S���Ɠ����蔻�菈��
	if (m_WallNum != 0)
	{
		//�ǂɓ����������ǂ����̃t���O�͏�����Ԃł́u�������Ă��Ȃ��v�ɂ��Ă���
		m_HitFlag = false;

		//�ړ��������ǂ����ŏ����𕪊�
		if (m_moveflag == true)
		{
			//�ǃ|���S���̐������J��Ԃ�
			for (int i = 0; i < m_WallNum; i++)
			{
				//i�Ԗڂ̕ǃ|���S���̃A�h���X��ǃ|���S���|�C���^�z�񂩂�擾
				m_Poly = m_Wall[i];

				//�|���S���ƃv���C���[���������Ă��Ȃ������玟�̃J�E���g��
				if (HitCheck_Capsule_Triangle(m_mapHitColl, VAdd(m_mapHitColl, VGet(0.0f, m_len, 0.0f)), m_capsuleRadius, m_Poly->Position[0], m_Poly->Position[1], m_Poly->Position[2]) == false) continue;

				//�����ɂ�����|���S���ƃv���C���[���������Ă���Ƃ������ƂȂ̂ŁA�|���S���ɓ��������t���O�𗧂Ă�
				m_HitFlag = true;

				//�V���Ȉړ����W�ŕǃ|���S���Ɠ������Ă��Ȃ����ǂ����𔻒肷��
				for (j = 0; j < m_WallNum; j++)
				{
					//j�Ԗڂ̕ǃ|���S���Ɠ������Ă��Ȃ����ǂ����𔻒肷��
					m_Poly = m_Wall[j];

					//�������Ă����烋�[�v���甲����
					if (HitCheck_Capsule_Triangle(m_mapHitColl, VAdd(m_mapHitColl, VGet(0.0f, m_len, 0.0f)), m_capsuleRadius, m_Poly->Position[0], m_Poly->Position[1], m_Poly->Position[2]) == true) break;
				}

				//j��m_WallNum�������ꍇ�͂ǂ̃|���S���Ƃ�������Ȃ������Ƃ������ƂȂ̂�
				//�ǂɓ��������t���O��|���������Ń��[�v���甲����
				if (j == m_WallNum)
				{
					m_HitFlag = false;
					break;
				}

			}
		}
		else
		{
			//�ړ����Ă��Ȃ��ꍇ�̏���

			//�ǃ|���S���̐������J��Ԃ�
			for (int i = 0; i < m_WallNum; i++)
			{
				//i�Ԗڂ̕ǃ|���S���̃A�h���X��ǃ|���S���|�C���^�z�񂩂�擾
				m_Poly = m_Wall[i];

				//�|���S���ɓ������Ă����瓖�������t���O�𗧂Ă���Ń��[�v���甲����
				if (HitCheck_Capsule_Triangle(m_mapHitColl, VAdd(m_mapHitColl, VGet(0.0f, m_len, 0.0f)), m_capsuleRadius, m_Poly->Position[0], m_Poly->Position[1], m_Poly->Position[2]) == true)
				{
					m_HitFlag = true;
					break;
				}

			}
		}

		//�ǂɓ������Ă�����ǂ��牟���o���������s��
		if (m_HitFlag == true)
		{
			//�ǂ���̉����o�����������݂�ő吔�����J��Ԃ�
			for (int i = 0; i < PLAYER_MAX_HITCOLL; i++)
			{
				//�ǃ|���S���̐������J��Ԃ�
				for (int k = 0; k < m_WallNum; k++)
				{
					//j�Ԗڂ̕ǃ|���S���̃A�h���X��ǃ|���S���|�C���^�z�񂩂�擾
					m_Poly = m_Wall[k];

					//�v���C���[�Ɠ������Ă��邩����
					if (HitCheck_Capsule_Triangle(m_mapHitColl, VAdd(m_mapHitColl, VGet(0.0f, m_len, 0.0f)), m_capsuleRadius, m_Poly->Position[0], m_Poly->Position[1], m_Poly->Position[2]) == false) continue;

					//�������Ă�����K�苗�����v���C���[��ǂ̖@�������Ɉړ�������
					m_pos = VAdd(m_pos, VScale(m_Poly->Normal, 1.0f));

					//�ړ�������ŕǃ|���S���ƐڐG���Ă��邩�ǂ����𔻒�
					for (j = 0; j < m_WallNum; j++)
					{
						//�������Ă����烋�[�v�𔲂���
						m_Poly = m_Wall[j];
						if (HitCheck_Capsule_Triangle(m_mapHitColl, VAdd(m_mapHitColl, VGet(0.0f, m_len, 0.0f)), m_capsuleRadius, m_Poly->Position[0], m_Poly->Position[1], m_Poly->Position[2]) == true) break;

					}

					//���ׂẴ|���S���Ɠ������Ă��Ȃ������烋�[�v�I��
					if (j == m_WallNum) break;
				}

				//i��m_WallNum�ł͂Ȃ��ꍇ�͑S���̃|���S���ŉ����o�������݂�O�ɂ��ׂĂ̕ǃ|���S���ƐڐG���Ȃ��Ȃ����Ƃ������ƂȂ̂Ń��[�v���甲����
				if (i != m_WallNum) break;
			}
		}
	}

	//���o�����v���C���[�̎��͂̃|���S�������������
	MV1CollResultPolyDimTerminate(HitDim);
}

void BossEnemy::Draw()
{
	//�����x�N�g��
	Vec3 vec = m_vec.GetNormalized() * m_len * 0.5f;

	Pos3 pos1 = m_colPos + vec;
	Pos3 pos2 = m_colPos - vec;

#if false

	//�G�������Ă��鎞�͕`��
	if (m_hp > 0.0f)
	{
		DrawCapsule3D(pos1.GetVector(), pos2.GetVector(), m_capsuleRadius, 16, m_color, 0, false);

		//�U���͈͕̔`��
		DrawSphere3D(m_colPos.GetVector(), m_sphereRadius, 16, m_distanceColor, m_distanceColor, false);

		//�U������`��
		DrawSphere3D(m_colBossAttackPos1.GetVector(), m_bossAttackRadius1, 16, 0xffffff, 0xffffff, false);
		DrawSphere3D(m_colBossAttackPos2.GetVector(), m_bossAttackRadius2, 16, 0xffffff, 0xffffff, false);
		DrawSphere3D(m_colBossAttackPos3.GetVector(), m_bossAttackRadius3, 16, 0xffffff, 0xffffff, false);
	}

#endif
#if false

	DrawFormatString(0, 120, 0xffffff, "m_moveAttack1 : %d", m_bossAttack1);
	DrawFormatString(0, 180, 0xffffff, "m_moveAttack1 : %d", m_bossAttack2);
	DrawFormatString(0, 240, 0xffffff, "m_moveAttack1 : %d", m_bossAttack3);
	DrawFormatString(0, 300, 0xffffff, "m_BossAttack : %d", m_bossAttack);
	DrawFormatString(0, 360, 0xffffff, "m_PlayTime : %f", m_playTime);
	//DrawFormatString(0, 400, 0xffffff, "m_Attack : %f", m_attack);

	
#endif

#if true
	//�v���C���[���{�X��荶�ɂ����-�������邵�A�����[�P���炢�łP�A�j���[�V����
	//�v���C���[���{�X���E�ɂ����+�������邵�A����+1���炢��1�A�j���[�V����
	DrawFormatString(0, 320, 0xffffff, "m_angle : %f", m_angle);
	DrawFormatString(0, 380, 0xffffff, "correctionAngle : %f", correctionAngle);
	DrawFormatString(0, 440, 0xffffff, "right : %d", m_turnRight);
	DrawFormatString(0, 500, 0xffffff, "left : %d", m_turnLeft);
	DrawFormatString(100, 560, 0xffffff, "blend : %f", m_bossAnimBlend);
	DrawFormatString(100, 620, 0xffffff, "pattern : %d", m_bossMoveAttackPattern);
#endif

#if false
	DrawFormatString(100, 500, 0xffffff, "anim0 : %d", m_bossAnimOne[0]);
	DrawFormatString(100, 560, 0xffffff, "anim1 : %d", m_bossAnimOne[1]);
	DrawFormatString(100, 620, 0xffffff, "anim2 : %d", m_bossAnimOne[2]);
	DrawFormatString(100, 680, 0xffffff, "anim3 : %d", m_bossAnimOne[3]);
	DrawFormatString(100, 740, 0xffffff, "anim4 : %d", m_bossAnimOne[4]);
	DrawFormatString(100, 800, 0xffffff, "anim5 : %d", m_bossAnimOne[5]);
	DrawFormatString(100, 860, 0xffffff, "anim6 : %d", m_bossAnimOne[6]);
	DrawFormatString(100, 920, 0xffffff, "anim7 : %d", m_bossAnimOne[7]);
	DrawFormatString(100, 980, 0xffffff, "anim8 : %d", m_bossAnimOne[8]);

#endif

	//3D���f���|�W�V�����ݒ�
	MV1SetPosition(m_bossModelHandle, m_pos);

	//3D���f���`��
	MV1DrawModel(m_bossModelHandle);

	//3D���f���̉�]�n���Z�b�g����
	MV1SetRotationXYZ(m_bossModelHandle, VGet(0.0f, m_angle, 0.0f));

	//�U�����ꂽ���̃G�t�F�N�g�̃|�W�V����
	SetPosPlayingEffekseer3DEffect(m_effectHit, m_pos.x, m_pos.y + 70.0f, m_pos.z);

	//�G�t�F�N�g�̕`��
	//effect->Draw();
}

void BossEnemy::End()
{
	//���������
	effect->End();
}

bool BossEnemy::isSphereHit(const SphereCol& col, float damage, Effect& ef)
{
	bool isHit = m_capsuleCol.IsHitSphere(col);

	//�_���[�W���󂯂�����
	if (isHit)
	{
		m_color = 0xffff00;

		//�_���[�W����񂾂��^����
		if (m_damageReceived == false)
		{
			m_effectHit = PlayEffekseer3DEffect(ef.GetHitEffect());

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

	MATRIX mts = MGetRotY(D2R(m_bounceAngle));

	//�v���C���[�Ɠ���������
	if (isHit)
	{
		m_color = 0xffff00;

		m_outPush = VScale(vec, 0.1f);

		m_outPush = VTransform(m_outPush, mts);
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
	bool isHit = m_bossColDistance.IsHitCapsule(col);

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
