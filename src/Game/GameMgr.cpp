#include"../header/GameMgr.h"
#include"../header/KeyBoard.h"
#include"../header/FontMgr.h"
#include"../header/ColorMgr.h"
#include"../header/Function.h"

GameMgr::GameMgr()
{
	title = nullptr;
	state = GameState::TITLE;
	loadDataNum = -1;
	LoadData();
}

GameMgr::~GameMgr()
{
	if (title != nullptr)
		delete title;
	if (game != nullptr)
		delete game;
}

void GameMgr::Main()
{
	switch (state)
	{
	case GameState::TITLE:	TitleFunc();	break;
	case GameState::GAME:	GameFunc();		break;
	}
}

void GameMgr::TitleFunc()
{
	if (title == nullptr)
	{
		title = new Title(saveDataList);
	}

	title->Main();

	if (title->GetStateEndFlag())
	{
		loadDataNum = title->GetLoadDataNum();
		delete title;
		title = nullptr;
		state = GameState::GAME;
	}
}

void GameMgr::GameFunc()
{
	if (game == nullptr)
	{
		game = new Game(saveDataList,loadDataNum);
	}
	
	game->Main();
	if (game->GetSaveDataNum() != -1)
	{
		Save(game->GetSaveDataNum());
		game->ResetSaveDataNum();
	}

	if (game->GetStateEndFlag())
	{
		delete game;
		game = nullptr;
		state = GameState::TITLE;
	}
}

void GameMgr::LoadData()
{
	for (int i = 0; i < Define::SAVE_DATA_NUM; i++)
	{
		saveDataList[i].exist = false;

		stringstream file;
		file << "data/SaveData/saveData" << Function::NumToStringFillZero(i, 2) << ".txt";

		ifstream ifs(file.str());

		assert(!ifs.fail() && "PlayerData::Load()");

		string str;

		getline(ifs, str);

		if (str == "#")
		{
			continue;
		}

		saveDataList[i].exist = true;

		{
			stringstream ss;
			ss << str;
			ss >> saveDataList[i].playTime;
		}

		for (int j = 0; j < Define::RECIPE_NUM; j++)
		{
			getline(ifs, str);
			{
				int n;
				stringstream ss;
				ss << str;
				ss >> n;
				saveDataList[i].haveRecipe[j] = n == 1 ? true : false;
			}
		}
		for (int j = 0; j < Define::ACHIEVE_NUM; j++)
		{
			getline(ifs, str);
			{
				int n;
				stringstream ss;
				ss << str;
				ss >> n;
				saveDataList[i].achieveFlag[j] = n == 1 ? true : false;
			}
		}
		for (int j = 0; j < Define::CHARACTER_NUM; j++)
		{
			getline(ifs, str);
			{
				int n;
				stringstream ss;
				ss << str;
				ss >> n;
				saveDataList[i].existCharacterFlag[j] = n == 1 ? true : false;
			}
		}
		for (int j = 0; j < Define::FLAG_NUM; j++)
		{
			getline(ifs, str);
			{
				int n;
				stringstream ss;
				ss << str;
				ss >> n;
				saveDataList[i].flagList[j] = n == 1 ? true : false;
			}
		}

		for (int j = 0; j < Define::CHARACTER_NUM; j++)
		{
			getline(ifs, str);
			{
				int n;
				stringstream ss;
				ss << str;
				ss >> saveDataList[i].Lv[j];
			}
		}
		for (int j = 0; j < Define::CHARACTER_NUM; j++)
		{
			getline(ifs, str);
			{
				int n;
				stringstream ss;
				ss << str;
				ss >> saveDataList[i].HP[j];
			}
		}
		for (int j = 0; j < Define::CHARACTER_NUM; j++)
		{
			getline(ifs, str);
			{
				int n;
				stringstream ss;
				ss << str;
				ss >> saveDataList[i].SP[j];
			}
		}
		for (int j = 0; j < Define::CHARACTER_NUM; j++)
		{
			getline(ifs, str);
			{
				int n;
				stringstream ss;
				ss << str;
				ss >> saveDataList[i].EXP[j];
			}
		}
		for (int j = 0; j < Define::CHARACTER_NUM; j++)
		{
			getline(ifs, str);
			{
				int n;
				stringstream ss;
				ss << str;
				ss >> saveDataList[i].weapon[j];
			}
		}
		for (int j = 0; j < Define::CHARACTER_NUM; j++)
		{
			getline(ifs, str);
			{
				int n;
				stringstream ss;
				ss << str;
				ss >> saveDataList[i].head[j];
			}
		}
		for (int j = 0; j < Define::CHARACTER_NUM; j++)
		{
			getline(ifs, str);
			{
				int n;
				stringstream ss;
				ss << str;
				ss >> saveDataList[i].chest[j];
			}
		}
		for (int j = 0; j < Define::CHARACTER_NUM; j++)for (int k = 0; k < 3; k++)
		{
			getline(ifs, str);
			{
				int n;
				stringstream ss;
				ss << str;
				ss >> saveDataList[i].accessory[j][k];
			}
		}
		for (int j = 0; j < Define::CHARACTER_NUM; j++)for (int k = 0; k < 3; k++)
		{
			getline(ifs, str);
			{
				int n;
				stringstream ss;
				ss << str;
				ss >> saveDataList[i].setSkill[j][k];
			}
		}
		for (int j = 0; j < Define::CHARACTER_NUM; j++)for (int k = 0; k < Define::PLAYER_SKILL_MAX; k++)
		{
			getline(ifs, str);
			{
				int n;
				stringstream ss;
				ss << str;
				ss >> saveDataList[i].skillLevel[j][k];
			}
		}
		for (int j = 0; j < Define::CHARACTER_NUM; j++)for (int k = 0; k < Define::PLAYER_SKILL_MAX; k++)
		{
			getline(ifs, str);
			{
				int n;
				stringstream ss;
				ss << str;
				ss >> saveDataList[i].skillEXP[j][k];
			}
		}

		getline(ifs, str);
		{
			int n;
			stringstream ss;
			ss << str;
			ss >> saveDataList[i].money;
		}
		for (int j = 0; j < Define::ITEM_KIND; j++)
		{
			getline(ifs, str);
			{
				int n;
				stringstream ss;
				ss << str;
				ss >> saveDataList[i].holdItemList[j];
			}
		}
		getline(ifs, str);
		{
			int n;
			stringstream ss;
			ss << str;
			ss >> saveDataList[i].mapNum;
		}
		getline(ifs, str);
		{
			int n;
			stringstream ss;
			ss << str;
			ss >> saveDataList[i].id;
		}
		getline(ifs, str);
		{
			int n;
			stringstream ss;
			ss << str;
			ss >> saveDataList[i].masuPosition.x;
		}
		getline(ifs, str);
		{
			int n;
			stringstream ss;
			ss << str;
			ss >> saveDataList[i].masuPosition.y;
		}
	}
}

