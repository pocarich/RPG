#include"../header/EnemyMap003.h"
#include"../header/PlayerMap.h"
#include"../header/EnemySkillInfoList.h"

EnemyMap003::EnemyMap003(PlayerData* playerData, PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<EnemyMapPtr>& enemyMapList, list<PeopleMapPtr>& peopleMapList,int id,Vector2<int> masuPosition, Vector2<double>& camera, list<BattleEffectPtr>& battleEffectList, list<TextUIPtr>& textUIList, list<DropItemPtr>& dropItemList,int& mapNum) :EnemyMap(playerData,playerMap, bossMapList, objectMapList,enemyMapList,peopleMapList,id,masuPosition, camera, battleEffectList,textUIList,dropItemList, mapNum)
{
	enemyStatus = new EnemyStatus(3);
	kind = 3;
}

EnemyMap003::~EnemyMap003()
{

}

void EnemyMap003::UpdateNotice()
{
	if (stiffTimer > 0)
	{
		return;
	}

	if (abs(masuPosition.x - playerMap->GetMasuPosition().x) + abs(masuPosition.y - playerMap->GetMasuPosition().y) == 1)
	{
		attackKind = 4;

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
			assert(0 && "EnemyMap003::UpdateNotice()");
		}
		attackPointList.push_back(playerMap->GetMasuPosition());
	}
	else
	{
		StartMove(enemyStatus->GetMoveSpeedNotice(), StartMoveKind::CLOSE);
	}
}
