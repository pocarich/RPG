#include"../header/EnemyMap035.h"
#include"../header/PlayerMap.h"
#include"../header/EnemySkillInfoList.h"

EnemyMap035::EnemyMap035(PlayerData* playerData, PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<EnemyMapPtr>& enemyMapList, list<PeopleMapPtr>& peopleMapList, int id, Vector2<int> masuPosition, Vector2<double>& camera, list<BattleEffectPtr>& battleEffectList, list<TextUIPtr>& textUIList, list<DropItemPtr>& dropItemList, int& mapNum) :EnemyMap(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, id, masuPosition, camera, battleEffectList, textUIList, dropItemList, mapNum)
{
	enemyStatus = new EnemyStatus(35);
	kind = 35;
	tempAttackKind = -1;
}

EnemyMap035::~EnemyMap035()
{

}

void EnemyMap035::UpdateNotice()
{
	static const int width[] = { 0,1,2,3,3 };
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
		case 64:
		{
			Vector2<int> diff = playerMap->GetMasuPosition() - masuPosition;

			if (abs(masuPosition.x - playerMap->GetMasuPosition().x) + abs(masuPosition.y - playerMap->GetMasuPosition().y) <= 3)
			{
				attackKind = 64;
				tempAttackKind = -1;

				if (abs(diff.x) <= abs(diff.y))
				{
					if (diff.y < 0)
					{
						attackDirection = Direction::UP;

						Vector2<int> tempPos = masuPosition + Vector2<int>(0, -2);
						for (int i = -1; i < 2; i++)for (int j = -1; j < 2; j++)
						{
							attackPointList.push_back(tempPos + Vector2<int>(i, j));
						}
					}
					else
					{
						attackDirection = Direction::DOWN;
						Vector2<int> tempPos = masuPosition + Vector2<int>(0, 2);
						for (int i = -1; i < 2; i++)for (int j = -1; j < 2; j++)
						{
							attackPointList.push_back(tempPos + Vector2<int>(i, j));
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
							attackPointList.push_back(tempPos + Vector2<int>(i, j));
						}
					}
					else
					{
						attackDirection = Direction::LEFT;
						Vector2<int> tempPos = masuPosition + Vector2<int>(-2, 0);
						for (int i = -1; i < 2; i++)for (int j = -1; j < 2; j++)
						{
							attackPointList.push_back(tempPos + Vector2<int>(i, j));
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
		case 65:
		{
			Vector2<int> diff = playerMap->GetMasuPosition() - masuPosition;
			if (abs(diff.x) <= 2 && abs(diff.y) <= 2)
			{
				attackKind = 65;
				tempAttackKind = -1;

				attackDirection = Direction::DOWN;
				for (int i = -2; i < 3; i++)for (int j = -2; j < 3; j++)
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
		case 66:
		{
			Vector2<int> diff = playerMap->GetMasuPosition() - masuPosition;

			if ((abs(diff.x) <= 7 && diff.y == 0) || (abs(diff.y) <= 7 && diff.x == 0))
			{
				attackKind = 66;
				tempAttackKind = -1;

				if (diff.x > 0)
				{
					attackDirection = Direction::RIGHT;
					for (int i = 0; i < 10; i++)
					{
						Vector2<int> attackPoint = masuPosition + Vector2<int>(1 + i, 0);
						for (int j = -1; j < 2; j++)
						{
							attackPointList.push_back(attackPoint + Vector2<int>(0, j));
						}
					}
				}
				else if (diff.x < 0)
				{
					attackDirection = Direction::LEFT;
					for (int i = 0; i < 10; i++)
					{
						Vector2<int> attackPoint = masuPosition + Vector2<int>(-1 - i, 0);
						for (int j = -1; j < 2; j++)
						{
							attackPointList.push_back(attackPoint + Vector2<int>(0, j));
						}
					}
				}
				else if (diff.y > 0)
				{
					attackDirection = Direction::DOWN;
					for (int i = 0; i < 10; i++)
					{
						Vector2<int> attackPoint = masuPosition + Vector2<int>(0, 1 + i);
						for (int j = -1; j < 2; j++)
						{
							attackPointList.push_back(attackPoint + Vector2<int>(j, 0));
						}
					}
				}
				else if (diff.y < 0)
				{
					attackDirection = Direction::UP;
					for (int i = 0; i < 10; i++)
					{
						Vector2<int> attackPoint = masuPosition + Vector2<int>(0, -1 - i);
						for (int j = -1; j < 2; j++)
						{
							attackPointList.push_back(attackPoint + Vector2<int>(j, 0));
						}
					}
				}
				else
				{
					assert(0 && "EnemyaMap001::UpdateNotice()");
				}
			}
			else if (abs(diff.x)>7 || abs(diff.y)>7)
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

void EnemyMap035::UpdateTempAttackKind()
{
	Vector2<int> diff = playerMap->GetMasuPosition() - masuPosition;

	if (diff.length() <= 4)
	{
		int randNum = GetRand(1000) % 10;
		if (randNum >= 5)
		{
			tempAttackKind = 64;
		}
		else
		{
			tempAttackKind = 65;
		}
	}
	else
	{
		tempAttackKind = 66;
	}
}