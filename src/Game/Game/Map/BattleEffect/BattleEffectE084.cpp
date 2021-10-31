#include"../header/BattleEffectE084.h"
#include"../header/PlayerMap.h"
#include"../header/EnemyMap.h"

BattleEffectE084::BattleEffectE084(BossStatus bossStatus, PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<BattleEffectPtr>& battleEffectList, list<EnemyMapPtr>& enemyMapList, int sourceID, Vector2<int> masuPosition, Direction direction, Vector2<double>&camera, int& mapNum) :BattleEffect(playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, ObjectType::PLAYER, sourceID, masuPosition, direction, camera, mapNum, TargetType::PLAYER), bossStatus(bossStatus)
{
	switch (direction)
	{
	case Direction::DOWN:
		this->masuPosition.y+=3;
		break;
	case Direction::LEFT:
		this->masuPosition.x-=3;
		break;
	case Direction::RIGHT:
		this->masuPosition.x+=3;
		break;
	case Direction::UP:
		this->masuPosition.y-=3;
		break;
	}

	for (int i = -1; i < 2; i++)for (int j = -1; j < 2; j++)
	{
		hitPositionList.push_back(this->masuPosition + Vector2<int>(i, j));
	}

	position = Vector2<double>(this->masuPosition.x*Define::MASU_SIZE + Define::MASU_SIZE / 2, this->masuPosition.y*Define::MASU_SIZE + Define::MASU_SIZE / 2);

}

BattleEffectE084::~BattleEffectE084()
{

}

void BattleEffectE084::Update()
{
	effectTimer++;
	if (effectTimer == 1 || effectTimer == 28)
	{
		for (auto& pos : hitPositionList)
		{
			Vector2<double> tempPos = Vector2<double>(pos.x*Define::MASU_SIZE + Define::MASU_SIZE / 2, pos.y*Define::MASU_SIZE + Define::MASU_SIZE / 2);
			if (abs(playerMap->GetPosition().x - tempPos.x) < ((double)Define::MASU_SIZE - 2.0) && abs(playerMap->GetPosition().y - tempPos.y) < ((double)Define::MASU_SIZE - 2.0))
			{
				playerMap->CauseByBoss(bossStatus, direction, sourceID, 84);
			}
		}
	}
	if (effectTimer == 54)
	{
		disappearFlag = true;
	}
}

void BattleEffectE084::Draw()
{
	if (effectTimer < 27)
	{
		DrawRotaGraphF((float)position.x - camera.x, (float)position.y - camera.y, 1.0, 0.0, graph[52][(effectTimer / 3) % 9], TRUE);
	}
	if (0 <= (effectTimer - 27))
	{
		DrawRotaGraphF((float)position.x - camera.x, (float)position.y - camera.y, 1.0, 0.0, graph[52][(effectTimer / 3) % 9], TRUE, TRUE);
	}
}