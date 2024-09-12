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

	bool GetFist() { return m_equipmentFist; }         //�f�葕��
	bool GetSword() { return m_equipmentSword; }       //������

private:
	XINPUT_STATE m_xpad;  //�p�b�h����
	bool m_equipmentLeave;     //�����ʂւ̐؂�ւ����f
	bool m_rightEquipmentOpen;      //�E��̕���ύX��ʂ��J������
	bool m_equipmentFist;           //����������
	bool m_equipmentSword;           //����������
	int m_equipmentSelect[2];    //����I��ϐ�
	int m_rightItem[2];          //�E��̕��헓
	int m_rightEquipmentSelectY;      //�I�����Ă��鏊�ɔ����ړ�
	int m_waitTime;              //��������
	int m_rightEquipmentBoxColor;    //�����̔��̐F
	int m_button;                   //���͕ۑ��ϐ�
	int m_one;                      //���̓��͂��󂯎��
};

