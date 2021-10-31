#include"../header/BossMap007.h"
#include"../header/BattleEffectE078_1.h"
#include"../header/PlayerMap.h"
#include"../header/EnemySkillInfoList.h"
#include"../header/BattleEffectE087.h"

BossMap007::BossMap007(PlayerData* playerData, PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<EnemyMapPtr>& enemyMapList, list<PeopleMapPtr>& peopleMapList, list<BattleEffectPtr>& battleEffectList, list<TextUIPtr>& textUIList, list<DropItemPtr>& dropItemList, int id, Vector2<int> masuPosition, Vector2<double>& camera, int& mapNum, int standFlag,int specialEventNum) :BossMap(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, battleEffectList, textUIList, dropItemList, id, 0, masuPosition, camera, mapNum, standFlag,specialEventNum)
{
	bossStatus = new BossStatus(0);
}

BossMap007::~BossMap007()
{

}

void BossMap007::UpdateNotice()
{
	static const int width[] = { 0,0,1,2,3,4 };
	
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
		Vector2<int> diff = playerMap->GetMasuPosition() - masuPosition.front();

		switch (tempAttackKind)
		{
		case 84:
		{
			if (moveCounter < 3)
			{
				moveCounter++;
				StartMove(4.0, StartMoveKind::RAMDOM);
			}
			else
			{
				if (abs(masuPosition.front().x - playerMap->GetMasuPosition().x)<=1&&abs(masuPosition.front().y - playerMap->GetMasuPosition().y) <= 2|| abs(masuPosition.front().x - playerMap->GetMasuPosition().x) <= 2 && abs(masuPosition.front().y - playerMap->GetMasuPosition().y) <= 1)
				{
					attackKind = 84;

					if (abs(diff.x) <= abs(diff.y))
					{
						if (diff.y < 0)
						{
							attackDirection = Direction::UP;

							Vector2<int> tempPos = masuPosition.front() + Vector2<int>(0, -3);
							for (int i = -1; i < 2; i++)for (int j = -1; j < 2; j++)
							{
								attackPointList.push_back(tempPos + Vector2<int>(i, j));
							}
						}
						else
						{
							attackDirection = Direction::DOWN;
							Vector2<int> tempPos = masuPosition.front() + Vector2<int>(0, 3);
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
							Vector2<int> tempPos = masuPosition.front() + Vector2<int>(3, 0);
							for (int i = -1; i < 2; i++)for (int j = -1; j < 2; j++)
							{
								attackPointList.push_back(tempPos + Vector2<int>(i, j));
							}
						}
						else
						{
							attackDirection = Direction::LEFT;
							Vector2<int> tempPos = masuPosition.front() + Vector2<int>(-3, 0);
							for (int i = -1; i < 2; i++)for (int j = -1; j < 2; j++)
							{
								attackPointList.push_back(tempPos + Vector2<int>(i, j));
							}
						}
					}
				}
				else if (diff.length() > 3)
				{
					StartMove(4.0, StartMoveKind::CLOSE);
				}
				else
				{
					StartMove(4.0, StartMoveKind::ALIGNMENT);
				}
			}
		}
		break;
		case 85:
		{
			if (moveCounter < 3)
			{
				moveCounter++;
				StartMove(2, StartMoveKind::RAMDOM);
			}
			else
			{
				if ((abs(diff.x) <= 4 && diff.y == 0) || (abs(diff.y) <= 4 && diff.x == 0))
				{
					attackKind = 85;

					if (diff.x > 0)
					{
						attackDirection = Direction::RIGHT;
						for (int i = 1; i < 6; i++)
						{
							for (int j = -width[i]; j < width[i] + 1; j++)
							{
								Vector2<int> attackPoint = masuPosition.front() + Vector2<int>(1 + i, j);
								attackPointList.push_back(attackPoint);
							}
						}
					}
					else if (diff.x < 0)
					{
						attackDirection = Direction::LEFT;
						for (int i = 1; i < 6; i++)
						{
							for (int j = -width[i]; j < width[i] + 1; j++)
							{
								Vector2<int> attackPoint = masuPosition.front() + Vector2<int>(-1 - i, j);
								attackPointList.push_back(attackPoint);
							}
						}
					}
					else if (diff.y > 0)
					{
						attackDirection = Direction::DOWN;
						for (int i = 1; i < 6; i++)
						{
							for (int j = -width[i]; j < width[i] + 1; j++)
							{
								Vector2<int> attackPoint = masuPosition.front() + Vector2<int>(j, 1 + i);
								attackPointList.push_back(attackPoint);
							}
						}
					}
					else if (diff.y < 0)
					{
						attackDirection = Direction::UP;
						for (int i = 1; i < 6; i++)
						{
							for (int j = -width[i]; j < width[i] + 1; j++)
							{
								Vector2<int> attackPoint = masuPosition.front() + Vector2<int>(j, -1 - i);
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
					StartMove(4.0, StartMoveKind::CLOSE);
				}
				else
				{
					StartMove(4.0, StartMoveKind::ALIGNMENT);
				}
			}
		}
		break;
		case 86:
		{
			if ((abs(diff.x) <= 8 && diff.y == 0) || (abs(diff.y) <= 8 && diff.x == 0) || moveCounter == 15)
			{
				attackKind = 86;

				if (diff.x > 0)
				{
					attackDirection = Direction::RIGHT;
					for (int i = 0; i < 12; i++)
					{
						Vector2<int> attackPoint = masuPosition.front() + Vector2<int>(2 + i, 0);
						for (int j = -1; j < 2; j++)
						{
							attackPointList.push_back(attackPoint + Vector2<int>(0, j));
						}
					}
				}
				else if (diff.x < 0)
				{
					attackDirection = Direction::LEFT;
					for (int i = 0; i < 12; i++)
					{
						Vector2<int> attackPoint = masuPosition.front() + Vector2<int>(-2 - i, 0);
						for (int j = -1; j < 2; j++)
						{
							attackPointList.push_back(attackPoint + Vector2<int>(0, j));
						}
					}
				}
				else if (diff.y > 0)
				{
					attackDirection = Direction::DOWN;
					for (int i = 0; i < 12; i++)
					{
						Vector2<int> attackPoint = masuPosition.front() + Vector2<int>(0, 2 + i);
						for (int j = -1; j < 2; j++)
						{
							attackPointList.push_back(attackPoint + Vector2<int>(j, 0));
						}
					}
				}
				else if (diff.y < 0)
				{
					attackDirection = Direction::UP;
					for (int i = 0; i < 12; i++)
					{
						Vector2<int> attackPoint = masuPosition.front() + Vector2<int>(0, -2 - i);
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
			else if (abs(diff.x)>8 || abs(diff.y)>8)
			{
				StartMove(4.0, StartMoveKind::CLOSE);
				moveCounter++;
			}
			else
			{
				StartMove(4.0, StartMoveKind::ALIGNMENT);
				moveCounter++;
			}
		}
		break;
		case 87:
		{
			attackKind = 87;

			attackDirection = Direction::DOWN;
			attackPointList.push_back(masuPosition.front());
			for (int i = -1; i < 2; i++)for (int j = -1; j < 2; j++)
			{
				if (i != 0 || j != 0)
				{
					attackPointList.push_back(masuPosition.front() + Vector2<int>(i, j));
				}
			}
		}
		break;
		case 88:
		{
			if ((abs(diff.x) <= 7 && diff.y == 0) || (abs(diff.y) <= 7 && diff.x == 0) || moveCounter == 15)
			{
				attackKind = 88;
				tempAttackKind = -1;

				if (diff.x > 0)
				{
					attackDirection = Direction::RIGHT;
					for (int i = 0; i < 2; i++)
					{
						attackPointList.push_back(masuPosition.front() + Vector2<int>(2 + i, 0));
					}
					for (int i = -3; i < 4; i++) for (int j = -3; j < 4; j++)
					{
						attackPointList.push_back(masuPosition.front() + Vector2<int>(7 + i, j));
					}
				}
				else if (diff.x < 0)
				{
					attackDirection = Direction::LEFT;
					for (int i = 0; i < 2; i++)
					{
						attackPointList.push_back(masuPosition.front() + Vector2<int>(-2 - i, 0));
					}
					for (int i = -3; i < 4; i++) for (int j = -3; j < 4; j++)
					{
						attackPointList.push_back(masuPosition.front() + Vector2<int>(-7 + i, j));
					}
				}
				else if (diff.y > 0)
				{
					attackDirection = Direction::DOWN;
					for (int i = 0; i < 2; i++)
					{
						attackPointList.push_back(masuPosition.front() + Vector2<int>(0, 2 + i));
					}
					for (int i = -3; i < 4; i++) for (int j = -3; j < 4; j++)
					{
						attackPointList.push_back(masuPosition.front() + Vector2<int>(i, 7 + j));
					}
				}
				else if (diff.y < 0)
				{
					attackDirection = Direction::UP;
					for (int i = 0; i < 2; i++)
					{
						attackPointList.push_back(masuPosition.front() + Vector2<int>(0, -2 - i));
					}
					for (int i = -3; i < 4; i++) for (int j = -3; j < 4; j++)
					{
						attackPointList.push_back(masuPosition.front() + Vector2<int>(i, -7 + j));
					}
				}
				else
				{
					assert(0 && "EnemyaMap001::UpdateNotice()");
				}
			}
			else if (abs(diff.x) > 7 || abs(diff.y)>7)
			{
				StartMove(8.0, StartMoveKind::CLOSE);
				moveCounter++;
			}
			else
			{
				StartMove(8.0, StartMoveKind::ALIGNMENT);
				moveCounter++;
			}
		}
		break;
		case 89:
		{
			if (abs(masuPosition.front().x - playerMap->GetMasuPosition().x) <= 1 && abs(masuPosition.front().y - playerMap->GetMasuPosition().y) <= 2 || abs(masuPosition.front().x - playerMap->GetMasuPosition().x) <= 2 && abs(masuPosition.front().y - playerMap->GetMasuPosition().y) <= 1)
			{
				attackKind = 89;

				if (abs(diff.x) <= abs(diff.y))
				{
					if (diff.y < 0)
					{
						attackDirection = Direction::UP;

						Vector2<int> tempPos = masuPosition.front() + Vector2<int>(0, -3);
						for (int i = -1; i < 2; i++)for (int j = -1; j < 2; j++)
						{
							attackPointList.push_back(tempPos + Vector2<int>(i, j));
						}
					}
					else
					{
						attackDirection = Direction::DOWN;
						Vector2<int> tempPos = masuPosition.front() + Vector2<int>(0, 3);
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
						Vector2<int> tempPos = masuPosition.front() + Vector2<int>(3, 0);
						for (int i = -1; i < 2; i++)for (int j = -1; j < 2; j++)
						{
							attackPointList.push_back(tempPos + Vector2<int>(i, j));
						}
					}
					else
					{
						attackDirection = Direction::LEFT;
						Vector2<int> tempPos = masuPosition.front() + Vector2<int>(-3, 0);
						for (int i = -1; i < 2; i++)for (int j = -1; j < 2; j++)
						{
							attackPointList.push_back(tempPos + Vector2<int>(i, j));
						}
					}
				}
			}
			else if (diff.length() > 3)
			{
				StartMove(4.0, StartMoveKind::CLOSE);
			}
			else
			{
				StartMove(4.0, StartMoveKind::ALIGNMENT);
			}
		}
		break;
		}

	}
}

void BossMap007::UpdateTempAttackKind()
{
	Vector2<int> diff = playerMap->GetMasuPosition() - masuPosition.front();

	if (bossStatus->GetHPRate() > 0.5)
	{
		int randNum = GetRand(1000) % 10;

		if (diff.length() <= 4)
		{
			if (randNum < 2)
			{
				tempAttackKind = 86;
				stiffTime = 60;
				delay = 60;
			}
			else if (randNum < 6)
			{
				tempAttackKind = 84;
				stiffTime = 60;
				delay = 60;
			}
			else
			{
				tempAttackKind = 85;
				stiffTime = 60;
				delay = 60;
			}
		}
		else
		{
			if (randNum < 5)
			{
				tempAttackKind = 86;
				stiffTime = 60;
				delay = 60;
			}
			else
			{
				tempAttackKind = 85;
				stiffTime = 60;
				delay = 60;
			}
		}
	}
	else
	{
		if (preAttackKind == 89)
		{
			if (state < 2)
			{
				tempAttackKind = 89;
				stiffTime = 60;
				delay = 60;
				state++;
			}
			else
			{
				tempAttackKind = 88;
				stiffTime = 60;
				delay = 60;
				state = 0;
			}
		}
		else
		{

			int randNum = GetRand(1000) % 10;

			if (diff.length() <= 4)
			{
				if (randNum < 2)
				{
					tempAttackKind = 87;
					stiffTime = 60;
					delay = 60;
				}
				else if (randNum < 4)
				{
					tempAttackKind = 89;
					stiffTime = 60;
					delay = 60;
				}
				else if (randNum < 6)
				{
					tempAttackKind = 86;
					stiffTime = 60;
					delay = 60;
				}
				else if (randNum < 8)
				{
					tempAttackKind = 85;
					stiffTime = 60;
					delay = 60;
				}
				else
				{
					tempAttackKind = 84;
					stiffTime = 60;
					delay = 60;
				}
			}
			else
			{
				if (randNum < 1)
				{
					tempAttackKind = 89;
					stiffTime = 60;
					delay = 60;
				}
				else if (randNum < 3)
				{
					tempAttackKind = 84;
					stiffTime = 60;
					delay = 60;
				}
				else if (randNum < 6)
				{
					tempAttackKind = 85;
					stiffTime = 60;
					delay = 60;
				}
				else
				{
					tempAttackKind = 86;
					stiffTime = 60;
					delay = 60;
				}
			}
		}
	}
}