#include"../header/BossMap002.h"
#include"../header/BattleEffectE078_1.h"
#include"../header/PlayerMap.h"
#include"../header/EnemySkillInfoList.h"
#include"../header/EnemyMap044.h"

BossMap002::BossMap002(PlayerData* playerData, PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<EnemyMapPtr>& enemyMapList, list<PeopleMapPtr>& peopleMapList, list<BattleEffectPtr>& battleEffectList, list<TextUIPtr>& textUIList, list<DropItemPtr>& dropItemList, int id, Vector2<int> masuPosition, Vector2<double>& camera, int& mapNum, int standFlag,int specialEventNum) :BossMap(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, battleEffectList, textUIList, dropItemList, id, 2, masuPosition, camera, mapNum, standFlag,specialEventNum)
{
	bossStatus = new BossStatus(2);
	firstSammonFlag = false;
	subKind = 0;
	comboFlag = false;
}

BossMap002::~BossMap002()
{

}

void BossMap002::UpdateNotice()
{
	static const int width[] = { 0,1,1,2,2,3,3,4 };

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
		case 96:
			if (moveCounter < 5)
			{
				moveCounter++;
				StartMove(4.0, StartMoveKind::RAMDOM);
			}
			else
			{
				if ((abs(masuPosition.front().x - playerMap->GetMasuPosition().x) <= 1 && abs(masuPosition.front().y - playerMap->GetMasuPosition().y) <= 3 || abs(masuPosition.front().x - playerMap->GetMasuPosition().x) <= 3 && abs(masuPosition.front().y - playerMap->GetMasuPosition().y) <= 1))
				{
					attackKind = 96;

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
					StartMove(4.0, StartMoveKind::CLOSE);
				}
			}
			break;
		case 97:
			if (moveCounter < 3)
			{
				moveCounter++;
				StartMove(2, StartMoveKind::AWAY);
			}
			else
			{
				if ((abs(diff.x) <= 4 && diff.y == 0) || (abs(diff.y) <= 4 && diff.x == 0))
				{
					attackKind = 97;

					if (diff.x > 0)
					{
						attackDirection = Direction::RIGHT;
						for (int i = 1; i < 8; i++)
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
						for (int i = 1; i < 8; i++)
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
						for (int i = 1; i < 8; i++)
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
						for (int i = 1; i < 8; i++)
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
					StartMove(8.0, StartMoveKind::CLOSE);
				}
				else
				{
					StartMove(8.0, StartMoveKind::ALIGNMENT);
				}
			}
			break;
		case 98:
			if (moveCounter < 3)
			{
				moveCounter++;
				StartMove(4.0, StartMoveKind::RAMDOM);
			}
			else
			{
				if (abs(masuPosition.front().x - playerMap->GetMasuPosition().x) <= 1 && abs(masuPosition.front().y - playerMap->GetMasuPosition().y) <= 3 || abs(masuPosition.front().x - playerMap->GetMasuPosition().x) <= 3 && abs(masuPosition.front().y - playerMap->GetMasuPosition().y) <= 1)
				{
					attackKind = 98;

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
					StartMove(8.0, StartMoveKind::CLOSE);
				}
				else
				{
					StartMove(8.0, StartMoveKind::ALIGNMENT);
				}
			}
			break;
		case 99:
		{
			switch (state)
			{
			case 0:
				attackKind = 99;
				attackPointList.push_back(playerMap->GetMasuPosition());
				attackPointList.push_back(playerMap->GetMasuPosition() + Vector2<int>(1, 0));
				attackPointList.push_back(playerMap->GetMasuPosition() + Vector2<int>(-1, 0));
				attackPointList.push_back(playerMap->GetMasuPosition() + Vector2<int>(0, 1));
				attackPointList.push_back(playerMap->GetMasuPosition() + Vector2<int>(0, -1));
				break;
			case 1:
				attackKind = 100;
				for (int i = -1; i < 2; i++)for (int j = -1; j < 2; j++)
				{
					attackPointList.push_back(playerMap->GetMasuPosition() + Vector2<int>(i, j));
				}
				attackPointList.push_back(playerMap->GetMasuPosition() + Vector2<int>(2, 0));
				attackPointList.push_back(playerMap->GetMasuPosition() + Vector2<int>(-2, 0));
				attackPointList.push_back(playerMap->GetMasuPosition() + Vector2<int>(0, 2));
				attackPointList.push_back(playerMap->GetMasuPosition() + Vector2<int>(0, -2));
				break;
			case 2:
				attackKind = 101;
				for (int i = -3; i < 4; i++)for (int j = -3; j < 4; j++)
				{
					if (abs(i) + abs(j) <= 3)
					{
						attackPointList.push_back(playerMap->GetMasuPosition() + Vector2<int>(i, j));
					}
				}
				break;
			}
		}
		break;
		case 102:
			switch (subKind)
			{
			case 0:
				if (diff.length() <= 7)
				{
					attackKind = 102;
					for (int i = -10; i < 11; i++)for (int j = -1; j < 2; j++)
					{
						attackPointList.push_back(masuPosition.front() + Vector2<int>(i, j));
					}
					for (int i = -10; i < 11; i++)for (int j = -1; j < 2; j++)
					{
						attackPointList.push_back(masuPosition.front() + Vector2<int>(j, i));
					}
				}
				else
				{
					StartMove(4.0, StartMoveKind::CLOSE);
				}
				break;
			case 1:
				attackKind = 102;
				for (int i = -10; i < 11; i++)for (int j = -1; j < 2; j++)
				{
					attackPointList.push_back(masuPosition.front() + Vector2<int>(i, j));
				}
				for (int i = -10; i < 11; i++)for (int j = -1; j < 2; j++)
				{
					attackPointList.push_back(masuPosition.front() + Vector2<int>(j, i));
				}
				break;
			}
			break;
		case 103:
			switch (subKind)
			{
			case 0:
				if (diff.length() <= 7)
				{
					attackKind = 103;
					attackPointList.push_back(masuPosition.front() + Vector2<int>(0, 0));
					attackPointList.push_back(masuPosition.front() + Vector2<int>(1, 0));
					attackPointList.push_back(masuPosition.front() + Vector2<int>(-1, 0));
					attackPointList.push_back(masuPosition.front() + Vector2<int>(0, 1));
					attackPointList.push_back(masuPosition.front() + Vector2<int>(0, -1));
					for (int i = -7; i < 8; i++)
					{
						if (i < 0)
						{
							attackPointList.push_back(masuPosition.front() + Vector2<int>(i, i));
							attackPointList.push_back(masuPosition.front() + Vector2<int>(i, i - 1));
							attackPointList.push_back(masuPosition.front() + Vector2<int>(i - 1, i));
						}
						else if (i>0)
						{
							attackPointList.push_back(masuPosition.front() + Vector2<int>(i, i));
							attackPointList.push_back(masuPosition.front() + Vector2<int>(i, i + 1));
							attackPointList.push_back(masuPosition.front() + Vector2<int>(i + 1, i));
						}
					}
					for (int i = -7; i < 8; i++)
					{
						if (i < 0)
						{
							attackPointList.push_back(masuPosition.front() + Vector2<int>(i, -i));
							attackPointList.push_back(masuPosition.front() + Vector2<int>(i, -i + 1));
							attackPointList.push_back(masuPosition.front() + Vector2<int>(i - 1, -i));
						}
						else if (i>0)
						{
							attackPointList.push_back(masuPosition.front() + Vector2<int>(i, -i));
							attackPointList.push_back(masuPosition.front() + Vector2<int>(i, -i - 1));
							attackPointList.push_back(masuPosition.front() + Vector2<int>(i + 1, -i));
						}
					}
				}
				else
				{
					StartMove(4.0, StartMoveKind::CLOSE);
				}
				break;
			case 1:
				attackKind = 103;
				for (int i = -7; i < 8; i++)
				{
					if (i < 0)
					{
						attackPointList.push_back(masuPosition.front() + Vector2<int>(i, i));
						attackPointList.push_back(masuPosition.front() + Vector2<int>(i, i - 1));
						attackPointList.push_back(masuPosition.front() + Vector2<int>(i - 1, i));
					}
					else
					{
						attackPointList.push_back(masuPosition.front() + Vector2<int>(i, i));
						attackPointList.push_back(masuPosition.front() + Vector2<int>(i, i + 1));
						attackPointList.push_back(masuPosition.front() + Vector2<int>(i + 1, i));
					}
				}
				for (int i = -7; i < 8; i++)
				{
					if (i < 0)
					{
						attackPointList.push_back(masuPosition.front() + Vector2<int>(i, -i));
						attackPointList.push_back(masuPosition.front() + Vector2<int>(i, -i + 1));
						attackPointList.push_back(masuPosition.front() + Vector2<int>(i - 1, -i));
					}
					else
					{
						attackPointList.push_back(masuPosition.front() + Vector2<int>(i, -i));
						attackPointList.push_back(masuPosition.front() + Vector2<int>(i, -i - 1));
						attackPointList.push_back(masuPosition.front() + Vector2<int>(i + 1, -i));
					}
				}
				break;
			}
			break;
		case 104:
		{
			const Vector2<int> popPosition[4] = { Vector2<int>(35,21),Vector2<int>(41,21), Vector2<int>(35,24), Vector2<int>(41,24) };
			for (int i = 0; i < 4; i++)
			{
				attackPointList.push_back(popPosition[i]);
			}
			attackKind = 104;
		}
			break;
		case 105:
			if (diff.length() <= 5)
			{
				attackKind = 105;
				for (int i = -7; i < 8; i++)for (int j = -7; j < 8; j++)
				{
					if (Vector2<int>(i, j).length() <= 7)
					{
						attackPointList.push_back(masuPosition.front() + Vector2<int>(i, j));
					}
				}
			}
			else
			{
				StartMove(8.0, StartMoveKind::CLOSE);
			}
			break;
		}
	}
}

