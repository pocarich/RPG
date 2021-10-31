#include"../header/EnemyMap032.h"
#include"../header/PlayerMap.h"
#include"../header/EnemySkillInfoList.h"
#include"../header/BattleEffectE050.h"

EnemyMap032::EnemyMap032(PlayerData* playerData, PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<EnemyMapPtr>& enemyMapList, list<PeopleMapPtr>& peopleMapList, int id, Vector2<int> masuPosition, Vector2<double>& camera, list<BattleEffectPtr>& battleEffectList, list<TextUIPtr>& textUIList, list<DropItemPtr>& dropItemList, int& mapNum) :EnemyMap(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, id, masuPosition, camera, battleEffectList, textUIList, dropItemList, mapNum)
{
	enemyStatus = new EnemyStatus(32);
	kind = 32;
	tempAttackKind = -1;
}

EnemyMap032::~EnemyMap032()
{

}

void EnemyMap032::UpdateNotice()
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
		case 57:
		{
			Vector2<int> diff = playerMap->GetMasuPosition() - masuPosition;

			if (abs(masuPosition.x - playerMap->GetMasuPosition().x) + abs(masuPosition.y - playerMap->GetMasuPosition().y) <= 2)
			{
				attackKind = 57;
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
		case 58:
		{
			Vector2<int> diff = playerMap->GetMasuPosition() - masuPosition;

			if ((abs(diff.x) <= 7 && diff.y == 0) || (abs(diff.y) <= 7 && diff.x == 0))
			{
				attackKind = 58;
				tempAttackKind = -1;

				if (diff.x > 0)
				{
					attackDirection = Direction::RIGHT;
					for (int i = 0; i < 9; i++)
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
					for (int i = 0; i < 9; i++)
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
					for (int i = 0; i < 9; i++)
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
					for (int i = 0; i < 9; i++)
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

void EnemyMap032::UpdateTempAttackKind()
{
	Vector2<int> diff = playerMap->GetMasuPosition() - masuPosition;

	if (diff.length() <= 4)
	{
		tempAttackKind = 57;
	}
	else
	{
		tempAttackKind = 58;
	}
}