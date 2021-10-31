#include"../header/BattleEffectP000.h"
#include"../header/PlayerMap.h"
#include"../header/EnemyMap.h"

BattleEffectP000::BattleEffectP000(PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList,list<BattleEffectPtr>& battleEffectList, list<EnemyMapPtr>& enemyMapList, int sourceID, Vector2<int> masuPosition, Direction direction, Vector2<double>&camera, int& mapNum, Vector2<double>& playerPosition) :BattleEffect(playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, ObjectType::PLAYER, sourceID, masuPosition, direction, camera, mapNum, TargetType::ENEMY),playerPosition(playerPosition)
{

}

BattleEffectP000::~BattleEffectP000()
{

}

void BattleEffectP000::Update()
{
	effectTimer++;
}

void BattleEffectP000::Draw()
{
	DrawRotaGraphF((float)playerPosition.x-camera.x, (float)playerPosition.y-camera.y, 1.0, 0.0, graph[1][effectTimer%15], TRUE);
}