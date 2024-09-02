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

	CapsuleCol GetCol() const { return m_capsuleCol; }
	SphereCol GetAttackCol1() { return m_colBossAttackSphere1; }
	SphereCol GetAttackCol2() { return m_colBossAttackSphere2; }
	SphereCol GetAttackCol3() { return m_colBossAttackSphere3; }


private:
	bool m_gameClear;        //ƒ{ƒX‚ğ“|‚µ‚½‚çƒQ[ƒ€ƒNƒŠƒA
	bool m_bossDistance;     //ƒ{ƒX‚ª—£‚ê‚Ä‚¢‚½‚Æ‚«‚Ì”»’f
	bool m_bossBattle;       //ƒ{ƒX‚Ì—Õí‘Ô¨”»’è
	bool m_bossMoveAttack;   //ƒ{ƒX‚ÌUŒ‚s“®”»’è
	int m_bossAttack;     //ƒ{ƒX‚ÌUŒ‚ƒpƒ^[ƒ“
	unsigned int m_color = 0xffffff;
	unsigned int m_seachColor = 0xffffff;
	unsigned int m_distanceColor = 0xffffff;
	Pos3 m_colBossAttackPos1;     //UŒ‚‚Ì“–‚½‚è”»’è1
	Pos3 m_colBossAttackPos2;     //UŒ‚‚Ì“–‚½‚è”»’è2
	Pos3 m_colBossAttackPos3;     //UŒ‚‚Ì“–‚½‚è”»’è3
	float m_bossAttackRadius1;     //UŒ‚‚Ì“–‚½‚è”»’è”¼Œa1
	float m_bossAttackRadius2;     //UŒ‚‚Ì“–‚½‚è”»’è”¼Œa2
	float m_bossAttackRadius3;     //UŒ‚‚Ì“–‚½‚è”»’è”¼Œa3
	SphereCol m_colBossAttackSphere1;    //UŒ‚‚Ì“–‚½‚è”»’èCol1
	SphereCol m_colBossAttackSphere2;    //UŒ‚‚Ì“–‚½‚è”»’èCol2  
	SphereCol m_colBossAttackSphere3;    //UŒ‚‚Ì“–‚½‚è”»’èCol3  



	std::shared_ptr<Map> map = std::make_shared<Map>();
};

