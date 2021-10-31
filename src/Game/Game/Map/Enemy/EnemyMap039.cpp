#include"../header/EnemyMap039.h"
#include"../header/PlayerMap.h"
#include"../header/EnemySkillInfoList.h"

EnemyMap039::EnemyMap039(PlayerData* playerData, PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<EnemyMapPtr>& enemyMapList, list<PeopleMapPtr>& peopleMapList, int id, Vector2<int> masuPosition, Vector2<double>& camera, list<BattleEffectPtr>& battleEffectList, list<TextUIPtr>& textUIList, list<DropItemPtr>& dropItemList, int& mapNum) :EnemyMap(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, id, masuPosition, camera, battleEffectList, textUIList, dropItemList, mapNum)
{
	enemyStatus = new EnemyStatus(39);
	kind = 39;
	tempAttackKind = -1;
}

EnemyMap039::~EnemyMap039()
{

}

void EnemyMap039::UpdateNotice()
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
		case 75:
		{
			Vector2<int> diff = playerMap->GetMasuPosition() - masuPosition;
			if (diff.length() <= 7)
			{
				attackKind = 75;
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
		case 76:
		{
			Vector2<int> diff = playerMap->GetMasuPosition() - masuPosition;
			if (abs(diff.x) <= 2 && abs(diff.y) <= 2)
			{
				attackKind = 76;
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
		case 77:
		{
			Vector2<int> diff = playerMap->GetMasuPosition() - masuPosition;

			if ((abs(diff.x) <= 6 && diff.y == 0) || (abs(diff.y) <= 6 && diff.x == 0))
			{
				attackKind = 77;
				tempAttackKind = -1;

				if (diff.x > 0)
				{
					attackDirection = Direction::RIGHT;
					for (int i = 0; i < 3; i++)
					{
						attackPointList.push_back(masuPosition + Vector2<int>(1 + i, 0));
					}
					for (int i = -2; i < 3; i++) for (int j = -2; j < 3; j++)
					{
						attackPointList.push_back(masuPosition + Vector2<int>(6 + i, j));
					}
				}
				else if (diff.x < 0)
				{
					attackDirection = Direction::LEFT;
					for (int i = 0; i < 3; i++)
					{
						attackPointList.push_back(masuPosition + Vector2<int>(-1 - i, 0));
					}
					for (int i = -2; i < 3; i++) for (int j = -2; j < 3; j++)
					{
						attackPointList.push_back(masuPosition + Vector2<int>(-6 + i, j));
					}
				}
				else if (diff.y > 0)
				{
					attackDirection = Direction::DOWN;
					for (int i = 0; i < 3; i++)
					{
						attackPointList.push_back(masuPosition + Vector2<int>(0, 1 + i));
					}
					for (int i = -2; i < 3; i++) for (int j = -2; j < 3; j++)
					{
						attackPointList.push_back(masuPosition + Vector2<int>(i, 6 + j));
					}
				}
				else if (diff.y < 0)
				{
					attackDirection = Direction::UP;
					for (int i = 0; i < 3; i++)
					{
						attackPointList.push_back(masuPosition + Vector2<int>(0, -1 - i));
					}
					for (int i = -2; i < 3; i++) for (int j = -2; j < 3; j++)
					{
						attackPointList.push_back(masuPosition + Vector2<int>(i, -6 + j));
					}
				}
				else
				{
					assert(0 && "EnemyaMap001::UpdateNotice()");
				}
			}
			else if (abs(diff.x) > 6 || abs(diff.y)>6)
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

void EnemyMap039::UpdateTempAttackKind()
{
	Vector2<int> diff = playerMap->GetMasuPosition() - masuPosition;

	int randNum = GetRand(1000) % 10;
	if (randNum >= 5)
	{
		if (diff.length() <= 3)
		{
			tempAttackKind = 76;
		}
		else if (abs(diff.x) <= 2 || abs(diff.y) <= 2)
		{
			tempAttackKind = 77;
		}
		else
		{
			tempAttackKind = 75;
		}
	}
	else
	{
		tempAttackKind = 75;
	}
}