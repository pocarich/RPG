#pragma once

#include"EnemyMap.h"

class EnemyMap044 :public EnemyMap
{
private:
	static const int deathTime = 1200;
private:
	int tempAttackKind;
	int deathTimer;
private:
	void UpdateTempAttackKind();
public:
	EnemyMap044(PlayerData* playerData, PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<EnemyMapPtr>& enemyMapList, list<PeopleMapPtr>& peopleMapList, int id, Vector2<int> masuPosition, Vector2<double>& camera, list<BattleEffectPtr>& battleEffectList, list<TextUIPtr>& textUIList, list<DropItemPtr>& dropItemList, int& mapNum);
	~EnemyMap044();
	void UpdateNotice()override;
	void Update()override;
};