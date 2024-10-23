#pragma once
#include "DxLib.h"
#include "Library/MyLibrary.h"
#include "EnemyBase.h"

/// <summary>
/// 雑魚敵（１）
/// </summary>
class EnemyOne : public EnemyBase
{
public:
	//コンストラクタ
	EnemyOne();
	//デストラクタ
	virtual ~EnemyOne();

	//初期化
	void Init(std::shared_ptr<MyLibrary::Physics> physics) override;
	//更新
	void Update(MyLibrary::LibVec3 playerPos, bool isChase);
	//描画
	void Draw();
};

