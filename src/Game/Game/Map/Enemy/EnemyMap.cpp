#include"../header/EnemyMap.h"
#include"../header/Function.h"
#include"../header/CharacterSkillInfoList.h"
#include"../header/EnemySkillInfoList.h"
#include"../header/DamageText.h"
#include"../header/ColorMgr.h"
#include"../header/DropItem.h"
#include"../header/PlayerMap.h"
#include"../header/MapInfoList.h"
#include"../header/EventInfoList.h"
#include"../header/PeopleMap.h"
#include"../header/ObjectMap.h"
#include"../header/BossMap.h"

#include"../header/DropEXPText.h"
#include"../header/DropMoneyText.h"

#include"../header/BattleEffectE000.h"
#include"../header/BattleEffectE001.h"
#include"../header/BattleEffectE002.h"
#include"../header/BattleEffectE003.h"
#include"../header/BattleEffectE004.h"
#include"../header/BattleEffectE005.h"
#include"../header/BattleEffectE006.h"
#include"../header/BattleEffectE007.h"
#include"../header/BattleEffectE008.h"
#include"../header/BattleEffectE009.h"
#include"../header/BattleEffectE010.h"
#include"../header/BattleEffectE011.h"
#include"../header/BattleEffectE012.h"
#include"../header/BattleEffectE013.h"
#include"../header/BattleEffectE014.h"
#include"../header/BattleEffectE015.h"
#include"../header/BattleEffectE016.h"
#include"../header/BattleEffectE017.h"
#include"../header/BattleEffectE018.h"
#include"../header/BattleEffectE019.h"
#include"../header/BattleEffectE020.h"
#include"../header/BattleEffectE021.h"
#include"../header/BattleEffectE022.h"
#include"../header/BattleEffectE023.h"
#include"../header/BattleEffectE024.h"
#include"../header/BattleEffectE025.h"
#include"../header/BattleEffectE026.h"
#include"../header/BattleEffectE027.h"
#include"../header/BattleEffectE028_1.h"
#include"../header/BattleEffectE029.h"
#include"../header/BattleEffectE030.h"
#include"../header/BattleEffectE031.h"
#include"../header/BattleEffectE032.h"
#include"../header/BattleEffectE033.h"
#include"../header/BattleEffectE034.h"
#include"../header/BattleEffectE035.h"
#include"../header/BattleEffectE036.h"
#include"../header/BattleEffectE037.h"
#include"../header/BattleEffectE038.h"
#include"../header/BattleEffectE039.h"
#include"../header/BattleEffectE040.h"
#include"../header/BattleEffectE041.h"
#include"../header/BattleEffectE042.h"
#include"../header/BattleEffectE043.h"
#include"../header/BattleEffectE044.h"
#include"../header/BattleEffectE045.h"
#include"../header/BattleEffectE046.h"
#include"../header/BattleEffectE047.h"
#include"../header/BattleEffectE048_1.h"
#include"../header/BattleEffectE049.h"
#include"../header/BattleEffectE050.h"
#include"../header/BattleEffectE051.h"
#include"../header/BattleEffectE052.h"
#include"../header/BattleEffectE053.h"
#include"../header/BattleEffectE054.h"
#include"../header/BattleEffectE055.h"
#include"../header/BattleEffectE056.h"
#include"../header/BattleEffectE057.h"
#include"../header/BattleEffectE058.h"
#include"../header/BattleEffectE059.h"
#include"../header/BattleEffectE060.h"
#include"../header/BattleEffectE061.h"
#include"../header/BattleEffectE062.h"
#include"../header/BattleEffectE063.h"
#include"../header/BattleEffectE064.h"
#include"../header/BattleEffectE065.h"
#include"../header/BattleEffectE066.h"
#include"../header/BattleEffectE067.h"
#include"../header/BattleEffectE068.h"
#include"../header/BattleEffectE069.h"
#include"../header/BattleEffectE070.h"
#include"../header/BattleEffectE071.h"
#include"../header/BattleEffectE072.h"
#include"../header/BattleEffectE073.h"
#include"../header/BattleEffectE074.h"
#include"../header/BattleEffectE075.h"
#include"../header/BattleEffectE076.h"
#include"../header/BattleEffectE077_1.h"
#include"../header/BattleEffectE078_1.h"
#include"../header/BattleEffectE079.h"
#include"../header/BattleEffectE080.h"
#include"../header/BattleEffectE081.h"
#include"../header/BattleEffectE082.h"
#include"../header/BattleEffectE083.h"
#include"../header/BattleEffectE106.h"
#include"../header/BattleEffectE107.h"
#include"../header/BattleEffectE108.h"
#include"../header/BattleEffectE109.h"
#include"../header/BattleEffectE119.h"

GHandle EnemyMap::graph[Define::ENEMY_KIND_NUM];

