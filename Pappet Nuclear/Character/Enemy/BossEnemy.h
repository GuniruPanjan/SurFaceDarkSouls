#pragma once
#include "EnemyBase.h"

class BossEnemy : public EnemyBase
{
public:
	BossEnemy();
	virtual ~BossEnemy();

	void Init();
	void Update(Player& player, Map& map);
	void Action(Player& player);
	void Animation(float& time);
	void Draw();
	void End();

	bool isSphereHit(const SphereCol& col, float damage);
	bool isCapsuleHit(const CapsuleCol& col);

	float GetDamage() { return m_attack; }
	bool GameClear() { return m_gameClear; }
	bool GetBattle() { return m_bossBattle; }
	VECTOR GetPos() { return m_pos; }
	float GetPosX() { return m_pos.x; }
	float GetPosY() { return m_pos.y; }
	float GetPosZ() { return m_pos.z; }
	float GetHp() { return m_hp; }

	CapsuleCol GetCol() const { return m_capsuleCol; }
	SphereCol GetAttackCol1() { return m_colBossAttackSphere1; }
	SphereCol GetAttackCol2() { return m_colBossAttackSphere2; }
	SphereCol GetAttackCol3() { return m_colBossAttackSphere3; }


private:
	bool m_gameClear;        //�{�X��|������Q�[���N���A
	bool m_bossDistance;     //�{�X������Ă����Ƃ��̔��f
	bool m_bossBattle;       //�{�X�̗Ր�Ԑ�����
	bool m_bossMoveAttack;   //�{�X�̍U���s������
	bool m_bossMoveAttackPattern;    //�{�X�̃p�^�[��2�̍U������
	bool m_bossAttack1;           //�{�X�̍U��1�̔��f
	bool m_bossAttack2;           //�{�X�̍U��2�̔��f
	bool m_bossAttack3;           //�{�X�̍U��3�̔��f
	int m_bossAttack;     //�{�X�̍U���p�^�[��
	unsigned int m_color = 0xffffff;
	unsigned int m_seachColor = 0xffffff;
	unsigned int m_distanceColor = 0xffffff;
	Pos3 m_colBossAttackPos1;     //�U���̓����蔻��1
	Pos3 m_colBossAttackPos2;     //�U���̓����蔻��2
	Pos3 m_colBossAttackPos3;     //�U���̓����蔻��3
	float m_bossAttackRadius1;     //�U���̓����蔻�蔼�a1
	float m_bossAttackRadius2;     //�U���̓����蔻�蔼�a2
	float m_bossAttackRadius3;     //�U���̓����蔻�蔼�a3
	SphereCol m_colBossAttackSphere1;    //�U���̓����蔻��Col1
	SphereCol m_colBossAttackSphere2;    //�U���̓����蔻��Col2  
	SphereCol m_colBossAttackSphere3;    //�U���̓����蔻��Col3  



	std::shared_ptr<Map> map = std::make_shared<Map>();
};

