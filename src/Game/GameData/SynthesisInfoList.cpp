#include"../header/SynthesisInfoList.h"
#include"../header/Function.h"

vector<SynthesisInfo> SynthesisInfoList::synthesisInfoList;

void SynthesisInfoList::Load()
{
	ifstream ifs;

	ifs.open("data/csv/data/item/SynthesisInfoList.csv");

	assert(!ifs.fail() && "SynthesisInfoList::Load()");

	string readString;

	getline(ifs, readString);

	while (getline(ifs, readString))
	{
		SynthesisInfo synthesisInfo;

		auto element = Function::split(readString, ',');
		assert(element.size() == 3 && "SynthesisInfoList::Load() サイズが不正です。");

		for (int i = 0; i != element.size(); i++)
		{
			stringstream ss;
			int num;
			ss << element[i];
			switch (i)
			{
			case 0:
				ss >> synthesisInfo.itemKind;
				break;
			case 1:
			{
				auto element2 = Function::split(ss.str(), '|');

				for (int l = 0; l != element2.size(); l++)
				{
					stringstream ss2;
					int num;
					ss2 << element2[l];
					ss2 >> num;
					synthesisInfo.neddIngredients.push_back(num);
				}
			}
			break;
			case 2:
			{
				auto element2 = Function::split(ss.str(), '|');
				for (int l = 0; l != element2.size(); l++)
				{
					stringstream ss2;
					int num;
					ss2 << element2[l];
					ss2 >> num;
					synthesisInfo.needNum.push_back(num);
				}
			}
			break;
			}
		}
		synthesisInfoList.push_back(synthesisInfo);
	}

	ifs.close();
}