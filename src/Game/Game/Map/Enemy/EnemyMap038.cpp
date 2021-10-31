#include"../header/EnemyMap038.h"
#include"../header/PlayerMap.h"
#include"../header/EnemySkillInfoList.h"

EnemyMap038::EnemyMap038(PlayerData* playerData, PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<EnemyMapPtr>& enemyMapList, list<PeopleMapPtr>& peopleMapList, int id, Vector2<int> masuPosition, Vector2<double>& camera, list<BattleEffectPtr>& battleEffectList, list<TextUIPtr>& textUIList, list<DropItemPtr>& dropItemList, int& mapNum) :EnemyMap(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, id, masuPosition, camera, battleEffectList, textUIList, dropItemList, mapNum)
{
	enemyStatus = new EnemyStatus(38);
	kind = 38;
	tempAttackKind = -1;
}

EnemyMap038::~EnemyMap038()
{

}

void EnemyMap038::UpdateNotice()
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
		case 72:
		{
			if (abs(masuPosition.x - playerMap->GetMasuPosition().x) + abs(masuPosition.y - playerMap->GetMasuPosition().y) == 1)
			{
				attackKind = 72;

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
					assert(0 && "EnemyMap000::UpdateNotice()");
				}
				attackPointList.push_back(playerMap->GetMasuPosition());
			}
			else
			{
				StartMove(enemyStatus->GetMoveSpeedNotice(), StartMoveKind::CLOSE);
			}
		}
		break;
		case 73:
		{
			Vector2<int> diff = playerMap->GetMasuPosition() - masuPosition;

			if (abs(masuPosition.x - playerMap->GetMasuPosition().x) + abs(masuPosition.y - playerMap->GetMasuPosition().y) <= 2)
			{
				attackKind = 73;
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
		case 74:
		{
			Vector2<int> diff = playerMap->GetMasuPosition() - masuPosition;
			if (diff.length() <= 7)
			{
				attackKind = 74;
				tempAttackKind = -1;
				attackPointList.push_back(playerMap->GetMasuPosition());
				for (int i = -1; i < 2; i++)for (int j = -1; j < 2; j++)
				{
					if (i != 0 || j != 0)
					{
						attackPointList.push_back(playerMap->GetMasuPosition() + Vector2<int>(i, j));
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

void EnemyMap038::UpdateTempAttackKind()
{
	Vector2<int> diff = playerMap->GetMasuPosition() - masuPosition;

	if (diff.length() <= 1)
	{
		int randNum = GetRand(1000) % 10;
		if (randNum >= 2)
		{
			tempAttackKind = 73;
		}
		else
		{
			tempAttackKind = 72;
		}
	}
	else if (diff.length() <= 3)
	{
		tempAttackKind = 73;
	}
	else
	{
		tempAttackKind = 74;
	}
}