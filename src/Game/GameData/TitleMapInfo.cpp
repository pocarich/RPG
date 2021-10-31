#include"../header/TitleMapInfo.h"
#include"../header/Function.h"

int TitleMapInfo::mapChip[60][Define::WINDOW_WIDTH / Define::MASU_SIZE];
int TitleMapInfo::mapObject[60][Define::WINDOW_WIDTH / Define::MASU_SIZE];

void TitleMapInfo::Load()
{
	ifstream ifs;
	string readString;
	stringstream mapCSV;

	mapCSV << "data/csv/map/chip/TitleMap.csv";
	ifs.open(mapCSV.str());

	assert(!ifs.fail() && "TitleMapInfo::Load()");

	for (int i = 0; i < 3; i++)
	{
		getline(ifs, readString);
	}

	for (int i = 0; i < 60; i++)
	{
		getline(ifs, readString);
		vector<string> element = Function::split(readString, ',');
		assert(element.size() == 25&&"MapInfoList::Load() mapChipÇÃì«Ç›çûÇ›Ç…é∏îsÇµÇ‹ÇµÇΩÅB");
		for (int j = 0; j != element.size(); j++)
		{
			stringstream ss;
			ss << element[j];
			ss >> mapChip[i][j];
		}
	}

	getline(ifs, readString);

	for (int i = 0; i < 60; i++)
	{
		getline(ifs, readString);
		vector<string> element = Function::split(readString, ',');
		assert(element.size() == 25&&"MapInfoList::Load() mapObject1ÇÃì«Ç›çûÇ›Ç…é∏îsÇµÇ‹ÇµÇΩÅB");
		for (int j = 0; j != element.size(); j++)
		{
			stringstream ss;
			ss << element[j];
			ss >> mapObject[i][j];
		}
	}

	ifs.close();
}