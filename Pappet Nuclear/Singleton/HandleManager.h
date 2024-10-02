#pragma once
#include<string>
#include<list>

struct Handle
{
	std::string path;
	int handle;
	bool isEternal;
};


/// <summary>
/// �ǂݍ��ރ��f�����Ǘ�����N���X(�V���O���g��)
/// </summary>
class HandleManager
{

private:
	//�R���X�g���N�^��private�ɒu��
	HandleManager();
	//�f�X�g���N�^
	virtual ~HandleManager();

public:
	//�R�s�[�R���X�g���N�^���֎~����
	HandleManager(const HandleManager&) = delete;
	HandleManager& operator=(const HandleManager&) = delete;
	HandleManager(HandleManager&&) = delete;
	HandleManager& operator=(const HandleManager&&) = delete;

	//HandleManager��GetInstance()��ʂ����Q�Ƃ��炵�����p�ł��Ȃ�
	static HandleManager& GetInstance()
	{
		if (!m_instance)
		{
			m_instance = new HandleManager;
		}

		return *m_instance;
	}

	//���������[�N��h��
	static void Delete()
	{
		delete m_instance;
		m_instance = nullptr;
	}

public:
	//�w�肵���p�X�̃n���h�����擾����
	int GetModelHandle(std::string path, bool isEternal = false);
	//�p�X�̃��X�g����������
	void Clear();

private:
	//Singleton�̃|�C���^���v���O�����N�����Ɉ�����悤�ɂ���
	static HandleManager* m_instance;

private:
	std::list<Handle> m_handles;

};
