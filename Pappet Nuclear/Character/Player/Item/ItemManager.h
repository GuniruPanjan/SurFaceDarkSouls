#pragma once
#define ITEM_NUMBER 30

/// <summary>
/// �A�C�e�����Ǘ�����N���X
/// </summary>
class ItemManager
{
private:
	//�A�C�e���̍\����
	struct Item
	{
		int SmallCore = 0;    //���^�̃R�A
		int MediumCore = 0;   //���^�̃R�A
		int Rubbish = 0;      //�S�~
		int BlackSword = 0;   //��������
		int SmallShield = 0;  //��������
	};

public:
	//�R���X�g���N�^
	ItemManager();
	//�f�X�g���N�^
	virtual ~ItemManager();

	//����������
	void Init();

	//�X�V����
	void Update();

	/// <summary>
	/// �A�C�e������ɓ����
	/// </summary>
	/// <param name="array">�z��</param>
	/// <param name="itemNumber">�A�C�e���i���o�[</param>
	/// <param name="item">�A�C�e��</param>
	void ItemGet(int array, int itemNumber, int& item);

	//�`�揈��
	void Draw();

	//�I������
	void End();

	//�A�C�e���̑��݂�Ԃ�
	bool GetItem(int max) { return m_item[max]; }
	//�Ƃ����A�C�e����Ԃ�
	bool GetSetItem(int max) { return m_getItem[max]; }
	//�A�C�e���̑��݂����߂�
	bool SetItem(int max, bool item);
	//�A�C�e�����Ƃ��������f����
	bool SetGetItem(int max, bool item);


private:
	//�A�C�e�������݂��Ă���
	bool m_item[ITEM_NUMBER];
	//�v���C���[���A�C�e�����Ƃ���
	bool m_getItem[ITEM_NUMBER];
	//��񂾂��s��
	bool m_one[ITEM_NUMBER];

	//�\����
	Item s_item;
};

