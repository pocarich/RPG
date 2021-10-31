#include"../header/BattleEffectE019.h"
#include"../header/PlayerMap.h"
#include"../header/EnemyMap.h"

BattleEffectE019::BattleEffectE019(EnemyStatus enemyStatus, PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<BattleEffectPtr>& battleEffectList, list<EnemyMapPtr>& enemyMapList, int sourceID, Vector2<int> masuPosition, Direction direction, Vector2<double>&camera, int& mapNum) :BattleEffect(playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, ObjectType::PLAYER, sourceID, masuPosition, direction, camera, mapNum, TargetType::PLAYER),enemyStatus(enemyStatus)
{
	for (int i = -2; i != 3; i++)for (int j = -2; j != 3; j++)
	{
		hitPositionList.push_back(Vector2<int>(this->masuPosition.x + i, this->masuPosition.y + j));
	}
	position = Vector2<double>(this->masuPosition.x*Define::MASU_SIZE + Define::MASU_SIZE / 2, this->masuPosition.y*Define::MASU_SIZE + Define::MASU_SIZE / 2);

}

BattleEffectE019::~BattleEffectE019()
{

}

void BattleEffectE019::Update()
{
	effectTimer++;
	if (effectTimer == 1)
	{
		for (auto& pos : hitPositionList)
		{
			Vector2<double> tempPos = Vector2<double>(pos.x*Define::MASU_SIZE + Define::MASU_SIZE / 2, pos.y*Define::MASU_SIZE + Define::MASU_SIZE / 2);
			if (abs(playerMap->GetPosition().x - tempPos.x) < ((double)Define::MASU_SIZE - 2.0) && abs(playerMap->GetPosition().y - tempPos.y) < ((double)Define::MASU_SIZE - 2.0))
			{
				playerMap->CauseByEnemy(enemyStatus, direction, sourceID, 19);
			}
		}
	}
	if (effectTimer == 24)
	{
		disappearFlag = true;
	}
}

void BattleEffectE019::Draw()
{
	DrawRotaGraphF((float)position.x - 36 - camera.x, (float)position.y - 36 - camera.y, 1.0, 0.0, graph[16][(effectTimer / 3) % 8], TRUE);
	DrawRotaGraphF((float)position.x - 36 - camera.x, (float)position.y + 36 - camera.y, 1.0, 0.0, graph[16][(effectTimer / 3) % 8], TRUE);
	DrawRotaGraphF((float)position.x + 36 - camera.x, (float)position.y - 36 - camera.y, 1.0, 0.0, graph[16][(effectTimer / 3) % 8], TRUE);
	DrawRotaGraphF((float)position.x + 36 - camera.x, (float)position.y + 36 - camera.y, 1.0, 0.0, graph[16][(effectTimer / 3) % 8], TRUE);
}