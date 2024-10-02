#pragma once

template <class _Ty> 
/// <summary>
/// �V���O���g���쐬
/// </summary>
class Singleton
{
public:

	typedef _Ty InstanceType;

private:
	//�N���X�O����̃C���X�^���X�̍쐬�E�폜���֎~
	Singleton() = default;
	~Singleton(){}

	//�R�s�[�R���X�g���N�^�̋֎~
	Singleton(const Singleton&) = delete;
	//���[�u�R���X�g���N�^�̋֎~
	Singleton(const Singleton&&) = delete;
	//������Z�q�̋֎~
	Singleton operator= (const Singleton&) = delete;
	Singleton operator= (const Singleton&&) = delete;

	static InstanceType* _pInstance;    //�B��̃C���X�^���X

public:

	//�C���X�^���X���������x�g���Ă������C���X�^���X�������ł���
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

