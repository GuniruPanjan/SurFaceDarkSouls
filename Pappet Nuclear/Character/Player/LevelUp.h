#pragma once

class Player;
class Enemy;

/// <summary>
/// レベル関係を管理するクラス
/// </summary>
class LevelUp
{
public:
	//コンストラクタ
	LevelUp();
	//デストラクタ
	virtual ~LevelUp();

	//初期化処理
	void Init(Player& player, Enemy& enemy);
	//レベルを上げる更新処理
	void Update(Player& player, Enemy& enemy);
	//プレイヤーが死んだ時の処理
	void PlayerDeath(Player& player);
	//ステータスを描画する
	void Draw();
	//終了処理
	void End();

private:
	int m_lHp;        //体力レベル 
	int m_lStamina;   //スタミナレベル
	int m_lMuscle;    //筋力レベル
	int m_lSkill;     //技量レベル
	int m_lAll;       //すべてのレベル
	int m_lCore;      //レベル上げに使うコアまとめ
	int m_lUseCore;   //レベル上げに使うコア
};

