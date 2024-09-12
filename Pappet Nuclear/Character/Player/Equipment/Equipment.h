#pragma once
#include "UI/UIManager.h"

//struct RightEquipmentItem
//{
//
//	int s_hand = 1;
//	int s_sword = 0;
//
//}RightItem;

class Equipment : public UIManager
{
public:
	Equipment();
	virtual ~Equipment();

	void Init();
	void Update();
	void RightUpdate();
	void Draw();
	void RightDraw();
	void End();

	bool GetEquipment() { return m_equipmentLeave; }
	bool GetRightEquipment() { return m_rightEquipmentOpen; }
	bool SetRightEquipment(bool right) { return m_rightEquipmentOpen = right; }

	bool GetFist() { return m_equipmentFist; }         //素手装備
	bool GetSword() { return m_equipmentSword; }       //剣装備

private:
	XINPUT_STATE m_xpad;  //パッド入力
	bool m_equipmentLeave;     //武器画面への切り替え判断
	bool m_rightEquipmentOpen;      //右手の武器変更画面を開く判定
	bool m_equipmentFist;           //拳装備判定
	bool m_equipmentSword;           //剣装備判定
	int m_equipmentSelect[2];    //武器選択変数
	int m_rightItem[2];          //右手の武器欄
	int m_rightEquipmentSelectY;      //選択している所に箱を移動
	int m_waitTime;              //押す時間
	int m_rightEquipmentBoxColor;    //装備の箱の色
	int m_button;                   //入力保存変数
	int m_one;                      //一回の入力を受け取る
};

