#pragma once
#include "Character/CharacterBase.h"
#include <string>
#include <memory>

namespace DataLoad
{
	//�X�e�[�^�X���񋓌^
	enum CsvStatus : int
	{
		name,      //�L�����N�^�[��
		hp,        //�̗�
		stamina,   //�X�^�~�i
		attack,    //�U����
		muscle,    //�ؗ�
		skill,     //�Z��
		defense,   //�h���
		speed,     //���x
		core,      //�h���b�v�R�A
	};

	//�G�̐����ꏊ�̗񋓌^
	enum CsvEnemyStage : int
	{
		ID,         //�GID
		max,        //�G�̍ő�o����
		x,          //�G��X���W
		y,          //�G��Y���W
		z,          //�G��Z���W
	};
}

/// <summary>
/// Csv��ǂݍ��ރN���X
/// </summary>
class CsvLoad
{
private:
	//�V���O���g���ɂ��邽�߃R���X�g���N�^��private�ɒu��
	CsvLoad() {};

public:
	virtual ~CsvLoad() {};

	//�R�s�[�R���X�g���N�^���֎~����
	CsvLoad(const CsvLoad&) = delete;
	CsvLoad& operator = (const CsvLoad&) = delete;
	CsvLoad(CsvLoad&&) = delete;
	CsvLoad& operator = (const CsvLoad&&) = delete;

	/// <summary>
	/// GetInstance()��ʂ����Q�Ƃ��炵�����p�ł��Ȃ�
	/// </summary>
	/// <returns></returns>
	static CsvLoad& GetInstance()
	{
		if (!m_instance)
		{
			m_instance = new CsvLoad;
		}

		return *m_instance;
	}

	//���������[�N��h������
	static void Destroy()
	{
		delete m_instance;
		m_instance = nullptr;
	}

public:
	//�X�e�[�^�X��񃍁[�h
	void StatusLoad(CharacterBase::Status& data, const char* charaName);

	//�G������񃍁[�h
	//void EnemyDataLoad(const char* stageName, std::list<>)

	//�A�j���[�V������񃍁[�h
	void AnimDataLoad(std::string charaName, std::map<std::string, int>& anim);

private:
	//Singleton�̃|�C���^���v���O�����N�����Ɉ�����悤�ɂ���
	static CsvLoad* m_instance;
};

