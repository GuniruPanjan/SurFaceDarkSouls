#pragma once
#include "EffekseerForDXLib.h"
#include <string>
#include <memory>
#include <map>
#include <vector>
#include "DxLib.h"

/// <summary>
/// エフェクトを管理するクラス
/// </summary>
class Effect
{
private:
	//エフェクト構造体
	struct Effectstruct
	{
		int handle;
		float x, y, z;
		int frame;
		bool isExist;
	};

	//エフェクト生成構造体
	struct EffectEmitter
	{
		int emitterHandle = -1;
		const char* effectPath = "";
		std::vector<Effectstruct> effects;
		int endFrame;
	};

private:
	//シングルトンパターン
	Effect() {};

public:
	virtual ~Effect();

	//コピーコンストラクタから実態の生成ができてしまうため
	//コピーコンストラクタを禁止する
	Effect(const Effect&) = delete;
	Effect& operator=(const Effect&) = delete;
	Effect(Effect&&) = delete;
	Effect& operator=(const Effect&&) = delete;

	/// <summary>
	/// EffectはGetInstance()を通した参照からしか利用できない
	/// </summary>
	/// <returns></returns>
	static Effect& GetInstance()
	{
		if (!m_instance)
		{
			m_instance = new Effect;
		}

		return *m_instance;
	}

	//メモリリークを防ぐ
	static void Destroy()
	{
		delete m_instance;
		m_instance = nullptr;
	}

public:
	//エフェクトをロードする
	void EffectLoad(std::string name, const char* path, int endFrame, float scale = 1.0f);

	//更新
	void Update();

	//描画
	void Draw();

	//エフェクトを生成する
	void EffectCreate(std::string name, VECTOR pos);

private:
	//Singletonのポインタがプログラム起動時に一つ作られるようにする
	static Effect* m_instance;

private:
	//エフェクトのハンドル
	std::map<std::string, std::shared_ptr<EffectEmitter>> m_effect;
};

