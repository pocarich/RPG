#pragma once

#include"EnemyMap.h"

class EnemyMap033 :public EnemyMap
{
	int tempAttackKind;
private:
	void UpdateTempAttackKind(); 
public:
	EnemyMap033(PlayerData* playerData, PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<EnemyMapPtr>& enemyMapList, list<PeopleMapPtr>& peopleMapList,int id,Vector2<int> masuPosition, Vector2<double>& camera, list<BattleEffectPtr>& battleEffectList, list<TextUIPtr>& textUIList, list<DropItemPtr>& dropItemList,int& mapNum);
	~EnemyMap033();
	void UpdateNotice()override;
};