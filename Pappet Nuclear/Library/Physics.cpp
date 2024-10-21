#include "MyLibrary.h"
#include "DxLib.h"
#include <cassert>

namespace
{
	//最大当たり判定ポリゴン数
	constexpr int kMaxColHitPoly = 3000;
	//壁押し出し処理の最大試行回数
	constexpr int kMaxColHitTry = 20;
	//壁押し出し時にスライドさせる距離
	constexpr float kColHitSlideLength = 1.0f;
	//壁ポリゴンか床ポリゴンかを判断するための変数
	constexpr float kWallPolyBorder = 0.4f;
	//壁ポリゴンと判断するための高さ変数
	constexpr float kWallPolyHeight = 5.0f;

	//重力
	constexpr float kGravity = -0.018f;
	//最大重力加速度
	constexpr float kMaxGravity = -2.0f;

	//補正前情報色
	const int kBeforeColor = 0xffffff;
	//補正前予定情報色
	const int kBeforePlanColor = 0x00ff00;
	//補正後情報色
	const int kAfterColor = 0xffff00;
}

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="mapStageCollisionHandle">キャラクターのステージ当たり判定ハンドル</param>
MyLibrary::Physics::Physics(int mapStageCollisionHandle)
{
	m_stageCollisionHandle = mapStageCollisionHandle;
}

/// <summary>
/// 衝突物の登録
/// </summary>
/// <param name="collidable">追加する当たり判定</param>
void MyLibrary::Physics::Entry(std::shared_ptr<Collidable> collidable)
{
	//登録
	bool found = (std::find(m_collidables.begin(), m_collidables.end(), collidable) != m_collidables.end());

	if (!found)
	{
		m_collidables.emplace_back(collidable);
	}
	//既に登録されてたらエラー
	else
	{
		assert(0 && "指定のcollidableは登録済みです");
	}

}

/// <summary>
/// 衝突物の登録削除
/// </summary>
/// <param name="collidable">削除する当たり判定</param>
void MyLibrary::Physics::Exit(std::shared_ptr<Collidable> collidable)
{
	bool found = (std::find(m_collidables.begin(), m_collidables.end(), collidable) != m_collidables.end());
	if (found)
	{
		m_collidables.remove(collidable);
	}
	//登録されていなかったらエラー
	else
	{
		assert(0 && "指定のcollidableが登録されていません");
	}

}

