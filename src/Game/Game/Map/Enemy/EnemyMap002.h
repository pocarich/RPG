#pragma once

#include"EnemyMap.h"

class EnemyMap002 :public EnemyMap
{
public:
	EnemyMap002(PlayerData* playerData, PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<EnemyMapPtr>& enemyMapList, list<PeopleMapPtr>& peopleMapList,int id,Vector2<int> masuPosition, Vector2<double>& camera, list<BattleEffectPtr>& battleEffectList, list<TextUIPtr>& textUIList, list<DropItemPtr>& dropItemList,int& mapNum);
	~EnemyMap002();
	void UpdateNotice()override;
	void Draw()override;
};