EnemyMap::EnemyMap(PlayerData* playerData, PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<EnemyMapPtr>& enemyMapList, list<PeopleMapPtr>& peopleMapList,int id,Vector2<int> masuPosition, Vector2<double>& camera, list<BattleEffectPtr>& battleEffectList, list<TextUIPtr>& textUIList, list<DropItemPtr>& dropItemList,int& mapNum) :textUIList(textUIList),playerData(playerData),enemyMapList(enemyMapList),peopleMapList(peopleMapList),playerMap(playerMap),id(id),masuPosition(masuPosition), camera(camera), battleEffectList(battleEffectList), dropItemList(dropItemList),mapNum(mapNum),bossMapList(bossMapList),objectMapList(objectMapList)
{
	position = Vector2<double>(masuPosition.x*Define::MASU_SIZE + (double)Define::MASU_SIZE / 2, masuPosition.y*Define::MASU_SIZE + (double)Define::MASU_SIZE / 2);
	direction = Direction::DOWN;
	moveState = MoveState::STOP;

	velocity = Vector2<double>(0.0, 0.0);
	moveTime = 0;
	moveEndTime = 0;

	deathFlag = false;
	
	damagedFlag = false;
	damagedTimer = 0;

	kind = -1;

	knockBackFlag = false;
	knockBackTimer = 0;
	knockBackVelocity = Vector2<double>(0.0, 0.0);
	knockBackDirection = Direction::UP;

	noticeFlag = false;
	moveIntervalTimer = 0;

	stiffTimer = 0;
	
	attackKind = -1;
	attackTimer = 0;
	setStiffTime = -1;
	setAttackTime = -1;
	subState = 0;
	moveCounter = 0;
}

EnemyMap::~EnemyMap()
{
	delete enemyStatus;
}

void EnemyMap::Load()
{
	for (int i = 0; i < Define::ENEMY_KIND_NUM; i++)
	{
		stringstream ss;
		ss << "data/graph/character/enemy/enemy" << Function::NumToStringFillZero(i, 3) << ".png";
		graph[i] = LoadGraph(ss.str().c_str());
		assert(graph[i] != 0 && "EnemyMap::Load()‚É‚ÄŽ¸”s‚µ‚Ü‚µ‚½B");
	}
}

void EnemyMap::Update()
{
	UpdateDamagedTimer();
	UpdateStiffTimer();

	if (knockBackFlag)
	{
		UpdateKnockBack();
	}
	else
	{
		switch (moveState)
		{
		case MoveState::STOP:
			if (!noticeFlag)
			{
				UpdateMoveUnnotice();
				Notice();
			}
			else
			{
				if (attackKind == -1)
				{
					UpdateNotice();
				}
				else
				{
					UpdateAttackTimer();
				}
			}
			break;
		default:
			Move();
			break;
		}
	}
}

