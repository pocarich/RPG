#pragma once

#include"Define.h"
#include"PlayerStatus.h"
#include"CharacterStatus.h"
#include"SaveData.h"

class PlayerData
{
private:
	PlayerStatus* playerStatus;
	vector<CharacterStatus*> characterStatusList;
	vector<bool> haveRecipe;
	vector<bool> achieveFlag;
	bool existCharacterFlag[Define::CHARACTER_NUM];
	int playTime;
	array<bool, Define::FLAG_NUM> flagList;
	vector<int> getAchieve;
private:
	void CheckFlag();
	void CheckAchieve();
	void UpdatePlayTime();
	void CheckAddCharacter();
public:
	PlayerData(array<SaveData, Define::SAVE_DATA_NUM>& saveDataList,int loadDataNum);
	~PlayerData();
	void Save(array<SaveData, Define::SAVE_DATA_NUM>& saveDataList,int saveDataNum);
	void GetRecipe(int itemKind);
	void Update();
	void AddCharacter(int id);
	void OutCharacter(int id);
	void UseINN();
	void KillBoss(int kind);
	void KillMonster(int kind);
	void StandFlag(int num) { flagList[num] = true; }
	void ResetGetAchieve() { getAchieve.clear(); }
	PlayerStatus* GetPlayerStatus()const { return playerStatus; }
	vector<CharacterStatus*>& GetCharacterStatusList() { return characterStatusList; }
	int GetPlayTime()const { return playTime; }
	const vector<bool>& GetHaveRecipe()const { return haveRecipe; }
	const vector<bool>& GetAchieveFlag()const { return achieveFlag; }
	const bool* GetExistCharacterFlag()const { return existCharacterFlag; }
	const array<bool, Define::FLAG_NUM>& GetFlagList()const { return flagList; }
	const vector<int>& GetGetAchieve()const { return getAchieve; }
};