#pragma once
#include "ObjectBase.h"

/// <summary>
/// 攻撃を受ける当たり判定クラス
/// </summary>
class HitObject : public ObjectBase
{
public:
	//コンストラクタ
	HitObject(float radius, float len, MyLibrary::LibVec3 vec);
	//デストラクタ
	~HitObject();

	//初期化
	void Init(std::shared_ptr<MyLibrary::Physics> physics, MyLibrary::LibVec3 pos, bool isEnemy);
	//更新
	void Update(MyLibrary::LibVec3 pos);

	//当たり判定削除
	void Finalize(std::shared_ptr<MyLibrary::Physics> physics) override;

	//ほかのオブジェクトに当たった時
	void OnTriggerEnter(const std::shared_ptr<Collidable>& collidable) override;

	//当たったオブジェクトの攻撃力を取得
	int GetIsAttackNum();

	//ほかのオブジェクトに当たったどうか
	bool GetIsHit();
private:
	//物理クラスのポインタ
	std::shared_ptr<MyLibrary::Physics> m_pPhysics;

	//最後に当たったオブジェクトの攻撃力
	int m_lastHitObjectAttack;
	//当たったオブジェクトのタグ
	ObjectTag m_hitObjectTag;
	//このクラスの持ち主が敵かどうか
	bool m_isEnemy;
	//ほかのオブジェクトにあたったかどうか
	bool m_isHit;

};

