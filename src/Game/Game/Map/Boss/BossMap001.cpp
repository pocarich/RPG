#include"../header/BossMap001.h"
#include"../header/BattleEffectE078_1.h"
#include"../header/PlayerMap.h"
#include"../header/EnemySkillInfoList.h"
#include"../header/BattleEffectE087.h"
#include"../header/MapInfoList.h"

BossMap001::BossMap001(PlayerData* playerData, PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<EnemyMapPtr>& enemyMapList, list<PeopleMapPtr>& peopleMapList, list<BattleEffectPtr>& battleEffectList, list<TextUIPtr>& textUIList, list<DropItemPtr>& dropItemList, int id, Vector2<int> masuPosition, Vector2<double>& camera, int& mapNum, int standFlag,int specialEventNum) :BossMap(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, battleEffectList, textUIList, dropItemList, id, 1, masuPosition, camera, mapNum, standFlag,specialEventNum)
{
	bossStatus = new BossStatus(1);
	firstAttakcFlag = false;
	subKind = 0;
}

BossMap001::~BossMap001()
{

}

void BossMap001::UpdateNotice()
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
		case 90:
		{
			if ((abs(masuPosition.front().x - playerMap->GetMasuPosition().x) <= 3 && abs(masuPosition.front().y - playerMap->GetMasuPosition().y) <= 3) || moveCounter >= 5)
			{
				attackKind = 90;
				attackDirection = Direction::UP;

				for (int i = -4; i < 5; i++)for (int j = -4; j < 5; j++)
				{
					attackPointList.push_back(masuPosition.front() + Vector2<int>(i, j));
				}
			}
			else if (diff.length() > 3)
			{
				StartMove(2.0, StartMoveKind::CLOSE);
				moveCounter++;
			}
		}
		break;
		case 91:
		{
			if ((abs(masuPosition.front().x - playerMap->GetMasuPosition().x) <= 1 && abs(masuPosition.front().y - playerMap->GetMasuPosition().y) <= 3 || abs(masuPosition.front().x - playerMap->GetMasuPosition().x) <= 3 && abs(masuPosition.front().y - playerMap->GetMasuPosition().y) <= 1) || moveCounter >= 5)
			{
				attackKind = 91;

				if (abs(diff.x) <= abs(diff.y))
				{
					if (diff.y < 0)
					{
						attackDirection = Direction::UP;

						Vector2<int> tempPos = masuPosition.front() + Vector2<int>(0, -3);
						for (int i = -2; i < 3; i++)for (int j = -2; j < 3; j++)
						{
							attackPointList.push_back(tempPos + Vector2<int>(i, j));
						}
					}
					else
					{
						attackDirection = Direction::DOWN;
						Vector2<int> tempPos = masuPosition.front() + Vector2<int>(0, 3);
						for (int i = -2; i < 3; i++)for (int j = -2; j < 3; j++)
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
						for (int i = -2; i < 3; i++)for (int j = -2; j < 3; j++)
						{
							attackPointList.push_back(tempPos + Vector2<int>(i, j));
						}
					}
					else
					{
						attackDirection = Direction::LEFT;
						Vector2<int> tempPos = masuPosition.front() + Vector2<int>(-3, 0);
						for (int i = -2; i < 3; i++)for (int j = -2; j < 3; j++)
						{
							attackPointList.push_back(tempPos + Vector2<int>(i, j));
						}
					}
				}
			}
			else
			{
				moveCounter++;
				StartMove(2.0, StartMoveKind::CLOSE);
			}
		}
		break;
		case 92:
		{
			if (diff.length() <= 7)
			{
				attackDirection = Direction::UP;
				attackKind = 92;
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
				StartMove(2.0, StartMoveKind::CLOSE);
			}
		}
		break;
		case 93:
		{
			if (state == 0)
			{
				if (moveCounter < 3)
				{
					moveCounter++;
					StartMove(2, StartMoveKind::AWAY);
				}
				else
				{
					if ((abs(diff.x) <= 7 && diff.y == 0) || (abs(diff.y) <= 7 && diff.x == 0))
					{
						attackKind = 93;

						if (diff.x > 0)
						{
							attackDirection = Direction::RIGHT;
							for (int i = -1; i < 2; i++)
							{
								attackPointList.push_back(masuPosition.front() + Vector2<int>(2, i));
							}
						}
						else if (diff.x < 0)
						{
							attackDirection = Direction::LEFT;
							for (int i = -1; i < 2; i++)
							{
								attackPointList.push_back(masuPosition.front() + Vector2<int>(-2, i));
							}
						}
						else if (diff.y > 0)
						{
							attackDirection = Direction::DOWN;
							for (int i = -1; i < 2; i++)
							{
								attackPointList.push_back(masuPosition.front() + Vector2<int>(i, 2));
							}
						}
						else if (diff.y < 0)
						{
							attackDirection = Direction::UP;
							for (int i = -1; i < 2; i++)
							{
								attackPointList.push_back(masuPosition.front() + Vector2<int>(i, -2));
							}
						}
						else
						{
							assert(0 && "EnemyaMap001::UpdateNotice()");
						}
					}
					else if (abs(diff.x)>5 || abs(diff.y)>5)
					{
						StartMove(2.0, StartMoveKind::CLOSE);
						moveCounter++;
					}
					else
					{
						StartMove(2.0, StartMoveKind::ALIGNMENT);
						moveCounter++;
					}
				}
			}
			else
			{
				if (moveCounter == 0)
				{
					double _speed = subKind == 0 ? 2.0 : 4.0;
					if (!StartMove(_speed, attackDirection))
					{
						preAttackKind = -1;
						attackKind = -1;
						tempAttackKind = -1;
						moveCounter = 0;
						state = 0;
						stiffTimer = 30;
					}
					moveCounter++;
				}
				else
				{
					attackKind = 93;

					switch (attackDirection)
					{
					case Direction::DOWN:
						for (int i = -1; i < 2; i++)
						{
							attackPointList.push_back(masuPosition.front() + Vector2<int>(i, 2));
						}
						break;
					case Direction::UP:
						for (int i = -1; i < 2; i++)
						{
							attackPointList.push_back(masuPosition.front() + Vector2<int>(i, -2));
						}
						break;
					case Direction::LEFT:
						for (int i = -1; i < 2; i++)
						{
							attackPointList.push_back(masuPosition.front() + Vector2<int>(-2, i));
						}
						break;
					case Direction::RIGHT:
						for (int i = -1; i < 2; i++)
						{
							attackPointList.push_back(masuPosition.front() + Vector2<int>(2, i));
						}
						break;
					}
				}
			}
		}
		break;
		case 94:
		{
			if (diff.length() <= 7)
			{
				attackKind = 94;

				for (int i = 0; i < (int)(19 * 19 / 2.5); i++)
				{
					int randx = (GetRand(10000) % 19) - 10;
					int randy = (GetRand(10000) % 19) - 10;

					Vector2<int> pos = masuPosition.front() + Vector2<int>(randx, randy);

					if (find(attackPointList.begin(), attackPointList.end(), pos) == attackPointList.end() && MapInfoList::GetMapInfoList()[mapNum].canThrough[pos.y][pos.x])
					{
						attackPointList.push_back(masuPosition.front() + Vector2<int>(randx, randy));
					}
				}
			}
			else
			{
				StartMove(2.0, StartMoveKind::CLOSE);
				moveCounter++;
			}
		}
		break;
		case 95:
		{
			if (subKind == 0)
			{
				if (moveCounter < 3)
				{
					moveCounter++;
					StartMove(2, StartMoveKind::AWAY);
				}
				else
				{
					if (diff.length() <= 7)
					{
						attackKind = 95;

						attackPointList.push_back(masuPosition.front());
						for (int i = -1; i < 2; i++)for (int j = -1; j < 2; j++)
						{
							if (i != 0 || j != 0)
							{
								attackPointList.push_back(masuPosition.front() + Vector2<int>(i, j));
							}
						}
					}
					else
					{
						StartMove(2.0, StartMoveKind::CLOSE);
						moveCounter++;
					}
				}
			}
			else
			{
				attackKind = 95;

				attackPointList.push_back(masuPosition.front());
				for (int i = -1; i < 2; i++)for (int j = -1; j < 2; j++)
				{
					if (i != 0 || j != 0)
					{
						attackPointList.push_back(masuPosition.front() + Vector2<int>(i, j));
					}
				}
			}
		}
		break;
		}

	}
}

