#include"../header/BattleEffectE127.h"
#include"../header/PlayerMap.h"
#include"../header/EnemyMap.h"

BattleEffectE127::BattleEffectE127(BossStatus bossStatus, PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<BattleEffectPtr>& battleEffectList, list<EnemyMapPtr>& enemyMapList, int sourceID, Vector2<int> masuPosition, Direction direction, Vector2<double>&camera, int& mapNum) :BattleEffect(playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, ObjectType::PLAYER, sourceID, masuPosition, direction, camera, mapNum, TargetType::PLAYER), bossStatus(bossStatus)
{
	position = Vector2<double>(this->masuPosition.x*Define::MASU_SIZE + Define::MASU_SIZE / 2, this->masuPosition.y*Define::MASU_SIZE + Define::MASU_SIZE / 2);
}

BattleEffectE127::~BattleEffectE127()
{

}

void BattleEffectE127::Update()
{
	effectTimer++;
	if (effectTimer == 1)
	{
		if (abs(playerMap->GetPosition().x - position.x) < ((double)Define::MASU_SIZE - 2.0) && abs(playerMap->GetPosition().y - position.y) < ((double)Define::MASU_SIZE - 2.0))
		{
			playerMap->CauseByBoss(bossStatus, direction, sourceID, 127);
		}
	}
	if (effectTimer == 32)
	{
		disappearFlag = true;
	}
}

void BattleEffectE127::Draw()
{
	DrawRotaGraphF((float)position.x - camera.x, (float)position.y - camera.y, 1.0, 0.0, graph[18][(effectTimer / 4) % 8], TRUE);
}