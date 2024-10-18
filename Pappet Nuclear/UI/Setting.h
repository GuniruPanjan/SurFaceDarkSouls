#pragma once
#include "BGM�ESE/SEManager.h"
#include "DxLib.h"
#include<memory>

class SelectManager;
class UIBase;

/// <summary>
/// �ݒ菈���p�̃N���X
/// </summary>
class Setting
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Setting();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~Setting();

	/// <summary>
	/// ����������
	/// </summary>
	void Init();

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();

	/// <summary>
	/// ���j���[�̍X�V����
	/// </summary>
	void MenuUpdate();

	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw();

	/// <summary>
    /// �I�𒆂̐F��ς���
    /// </summary>
    /// <param name="select">�񋓌^</param>
    /// <param name="now">�I�����Ă����</param>
    /// <param name="other1">����ȊO�P</param>
    /// <param name="other2">����ȊO�Q</param>
    /// <param name="other3">����ȊO�R</param>
    /// <param name="other4">����ȊO�S</param>
    /// <param name="black">�����摜�̃u�����h��</param>
    /// <param name="white">�����摜�̃u�����h��</param>
	void BrightColorDraw(int select, int now, int other1, int other2, int other3, int other4, int black, int white);

	// <summary>
    /// �I�𒆂̐F��ς���
    /// </summary>
    /// <param name="select">�񋓌^</param>
    /// <param name="now">�I�����Ă����</param>
    /// <param name="other1">����ȊO�P</param>
    /// <param name="other2">����ȊO�Q</param>
    /// <param name="other3">����ȊO�R</param>
    /// <param name="other4">����ȊO�S</param>
    /// <param name="volume">����</param>
	void VolumeColorDraw(int select, int now, int other1, int other2, int other3, int other4, int volume);

	/// <summary>
	/// �ݒ�̕`��
	/// </summary>
	/// <param name="volume">����</param>
	void SettingDraw(int volume);
	
	/// <summary>
	/// ���j���[�`��
	/// </summary>
	void MenuDraw();

	/// <summary>
	/// �I������
	/// </summary>
	void End();

	/// <summary>
	/// ���ʂ��Ƃ�
	/// </summary>
	/// <returns>���ʂ�Ԃ�</returns>
	int GetVolume() { return m_volumeSize; }

	/// <summary>
	/// �ݒ�V�[�����o�����߂̔�����Ƃ�
	/// </summary>
	/// <returns>�����Ԃ�</returns>
	bool GetSettingScene() { return m_settingScene; }

	/// <summary>
	/// �ݒ�V�[�����o�����߂̔�������߂�
	/// </summary>
	/// <param name="scene">������Ƃ�</param>
	/// <returns>���ʂ�Ԃ�</returns>
	bool SetSettingScene(bool scene) { return m_settingScene = scene; }

	/// <summary>
	/// �������J��������Ƃ�
	/// </summary>
	/// <returns>�����Ԃ�</returns>
	bool GetEquipment() { return m_equipmentMenu; }

	/// <summary>
	/// �������J����������߂�
	/// </summary>
	/// <param name="re">������Ƃ�</param>
	/// <returns>���ʂ�Ԃ�</returns>
	bool SetEquipment(bool re) { return m_equipmentMenu = re; }

	/// <summary>
	/// ��ʂɖ߂锻����Ƃ�
	/// </summary>
	/// <returns>�����Ԃ�</returns>
	bool GetReturn() { return m_returnMenu; }

	/// <summary>
	/// ��ʂɖ߂锻������߂�
	/// </summary>
	/// <param name="re">������Ƃ�</param>
	/// <returns>���ʂ�Ԃ�</returns>
	bool SetReturn(bool re) { return m_returnMenu = re; }

	/// <summary>
	/// �^�C�g���ɖ߂锻����Ƃ�
	/// </summary>
	/// <returns>������Ƃ�</returns>
	bool GetTitle() { return m_titleMenu; }

private:
	int m_black;        //�����摜�i�[�ϐ�
	int m_white;        //�����摜�i�[�ϐ�
	int m_back;         //�����摜�i�[�ϐ�
	XINPUT_STATE m_xpad;  //�p�b�h����
	int m_menuSelect[3];    //���j���[�I�� 
	int m_blackPal;      //�����摜�̃A���t�@�l�ۑ�
	int m_whitePal;      //�����摜�̃A���t�@�l�ۑ�
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
	std::shared_ptr<UIBase> ui = std::make_shared<UIBase>();
};

