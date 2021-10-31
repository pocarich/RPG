#include"../header/PlayerData.h"
#include"../header/Function.h"

PlayerData::PlayerData(array<SaveData, Define::SAVE_DATA_NUM>& saveDataList,int loadDataNum)
{
	for (int i = 0; i < Define::CHARACTER_NUM; i++)
	{
		existCharacterFlag[i] = false;
		characterStatusList.push_back(new CharacterStatus(i,saveDataList,loadDataNum));
	}

	playerStatus = new PlayerStatus(saveDataList, loadDataNum);

	playTime = 0;

	for (int i = 0; i < Define::RECIPE_NUM; i++)
	{
		haveRecipe.push_back(false);
	}
	for (int i = 0; i < Define::ACHIEVE_NUM; i++)
	{
		achieveFlag.push_back(false);
	}
	for (int i = 0; i != flagList.size(); i++)
	{
		flagList[i] = false;
	}
	AddCharacter(0);

	if (loadDataNum != -1)
	{
		for (int i = 0; i < Define::RECIPE_NUM; i++)
		{
			haveRecipe[i] = saveDataList[loadDataNum].haveRecipe[i];
		}
		for (int i = 0; i < Define::ACHIEVE_NUM; i++)
		{
			achieveFlag[i] = saveDataList[loadDataNum].achieveFlag[i];
		}
		for (int i = 0; i < Define::CHARACTER_NUM; i++)
		{
			existCharacterFlag[i] = saveDataList[loadDataNum].existCharacterFlag[i];
		}
		for (int i = 0; i < Define::FLAG_NUM; i++)
		{
			flagList[i] = saveDataList[loadDataNum].flagList[i];
		}
		playTime = saveDataList[loadDataNum].playTime;

		if (flagList[2])
		{
			AddCharacter(1);
		}
	}
}

PlayerData::~PlayerData()
{
	delete playerStatus;

	for (int i = 0; i != characterStatusList.size(); i++)
	{
		delete characterStatusList[i];
	}
	characterStatusList.clear();
}

void PlayerData::Save(array<SaveData, Define::SAVE_DATA_NUM>& saveDataList, int saveDataNum)
{
	playerStatus->Save(saveDataList, saveDataNum);
	for (auto obj : characterStatusList)
	{
		obj->Save(saveDataList, saveDataNum);
	}

	for (int i = 0; i < Define::RECIPE_NUM; i++)
	{
		saveDataList[saveDataNum].haveRecipe[i] = haveRecipe[i];
	}
	for (int i = 0; i < Define::ACHIEVE_NUM; i++)
	{
		saveDataList[saveDataNum].achieveFlag[i] = achieveFlag[i];
	}
	for (int i = 0; i < Define::CHARACTER_NUM; i++)
	{
		saveDataList[saveDataNum].existCharacterFlag[i] = existCharacterFlag[i];
	}
	for (int i = 0; i < Define::FLAG_NUM; i++)
	{
		saveDataList[saveDataNum].flagList[i] = flagList[i];
	}
	saveDataList[saveDataNum].playTime = playTime;
}

void PlayerData::AddCharacter(int id)
{
	existCharacterFlag[id] = true;
}

void PlayerData::OutCharacter(int id)
{
	existCharacterFlag[id] = false;
}

void PlayerData::UseINN()
{
	for (auto& obj : characterStatusList)
	{
		obj->UseINN();
	}
}

void PlayerData::UpdatePlayTime()
{
	playTime++;
}

void PlayerData::KillMonster(int kind)
{
	
}

void PlayerData::KillBoss(int kind)
{

}

void PlayerData::Update()
{
	UpdatePlayTime();
	CheckFlag();
	CheckAddCharacter();
	CheckAchieve();
}

void PlayerData::CheckAddCharacter()
{
	if (!existCharacterFlag[1])
	{
		if (flagList[2])
		{
			AddCharacter(1);
		}
	}
}

void PlayerData::CheckFlag()
{
	flagList[1] = playerStatus->GetHoldItemList()[97] >= 3 || flagList[2];
	flagList[50] = playerStatus->GetHoldItemList()[108] > 0;
	flagList[51] = playerStatus->GetHoldItemList()[109] > 0;
	flagList[52] = playerStatus->GetHoldItemList()[110] > 0;
	flagList[53] = playerStatus->GetHoldItemList()[111] > 0;
	flagList[54] = flagList[50] && flagList[51] && flagList[52] && flagList[53];
	flagList[55] = playerStatus->GetHoldItemList()[101] > 0;
	flagList[56] = playerStatus->GetHoldItemList()[102] > 0;
	flagList[57] = playerStatus->GetHoldItemList()[118] > 0;
}