/// <summary>
/// 更新
/// </summary>
void MyLibrary::Physics::Update()
{
	//当たり判定のログを残す
	m_preCollideInfo = m_newCollideInfo;
	m_newCollideInfo.clear();
	m_preTriggerInfo = m_newTriggerInfo;
	m_newTriggerInfo.clear();
	m_onCollideInfo.clear();

	//移動
	for (auto& item : m_collidables)
	{
		auto pos = item->rigidbody.GetPos();
		auto velocity = item->rigidbody.GetVelocity();

		//重力を利用する設定なら、重力を追加
		if (item->rigidbody.GetUseGravity())
		{
			velocity = velocity + LibVec3(0.0f, kGravity, 0.0f);

			//最大重力より大きかったら
			if (velocity.y < kMaxGravity)
			{
				velocity = LibVec3(velocity.x, kMaxGravity, velocity.z);
			}
		}

		auto nextPos = pos + velocity;

		item->rigidbody.SetVelocity(velocity);

		//もともとの情報、予定情報をデバッグ表示
#if _DEBUG

		for (const auto& collider : item->m_colliders)
		{
			auto kind = collider->GetKind();
			if (kind == CollidableData::Kind::Capsule)
			{
				auto capsuleData = dynamic_cast<MyLibrary::CollidableDataCapsule*> (collider.get());
				auto vec = capsuleData->m_vec;
				auto len = capsuleData->m_len;
				auto radius = capsuleData->m_radius;
				MyLibrary::DebugDraw::AddDrawCapsule(pos, vec, radius, len, kBeforeColor);
				MyLibrary::DebugDraw::AddDrawCapsule(nextPos, vec, radius, len, kBeforePlanColor);
			}
			else if (kind == CollidableData::Kind::Sphere)
			{
				auto sphereData = dynamic_cast<MyLibrary::CollidableDataSphere*> (collider.get());
				auto radius = sphereData->m_radius;
				MyLibrary::DebugDraw::AddDrawSphere(pos, radius, kBeforeColor);
				MyLibrary::DebugDraw::AddDrawSphere(pos, radius, kBeforePlanColor);
			}
			else if (kind == CollidableData::Kind::Rect)
			{
				auto rectData = dynamic_cast<MyLibrary::CollidableDataRect*> (collider.get());
				auto size = rectData->m_size;
				MyLibrary::DebugDraw::AddDrawRect(pos, size, kBeforeColor);
				MyLibrary::DebugDraw::AddDrawRect(pos, size, kBeforePlanColor);
			}

		}
#endif
		//予定ポジション設定
		item->rigidbody.SetNextPos(nextPos);

	}

	//当たり判定チェック（nextPos指定）
	CheckCollide();

	for (auto& item : m_collidables)
	{
		if (item->GetTag() == ObjectTag::Player || item->GetTag() == ObjectTag::Enemy ||
			item->GetTag() == ObjectTag::Boss)
		{
			float rad = 0;
			int madelHandle = -1;

			for (auto& col : item->m_colliders)
			{
				rad = dynamic_cast<MyLibrary::CollidableDataCapsule*> (col.get())->m_radius;

				madelHandle = m_stageCollisionHandle;
			}
			m_hitDim = MV1CollCheck_Sphere(madelHandle, -1, item->rigidbody.GetNextPosVECTOR(), rad);
		}
		else
		{
			continue;
		}

		//壁と床の当たり判定を行う
		CheckWallAndFloor(item);
		//壁との当たり判定処理
		FixPositionWithWall(item);
		//床との当たり判定処理
		FixNowPositionWithFloor(item);

		//検出したプレイヤーの周囲のポリゴン情報を解放する
		MV1CollResultPolyDimTerminate(m_hitDim);

	}

	CheckSendOnCollideInfo(m_preCollideInfo, m_newCollideInfo, false);
	CheckSendOnCollideInfo(m_preTriggerInfo, m_newTriggerInfo, true);

	//位置決定
	FixPosition();

	for (const auto& info : m_onCollideInfo)
	{
		if (info.kind == eOnCollideInfoKind::CollideEnter)
		{
			info.mySelf->OnCollideEnter(info.person);
		}
		else if (info.kind == eOnCollideInfoKind::CollideStay)
		{
			info.mySelf->OnCollideStay(info.person);
		}
		else if (info.kind == eOnCollideInfoKind::CollideExit)
		{
			info.mySelf->OnCollideExit(info.person);
		}
		else if (info.kind == eOnCollideInfoKind::TriggerEnter)
		{
			info.mySelf->OnTriggerEnter(info.person);
		}
		else if (info.kind == eOnCollideInfoKind::TriggerStay)
		{
			info.mySelf->OnTriggerStay(info.person);
		}
		else if (info.kind == eOnCollideInfoKind::TriggerExit)
		{
			info.mySelf->OnTriggerExit(info.person);
		}
	}

}

/// <summary>
/// 当たり判定チェック
/// </summary>
void MyLibrary::Physics::CheckCollide()
{
	std::vector<OnCollideInfoData> onCollideInfo;
	//衝突通知、ポジション補正
	bool doCheck = true;
	int checkCount = 0;     //チャック回数
	while (doCheck)
	{
		doCheck = false;
		checkCount++;

		//2重ループで全オブジェクト当たり判定
		//FIXME : 重いので近いオブジェクト同士のみ当たり判定するなど工夫がいる
		for (const auto& objA : m_collidables)
		{
			for (const auto& objB : m_collidables)
			{
				//同一オブジェクトなら早期リターン
				if (objA == objB)
					continue;

				for (const auto& colA : objA->m_colliders)
				{
					for (const auto& colB : objB->m_colliders)
					{
						if (!IsCollide(objA->rigidbody, objB->rigidbody, colA.get(), colB.get())) continue;

						bool isTrigger = colA->IsTrigger() || colB->IsTrigger();

						if (isTrigger)
						{
							AddNewCollideInfo(objA, objB, m_newTriggerInfo);
						}
						else
						{
							AddNewCollideInfo(objA, objB, m_newCollideInfo);
						}

						//Triggerの場合は位置補正はしない
						if (isTrigger) continue;

						auto primary = objA;
						auto secondary = objB;

						if (primary == secondary)
						{
							break;
						}

						auto primaryCollider = colA;
						auto secondaryCollider = colB;
						if (objA->priority < objB->priority)
						{
							primary = objB;
							secondary = objA;
							primaryCollider = colB;
							secondaryCollider = colA;
						}

						FixNextPosition(primary->rigidbody, secondary->rigidbody, primaryCollider.get(), secondaryCollider.get());
						//位置補正をしたらもう一度初めから行う
						doCheck = true;
						break;
					}
					if (doCheck) break;
				}
				if (doCheck) break;
			}
			if (doCheck) break;
		}
		if (doCheck && checkCount > 800)
		{
#if _DEBUG
			printfDx("規定回数を超えました");
#endif
			break;
		}
	}
}

