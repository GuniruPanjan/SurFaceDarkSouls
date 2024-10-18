#include "Enemy.h"

/// <summary>
/// コンストラクタ
/// </summary>
Enemy::Enemy()
{
}

/// <summary>
/// デストラクタ
/// </summary>
Enemy::~Enemy()
{
}

/// <summary>
/// 初期化処理
/// </summary>
/// <param name="max">最大数</param>
void Enemy::Init(int max)
{
	enemy->Init(max);	
}

/// <summary>
/// ボスの初期化処理
/// </summary>
void Enemy::BossInit()
{
	boss->Init();
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="player">プレイヤー呼び出し</param>
/// <param name="map">マップ呼び出し</param>
/// <param name="max">最大数</param>
/// <param name="volume">音量</param>
void Enemy::Update(Player& player, Map& map, int max, int volume)
{
	enemy->Update(player, max, volume);
}

/// <summary>
/// ボスの更新処理
/// </summary>
/// <param name="player">プレイヤー呼び出し</param>
/// <param name="map">マップ呼び出し</param>
/// <param name="volume">音量</param>
void Enemy::BossUpdate(Player& player, Map& map, int volume)
{
	boss->Update(player, map, volume);
}

/// <summary>
/// マップ判定処理
/// </summary>
/// <param name="map">マップ呼び出し</param>
/// <param name="max">最大数</param>
void Enemy::MapHitWenemy(Map& map, int max)
{
	enemy->HitMap(map, max);
}

/// <summary>
/// マップ呼び出し
/// </summary>
/// <param name="map">マップ呼び出し</param>
void Enemy::MapHitBoss(Map& map)
{
	boss->MapHit(map);
}

/// <summary>
/// 描画処理
/// </summary>
/// <param name="max">最大数</param>
void Enemy::Draw(int max)
{
	enemy->Draw(max);
}

/// <summary>
/// ボスの描画処理
/// </summary>
void Enemy::BossDraw()
{
	boss->Draw();
}

/// <summary>
/// 終了処理
/// </summary>
/// <param name="max">最大数</param>
void Enemy::End(int max)
{
	for (int i = 0; i < max; i++)
	{
		enemy->End(i);
	}
	

	boss->End();
}

//エネミーの攻撃所得
SphereCol Enemy::GetAttackCol(int max)
{
	return enemy->GetAttackCol(max);
	
}
