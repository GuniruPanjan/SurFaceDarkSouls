#pragma once
#include "Character/CharacterBase.h"
#include "Character/Player/Weapon/Weapon.h"


class Player : public CharacterBase
{
public:
	Player();
	virtual ~Player();

	void Init();
	void Update();
	void OtherInfluence(VECTOR outpush);
	void Action();
	void Animation(float& time, VECTOR& pos);
	void HitObj(Map& map);
	void SaveAction(Map& map);
	void Draw();
	void End();

	//カプセル同士の当たり判定
	bool IsCapsuleHit(const CapsuleCol& col, const CapsuleCol& col1);
	bool isSphereHit(const SphereCol& col, const SphereCol& col1, const SphereCol& col2, const SphereCol& col3, float damage, float bossdamage);

	void SetCameraAngle(float angle) { m_cameraAngle = angle; }

	VECTOR GetPos() { return m_pos; }
	float GetPosX() { return m_pos.x; }
	float GetPosY() { return m_pos.y; }
	float GetPosZ() { return m_pos.z; }
	float GetDamage() { return m_attack; }
	float GetAngle() { return m_angle; }
	float GetBounceDis() { return m_bounceDis; }
	VECTOR GetBounceMove() { return m_bounceMove; }
	CapsuleCol GetCapsuleCol() { return m_capsuleCol; }
	SphereCol GetSphereCol() { return m_sphereCol; }

	bool GetLock() { return m_lockonTarget; }
	bool GetRest() { return m_restAction; }
	bool SetRest(bool rest) { return m_restAction = rest; }
	bool GetDeath() { return m_death; }

	//UIに必要な変数
	float GetHp() { return m_hp; }
	float GetStamina() { return m_stamina; }
	int GetRecoveryNumber() { return m_recoveryNumber; }

private:
	float m_cameraAngle;  //カメラ情報
	float m_updatePosX;   //X座標更新用変数
	float m_updatePosY;   //Y座標更新用変数
	float m_updatePosZ;   //Z座標更新用変数
	float m_stamina;      //スタミナ
	int m_animHeel;       //回復アニメーション代入
	int m_recoveryNumber;     //回復できる回数変数
	float m_recoberyAmount;   //回復量
	float m_heel;             //hpに足す回復量
	bool m_recoberyAction;    //回復中の判定
	bool m_lockonTarget;  //ターゲットロックオン判定
	int m_moveAnimFrameIndex;  //フレームを検索する
	int m_moveAnimFrameRight;   //右手のフレームを検索する
	VECTOR m_moveAnimFrameRigthPosition;  //右手のフレームのポジション
	int m_moveAnimShieldFrameIndex;  //ガードするときのフレーム検索
	MATRIX m_moveWeaponFrameMatrix;   //武器をアタッチするフレームのローカル座標
	int m_a;  //長押し確認変数
	int m_pad;  //パッド入力所得変数
	XINPUT_STATE m_xpad;  //パッド入力
	int m_animRollAttack;  //キャラがローディング後に攻撃するアニメーション
	bool m_avoidance;   //回避入力を判断するための変数
	bool m_nextAttack1;  //次の攻撃判定
	bool m_nextAttack2;  //次の攻撃判定
	bool m_pushButton;   //ボタンの入力を一回だけ受け取るための判定
	bool m_avoidanceNow;   //回避できるフレーム中か判断する変数
	bool m_restAction;    //回復ができるようになる判定
	bool m_dashMove;     //ダッシュしてる判断用変数
	bool m_staminaBroke;   //スタミナ切れ判定
	VECTOR m_nowPos;   //現在のフレームの座標を取得する
	VECTOR m_bounceMove;   //押し出すための変数

	unsigned int m_color = 0xffffff;   //デバッグ用の色変更

	//レベル関係
	int m_hpLevel;       //HPレベル
	int m_staminaLevel;    //スタミナレベル

	std::shared_ptr<Weapon> weapon = std::make_shared<Weapon>();
};