void EnemyMap::UpdateAttackTimer()
{
	attackTimer++;
	int _attackTime = EnemySkillInfoList::GetEnemySkillInfoList()[attackKind].delay;
	if (setAttackTime != -1)
	{
		_attackTime = setAttackTime;
	}
	if (attackTimer >= _attackTime)
	{
		switch (attackKind)
		{
		case 0:
			battleEffectList.push_back(make_shared<BattleEffectE000>(*enemyStatus, playerMap, bossMapList,objectMapList,battleEffectList, enemyMapList, id, masuPosition, attackDirection, camera, mapNum));
			break;
		case 1:
			battleEffectList.push_back(make_shared<BattleEffectE001>(*enemyStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition, attackDirection, camera, mapNum));
			break;
		case 2:
			battleEffectList.push_back(make_shared<BattleEffectE002>(*enemyStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition, attackDirection, camera, mapNum));
			break;
		case 3:
			battleEffectList.push_back(make_shared<BattleEffectE003>(*enemyStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition, attackDirection, camera, mapNum));
			break;
		case 4:
			battleEffectList.push_back(make_shared<BattleEffectE004>(*enemyStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition, attackDirection, camera, mapNum));
			break;
		case 5:
			battleEffectList.push_back(make_shared<BattleEffectE005>(*enemyStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition, attackDirection, camera, mapNum));
			break;
		case 6:
			battleEffectList.push_back(make_shared<BattleEffectE006>(*enemyStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition, attackDirection, camera, mapNum));
			break;
		case 7:
			battleEffectList.push_back(make_shared<BattleEffectE007>(*enemyStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition, attackDirection, camera, mapNum));
			break;
		case 8:
			battleEffectList.push_back(make_shared<BattleEffectE008>(*enemyStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition, attackDirection, camera, mapNum));
			break;
		case 9:
			battleEffectList.push_back(make_shared<BattleEffectE009>(*enemyStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition, attackDirection, camera, mapNum));
			break;
		case 10:
		{
			for (int i = 0; i < (int)BattleEffectE010::EightDirection::SIZE; i++)
			{
				battleEffectList.push_back(make_shared<BattleEffectE010>(*enemyStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition, attackDirection, (BattleEffectE010::EightDirection)i, camera, mapNum));
			}
		}
		break;
		case 11:
			battleEffectList.push_back(make_shared<BattleEffectE011>(*enemyStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition, attackDirection, camera, mapNum));
			break;
		case 12:
			battleEffectList.push_back(make_shared<BattleEffectE012>(*enemyStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition, attackDirection, camera, mapNum));
			break;
		case 13:
		{
			battleEffectList.push_back(make_shared<BattleEffectE013>(*enemyStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition + Vector2<int>(1, 0), attackDirection, camera, mapNum));
			battleEffectList.push_back(make_shared<BattleEffectE013>(*enemyStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition + Vector2<int>(2, 0), attackDirection, camera, mapNum));
			battleEffectList.push_back(make_shared<BattleEffectE013>(*enemyStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition + Vector2<int>(1, 1), attackDirection, camera, mapNum));
			battleEffectList.push_back(make_shared<BattleEffectE013>(*enemyStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition + Vector2<int>(0, 1), attackDirection, camera, mapNum));
			battleEffectList.push_back(make_shared<BattleEffectE013>(*enemyStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition + Vector2<int>(0, 2), attackDirection, camera, mapNum));
			battleEffectList.push_back(make_shared<BattleEffectE013>(*enemyStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition + Vector2<int>(-1, 1), attackDirection, camera, mapNum));
			battleEffectList.push_back(make_shared<BattleEffectE013>(*enemyStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition + Vector2<int>(-1, 0), attackDirection, camera, mapNum));
			battleEffectList.push_back(make_shared<BattleEffectE013>(*enemyStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition + Vector2<int>(-2, 0), attackDirection, camera, mapNum));
			battleEffectList.push_back(make_shared<BattleEffectE013>(*enemyStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition + Vector2<int>(-1, -1), attackDirection, camera, mapNum));
			battleEffectList.push_back(make_shared<BattleEffectE013>(*enemyStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition + Vector2<int>(0, -1), attackDirection, camera, mapNum));
			battleEffectList.push_back(make_shared<BattleEffectE013>(*enemyStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition + Vector2<int>(0, -2), attackDirection, camera, mapNum));
			battleEffectList.push_back(make_shared<BattleEffectE013>(*enemyStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition + Vector2<int>(1, -1), attackDirection, camera, mapNum));
		}
		break;
		case 14:
			battleEffectList.push_back(make_shared<BattleEffectE014>(*enemyStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition, attackDirection, camera, mapNum));
			break;
		case 15:
			battleEffectList.push_back(make_shared<BattleEffectE015>(*enemyStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, attackPointList.front(), attackDirection, camera, mapNum));
			break;
		case 16:
			for (auto& pos : attackPointList)
			{
				battleEffectList.push_back(make_shared<BattleEffectE016>(*enemyStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, pos, attackDirection, camera, mapNum));
			}
			break;
		case 17:
			for (int i = 0; i < 3; i++)
			{
				if (MapInfoList::GetMapInfoList()[mapNum].canThrough[attackPointList[i].y][attackPointList[i].x])
				{
					battleEffectList.push_back(make_shared<BattleEffectE017>(*enemyStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, attackPointList[i], attackDirection, camera, mapNum));
				}
			}
			break;
		case 18:
			battleEffectList.push_back(make_shared<BattleEffectE018>(*enemyStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition, attackDirection, camera, mapNum));
			break;
		case 19:
			battleEffectList.push_back(make_shared<BattleEffectE019>(*enemyStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition, attackDirection, camera, mapNum));
			break;
		case 20:
			battleEffectList.push_back(make_shared<BattleEffectE020>(*enemyStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition, attackDirection, camera, mapNum));
			break;
		case 21:
			battleEffectList.push_back(make_shared<BattleEffectE021>(*enemyStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition, attackDirection, camera, mapNum, 0));
			break;
		case 22:
			battleEffectList.push_back(make_shared<BattleEffectE022>(*enemyStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition, attackDirection, camera, mapNum));
			break;
		case 23:
			battleEffectList.push_back(make_shared<BattleEffectE023>(*enemyStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition, attackDirection, camera, mapNum));
			break;
		case 24:
			for (auto& pos : attackPointList)
			{
				battleEffectList.push_back(make_shared<BattleEffectE024>(*enemyStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, pos, attackDirection, camera, mapNum));
			}
			break;
		case 25:
			battleEffectList.push_back(make_shared<BattleEffectE025>(*enemyStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition, attackDirection, camera, mapNum));
			break;
		case 26:
			for (auto& pos : attackPointList)
			{
				battleEffectList.push_back(make_shared<BattleEffectE026>(*enemyStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, pos, attackDirection, camera, mapNum));
			}
			break;
		case 27:
			battleEffectList.push_back(make_shared<BattleEffectE027>(*enemyStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition, attackDirection, camera, mapNum));
			break;
		case 28:
			battleEffectList.push_back(make_shared<BattleEffectE028_1>(*enemyStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition, attackDirection, camera, mapNum));
			break;
		case 29:
			battleEffectList.push_back(make_shared<BattleEffectE029>(*enemyStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition, attackDirection, camera, mapNum));
			break;
		case 30:
			battleEffectList.push_back(make_shared<BattleEffectE030>(*enemyStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition, attackDirection, camera, mapNum));
			break;
		case 31:
			battleEffectList.push_back(make_shared<BattleEffectE031>(*enemyStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition, attackDirection, camera, mapNum));
			break;
		case 32:
			for (auto& pos : attackPointList)
			{
				battleEffectList.push_back(make_shared<BattleEffectE032>(*enemyStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, pos, attackDirection, camera, mapNum));
			}
			break;
		case 33:
			battleEffectList.push_back(make_shared<BattleEffectE033>(*enemyStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, attackPointList.front(), attackDirection, camera, mapNum));
			break;
		case 34:
			for (auto& pos : attackPointList)
			{
				battleEffectList.push_back(make_shared<BattleEffectE034>(*enemyStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, pos, attackDirection, camera, mapNum));
			}
			break;
		case 35:
			battleEffectList.push_back(make_shared<BattleEffectE035>(*enemyStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition, attackDirection, camera, mapNum));
			break;
		case 36:
			battleEffectList.push_back(make_shared<BattleEffectE036>(*enemyStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition, attackDirection, camera, mapNum));
			break;
		case 37:
			battleEffectList.push_back(make_shared<BattleEffectE037>(*enemyStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition, attackDirection, camera, mapNum));
			break;
		case 38:
			battleEffectList.push_back(make_shared<BattleEffectE038>(*enemyStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition, attackDirection, camera, mapNum));
			break;
		case 39:
			battleEffectList.push_back(make_shared<BattleEffectE039>(*enemyStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, attackPointList.front(), attackDirection, camera, mapNum));
			break;
		case 40:
			battleEffectList.push_back(make_shared<BattleEffectE040>(*enemyStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition, attackDirection, camera, mapNum));
			break;
		case 41:
			for (auto& pos : attackPointList)
			{
				battleEffectList.push_back(make_shared<BattleEffectE041>(*enemyStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, pos, attackDirection, camera, mapNum));
			}
			break;
		case 42:
			for (auto& pos : attackPointList)
			{
				battleEffectList.push_back(make_shared<BattleEffectE042>(*enemyStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, pos, attackDirection, camera, mapNum));
			}
			break;
		case 43:
			for (auto& pos : attackPointList)
			{
				battleEffectList.push_back(make_shared<BattleEffectE043>(*enemyStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, pos, attackDirection, camera, mapNum));
			}
			break;
		case 44:
			battleEffectList.push_back(make_shared<BattleEffectE044>(*enemyStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition, attackDirection, camera, mapNum));
			break;
		case 45:
			for (int i = 0; i < 3; i++)
			{
				if (MapInfoList::GetMapInfoList()[mapNum].canThrough[attackPointList[i].y][attackPointList[i].x])
				{
					battleEffectList.push_back(make_shared<BattleEffectE045>(*enemyStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, attackPointList[i], attackDirection, camera, mapNum, 0));
				}
			}
			break;
		case 46:
			battleEffectList.push_back(make_shared<BattleEffectE046>(*enemyStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, attackPointList.front(), attackDirection, camera, mapNum));
			break;
		case 47:
			battleEffectList.push_back(make_shared<BattleEffectE047>(*enemyStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition, attackDirection, camera, mapNum));
			break;
		case 48:
			battleEffectList.push_back(make_shared<BattleEffectE048_1>(*enemyStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition, attackDirection, camera, mapNum));
			break;
		case 49:
			battleEffectList.push_back(make_shared<BattleEffectE049>(*enemyStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition, attackDirection, camera, mapNum));
			break;
		case 50:
			battleEffectList.push_back(make_shared<BattleEffectE050>(*enemyStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition, attackDirection, camera, mapNum));
			break;
		case 51:
			battleEffectList.push_back(make_shared<BattleEffectE051>(*enemyStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, attackPointList.front(), attackDirection, camera, mapNum));
			break;
		case 52:
			for (auto& pos : attackPointList)
			{
				battleEffectList.push_back(make_shared<BattleEffectE052>(*enemyStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, pos, attackDirection, camera, mapNum));
			}
			break;
		case 53:
			battleEffectList.push_back(make_shared<BattleEffectE053>(*enemyStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition, attackDirection, camera, mapNum));
			break;
		case 54:
			battleEffectList.push_back(make_shared<BattleEffectE054>(*enemyStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition, attackDirection, camera, mapNum));
			break;
		case 55:
			battleEffectList.push_back(make_shared<BattleEffectE055>(*enemyStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition, attackDirection, camera, mapNum));
			break;
		case 56:
			for (auto& pos : attackPointList)
			{
				battleEffectList.push_back(make_shared<BattleEffectE056>(*enemyStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, pos, attackDirection, camera, mapNum));
			}
			break;
		case 57:
			battleEffectList.push_back(make_shared<BattleEffectE057>(*enemyStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition, attackDirection, camera, mapNum));
			break;
		case 58:
			battleEffectList.push_back(make_shared<BattleEffectE058>(*enemyStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition, attackDirection, camera, mapNum, 0));
			break;
		case 59:
			battleEffectList.push_back(make_shared<BattleEffectE059>(*enemyStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition, attackDirection, camera, mapNum));
			break;
		case 60:
			battleEffectList.push_back(make_shared<BattleEffectE060>(*enemyStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition, attackDirection, camera, mapNum, 0, 0));
			break;
		case 61:
			battleEffectList.push_back(make_shared<BattleEffectE061>(*enemyStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition, attackDirection, camera, mapNum));
			break;
		case 62:
			battleEffectList.push_back(make_shared<BattleEffectE062>(*enemyStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition, attackDirection, camera, mapNum, 0, 0));
			break;
		case 63:
			for (auto& pos : attackPointList)
			{
				battleEffectList.push_back(make_shared<BattleEffectE063>(*enemyStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, pos, attackDirection, camera, mapNum));
			}
			break;
		case 64:
			battleEffectList.push_back(make_shared<BattleEffectE064>(*enemyStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition, attackDirection, camera, mapNum));
			break;
		case 65:
			battleEffectList.push_back(make_shared<BattleEffectE065>(*enemyStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition, attackDirection, camera, mapNum));
			break;
		case 66:
			for (int i = 0; i < 3; i++)
			{
				if (MapInfoList::GetMapInfoList()[mapNum].canThrough[attackPointList[i].y][attackPointList[i].x])
				{
					battleEffectList.push_back(make_shared<BattleEffectE066>(*enemyStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, attackPointList[i], attackDirection, camera, mapNum, 0));
				}
			}
			break;
		case 67:
			battleEffectList.push_back(make_shared<BattleEffectE067>(*enemyStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition, attackDirection, camera, mapNum));
			break;
		case 68:
			battleEffectList.push_back(make_shared<BattleEffectE068>(*enemyStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition, attackDirection, camera, mapNum, 0, 0));
			break;
		case 69:
			battleEffectList.push_back(make_shared<BattleEffectE069>(*enemyStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition, attackDirection, camera, mapNum));
			break;
		case 70:
			battleEffectList.push_back(make_shared<BattleEffectE070>(*enemyStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition, attackDirection, camera, mapNum));
			break;
		case 71:
			battleEffectList.push_back(make_shared<BattleEffectE071>(*enemyStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, attackPointList.front(), attackDirection, camera, mapNum));
			break;
		case 72:
			battleEffectList.push_back(make_shared<BattleEffectE072>(*enemyStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition, attackDirection, camera, mapNum));
			break;
		case 73:
			battleEffectList.push_back(make_shared<BattleEffectE073>(*enemyStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition, attackDirection, camera, mapNum));
			break;
		case 74:
			battleEffectList.push_back(make_shared<BattleEffectE074>(*enemyStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, attackPointList.front(), attackDirection, camera, mapNum));
			break;
		case 75:
			battleEffectList.push_back(make_shared<BattleEffectE075>(*enemyStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, attackPointList.front(), attackDirection, camera, mapNum));
			break;
		case 76:
			battleEffectList.push_back(make_shared<BattleEffectE076>(*enemyStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition, attackDirection, camera, mapNum));
			break;
		case 77:
			battleEffectList.push_back(make_shared<BattleEffectE077_1>(*enemyStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition, attackDirection, camera, mapNum));
			break;
		case 78:
			battleEffectList.push_back(make_shared<BattleEffectE078_1>(*enemyStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition, attackDirection, camera, mapNum));
			break;
		case 79:
			for (auto& pos : attackPointList)
			{
				battleEffectList.push_back(make_shared<BattleEffectE079>(*enemyStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, pos, attackDirection, camera, mapNum));
			}
			break;
		case 80:
			battleEffectList.push_back(make_shared<BattleEffectE080>(*enemyStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, attackPointList.front(), attackDirection, camera, mapNum));
			break;
		case 81:
			battleEffectList.push_back(make_shared<BattleEffectE081>(*enemyStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition, attackDirection, camera, mapNum));
			break;
		case 82:
			battleEffectList.push_back(make_shared<BattleEffectE082>(*enemyStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition, attackDirection, camera, mapNum));
			break;
		case 83:
			battleEffectList.push_back(make_shared<BattleEffectE083>(*enemyStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, attackPointList.front(), attackDirection, camera, mapNum));
			break;
		case 106:
			battleEffectList.push_back(make_shared<BattleEffectE106>(*enemyStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition, attackDirection, camera, mapNum));
			break;
		case 107:
			battleEffectList.push_back(make_shared<BattleEffectE107>(*enemyStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition, attackDirection, camera, mapNum));
			break;
		case 108:
			battleEffectList.push_back(make_shared<BattleEffectE108>(*enemyStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition, attackDirection, camera, mapNum));
			break;
		case 109:
			battleEffectList.push_back(make_shared<BattleEffectE109>(*enemyStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition, attackDirection, camera, mapNum, 0, 0));
			break;
		case 110:
			for (auto& pos : attackPointList)
			{
				battleEffectList.push_back(make_shared<BattleEffectE119>(*enemyStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, pos, attackDirection, camera, mapNum));
			}
			break;
		}

		attackPointList.clear();
		attackTimer = 0;
		stiffTimer = EnemySkillInfoList::GetEnemySkillInfoList()[attackKind].stiff;
		if (setStiffTime != -1)
		{
			stiffTimer = setStiffTime;
		}
		setStiffTime = -1;
		setAttackTime = -1;
		attackKind = -1;
		subState = 0;
		moveCounter = 0;
	}
}

