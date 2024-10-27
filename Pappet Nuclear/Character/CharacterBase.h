#pragma once
#include "DxLib.h"
#include "BGM�ESE/SEManager.h"
#include "Col/CapsuleCol.h"
#include "Col/SphereCol.h"
#include "Col/RectCol.h"
#include "Singleton/HandleManager.h"
#include "Effect/Effect.h"
#include "Animation/BlendAnimation.h"
#include "Library/MyLibrary.h"
#include "Object/AttackObject.h"
#include "Object/HitObject.h"
#include <memory>
#include <map>
#include <string>

//���������̃A�j���[�V����
#define  ANIMATION   30
#define D2R(deg) ((deg)*DX_PI_F/180.0f)
#define PLAYER_MAX_HITCOLL  500    //��������R���W�����|���S���̍ő吔
#define ENEMY_NOW 5  //�G�̔z��ŏo����

class Map;   //�}�b�v�N���X
class ItemManager;    //�A�C�e���}�l�[�W���[�N���X

/// <summary>
/// �L�����N�^�[�̊��N���X
/// </summary>
class CharacterBase : public MyLibrary::Collidable
{
public:
	//�X�e�[�^�X�̍\����
	struct Status
	{
		float s_hp;       //�̗�
		float s_stamina;  //�X�^�~�i
		float s_attack;   //�U����
		int s_muscle;     //�ؗ�
		int s_skill;      //�Z��
		float s_defense;  //�h���
		float s_speed;    //���x
		int s_core;       //���Ƃ��R�A
	};

	//�R���X�g���N�^
	//CharacterBase() :
	//	m_hp(0.0f),
	//	m_attack(0.0f),
	//	m_handle(-1),
	//	m_modelSize(0.0f),
	//	m_angle(0.0f),
	//	m_speed(0.0f),
	//	m_bounceDis(0.0f),
	//	m_death(false),
	//	m_oneInit(false),
	//	m_posX(0.0f),
	//	m_posY(0.0f),
	//	m_posZ(0.0f),
	//	m_moveflag(false),
	//	m_moveAttack(false),
	//	m_moveAttackEnd(true),
	//	m_damageReceived(false),
	//	m_attackNumber(0),
	//	m_playTime(0.0f),
	//	m_animStand(-1),
	//	m_animWalk(-1),
	//	m_animRun(-1),
	//	m_animRoll(-1),
	//	m_animHit(-1),
	//	m_animDeath(-1),
	//	m_animAttack1(-1),
	//	m_animAttack2(-1),
	//	m_animAttack3(-1),
	//	m_len(0.0f),
	//	m_capsuleRadius(0.0f),
	//	m_sphereRadius(0.0f),
	//	m_move(VGet(0.0f, 0.0f, 0.0f)),
	//	m_pos(VGet(m_posX, m_posY, m_posZ)),
	//	m_drawPos(VGet(0.0f, 0.0f, 0.0f)),
	//	m_prevPos(VGet(0.0f, 0.0f, 0.0f)),
	//	m_nowPos(VGet(0.0f, 0.0f, 0.0f)),
	//	m_moveVector(VGet(0.0f, 0.0f, 0.0f)),
	//	m_mapHitColl(VGet(0.0f,0.0f,0.0f)),
	//	m_HitFlag(false),
	//	m_WallNum(0),
	//	m_FloorNum(0),
	//	m_HitDimNum(0),
	//	m_effectActivation(false),
	//	m_playerDif(VGet(0.0f,0.0f,0.0f)),
	//	m_shieldDif(VGet(0.0f,0.0f,0.0f)),
	//	m_animBlend(1.0f),
	//	m_animBlendOne(false),
	//	HitDim(),
	//	m_Wall(),
	//	m_Floor(),
	//	m_Poly()
	//{
	//	for (int i = 0; i < ANIMATION; i++)
	//	{
	//		m_animation[i] = -1;
	//		m_totalAnimTime[i] = 0.0f;
	//		m_animOne[i] = false;
	//	}
	//}

	//�R���X�g���N�^
	CharacterBase(Priority priority, ObjectTag tag);

	//�f�X�g���N�^
	virtual ~CharacterBase();

