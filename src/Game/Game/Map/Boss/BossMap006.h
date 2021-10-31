#pragma once

#include"BossMap.h"

class BossMap006 :public BossMap
{
private:
	void UpdateTempAttackKind();
public:
	BossMap006(PlayerData* playerData, PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<EnemyMapPtr>& enemyMapList, list<PeopleMapPtr>& peopleMapList, list<BattleEffectPtr>& battleEffectList, list<TextUIPtr>& textUIList, list<DropItemPtr>& dropItemList, int id, Vector2<int> masuPosition, Vector2<double>& camera, int& mapNum, int standFlag,int specialEventNum);
	~BossMap006();
	void UpdateNotice()override;
};