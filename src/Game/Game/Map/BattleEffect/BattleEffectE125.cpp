#include"../header/BattleEffectE125.h"
#include"../header/PlayerMap.h"
#include"../header/EnemyMap.h"

BattleEffectE125::BattleEffectE125(BossStatus bossStatus, PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<BattleEffectPtr>& battleEffectList, list<EnemyMapPtr>& enemyMapList, int sourceID, Vector2<int> masuPosition, Direction direction, Vector2<double>&camera, int& mapNum) :BattleEffect(playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, ObjectType::PLAYER, sourceID, masuPosition, direction, camera, mapNum, TargetType::PLAYER), bossStatus(bossStatus)
{
	position = Vector2<double>(this->masuPosition.x*Define::MASU_SIZE + Define::MASU_SIZE / 2, this->masuPosition.y*Define::MASU_SIZE + Define::MASU_SIZE / 2);
	happenNextFlag = false;
}

BattleEffectE125::~BattleEffectE125()
{

}

void BattleEffectE125::Update()
{
	effectTimer++;

	if (effectTimer == 35)
	{
		if (abs(playerMap->GetPosition().x - position.x) < ((double)Define::MASU_SIZE - 2.0) && abs(playerMap->GetPosition().y - position.y) < ((double)Define::MASU_SIZE - 2.0))
		{
			playerMap->CauseByBoss(bossStatus, direction, sourceID, 125);
		}
	}

	if (!happenNextFlag)
	{
		if (effectTimer >= StartReadyTime)
		{
			int randDistance = GetRand(100) % 10;
			double randAngle = 2 * M_PI / 100 * (GetRand(10000) % 100);
			Vector2<int> attackPos = playerMap->GetMasuPosition() + Vector2<int>((int)(randDistance*cos(randAngle)), (int)(randDistance*sin(randAngle)));
			if (CanMoveToNextPosition(attackPos, Direction::DOWN))
			{
				battleEffectList.push_back(make_shared<BattleEffectE125>(bossStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, sourceID, attackPos, direction, camera, mapNum));
				happenNextFlag = true;
			}
		}
	}

	if (effectTimer >= 70&&happenNextFlag)
	{
		disappearFlag = true;
	}
}
void BattleEffectE125::Draw()
{
	DrawRotaGraphF((float)position.x - camera.x, (float)position.y - camera.y, 1.0, 0.0, graph[78][(effectTimer / 5) % 14], TRUE);
}