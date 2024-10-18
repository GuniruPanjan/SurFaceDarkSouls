#include "SelectManager.h"
#include "DxLib.h"

namespace
{
	bool menuOne = false;   //��x�����s��
	bool itemOne = false;   //��x�����s��
}

/// <summary>
/// �R���X�g���N�^
/// </summary>
SelectManager::SelectManager():
	NowSelect()
{
}

/// <summary>
///�f�X�g���N�^
/// </summary>
SelectManager::~SelectManager()
{
}

/// <summary>
/// ���j���[�Ȃǂ̃Z���N�g
/// </summary>
/// <param name="stick">�X�e�B�b�N����</param>
/// <param name="one">��񂾂��s��</param>
/// <param name="button">�{�^������</param>
/// <param name="decision">���肵���Ƃ��ɕԂ��ϐ�</param>
/// <param name="now">�I���̐�</param>
void SelectManager::Menu_Update(int stick, bool& one, int button, int& decision, int now)
{
	//��x����������
	if (menuOne == false)
	{
		NowSelect = now;   //���݂̑I����
		decision = 0;

		menuOne = true;
	}

	//��I��or���I��
	if (stick > 0 && one == false)
	{
		//NowSelect��Now�������ꍇ
		if (NowSelect == now)
		{
			NowSelect = (NowSelect = Ten);    //�I��������ԉ��ɂ���
		}
		//NowSelect��Now�ȏゾ�����ꍇ
		else if (NowSelect > now)
		{
			NowSelect = (NowSelect - 1);   //�I��������グ��
		}
		
		
		one = true;
	}

	//���I��or�E�I��
	if (stick < 0 && one == false)
	{
		
		//NowSelect��Ten�������ꍇ
		if (NowSelect == Ten)
		{
			NowSelect = (NowSelect = now);    //�I��������ԏ�ɂ���
		}
		//NowSelect��Ten�ȉ��������ꍇ
		else if (NowSelect < SELECT_SIZE)
		{
			NowSelect = (NowSelect + 1);   //�I�������������
		}

		one = true;
	}

	//�{�^���������ꂽ��
	if (button == 1)
	{
		switch (NowSelect)     //���ݑI�𒆂̏�Ԃɂ���ď����𕪊�
		{
		case One:
			decision = 1;
			menuOne = false;
			break;
		case Two:
			decision = 2;
			menuOne = false;
			break;
		case Three:
			decision = 3;
			menuOne = false;
			break;
		case Four:
			decision = 4;
			menuOne = false;
			break;
		case Five:
			decision = 5;
			menuOne = false;
			break;
		case Six:
			decision = 6;
			menuOne = false;
			break;
		case Seven:
			decision = 7;
			menuOne = false;
			break;
		case Eight:
			decision = 8;
			menuOne = false;
			break;
		case Nine:
			decision = 9;
			menuOne = false;
			break;
		case Ten:
			decision = 10;
			menuOne = false;
			break;
		}
	}
	
}

void SelectManager::Item_Update()
{
}

/// <summary>
/// �`�揈��
/// </summary>
void SelectManager::Draw()
{
#if _DEBUG
	DrawFormatString(100, 100, 0xffffff, "%d", NowSelect);
#endif
}
