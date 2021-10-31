#include"../header/EnemyMap019.h"
#include"../header/PlayerMap.h"
#include"../header/EnemySkillInfoList.h"

EnemyMap019::EnemyMap019(PlayerData* playerData, PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<EnemyMapPtr>& enemyMapList, list<PeopleMapPtr>& peopleMapList, int id, Vector2<int> masuPosition, Vector2<double>& camera, list<BattleEffectPtr>& battleEffectList, list<TextUIPtr>& textUIList, list<DropItemPtr>& dropItemList, int& mapNum) :EnemyMap(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, id, masuPosition, camera, battleEffectList, textUIList, dropItemList, mapNum)
{
	enemyStatus = new EnemyStatus(19);
	kind = 19;
	tempAttackKind = -1;
}

EnemyMap019::~EnemyMap019()
{

}

void EnemyMap019::UpdateNotice()
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
		case 31:
		{
			Vector2<int> diff = playerMap->GetMasuPosition() - masuPosition;

			if (abs(masuPosition.x - playerMap->GetMasuPosition().x) + abs(masuPosition.y - playerMap->GetMasuPosition().y) <= 3)
			{
				attackKind = 31;
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
		case 32:
		{
			Vector2<int> diff = playerMap->GetMasuPosition() - masuPosition;

			if (abs(masuPosition.x - playerMap->GetMasuPosition().x) + abs(masuPosition.y - playerMap->GetMasuPosition().y) <= 1)
			{
				attackKind = 32;
				tempAttackKind = -1;

				attackDirection = Direction::DOWN;
				for (int i = -1; i < 2; i++)for (int j = -1; j < 2; j++)
				{
					if (!(i == 0 && j == 0))
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
		}

	}
}

void EnemyMap019::UpdateTempAttackKind()
{
	Vector2<int> diff = playerMap->GetMasuPosition() - masuPosition;

	if (diff.length() <= 1)
	{
		int randNum = GetRand(1000) % 10;
		if (randNum >= 2)
		{
			tempAttackKind = 31;
		}
		else
		{
			tempAttackKind = 32;
		}
	}
	else
	{
		tempAttackKind = 31;
	}
}