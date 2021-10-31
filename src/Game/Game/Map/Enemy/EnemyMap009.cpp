#include"../header/EnemyMap009.h"
#include"../header/PlayerMap.h"
#include"../header/EnemySkillInfoList.h"

EnemyMap009::EnemyMap009(PlayerData* playerData, PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<EnemyMapPtr>& enemyMapList, list<PeopleMapPtr>& peopleMapList,int id,Vector2<int> masuPosition, Vector2<double>& camera, list<BattleEffectPtr>& battleEffectList, list<TextUIPtr>& textUIList, list<DropItemPtr>& dropItemList,int& mapNum) :EnemyMap(playerData,playerMap, bossMapList, objectMapList,enemyMapList,peopleMapList,id,masuPosition, camera, battleEffectList,textUIList,dropItemList, mapNum)
{
	enemyStatus = new EnemyStatus(9);
	kind = 9;
}

EnemyMap009::~EnemyMap009()
{

}

void EnemyMap009::UpdateNotice()
{
	if (stiffTimer > 0)
	{
		return;
	}

	if (abs(masuPosition.x - playerMap->GetMasuPosition().x) + abs(masuPosition.y - playerMap->GetMasuPosition().y) == 1)
	{
		int randNum = GetRand(1000) % 10;
		if (randNum >= 2)
		{
			attackKind = 12;
		}
		else
		{
			attackKind = 13;
		}

		switch (attackKind)
		{
		case 12:
		{
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
				assert(0 && "EnemyMap009::UpdateNotice()");
			}
			attackPointList.push_back(playerMap->GetMasuPosition());
		}
		break;
		case 13:
		{
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
				assert(0 && "EnemyMap009::UpdateNotice()");
			}
			attackPointList.push_back(masuPosition+Vector2<int>(1,0));
			attackPointList.push_back(masuPosition + Vector2<int>(2, 0));
			attackPointList.push_back(masuPosition + Vector2<int>(1, 1));
			attackPointList.push_back(masuPosition + Vector2<int>(0, 1));
			attackPointList.push_back(masuPosition + Vector2<int>(0, 2));
			attackPointList.push_back(masuPosition + Vector2<int>(-1, 1));
			attackPointList.push_back(masuPosition + Vector2<int>(-1, 0));
			attackPointList.push_back(masuPosition + Vector2<int>(-2, 0));
			attackPointList.push_back(masuPosition + Vector2<int>(-1, -1));
			attackPointList.push_back(masuPosition + Vector2<int>(0, -1));
			attackPointList.push_back(masuPosition + Vector2<int>(0, -2));
			attackPointList.push_back(masuPosition + Vector2<int>(1, -1));
		}
		break;
		}
	}
	else
	{
		StartMove(enemyStatus->GetMoveSpeedNotice(), StartMoveKind::CLOSE);
	}
}