/// <summary>
/// 二つのオブジェクトが接触しているかどうか
/// </summary>
/// <param name="rigidA">オブジェクトAの物理データ</param>
/// <param name="rigidB">オブジェクトBの物理データ</param>
/// <param name="colliderA">オブジェクトAの当たり判定データ</param>
/// <param name="colliderB">オブジェクトBの当たり判定データ</param>
/// <returns></returns>
bool MyLibrary::Physics::IsCollide(const Rigidbody& rigidA, const Rigidbody& rigidB, CollidableData* colliderA, CollidableData* colliderB) const
{
	bool isCollide = false;

	auto kindA = colliderA->GetKind();
	auto kindB = colliderB->GetKind();

	if (kindA == MyLibrary::CollidableData::Kind::Capsule && kindB == MyLibrary::CollidableData::Kind::Capsule)
	{
		auto colA = dynamic_cast<MyLibrary::CollidableDataCapsule*>(colliderA);
		auto colB = dynamic_cast<MyLibrary::CollidableDataCapsule*>(colliderB);

		auto atob = rigidA.GetNextPos() - rigidB.GetNextPos();
		auto atobLength = atob.Length();

		//お互いの距離が、それぞれ半径を足したものより小さければ当たる
		isCollide = (atobLength < colA->m_radius + colB->m_radius);
	}

	return isCollide;
}

/// <summary>
/// 当たったオブジェクトのペアを登録する
/// </summary>
/// <param name="objA">オブジェクトA</param>
/// <param name="objB">オブジェクトB</param>
/// <param name="info">登録する配列</param>
void MyLibrary::Physics::AddNewCollideInfo(const std::shared_ptr<Collidable>& objA, const std::shared_ptr<Collidable>& objB, SendCollideInfo& info)
{
	bool isPairA = info.find(objA) != info.end();
	bool isPairB = info.find(objB) != info.end();
	if (isPairA || isPairB)
	{
		std::shared_ptr<Collidable> parent = objA;
		std::shared_ptr<Collidable> child = objB;
		if (isPairB)
		{
			parent = objB;
			child = objA;
		}
		bool isChild = std::find(info[parent].begin(), info[parent].end(), child) != info[parent].end();
		if (!isChild)
		{
			info[parent].emplace_back(child);
		}
	}
	else
	{
		info[objA].emplace_back(objB);
	}
}

/// <summary>
/// 移動予定の座標を修正する
/// </summary>
/// <param name="primaryRigid">優先度が高いオブジェクトの物理データ</param>
/// <param name="secondaryRigid">優先度が低いオブジェクトの物理データ</param>
/// <param name="primaryCollider">優先度が高いオブジェクトの当たり判定データ</param>
/// <param name="secondaryCollider">優先度が低いオブジェクトの当たり判定データ</param>
void MyLibrary::Physics::FixNextPosition(const Rigidbody& primaryRigid, Rigidbody& secondaryRigid, CollidableData* primaryCollider, CollidableData* secondaryCollider) const
{
	//当たり判定の種別毎に補正方法を変える
	auto primaryKind = primaryCollider->GetKind();
	auto secondaryKind = secondaryCollider->GetKind();

	if (primaryKind == MyLibrary::CollidableData::Kind::Capsule && secondaryKind == MyLibrary::CollidableData::Kind::Capsule)
	{
		auto primaryToSecondary = secondaryRigid.GetNextPos() - primaryRigid.GetNextPos();
		auto primaryToSecondaryN = primaryToSecondary.Normalize();

		auto primaryColliderData = dynamic_cast<MyLibrary::CollidableDataCapsule*>(primaryCollider);
		auto secondaryColliderData = dynamic_cast<MyLibrary::CollidableDataCapsule*>(secondaryCollider);
		auto awayDist = primaryColliderData->m_radius + secondaryColliderData->m_radius + 0.0001f; //そのままだとあたる位置になるから余分に離す
		auto primaryToNewSecondaryPos = primaryToSecondaryN * awayDist;
		auto fixedPos = primaryRigid.GetNextPos() + primaryToNewSecondaryPos;
		fixedPos.y = secondaryRigid.GetPos().y;
		secondaryRigid.SetNextPos(fixedPos);

	}
}