void EnemyMap::UpdateStiffTimer()
{
	stiffTimer--;
	stiffTimer = max(stiffTimer, 0);
}

void EnemyMap::UpdateMoveUnnotice()
{
	if (moveIntervalTimer < enemyStatus->GetMoveIntervalUnnotice())
	{
		UpdateMoveIntervalTimer();
	}
	else
	{
		StartMove(enemyStatus->GetMoveSpeedUnnotice(), StartMoveKind::RAMDOM);
	}
}

void EnemyMap::UpdateMoveIntervalTimer()
{
	moveIntervalTimer++;
}

void EnemyMap::StartMove(double _speed, StartMoveKind startMoveKind)
{
	if (stiffTimer > 0)
	{
		return;
	}

	Direction nextDirection;
	Vector2<int> next;

	switch (startMoveKind)
	{
	case StartMoveKind::RAMDOM:
		nextDirection = (Direction)(GetRand(1000) % (int)Direction::SIZE);
		break;
	case StartMoveKind::CLOSE:
	{
		Vector2<int> diff = playerMap->GetMasuPosition() - masuPosition;
		Vector2<int> next1, next2;
		Direction nextDirection1, nextDirection2;

		if (abs(diff.x) <= abs(diff.y))
		{
			if (diff.y > 0)
			{
				next1 = masuPosition + Vector2<int>(0, 1);
				nextDirection1 = Direction::DOWN;
			}
			else
			{
				next1 = masuPosition + Vector2<int>(0, -1);
				nextDirection1 = Direction::UP;
			}
			if (diff.x > 0)
			{
				next2 = masuPosition + Vector2<int>(1, 0);
				nextDirection2 = Direction::RIGHT;
			}
			else
			{
				next2 = masuPosition + Vector2<int>(-1, 0);
				nextDirection2 = Direction::LEFT;
			}
		}
		else
		{
			if (diff.y > 0)
			{
				next2 = masuPosition + Vector2<int>(0, 1);
				nextDirection2 = Direction::DOWN;
			}
			else
			{
				next2 = masuPosition + Vector2<int>(0, -1);
				nextDirection2 = Direction::UP;
			}
			if (diff.x > 0)
			{
				next1 = masuPosition + Vector2<int>(1, 0);
				nextDirection1 = Direction::RIGHT;
			}
			else
			{
				next1 = masuPosition + Vector2<int>(-1, 0);
				nextDirection1 = Direction::LEFT;
			}
		}

		if (CanMoveToNextPosition(next1,nextDirection1))
		{
			nextDirection = nextDirection1;
		}
		else
		{
			nextDirection = nextDirection2;
		}
	}
	break;
	case StartMoveKind::ALIGNMENT:
	{
		Vector2<int> diff = playerMap->GetMasuPosition() - masuPosition;
		Vector2<int> next1, next2;
		Direction nextDirection1, nextDirection2;

		if (abs(diff.x) <= abs(diff.y))
		{
			if (diff.y > 0)
			{
				next2 = masuPosition + Vector2<int>(0, 1);
				nextDirection2 = Direction::DOWN;
			}
			else
			{
				next2 = masuPosition + Vector2<int>(0, -1);
				nextDirection2 = Direction::UP;
			}
			if (diff.x > 0)
			{
				next1 = masuPosition + Vector2<int>(1, 0);
				nextDirection1 = Direction::RIGHT;
			}
			else
			{
				next1 = masuPosition + Vector2<int>(-1, 0);
				nextDirection1 = Direction::LEFT;
			}
		}
		else
		{
			if (diff.y > 0)
			{
				next1 = masuPosition + Vector2<int>(0, 1);
				nextDirection1 = Direction::DOWN;
			}
			else
			{
				next1 = masuPosition + Vector2<int>(0, -1);
				nextDirection1 = Direction::UP;
			}
			if (diff.x > 0)
			{
				next2 = masuPosition + Vector2<int>(1, 0);
				nextDirection2 = Direction::RIGHT;
			}
			else
			{
				next2 = masuPosition + Vector2<int>(-1, 0);
				nextDirection2 = Direction::LEFT;
			}
		}

		if (CanMoveToNextPosition(next1,nextDirection1))
		{
			nextDirection = nextDirection1;
		}
		else
		{
			nextDirection = nextDirection2;
		}
	}
	break;
	case StartMoveKind::AWAY:
	{
		Vector2<int> diff = playerMap->GetMasuPosition() - masuPosition;
		Vector2<int> next1, next2;
		Direction nextDirection1, nextDirection2;

		if (abs(diff.x) <= abs(diff.y))
		{
			if (diff.y > 0)
			{
				next1 = masuPosition - Vector2<int>(0, 1);
				nextDirection1 = Direction::UP;
			}
			else
			{
				next1 = masuPosition - Vector2<int>(0, -1);
				nextDirection1 = Direction::DOWN;
			}
			if (diff.x > 0)
			{
				next2 = masuPosition - Vector2<int>(1, 0);
				nextDirection2 = Direction::LEFT;
			}
			else
			{
				next2 = masuPosition - Vector2<int>(-1, 0);
				nextDirection2 = Direction::RIGHT;
			}
		}
		else
		{
			if (diff.y > 0)
			{
				next2 = masuPosition - Vector2<int>(0, 1);
				nextDirection2 = Direction::UP;
			}
			else
			{
				next2 = masuPosition - Vector2<int>(0, -1);
				nextDirection2 = Direction::DOWN;
			}
			if (diff.x > 0)
			{
				next1 = masuPosition - Vector2<int>(1, 0);
				nextDirection1 = Direction::LEFT;
			}
			else
			{
				next1 = masuPosition - Vector2<int>(-1, 0);
				nextDirection1 = Direction::RIGHT;
			}
		}

		if (CanMoveToNextPosition(next1,nextDirection1))
		{
			nextDirection = nextDirection1;
		}
		else
		{
			nextDirection = nextDirection2;
		}
	}
		break;
	}

	direction = nextDirection;

	switch (nextDirection)
	{
	case Direction::UP:
		next = masuPosition + Vector2<int>(0, -1);
		break;
	case Direction::DOWN:
		next = masuPosition + Vector2<int>(0, 1);
		break;
	case Direction::LEFT:
		next = masuPosition + Vector2<int>(-1, 0);
		break;
	case Direction::RIGHT:
		next = masuPosition + Vector2<int>(1, 0);
		break;
	}

	if (CanMoveToNextPosition(next,nextDirection))
	{
		masuPosition = next;
		switch (nextDirection)
		{
		case Direction::UP:
			velocity = Vector2<double>::UP;
			break;
		case Direction::DOWN:
			velocity = Vector2<double>::DOWN;
			break;
		case Direction::LEFT:
			velocity = Vector2<double>::LEFT;
			break;
		case Direction::RIGHT:
			velocity = Vector2<double>::RIGHT;
			break;
		}

		velocity *= _speed;
		moveEndTime = (int)((double)Define::MASU_SIZE / (int)_speed);
		moveState = MoveState::WALK;
		moveIntervalTimer = 0;
	}
}

