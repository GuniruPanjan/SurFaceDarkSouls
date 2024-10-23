#include "LevelUp.h"
#include "Player.h"
#include "Character/Enemy/Enemy.h"

/// <summary>
/// コンストラクタ
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
/// デストラクタ
/// </summary>
LevelUp::~LevelUp()
{
}

/// <summary>
/// 初期化処理
/// </summary>
/// <param name="player">プレイヤーを呼び出す</param>
/// <param name="enemy">エネミーを呼び出す</param>
void LevelUp::Init(Player& player, Enemy& enemy)
{
	//プレイヤーのレベルに代入する
	player.m_levelStatus.sl_hp = m_lHp;
	player.m_levelStatus.sl_stamina = m_lStamina;
	player.m_levelStatus.sl_muscle = m_lMuscle;
	player.m_levelStatus.sl_skill = m_lSkill;
	player.m_levelStatus.sl_all = m_lAll;

	//コアも初期化する
	m_lCore = enemy.GetCore();
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="player">プレイヤーを呼び出す</param>
/// <param name="enemy">エネミーを呼び出す</param>
void LevelUp::Update(Player& player, Enemy& enemy)
{
	//レベルを上げる
	if (m_lCore >= m_lUseCore * m_lAll)
	{


		//上げた分を減らす
		m_lCore = m_lCore - (m_lUseCore * m_lAll);
	}

	//全てのレベルと合わせる
	m_lAll = m_lHp + m_lStamina + m_lMuscle + m_lSkill;
}

/// <summary>
/// プレイヤーが死んだ時の処理
/// </summary>
/// <param name="player">プレイヤーを呼び出す</param>
void LevelUp::PlayerDeath(Player& player)
{
}

/// <summary>
/// 描画処理
/// </summary>
void LevelUp::Draw()
{
}

/// <summary>
/// 終了処理
/// </summary>
void LevelUp::End()
{
}
