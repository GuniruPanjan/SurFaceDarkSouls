#pragma once
#include "SceneBase.h"
#include "Map/Map.h"
#include<memory>

class SelectManager;

class SceneTitle : public SceneBase
{
public:
	SceneTitle();
	virtual ~SceneTitle();

	virtual void Init();
	virtual std::shared_ptr<SceneBase> Update();
	void SelectBlend(int select, int now, int other1, int other2);
	virtual void Draw();
	virtual void End();

private:
	//Pad���͏����ϐ�
	int m_pad;
	XINPUT_STATE m_xpad;  //�p�b�h����
	int m_start;
	int m_setting;
	int m_end;
	int m_right;
	int m_button;    //���������Ԃ𓾂�
	int m_select[3];    //�I��p�̕ϐ�
	int m_pal[3];      //�u�����h�`��p
	bool m_one;      //�P������
	bool m_blend;    //�u�����h����
	bool m_setButton;    //�ݒ�̔���
	int m_waitTime;      //�҂��߂̎���
	VECTOR m_analog;
	VECTOR m_cameraPos;    //�J�����|�W�V����
	VECTOR m_cameraTarget;     //�J�����̃^�[�Q�b�g�|�W�V����

	//���f���p�ϐ�
	int m_playerHandle;
	int m_anim;
	int m_animation;
	float m_totalAnimationTime;
	float m_playTime;
	VECTOR m_pos;

	
	//�X�}�[�g�|�C���^
	std::shared_ptr<Map> map = std::make_shared<Map>();
	std::shared_ptr<SEManager> se = std::make_shared<SEManager>();
	std::shared_ptr<SelectManager> pselect = std::make_shared<SelectManager>();
};