void EnemyMap::Notice()
{
	double distance = (masuPosition - playerMap->GetMasuPosition()).length();
	if (distance <= enemyStatus->GetNoticeDistance())
	{
		noticeFlag = true;
	}
}

void EnemyMap::Move()
{
	position += velocity;

	moveTime++;
	if (moveTime == moveEndTime)
	{
		moveTime = 0;
		moveState = MoveState::STOP;
		position = Vector2<double>((double)masuPosition.x, (double)masuPosition.y)*(double)Define::MASU_SIZE + Vector2<double>((double)Define::MASU_SIZE / 2, (double)Define::MASU_SIZE / 2);
	}
}

void EnemyMap::UpdateDamagedTimer()
{
	if (damagedFlag)
	{
		damagedTimer++;
		if (damagedTimer == Define::SHOW_ENEMY_HP_TIME)
		{
			damagedTimer = 0;
			damagedFlag = false;
		}
	}
}

void EnemyMap::UpdateKnockBack()
{
	if (knockBackTimer % (Define::MASU_SIZE / Define::KNOCKBACK_VELOCITY) == 0)
	{
		Vector2<int> next;
		switch (knockBackDirection)
		{
		case Direction::DOWN:
			next = masuPosition + Vector2<int>((int)Vector2<double>::DOWN.x, (int)Vector2<double>::DOWN.y);
			break;
		case Direction::LEFT:
			next = masuPosition + Vector2<int>((int)Vector2<double>::LEFT.x, (int)Vector2<double>::LEFT.y);
			break;
		case Direction::RIGHT:
			next = masuPosition + Vector2<int>((int)Vector2<double>::RIGHT.x, (int)Vector2<double>::RIGHT.y);
			break;
		case Direction::UP:
			next = masuPosition + Vector2<int>((int)Vector2<double>::UP.x, (int)Vector2<double>::UP.y);
			break;
		}
		if (CanMoveToNextPosition(next,knockBackDirection))
		{
			masuPosition = next;
		}
		else
		{
			knockBackFlag = false;
			knockBackTimer = 0;
			return;
		}
	}
	position += knockBackVelocity;
	knockBackTimer++;
	if (knockBackTimer == (Define::MASU_SIZE * 3 / Define::KNOCKBACK_VELOCITY))
	{
		knockBackFlag = false;
		knockBackTimer = 0;
	}
}

