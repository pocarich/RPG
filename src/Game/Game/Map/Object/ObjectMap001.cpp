#include"../header/ObjectMap001.h"

ObjectMap001::ObjectMap001(Vector2<int> masuPosition, PlayerData* playerData, PlayerMap* playerMap, list<TextUIPtr>& textUIList, list<BattleEffectPtr>& battleEffectList, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<PeopleMapPtr>& peopleMapList, list<EnemyMapPtr>& enemyMapList, list<DropItemPtr>& dropItemMapList, int& mapNum, Vector2<double>& camera) :ObjectMap(1, masuPosition, playerData, playerMap, textUIList, battleEffectList, bossMapList, objectMapList, peopleMapList, enemyMapList, dropItemMapList, mapNum, camera)
{

}

void ObjectMap001::Draw()
{
	DrawRotaGraphF(position.x - camera.x, position.y - camera.y, 1.0, 0.0, graph[graphKindList[kind]][0], TRUE);
}