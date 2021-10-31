#include"../header/EnemyMap040.h"
#include"../header/BattleEffectE078_1.h"
#include"../header/PlayerMap.h"
#include"../header/EnemySkillInfoList.h"

EnemyMap040::EnemyMap040(PlayerData* playerData, PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<EnemyMapPtr>& enemyMapList, list<PeopleMapPtr>& peopleMapList, int id, Vector2<int> masuPosition, Vector2<double>& camera, list<BattleEffectPtr>& battleEffectList, list<TextUIPtr>& textUIList, list<DropItemPtr>& dropItemList, int& mapNum) :EnemyMap(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, id, masuPosition, camera, battleEffectList, textUIList, dropItemList, mapNum)
{
	enemyStatus = new EnemyStatus(40);
	kind = 40;
	randomMoveCounter = 0;
	tempAttackKind = -1;
}

EnemyMap040::~EnemyMap040()
{

}

void EnemyMap040::UpdateNotice()
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
		case 78:
		{
			if (randomMoveCounter < randomMoveCount)
			{
				randomMoveCounter++;
				StartMove(enemyStatus->GetMoveSpeedNotice(), StartMoveKind::RAMDOM);
			}
			else
			{
				Vector2<int> diff = playerMap->GetMasuPosition() - masuPosition;
				if (abs(diff.x) < 7 && abs(diff.y) < 7)
				{
					randomMoveCounter = 0;
					attackKind = 78;
					tempAttackKind = -1;
					attackPointList.push_back(masuPosition);
				}
				else
				{
					StartMove(enemyStatus->GetMoveSpeedNotice(), StartMoveKind::CLOSE);
				}
			}
		}
		break;
		case 79:
		{
			if (randomMoveCounter < randomMoveCount)
			{
				randomMoveCounter++;
				StartMove(enemyStatus->GetMoveSpeedNotice(), StartMoveKind::RAMDOM);
			}
			else
			{
				Vector2<int> diff = playerMap->GetMasuPosition() - masuPosition;
				if (abs(diff.x) <= 2 && abs(diff.y) <= 2)
				{
					attackKind = 79;
					tempAttackKind = -1;
					randomMoveCounter = 0;

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
		}
		break;
		case 80:
		{
			Vector2<int> diff = playerMap->GetMasuPosition() - masuPosition;
			if (diff.length() <= 7)
			{
				attackKind = 80;
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

void EnemyMap040::UpdateTempAttackKind()
{
	Vector2<int> diff = playerMap->GetMasuPosition() - masuPosition;

	if (count_if(battleEffectList.begin(), battleEffectList.end(), [&](BattleEffectPtr& obj) {return typeid(*obj) == typeid(BattleEffectE078_1); }) == 0)
	{
		tempAttackKind = 78;
	}
	else
	{
		if (diff.length() <= 4)
		{
			int randNum = GetRand(1000) % 10;
			if (randNum >= 5)
			{
				tempAttackKind = 79;
			}
			else
			{
				tempAttackKind = 80;
			}
		}
		else
		{
			tempAttackKind = 80;
		}
	}
}