void EnemyMap::CauseByPlayer(int sourceID, int skillKind,bool SPMAX)
{
	int value;
	value = enemyStatus->CauseByPlayer(playerData, sourceID, skillKind, attackTimer > 0,SPMAX);
	if (value >= 10000)
	{
		playerData->StandFlag(900);
	}
	noticeFlag = true;
	
	if (enemyStatus->GetHP() == 0)
	{
		deathFlag = true;
	}

	if (skillKind != 100 && skillKind != 101)
	{
		if (CharacterSkillInfoList::GetCharacterSkillInfoList()[skillKind].attribute[(int)PlayerSkillAttribute::KNOCKBACK] == 1)
		{
			switch (playerMap->GetDirection())
			{
			case Direction::DOWN:
				knockBackVelocity = Vector2<double>::DOWN*Define::KNOCKBACK_VELOCITY;
				break;
			case Direction::LEFT:
				knockBackVelocity = Vector2<double>::LEFT*Define::KNOCKBACK_VELOCITY;
				break;
			case Direction::RIGHT:
				knockBackVelocity = Vector2<double>::RIGHT*Define::KNOCKBACK_VELOCITY;
				break;
			case Direction::UP:
				knockBackVelocity = Vector2<double>::UP*Define::KNOCKBACK_VELOCITY;
				break;
			}
			knockBackFlag = true;
			knockBackDirection = playerMap->GetDirection();
		}
	}

	if (skillKind == 100 || skillKind == 101||CharacterSkillInfoList::GetCharacterSkillInfoList()[skillKind].type == SkillType::ATTACK)
	{
		damagedFlag = true;
		damagedTimer = 0;
		textUIList.push_back(make_shared<DamageText>(camera, position, value));
	}
}

