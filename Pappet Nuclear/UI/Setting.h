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
	XINPUT_STATE m_xpad;  //パッド入力
	int m_select[2];    //選択用の変数
	int m_black;
	int m_white;
	int m_blackPal;
	int m_whitePal;
	int m_button;    //押した時間を得る
	bool m_one;      //単発入力
};

