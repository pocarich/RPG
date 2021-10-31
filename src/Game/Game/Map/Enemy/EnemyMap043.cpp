#include"../header/EnemyMap043.h"
#include"../header/PlayerMap.h"
#include"../header/EnemySkillInfoList.h"

EnemyMap043::EnemyMap043(PlayerData* playerData, PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<EnemyMapPtr>& enemyMapList, list<PeopleMapPtr>& peopleMapList, int id, Vector2<int> masuPosition, Vector2<double>& camera, list<BattleEffectPtr>& battleEffectList, list<TextUIPtr>& textUIList, list<DropItemPtr>& dropItemList, int& mapNum) :EnemyMap(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, id, masuPosition, camera, battleEffectList, textUIList, dropItemList, mapNum)
{
	enemyStatus = new EnemyStatus(43);
	kind = 43;
	tempAttackKind = -1;
}

EnemyMap043::~EnemyMap043()
{

}

void EnemyMap043::UpdateNotice()
{
	static const int width[] = { 0,1,2,3,3,3,3,3,3,3 };

	Vector2<int> diff = playerMap->GetMasuPosition() - masuPosition;

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
		case 107:
			if (moveCounter < 3 && subState == 0)
			{
				moveCounter++;
				double _speed = 2.0;
				if (enemyStatus->GetHPRate() < 0.5)
				{
					_speed = 4.0;
				}
				StartMove(_speed, StartMoveKind::RAMDOM);
			}
			else
			{
				if (abs(masuPosition.x - playerMap->GetMasuPosition().x) + abs(masuPosition.y - playerMap->GetMasuPosition().y) <= 2)
				{
					attackKind = 107;
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
				else
				{
					double _speed = 2.0;
					if (enemyStatus->GetHPRate() < 0.5)
					{
						_speed = 4.0;
					}
					StartMove(_speed, StartMoveKind::CLOSE);
				}
			}
			break;
		case 108:
			if (moveCounter < 5 && subState == 0)
			{
				moveCounter++;
				double _speed = 2.0;
				if (enemyStatus->GetHPRate() < 0.5)
				{
					_speed = 4.0;
				}
				StartMove(_speed, StartMoveKind::RAMDOM);
			}
			else
			{
				if (abs(diff.x) <= 2 && abs(diff.y) <= 2)
				{
					attackKind = 108;
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
					double _speed = 2.0;
					if (enemyStatus->GetHPRate() < 0.5)
					{
						_speed = 4.0;
					}
					StartMove(_speed, StartMoveKind::CLOSE);
				}
			}
			break;
		case 109:
			if (moveCounter < 3)
			{
				moveCounter++;
				double _speed = 2.0;
				if (enemyStatus->GetHPRate() < 0.5)
				{
					_speed = 4.0;
				}
				StartMove(_speed, StartMoveKind::AWAY);
			}
			else
			{
				if ((abs(diff.x) <= 6 && diff.y == 0) || (abs(diff.y) <= 6 && diff.x == 0))
				{
					attackKind = 109;
					tempAttackKind = -1;

					if (diff.x > 0)
					{
						attackDirection = Direction::RIGHT;
						for (int i = 0; i < 10; i++)
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
						for (int i = 0; i < 10; i++)
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
						for (int i = 0; i < 10; i++)
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
						for (int i = 0; i < 10; i++)
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
				else if (abs(diff.x) > 6 || abs(diff.y)>6)
				{
					double _speed = 2.0;
					if (enemyStatus->GetHPRate() < 0.5)
					{
						_speed = 4.0;
					}
					StartMove(_speed, StartMoveKind::CLOSE);
				}
				else
				{
					double _speed = 2.0;
					if (enemyStatus->GetHPRate() < 0.5)
					{
						_speed = 4.0;
					}
					StartMove(_speed, StartMoveKind::ALIGNMENT);
				}
			}
			break;
		case 110:
			if (moveCounter < 3 && subState == 0)
			{
				moveCounter++;
				double _speed = 2.0;
				if (enemyStatus->GetHPRate() < 0.5)
				{
					_speed = 4.0;
				}
				StartMove(_speed, StartMoveKind::RAMDOM);
			}
			else
			{
				if (diff.length() <= 7)
				{
					attackKind = 110;
					tempAttackKind = -1;
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
					double _speed = 2.0;
					if (enemyStatus->GetHPRate() < 0.5)
					{
						_speed = 4.0;
					}
					StartMove(_speed, StartMoveKind::CLOSE);
				}
			}
			break;
		}
	}
}

void EnemyMap043::UpdateTempAttackKind()
{
	Vector2<int> diff = playerMap->GetMasuPosition() - masuPosition;

	if (enemyStatus->GetHPRate() > 0.7)
	{
		if (diff.length() <= 3)
		{
			int randNum = GetRand(1000) % 10;
			if (randNum >= 5)
			{
				tempAttackKind = 107;
			}
			else
			{
				tempAttackKind = 108;
			}
		}
		else
		{
			int randNum = GetRand(1000) % 10;
			if (randNum >= 5)
			{
				tempAttackKind = 109;
			}
			else
			{
				tempAttackKind = 110;
			}
		}
	}
	else if (enemyStatus->GetHPRate() > 0.5)
	{
		if (diff.length() <= 4)
		{
			int randNum = GetRand(1000) % 10;
			if (randNum >= 5)
			{
				subState = (GetRand(100) % 10) >= 5 ? 1 : 0;
				tempAttackKind = 107;
				setStiffTime = 40;
			}
			else
			{
				tempAttackKind = 108;
				setStiffTime = 40;
			}
		}
		else
		{
			int randNum = GetRand(1000) % 10;
			if (randNum >= 5)
			{
				subState = (GetRand(100) % 10) >= 5 ? 1 : 0;
				tempAttackKind = 109;
				setStiffTime = 40;
			}
			else
			{
				tempAttackKind = 110;
				setStiffTime = 40;
			}
		}
	}
	else if (enemyStatus->GetHPRate() > 0.3)
	{
		if (diff.length() <= 4)
		{
			int randNum = GetRand(1000) % 10;
			if (randNum >= 6)
			{
				subState = (GetRand(100) % 10) >= 5 ? 1 : 0;
				tempAttackKind = 107;
				setStiffTime = 40;
			}
			else if(randNum>=2)
			{
				tempAttackKind = 108;
				setStiffTime = 40;
			}
			else
			{
				tempAttackKind = 109;
				setStiffTime = 40;
			}
		}
		else
		{
			int randNum = GetRand(1000) % 10;
			if (randNum >= 6)
			{
				subState = (GetRand(100) % 10) >= 5 ? 1 : 0;
				tempAttackKind = 109;
				setStiffTime = 40;
			}
			else if(randNum>=2)
			{
				tempAttackKind = 110;
				setStiffTime = 40;
			}
			else
			{
				tempAttackKind = 107;
				setStiffTime = 40;
			}
		}
	}
	else
	{
		if (diff.length() <= 4)
		{
			int randNum = GetRand(1000) % 10;
			if (randNum >= 6)
			{
				subState = (GetRand(100) % 10) >= 5 ? 1 : 0;
				tempAttackKind = 107;
				setStiffTime = 40;
				setAttackTime = 40;
			}
			else if (randNum >= 2)
			{
				subState = (GetRand(100) % 10) >= 5 ? 1 : 0;
				tempAttackKind = 108;
				setStiffTime = 40;
				setAttackTime = 40;
			}
			else
			{
				subState = (GetRand(100) % 10) >= 5 ? 1 : 0;
				tempAttackKind = 109;
				setStiffTime = 40;
				setAttackTime = 40;
			}
		}
		else
		{
			int randNum = GetRand(1000) % 10;
			if (randNum >= 6)
			{
				subState = (GetRand(100) % 10) >= 5 ? 1 : 0;
				tempAttackKind = 109;
				setStiffTime = 40;
				setAttackTime = 40;
			}
			else if (randNum >= 2)
			{
				subState = (GetRand(100) % 10) >= 5 ? 1 : 0;
				tempAttackKind = 110;
				setStiffTime = 40;
				setAttackTime = 40;
			}
			else
			{
				subState = (GetRand(100) % 10) >= 5 ? 1 : 0;
				tempAttackKind = 107;
				setStiffTime = 40;
				setAttackTime = 40;
			}
		}
	}
}