void EnemyMap::DrawHP()
{
	//if (damagedFlag)
	{
		DrawFillBox(position.x - 16 - camera.x, position.y - 20 - camera.y, position.x - 16 + 32 * (enemyStatus->GetHPRate()) - camera.x, position.y - 17 - camera.y, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::GREEN]);
	}
}

void EnemyMap::Death()
{
	assert(kind != -1 && "EnemyMap::Death()");
	playerData->KillMonster(kind);
	for (auto& obj : playerData->GetCharacterStatusList())
	{
		if (!playerData->GetExistCharacterFlag()[obj->GetCharacterNum()] || obj->GetHP() == 0)
		{
			continue;
		}
		obj->AddEXP(enemyStatus->GetDropEXP());
	}
	playerData->GetPlayerStatus()->AddMoney(enemyStatus->GetDropMoney());
	playerData->StandFlag(100 + kind);

	textUIList.push_back(make_shared<DropEXPText>(camera, Vector2<double>(position.x, position.y - 10), enemyStatus->GetDropEXP()));
	textUIList.push_back(make_shared<DropMoneyText>(camera, Vector2<double>(position.x, position.y + 10), enemyStatus->GetDropMoney()));

	vector<int> dropItem;

	for (int i = 0; i != enemyStatus->GetDropItem().size(); i++)
	{
		int rand = (GetRand(10000) % 100) + 1;
		if (rand <= enemyStatus->GetDropItemPercent()[i])
		{
			dropItem.push_back(enemyStatus->GetDropItem()[i]);
		}
	}

	if (dropItem.size() != 0)
	{
		dropItemList.push_back(make_shared<DropItem>(dropItem, masuPosition, camera));
	}
}

