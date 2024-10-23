#include "CsvLoad.h"
#include <vector>
#include <sstream>
#include <fstream>
#include <cassert>

CsvLoad* CsvLoad::m_instance = nullptr;

namespace
{
	//csvƒf[ƒ^‚Ì,‚Å•¶š—ñ‚ğ•ªŠ„‚·‚é
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

void CsvLoad::StatusLoad(CharacterBase::Status& data, const char* charaName)
{
}

void CsvLoad::AnimDataLoad(std::string charaName, std::map<std::string, int>& anim)
{
}