/// <summary>
/// 種類毎に衝突通知を飛ばす配列に追加する
/// </summary>
/// <param name="preSendInfo">衝突したオブジェクトのリストのログ</param>
/// <param name="newSendInfo">衝突したオブジェクトのリスト</param>
/// <param name="isTrigger">無視するかどうか</param>
void MyLibrary::Physics::CheckSendOnCollideInfo(SendCollideInfo& preSendInfo, SendCollideInfo& newSendInfo, bool isTrigger)
{
	for (auto& parent : newSendInfo)
	{
		//以前の情報に親として登録されているか
		bool isPreParent = preSendInfo.find(parent.first) != preSendInfo.end();
		bool isAllEnter = true;

		for (auto& child : parent.second)
		{
			bool isPreChild = false;
			if (isPreChild)
			{
				//以前の情報に子として登録されているか
				auto& preParent = preSendInfo[parent.first];
				isPreChild = std::find(preParent.begin(), preParent.end(), child) != preParent.end();

			}

			//今回入ってきた場合はEnterを呼ぶ(子として登録されていない)
			if (!isPreChild)
			{
				if (isTrigger)
				{
					AddOnCollideInfo(parent.first, child, eOnCollideInfoKind::TriggerEnter);
					AddOnCollideInfo(child, parent.first, eOnCollideInfoKind::TriggerEnter);
				}
				else
				{
					AddOnCollideInfo(parent.first, child, eOnCollideInfoKind::CollideEnter);
					AddOnCollideInfo(child, parent.first, eOnCollideInfoKind::CollideEnter);
				}
			}

			//Staryは毎度呼ぶ
			if (isTrigger)
			{
				AddOnCollideInfo(parent.first, child, eOnCollideInfoKind::TriggerStay);
				AddOnCollideInfo(child, parent.first, eOnCollideInfoKind::TriggerStay);
			}
			else
			{
				AddOnCollideInfo(parent.first, child, eOnCollideInfoKind::CollideStay);
				AddOnCollideInfo(child, parent.first, eOnCollideInfoKind::CollideStay);
			}

			//登録されていた情報を削除
			if (isPreChild)
			{
				preSendInfo[parent.first].remove(child);
			}
			//全て登録されていなかったとする
			else
			{
				isAllEnter = false;
			}
		}

		//全て登録されていたら親の情報も消す
		if (isAllEnter)
		{
			preSendInfo.erase(parent.first);
		}
	}

	//残っている前情報からExistを呼ぶ(登録が残っている=今回抜けた)
	for (auto& parent : preSendInfo)
	{
		for (auto& child : parent.second)
		{
			if(isTrigger)
			{
				AddOnCollideInfo(parent.first, child, eOnCollideInfoKind::TriggerExit);
				AddOnCollideInfo(child, parent.first, eOnCollideInfoKind::TriggerExit);
			}
			else
			{
				AddOnCollideInfo(parent.first, child, eOnCollideInfoKind::CollideExit);
				AddOnCollideInfo(child, parent.first, eOnCollideInfoKind::CollideExit);
			}
		}
	}
}

/// <summary>
/// 衝突通知を飛ばす配列に追加する
/// </summary>
/// <param name="mySelf">自身</param>
/// <param name="person">衝突した相手</param>
/// <param name="kind">当たり判定の種類</param>
void MyLibrary::Physics::AddOnCollideInfo(const std::shared_ptr<Collidable>& mySelf, const std::shared_ptr<Collidable>& person, eOnCollideInfoKind kind)
{
	OnCollideInfoData addInfo;
	addInfo.mySelf = mySelf;
	addInfo.person = person;
	addInfo.kind = kind;
	m_onCollideInfo.emplace_back(addInfo);
}