	//virtual�Ōp������Ăяo��

	//����������
	virtual void Init(){};

	//���f���̒��S���W���v�Z
	virtual void CalculationCenterPos(float modeldefaultSize, float modelSize);

	//�_���[�W��������铖���蔻����쐬
	virtual void InitHitBox(float radius, float len, MyLibrary::LibVec3 vec, bool isEnemy);

	//�U����������铖���蔻����쐬
	virtual void InitAttackBox(float radius, MyLibrary::LibVec3 pos, bool isEnemy);

	//�X�V����
	virtual void Update(){};

	//�Փ˂����Ƃ�
	virtual void OnCollideEnter(const std::shared_ptr<Collidable>& col) = 0;

	//�`�揈��
	virtual void Draw(){};

	//�I������
	virtual void End(){};

protected:
	//�A�j���[�V�����X�V�Ǘ�
	bool UpdateAnimation(int attachNo, float time = 0.0f);
	//�A�j���[�V�����ύX�Ǘ�
	void ChangeAnimation(int animIndex, float changeSpeed = 0.5f);

protected:
	//�����N���X�̃|�C���^
	std::shared_ptr<MyLibrary::Physics> m_pPhysics;
	//���f�����W
	MyLibrary::LibVec3 m_modelPos;
	//���f���̒��S���W
	MyLibrary::LibVec3 m_centerPos;
	//�����蔻����W
	MyLibrary::LibVec3 m_collisionPos;
	//�U���̔�����W
	MyLibrary::LibVec3 m_attackPos;
	//�ړ��x�N�g��
	MyLibrary::LibVec3 m_moveVec;
	
	//�U���̔��a
	float m_attackRadius;

	//�X�e�[�^�X
	Status m_status;

	int m_handle;  //�L�����̃��f���n���h��
	float m_modelSize;  //�L�����̃��f���T�C�Y
	float m_angle;  //�L�����̃A���O��
	float m_bounceDis;    //�L�����������o������
	bool m_death;   //�L�����̎��S����
	bool m_isHit;    //�U�����󂯂����ǂ�������
	bool m_oneInit;     //��񂾂�����������
	float m_posX;  //�L������X���W
	float m_posY;  //�L������Y���W
	float m_posZ;  //�L������Z���W
	bool m_moveflag;  //�L�����������������f����t���O
	bool m_moveAttack;  //�L�������U���������ǂ������f����t���O
	bool m_moveAttackEnd;  //�L�����̍U�����I���������ǂ������f����t���O
	bool m_damageReceived;  //�L�������_���[�W���󂯂����ǂ������f����t���O
	int m_attackNumber;   //�L�����̍U�������i�K�ڂ����f����ϐ�
	float m_playTime;  //�L�����̃A�j���[�V������i�߂鎞��
	float m_animBlend; //�L�����̃A�j���[�V�����u�����h��
	bool m_animBlendOne;   //�L�����̃A�j���[�V�����u�����h���̏���������񂾂��s��
	int m_animStand;  //�L�����̗����Ă���A�j���[�V�����i�[�ϐ�
	int m_animWalk;   //�L�����̕����A�j���[�V�����i�[�ϐ�
	int m_animRun;    //�L�����̑���A�j���[�V�����i�[�ϐ�
	int m_animRoll;   //�L�����̃��[�f�B���O�A�j���[�V�����i�[�ϐ�
	int m_animHit;    //�L�������U�����󂯂����̃A�j���[�V�����i�[�ϐ�
	int m_animDeath;  //�L���������񂾎��̃A�j���[�V�����i�[�ϐ�
	int m_animAttack1;   //�L�����̍U���A�j���[�V�����i�[�ϐ�
	int m_animAttack2;   //�L�����̍U���A�j���[�V�����i�[�ϐ�
	int m_animAttack3;   //�L�����̍U���A�j���[�V�����i�[�ϐ�
	int m_animation[ANIMATION];  //�L�����̃A�j���[�V�����i�[�ϐ�
	float m_totalAnimTime[ANIMATION];  //�L�����̃A�j���[�V�����Đ�����
	bool m_animOne[ANIMATION];   //�L�����̃A�j���[�V����������ׂ̕ϐ�
	VECTOR m_move;  //�L�����̈ړ�
	VECTOR m_pos;  //�L�����̃|�W�V����
	VECTOR m_drawPos;   //�L�����̃��f����`�悷��|�W�V����
	VECTOR m_prevPos;  //�L�����̃A�j���[�V�����ňړ����Ă���t���[���̍��W�擾
	VECTOR m_nowPos;  //�L�����̃A�j���[�V������̍��W���擾����
	VECTOR m_moveVector;  //�L�����̃A�j���[�V�����ł̍��W�ړ��l������

