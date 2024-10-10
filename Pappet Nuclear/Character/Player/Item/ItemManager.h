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

	//列挙型
	typedef enum
	{
		SmallCore,       //小さいコア
		MediumCore,      //中型のコア
		Rubbish          //ゴミ
	}Item;
};