/// <summary>
/// 最終的な位置を決定する
/// </summary>
void MyLibrary::Physics::FixPosition()
{
	for (auto& item : m_collidables)
	{
		//Posを更新するので、velocityもそこに移動するvelocityに修正
		LibVec3 toFixedPos = item->rigidbody.GetNextPos() - item->rigidbody.GetPos();
		item->rigidbody.SetVelocity(toFixedPos);

		//位置確定
		item->rigidbody.SetPos(item->rigidbody.GetNextPos());
	}
}

/// <summary>
/// チェックしたポリゴンが壁ポリゴンか床ポリゴンかを判断する
/// </summary>
/// <param name="col">チェックするオブジェクト</param>
void MyLibrary::Physics::CheckWallAndFloor(std::shared_ptr<Collidable>& col)
{
	//壁ポリゴンと床ポリゴンの数を初期化する
	m_wallNum = 0;
	m_floorNum = 0;

	//検出されたポリゴンの数だけ繰り返し
	for (int i = 0; i < m_hitDim.HitNum; i++)
	{
		//ポリゴンの法線のY成分が壁ポリゴンボーダーに達しているかどうかで壁ポリゴンか床ポリゴンかを判断する
		if (m_hitDim.Dim[i].Normal.y < kWallPolyBorder && m_hitDim.Dim[i].Normal.y > -kWallPolyBorder)
		{
			//壁ポリゴンと判断された場合でも、プレイヤーのY座標より高いポリゴンのみ当たり判定を行う
			if (m_hitDim.Dim[i].Position[0].y > col->rigidbody.GetPos().y + kWallPolyHeight ||
				m_hitDim.Dim[i].Position[1].y > col->rigidbody.GetPos().y + kWallPolyHeight ||
				m_hitDim.Dim[i].Position[2].y > col->rigidbody.GetPos().y + kWallPolyHeight)
			{
				//ポリゴンの数が限界数に達していなかったらポリゴンを配列に追加
				if (m_wallNum < ColInfo::kMaxColHitPoly)
				{
					//ポリゴンの構造体のアドレスを壁ポリゴンポインタ配列に追加する
					m_pWallPoly[m_wallNum] = &m_hitDim.Dim[i];

					//壁ポリゴンの数を加算する
					m_wallNum++;
				}
			}
		}
		else
		{
			//ポリゴンの数が限界数に達していなかったらポリゴンを配列に追加
			if (m_floorNum < ColInfo::kMaxColHitPoly)
			{
				//ポリゴンの構造体のアドレスを床ポリゴンポインタ配列に保存する
				m_pFloorPoly[m_floorNum] = &m_hitDim.Dim[i];

				//床ポリゴンの数を加算する
				m_floorNum;
			}
		}
	}
}

