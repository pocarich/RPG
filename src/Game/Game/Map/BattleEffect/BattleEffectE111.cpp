#include"../header/BattleEffectE111.h"
#include"../header/PlayerMap.h"
#include"../header/EnemyMap.h"

BattleEffectE111::BattleEffectE111(BossStatus bossStatus, PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<BattleEffectPtr>& battleEffectList, list<EnemyMapPtr>& enemyMapList, int sourceID, Vector2<int> masuPosition, Direction direction, Vector2<double>&camera, int& mapNum) :BattleEffect(playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, ObjectType::PLAYER, sourceID, masuPosition, direction, camera, mapNum, TargetType::PLAYER), bossStatus(bossStatus)
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

	for (int k = 0; k < 3; k++)
	{
		int x = -1 + GetRand(100) % 3;
		int y = -1 + GetRand(100) % 3;
		hitPositionList[k].push_back(this->masuPosition + Vector2<int>(x, y));
		for (int i = -1; i < 2; i++)for (int j = -1; j < 2; j++)
		{
			if (i != 0 && j != 0)
			{
				hitPositionList[k].push_back(this->masuPosition + Vector2<int>(x, y) + Vector2<int>(i, j));
			}
		}
	}

	position = Vector2<double>(this->masuPosition.x*Define::MASU_SIZE + Define::MASU_SIZE / 2, this->masuPosition.y*Define::MASU_SIZE + Define::MASU_SIZE / 2);

}

BattleEffectE111::~BattleEffectE111()
{

}

void BattleEffectE111::Update()
{
	effectTimer++;
	if (effectTimer %interval == 1 && effectTimer <= (interval * 2 + 1)) 
	{
			for (auto& pos : hitPositionList[(int)(effectTimer/interval)])
			{
				Vector2<double> tempPos = Vector2<double>(pos.x*Define::MASU_SIZE + Define::MASU_SIZE / 2, pos.y*Define::MASU_SIZE + Define::MASU_SIZE / 2);
				if (abs(playerMap->GetPosition().x - tempPos.x) < ((double)Define::MASU_SIZE - 2.0) && abs(playerMap->GetPosition().y - tempPos.y) < ((double)Define::MASU_SIZE - 2.0))
				{
					playerMap->CauseByBoss(bossStatus, direction, sourceID, 111);
				}
			}
	}
	if (effectTimer == (interval * 2 + 30))
	{
		disappearFlag = true;
	}
}

void BattleEffectE111::Draw()
{
	if (effectTimer <= 24)
	{
		Vector2<double> tempPos = Vector2<double>(hitPositionList[0].front().x*Define::MASU_SIZE + Define::MASU_SIZE / 2, hitPositionList[0].front().y*Define::MASU_SIZE + Define::MASU_SIZE / 2);
		DrawRotaGraphF((float)tempPos.x - camera.x, (float)tempPos.y - camera.y, 1.0, 0.0, graph[39][(effectTimer / 3) % 10], TRUE);
	}

	if (0 <= (effectTimer - interval) && (effectTimer - interval) <= 24)
	{
		Vector2<double> tempPos = Vector2<double>(hitPositionList[1].front().x*Define::MASU_SIZE + Define::MASU_SIZE / 2, hitPositionList[1].front().y*Define::MASU_SIZE + Define::MASU_SIZE / 2);
		DrawRotaGraphF((float)tempPos.x - camera.x, (float)tempPos.y - camera.y, 1.0, 0.0, graph[39][((effectTimer - interval) / 3) % 10], TRUE);
	}

	if (0 <= (effectTimer - interval * 2) && (effectTimer - interval * 2) <= 30)
	{
		Vector2<double> tempPos = Vector2<double>(hitPositionList[2].front().x*Define::MASU_SIZE + Define::MASU_SIZE / 2, hitPositionList[2].front().y*Define::MASU_SIZE + Define::MASU_SIZE / 2);
		DrawRotaGraphF((float)tempPos.x - camera.x, (float)tempPos.y - camera.y, 1.0, 0.0, graph[39][((effectTimer - interval * 2) / 3) % 10], TRUE);
	}
}