#include"../header/BattleEffectE104.h"
#include"../header/PlayerMap.h"
#include"../header/EnemyMap.h"

BattleEffectE104::BattleEffectE104(BossStatus bossStatus, PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<BattleEffectPtr>& battleEffectList, list<EnemyMapPtr>& enemyMapList, int sourceID, Vector2<int> masuPosition, Direction direction, Vector2<double>&camera, int& mapNum) :BattleEffect(playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, ObjectType::PLAYER, sourceID, masuPosition, direction, camera, mapNum, TargetType::PLAYER), bossStatus(bossStatus)
{
	position = Vector2<double>(this->masuPosition.x*Define::MASU_SIZE + Define::MASU_SIZE / 2, this->masuPosition.y*Define::MASU_SIZE + Define::MASU_SIZE / 2);
}

BattleEffectE104::~BattleEffectE104()
{

}

void BattleEffectE104::Update()
{
	effectTimer++;
	if (effectTimer == 16)
	{
		disappearFlag = true;
	}
}

void BattleEffectE104::Draw()
{
	DrawRotaGraphF((float)position.x - camera.x, (float)position.y - camera.y, 1.0, 0.0, graph[71][(effectTimer / 2) % 8], TRUE);
}