/// <summary>
/// 壁ポリゴンとの当たり判定をチェックし、移動させる
/// </summary>
/// <param name="col">チェックするオブジェクト</param>
void MyLibrary::Physics::FixPositionWithWall(std::shared_ptr<Collidable>& col)
{
	float radius = 0.0f;
	VECTOR vec = VGet(0.0f, 0.0f, 0.0f);
	for (auto& col : col->m_colliders)
	{
		radius = dynamic_cast<MyLibrary::CollidableDataCapsule*> (col.get())->m_radius;
		vec = dynamic_cast<MyLibrary::CollidableDataCapsule*> (col.get())->m_vec.ConversionToVECTOR();
	}

	//壁ポリゴンがない場合は何もしない
	if (m_wallNum == 0) return;

	//壁ポリゴンとの当たり判定処理
	//壁に当たったかどうかのフラグは初期状態では「当たっていない」にしておく
	m_isHitFlag = false;

	//移動したかどうかで処理を分岐
	if (col->rigidbody.GetDir().Length() != 0.0f)
	{
		//壁ポリゴンの数だけ繰り返し
		for (int i = 0; i < m_wallNum; i++)
		{
			//i番目の壁ポリゴンのアドレスを壁ポリゴンポインタ配列から取得
			m_pPoly = m_pWallPoly[i];

			//ポリゴンとプレイヤーが当たっていなかったら次のカウントへ
			if (!HitCheck_Capsule_Triangle(VAdd(col->rigidbody.GetNextPosVECTOR(), vec), VSub(col->rigidbody.GetNextPosVECTOR(), vec), radius,
				m_pPoly->Position[0], m_pPoly->Position[1], m_pPoly->Position[2])) continue;

			//ここにきたらポリゴンとプレイヤーが当たっているということなので、ポリゴンに当たったフラグを立てる
			m_isHitFlag = true;

			//壁を考慮した移動を外積を使って算出
			MyLibrary::LibVec3 SlideVec;

			VECTOR ret;
			ret = VCross(col->rigidbody.GetVelocityVECTOR(), m_pPoly->Normal);
			//進行方向ベクトルと壁ポリゴンの法線ベクトルに垂直なベクトルを算出
			SlideVec = MyLibrary::LibVec3(ret.x, ret.y, ret.z);

			//それを移動前の座標に足したものを新たな座標とする
			col->rigidbody.SetNextPos(col->rigidbody.GetPos() + SlideVec);

			//新たな移動座標で壁ポリゴンと当たっていないかどうかを判定する
			bool isHitWallPolygon = false;
			for (int j = 0; j < m_wallNum; j++)
			{
				//j番目の壁ポリゴンのアドレスを壁ポリゴンポインタ配列から取得
				m_pPoly = m_pWallPoly[j];

				//当たっていたらループから抜ける
				if (HitCheck_Capsule_Triangle(VAdd(col->rigidbody.GetNextPosVECTOR(), vec), VSub(col->rigidbody.GetNextPosVECTOR(), vec), radius,
					m_pPoly->Position[0], m_pPoly->Position[1], m_pPoly->Position[2]))
				{
					//trueにする
					isHitWallPolygon = true;
					break;
				}
			}

			//全てのポリゴンと当たっていなかったらここでループ終了
			if (!isHitWallPolygon)
			{
				//ヒットフラグを倒す
				m_isHitFlag = false;
				break;
			}
		}
	}
	else
	{
		//移動していない場合の処理

		//壁ポリゴンの数だけ繰り返し
		for (int i = 0; i < m_wallNum; i++)
		{
			//i番目の壁ポリゴンのアドレスを壁ポリゴンポインタ配列から取得
			m_pPoly = m_pWallPoly[i];

			//ポリゴンに当たっていたら当たったフラグを立てた上でループから抜ける
			if (HitCheck_Capsule_Triangle(VAdd(col->rigidbody.GetNextPosVECTOR(), vec), VSub(col->rigidbody.GetNextPosVECTOR(), vec), radius,
				m_pPoly->Position[0], m_pPoly->Position[1], m_pPoly->Position[2]))
			{
				m_isHitFlag = true;
				break;
			}
		}


		//壁に当たっていたら壁から押し出す処理を行う
		if (m_isHitFlag)
		{
			FixPositionWithWallInternal(col);
		}
	}
}