void PlayerData::CheckAchieve()
{
	if (!achieveFlag[0])
	{
		bool flag = false;
		for (int i = 100; i <= 143; i++)
		{
			if (flagList[i])
			{
				flag = true;
			}
		}
		if (flag)
		{
			achieveFlag[0] = true;
			getAchieve.push_back(0);
		}
	}
	if (!achieveFlag[1])
	{
		bool flag = false;
		for (int i = 300; i <= 331; i++)
		{
			if (flagList[i])
			{
				flag = true;
			}
		}
		if (flag)
		{
			achieveFlag[1] = true;
			getAchieve.push_back(1);
		}
	}
	if (!achieveFlag[2])
	{
		bool flag = true;
		for (int i = 100; i <= 143; i++)
		{
			if (!flagList[i])
			{
				flag = false;
			}
		}
		if (flag)
		{
			achieveFlag[2] = true;
			getAchieve.push_back(2);
		}
	}
	if (!achieveFlag[3])
	{
		bool flag = true;
		for (int i = 300; i <= 331; i++)
		{
			if (!flagList[i])
			{
				flag = false;
			}
		}
		if (flag)
		{
			achieveFlag[3] = true;
			getAchieve.push_back(3);
		}
	}
	if (!achieveFlag[4])
	{
		if (flagList[2])
		{
			achieveFlag[4] = true;
			getAchieve.push_back(4);
		}
	}
	if (!achieveFlag[5])
	{
		if (flagList[5])
		{
			achieveFlag[5] = true;
			getAchieve.push_back(5);
		}
	}
	if (!achieveFlag[6])
	{
		if (flagList[7])
		{
			achieveFlag[6] = true;
			getAchieve.push_back(6);
		}
	}
	if (!achieveFlag[7])
	{
		if (flagList[10])
		{
			achieveFlag[7] = true;
			getAchieve.push_back(7);
		}
	}
	if (!achieveFlag[8])
	{
		if (flagList[31])
		{
			achieveFlag[8] = true;
			getAchieve.push_back(8);
		}
	}
	if (!achieveFlag[9])
	{
		if (flagList[50])
		{
			achieveFlag[9] = true;
			getAchieve.push_back(9);
		}
	}
	if (!achieveFlag[10])
	{
		if (flagList[51])
		{
			achieveFlag[10] = true;
			getAchieve.push_back(10);
		}
	}
	if (!achieveFlag[11])
	{
		if (flagList[52])
		{
			achieveFlag[11] = true;
			getAchieve.push_back(11);
		}
	}
	if (!achieveFlag[12])
	{
		if (flagList[53])
		{
			achieveFlag[12] = true;
			getAchieve.push_back(12);
		}
	}
	if (!achieveFlag[13])
	{
		if (flagList[578] && flagList[577] && flagList[573] && flagList[570])
		{
			achieveFlag[13] = true;
			getAchieve.push_back(13);
		}
	}
	if (!achieveFlag[14])
	{
		bool flag = true;
		for (int i = 500; i <= 581; i++)
		{
			if (!flagList[i])
			{
				flag = false;
			}
		}
		if (flag)
		{
			achieveFlag[14] = true;
			getAchieve.push_back(14);
		}
	}
	if (!achieveFlag[15])
	{
		if (flagList[900])
		{
			achieveFlag[15] = true;
			getAchieve.push_back(15);
		}
	}
	if (!achieveFlag[16])
	{
		bool flag = true;
		for (int i = 0; i <= 15; i++)
		{
			if (!achieveFlag[i])
			{
				flag = false;
			}
		}
		if (flag)
		{
			achieveFlag[16] = true;
			getAchieve.push_back(16);
		}
	}
}

void PlayerData::GetRecipe(int itemKind)
{
	switch (itemKind)
	{
	case 104:
		haveRecipe[0] = true;
		haveRecipe[1] = true;
		haveRecipe[2] = true;
		haveRecipe[3] = true;
		haveRecipe[12] = true;
		haveRecipe[16] = true;
		haveRecipe[30] = true;
		break;
	case 105:
		haveRecipe[4] = true;
		haveRecipe[5] = true;
		haveRecipe[6] = true;
		haveRecipe[7] = true;
		haveRecipe[13] = true;
		haveRecipe[17] = true;
		haveRecipe[20] = true;
		haveRecipe[21] = true;
		haveRecipe[22] = true;
		haveRecipe[23] = true;
		haveRecipe[24] = true;
		haveRecipe[25] = true;
		haveRecipe[31] = true;
		break;
	case 106:
		haveRecipe[8] = true;
		haveRecipe[9] = true;
		haveRecipe[10] = true;
		haveRecipe[14] = true;
		haveRecipe[18] = true;
		haveRecipe[26] = true;
		haveRecipe[27] = true;
		haveRecipe[28] = true;
		haveRecipe[29] = true;
		break;
	case 107:
		haveRecipe[11] = true;
		haveRecipe[15] = true;
		haveRecipe[19] = true;
		break;
	}
}