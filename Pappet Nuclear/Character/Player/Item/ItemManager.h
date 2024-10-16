#pragma once
#define ITEM_NUMBER 30

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
	ItemManager();
	virtual ~ItemManager();

	void Init();
	void Update();
	void ItemGet(int array, int itemNumber, int& item);
	void Draw();
	void End();

	bool GetItem(int max) { return m_item[max]; }
	bool GetSetItem(int max) { return m_getItem[max]; }
	bool SetItem(int max, bool item);
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

