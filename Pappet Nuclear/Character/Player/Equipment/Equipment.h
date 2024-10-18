#pragma once
#include "UI/UIBase.h"

/// <summary>
/// �������Ǘ�����N���X
/// </summary>
class Equipment : public UIBase
{
public:
	//�R���X�g���N�^
	Equipment();

	//�f�X�g���N�^
	virtual ~Equipment();

	//����������
	void Init();

	//�X�V����
	void Update();

	//�E��̑�������
	void RightUpdate();

	//����̑�������
	void LeftUpdate();

	//�`�揈��
	void Draw();

	//�E��̑����`�揈��
	void RightDraw();

	//����̑����`�揈��
	void LeftDraw();

	//�I������
	void End();


	bool GetEquipment() { return m_equipmentLeave; }
	bool GetRightEquipment() { return m_rightEquipmentOpen; }
	bool GetLeftEquipment() { return m_leftEquipmentOpen; }
	bool SetRightEquipment(bool right) { return m_rightEquipmentOpen = right; }

	bool GetRightFist() { return m_equipmentRightFist; }         //�f�葕��
	bool GetLeftFist() { return m_equipmentLeftFist; }           //�f�葕��
	bool GetSword() { return m_equipmentSword; }       //������
	bool GetShield() { return m_equipmentShield; }     //������


private:
	XINPUT_STATE m_xpad;  //�p�b�h����
	bool m_equipmentLeave;     //�����ʂւ̐؂�ւ����f
	bool m_rightEquipmentOpen;      //�E��̕���ύX��ʂ��J������
	bool m_leftEquipmentOpen;       //����̕���ύX��ʂ��J������
	bool m_equipmentRightFist;           //�E�̌���������
	bool m_equipmentLeftFist;            //���̌���������
	bool m_equipmentSword;           //����������
	bool m_equipmentShield;          //����������
	int m_equipmentSelect[2];    //����I��ϐ�
	int m_rightItem[2];          //�E��̕��헓
	int m_leftItem[2];           //����̕��헓
	int m_rightEquipmentSelectY;      //�I�����Ă��鏊�ɔ����ړ�
	int m_leftEquipmentSelectY;       //�I�����Ă��鏊�ɔ����ړ�
	int m_waitTime;              //��������
	int m_rightEquipmentBoxColor;    //�����̔��̐F
	int m_leftEquipmentBoxColor;     //�����̔��̐F
	int m_button;                   //���͕ۑ��ϐ�
	int m_one;                      //���̓��͂��󂯎��
};

