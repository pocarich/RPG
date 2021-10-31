#include"../header/EnemyMap027.h"
#include"../header/PlayerMap.h"
#include"../header/EnemySkillInfoList.h"

EnemyMap027::EnemyMap027(PlayerData* playerData, PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<EnemyMapPtr>& enemyMapList, list<PeopleMapPtr>& peopleMapList, int id, Vector2<int> masuPosition, Vector2<double>& camera, list<BattleEffectPtr>& battleEffectList, list<TextUIPtr>& textUIList, list<DropItemPtr>& dropItemList, int& mapNum) :EnemyMap(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, id, masuPosition, camera, battleEffectList, textUIList, dropItemList, mapNum)
{
	enemyStatus = new EnemyStatus(27);
	kind = 27;
	tempAttackKind = -1;
	randomMoveCounter = 0;
}

EnemyMap027::~EnemyMap027()
{

}

void EnemyMap027::UpdateNotice()
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
		case 47:
		{
			if (abs(masuPosition.x - playerMap->GetMasuPosition().x) + abs(masuPosition.y - playerMap->GetMasuPosition().y) == 1)
			{
				attackKind = 47;
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
				for (int i = -1; i < 2; i++)for (int j = -1; j < 2; j++)
				{
					if (i != 0 || j != 0)
					{
						attackPointList.push_back(masuPosition + Vector2<int>(i, j));
					}
				}
			}
			else
			{
				StartMove(enemyStatus->GetMoveSpeedNotice(), StartMoveKind::CLOSE);
			}
		}
		break;
		case 48:
		{
			if (randomMoveCounter < randomMoveCount)
			{
				StartMove(enemyStatus->GetMoveSpeedNotice(), StartMoveKind::RAMDOM);
				randomMoveCounter++;
			}
			else
			{
				Vector2<int> diff = playerMap->GetMasuPosition() - masuPosition;
				if ((abs(diff.x) <= 6 && diff.y == 0) || (abs(diff.y) <= 6 && diff.x == 0))
				{
					attackKind = 48;
					tempAttackKind = -1;
					randomMoveCounter = 0;

					if (diff.x > 0)
					{
						attackDirection = Direction::RIGHT;
						for (int i = 0; i < 3; i++)
						{
							Vector2<int> attackPoint = masuPosition + Vector2<int>(1 + i, 0);
							attackPointList.push_back(attackPoint);
						}
						for (int i = -1; i < 2; i++)for (int j = -1; j < 2; j++)
						{
							Vector2<int> attackPoint = masuPosition + Vector2<int>(5 + i, j);
							attackPointList.push_back(attackPoint);
						}
					}
					else if (diff.x < 0)
					{
						attackDirection = Direction::LEFT;
						for (int i = 0; i < 3; i++)
						{
							Vector2<int> attackPoint = masuPosition + Vector2<int>(-1 - i, 0);
							attackPointList.push_back(attackPoint);
						}
						for (int i = -1; i < 2; i++)for (int j = -1; j < 2; j++)
						{
							Vector2<int> attackPoint = masuPosition + Vector2<int>(-5 + i, j);
							attackPointList.push_back(attackPoint);
						}
					}
					else if (diff.y > 0)
					{
						attackDirection = Direction::DOWN;
						for (int i = 0; i < 3; i++)
						{
							Vector2<int> attackPoint = masuPosition + Vector2<int>(0, 1 + i);
							attackPointList.push_back(attackPoint);
						}
						for (int i = -1; i < 2; i++)for (int j = -1; j < 2; j++)
						{
							Vector2<int> attackPoint = masuPosition + Vector2<int>(i, 5 + j);
							attackPointList.push_back(attackPoint);
						}
					}
					else if (diff.y < 0)
					{
						attackDirection = Direction::UP;
						for (int i = 0; i < 3; i++)
						{
							Vector2<int> attackPoint = masuPosition + Vector2<int>(0, -1 - i);
							attackPointList.push_back(attackPoint);
						}
						for (int i = -1; i < 2; i++)for (int j = -1; j < 2; j++)
						{
							Vector2<int> attackPoint = masuPosition + Vector2<int>(i, -5 + j);
							attackPointList.push_back(attackPoint);
						}
					}
					else
					{
						assert(0 && "EnemyaMap001::UpdateNotice()");
					}
				}
				else if (abs(diff.x)>6 || abs(diff.y)>6)
				{
					StartMove(enemyStatus->GetMoveSpeedNotice(), StartMoveKind::CLOSE);
				}
				else
				{
					StartMove(enemyStatus->GetMoveSpeedNotice(), StartMoveKind::ALIGNMENT);
				}
			}
		}
		break;
		}

	}
}

void EnemyMap027::UpdateTempAttackKind()
{
	Vector2<int> diff = playerMap->GetMasuPosition() - masuPosition;

	if (diff.length() <= 4)
	{
		tempAttackKind = 47;
	}
	else
	{
		tempAttackKind = 48;
	}
}