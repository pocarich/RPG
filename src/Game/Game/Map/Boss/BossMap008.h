#pragma once

#include"BossMap.h"

class BossMap008 :public BossMap
{
private:
	static const int apoInterval = 20;
private:
	bool firstApoFlag;
	bool firstRandLaserFlag;
	int subKind;
	int werpTime;
	int apoCounter;
private:
	void UpdateTempAttackKind();
	bool Werp(Vector2<int> werpPos, int werpStiffTime, double distance, bool equalDistance);
public:
	BossMap008(PlayerData* playerData, PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<EnemyMapPtr>& enemyMapList, list<PeopleMapPtr>& peopleMapList, list<BattleEffectPtr>& battleEffectList, list<TextUIPtr>& textUIList, list<DropItemPtr>& dropItemList, int id, Vector2<int> masuPosition, Vector2<double>& camera, int& mapNum, int standFlag, int specialEventNum);
	~BossMap008();
	void UpdateNotice()override;
};