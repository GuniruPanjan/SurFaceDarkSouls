#include "WeaponSummary.h"
#include "Singleton/HandleManager.h"

namespace
{
	int a;
	MATRIX temp;
	MATRIX mat;

	//シングルトン
	auto& handle = HandleManager::GetInstance();
}

/// <summary>
/// コンストラクタ
/// </summary>
WeaponSummary::WeaponSummary():
	m_weaponHandle(-1),
	m_weaponSize(0.0f),
	m_weaponFrameIndex(0),
	m_weaponFramePosition(VGet(0.0f, 0.0f, 0.0f)),
	m_weaponPosition(VGet(0.0f,0.0f,0.0f))
{
	m_transMatrix = MV1GetFrameLocalWorldMatrix(0, 0);
	m_mixMatrix = MV1GetFrameLocalWorldMatrix(0, 0);
	m_weaponMatrixY = MGetRotY(5.655f);
	m_weaponMatrixZ = MGetRotZ(1.795f);
}

/// <summary>
/// デストラクタ
/// </summary>
WeaponSummary::~WeaponSummary()
{
	//メモリ解放
	MV1DeleteModel(m_weaponHandle);
	MV1DeleteModel(pshield->m_shieldHandle);

	//メモリ解放
	handle.Clear();
}

/// <summary>
/// 初期化処理
/// </summary>
void WeaponSummary::Init()
{
	m_weaponSize = 0.5f;

	m_weaponHandle = handle.GetModelHandle("Data/Weapon/Sword.mv1");

	m_weaponPosition = VGet(0.0f, 1.947f, -1.947f);

	//サイズ変更
	MV1SetScale(m_weaponHandle, VGet(m_weaponSize, m_weaponSize, m_weaponSize));


	//盾の初期化
	pshield->m_shieldSize = 1.0f;
	pshield->m_shieldHandle = handle.GetModelHandle("Data/Weapon/Shield.mv1");
	pshield->m_mixMatrix = MV1GetFrameLocalMatrix(0, 0);
	pshield->m_shieldFrameIndex = 0;
	pshield->m_shieldFramePosition = VGet(0.0f, 0.0f, 0.0f);
	pshield->m_shieldPos = VGet(0.0f, 0.0f, 7.787f);
	pshield->m_transMatrix = MV1GetFrameLocalWorldMatrix(0, 0);
	pshield->m_weaponMatrixY = MGetRotY(3.142f);
	pshield->m_weaponMatrixZ = MGetRotZ(0.0f);
}

/// <summary>
/// 右手の装備の更新処理
/// </summary>
/// <param name="mat">右手の行列</param>
void WeaponSummary::RightUpdate(MATRIX mat)
{
	MV1SetMatrix(m_weaponHandle, MGetIdent());

	//フレームを検索
	m_weaponFrameIndex = MV1SearchFrame(m_weaponHandle, "2:Sphere");

	m_weaponFramePosition = MV1GetFramePosition(m_weaponHandle, m_weaponFrameIndex);

	m_weaponPosition = VAdd(m_weaponFramePosition, m_weaponPosition);

	//アタッチするモデルをフレームの座標を原点にするための平行移動行列を作成
	m_transMatrix = MGetTranslate(VScale(m_weaponPosition, -1.0f));

	m_transMatrix = MMult(m_transMatrix, m_weaponMatrixY);
	m_transMatrix = MMult(m_transMatrix, m_weaponMatrixZ);

	m_mixMatrix = MMult(m_transMatrix, mat);

	MV1SetMatrix(m_weaponHandle, m_mixMatrix);
}

/// <summary>
/// 左手の更新処理
/// </summary>
/// <param name="mat">左手の行列</param>
void WeaponSummary::LeftUpdate(MATRIX mat)
{
	MV1SetMatrix(pshield->m_shieldHandle, MGetIdent());

	//フレームを検索
	pshield->m_shieldFrameIndex = MV1SearchFrame(pshield->m_shieldHandle, "0:fbx");

	pshield->m_shieldFramePosition = MV1GetFramePosition(pshield->m_shieldHandle, pshield->m_shieldFrameIndex);

	pshield->m_shieldPos = VAdd(pshield->m_shieldFramePosition, pshield->m_shieldPos);

	//アタッチするモデルをフレームの座標を原点にするための平行移動行列を作成
	pshield->m_transMatrix = MGetTranslate(VScale(pshield->m_shieldPos, -1.0f));

	pshield->m_transMatrix = MMult(pshield->m_transMatrix, pshield->m_weaponMatrixY);
	pshield->m_transMatrix = MMult(pshield->m_transMatrix, pshield->m_weaponMatrixZ);

	pshield->m_mixMatrix = MMult(pshield->m_transMatrix, mat);

	MV1SetMatrix(pshield->m_shieldHandle, pshield->m_mixMatrix);
}

/// <summary>
/// 右手の装備の描画処理
/// </summary>
void WeaponSummary::RightDraw()
{
	//モデル描画
	MV1DrawModel(m_weaponHandle);
}

/// <summary>
/// 左手の装備の描画処理
/// </summary>
void WeaponSummary::LeftDraw()
{
	//モデル描画
	MV1DrawModel(pshield->m_shieldHandle);
}

/// <summary>
/// 終了処理
/// </summary>
void WeaponSummary::End()
{
	//メモリ解放
	MV1DeleteModel(m_weaponHandle);
	MV1DeleteModel(pshield->m_shieldHandle);

	//メモリ解放
	handle.Clear();
}
