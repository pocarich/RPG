#include"../header/EnemyMap004.h"
#include"../header/PlayerMap.h"
#include"../header/EnemySkillInfoList.h"

EnemyMap004::EnemyMap004(PlayerData* playerData, PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<EnemyMapPtr>& enemyMapList, list<PeopleMapPtr>& peopleMapList, int id, Vector2<int> masuPosition, Vector2<double>& camera, list<BattleEffectPtr>& battleEffectList, list<TextUIPtr>& textUIList, list<DropItemPtr>& dropItemList, int& mapNum) :EnemyMap(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, id, masuPosition, camera, battleEffectList, textUIList, dropItemList, mapNum)
{
	enemyStatus = new EnemyStatus(4);
	kind = 4;
	tempAttackKind = -1;
}

EnemyMap004::~EnemyMap004()
{

}

void EnemyMap004::UpdateNotice()
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
		case 6:
		{
			if (abs(masuPosition.x - playerMap->GetMasuPosition().x) + abs(masuPosition.y - playerMap->GetMasuPosition().y) == 1)
			{
				attackKind = 6;
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
		case 5:
		{
			Vector2<int> diff = playerMap->GetMasuPosition() - masuPosition;

			if ((abs(diff.x) <= 7 && diff.y == 0) || (abs(diff.y) <= 7 && diff.x == 0))
			{
				attackKind = 5;
				tempAttackKind = -1;

				if (diff.x > 0)
				{
					attackDirection = Direction::RIGHT;
					for (int i = 0; i < 7; i++)
					{
						Vector2<int> attackPoint = masuPosition + Vector2<int>(1 + i, 0);
						attackPointList.push_back(attackPoint);
					}
				}
				else if (diff.x < 0)
				{
					attackDirection = Direction::LEFT;
					for (int i = 0; i < 7; i++)
					{
						Vector2<int> attackPoint = masuPosition + Vector2<int>(-1 - i, 0);
						attackPointList.push_back(attackPoint);
					}
				}
				else if (diff.y > 0)
				{
					attackDirection = Direction::DOWN;
					for (int i = 0; i < 7; i++)
					{
						Vector2<int> attackPoint = masuPosition + Vector2<int>(0, 1 + i);
						attackPointList.push_back(attackPoint);
					}
				}
				else if (diff.y < 0)
				{
					attackDirection = Direction::UP;
					for (int i = 0; i < 7; i++)
					{
						Vector2<int> attackPoint = masuPosition + Vector2<int>(0, -1 - i);
						attackPointList.push_back(attackPoint);
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

void EnemyMap004::UpdateTempAttackKind()
{
	Vector2<int> diff = playerMap->GetMasuPosition() - masuPosition;

	if (diff.length() <= 4)
	{
		tempAttackKind = 6;
	}
	else
	{
		tempAttackKind = 5;
	}
}