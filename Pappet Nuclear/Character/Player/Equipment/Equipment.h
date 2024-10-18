#pragma once
#include "UI/UIBase.h"

/// <summary>
/// 装備を管理するクラス
/// </summary>
class Equipment : public UIBase
{
public:
	//コンストラクタ
	Equipment();

	//デストラクタ
	virtual ~Equipment();

	//初期化処理
	void Init();

	//更新処理
	void Update();

	//右手の装備処理
	void RightUpdate();

	//左手の装備処理
	void LeftUpdate();

	//描画処理
	void Draw();

	//右手の装備描画処理
	void RightDraw();

	//左手の装備描画処理
	void LeftDraw();

	//終了処理
	void End();


	bool GetEquipment() { return m_equipmentLeave; }
	bool GetRightEquipment() { return m_rightEquipmentOpen; }
	bool GetLeftEquipment() { return m_leftEquipmentOpen; }
	bool SetRightEquipment(bool right) { return m_rightEquipmentOpen = right; }

	bool GetRightFist() { return m_equipmentRightFist; }         //素手装備
	bool GetLeftFist() { return m_equipmentLeftFist; }           //素手装備
	bool GetSword() { return m_equipmentSword; }       //剣装備
	bool GetShield() { return m_equipmentShield; }     //盾装備


private:
	XINPUT_STATE m_xpad;  //パッド入力
	bool m_equipmentLeave;     //武器画面への切り替え判断
	bool m_rightEquipmentOpen;      //右手の武器変更画面を開く判定
	bool m_leftEquipmentOpen;       //左手の武器変更画面を開く判定
	bool m_equipmentRightFist;           //右の拳装備判定
	bool m_equipmentLeftFist;            //左の拳装備判定
	bool m_equipmentSword;           //剣装備判定
	bool m_equipmentShield;          //盾装備判定
	int m_equipmentSelect[2];    //武器選択変数
	int m_rightItem[2];          //右手の武器欄
	int m_leftItem[2];           //左手の武器欄
	int m_rightEquipmentSelectY;      //選択している所に箱を移動
	int m_leftEquipmentSelectY;       //選択している所に箱を移動
	int m_waitTime;              //押す時間
	int m_rightEquipmentBoxColor;    //装備の箱の色
	int m_leftEquipmentBoxColor;     //装備の箱の色
	int m_button;                   //入力保存変数
	int m_one;                      //一回の入力を受け取る
};

