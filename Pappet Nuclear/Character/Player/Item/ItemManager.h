#pragma once
#define ITEM_NUMBER 30

class ItemManager
{
public:
	ItemManager();
	virtual ~ItemManager();

	void Init();
	void Update();
	void Draw();
	void End();

	bool GetItem(int max) { return m_item[max]; }
	bool SetItem(int max, bool item) { return m_item[max] = item; }

private:

	bool m_item[ITEM_NUMBER];

	//�񋓌^
	typedef enum
	{
		SmallCore,       //�������R�A
		MediumCore,      //���^�̃R�A
		Rubbish          //�S�~
	}Item;
};

