#pragma once

#include"ObjectMap.h"

class ObjectMap001 :public ObjectMap
{
public:
	ObjectMap001(Vector2<int> masuPosition, PlayerData* playerData, PlayerMap* playerMap, list<TextUIPtr>& textUIList, list<BattleEffectPtr>& battleEffectList, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<PeopleMapPtr>& peopleMapList, list<EnemyMapPtr>& enemyMapList, list<DropItemPtr>& dropItemMapList, int& mapNum, Vector2<double>& camera);
	void Draw()override;
};