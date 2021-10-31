#include"../header/BossMap008.h"
#include"../header/BattleEffectE078_1.h"
#include"../header/PlayerMap.h"
#include"../header/EnemySkillInfoList.h"
#include"../header/EnemyMap044.h"
#include"../header/MapInfoList.h"

BossMap008::BossMap008(PlayerData* playerData, PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<EnemyMapPtr>& enemyMapList, list<PeopleMapPtr>& peopleMapList, list<BattleEffectPtr>& battleEffectList, list<TextUIPtr>& textUIList, list<DropItemPtr>& dropItemList, int id, Vector2<int> masuPosition, Vector2<double>& camera, int& mapNum, int standFlag, int specialEventNum) :BossMap(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, battleEffectList, textUIList, dropItemList, id, 8, masuPosition, camera, mapNum, standFlag, specialEventNum)
{
	bossStatus = new BossStatus(8);
	firstApoFlag = false;
	subKind = 0;
	werpTime = 0;
	firstRandLaserFlag = false;
	apoCounter = 0;
}

BossMap008::~BossMap008()
{

}

bool BossMap008::Werp(Vector2<int> werpPos, int werpStiffTime, double distance, bool equalDistance)
{
	array<Vector2<int>, 9> next;

	if (werpPos != Vector2<int>(-1, -1))
	{
		Vector2<int> werpVector = werpPos - masuPosition.front();
		for (int i = 0; i != masuPosition.size(); i++)
		{
			next[i] = masuPosition[i] + werpVector;
		}
	}
	else
	{
		double randAngle = 2 * M_PI / 100 * (GetRand(10000) % 100);
		int randRadius = 0;
		if (!equalDistance)
		{
			assert((int)distance >= 5 && "BossMap008");
			randRadius = GetRand(100) % ((int)distance - 4) + 4;
		}
		if (equalDistance)
		{
			randRadius = (int)distance;
		}
		Vector2<int> diffVector = playerMap->GetMasuPosition() + Vector2<int>(randRadius*cos(randAngle), randRadius*sin(randAngle));
		next[0] = diffVector;
		int posCounter = 1;
		for (int i = -1; i < 2; i++)for (int j = -1; j < 2; j++)
		{
			if (!(i == 0 && j == 0))
			{
				next[posCounter] = next[0] + Vector2<int>(i, j);
				posCounter++;
			}
		}
	}
	if (count_if(next.begin(), next.end(), [&](const Vector2<int>& pos) {return !CanMoveToNextPosition(pos, Direction::UP); }) == 0)
	{
		for (int i = 0; i != masuPosition.size(); i++)
		{
			masuPosition[i] = next[i];
		}
		position = Vector2<double>((double)masuPosition.front().x, (double)masuPosition.front().y)*(double)Define::MASU_SIZE + Vector2<double>((double)Define::MASU_SIZE / 2, (double)Define::MASU_SIZE / 2);
		stiffTimer = werpStiffTime;
		return true;
	}
	else
	{
		return false;
	}
}

