#include"../header/EnemyMap031.h"
#include"../header/PlayerMap.h"
#include"../header/EnemySkillInfoList.h"

EnemyMap031::EnemyMap031(PlayerData* playerData, PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<EnemyMapPtr>& enemyMapList, list<PeopleMapPtr>& peopleMapList, int id, Vector2<int> masuPosition, Vector2<double>& camera, list<BattleEffectPtr>& battleEffectList, list<TextUIPtr>& textUIList, list<DropItemPtr>& dropItemList, int& mapNum) :EnemyMap(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, id, masuPosition, camera, battleEffectList, textUIList, dropItemList, mapNum)
{
	enemyStatus = new EnemyStatus(31);
	kind = 31;
	tempAttackKind = -1;
}

EnemyMap031::~EnemyMap031()
{

}

void EnemyMap031::UpdateNotice()
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
		case 55:
		{
			Vector2<int> diff = playerMap->GetMasuPosition() - masuPosition;
			if (abs(diff.x) <= 2 && abs(diff.y) <= 2)
			{
				attackKind = 55;
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
		case 56:
		{
				Vector2<int> diff = playerMap->GetMasuPosition() - masuPosition;
				if ((abs(diff.x) <= 3 && diff.y == 0) || (abs(diff.y) <= 3 && diff.x == 0))
				{
					attackKind = 56;
					tempAttackKind = -1;

					if (diff.x > 0)
					{
						attackDirection = Direction::RIGHT;
						for (int i = 0; i < 1; i++)
						{
							Vector2<int> attackPoint = masuPosition + Vector2<int>(1 + i, 0);
							attackPointList.push_back(attackPoint);
						}
						for (int i = -1; i < 2; i++)for (int j = -1; j < 2; j++)
						{
							Vector2<int> attackPoint = masuPosition + Vector2<int>(3 + i, j);
							attackPointList.push_back(attackPoint);
						}
					}
					else if (diff.x < 0)
					{
						attackDirection = Direction::LEFT;
						for (int i = 0; i < 1; i++)
						{
							Vector2<int> attackPoint = masuPosition + Vector2<int>(-1 - i, 0);
							attackPointList.push_back(attackPoint);
						}
						for (int i = -1; i < 2; i++)for (int j = -1; j < 2; j++)
						{
							Vector2<int> attackPoint = masuPosition + Vector2<int>(-3 + i, j);
							attackPointList.push_back(attackPoint);
						}
					}
					else if (diff.y > 0)
					{
						attackDirection = Direction::DOWN;
						for (int i = 0; i < 1; i++)
						{
							Vector2<int> attackPoint = masuPosition + Vector2<int>(0, 1 + i);
							attackPointList.push_back(attackPoint);
						}
						for (int i = -1; i < 2; i++)for (int j = -1; j < 2; j++)
						{
							Vector2<int> attackPoint = masuPosition + Vector2<int>(i, 3 + j);
							attackPointList.push_back(attackPoint);
						}
					}
					else if (diff.y < 0)
					{
						attackDirection = Direction::UP;
						for (int i = 0; i < 1; i++)
						{
							Vector2<int> attackPoint = masuPosition + Vector2<int>(0, -1 - i);
							attackPointList.push_back(attackPoint);
						}
						for (int i = -1; i < 2; i++)for (int j = -1; j < 2; j++)
						{
							Vector2<int> attackPoint = masuPosition + Vector2<int>(i, -3 + j);
							attackPointList.push_back(attackPoint);
						}
					}
					else
					{
						assert(0 && "EnemyaMap001::UpdateNotice()");
					}
				}
				else if (abs(diff.x)>3 || abs(diff.y)>3)
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

void EnemyMap031::UpdateTempAttackKind()
{
	Vector2<int> diff = playerMap->GetMasuPosition() - masuPosition;

	if (abs(diff.x) <= 2 && abs(diff.y) <= 2)
	{
		tempAttackKind = 55;
	}
	else
	{
		tempAttackKind = 56;
	}
}