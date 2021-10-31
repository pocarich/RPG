#include"../header/EnemyMap007.h"
#include"../header/PlayerMap.h"
#include"../header/EnemySkillInfoList.h"

const int EnemyMap007::randomMoveCount = 5;

EnemyMap007::EnemyMap007(PlayerData* playerData, PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<EnemyMapPtr>& enemyMapList, list<PeopleMapPtr>& peopleMapList, int id, Vector2<int> masuPosition, Vector2<double>& camera, list<BattleEffectPtr>& battleEffectList, list<TextUIPtr>& textUIList, list<DropItemPtr>& dropItemList, int& mapNum) :EnemyMap(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, id, masuPosition, camera, battleEffectList, textUIList, dropItemList, mapNum)
{
	enemyStatus = new EnemyStatus(7);
	kind = 7;
	tempAttackKind = -1;
	randomMoveCounter = 0;
}

EnemyMap007::~EnemyMap007()
{

}

void EnemyMap007::UpdateNotice()
{
	if (stiffTimer > 0)
	{
		return;
	}

	if (tempAttackKind == -1)
	{
		UpdateTempAttackKind();
	}
	else
	{
		switch (tempAttackKind)
		{
		case 9:
		{
			if (abs(masuPosition.x - playerMap->GetMasuPosition().x) + abs(masuPosition.y - playerMap->GetMasuPosition().y) == 1)
			{
				attackKind = 9;
				tempAttackKind = -1;

				Vector2<int> diff = playerMap->GetMasuPosition() - masuPosition;
				if (diff == Vector2<int>(1, 0))
				{
					attackDirection = Direction::RIGHT;
				}
				else if (diff == Vector2<int>(-1, 0))
				{
					attackDirection = Direction::LEFT;
				}
				else if (diff == Vector2<int>(0, -1))
				{
					attackDirection = Direction::UP;
				}
				else if (diff == Vector2<int>(0, 1))
				{
					attackDirection = Direction::DOWN;
				}
				else
				{
					assert(0 && "EnemyMap001::UpdateNotice()");
				}
				attackPointList.push_back(playerMap->GetMasuPosition());
			}
			else
			{
				StartMove(enemyStatus->GetMoveSpeedNotice(), StartMoveKind::CLOSE);
			}
		}
		break;
		case 10:
		{
			if (randomMoveCounter < randomMoveCount)
			{
				StartMove(enemyStatus->GetMoveSpeedNotice(), StartMoveKind::RAMDOM);
				randomMoveCounter++;
			}
			else
			{
				randomMoveCounter = 0;
				attackKind = 10;
				tempAttackKind = -1;
				for (int i = -3; i < 4; i++)for (int j = -3; j < 4; j++)
				{
					attackPointList.push_back(masuPosition + Vector2<int>(i, j));
				}
			}
		}
		break;
		}

	}
}

void EnemyMap007::UpdateTempAttackKind()
{
	Vector2<int> diff = playerMap->GetMasuPosition() - masuPosition;

	if (diff.length() <= 4)
	{
		tempAttackKind = 9;
	}
	else
	{
		tempAttackKind = 10;
	}
}