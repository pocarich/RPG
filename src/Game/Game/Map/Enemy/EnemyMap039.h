#pragma once

#include"EnemyMap.h"

class EnemyMap039 :public EnemyMap
{
	int tempAttackKind;
private:
	void UpdateTempAttackKind();
public:
	EnemyMap039(PlayerData* playerData, PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<EnemyMapPtr>& enemyMapList, list<PeopleMapPtr>& peopleMapList,int id,Vector2<int> masuPosition, Vector2<double>& camera, list<BattleEffectPtr>& battleEffectList, list<TextUIPtr>& textUIList, list<DropItemPtr>& dropItemList,int& mapNum);
	~EnemyMap039();
	void UpdateNotice()override;
};