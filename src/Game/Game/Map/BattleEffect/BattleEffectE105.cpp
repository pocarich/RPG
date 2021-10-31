#include"../header/BattleEffectE105.h"
#include"../header/PlayerMap.h"
#include"../header/EnemyMap.h"

BattleEffectE105::BattleEffectE105(BossStatus bossStatus, PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<BattleEffectPtr>& battleEffectList, list<EnemyMapPtr>& enemyMapList, int sourceID, Vector2<int> masuPosition, Direction direction, Vector2<double>&camera, int& mapNum) :BattleEffect(playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, ObjectType::PLAYER, sourceID, masuPosition, direction, camera, mapNum, TargetType::PLAYER), bossStatus(bossStatus)
{
	for (int i = -7; i < 8; i++)for (int j = -7; j < 8; j++)
	{
		if (Vector2<int>(i, j).length() <= 7)
		{
			hitPositionList.push_back(masuPosition + Vector2<int>(i, j));
		}
	}

	position = Vector2<double>(this->masuPosition.x*Define::MASU_SIZE + Define::MASU_SIZE / 2, this->masuPosition.y*Define::MASU_SIZE + Define::MASU_SIZE / 2);

}

BattleEffectE105::~BattleEffectE105()
{

}

void BattleEffectE105::Update()
{
	effectTimer++;
	if (effectTimer % 10 == 1)
	{
		for (auto& pos : hitPositionList)
		{
			Vector2<double> tempPos = Vector2<double>(pos.x*Define::MASU_SIZE + Define::MASU_SIZE / 2, pos.y*Define::MASU_SIZE + Define::MASU_SIZE / 2);
			if (abs(playerMap->GetPosition().x - tempPos.x) < ((double)Define::MASU_SIZE - 2.0) && abs(playerMap->GetPosition().y - tempPos.y) < ((double)Define::MASU_SIZE - 2.0))
			{
				playerMap->CauseByBoss(bossStatus, direction, sourceID, 105);
			}
		}
	}
	if (effectTimer == 72)
	{
		disappearFlag = true;
	}
}

void BattleEffectE105::Draw()
{
	DrawRotaGraphF((float)position.x - camera.x, (float)position.y - camera.y, 1.0, 0.0, graph[69][(effectTimer / 3) % 24], TRUE);
}