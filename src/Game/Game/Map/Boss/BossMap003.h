#pragma once

#include"BossMap.h"

class BossMap003 :public BossMap
{
private:
private:
	bool firstSammonFlag;
	int subKind;
	bool comboFlag;
private:
	void UpdateTempAttackKind();
public:
	BossMap003(PlayerData* playerData, PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<EnemyMapPtr>& enemyMapList, list<PeopleMapPtr>& peopleMapList, list<BattleEffectPtr>& battleEffectList, list<TextUIPtr>& textUIList, list<DropItemPtr>& dropItemList, int id, Vector2<int> masuPosition, Vector2<double>& camera, int& mapNum, int standFlag, int specialEventNum);
	~BossMap003();
	void UpdateNotice()override;
};