#pragma once
#include "BGM�ESE/SEManager.h"
#include "DxLib.h"
#include<memory>

class SelectManager;

class Setting
{
public:
	Setting();
	virtual ~Setting();

	void Init();
	void Update();
	void MenuUpdate();
	void Draw();
	void BrightColorDraw(int select, int now, int other1, int other2, int other3, int other4, int black, int white);
	void VolumeColorDraw(int select, int now, int other1, int other2, int other3, int other4, int volume);
	void SettingDraw(int volume);
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
	XINPUT_STATE m_xpad;  //�p�b�h����
	int m_select[3];    //�I��p�̕ϐ�
	int m_menuSelect[3];    //���j���[�I��
	int m_volumeSelect[5];   //���ʂ̑I��ϐ� 
	int m_blackPal;
	int m_whitePal;
	int m_button;    //���������Ԃ𓾂�
	int m_thumb;     //���������Ԃ𓾂�
	int m_waitTime;    //���͂�҂��߂̎���
	int m_brightnessColor;    //���邳�̐F
	int m_bgmColor;          //���ʂ̐F
	int m_returnColor;       //�߂�̐F
	int m_brightColor[5];    //���邳�I���̐F
	int m_volumeColor[5];    //���ʑI���̐F
	int m_menuColor[3];      //���j���[�̐F
	bool m_one;      //�P������
	bool m_settingScene;    //�ݒ肷�邽�߂̉�ʂ��Ăԕϐ�
	bool m_brightness;      //���邳�ݒ�
	bool m_volume;          //���ʐݒ�
	int m_volumeSize;         //����
	bool m_equipmentMenu;     //�������j���[
	bool m_returnMenu;        //�߂郁�j���[
	bool m_titleMenu;         //�^�C�g�����j���[

	//�X�}�[�g�|�C���^
	std::shared_ptr<SEManager> se = std::make_shared<SEManager>();
	std::shared_ptr<SelectManager> pselect = std::make_shared<SelectManager>();
};

