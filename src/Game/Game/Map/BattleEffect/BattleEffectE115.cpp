#include"../header/BattleEffectE115.h"
#include"../header/PlayerMap.h"
#include"../header/EnemyMap.h"

BattleEffectE115::BattleEffectE115(BossStatus bossStatus, PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<BattleEffectPtr>& battleEffectList, list<EnemyMapPtr>& enemyMapList, int sourceID, Vector2<int> masuPosition, Direction direction, Vector2<double>&camera, int& mapNum, int stateCount, int offset) :BattleEffect(playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, ObjectType::PLAYER, sourceID, masuPosition, direction, camera, mapNum, TargetType::PLAYER), bossStatus(bossStatus), stateCount(stateCount), offset(offset)
{
	if (stateCount == 0)
	{
		switch (direction)
		{
		case Direction::DOWN:
			this->masuPosition.y += 1;
			break;
		case Direction::LEFT:
			this->masuPosition.x -= 1;
			break;
		case Direction::RIGHT:
			this->masuPosition.x += 1;
			break;
		case Direction::UP:
			this->masuPosition.y -= 1;
			break;
		}
	}

	position = Vector2<double>(this->masuPosition.x*Define::MASU_SIZE + Define::MASU_SIZE / 2, this->masuPosition.y*Define::MASU_SIZE + Define::MASU_SIZE / 2);
}

BattleEffectE115::~BattleEffectE115()
{

}

void BattleEffectE115::Update()
{
	static const int width[] = { 0,1,1,2,2,3,3,4 };
	effectTimer++;
	if (effectTimer == 1)
	{
		if (abs(playerMap->GetPosition().x - position.x) < ((double)Define::MASU_SIZE - 2.0) && abs(playerMap->GetPosition().y - position.y) < ((double)Define::MASU_SIZE - 2.0))
		{
			playerMap->CauseByBoss(bossStatus, direction, sourceID, 115);
		}
	}
	if (effectTimer == nextPopTime&&stateCount + 1 < stateMax)
	{
		{
			Vector2<int> next = masuPosition;
			switch (direction)
			{
			case Direction::DOWN:
				next.y++;
				break;
			case Direction::LEFT:
				next.x--;
				break;
			case Direction::RIGHT:
				next.x++;
				break;
			case Direction::UP:
				next.y--;
				break;
			}
			if (CanMoveToNextPosition(next, direction))
			{
				int newOffset = offset;
				if (width[stateCount + 1] > width[stateCount])
				{
					newOffset++;
				}
				battleEffectList.push_back(make_shared<BattleEffectE115>(bossStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, sourceID, next, direction, camera, mapNum, stateCount + 1, newOffset));
			}
		}

		if (width[stateCount + 1] > width[stateCount])
		{
			if (offset == 0)
			{
				Vector2<int> next = masuPosition;
				switch (direction)
				{
				case Direction::DOWN:
					next.y++;
					next.x--;
					break;
				case Direction::LEFT:
					next.x--;
					next.y--;
					break;
				case Direction::RIGHT:
					next.x++;
					next.y++;
					break;
				case Direction::UP:
					next.y--;
					next.x++;
					break;
				}
				if (CanMoveToNextPosition(next, direction))
				{
					battleEffectList.push_back(make_shared<BattleEffectE115>(bossStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, sourceID, next, direction, camera, mapNum, stateCount + 1, 0));
				}
			}
			if (offset == 2 * width[stateCount])
			{
				Vector2<int> next = masuPosition;
				switch (direction)
				{
				case Direction::DOWN:
					next.y++;
					next.x++;
					break;
				case Direction::LEFT:
					next.x--;
					next.y++;
					break;
				case Direction::RIGHT:
					next.x++;
					next.y--;
					break;
				case Direction::UP:
					next.y--;
					next.x--;
					break;
				}
				if (CanMoveToNextPosition(next, direction))
				{
					battleEffectList.push_back(make_shared<BattleEffectE115>(bossStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, sourceID, next, direction, camera, mapNum, stateCount + 1, offset + 2));
				}
			}
		}
	}
	if (effectTimer == 24)
	{
		disappearFlag = true;
	}
}

void BattleEffectE115::Draw()
{
	DrawRotaGraphF((float)position.x - camera.x, (float)position.y - camera.y, 1.0, 0.0, graph[73][(effectTimer / 3) % 8], TRUE);
}