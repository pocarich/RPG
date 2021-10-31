#include"../header/EnemyMap010.h"
#include"../header/PlayerMap.h"
#include"../header/EnemySkillInfoList.h"

const int EnemyMap010::randomMoveCount = 5;

EnemyMap010::EnemyMap010(PlayerData* playerData, PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<EnemyMapPtr>& enemyMapList, list<PeopleMapPtr>& peopleMapList, int id, Vector2<int> masuPosition, Vector2<double>& camera, list<BattleEffectPtr>& battleEffectList, list<TextUIPtr>& textUIList, list<DropItemPtr>& dropItemList, int& mapNum) :EnemyMap(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, id, masuPosition, camera, battleEffectList, textUIList, dropItemList, mapNum)
{
	enemyStatus = new EnemyStatus(10);
	kind = 10;
	tempAttackKind = -1;
	randomMoveCounter = 0;
}

EnemyMap010::~EnemyMap010()
{

}

void EnemyMap010::UpdateNotice()
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
		case 14:
		{
			if (abs(masuPosition.x - playerMap->GetMasuPosition().x) + abs(masuPosition.y - playerMap->GetMasuPosition().y) == 1)
			{
				attackKind = 14;
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
		case 15:
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
					attackKind = 15;
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

void EnemyMap010::UpdateTempAttackKind()
{
	Vector2<int> diff = playerMap->GetMasuPosition() - masuPosition;

	if (diff.length() <= 4)
	{
		tempAttackKind = 14;
	}
	else
	{
		tempAttackKind = 15;
	}
}