void BossMap002::UpdateTempAttackKind()
{
	Vector2<int> diff = playerMap->GetMasuPosition() - masuPosition.front();

	if (preAttackKind == 102)
	{
		if (state == 0)
		{
			tempAttackKind = 103;
			subKind = 1;
			setStiffTime = 100;
			state++;
		}
		else
		{
			state = 0;
			preAttackKind = -1;
		}
		if (comboFlag)
		{
			setStiffTime = 20;
		}
		return;
	}
	if (preAttackKind == 103)
	{
		if (state == 0)
		{
			tempAttackKind = 102;
			subKind = 1;
			setStiffTime = 100;
			state++;
		}
		else
		{
			state = 0;
			preAttackKind = -1;
		}
		if (comboFlag)
		{
			setStiffTime = 20;
		}
		return;
	}

	if (preAttackKind == 99|| preAttackKind == 100|| preAttackKind == 101)
	{
		if (state<2)
		{
			state++;
			tempAttackKind = 99;
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
			int randNum = GetRand(100) % 2;
			if (randNum == 0)
			{
				tempAttackKind = 102;
				subKind = 0;
			}
			else
			{
				tempAttackKind = 103;
				subKind = 0;
			}
			state1++;
		}
			break;
		case 1:
			tempAttackKind = 99;
			state1++;
			break;
		case 2:
			tempAttackKind = 105;
			comboFlag = false;
			state1 = 0;
			break;
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
				tempAttackKind = 96;
			}
			else if (randNum < 50)
			{
				tempAttackKind = 97;
			}
			else if (randNum < 70)
			{
				tempAttackKind = 98;
			}
			else if (randNum < 85)
			{
				tempAttackKind = 99;
			}
			else
			{
				tempAttackKind = 103;
			}
		}
		else
		{
			if (randNum < 20)
			{
				tempAttackKind = 96;
			}
			else if (randNum < 50)
			{
				tempAttackKind = 97;
			}
			else if (randNum < 65)
			{
				tempAttackKind = 98;
			}
			else if (randNum < 85)
			{
				tempAttackKind = 99;
			}
			else
			{
				tempAttackKind = 103;
			}
		}
	}
	else
	{
		int randNum = GetRand(1000) % 100;
		int randNum2 = GetRand(1000) % 10;

		if (!firstSammonFlag)
		{
			tempAttackKind = 104;
			firstSammonFlag = true;
		}
		else
		{
			if (randNum2 == 0)
			{
				if (find_if(enemyMapList.begin(), enemyMapList.end(), [](EnemyMapPtr& obj) {return typeid(*obj) == typeid(EnemyMap044); }) == enemyMapList.end())
				{
					tempAttackKind = 104;
				}
			}
			else if (randNum2 == 1)
			{
				comboFlag = true;
			}
			else
			{
				if (diff.length() <= 4)
				{
					if (randNum < 30)
					{
						tempAttackKind = 96;
					}
					else if (randNum < 50)
					{
						tempAttackKind = 97;
					}
					else if (randNum < 70)
					{
						tempAttackKind = 98;
					}
					else if (randNum < 85)
					{
						tempAttackKind = 99;
					}
					else
					{
						tempAttackKind = 103;
					}
				}
				else
				{
					if (randNum < 20)
					{
						tempAttackKind = 96;
					}
					else if (randNum < 50)
					{
						tempAttackKind = 97;
					}
					else if (randNum < 65)
					{
						tempAttackKind = 98;
					}
					else if (randNum < 85)
					{
						tempAttackKind = 99;
					}
					else
					{
						tempAttackKind = 103;
					}
				}
			}
		}
	}
}