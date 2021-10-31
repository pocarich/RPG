#pragma once

#include"BossMap.h"

class BossMap005 :public BossMap
{
private:
	void UpdateTempAttackKind();
public:
	BossMap005(PlayerData* playerData, PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<EnemyMapPtr>& enemyMapList, list<PeopleMapPtr>& peopleMapList, list<BattleEffectPtr>& battleEffectList, list<TextUIPtr>& textUIList, list<DropItemPtr>& dropItemList, int id, Vector2<int> masuPosition, Vector2<double>& camera, int& mapNum, int standFlag,int specialEventNum);
	~BossMap005();
	void UpdateNotice()override;
};