#pragma once
#include "SceneBase.h"
#include "Map/Map.h"
#include<memory>

class SelectManager;

class SceneTitle : public SceneBase
{
public:
	SceneTitle();
	virtual ~SceneTitle();

	virtual void Init();
	virtual std::shared_ptr<SceneBase> Update();
	void SelectBlend(int select, int now, int other1, int other2);
	virtual void Draw();
	virtual void End();

private:
	//Pad入力所得変数
	int m_pad;
	XINPUT_STATE m_xpad;  //パッド入力
	int m_start;
	int m_setting;
	int m_end;
	int m_right;
	int m_button;    //押した時間を得る
	int m_select[3];    //選択用の変数
	int m_pal[3];      //ブレンド描画用
	bool m_one;      //単発入力
	bool m_blend;    //ブレンド判定
	bool m_setButton;    //設定の判定
	int m_waitTime;      //待つための時間
	VECTOR m_analog;
	VECTOR m_cameraPos;    //カメラポジション
	VECTOR m_cameraTarget;     //カメラのターゲットポジション

	//モデル用変数
	int m_playerHandle;
	int m_anim;
	int m_animation;
	float m_totalAnimationTime;
	float m_playTime;
	VECTOR m_pos;

	
	//スマートポインタ
	std::shared_ptr<Map> map = std::make_shared<Map>();
	std::shared_ptr<SEManager> se = std::make_shared<SEManager>();
	std::shared_ptr<SelectManager> pselect = std::make_shared<SelectManager>();
};