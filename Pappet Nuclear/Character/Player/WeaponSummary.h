#pragma once
#include "DxLib.h"

class WeaponSummary
{
public:
	WeaponSummary();
	virtual ~WeaponSummary();

	void Init();
	void Update(MATRIX mat);
	void Draw(VECTOR& vector);
	void End();

private:
	int m_weaponHandle;   //武器の保存変数
	float m_weaponSize;     //武器のサイズ変更
	int m_weaponFrameIndex;      //モデルのインデックス
	VECTOR m_weaponPos;        //モデルのポジション設定
	VECTOR m_weaponFramePosition;      //アタッチするモデルのフレーム座標
	VECTOR m_weaponPosition;           //モデルのポジション
	MATRIX m_transMatrix;
	MATRIX m_weaponMatrixY;    //武器の行列Y
	MATRIX m_weaponMatrixZ;    //武器の行列Z
	MATRIX m_mixMatrix;      //行列合成
};

