#pragma once

#include"EnemyMap.h"

class EnemyMap037 :public EnemyMap
{
	int tempAttackKind;
private:
	void UpdateTempAttackKind();
public:
	EnemyMap037(PlayerData* playerData, PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<EnemyMapPtr>& enemyMapList, list<PeopleMapPtr>& peopleMapList,int id,Vector2<int> masuPosition, Vector2<double>& camera, list<BattleEffectPtr>& battleEffectList, list<TextUIPtr>& textUIList, list<DropItemPtr>& dropItemList,int& mapNum);
	~EnemyMap037();
	void UpdateNotice()override;
};