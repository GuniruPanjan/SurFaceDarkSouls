#pragma once

//ゲームオブジェクトのタグ
enum class ObjectTag
{
	Player,               //プレイヤー
	Enemy,                //エネミー(まとめ)
	PlayerAttackSphere,   //プレイヤーの攻撃
	EnemyAttackSphere,    //エネミーの攻撃
	SearchSphere,         //エネミーの索敵
	ItemSphere,           //アイテムの所得範囲
	RestSphere,           //休息できる範囲
	BossEnterRect         //ボス部屋の入口
};
