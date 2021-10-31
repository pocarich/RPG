#include"../header/ObjectMap000.h"

ObjectMap000::ObjectMap000(Vector2<int> masuPosition, PlayerData* playerData, PlayerMap* playerMap, list<TextUIPtr>& textUIList, list<BattleEffectPtr>& battleEffectList, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<PeopleMapPtr>& peopleMapList, list<EnemyMapPtr>& enemyMapList, list<DropItemPtr>& dropItemMapList, int& mapNum, Vector2<double>& camera) :ObjectMap(0, masuPosition, playerData, playerMap, textUIList, battleEffectList, bossMapList, objectMapList, peopleMapList, enemyMapList, dropItemMapList, mapNum, camera)
{

}

void ObjectMap000::Draw()
{
	DrawRotaGraphF(position.x - camera.x, position.y - camera.y, 1.0, 0.0, graph[graphKindList[kind]][(animationTimer / 3) % 15], TRUE);
}