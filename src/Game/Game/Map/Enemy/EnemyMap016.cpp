#include"../header/EnemyMap016.h"
#include"../header/PlayerMap.h"
#include"../header/EnemySkillInfoList.h"

EnemyMap016::EnemyMap016(PlayerData* playerData, PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<EnemyMapPtr>& enemyMapList, list<PeopleMapPtr>& peopleMapList, int id, Vector2<int> masuPosition, Vector2<double>& camera, list<BattleEffectPtr>& battleEffectList, list<TextUIPtr>& textUIList, list<DropItemPtr>& dropItemList, int& mapNum) :EnemyMap(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, id, masuPosition, camera, battleEffectList, textUIList, dropItemList, mapNum)
{
	enemyStatus = new EnemyStatus(16);
	kind = 16;
	tempAttackKind = -1;
}

EnemyMap016::~EnemyMap016()
{

}

void EnemyMap016::UpdateNotice()
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
		case 26:
		{
			Vector2<int> diff = playerMap->GetMasuPosition() - masuPosition;

			if (abs(masuPosition.x - playerMap->GetMasuPosition().x) + abs(masuPosition.y - playerMap->GetMasuPosition().y) <= 3)
			{
				attackKind = 26;
				tempAttackKind = -1;

				if (abs(diff.x) <= abs(diff.y))
				{
					if (diff.y < 0)
					{
						attackDirection = Direction::UP;

						Vector2<int> tempPos = masuPosition + Vector2<int>(0, -2);
						for (int i = -1; i < 2; i++)for (int j = -1; j < 2; j++)
						{
							Vector2<int> tempPos2 = tempPos + Vector2<int>(i, j);
							Vector2<int> diff2 = tempPos2 - masuPosition;
							if (!(abs(diff2.x) == 1 && abs(diff2.y) == 1))
							{
								attackPointList.push_back(tempPos2);
							}
						}
					}
					else
					{
						attackDirection = Direction::DOWN;
						Vector2<int> tempPos = masuPosition + Vector2<int>(0, 2);
						for (int i = -1; i < 2; i++)for (int j = -1; j < 2; j++)
						{
							Vector2<int> tempPos2 = tempPos + Vector2<int>(i, j);
							Vector2<int> diff2 = tempPos2 - masuPosition;
							if (!(abs(diff2.x) == 1 && abs(diff2.y) == 1))
							{
								attackPointList.push_back(tempPos2);
							}
						}
					}
				}
				else
				{
					if (diff.x > 0)
					{
						attackDirection = Direction::RIGHT;
						Vector2<int> tempPos = masuPosition + Vector2<int>(2, 0);
						for (int i = -1; i < 2; i++)for (int j = -1; j < 2; j++)
						{
							Vector2<int> tempPos2 = tempPos + Vector2<int>(i, j);
							Vector2<int> diff2 = tempPos2 - masuPosition;
							if (!(abs(diff2.x) == 1 && abs(diff2.y) == 1))
							{
								attackPointList.push_back(tempPos2);
							}
						}
					}
					else
					{
						attackDirection = Direction::LEFT;
						Vector2<int> tempPos = masuPosition + Vector2<int>(-2, 0);
						for (int i = -1; i < 2; i++)for (int j = -1; j < 2; j++)
						{
							Vector2<int> tempPos2 = tempPos + Vector2<int>(i, j);
							Vector2<int> diff2 = tempPos2 - masuPosition;
							if (!(abs(diff2.x) == 1 && abs(diff2.y) == 1))
							{
								attackPointList.push_back(tempPos2);
							}
						}
					}
				}
			}
			else if (abs(diff.x) > 3 || abs(diff.y)>3)
			{
				StartMove(enemyStatus->GetMoveSpeedNotice(), StartMoveKind::CLOSE);
			}
			else
			{
				StartMove(enemyStatus->GetMoveSpeedNotice(), StartMoveKind::ALIGNMENT);
			}
		}
		break;
		case 25:
		{
			Vector2<int> diff = playerMap->GetMasuPosition() - masuPosition;

			if (abs(masuPosition.x - playerMap->GetMasuPosition().x) + abs(masuPosition.y - playerMap->GetMasuPosition().y) <= 1)
			{
				attackKind = 25;
				tempAttackKind = -1;

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
		}

	}
}

void EnemyMap016::UpdateTempAttackKind()
{
	Vector2<int> diff = playerMap->GetMasuPosition() - masuPosition;

	int randNum = GetRand(1000) % 10;
	if (randNum >= 2)
	{
		tempAttackKind = 25;
	}
	else
	{
		tempAttackKind = 26;
	}
}