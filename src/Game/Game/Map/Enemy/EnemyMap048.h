#pragma once

#include"EnemyMap.h"

class EnemyMap048 :public EnemyMap
{
public:
	EnemyMap048(PlayerData* playerData, PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<EnemyMapPtr>& enemyMapList, list<PeopleMapPtr>& peopleMapList,int id,Vector2<int> masuPosition, Vector2<double>& camera, list<BattleEffectPtr>& battleEffectList, list<TextUIPtr>& textUIList, list<DropItemPtr>& dropItemList,int& mapNum);
	~EnemyMap048();
	void UpdateNotice()override;
	void Draw()override;
};