	//�A�j���[�V�����֌W
	std::map<std::string, int> m_animIdx;
	int m_nowAnimIdx;
	int m_nowAnimNo;             //���݂̃A�j���[�V����
	int m_prevAnimNo;            //�ύX�O�̃A�j���[�V����
	float m_animBlendRate;       //�A�j���[�V�����̃u�����h��
	float m_animTime;            //�A�j���[�V�����Đ����x
	bool m_isAnimationFinish;    //�A�j���[�V�������I��������ǂ���

	//�G�t�F�N�g�Ɋւ���ϐ�
	bool m_effectActivation;     //�G�t�F�N�g�𔭓�����

	//�����蔻��p�̃����o�ϐ�
	Pos3 m_colPos; //�����蔻��p�̃����o�ϐ�
	Pos3 m_colAttackPos;  //�U���̓����蔻��p�̃����o�ϐ�
	Pos3 m_colDeathPos;  //���񂾎����������邠���蔻��p�̃����o�ϐ�
	Pos3 m_initializationPos;   //�A�^�b�N�̓����蔻�������������|�W�V����
	Vec3 m_vec;  //�L�����̓����蔻��p�̃x�N�^�[�����o�ϐ�
	Vec3 m_deathVec;  //�L���������񂾎��p�̃x�N�^�[�����o�ϐ�
	float m_len;  //����
	float m_capsuleRadius;  //�J�v�Z���̔��a
	float m_sphereRadius;   //�X�t�B�A�̔��a
	CapsuleCol m_capsuleCol;  //�J�v�Z���̓����蔻��
	SphereCol m_sphereCol;  //�X�t�B�A�̓����蔻��
	VECTOR m_mapHitColl;    //�L�����N�^�[�̃}�b�v�Ƃ̓����蔻��
	VECTOR m_playerDif;      //�v���C���[�Ƃ̋��������߂�
	VECTOR m_shieldDif;     //���Ƃ̋��������߂�

	//�}�b�v�Ƃ̓����蔻��
	bool m_HitFlag;              //�|���S���ɓ����������ǂ������L�����Ă����̂Ɏg���ϐ�
	int m_WallNum;               //�ǃ|���S���Ɣ��f���ꂽ�|���S���̐�
	int m_FloorNum;              //���|���S���Ɣ��f���ꂽ�|���S���̐�
	MV1_COLL_RESULT_POLY_DIM HitDim;      //�L�����̎��͂ɂ���|���S�������o�������ʂ��������铖���蔻�茋�ʍ\����
	int m_HitDimNum;        //HitDim�̗L���Ȕz��v�f��
	MV1_COLL_RESULT_POLY* m_Wall[PLAYER_MAX_HITCOLL];     //�ǃ|���S���Ɣ��f���ꂽ�|���S���̍\���̂̃A�h���X��ۑ����Ă������߂̃|�C���^�z��
	MV1_COLL_RESULT_POLY* m_Floor[PLAYER_MAX_HITCOLL];    //���|���S���Ɣ��f���ꂽ�|���S���̍\���̂̃A�h���X��ۑ����Ă������߂̃|�C���^�z��
	MV1_COLL_RESULT_POLY* m_Poly;  //�|���S���̍\���̂ɃA�N�Z�X���邽�߂ɂ��悤����|�C���^

	//�X�}�[�g�|�C���^
	std::shared_ptr<SEManager> se = std::make_shared<SEManager>();
	std::shared_ptr<HitObject> phit = std::make_shared<HitObject>();
	std::shared_ptr<AttackObject> pattack = std::make_shared<AttackObject>();
};