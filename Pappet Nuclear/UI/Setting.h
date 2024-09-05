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
	XINPUT_STATE m_xpad;  //�p�b�h����
	int m_select[3];    //�I��p�̕ϐ�
	int m_black;
	int m_white;
	int m_back; 
	int m_blackPal;
	int m_whitePal;
	int m_button;    //���������Ԃ𓾂�
	int m_waitTime;    //���͂�҂��߂̎���
	int m_brightnessColor;    //���邳�̐F
	int m_bgmColor;          //���ʂ̐F
	int m_returnColor;       //�߂�̐F
	bool m_one;      //�P������
	bool m_settingScene;    //�ݒ肷�邽�߂̉�ʂ��Ăԕϐ�
};

