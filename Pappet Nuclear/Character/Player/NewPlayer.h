#pragma once
#include "DxLib.h"
#include "Library/MyLibrary.h"
#include "Character/CharacterBase.h"
#include "Character/Player/Equipment/Equipment.h"
#include "Character/Player/WeaponSummary.h"
#include <list>
#include <memory>

class NewPlayer : public CharacterBase
{
public:
	//レベル関係の構造体
	struct LevelUpStatus
	{
		int sl_hp;         //体力
		int sl_stamina;    //スタミナ
		int sl_muscle;     //筋力
		int sl_skill;      //技量
		int sl_all;        //すべてのレベル

	}m_levelStatus;

	NewPlayer();
	virtual ~NewPlayer();

	void Init(std::shared_ptr<MyLibrary::Physics> physics);
	void Finalize();
	void Update(std::shared_ptr<Equipment> eq);
	void Animation();
	void Draw(std::shared_ptr<Equipment> eq);

	//衝突した時
	void OnCollideEnter(const std::shared_ptr<Collidable>& collidable) override;
	void OnTriggerEnter(const std::shared_ptr<Collidable>& collidable) override;

	void SetCameraAngle(float angle) { m_cameraAngle = angle; }

	const MyLibrary::LibVec3 GetPos() const { return rigidbody.GetPos(); }



private:
	void SetModelPos();
private:
	XINPUT_STATE m_xpad;  //パッド入力
	float m_cameraAngle;  //カメラ情報
	float m_lockAngle;    //ロックオンした時のアングル 
	int m_recoveryNumber;     //回復できる回数変数
	float m_heel;             //hpに足す回復量
	bool m_recoberyAction;    //回復中の判定
	bool m_lockonTarget;  //ターゲットロックオン判定
	int m_moveAnimFrameIndex;  //フレームを検索する
	int m_moveAnimFrameRight;   //右手のフレームを検索する
	VECTOR m_moveAnimFrameRigthPosition;  //右手のフレームのポジション
	int m_moveAnimShieldFrameIndex;  //ガードするときのフレーム検索
	int m_moveAnimShieldFrameHandIndex;     //ガードするときの体のフレーム検索
	VECTOR m_moveAnimFrameLeftPosition;   //左手のフレームのポジション
	MATRIX m_moveWeaponFrameMatrix;   //武器をアタッチするフレームのローカル座標
	MATRIX m_moveShieldFrameMatrix;   //盾をアタッチするフレームのローカル座標
	bool m_oneAvoidance;   //一回だけ回避の方向を判定する
	bool m_nextAttack1;  //次の攻撃判定
	bool m_nextAttack2;  //次の攻撃判定
	bool m_avoidanceNow;   //回避できるフレーム中か判断する変数
	bool m_restAction;    //回復ができるようになる判定
	bool m_dashMove;     //ダッシュしてる判断用変数
	bool m_staminaBroke;   //スタミナ切れ判定
	bool m_menuOpen;      //メニューを開く
	bool m_notWeapon;     //武器を持ってない状態
	bool m_notShield;     //盾を持ってない状態
	bool m_fistCol;       //拳の当たり判定初期化
	bool m_swordCol;      //剣の当たり判定初期化判定
	VECTOR m_nowPos;   //現在のフレームの座標を取得する

	//スマートポインタ
	std::shared_ptr<WeaponSummary> weapon = std::make_shared<WeaponSummary>();
};

