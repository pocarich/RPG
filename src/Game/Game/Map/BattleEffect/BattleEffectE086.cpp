#include"../header/BattleEffectE086.h"
#include"../header/PlayerMap.h"
#include"../header/EnemyMap.h"

BattleEffectE086::BattleEffectE086(BossStatus bossStatus, PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<BattleEffectPtr>& battleEffectList, list<EnemyMapPtr>& enemyMapList, int sourceID, Vector2<int> masuPosition, Direction direction, Vector2<double>&camera, int& mapNum, int count) :BattleEffect(playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, ObjectType::PLAYER, sourceID, masuPosition, direction, camera, mapNum, TargetType::PLAYER), bossStatus(bossStatus), count(count)
{
	if (count == 0)
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
	}
	else
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
	}

	for (int i = -1; i != 2; i++)for (int j = -1; j != 2; j++)
	{
		hitPositionList.push_back(Vector2<int>(this->masuPosition.x + i, this->masuPosition.y + j));
	}

	position = Vector2<double>(this->masuPosition.x*Define::MASU_SIZE + Define::MASU_SIZE / 2, this->masuPosition.y*Define::MASU_SIZE + Define::MASU_SIZE / 2);

}

BattleEffectE086::~BattleEffectE086()
{

}

void BattleEffectE086::Update()
{
	effectTimer++;
	if (effectTimer == 1)
	{
		for (auto& pos : hitPositionList)
		{
			Vector2<double> tempPos = Vector2<double>(pos.x*Define::MASU_SIZE + Define::MASU_SIZE / 2, pos.y*Define::MASU_SIZE + Define::MASU_SIZE / 2);
			if (abs(playerMap->GetPosition().x - tempPos.x) < ((double)Define::MASU_SIZE - 2.0) && abs(playerMap->GetPosition().y - tempPos.y) < ((double)Define::MASU_SIZE - 2.0))
			{
				playerMap->CauseByBoss(bossStatus, direction, sourceID, 86);
			}
		}
	}

	if (effectTimer == popNextTime&&count + 1 < effectMax)
	{
		Vector2<int> tempPos = masuPosition;
		switch (direction)
		{
		case Direction::DOWN:
			tempPos.y += 3;
			break;
		case Direction::LEFT:
			tempPos.x -= 3;
			break;
		case Direction::RIGHT:
			tempPos.x += 3;
			break;
		case Direction::UP:
			tempPos.y -= 3;
			break;
		}
		if (CanMoveToNextPosition(tempPos,direction))
		{
			battleEffectList.push_back(make_shared<BattleEffectE086>(bossStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, sourceID, masuPosition, direction, camera, mapNum, count + 1));
		}
	}
	if (effectTimer == 21)
	{
		disappearFlag = true;
	}
}

void BattleEffectE086::Draw()
{
	DrawRotaGraphF((float)position.x - camera.x, (float)position.y - camera.y, 1.0, 0.0, graph[48][(effectTimer / 3) % 7], TRUE);
}