#include"../header/BattleEffectE052.h"
#include"../header/PlayerMap.h"
#include"../header/EnemyMap.h"

BattleEffectE052::BattleEffectE052(EnemyStatus enemyStatus, PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<BattleEffectPtr>& battleEffectList, list<EnemyMapPtr>& enemyMapList, int sourceID, Vector2<int> masuPosition, Direction direction, Vector2<double>&camera, int& mapNum) :BattleEffect(playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, ObjectType::PLAYER, sourceID, masuPosition, direction, camera, mapNum, TargetType::PLAYER), enemyStatus(enemyStatus)
{
	position = Vector2<double>(this->masuPosition.x*Define::MASU_SIZE + Define::MASU_SIZE / 2, this->masuPosition.y*Define::MASU_SIZE + Define::MASU_SIZE / 2);

}

BattleEffectE052::~BattleEffectE052()
{

}

void BattleEffectE052::Update()
{
	effectTimer++;
	if (effectTimer == 1)
	{
		if (abs(playerMap->GetPosition().x - position.x) < ((double)Define::MASU_SIZE - 2.0) && abs(playerMap->GetPosition().y - position.y) < ((double)Define::MASU_SIZE - 2.0))
		{
			playerMap->CauseByEnemy(enemyStatus, direction, sourceID, 52);
		}
	}
	if (effectTimer == 24)
	{
		disappearFlag = true;
	}
}

void BattleEffectE052::Draw()
{
	DrawRotaGraphF((float)position.x - camera.x, (float)position.y - camera.y, 1.0, 0.0, graph[40][(effectTimer / 3) % 8], TRUE);
}