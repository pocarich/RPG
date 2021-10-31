#pragma once

#include"EnemyMap.h"

class EnemyMap012 :public EnemyMap
{
private:
	static const int randomMoveCount;
private:
	int tempAttackKind;
	int randomMoveCounter;
private:
	void UpdateTempAttackKind();
public:
	EnemyMap012(PlayerData* playerData, PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<EnemyMapPtr>& enemyMapList, list<PeopleMapPtr>& peopleMapList, int id, Vector2<int> masuPosition, Vector2<double>& camera, list<BattleEffectPtr>& battleEffectList, list<TextUIPtr>& textUIList, list<DropItemPtr>& dropItemList, int& mapNum);
	~EnemyMap012();
	void UpdateNotice()override;
};