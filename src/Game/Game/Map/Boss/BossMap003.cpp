#include"../header/BossMap003.h"
#include"../header/BattleEffectE078_1.h"
#include"../header/PlayerMap.h"
#include"../header/EnemySkillInfoList.h"
#include"../header/EnemyMap044.h"

BossMap003::BossMap003(PlayerData* playerData, PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<EnemyMapPtr>& enemyMapList, list<PeopleMapPtr>& peopleMapList, list<BattleEffectPtr>& battleEffectList, list<TextUIPtr>& textUIList, list<DropItemPtr>& dropItemList, int id, Vector2<int> masuPosition, Vector2<double>& camera, int& mapNum, int standFlag, int specialEventNum) :BossMap(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, battleEffectList, textUIList, dropItemList, id, 3, masuPosition, camera, mapNum, standFlag, specialEventNum)
{
	bossStatus = new BossStatus(3);
	firstSammonFlag = false;
	subKind = 0;
	comboFlag = false;
}

BossMap003::~BossMap003()
{

}

void BossMap003::UpdateNotice()
{
	static const int width1[] = { 0,1,1,2,2,3,3,4 };
	static const int width2[] = { 0,1,2,3,4,5,5,6,6 };
	static const Vector2<int> round1[] = { Vector2<int>(2,0),Vector2<int>(-2,0),Vector2<int>(1,1),Vector2<int>(0,2),Vector2<int>(-1,1),Vector2<int>(-1,-1),Vector2<int>(0,-2),Vector2<int>(1,-1) };
	static const Vector2<int> round2[] = { Vector2<int>(4,0),Vector2<int>(-4,0),Vector2<int>(3,3),Vector2<int>(0,4),Vector2<int>(-3,3),Vector2<int>(-3,-3),Vector2<int>(0,-4),Vector2<int>(3,-3) };
	static const Vector2<int> round3[] = { Vector2<int>(6,0),Vector2<int>(-6,0),Vector2<int>(5,3),Vector2<int>(3,5),Vector2<int>(0,6),Vector2<int>(-3,5),Vector2<int>(-5,3),Vector2<int>(-5,-3),Vector2<int>(-3,-5),Vector2<int>(0,-6),Vector2<int>(3,-5),Vector2<int>(5,-3) };

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
		case 110:
			if (moveCounter < 5 && subKind == 0)
			{
				moveCounter++;
				StartMove(4.0, StartMoveKind::RAMDOM);
			}
			else
			{
				if (abs(masuPosition.front().x - playerMap->GetMasuPosition().x) <= 1 && abs(masuPosition.front().y - playerMap->GetMasuPosition().y) <= 2 || abs(masuPosition.front().x - playerMap->GetMasuPosition().x) <= 2 && abs(masuPosition.front().y - playerMap->GetMasuPosition().y) <= 1)
				{
					attackKind = 110;

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
		case 111:
			if (moveCounter < 3 && subKind == 0)
			{
				moveCounter++;
				StartMove(2.0, StartMoveKind::RAMDOM);
			}
			else
			{
				if ((abs(masuPosition.front().x - playerMap->GetMasuPosition().x) <= 1 && abs(masuPosition.front().y - playerMap->GetMasuPosition().y) <= 3 || abs(masuPosition.front().x - playerMap->GetMasuPosition().x) <= 3 && abs(masuPosition.front().y - playerMap->GetMasuPosition().y) <= 1) || moveCounter >= 5)
				{
					attackKind = 111;

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
					StartMove(4.0, StartMoveKind::CLOSE);
				}
			}
			break;
		case 112:
			switch (state)
			{
			case 0:
				if (diff.length() <= 5)
				{
					attackKind = 112;
					for (int k = 0; k < 8; k++)for (int i = -1; i < 2; i++)for (int j = -1; j < 2; j++)
					{
						if (abs(i) + abs(j) <= 1)
						{
							attackPointList.push_back(masuPosition.front() + round1[k] + Vector2<int>(i, j));
						}
					}
				}
				else
				{
					StartMove(4.0, StartMoveKind::CLOSE);
				}
				break;
			case 1:
				attackKind = 113;
				for (int k = 0; k < 8; k++)for (int i = -2; i < 3; i++)for (int j = -2; j < 3; j++)
				{
					if (abs(i) + abs(j) <= 2)
					{
						attackPointList.push_back(masuPosition.front() + round2[k] + Vector2<int>(i, j));
					}
				}
				break;
			case 2:
				attackKind = 114;
				for (int k = 0; k < 12; k++)for (int i = -2; i < 3; i++)for (int j = -2; j < 3; j++)
				{
					if (abs(i) + abs(j) <= 2)
					{
						attackPointList.push_back(masuPosition.front() + round3[k] + Vector2<int>(i, j));
					}
				}
				break;
			}
			break;
		case 115:
			if (moveCounter < 5 && subKind == 0)
			{
				moveCounter++;
				StartMove(4.0, StartMoveKind::AWAY);
			}
			else
			{
				if ((abs(diff.x) <= 5 && diff.y == 0) || (abs(diff.y) <= 5 && diff.x == 0))
				{
					attackKind = 115;

					if (diff.x > 0)
					{
						attackDirection = Direction::RIGHT;
						for (int i = 1; i < 8; i++)
						{
							for (int j = -width1[i]; j < width1[i] + 1; j++)
							{
								Vector2<int> attackPoint = masuPosition.front() + Vector2<int>(1 + i, j);
								attackPointList.push_back(attackPoint);
							}
						}
					}
					else if (diff.x < 0)
					{
						attackDirection = Direction::LEFT;
						for (int i = 1; i < 8; i++)
						{
							for (int j = -width1[i]; j < width1[i] + 1; j++)
							{
								Vector2<int> attackPoint = masuPosition.front() + Vector2<int>(-1 - i, j);
								attackPointList.push_back(attackPoint);
							}
						}
					}
					else if (diff.y > 0)
					{
						attackDirection = Direction::DOWN;
						for (int i = 1; i < 8; i++)
						{
							for (int j = -width1[i]; j < width1[i] + 1; j++)
							{
								Vector2<int> attackPoint = masuPosition.front() + Vector2<int>(j, 1 + i);
								attackPointList.push_back(attackPoint);
							}
						}
					}
					else if (diff.y < 0)
					{
						attackDirection = Direction::UP;
						for (int i = 1; i < 8; i++)
						{
							for (int j = -width1[i]; j < width1[i] + 1; j++)
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
					StartMove(4.0, StartMoveKind::CLOSE);
				}
				else
				{
					StartMove(4.0, StartMoveKind::ALIGNMENT);
				}
			}
			break;
		case 116:
			if ((abs(diff.x) <= 6 && diff.y == 0) || (abs(diff.y) <= 6 && diff.x == 0))
			{
				attackKind = 116;

				if (diff.x > 0)
				{
					attackDirection = Direction::RIGHT;
					for (int i = 1; i < 9; i++)
					{
						for (int j = -width2[i]; j < width2[i] + 1; j++)
						{
							Vector2<int> attackPoint = masuPosition.front() + Vector2<int>(1 + i, j);
							attackPointList.push_back(attackPoint);
						}
					}
				}
				else if (diff.x < 0)
				{
					attackDirection = Direction::LEFT;
					for (int i = 1; i < 9; i++)
					{
						for (int j = -width2[i]; j < width2[i] + 1; j++)
						{
							Vector2<int> attackPoint = masuPosition.front() + Vector2<int>(-1 - i, j);
							attackPointList.push_back(attackPoint);
						}
					}
				}
				else if (diff.y > 0)
				{
					attackDirection = Direction::DOWN;
					for (int i = 1; i < 9; i++)
					{
						for (int j = -width2[i]; j < width2[i] + 1; j++)
						{
							Vector2<int> attackPoint = masuPosition.front() + Vector2<int>(j, 1 + i);
							attackPointList.push_back(attackPoint);
						}
					}
				}
				else if (diff.y < 0)
				{
					attackDirection = Direction::UP;
					for (int i = 1; i < 9; i++)
					{
						for (int j = -width2[i]; j < width2[i] + 1; j++)
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
			else if (abs(diff.x) > 6 || abs(diff.y)>6)
			{
				StartMove(8.0, StartMoveKind::CLOSE);
			}
			else
			{
				StartMove(8.0, StartMoveKind::ALIGNMENT);
			}
			break;
		case 117:
			if (moveCounter < 5 && subKind == 0)
			{
				moveCounter++;
				StartMove(8.0, StartMoveKind::AWAY);
			}
			else
			{
				if ((abs(diff.x) <= 7 && diff.y == 0) || (abs(diff.y) <= 7 && diff.x == 0) || moveCounter == 15)
				{
					attackKind = 117;
					tempAttackKind = -1;

					if (diff.x > 0)
					{
						attackDirection = Direction::RIGHT;
						for (int i = 0; i < 4; i++)
						{
							attackPointList.push_back(masuPosition.front() + Vector2<int>(2 + i, 0));
						}
						for (int i = -1; i < 2; i++) for (int j = -1; j < 2; j++)
						{
							attackPointList.push_back(masuPosition.front() + Vector2<int>(7 + i, j));
						}
					}
					else if (diff.x < 0)
					{
						attackDirection = Direction::LEFT;
						for (int i = 0; i < 4; i++)
						{
							attackPointList.push_back(masuPosition.front() + Vector2<int>(-2 - i, 0));
						}
						for (int i = -1; i < 2; i++) for (int j = -1; j < 2; j++)
						{
							attackPointList.push_back(masuPosition.front() + Vector2<int>(-7 + i, j));
						}
					}
					else if (diff.y > 0)
					{
						attackDirection = Direction::DOWN;
						for (int i = 0; i < 4; i++)
						{
							attackPointList.push_back(masuPosition.front() + Vector2<int>(0, 2 + i));
						}
						for (int i = -1; i < 2; i++) for (int j = -1; j < 2; j++)
						{
							attackPointList.push_back(masuPosition.front() + Vector2<int>(i, 7 + j));
						}
					}
					else if (diff.y < 0)
					{
						attackDirection = Direction::UP;
						for (int i = 0; i < 4; i++)
						{
							attackPointList.push_back(masuPosition.front() + Vector2<int>(0, -2 - i));
						}
						for (int i = -1; i < 2; i++) for (int j = -1; j < 2; j++)
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
		case 118:
			if ((abs(diff.x) <= 7 && diff.y == 0) || (abs(diff.y) <= 7 && diff.x == 0) || state != 0)
			{
				attackKind = 118;
				for (int k = 0; k < 4; k++)
				{
					int radius = GetRand(100) % 9;
					double angle = 2.0 * M_PI / 100 * (GetRand(10000) % 100);

					int x = int(radius*cos(angle));
					int y = int(radius*sin(angle));

					for (int i = -3; i < 4; i++)for (int j = -3; j < 4; j++)
					{
						if (abs(i) + abs(j) <= 3)
						{
							attackPointList.push_back(playerMap->GetMasuPosition() + Vector2<int>(x, y) + Vector2<int>(i, j));
						}
					}
				}
			}
			else
			{
				StartMove(4.0, StartMoveKind::CLOSE);
			}
			break;
		}
	}
}

void BossMap003::UpdateTempAttackKind()
{
	Vector2<int> diff = playerMap->GetMasuPosition() - masuPosition.front();

	if (preAttackKind == 112 || preAttackKind == 113 || preAttackKind == 114)
	{
		if (state<2)
		{
			state++;
			tempAttackKind = 112;
			subKind = 0;
			if (comboFlag)
			{
				setStiffTime = 20;
			}
		}
		else
		{
			state = 0;
			preAttackKind = -1;
		}
		return;
	}

	if (comboFlag)
	{
		switch (state1)
		{
		case 0:
		{
			tempAttackKind = 115;
			subKind = 0;
			setStiffTime = 40;
			state1++;
		}
		break;
		case 1:
			subKind = 1;
			tempAttackKind = 115;
			subKind = 0;
			setStiffTime = 40;
			state1++;
			break;
		case 2:
			tempAttackKind = 116;
			subKind = 0;
			comboFlag = false;
			state1 = 0;
			break;
		}
		return;
	}

	if (preAttackKind == 118)
	{
		if (state<2)
		{
			state++;
			tempAttackKind = 118;
			subKind = 0;
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

	if (bossStatus->GetHPRate() > 0.5)
	{
		int randNum = GetRand(1000) % 100;

		if (diff.length() <= 4)
		{
			if (randNum < 30)
			{
				tempAttackKind = 110;
				subKind = 0;
			}
			else if (randNum < 60)
			{
				tempAttackKind = 111;
				subKind = 0;
			}
			else if (randNum < 80)
			{
				tempAttackKind = 115;
				subKind = 0;
			}
			else if (randNum < 90)
			{
				tempAttackKind = 117;
				subKind = 0;
			}
			else
			{
				tempAttackKind = 118;
				subKind = 0;
			}
		}
		else
		{
			if (randNum < 30)
			{
				subKind = 1;
				tempAttackKind = 110;
			}
			else if (randNum < 50)
			{
				subKind = 1;
				tempAttackKind = 111;
			}
			else if (randNum < 70)
			{
				subKind = 1;
				tempAttackKind = 115;
			}
			else if (randNum < 85)
			{
				tempAttackKind = 117;
				subKind = 0;
			}
			else
			{
				subKind = 1;
				tempAttackKind = 118;
			}
		}
	}
	else
	{
		int randNum = GetRand(1000) % 100;
		int randNum2 = GetRand(1000) % 100;

		if (randNum2 <= 10)
		{
			tempAttackKind = 112;
			subKind = 0;
		}
		else if (randNum2 <= 20)
		{
			comboFlag = true;
		}
		else
		{
			if (diff.length() <= 4)
			{
				if (randNum < 30)
				{
					subKind = GetRand(100) % 2 == 1 ? 1 : 0;
					tempAttackKind = 110;
				}
				else if (randNum < 60)
				{
					subKind = GetRand(100) % 2 == 1 ? 1 : 0;
					tempAttackKind = 111;
				}
				else if (randNum < 80)
				{
					tempAttackKind = 115;
					subKind = 0;
				}
				else if (randNum < 90)
				{
					tempAttackKind = 117;
					subKind = 0;
				}
				else
				{
					tempAttackKind = 118;
					subKind = 0;
				}
			}
			else
			{
				if (randNum < 30)
				{
					subKind = 1;
					tempAttackKind = 110;
				}
				else if (randNum < 50)
				{
					subKind = 1;
					tempAttackKind = 111;
				}
				else if (randNum < 70)
				{
					subKind = 1;
					tempAttackKind = 115;
				}
				else if (randNum < 85)
				{
					tempAttackKind = 117;
					subKind = 0;
				}
				else
				{
					subKind = 1;
					tempAttackKind = 118;
					subKind = 0;
				}
			}
		}
	}
}