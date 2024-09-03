#pragma once
#include "SceneBase.h"
#define SCREEN_W         640       //画像の横幅
#define SCREEN_H         480       //画像の立幅
#define DOWN_SCALE       8         //ガウスフィルタを掛ける画像が画面のサイズの何分の1か
#define DOWN_SCALE_SCREEN_W   (SCREEN_W / DOWN_SCALE)     //ガウスフィルタを掛ける画像の横幅
#define DOWN_SCALE_SCREEN_H   (SCREEN_H / DOWN_SCALE)     //ガウスフィルタを掛ける立幅


class SceneTitle : public SceneBase
{
public:
	SceneTitle();
	virtual ~SceneTitle();

	virtual void Init();
	virtual std::shared_ptr<SceneBase> Update();
	virtual void Draw();
	virtual void End();

private:
	//Pad入力所得変数
	int m_pad;

	int ColorScreeen = 0;  //普通の描画結果を書き込むスクリーン
	int HighBringhtScreen = 0;  //普通の描画結果から高輝度部分を抜き出した結果を書き込むスクリーン
	int DownScaleScreen = 0;    //高輝度部分を縮小した結果を書き込むスクリーン
	int GaussScreen = 0;    //縮小画像をガウスフィルタでぼかした結果を書き込むスクリーン

};