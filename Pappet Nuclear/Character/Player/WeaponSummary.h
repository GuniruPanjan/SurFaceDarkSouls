#pragma once
#include "DxLib.h"
#include<memory>

/// <summary>
/// 武器を管理するクラス
/// </summary>
class WeaponSummary
{
public:
	//コンストラクタ
	WeaponSummary();
	//デストラクタ
	virtual ~WeaponSummary();

	//初期化処理
	void Init();

	//右手の装備更新処理
	void RightUpdate(MATRIX mat);

	//左手の装備更新処理
	void LeftUpdate(MATRIX mat);

	//右手の装備の描画処理
	void RightDraw();

	//左手の装備の描画処理
	void LeftDraw();

	//終了処理
	void End();

private:
	int m_weaponHandle;   //武器の保存変数
	float m_weaponSize;     //武器のサイズ変更
	int m_weaponFrameIndex;      //モデルのインデックス
	VECTOR m_weaponFramePosition;      //アタッチするモデルのフレーム座標
	VECTOR m_weaponPosition;           //モデルのポジション
	MATRIX m_transMatrix;
	MATRIX m_weaponMatrixY;    //武器の行列Y
	MATRIX m_weaponMatrixZ;    //武器の行列Z
	MATRIX m_mixMatrix;      //行列合成

	//盾の構造体
	struct WeaponShield
	{
		int m_shieldHandle;    //盾の保存変数
		float m_shieldSize;    //武器のサイズ変更
		int m_shieldFrameIndex;     //モデルのインデックス
		VECTOR m_shieldPos;     //モデルのポジション設定
		VECTOR m_shieldFramePosition;    //アタッチするモデルのフレーム座標
		MATRIX m_transMatrix;
		MATRIX m_weaponMatrixY;    //武器の行列Y
		MATRIX m_weaponMatrixZ;    //武器の行列Z
		MATRIX m_mixMatrix;        //行列合成
	};

	//スマートポインタ
	std::shared_ptr<WeaponShield> pshield = std::make_shared<WeaponShield>();
};