/// <summary>
/// 壁の中から押し出す
/// </summary>
/// <param name="col">チェックするオブジェクト</param>
void MyLibrary::Physics::FixPositionWithWallInternal(std::shared_ptr<Collidable>& col)
{
	float radius = 0.0f;
	VECTOR vec = VGet(0.0f, 0.0f, 0.0f);
	for (auto& col : col->m_colliders)
	{
		radius = dynamic_cast<MyLibrary::CollidableDataCapsule*> (col.get())->m_radius;
		vec = dynamic_cast<MyLibrary::CollidableDataCapsule*> (col.get())->m_vec.ConversionToVECTOR();
	}

	//壁からの押し出し処理を試みる最大数だけ繰り返し
	for (int i = 0; i < ColInfo::kMaxColHitTry; i++)
	{
		//当たる可能性のある壁ポリゴンを全て見る
		bool isHitWall = false;
		//壁ポリゴンの数だけ繰り返し
		for (int j = 0; j < m_wallNum; j++)
		{
			//j番目の壁ポリゴンのアドレスを壁ポリゴンポインタ配列から取得
			m_pPoly = m_pWallPoly[j];

			//ポリゴンとプレイヤーが当たっていなかったら次のカウントへ
			if (!HitCheck_Capsule_Triangle(VAdd(col->rigidbody.GetNextPosVECTOR(), vec), VSub(col->rigidbody.GetNextPosVECTOR(), vec), radius,
				m_pPoly->Position[0], m_pPoly->Position[1], m_pPoly->Position[2])) continue;

			auto ret = VAdd(col->rigidbody.GetNextPosVECTOR(), VScale(m_pPoly->Normal, kColHitSlideLength));

			MyLibrary::LibVec3 set;
			set = MyLibrary::LibVec3(ret.x, ret.y, ret.z);

			//当たっていたら規定距離分プレイヤーを壁の法線方向に移動させる
			col->rigidbody.SetNextPos(set);

			//移動したうえで壁ポリゴンと接続しているかどうかを判定
			for (int k = 0; k < m_wallNum; k++)
			{
				//当たっていたらループを抜ける
				m_pPoly = m_pWallPoly[k];
				if (HitCheck_Capsule_Triangle(VAdd(col->rigidbody.GetNextPosVECTOR(), vec), VSub(col->rigidbody.GetNextPosVECTOR(), vec), radius,
					m_pPoly->Position[0], m_pPoly->Position[1], m_pPoly->Position[2]))
				{
					isHitWall = true;
					break;
				}

			}

			//全てのポリゴンと当たっていなかったらここでループ終了
			if (!isHitWall) break;
		}

		//ループ終了
		if (!isHitWall) break;
	}
}

/// <summary>
/// 床ポリゴンとの当たり判定をチェックし、移動させる
/// </summary>
/// <param name="col">チェックするオブジェクト</param>
void MyLibrary::Physics::FixNowPositionWithFloor(std::shared_ptr<Collidable>& col)
{
	//床ポリゴンがない場合は何もしない
	if (m_floorNum == 0) return;

	float radius = 0.0f;
	VECTOR vec = VGet(0.0f, 0.0f, 0.0f);
	for (auto& col : col->m_colliders)
	{
		radius = dynamic_cast<MyLibrary::CollidableDataCapsule*> (col.get())->m_radius;
		vec = dynamic_cast<MyLibrary::CollidableDataCapsule*> (col.get())->m_vec.ConversionToVECTOR();
	}

	//床ポリゴンとの当たり判定処理
	//あたったかどうかのフラグ初期化
	bool isHitFlag = false;

	//床ポリゴンとの当たり判定
	//一番高い床ポリゴンにぶつける為の判定用変数を初期化
	float PolyMaxPosY = 0.0f;

	//床ポリゴンの数だけ繰り返し
	for (int i = 0; i < m_floorNum; i++)
	{
		//i番目の床ポリゴンのアドレスを床ポリゴンポインタ配列から取得
		m_pPoly = m_pFloorPoly[i];

		//ポリゴンとプレイヤーが当たっていなかったら次のカウントへ
		if (HitCheck_Capsule_Triangle(VAdd(col->rigidbody.GetNextPosVECTOR(), vec), VSub(col->rigidbody.GetNextPosVECTOR(), vec), radius,
			m_pPoly->Position[0], m_pPoly->Position[1], m_pPoly->Position[2])) continue;

		float mostHeightY = m_pPoly->Position[0].y;

		if (mostHeightY < m_pPoly->Position[1].y)
		{
			mostHeightY = m_pPoly->Position[1].y;
		}

		if (mostHeightY < m_pPoly->Position[2].y)
		{
			mostHeightY = m_pPoly->Position[2].y;
		}

		//既に当たったポリゴンがあり、且つ今まで検出した床ポリゴンより低い場合は何もしない
		if (m_isHitFlag && PolyMaxPosY > mostHeightY) continue;

		//ポリゴンに当たったフラグを立てる
		m_isHitFlag = true;

		//接触したY座標を保持する
		PolyMaxPosY = mostHeightY;
	}

	//床ポリゴンの当たり判定かつ、ジャンプ力が0よりも小さい(下降中の場合)どうかで処理を分岐
	if (m_isHitFlag)
	{
		//接触したポリゴンで一番高いY座標をプレイヤーのY座標にする
		auto set = col->rigidbody.GetNextPos();
		set.y = PolyMaxPosY + radius;
		col->rigidbody.SetNextPos(set);
	}
}
