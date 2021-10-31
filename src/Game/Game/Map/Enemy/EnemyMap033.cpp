#include"../header/EnemyMap033.h"
#include"../header/PlayerMap.h"
#include"../header/EnemySkillInfoList.h"

EnemyMap033::EnemyMap033(PlayerData* playerData, PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<EnemyMapPtr>& enemyMapList, list<PeopleMapPtr>& peopleMapList, int id, Vector2<int> masuPosition, Vector2<double>& camera, list<BattleEffectPtr>& battleEffectList, list<TextUIPtr>& textUIList, list<DropItemPtr>& dropItemList, int& mapNum) :EnemyMap(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, id, masuPosition, camera, battleEffectList, textUIList, dropItemList, mapNum)
{
	enemyStatus = new EnemyStatus(33);
	kind = 33;
	tempAttackKind = -1;
}

EnemyMap033::~EnemyMap033()
{

}

void EnemyMap033::UpdateNotice()
{
	static const int width[] = { 0,0,1,1,2,2,3 };
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
		case 59:
		{
			Vector2<int> diff = playerMap->GetMasuPosition() - masuPosition;
			if (abs(diff.x) <= 2 && abs(diff.y) <= 2)
			{
				attackKind = 59;
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
		case 60:
		{
			Vector2<int> diff = playerMap->GetMasuPosition() - masuPosition;
			if ((abs(diff.x) <= 5 && diff.y == 0) || (abs(diff.y) <= 5 && diff.x == 0))
			{
				attackKind = 60;
				tempAttackKind = -1;

				if (diff.x > 0)
				{
					attackDirection = Direction::RIGHT;
					for (int i = 0; i < 7; i++)
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
					for (int i = 0; i < 7; i++)
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
					for (int i = 0; i < 7; i++)
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
					for (int i = 0; i < 7; i++)
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
			else if (abs(diff.x) > 5 || abs(diff.y)>5)
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

void EnemyMap033::UpdateTempAttackKind()
{
	Vector2<int> diff = playerMap->GetMasuPosition() - masuPosition;

	if (diff.length() <= 4)
	{
		tempAttackKind = 59;
	}
	else
	{
		tempAttackKind = 60;
	}
}