#include"../header/BattleEffectE047.h"
#include"../header/PlayerMap.h"
#include"../header/EnemyMap.h"

BattleEffectE047::BattleEffectE047(EnemyStatus enemyStatus, PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<BattleEffectPtr>& battleEffectList, list<EnemyMapPtr>& enemyMapList, int sourceID, Vector2<int> masuPosition, Direction direction, Vector2<double>&camera, int& mapNum) :BattleEffect(playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, ObjectType::PLAYER, sourceID, masuPosition, direction, camera, mapNum, TargetType::PLAYER), enemyStatus(enemyStatus)
{
	for (int i = -1; i < 2; i++)for (int j = -1; j < 2; j++)
	{
		if (i != 0 || j != 0)
		{
			attackPositionList.push_back(this->masuPosition + Vector2<int>(i, j));
		}
	}
	position = Vector2<double>(this->masuPosition.x*Define::MASU_SIZE + Define::MASU_SIZE / 2, this->masuPosition.y*Define::MASU_SIZE + Define::MASU_SIZE / 2);

}

BattleEffectE047::~BattleEffectE047()
{

}

void BattleEffectE047::Update()
{
	effectTimer++;
	if (effectTimer == 1)
	{
		for (auto& pos : attackPositionList)
		{
			Vector2<double> tempPos = Vector2<double>(pos.x*Define::MASU_SIZE + Define::MASU_SIZE / 2, pos.y*Define::MASU_SIZE + Define::MASU_SIZE / 2);
			if (abs(playerMap->GetPosition().x - tempPos.x) < ((double)Define::MASU_SIZE - 2.0) && abs(playerMap->GetPosition().y - tempPos.y) < ((double)Define::MASU_SIZE - 2.0))
			{
				playerMap->CauseByEnemy(enemyStatus, direction, sourceID, 47);
			}
		}
	}
	if (effectTimer == 30)
	{
		disappearFlag = true;
	}
}

void BattleEffectE047::Draw()
{
	DrawRotaGraphF((float)position.x - camera.x, (float)position.y - camera.y, 1.0, 0.0, graph[2][(effectTimer / 3) % 10], TRUE);
}