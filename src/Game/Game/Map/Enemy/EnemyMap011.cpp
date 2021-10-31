#include"../header/EnemyMap011.h"
#include"../header/PlayerMap.h"
#include"../header/EnemySkillInfoList.h"

const int EnemyMap011::randomMoveCount = 5;

EnemyMap011::EnemyMap011(PlayerData* playerData, PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<EnemyMapPtr>& enemyMapList, list<PeopleMapPtr>& peopleMapList, int id, Vector2<int> masuPosition, Vector2<double>& camera, list<BattleEffectPtr>& battleEffectList, list<TextUIPtr>& textUIList, list<DropItemPtr>& dropItemList, int& mapNum) :EnemyMap(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, id, masuPosition, camera, battleEffectList, textUIList, dropItemList, mapNum)
{
	enemyStatus = new EnemyStatus(11);
	kind = 11;
	tempAttackKind = -1;
	randomMoveCounter = 0;
}

EnemyMap011::~EnemyMap011()
{

}

void EnemyMap011::UpdateNotice()
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
		case 16:
		{
			if (abs(masuPosition.x - playerMap->GetMasuPosition().x) + abs(masuPosition.y - playerMap->GetMasuPosition().y) == 1)
			{
				attackKind = 16;
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
		case 17:
		{
			Vector2<int> diff = playerMap->GetMasuPosition() - masuPosition;

			if (diff.length() <= 7&&randomMoveCounter<randomMoveCount)
			{
				StartMove(enemyStatus->GetMoveSpeedNotice(), StartMoveKind::AWAY);
				randomMoveCounter++;
			}
			else if ((abs(diff.x) <= 9 && diff.y == 0) || (abs(diff.y) <= 9 && diff.x == 0))
			{
				randomMoveCounter = 0;
				attackKind = 17;
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
			else if (abs(diff.x)>9 || abs(diff.y)>9)
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

void EnemyMap011::UpdateTempAttackKind()
{
	Vector2<int> diff = playerMap->GetMasuPosition() - masuPosition;

	if (diff.length() <= 5)
	{
		int randNum = GetRand(1000) % 10;
		if(randNum>=3)
		{ 
			tempAttackKind = 16;
		}
		else
		{
			tempAttackKind = 17;
		}
	}
	else
	{
		tempAttackKind = 17;
	}
}