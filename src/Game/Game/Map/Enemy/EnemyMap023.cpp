#include"../header/EnemyMap023.h"
#include"../header/PlayerMap.h"
#include"../header/EnemySkillInfoList.h"

const int EnemyMap023::randomMoveCount = 5;

EnemyMap023::EnemyMap023(PlayerData* playerData, PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<EnemyMapPtr>& enemyMapList, list<PeopleMapPtr>& peopleMapList, int id, Vector2<int> masuPosition, Vector2<double>& camera, list<BattleEffectPtr>& battleEffectList, list<TextUIPtr>& textUIList, list<DropItemPtr>& dropItemList, int& mapNum) :EnemyMap(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, id, masuPosition, camera, battleEffectList, textUIList, dropItemList, mapNum)
{
	enemyStatus = new EnemyStatus(23);
	kind = 23;
	tempAttackKind = -1;
	randomMoveCounter = 0;
}

EnemyMap023::~EnemyMap023()
{

}

void EnemyMap023::UpdateNotice()
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
		case 38:
		{
			if (abs(masuPosition.x - playerMap->GetMasuPosition().x) + abs(masuPosition.y - playerMap->GetMasuPosition().y) == 1)
			{
				attackKind = 38;
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
		case 39:
		{
			if (randomMoveCounter < randomMoveCount)
			{
				StartMove(enemyStatus->GetMoveSpeedNotice(), StartMoveKind::RAMDOM);
				randomMoveCounter++;
			}
			else
			{
				Vector2<int> diff = playerMap->GetMasuPosition() - masuPosition;
				if (diff.length() <= 7)
				{
					randomMoveCounter = 0;
					attackKind = 39;
					tempAttackKind = -1;
					attackPointList.push_back(playerMap->GetMasuPosition());
				}
				else
				{
					StartMove(enemyStatus->GetMoveSpeedNotice(), StartMoveKind::CLOSE);
				}
			}
		}
		break;
		}

	}
}

void EnemyMap023::UpdateTempAttackKind()
{
	Vector2<int> diff = playerMap->GetMasuPosition() - masuPosition;

	if (diff.length() <= 4)
	{
		tempAttackKind = 38;
	}
	else
	{
		tempAttackKind = 39;
	}
}