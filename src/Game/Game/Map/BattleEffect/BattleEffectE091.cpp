#include"../header/BattleEffectE091.h"
#include"../header/PlayerMap.h"
#include"../header/EnemyMap.h"

BattleEffectE091::BattleEffectE091(BossStatus bossStatus, PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<BattleEffectPtr>& battleEffectList, list<EnemyMapPtr>& enemyMapList, int sourceID, Vector2<int> masuPosition, Direction direction, Vector2<double>&camera, int& mapNum) :BattleEffect(playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, ObjectType::PLAYER, sourceID, masuPosition, direction, camera, mapNum, TargetType::PLAYER),bossStatus(bossStatus)
{
	switch (direction)
	{
	case Direction::DOWN:
		this->masuPosition.y += 3;
		break;
	case Direction::LEFT:
		this->masuPosition.x -= 3;
		break;
	case Direction::RIGHT:
		this->masuPosition.x += 3;
		break;
	case Direction::UP:
		this->masuPosition.y -= 3;
		break;
	}

	for (int i = -2; i != 3; i++)for (int j = -2; j != 3; j++)
	{
		hitPositionList.push_back(Vector2<int>(this->masuPosition.x + i, this->masuPosition.y + j));
	}

	position = Vector2<double>(this->masuPosition.x*Define::MASU_SIZE + Define::MASU_SIZE / 2, this->masuPosition.y*Define::MASU_SIZE + Define::MASU_SIZE / 2);

}

BattleEffectE091::~BattleEffectE091()
{

}

void BattleEffectE091::Update()
{
	effectTimer++;
	if (effectTimer == 1)
	{
		for (auto& pos : hitPositionList)
		{
			Vector2<double> tempPos = Vector2<double>(pos.x*Define::MASU_SIZE + Define::MASU_SIZE / 2, pos.y*Define::MASU_SIZE + Define::MASU_SIZE / 2);
			if (abs(playerMap->GetPosition().x - tempPos.x) < ((double)Define::MASU_SIZE - 2.0) && abs(playerMap->GetPosition().y - tempPos.y) < ((double)Define::MASU_SIZE - 2.0))
			{
				playerMap->CauseByBoss(bossStatus, direction, sourceID, 91);
			}
		}
	}
	if (effectTimer == 15)
	{
		disappearFlag = true;
	}
}

void BattleEffectE091::Draw()
{
	DrawRotaGraphF((float)position.x - camera.x, (float)position.y - camera.y, 1.0, 0.0, graph[62][(effectTimer / 3) % 5], TRUE);
}