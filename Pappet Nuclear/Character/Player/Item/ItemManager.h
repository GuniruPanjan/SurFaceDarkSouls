#pragma once
class ItemManager
{
public:
	ItemManager();
	virtual ~ItemManager();

	void Init();
	void Update();
	void Draw();
	void End();

private:

	//�񋓌^
	typedef enum
	{
		SmallCore,       //�������R�A
		MediumCore,      //���^�̃R�A
		Rubbish          //�S�~
	}Item;
};

