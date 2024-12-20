#pragma once
#include "Character/CharacterBase.h"
#include "Character/Player/WeaponSummary.h"
#include "Character/Player/Equipment/Equipment.h"

class Player : public CharacterBase
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

	Player();
	virtual ~Player();

	void Init();
	void Update();
	void WeaponUpdate(Equipment& eq);
	void PlaySE(int volume);
	void OtherInfluence(VECTOR outpush, VECTOR weakoutpush);
	void Action();
	void NotWeaponAnimation(float& time);
	void Animation(float& time, VECTOR& pos);
	void WeaponAnimation(float& time);
	void HitObj(Map& map, ItemManager& item);
	void MapAction(Map& map, ItemManager& item);
	void Draw();
	void WeaponDraw(Equipment& eq);
	void End();

	//衝突したとき
	void OnCollideEnter(const std::shared_ptr<Collidable>& collidable)override;
	void OnTriggerEnter(const std::shared_ptr<Collidable>& collidable)override;

	//カプセル同士の当たり判定
	bool IsCapsuleHit(const CapsuleCol& col, const CapsuleCol& col1);
	bool isSphereHit(const SphereCol& col, float damage);
	bool isBossSphereHit(const SphereCol& col1, const SphereCol& col2, const SphereCol& col3, float bossdamage);
	bool isShieldHit(const SphereCol& col, float damage);
	bool isBossShieldHit(const SphereCol& col1, const SphereCol& col2, const SphereCol& col3, float bossdamage);
	bool isTargetHit(const CapsuleCol& col, int max);

	void SetCameraAngle(float angle) { m_cameraAngle = angle; }

	VECTOR GetPos() { return m_pos; }
	float GetPosX() { return m_pos.x; }
	float GetPosY() { return m_pos.y; }
	float GetPosZ() { return m_pos.z; }
	float SetAngle(float lockangle) { return m_lockAngle = lockangle; }
	VECTOR GetShieldPos() { return VGet(m_rectPos.x, m_rectPos.y, m_rectPos.z); }
	float GetDamage() { return m_status.s_attack; }
	float GetAngle() { return m_angle; }
	float GetBounceDis() { return m_bounceDis; }
	float GetSpeed() { return m_status.s_speed; }
	VECTOR GetBounceMove() { return m_bounceMove; }
	CapsuleCol GetCapsuleCol() { return m_capsuleCol; }
	SphereCol GetSphereCol() { return m_sphereCol; }

	bool GetLock() { return m_lockonTarget; }
	bool SetLock(bool lock) { return m_lockonTarget = lock; }
	bool GetRest() { return m_restAction; }
	bool SetRest(bool rest) { return m_restAction = rest; }
	bool GetDeath() { return m_death; }
	bool GetReceived() { return m_damageReceived; }
	bool SetReceived(bool recebived) { return m_damageReceived = recebived; }
	bool GetMenu() { return m_menuOpen; }
	bool SetMenu(bool menu) { return m_menuOpen = menu; }
	int GetButton() { return m_button; }
	int SetCore(int core) { return m_coreAllLevel = core; }
	bool GetOne() { return m_one; }
	bool GetTarget(int max) { return m_targetNumber[max]; }

	//UIに必要な変数
	float GetHp() { return m_status.s_hp; }
	float GetStamina() { return m_status.s_stamina; }
	int GetRecoveryNumber() { return m_recoveryNumber; }

