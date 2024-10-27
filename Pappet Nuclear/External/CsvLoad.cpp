#include "CsvLoad.h"
#include <vector>
#include <sstream>
#include <fstream>
#include <cassert>

CsvLoad* CsvLoad::m_instance = nullptr;

namespace
{
	//csv�f�[�^��,�ŕ�����𕪊�����
	std::vector<std::string> Split(std::string& input, char delimiter)
	{
		std::istringstream stream(input);
		std::string field;
		std::vector<std::string> result;
		while (getline(stream, field, delimiter))
		{
			result.push_back(field);
		}
		return result;
	}

	const std::string cFrontPathName = "Data/Csv";
	const std::string cBackPathName = ".csv";
}

/// <summary>
/// �X�e�[�^�X��񃍁[�h
/// </summary>
/// <param name="data">�X�e�[�^�X���</param>
/// <param name="charaName">�L�����N�^�[�̖��O</param>
void CsvLoad::StatusLoad(CharacterBase::Status& data, const char* charaName)
{
	//�ꎞ�ۑ��pstring
	std::string strBuf;
	//�J���}�����ꎞ�ۑ��pstring
	std::vector<std::string> strConmaBuf;

	//�t�@�C���ǂݍ���
	std::ifstream cfs("Data/Csv/status.csv");
	if (!cfs)
	{
		assert(false);
		return;
	}

	//�����擾�ł������ǂ����̃t���O
	bool isGet = false;

	//�Ή���񂪓����Ă��邽�ߖ�������
	std::getline(cfs, strBuf);

	while (getline(cfs, strBuf))
	{
		//�擾������������J���}��؂�̔z��(���Q)�ɂ���
		strConmaBuf = Split(strBuf, ',');

		//0 : �L�����N�^�[��
		//1 : �̗�
		//2 : �X�^�~�i
		//3 : �U����
		//4 : �ؗ�
		//5 : �Z��
		//6 : �h���
		//7 : ���x
		//8 : �R�A

		//�w�肵���L�����N�^�[���ƈ�v����f�[�^������Ώ����擾����
		if (strConmaBuf[DataLoad::CsvStatus::name] == charaName)
		{
			isGet = true;
			data.s_hp = std::stoi(strConmaBuf[DataLoad::CsvStatus::hp]);
			data.s_stamina = std::stoi(strConmaBuf[DataLoad::CsvStatus::stamina]);
			data.s_attack = std::stoi(strConmaBuf[DataLoad::CsvStatus::attack]);
			data.s_muscle = std::stoi(strConmaBuf[DataLoad::CsvStatus::muscle]);
			data.s_skill = std::stoi(strConmaBuf[DataLoad::CsvStatus::skill]);
			data.s_defense = std::stoi(strConmaBuf[DataLoad::CsvStatus::defense]);
			data.s_speed = std::stoi(strConmaBuf[DataLoad::CsvStatus::speed]);
			data.s_core = std::stoi(strConmaBuf[DataLoad::CsvStatus::core]);		
		}
	}

	if (!isGet)
	{
		assert(0 && "�w�肵���L�����N�^�[���̏����擾�ł��Ȃ�����");
	}

	return;
}

/// <summary>
/// �A�j���[�V������񃍁[�h
/// </summary>
/// <param name="charaName">�ǂݍ��݂����L�����N�^�[��</param>
/// <param name="anim">�i�[����A�j���[�V�������</param>
void CsvLoad::AnimDataLoad(std::string charaName, std::map<std::string, int>& anim)
{
	//�ꎞ�ۑ��pstring
	std::string strBuf;
	//�J���}�����ꎞ�ۑ��pstring
	std::vector<std::string> strConmaBuf;

	//�t�@�C���ǂݍ���
	std::ifstream ifs("Data/Csv/animation.csv");
	if (!ifs)
	{
		assert(false);
		return;
	}

	//�����擾�ł������ǂ����̃t���O
	bool isGet = false;

	//�A�j���[�V�������ۑ��pstring
	std::vector<std::string> animationNameBuf;

	//�A�j���[�V�����̖��O��ۑ�����
	std::getline(ifs, strBuf);
	animationNameBuf = Split(strBuf, ',');

	while (std::getline(ifs, strBuf))
	{
		//�O�̃��[�v�ł��łɎ擾�ł��Ă����烋�[�v���I���
		if (isGet)
		{
			break;
		}

		//�擾������������J���}��؂�̔z��(���Q)�ɂ���
		strConmaBuf = Split(strBuf, ',');

		//�ǂݍ��݂����L�����N�^�[���Ɠǂݍ��񂾃L�����N�^�[���������Ȃ�
		if (strConmaBuf[0] == charaName)
		{
			//�A�j���[�V���������i�[���Ă���
			isGet = true;
			for (int i = 0; i < strConmaBuf.size(); i++)
			{
				//�A�j���[�V����Idx��-1�ȉ��������ꍇ���݂��Ȃ����ߒǉ����Ȃ�
				if (std::stoi(strConmaBuf[i]) != -1)
				{
					anim[animationNameBuf[i]] = std::stoi(strConmaBuf[i]);
				}
			}
		}
	}

	if (!isGet)
	{
		assert(0 && "�w�肵���L�����N�^�[���̃A�j���[�V���������擾�ł��Ȃ�");
	}

	return;
}
