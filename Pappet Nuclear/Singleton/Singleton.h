#pragma once

template <class _Ty> 
/// <summary>
/// シングルトン作成
/// </summary>
class Singleton
{
public:

	typedef _Ty InstanceType;

private:
	//クラス外からのインスタンスの作成・削除を禁止
	Singleton() = default;
	~Singleton(){}

	//コピーコンストラクタの禁止
	Singleton(const Singleton&) = delete;
	//ムーブコンストラクタの禁止
	Singleton(const Singleton&&) = delete;
	//代入演算子の禁止
	Singleton operator= (const Singleton&) = delete;
	Singleton operator= (const Singleton&&) = delete;

	static InstanceType* _pInstance;    //唯一のインスタンス

public:

	//インスタンスを所得何度使っても同じインスタンスが所得できる
	static Singleton& GetInstance()
	{
		static Singleton s;
		return s;
	}

	static InstanceType* GetSingletonPtr(void)
	{
		if (!_pInstance) { _pInstance = new InstanceType(); }
		return _pInstance;
	}

};

template <class _Ty>
typename Singleton<_Ty>::InstanceType* Singleton<_Ty>::_pInstance = nullptr;

