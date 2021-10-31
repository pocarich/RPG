#include"../header/EnemyMap029.h"
#include"../header/PlayerMap.h"
#include"../header/EnemySkillInfoList.h"

EnemyMap029::EnemyMap029(PlayerData* playerData, PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<EnemyMapPtr>& enemyMapList, list<PeopleMapPtr>& peopleMapList, int id, Vector2<int> masuPosition, Vector2<double>& camera, list<BattleEffectPtr>& battleEffectList, list<TextUIPtr>& textUIList, list<DropItemPtr>& dropItemList, int& mapNum) :EnemyMap(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, id, masuPosition, camera, battleEffectList, textUIList, dropItemList, mapNum)
{
	enemyStatus = new EnemyStatus(29);
	kind = 29;
	randomMoveCounter = 0;
	tempAttackKind = -1;
}

EnemyMap029::~EnemyMap029()
{

}

void EnemyMap029::UpdateNotice()
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
		case 52:
		{
			Vector2<int> diff = playerMap->GetMasuPosition() - masuPosition;
			if (abs(diff.x) <= 2 && abs(diff.y) <= 2)
			{
				randomMoveCounter = 0;
				attackKind = 52;
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
		case 51:
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
					attackKind = 51;
					tempAttackKind = -1;
					attackPointList.push_back(playerMap->GetMasuPosition());
				}
				else
				{
					StartMove(enemyStatus->GetMoveSpeedNotice(), StartMoveKind::CLOSE);
				}
			}
		}
		break;
		}

	}
}

void EnemyMap029::UpdateTempAttackKind()
{
	Vector2<int> diff = playerMap->GetMasuPosition() - masuPosition;

	if (abs(diff.x) <= 2 && abs(diff.y) <= 2)
	{
		tempAttackKind = 52;
	}
	else
	{
		tempAttackKind = 51;
	}
}