void BossMap008::UpdateNotice()
{
	static const int width[] = { 0,1,2,3,4,5,6,7,8,9,10 };

	static const Vector2<int> constPos[] = { Vector2<int>(7,0),Vector2<int>(-7,0),Vector2<int>(0,7),Vector2<int>(0,-7) };
	static const Vector2<int> constPos2[] = { Vector2<int>(5,0),Vector2<int>(-5,0),Vector2<int>(0,5),Vector2<int>(0,-5) };

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
		case 120:
			if (werpCounter < 5 && subKind == 1)
			{
				if (werpCounter < 4)
				{
					if (Werp(Vector2<int>(-1, -1), 15, 7, false))
					{
						werpCounter++;
					}
				}
				else
				{
					int randNum = GetRand(100) % 4;
					if (Werp(playerMap->GetMasuPosition() + constPos[randNum], 0, 0, false))
					{
						werpCounter++;
					}
				}
			}
			else if (moveCounter < 5 && subKind == 0)
			{
				moveCounter++;
				StartMove(8.0, StartMoveKind::AWAY);
			}
			else
			{
				if ((abs(diff.x) <= 7 && diff.y == 0) || (abs(diff.y) <= 7 && diff.x == 0) || moveCounter == 15)
				{
					attackKind = 120;
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
		case 121:
			if (werpCounter < 7 && subKind < 2)
			{
				if (werpCounter < 6)
				{
					if (Werp(Vector2<int>(-1, -1), 10, 7, false))
					{
						werpCounter++;
					}
				}
				else
				{
					int randNum = GetRand(100) % 4;
					if (Werp(Vector2<int>(-1, -1), 0, 10, false))
					{
						werpCounter++;
					}
				}
			}
			else
			{
				attackKind = 121;

				attackPointList.push_back(masuPosition.front());
				for (int i = -1; i < 2; i++)for (int j = -1; j < 2; j++)
				{
					if (i != 0 || j != 0)
					{
						attackPointList.push_back(masuPosition.front() + Vector2<int>(i, j));
					}
				}

				if (abs(diff.x) <= abs(diff.y))
				{
					if (diff.y < 0)
					{
						attackDirection = Direction::UP;
					}
					else
					{
						attackDirection = Direction::DOWN;
					}
				}
				else
				{
					if (diff.x > 0)
					{
						attackDirection = Direction::RIGHT;
					}
					else
					{
						attackDirection = Direction::LEFT;
					}
				}
			}
			break;
		case 122:
			if (werpCounter < 5 && subKind == 1)
			{
				if (werpCounter < 4)
				{
					if (Werp(Vector2<int>(-1, -1), 15, 7, false))
					{
						werpCounter++;
					}
				}
				else
				{
					int randNum = GetRand(100) % 4;
					if (Werp(playerMap->GetMasuPosition() + constPos[randNum], 0, 0, false))
					{
						werpCounter++;
					}
				}
			}
			else if (moveCounter < 5 && subKind == 0)
			{
				moveCounter++;
				StartMove(8.0, StartMoveKind::AWAY);
			}
			else
			{
				if ((abs(diff.x) <= 5 && diff.y == 0) || (abs(diff.y) <= 5 && diff.x == 0))
				{
					attackKind = 122;

					if (diff.x > 0)
					{
						attackDirection = Direction::RIGHT;
						for (int i = 1; i < 11; i++)
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
						for (int i = 1; i < 11; i++)
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
						for (int i = 1; i < 11; i++)
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
						for (int i = 1; i < 11; i++)
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
				else if (abs(diff.x) > 5 || abs(diff.y)>5)
				{
					StartMove(8.0, StartMoveKind::CLOSE);
				}
				else
				{
					StartMove(8.0, StartMoveKind::ALIGNMENT);
				}
			}
			break;
		case 123:
			if (werpCounter < 3 && subKind == 1)
			{
				if (werpCounter < 2)
				{
					if (Werp(Vector2<int>(-1, -1), 15, 7, false))
					{
						werpCounter++;
					}
				}
				else
				{
					int randNum = GetRand(100) % 4;
					if (Werp(Vector2<int>(-1, -1), 0, 3, true))
					{
						werpCounter++;
					}
				}
			}
			else
			{
				if (diff.length() <= 3)
				{
					attackKind = 123;
					for (int i = -4; i < 5; i++)for (int j = -4; j < 5; j++)
					{
						if (Vector2<int>(i, j).length() <= 4)
						{
							attackPointList.push_back(masuPosition.front() + Vector2<int>(i, j));
						}
					}
				}
				else
				{
					StartMove(8.0, StartMoveKind::CLOSE);
				}
			}
			break;
		case 124:
			attackKind = 124;
			break;
		case 125:
		{
			int randDistance = GetRand(100) % 10;
			double randAngle = 2 * M_PI / 100 * (GetRand(10000) % 100);
			Vector2<int> attackPos = playerMap->GetMasuPosition() + Vector2<int>((int)(randDistance*cos(randAngle)), (int)(randDistance*sin(randAngle)));
			if (CanMoveToNextPosition(attackPos, Direction::DOWN))
			{
				attackKind = 125;
				attackPointList.push_back(attackPos);
			}
		}
			break;
		case 126:
			if (werpCounter < 5 && subKind == 1)
			{
				if (werpCounter < 4)
				{
					if (Werp(Vector2<int>(-1, -1), 10, 7, false))
					{
						werpCounter++;
					}
				}
				else
				{
					int randNum = GetRand(100) % 4;
					if (Werp(Vector2<int>(-1, -1), 0, 3, true))
					{
						werpCounter++;
					}
				}
			}
			else if (moveCounter < 5 && subKind == 0)
			{
				moveCounter++;
				StartMove(8.0, StartMoveKind::RAMDOM);
			}
			else
			{
				attackKind = 126;
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
		case 127:
			if (werpCounter < 5 && subKind == 1)
			{
				if (werpCounter < 4)
				{
					if (Werp(Vector2<int>(-1, -1), 20, 7, false))
					{
						werpCounter++;
					}
				}
				else
				{
					int randNum = GetRand(100) % 4;
					if (Werp(Vector2<int>(-1, -1), 0, 3, true))
					{
						werpCounter++;
					}
				}
			}
			else
			{
				if (diff.length() <= 3)
				{
					attackKind = 127;
					for (int i = -5; i < 6; i++)for (int j = -5; j < 6; j++)
					{
						if (Vector2<int>(i, j).length() <= 5)
						{
							attackPointList.push_back(masuPosition.front() + Vector2<int>(i, j));
						}
					}
				}
				else
				{
					StartMove(8.0, StartMoveKind::CLOSE);
				}
			}
			break;
		case 128:
			attackKind = 128;
			for (int i = -10; i < 11; i++)for (int j = -10; j < 11; j++)
			{
				if (Vector2<int>(i, j).length() <= 10)
				{
					attackPointList.push_back(masuPosition.front() + Vector2<int>(i, j));
				}
			}
			break;
		case 129:
			if (werpCounter < 10)
			{
				if (werpCounter < 5)
				{
					if (Werp(Vector2<int>(-1, -1), 15, 7, false))
					{
						werpCounter++;
					}
				}
				else if (werpCounter < 9)
				{
					if (Werp(Vector2<int>(-1, -1), 7, 7, false))
					{
						werpCounter++;
					}
				}
				else
				{
					int randNum = GetRand(100) % 4;
					if (Werp(Vector2<int>(37, 35), 0, 0, false))
					{
						werpCounter++;
					}
					else if (Werp(Vector2<int>(37, 38), 0, 0, false))
					{
						werpCounter++;
					}
				}
			}
			else
			{
				attackKind = 129;
				for (int i = 0; i < MapInfoList::GetMapInfoList()[mapNum].heightNum; i++)for (int j = 0; j < MapInfoList::GetMapInfoList()[mapNum].widthNum; j++)
				{
					if (MapInfoList::GetMapInfoList()[mapNum].canThrough[i][j])
					{
						attackPointList.push_back(Vector2<int>(j, i));
					}
				}
			}
			break;
		case 130:
			if (werpCounter < 15)
			{
				if (werpCounter < 5)
				{
					if (Werp(Vector2<int>(-1, -1), 15, 7, false))
					{
						werpCounter++;
					}
				}
				else if (werpCounter < 10)
				{
					if (Werp(Vector2<int>(-1, -1), 10, 7, false))
					{
						werpCounter++;
					}
				}
				else if (werpCounter < 14)
				{
					if (Werp(Vector2<int>(-1, -1), 5, 7, false))
					{
						werpCounter++;
					}
				}
				else
				{
					int randNum = GetRand(100) % 4;
					if (Werp(Vector2<int>(37, 35), 0, 0, false))
					{
						werpCounter++;
					}
					else if (Werp(Vector2<int>(37, 38), 0, 0, false))
					{
						werpCounter++;
					}
				}
			}
			else
			{
				attackKind = 130;
				for (int i = 0; i < MapInfoList::GetMapInfoList()[mapNum].heightNum; i++)for (int j = 0; j < MapInfoList::GetMapInfoList()[mapNum].widthNum; j++)
				{
					if (MapInfoList::GetMapInfoList()[mapNum].canThrough[i][j])
					{
						attackPointList.push_back(Vector2<int>(j, i));
					}
				}
			}
			break;
		}
	}
}

void BossMap008::UpdateTempAttackKind()
{
	Vector2<int> diff = playerMap->GetMasuPosition() - masuPosition.front();

	if (preAttackKind == 127)
	{
		tempAttackKind = 128;
		return;
	}

	if (preAttackKind == 121)
	{
		if (state<2)
		{
			state++;
			tempAttackKind = 121;
			subKind = 3;
			if (state == 2)
			{
				setStiffTime = 120;
			}
		}
		else
		{
			state = 0;
			preAttackKind = -1;
		}
		return;
	}

	if (bossStatus->GetHPRate() > 0.7)
	{
		int randNum = GetRand(1000) % 100;

		if (diff.length() <= 4)
		{
			if (randNum < 25)
			{
				tempAttackKind = 120;
				subKind = (GetRand(100) % 2);
			}
			else if (randNum < 50)
			{
				tempAttackKind = 123;
				subKind = (GetRand(100) % 2);
			}
			else if (randNum < 70)
			{
				tempAttackKind = 121;
				subKind = (GetRand(100) % 2);
			}
			else if (randNum < 90)
			{
				tempAttackKind = 122;
				subKind = (GetRand(100) % 2);
			}
			else
			{
				tempAttackKind = 124;
				subKind = (GetRand(100) % 2);
			}
		}
		else
		{
			if (randNum < 25)
			{
				tempAttackKind = 120;
				subKind = 1;
			}
			else if (randNum < 50)
			{
				tempAttackKind = 123;
				subKind = 1;
			}
			else if (randNum < 70)
			{
				tempAttackKind = 121;
				subKind = 1;
			}
			else if (randNum < 90)
			{
				tempAttackKind = 122;
				subKind = 1;
			}
			else
			{
				tempAttackKind = 124;
				subKind = 1;
			}
		}
	}
	else if (bossStatus->GetHPRate()>0.5)
	{
		int randNum = GetRand(1000) % 100;

		if (!firstRandLaserFlag)
		{
			tempAttackKind = 125;
			firstRandLaserFlag = true;
		}
		else if (diff.length() <= 4)
		{
			if (randNum < 25)
			{
				tempAttackKind = 120;
				subKind = (GetRand(100) % 2);
			}
			else if (randNum < 50)
			{
				tempAttackKind = 123;
				subKind = (GetRand(100) % 2);
			}
			else if (randNum < 70)
			{
				tempAttackKind = 121;
				subKind = (GetRand(100) % 2);
			}
			else if (randNum < 90)
			{
				tempAttackKind = 122;
				subKind = (GetRand(100) % 2);
			}
			else
			{
				tempAttackKind = 124;
				subKind = (GetRand(100) % 2);
			}
		}
		else
		{
			if (randNum < 25)
			{
				tempAttackKind = 120;
				subKind = 1;
			}
			else if (randNum < 50)
			{
				tempAttackKind = 123;
				subKind = 1;
			}
			else if (randNum < 70)
			{
				tempAttackKind = 121;
				subKind = 1;
			}
			else if (randNum < 90)
			{
				tempAttackKind = 122;
				subKind = 1;
			}
			else
			{
				tempAttackKind = 124;
				subKind = 1;
			}
		}
	}
	else if (bossStatus->GetHPRate()>0.1)
	{
		int randNum = GetRand(1000) % 100;

		if (!firstApoFlag)
		{
			tempAttackKind = 129;
			firstApoFlag = true;
		}
		else if (apoCounter == apoInterval)
		{
			tempAttackKind = 129;
			apoCounter = 0;
		}
		else if (diff.length() <= 4)
		{
			if (randNum < 15)
			{
				tempAttackKind = 120;
				subKind = (GetRand(100) % 2);
				apoCounter++;
			}
			else if (randNum < 30)
			{
				tempAttackKind = 121;
				subKind = (GetRand(100) % 2);
				apoCounter++;
			}
			else if (randNum < 45)
			{
				tempAttackKind = 122;
				subKind = (GetRand(100) % 2);
				apoCounter++;
			}
			else if (randNum < 60)
			{
				tempAttackKind = 123;
				subKind = (GetRand(100) % 2);
				apoCounter++;
			}
			else if (randNum < 75)
			{
				tempAttackKind = 124;
				subKind = (GetRand(100) % 2);
				apoCounter++;
			}
			else if (randNum < 90)
			{
				tempAttackKind = 126;
				subKind = (GetRand(100) % 2);
				apoCounter++;
			}
			else
			{
				tempAttackKind = 127;
				subKind = (GetRand(100) % 2);
				apoCounter++;
			}
		}
		else
		{
			if (randNum < 15)
			{
				tempAttackKind = 120;
				subKind = 1;
				apoCounter++;
			}
			else if (randNum < 30)
			{
				tempAttackKind = 121;
				subKind = 1;
				apoCounter++;
			}
			else if (randNum < 45)
			{
				tempAttackKind = 122;
				subKind = 1;
				apoCounter++;
			}
			else if (randNum < 60)
			{
				tempAttackKind = 123;
				subKind = 1;
				apoCounter++;
			}
			else if (randNum < 75)
			{
				tempAttackKind = 124;
				subKind = 1;
				apoCounter++;
			}
			else if (randNum < 90)
			{
				tempAttackKind = 126;
				subKind = 1;
				apoCounter++;
			}
			else
			{
				tempAttackKind = 127;
				subKind = 1;
				apoCounter++;
			}
		}
	}
	else
	{
		tempAttackKind = 130;
	}
}