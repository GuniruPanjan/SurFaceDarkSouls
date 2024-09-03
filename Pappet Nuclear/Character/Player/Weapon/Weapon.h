#pragma once
#include "DxLib.h"

class Weapon
{
public:
	Weapon();
	virtual ~Weapon();

	void Init();
	void Update(MATRIX& matrix);
	void Draw(VECTOR& vector);
	void End();

private:
	int m_weaponHandle;   //武器の保存変数
	float m_weaponSize;     //武器のサイズ変更
	int m_weaponFrameIndex;      //モデルのインデックス
	VECTOR m_weaponPos;        //モデルのポジション設定
	VECTOR m_weaponFramePosition;      //アタッチするモデルのフレーム座標
	MATRIX m_transMatrix;
	MATRIX m_mixMatrix;      //行列合成
};

