#include "SelectManager.h"
#include "DxLib.h"

namespace
{
	bool menuOne = false;   //一度だけ行う
	bool itemOne = false;   //一度だけ行う
}

SelectManager::SelectManager():
	NowSelect()
{
}

SelectManager::~SelectManager()
{
}


void SelectManager::Menu_Update(int stick, bool& one, int button, int& decision, int now)
{
	//一度だけ初期化
	if (menuOne == false)
	{
		NowSelect = now;   //現在の選択肢
		decision = 0;

		menuOne = true;
	}

	//上選択or左選択
	if (stick > 0 && one == false)
	{
		//NowSelectがEightだった場合
		if (NowSelect == now)
		{
			NowSelect = (NowSelect = Ten);    //選択肢を一番下にする
		}
		//NowSelectがEight以上だった場合
		else if (NowSelect > now)
		{
			NowSelect = (NowSelect - 1);   //選択肢を一つ上げる
		}
		
		
		one = true;
	}

	//下選択or右選択
	if (stick < 0 && one == false)
	{
		
		//NowSelectがTenだった場合
		if (NowSelect == Ten)
		{
			NowSelect = (NowSelect = now);    //選択肢を一番上にする
		}
		//NowSelectがTen以下だった場合
		else if (NowSelect < SELECT_SIZE)
		{
			NowSelect = (NowSelect + 1);   //選択肢を一つ下げる
		}

		one = true;
	}

	//ボタンが押されたら
	if (button == 1)
	{
		switch (NowSelect)     //現在選択中の状態によって処理を分岐
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

void SelectManager::Draw()
{
#if _DEBUG
	DrawFormatString(100, 100, 0xffffff, "%d", NowSelect);
#endif
}
