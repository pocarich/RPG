#pragma once

#include"EnemyMap.h"

class EnemyMap027 :public EnemyMap
{
private:
	static const int randomMoveCount = 3;
private:
	int randomMoveCounter;
	int tempAttackKind;
private:
	void UpdateTempAttackKind();
public:
	EnemyMap027(PlayerData* playerData, PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<EnemyMapPtr>& enemyMapList, list<PeopleMapPtr>& peopleMapList,int id,Vector2<int> masuPosition, Vector2<double>& camera, list<BattleEffectPtr>& battleEffectList, list<TextUIPtr>& textUIList, list<DropItemPtr>& dropItemList,int& mapNum);
	~EnemyMap027();
	void UpdateNotice()override;
};