void GameMgr::Save(int saveDataNum)
{
	game->Save(saveDataNum);
	saveDataList[saveDataNum].exist = true;

	stringstream file;
	file << "data/SaveData/saveData" << Function::NumToStringFillZero(saveDataNum, 2) << ".txt";

	ofstream ofs(file.str());

	assert(!ofs.fail() && "PlayerData::Load()");

	ofs << saveDataList[saveDataNum].playTime << endl;

	for (int i = 0; i < Define::RECIPE_NUM; i++)
	{
		int num = saveDataList[saveDataNum].haveRecipe[i] ? 1 : 0;
		ofs << num << endl;
	}
	for (int i = 0; i < Define::ACHIEVE_NUM; i++)
	{
		int num = saveDataList[saveDataNum].achieveFlag[i];
		ofs << num << endl;
	}
	for (int i = 0; i < Define::CHARACTER_NUM; i++)
	{
		int num = saveDataList[saveDataNum].existCharacterFlag[i];
		ofs << num << endl;
	}
	for (int i = 0; i < Define::FLAG_NUM; i++)
	{
		int num = saveDataList[saveDataNum].flagList[i];
		ofs << num << endl;
	}
	for (int i = 0; i < Define::CHARACTER_NUM; i++)
	{
		ofs << saveDataList[saveDataNum].Lv[i] << endl;
	}
	for (int i = 0; i < Define::CHARACTER_NUM; i++)
	{
		ofs << saveDataList[saveDataNum].HP[i] << endl;
	}
	for (int i = 0; i < Define::CHARACTER_NUM; i++)
	{
		ofs << saveDataList[saveDataNum].SP[i] << endl;
	}
	for (int i = 0; i < Define::CHARACTER_NUM; i++)
	{
		ofs << saveDataList[saveDataNum].EXP[i] << endl;
	}
	for (int i = 0; i < Define::CHARACTER_NUM; i++)
	{
		ofs << saveDataList[saveDataNum].weapon[i] << endl;
	}
	for (int i = 0; i < Define::CHARACTER_NUM; i++)
	{
		ofs << saveDataList[saveDataNum].head[i] << endl;
	}
	for (int i = 0; i < Define::CHARACTER_NUM; i++)
	{
		ofs << saveDataList[saveDataNum].chest[i] << endl;
	}
	for (int i = 0; i < Define::CHARACTER_NUM; i++)for (int j = 0; j < 3;j++)
	{
		ofs << saveDataList[saveDataNum].accessory[i][j] << endl;
	}
	for (int i = 0; i < Define::CHARACTER_NUM; i++)for (int j = 0; j < 3; j++)
	{
		ofs << saveDataList[saveDataNum].setSkill[i][j] << endl;
	}
	for (int i = 0; i < Define::CHARACTER_NUM; i++)for (int j = 0; j < Define::PLAYER_SKILL_MAX; j++)
	{
		ofs << saveDataList[saveDataNum].skillLevel[i][j] << endl;
	}
	for (int i = 0; i < Define::CHARACTER_NUM; i++)for (int j = 0; j < Define::PLAYER_SKILL_MAX; j++)
	{
		ofs << saveDataList[saveDataNum].skillEXP[i][j] << endl;
	}
	ofs << saveDataList[saveDataNum].money << endl;
	for (int i = 0; i < Define::ITEM_KIND; i++)
	{
		ofs << saveDataList[saveDataNum].holdItemList[i] << endl;
	}
	ofs << saveDataList[saveDataNum].mapNum << endl;
	ofs << saveDataList[saveDataNum].id << endl;
	ofs << saveDataList[saveDataNum].masuPosition.x << endl;
	ofs << saveDataList[saveDataNum].masuPosition.y << endl;
}