#pragma once

#include"ObjectMap.h"

class ObjectMap000 :public ObjectMap
{
public:
	ObjectMap000(Vector2<int> masuPosition, PlayerData* playerData, PlayerMap* playerMap, list<TextUIPtr>& textUIList, list<BattleEffectPtr>& battleEffectList, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<PeopleMapPtr>& peopleMapList, list<EnemyMapPtr>& enemyMapList, list<DropItemPtr>& dropItemMapList, int& mapNum, Vector2<double>& camera);
	void Draw()override;
};