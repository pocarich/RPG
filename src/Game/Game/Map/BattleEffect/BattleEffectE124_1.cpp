#include"../header/BattleEffectE124_1.h"
#include"../header/PlayerMap.h"
#include"../header/EnemyMap.h"

BattleEffectE124_1::BattleEffectE124_1(BossStatus bossStatus, PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<BattleEffectPtr>& battleEffectList, list<EnemyMapPtr>& enemyMapList, int sourceID, Vector2<int> masuPosition, Direction direction, Vector2<double>&camera, int& mapNum) :BattleEffect(playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, ObjectType::PLAYER, sourceID, masuPosition, direction, camera, mapNum, TargetType::PLAYER), bossStatus(bossStatus)
{
	position = Vector2<double>(this->masuPosition.x*Define::MASU_SIZE + Define::MASU_SIZE / 2, this->masuPosition.y*Define::MASU_SIZE + Define::MASU_SIZE / 2);
}

BattleEffectE124_1::~BattleEffectE124_1()
{

}

void BattleEffectE124_1::Update()
{
	effectTimer++;

	if (effectTimer == 180)
	{
		disappearFlag = true;
	}
}
void BattleEffectE124_1::Draw()
{
	static const int graphKind[] = { 5,6,7,8,9 };
	DrawRotaGraphF((float)position.x - camera.x, (float)position.y - camera.y, 1.0, 0.0, graph[76][graphKind[(effectTimer / 3) % 5]], TRUE);
}