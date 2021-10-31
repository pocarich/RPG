#include"../header/BattleEffectE120_2.h"
#include"../header/PlayerMap.h"
#include"../header/EnemyMap.h"

BattleEffectE120_2::BattleEffectE120_2(BossStatus bossStatus, PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<BattleEffectPtr>& battleEffectList, list<EnemyMapPtr>& enemyMapList, int sourceID, Vector2<int> masuPosition, Direction direction, Vector2<double>&camera, int& mapNum) :BattleEffect(playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, ObjectType::PLAYER, sourceID, masuPosition, direction, camera, mapNum, TargetType::PLAYER), bossStatus(bossStatus)
{
	for (int i = -3; i < 4; i++)for (int j = -3; j < 4; j++)
	{
		attackPositionList.push_back(this->masuPosition + Vector2<int>(i, j));
	}
	position = Vector2<double>(this->masuPosition.x*Define::MASU_SIZE + Define::MASU_SIZE / 2, this->masuPosition.y*Define::MASU_SIZE + Define::MASU_SIZE / 2);
}

BattleEffectE120_2::~BattleEffectE120_2()
{

}

void BattleEffectE120_2::Update()
{
	effectTimer++;
	if (effectTimer%hitInterval == 1)
	{
		for (auto& pos : attackPositionList)
		{
			Vector2<double> tempPos = Vector2<double>(pos.x*Define::MASU_SIZE + Define::MASU_SIZE / 2, pos.y*Define::MASU_SIZE + Define::MASU_SIZE / 2);
			if (abs(playerMap->GetPosition().x - tempPos.x) < ((double)Define::MASU_SIZE - 2.0) && abs(playerMap->GetPosition().y - tempPos.y) < ((double)Define::MASU_SIZE - 2.0))
			{
				playerMap->CauseByBoss(bossStatus, direction, sourceID, 120);
			}
		}
	}
	if (effectTimer == existTime)
	{
		disappearFlag = true;
	}
}

void BattleEffectE120_2::Draw()
{
	static const int graphKind[] = { 2,3,4,5 };
	DrawRotaGraphF((float)position.x - camera.x, (float)position.y - camera.y, 1.0, 0.0, graph[25][graphKind[(effectTimer / 1) % 4]], TRUE);
}