#include"../header/EnemyMap034.h"
#include"../header/PlayerMap.h"
#include"../header/EnemySkillInfoList.h"

EnemyMap034::EnemyMap034(PlayerData* playerData, PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<EnemyMapPtr>& enemyMapList, list<PeopleMapPtr>& peopleMapList, int id, Vector2<int> masuPosition, Vector2<double>& camera, list<BattleEffectPtr>& battleEffectList, list<TextUIPtr>& textUIList, list<DropItemPtr>& dropItemList, int& mapNum) :EnemyMap(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, id, masuPosition, camera, battleEffectList, textUIList, dropItemList, mapNum)
{
	enemyStatus = new EnemyStatus(34);
	kind = 34;
	tempAttackKind = -1;
}

EnemyMap034::~EnemyMap034()
{

}

void EnemyMap034::UpdateNotice()
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
		case 61:
		{
			Vector2<int> diff = playerMap->GetMasuPosition() - masuPosition;

			if (abs(masuPosition.x - playerMap->GetMasuPosition().x) + abs(masuPosition.y - playerMap->GetMasuPosition().y) <= 2)
			{
				attackKind = 61;
				tempAttackKind = -1;

				if (abs(diff.x) <= abs(diff.y))
				{
					if (diff.y < 0)
					{
						attackDirection = Direction::UP;

						Vector2<int> tempPos = masuPosition + Vector2<int>(0, -1);
						for (int i = -1; i < 2; i++)for (int j = -1; j < 2; j++)
						{
							attackPointList.push_back(tempPos + Vector2<int>(i, j));
						}
					}
					else
					{
						attackDirection = Direction::DOWN;
						Vector2<int> tempPos = masuPosition + Vector2<int>(0, 1);
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
						Vector2<int> tempPos = masuPosition + Vector2<int>(1, 0);
						for (int i = -1; i < 2; i++)for (int j = -1; j < 2; j++)
						{
							attackPointList.push_back(tempPos + Vector2<int>(i, j));
						}
					}
					else
					{
						attackDirection = Direction::LEFT;
						Vector2<int> tempPos = masuPosition + Vector2<int>(-1, 0);
						for (int i = -1; i < 2; i++)for (int j = -1; j < 2; j++)
						{
							attackPointList.push_back(tempPos + Vector2<int>(i, j));
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
		case 62:
		{
			Vector2<int> diff = playerMap->GetMasuPosition() - masuPosition;
			if ((abs(diff.x) <= 4 && diff.y == 0) || (abs(diff.y) <= 4 && diff.x == 0))
			{
				attackKind = 62;
				tempAttackKind = -1;

				if (diff.x > 0)
				{
					attackDirection = Direction::RIGHT;
					for (int i = 0; i < 5; i++)
					{
						for (int j = -width[i]; j < width[i] + 1; j++)
						{
							Vector2<int> attackPoint = masuPosition + Vector2<int>(1 + i, j);
							attackPointList.push_back(attackPoint);
						}
					}
				}
				else if (diff.x < 0)
				{
					attackDirection = Direction::LEFT;
					for (int i = 0; i < 5; i++)
					{
						for (int j = -width[i]; j < width[i] + 1; j++)
						{
							Vector2<int> attackPoint = masuPosition + Vector2<int>(-1 - i, j);
							attackPointList.push_back(attackPoint);
						}
					}
				}
				else if (diff.y > 0)
				{
					attackDirection = Direction::DOWN;
					for (int i = 0; i < 5; i++)
					{
						for (int j = -width[i]; j < width[i] + 1; j++)
						{
							Vector2<int> attackPoint = masuPosition + Vector2<int>(j, 1 + i);
							attackPointList.push_back(attackPoint);
						}
					}
				}
				else if (diff.y < 0)
				{
					attackDirection = Direction::UP;
					for (int i = 0; i < 5; i++)
					{
						for (int j = -width[i]; j < width[i] + 1; j++)
						{
							Vector2<int> attackPoint = masuPosition + Vector2<int>(j, -1 - i);
							attackPointList.push_back(attackPoint);
						}
					}
				}
				else
				{
					assert(0 && "EnemyaMap001::UpdateNotice()");
				}
			}
			else if (abs(diff.x) > 4 || abs(diff.y)>4)
			{
				StartMove(enemyStatus->GetMoveSpeedNotice(), StartMoveKind::CLOSE);
			}
			else
			{
				StartMove(enemyStatus->GetMoveSpeedNotice(), StartMoveKind::ALIGNMENT);
			}
		}
		break;
		case 63:
		{
			Vector2<int> diff = playerMap->GetMasuPosition() - masuPosition;
			if (diff.length() <= 7)
			{
				attackKind = 63;
				tempAttackKind = -1;
				for (int i = -1; i < 2; i++)for (int j = -1; j < 2; j++)
				{
					attackPointList.push_back(playerMap->GetMasuPosition() + Vector2<int>(i, j));
				}
				attackPointList.push_back(playerMap->GetMasuPosition() + Vector2<int>(2, 0));
				attackPointList.push_back(playerMap->GetMasuPosition() + Vector2<int>(-2, 0));
				attackPointList.push_back(playerMap->GetMasuPosition() + Vector2<int>(0, 2));
				attackPointList.push_back(playerMap->GetMasuPosition() + Vector2<int>(0, -2));
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

void EnemyMap034::UpdateTempAttackKind()
{
	Vector2<int> diff = playerMap->GetMasuPosition() - masuPosition;

	if (diff.length() <= 3)
	{
		tempAttackKind = 61;
	}
	else if (diff.length() <= 5)
	{
		tempAttackKind = 62;
	}
	else
	{
		tempAttackKind = 63;
	}
}