void BossMap001::UpdateTempAttackKind()
{
	Vector2<int> diff = playerMap->GetMasuPosition() - masuPosition.front();

	if (!firstAttakcFlag)
	{
		tempAttackKind = 94;
		firstAttakcFlag = true;
		return;
	}

	if (preAttackKind == 93)
	{
		if (state < 7)
		{
			tempAttackKind = 93;
			state++;
		}
		else
		{
			state = 0;
			preAttackKind = -1;
			stiffTimer = 30;
		}
		return;
	}

	if (bossStatus->GetHPRate() > 0.5)
	{
		int randNum = GetRand(1000) % 10;

		if (diff.length() <= 4)
		{
			if (randNum < 3)
			{
				tempAttackKind = 91;
			}
			else if (randNum < 5)
			{
				tempAttackKind = 90;
			}
			else if (randNum < 8)
			{
				tempAttackKind = 93;
				subKind = 0;
			}
			else
			{
				subKind = 0;
				tempAttackKind = 95;
			}
		}
		else
		{
			if (randNum < 3)
			{
				tempAttackKind = 95;
				subKind = 0;
			}
			else if (randNum < 6)
			{
				tempAttackKind = 93;
				subKind = 0;
			}
			else
			{
				tempAttackKind = 92;
			}
		}
	}
	else
	{
		if (preAttackKind == 94)
		{
			if (state < 2)
			{
				tempAttackKind = 94;
				state++;
			}
			else
			{
				state = 0;
				preAttackKind = -1;
				stiffTimer = 60;
			}
			return;
		}

		if (preAttackKind == 95)
		{
			if (state < 2)
			{
				tempAttackKind = 95;
				subKind = 1;
				state++;
			}
			else
			{
				state = 0;
				preAttackKind = -1;
				stiffTimer = 60;
			}
			return;
		}

		int randNum = GetRand(1000) % 10;
		int randNum2 = GetRand(1000) % 10;

		if (randNum2 < 2)
		{
			tempAttackKind = 94;
		}
		else
		{
			if (diff.length() <= 4)
			{
				if (randNum < 3)
				{
					tempAttackKind = 91;
				}
				else if (randNum < 5)
				{
					tempAttackKind = 90;
				}
				else if (randNum < 8)
				{
					tempAttackKind = 93;
					subKind = 1;
				}
				else
				{
					tempAttackKind = 95;
					subKind = 0;
				}
			}
			else
			{
				if (randNum < 3)
				{
					tempAttackKind = 95;
					subKind = 0;
				}
				else if (randNum < 6)
				{
					tempAttackKind = 93;
					subKind = 1;
				}
				else
				{
					tempAttackKind = 92;
				}
			}
		}
	}
}