#pragma once
#include "DxLib.h"

class Setting
{
public:
	Setting();
	virtual ~Setting();

	void Init();
	void Update();
	void Draw();
	void SettingDraw();
	void End();

	int MyLoadGraph(const char* FileName, int XSize, int YSize);

	bool GetSettingScene() { return m_settingScene; }
	bool SetSettingScene(bool scene) { return m_settingScene = scene; }

private:
	XINPUT_STATE m_xpad;  //パッド入力
	int m_select[3];    //選択用の変数
	int m_black;
	int m_white;
	int m_back; 
	int m_blackPal;
	int m_whitePal;
	int m_button;    //押した時間を得る
	int m_waitTime;    //入力を待つための時間
	bool m_one;      //単発入力
	bool m_settingScene;    //設定するための画面を呼ぶ変数
};

