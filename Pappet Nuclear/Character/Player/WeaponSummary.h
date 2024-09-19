#pragma once
#include "DxLib.h"
#include<memory>

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

class WeaponSummary
{
public:
	WeaponSummary();
	virtual ~WeaponSummary();

	void Init();
	void RightUpdate(MATRIX mat);
	void LeftUpdate(MATRIX mat);
	void RightDraw();
	void LeftDraw();
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

	//スマートポインタ
	std::shared_ptr<WeaponShield> pshield = std::make_shared<WeaponShield>();
};

