#pragma once
#include "BGM・SE/SEManager.h"
#include "DxLib.h"
#include<memory>

class Setting
{
public:
	Setting();
	virtual ~Setting();

	void Init();
	void Update();
	void MenuUpdate();
	void Draw();
	void SettingDraw();
	void MenuDraw();
	void End();

	int MyLoadGraph(const char* FileName, int XSize, int YSize);
	int GetVolume() { return m_volumeSize; }

	bool GetSettingScene() { return m_settingScene; }
	bool SetSettingScene(bool scene) { return m_settingScene = scene; }

	bool GetEquipment() { return m_equipmentMenu; }
	bool SetEquipment(bool re) { return m_equipmentMenu = re; }
	bool GetReturn() { return m_returnMenu; }
	bool SetReturn(bool re) { return m_returnMenu = re; }
	bool GetTitle() { return m_titleMenu; }

private:
	int m_black;
	int m_white;
	int m_back;
	XINPUT_STATE m_xpad;  //パッド入力
	int m_select[3];    //選択用の変数
	int m_menuSelect[3];    //メニュー選択
	int m_brightSelect[5];   //明るさの選択変数
	int m_volumeSelect[5];   //音量の選択変数 
	int m_blackPal;
	int m_whitePal;
	int m_button;    //押した時間を得る
	int m_thumb;     //押した時間を得る
	int m_waitTime;    //入力を待つための時間
	int m_brightnessColor;    //明るさの色
	int m_bgmColor;          //音量の色
	int m_returnColor;       //戻るの色
	int m_brightColor[5];    //明るさ選択の色
	int m_volumeColor[5];    //音量選択の色
	int m_menuColor[3];      //メニューの色
	bool m_one;      //単発入力
	bool m_settingScene;    //設定するための画面を呼ぶ変数
	bool m_brightness;      //明るさ設定
	bool m_volume;          //音量設定
	int m_volumeSize;         //音量
	bool m_equipmentMenu;     //装備メニュー
	bool m_returnMenu;        //戻るメニュー
	bool m_titleMenu;         //タイトルメニュー

	std::shared_ptr<SEManager> se = std::make_shared<SEManager>();
};

