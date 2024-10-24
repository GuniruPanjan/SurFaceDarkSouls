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

}