bool EnemyMap::CanMoveToNextPosition(Vector2<int> next,Direction nextDirection)
{
	if (!MapInfoList::GetMapInfoList()[mapNum].canThrough[next.y][next.x])
	{
		return false;
	}

	if (MapInfoList::GetMapInfoList()[mapNum].event[next.y][next.x] != -1)
	{
		if (!EventInfoList::GetEventInfoList()[MapInfoList::GetMapInfoList()[mapNum].event[next.y][next.x]].canThrough)
		{
			return false;
		}
	}

	for (auto& obj : objectMapList)
	{
		if (!obj->GetCanThrough() && obj->GetMasuPosition() == next)
		{
			return false;
		}
	}

	if (playerMap->GetMasuPosition() == next)
	{
		return false;
	}

	if (find_if(bossMapList.begin(), bossMapList.end(), [&](BossMapPtr& obj) {return count_if(obj->GetMasuPosition().begin(), obj->GetMasuPosition().end(), [&](const Vector2<int>& pos) {return pos == next; }) > 0; }) != bossMapList.end())
	{
		return false;
	}

	if (find_if(enemyMapList.begin(), enemyMapList.end(), [&](EnemyMapPtr& obj) {return obj->GetMasuPosition() == next; }) != enemyMapList.end())
	{
		return false;
	}

	if (find_if(peopleMapList.begin(), peopleMapList.end(), [&](PeopleMapPtr& obj) {return obj->GetMasuPosition() == next; }) != peopleMapList.end())
	{
		return false;
	}

	switch (nextDirection)
	{
	case Direction::UP:
		for (auto n : MapInfoList::GetCannotThroughUp())
		{
			if (MapInfoList::GetMapInfoList()[mapNum].mapChip[masuPosition.y][masuPosition.x] == n)
			{
				return false;
			}
		}
		for (auto n : MapInfoList::GetCannotThroughUpObject())
		{
			if (MapInfoList::GetMapInfoList()[mapNum].mapObject[0][masuPosition.y][masuPosition.x] == n)
			{
				return false;
			}
		}
		for (auto n : MapInfoList::GetCannotThroughDown())
		{
			if (MapInfoList::GetMapInfoList()[mapNum].mapChip[masuPosition.y - 1][masuPosition.x] == n)
			{
				return false;
			}
		}
		for (auto n : MapInfoList::GetCannotThroughDownObject())
		{
			if (MapInfoList::GetMapInfoList()[mapNum].mapObject[0][masuPosition.y - 1][masuPosition.x] == n)
			{
				return false;
			}
		}
		break;
	case Direction::DOWN:
		for (auto n : MapInfoList::GetCannotThroughDown())
		{
			if (MapInfoList::GetMapInfoList()[mapNum].mapChip[masuPosition.y][masuPosition.x] == n)
			{
				return false;
			}
		}
		for (auto n : MapInfoList::GetCannotThroughDownObject())
		{
			if (MapInfoList::GetMapInfoList()[mapNum].mapObject[0][masuPosition.y][masuPosition.x] == n)
			{
				return false;
			}
		}
		for (auto n : MapInfoList::GetCannotThroughUp())
		{
			if (MapInfoList::GetMapInfoList()[mapNum].mapChip[masuPosition.y + 1][masuPosition.x] == n)
			{
				return false;
			}
		}
		for (auto n : MapInfoList::GetCannotThroughUpObject())
		{
			if (MapInfoList::GetMapInfoList()[mapNum].mapObject[0][masuPosition.y + 1][masuPosition.x] == n)
			{
				return false;
			}
		}
		break;
	case Direction::RIGHT:
		for (auto n : MapInfoList::GetCannotThroughRight())
		{
			if (MapInfoList::GetMapInfoList()[mapNum].mapChip[masuPosition.y][masuPosition.x] == n)
			{
				return false;
			}
		}
		for (auto n : MapInfoList::GetCannotThroughRightObject())
		{
			if (MapInfoList::GetMapInfoList()[mapNum].mapObject[0][masuPosition.y][masuPosition.x] == n)
			{
				return false;
			}
		}
		for (auto n : MapInfoList::GetCannotThroughLeft())
		{
			if (MapInfoList::GetMapInfoList()[mapNum].mapChip[masuPosition.y][masuPosition.x + 1] == n)
			{
				return false;
			}
		}
		for (auto n : MapInfoList::GetCannotThroughLeftObject())
		{
			if (MapInfoList::GetMapInfoList()[mapNum].mapObject[0][masuPosition.y][masuPosition.x + 1] == n)
			{
				return false;
			}
		}
		break;
	case Direction::LEFT:
		for (auto n : MapInfoList::GetCannotThroughLeft())
		{
			if (MapInfoList::GetMapInfoList()[mapNum].mapChip[masuPosition.y][masuPosition.x] == n)
			{
				return false;
			}
		}
		for (auto n : MapInfoList::GetCannotThroughLeftObject())
		{
			if (MapInfoList::GetMapInfoList()[mapNum].mapObject[0][masuPosition.y][masuPosition.x] == n)
			{
				return false;
			}
		}
		for (auto n : MapInfoList::GetCannotThroughRight())
		{
			if (MapInfoList::GetMapInfoList()[mapNum].mapChip[masuPosition.y][masuPosition.x - 1] == n)
			{
				return false;
			}
		}
		for (auto n : MapInfoList::GetCannotThroughRightObject())
		{
			if (MapInfoList::GetMapInfoList()[mapNum].mapObject[0][masuPosition.y][masuPosition.x - 1] == n)
			{
				return false;
			}
		}
		break;
	}

	return true;
}

void EnemyMap::DrawAttackPoint()
{
	Function::Alpha(160);
	for (auto& pos : attackPointList)
	{
		Vector2<int> tempPos = pos*Define::MASU_SIZE;
		DrawFillBox(tempPos.x - camera.x, tempPos.y - camera.y, tempPos.x + Define::MASU_SIZE - camera.x, tempPos.y + Define::MASU_SIZE - camera.y, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::RED]);
	}
	Function::Alpha(255);
}

void EnemyMap::Draw()
{
	DrawRotaGraphF(position.x - camera.x, position.y - camera.y, 1.0, 0.0, graph[kind], TRUE);
}