private:
	float m_cameraAngle;  //カメラ情報
	float m_updatePosX;   //X座標更新用変数
	float m_updatePosY;   //Y座標更新用変数
	float m_updatePosZ;   //Z座標更新用変数
	float m_lockAngle;    //ロックオンした時のアングル 
	float m_swordRadius;   //剣の当たり判定の半径
	float m_targetRadius;   //ターゲットの当たり判定の半径
	int m_recoveryNumber;     //回復できる回数変数
	float m_recoberyAmount;   //回復量
	float m_heel;             //hpに足す回復量
	bool m_recoberyAction;    //回復中の判定
	bool m_lockonTarget;  //ターゲットロックオン判定
	bool m_targetNumber[ENEMY_NOW];     //ターゲットできる奴の判定
	int m_moveAnimFrameIndex;  //フレームを検索する
	int m_moveAnimFrameRight;   //右手のフレームを検索する
	VECTOR m_moveAnimFrameRigthPosition;  //右手のフレームのポジション
	int m_moveAnimShieldFrameIndex;  //ガードするときのフレーム検索
	int m_moveAnimShieldFrameHandIndex;     //ガードするときの体のフレーム検索
	VECTOR m_moveAnimFrameLeftPosition;   //左手のフレームのポジション
	MATRIX m_moveWeaponFrameMatrix;   //武器をアタッチするフレームのローカル座標
	MATRIX m_moveShieldFrameMatrix;   //盾をアタッチするフレームのローカル座標
	int m_a;  //長押し確認変数
	int m_pad;  //パッド入力所得変数
	XINPUT_STATE m_xpad;  //パッド入力
	int m_animRollAttack;  //キャラがローディング後に攻撃するアニメーション
	int m_bugTime;         //一定時間経ったらバグと判断する
	int m_button;          //ボタン変数
	bool m_one;            //一回だけ判定をする
	bool m_oneAvoidance;   //一回だけ回避の方向を判定する
	bool m_avoidance;   //回避入力を判断するための変数
	bool m_nextAttack1;  //次の攻撃判定
	bool m_nextAttack2;  //次の攻撃判定
	bool m_pushButton;   //ボタンの入力を一回だけ受け取るための判定
	bool m_avoidanceNow;   //回避できるフレーム中か判断する変数
	bool m_restAction;    //回復ができるようになる判定
	bool m_dashMove;     //ダッシュしてる判断用変数
	bool m_staminaBroke;   //スタミナ切れ判定
	bool m_shieldNow;     //防御中の判定
	bool m_oneShield;     //一回だけ
	bool m_bug;           //バグの判定
	bool m_menuOpen;      //メニューを開く
	bool m_notWeapon;     //武器を持ってない状態
	bool m_notShield;     //盾を持ってない状態
	bool m_fistCol;       //拳の当たり判定初期化
	bool m_swordCol;      //剣の当たり判定初期化判定
	VECTOR m_nowPos;   //現在のフレームの座標を取得する
	VECTOR m_bounceMove;   //押し出すための変数
	Pos3 m_targetColPos;     //ターゲットの当たり判定ポジション
	Pos3 m_rectPos;          //盾の当たり判定ポジション
	Size m_rectSize;         //盾の当たり判定サイズ
	SphereCol m_targetCunCol;   //ターゲットできるようにする
	RectCol m_rectCol;       //盾の当たり判定

	float m_rate;
	bool m_a1;

	unsigned int m_color = 0xffffff;   //デバッグ用の色変更
	unsigned int m_rectColor = 0xffffff;      //デバッグ用の色変更

	//アニメーション関係
	int m_animLeft;       //左に歩くアニメーション代入
	int m_animRight;      //右に歩くアニメーション代入
	int m_animHeel;       //回復アニメーション代入
	int m_animShield;      //盾を構えるアニメーション代入
	int m_animShieldImpact;     //武器を持った時の立ってるアニメーション
	int m_animWeaponWalk;      //武器を持った時の歩いているアニメーション
	int m_animWeaponLeftWalk;   //武器を持った時左に歩くアニメーション
	int m_animWeaponRun;       //武器を持った時の走っているアニメーション
	int m_animShieldStand;     //盾を構えた時の立ってるアニメーション
	int m_animTaking;          //アイテムの所得アニメーション
	int m_animTouch;           //何かに触れる時のアニメーション
	bool m_hit;           //怯み判定
	bool m_weaponMoveRight;     //武器を持った時の右歩きアニメーションにするための判定
	bool m_hitImpact;     //盾受け判定
	bool m_shield;        //防御のアニメーション判定
	bool m_weaponAnimOne;      //武器を持った時にブレンド率を一回だけ調整する
	bool m_notWeaponAnimOne;   //武器を持ってない時にブレンド率を一回だけ調整する
	bool m_itemTaking;         //アイテム所得アニメーション判定
	bool m_itemTakingNow;      //アイテム所得中のアニメーション判定

	//レベル関係
	int m_coreAllLevel;        //レベルを上げるための変数
	int m_hpLevel;       //HPレベル
	int m_staminaLevel;    //スタミナレベル

	//エフェクト関係変数
	int m_effectHeel;        //回復のエフェクト
	bool m_effectOneHeel;    //回復のエフェクトを一回実行

	//スマートポインタ
	std::shared_ptr<WeaponSummary> weapon = std::make_shared<WeaponSummary>();

	//アニメーションブレンド
	std::shared_ptr<BlendAnimation> pAnim = std::make_shared<BlendAnimation>();
};

