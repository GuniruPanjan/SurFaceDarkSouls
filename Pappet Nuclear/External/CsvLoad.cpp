#include "CsvLoad.h"
#include <vector>
#include <sstream>
#include <fstream>
#include <cassert>

CsvLoad* CsvLoad::m_instance = nullptr;

namespace
{
	//csvデータの,で文字列を分割する
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
/// ステータス情報ロード
/// </summary>
/// <param name="data">ステータス情報</param>
/// <param name="charaName">キャラクターの名前</param>
void CsvLoad::StatusLoad(CharacterBase::Status& data, const char* charaName)
{
	//一時保存用string
	std::string strBuf;
	//カンマ分け一時保存用string
	std::vector<std::string> strConmaBuf;

	//ファイル読み込み
	std::ifstream cfs("Data/Csv/status.csv");
	if (!cfs)
	{
		assert(false);
		return;
	}

	//情報を取得できたかどうかのフラグ
	bool isGet = false;

	//対応情報が入っているため無視する
	std::getline(cfs, strBuf);

	while (getline(cfs, strBuf))
	{
		//取得した文字列をカンマ区切りの配列(情報群)にする
		strConmaBuf = Split(strBuf, ',');

		//0 : キャラクター名
		//1 : 体力
		//2 : スタミナ
		//3 : 攻撃力
		//4 : 筋力
		//5 : 技量
		//6 : 防御力
		//7 : 速度
		//8 : コア

		//指定したキャラクター名と一致するデータがあれば情報を取得する
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
		assert(0 && "指定したキャラクター名の情報を取得できなかった");
	}

	return;
}

/// <summary>
/// アニメーション情報ロード
/// </summary>
/// <param name="charaName">読み込みたいキャラクター名</param>
/// <param name="anim">格納するアニメーション情報</param>
void CsvLoad::AnimDataLoad(std::string charaName, std::map<std::string, int>& anim)
{
	//一時保存用string
	std::string strBuf;
	//カンマ分け一時保存用string
	std::vector<std::string> strConmaBuf;

	//ファイル読み込み
	std::ifstream ifs("Data/Csv/animation.csv");
	if (!ifs)
	{
		assert(false);
		return;
	}

	//情報を取得できたかどうかのフラグ
	bool isGet = false;

	//アニメーション名保存用string
	std::vector<std::string> animationNameBuf;

	//アニメーションの名前を保存する
	std::getline(ifs, strBuf);
	animationNameBuf = Split(strBuf, ',');

	while (std::getline(ifs, strBuf))
	{
		//前のループですでに取得できていたらループを終わる
		if (isGet)
		{
			break;
		}

		//取得した文字列をカンマ区切りの配列(情報群)にする
		strConmaBuf = Split(strBuf, ',');

		//読み込みたいキャラクター名と読み込んだキャラクター名が同じなら
		if (strConmaBuf[0] == charaName)
		{
			//アニメーション情報を格納していく
			isGet = true;
			for (int i = 0; i < strConmaBuf.size(); i++)
			{
				//アニメーションIdxが-1以下だった場合存在しないため追加しない
				if (std::stoi(strConmaBuf[i]) != -1)
				{
					anim[animationNameBuf[i]] = std::stoi(strConmaBuf[i]);
				}
			}
		}
	}

	if (!isGet)
	{
		assert(0 && "指定したキャラクター名のアニメーション情報を取得できない");
	}

	return;
}
