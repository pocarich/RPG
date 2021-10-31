#include"../header/EnemyMap025.h"
#include"../header/PlayerMap.h"
#include"../header/EnemySkillInfoList.h"

EnemyMap025::EnemyMap025(PlayerData* playerData, PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<EnemyMapPtr>& enemyMapList, list<PeopleMapPtr>& peopleMapList, int id, Vector2<int> masuPosition, Vector2<double>& camera, list<BattleEffectPtr>& battleEffectList, list<TextUIPtr>& textUIList, list<DropItemPtr>& dropItemList, int& mapNum) :EnemyMap(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, id, masuPosition, camera, battleEffectList, textUIList, dropItemList, mapNum)
{
	enemyStatus = new EnemyStatus(25);
	kind = 25;
	tempAttackKind = -1;
}

EnemyMap025::~EnemyMap025()
{

}

void EnemyMap025::UpdateNotice()
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
		case 42:
		{
			Vector2<int> diff = playerMap->GetMasuPosition() - masuPosition;

			if (abs(masuPosition.x - playerMap->GetMasuPosition().x) <= 1 && abs(masuPosition.y - playerMap->GetMasuPosition().y) <= 1)
			{
				attackKind = 42;
				tempAttackKind = -1;
				if (abs(diff.x) <= abs(diff.y))
				{
					if (diff.y < 0)
					{
						attackDirection = Direction::UP;

						Vector2<int> tempPos = masuPosition + Vector2<int>(0, -1);
						for (int i = -1; i < 2; i++)
						{
							attackPointList.push_back(tempPos + Vector2<int>(i, 0));
						}
					}
					else
					{
						attackDirection = Direction::DOWN;
						Vector2<int> tempPos = masuPosition + Vector2<int>(0, 1);
						for (int i = -1; i < 2; i++)
						{
							attackPointList.push_back(tempPos + Vector2<int>(i, 0));
						}
					}
				}
				else
				{
					if (diff.x > 0)
					{
						attackDirection = Direction::RIGHT;
						Vector2<int> tempPos = masuPosition + Vector2<int>(1, 0);
						for (int i = -1; i < 2; i++)
						{
							attackPointList.push_back(tempPos + Vector2<int>(0, i));
						}
					}
					else
					{
						attackDirection = Direction::LEFT;
						Vector2<int> tempPos = masuPosition + Vector2<int>(-1, 0);
						for (int i = -1; i < 2; i++)
						{
							attackPointList.push_back(tempPos + Vector2<int>(0, i));
						}
					}
				}
			}
			else
			{
				StartMove(enemyStatus->GetMoveSpeedNotice(), StartMoveKind::CLOSE);
			}
		}
		break;
		case 43:
		{
			Vector2<int> diff = playerMap->GetMasuPosition() - masuPosition;

			if ((abs(masuPosition.x - playerMap->GetMasuPosition().x)<=2&& abs(masuPosition.y - playerMap->GetMasuPosition().y)==0)|| (abs(masuPosition.y - playerMap->GetMasuPosition().y) <= 2 && abs(masuPosition.x - playerMap->GetMasuPosition().x) == 0))
			{
				attackKind = 43;
				tempAttackKind = -1;

				if (abs(diff.x) <= abs(diff.y))
				{
					if (diff.y < 0)
					{
						attackDirection = Direction::UP;

						for (int i = 0; i < 2; i++)
						{
							attackPointList.push_back(masuPosition + Vector2<int>(0, -1-i));
						}
					}
					else
					{
						attackDirection = Direction::DOWN;
						for (int i = 0; i < 2; i++)
						{
							attackPointList.push_back(masuPosition + Vector2<int>(0, 1+i));
						}
					}
				}
				else
				{
					if (diff.x > 0)
					{
						attackDirection = Direction::RIGHT;
						for (int i = 0; i < 2; i++)
						{
							attackPointList.push_back(masuPosition + Vector2<int>(1+i, 0));
						}
					}
					else
					{
						attackDirection = Direction::LEFT;
						for (int i = 0; i < 2; i++)
						{
							attackPointList.push_back(masuPosition + Vector2<int>(-1-i, 0));
						}
					}
				}
			}
			else if (abs(diff.x) > 2 || abs(diff.y)>2)
			{
				StartMove(enemyStatus->GetMoveSpeedNotice(), StartMoveKind::CLOSE);
			}
			else
			{
				StartMove(enemyStatus->GetMoveSpeedNotice(), StartMoveKind::ALIGNMENT);
			}
		}
		break;
		}

	}
}

void EnemyMap025::UpdateTempAttackKind()
{
	Vector2<int> diff = playerMap->GetMasuPosition() - masuPosition;

	int randNum = GetRand(1000) % 10;
	if (randNum >= 5)
	{
		tempAttackKind = 42;
	}
	else
	{
		tempAttackKind = 43;
	}
}