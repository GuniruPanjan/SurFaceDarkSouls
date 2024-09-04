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
	void End();

private:
	XINPUT_STATE m_xpad;  //�p�b�h����
	int m_select[2];    //�I��p�̕ϐ�
	int m_black;
	int m_white;
	int m_blackPal;
	int m_whitePal;
	int m_button;    //���������Ԃ𓾂�
	bool m_one;      //�P������
};

