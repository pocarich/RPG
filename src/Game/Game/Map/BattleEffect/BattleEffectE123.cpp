#include"../header/BattleEffectE123.h"
#include"../header/PlayerMap.h"
#include"../header/EnemyMap.h"

BattleEffectE123::BattleEffectE123(BossStatus bossStatus, PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<BattleEffectPtr>& battleEffectList, list<EnemyMapPtr>& enemyMapList, int sourceID, Vector2<int> masuPosition, Direction direction, Vector2<double>&camera, int& mapNum) :BattleEffect(playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, ObjectType::PLAYER, sourceID, masuPosition, direction, camera, mapNum, TargetType::PLAYER), bossStatus(bossStatus)
{
	for (int i = -4; i < 5; i++)for (int j = -4; j < 5; j++)
	{
		if (Vector2<int>(i, j).length() <= 4)
		{
			hitPositionList.push_back(masuPosition + Vector2<int>(i, j));
		}
	}

	position = Vector2<double>(this->masuPosition.x*Define::MASU_SIZE + Define::MASU_SIZE / 2, this->masuPosition.y*Define::MASU_SIZE + Define::MASU_SIZE / 2);

}

BattleEffectE123::~BattleEffectE123()
{

}

void BattleEffectE123::Update()
{
	effectTimer++;

	if (effectTimer == 1)
	{
		for (auto& pos : hitPositionList)
		{
			Vector2<double> tempPos = Vector2<double>(pos.x*Define::MASU_SIZE + Define::MASU_SIZE / 2, pos.y*Define::MASU_SIZE + Define::MASU_SIZE / 2);
			if (abs(playerMap->GetPosition().x - tempPos.x) < ((double)Define::MASU_SIZE - 2.0) && abs(playerMap->GetPosition().y - tempPos.y) < ((double)Define::MASU_SIZE - 2.0))
			{
				playerMap->CauseByBoss(bossStatus, direction, sourceID, 123);
			}
		}
	}

	if (effectTimer == 90)
	{
		disappearFlag = true;
	}
}
void BattleEffectE123::Draw()
{
	DrawRotaGraphF((float)position.x - camera.x, (float)position.y - camera.y-64, 1.0, 0.0, graph[75][(effectTimer / 3) % 30], TRUE);
}