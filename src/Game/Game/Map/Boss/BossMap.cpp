#include"../header/BossMap.h"
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

#include"../header/DropEXPText.h"
#include"../header/DropMoneyText.h"

#include"../header/ObjectMap000.h"

#include"../header/BattleEffectE084.h"
#include"../header/BattleEffectE085.h"
#include"../header/BattleEffectE086.h"
#include"../header/BattleEffectE087.h"
#include"../header/BattleEffectE088_1.h"
#include"../header/BattleEffectE089.h"
#include"../header/BattleEffectE090.h"
#include"../header/BattleEffectE091.h"
#include"../header/BattleEffectE092.h"
#include"../header/BattleEffectE093.h"
#include"../header/BattleEffectE094.h"
#include"../header/BattleEffectE095.h"
#include"../header/BattleEffectE096.h"
#include"../header/BattleEffectE097.h"
#include"../header/BattleEffectE098.h"
#include"../header/BattleEffectE099.h"
#include"../header/BattleEffectE100.h"
#include"../header/BattleEffectE101.h"
#include"../header/BattleEffectE102.h"
#include"../header/BattleEffectE103.h"
#include"../header/BattleEffectE104.h"
#include"../header/BattleEffectE105.h"
#include"../header/BattleEffectE110.h"
#include"../header/BattleEffectE111.h"
#include"../header/BattleEffectE112.h"
#include"../header/BattleEffectE113.h"
#include"../header/BattleEffectE114.h"
#include"../header/BattleEffectE115.h"
#include"../header/BattleEffectE116.h"
#include"../header/BattleEffectE117_1.h"
#include"../header/BattleEffectE118.h"
#include"../header/BattleEffectE120_1.h"
#include"../header/BattleEffectE121.h"
#include"../header/BattleEffectE122.h"
#include"../header/BattleEffectE123.h"
#include"../header/BattleEffectE124_1.h"
#include"../header/BattleEffectE124_2.h"
#include"../header/BattleEffectE125.h"
#include"../header/BattleEffectE126.h"
#include"../header/BattleEffectE127.h"
#include"../header/BattleEffectE128.h"
#include"../header/BattleEffectE129.h"
#include"../header/BattleEffectE130.h"
#include"../header/EnemyMap044.h"

GHandle BossMap::graph[Define::BOSS_KIND_NUM];

BossMap::BossMap(PlayerData* playerData, PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<EnemyMapPtr>& enemyMapList, list<PeopleMapPtr>& peopleMapList, list<BattleEffectPtr>& battleEffectList, list<TextUIPtr>& textUIList, list<DropItemPtr>& dropItemList, int id, int kind,Vector2<int> masuPosition, Vector2<double>& camera, int& mapNum, int standFlag,int specialEventNum) :textUIList(textUIList), playerData(playerData), bossMapList(bossMapList), enemyMapList(enemyMapList), peopleMapList(peopleMapList), playerMap(playerMap), id(id), camera(camera), battleEffectList(battleEffectList), dropItemList(dropItemList), mapNum(mapNum), objectMapList(objectMapList), standFlag(standFlag),kind(kind),specialEventNum(specialEventNum)
{
	this->masuPosition.push_back(masuPosition);
	for (int i = -1; i < 2; i++)for (int j = -1; j < 2; j++)
	{
		if (i != 0 || j != 0)
		{
			this->masuPosition.push_back(masuPosition + Vector2<int>(i,j));
		}
	}
	position = Vector2<double>(masuPosition.x*Define::MASU_SIZE + (double)Define::MASU_SIZE / 2, masuPosition.y*Define::MASU_SIZE + (double)Define::MASU_SIZE / 2);
	direction = Direction::DOWN;
	moveState = MoveState::STOP;

	velocity = Vector2<double>(0.0, 0.0);
	moveTime = 0;
	moveEndTime = 0;

	deathFlag = false;

	damagedFlag = false;
	damagedTimer = 0;

	knockBackFlag = false;
	knockBackTimer = 0;
	knockBackVelocity = Vector2<double>(0.0, 0.0);
	knockBackDirection = Direction::UP;

	moveIntervalTimer = 0;

	stiffTime = -1;
	delay = -1;
	stiffTimer = 0;

	attackKind = -1;
	attackTimer = 0;

	state = 0;
	state1 = 0;
	preAttackKind = -1;
	tempAttackKind = -1;
	moveCounter = 0;
	werpCounter = 0;
	setAttackTime = -1;
	setStiffTime = -1;
}

BossMap::~BossMap()
{
	delete bossStatus;
}

void BossMap::Load()
{
	for (int i = 0; i < Define::BOSS_KIND_NUM; i++)
	{
		stringstream ss;
		ss << "data/graph/character/enemy/boss" << Function::NumToStringFillZero(i, 3) << ".png";
		graph[i] = LoadGraph(ss.str().c_str());
		assert(graph[i] != 0 && "BossMap::Load()‚É‚ÄŽ¸”s‚µ‚Ü‚µ‚½B");
	}
}

void BossMap::Update()
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
			
				if (attackKind == -1)
				{
					UpdateNotice();
				}
				else
				{
					UpdateAttackTimer();
				}
			
			break;
		default:
			Move();
			break;
		}
	}
}

void BossMap::UpdateAttackTimer()
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
		case 84:
			battleEffectList.push_back(make_shared<BattleEffectE084>(*bossStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition.front(), attackDirection, camera, mapNum));
			break;
		case 85:
			battleEffectList.push_back(make_shared<BattleEffectE085>(*bossStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition.front(), attackDirection, camera, mapNum, 0, 0));
			break;
		case 86:
			battleEffectList.push_back(make_shared<BattleEffectE086>(*bossStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition.front(), attackDirection, camera, mapNum, 0));
			break;
		case 87:
			battleEffectList.push_back(make_shared<BattleEffectE087>(*bossStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition.front(), attackDirection, camera, mapNum));
			break;
		case 88:
			battleEffectList.push_back(make_shared<BattleEffectE088_1>(*bossStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition.front(), attackDirection, camera, mapNum));
			break;
		case 89:
			battleEffectList.push_back(make_shared<BattleEffectE089>(*bossStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition.front(), attackDirection, camera, mapNum));
			break;
		case 90:
			for (auto& pos : attackPointList)
			{
				battleEffectList.push_back(make_shared<BattleEffectE090>(*bossStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, pos, attackDirection, camera, mapNum));
			}
			break;
		case 91:
			battleEffectList.push_back(make_shared<BattleEffectE091>(*bossStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition.front(), attackDirection, camera, mapNum));
			break;
		case 92:
			for (auto& pos : attackPointList)
			{
				battleEffectList.push_back(make_shared<BattleEffectE092>(*bossStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, pos, attackDirection, camera, mapNum));
			}
			break;
		case 93:
			for (auto& pos : attackPointList)
			{
				battleEffectList.push_back(make_shared<BattleEffectE093>(*bossStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, pos, attackDirection, camera, mapNum));
			}
			break;
		case 94:
			for (auto& pos : attackPointList)
			{
				battleEffectList.push_back(make_shared<BattleEffectE094>(*bossStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, pos, attackDirection, camera, mapNum));
			}
			break;
		case 95:
			for (auto& pos : attackPointList)
			{
				if (attackPointList.front() == pos)
				{
					battleEffectList.push_back(make_shared<BattleEffectE095>(*bossStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, pos, attackDirection, camera, mapNum, true, 0));
				}
				else
				{
					battleEffectList.push_back(make_shared<BattleEffectE095>(*bossStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, pos, attackDirection, camera, mapNum, false, 0));
				}
			}
			break;
		case 96:
			battleEffectList.push_back(make_shared<BattleEffectE096>(*bossStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition.front(), attackDirection, camera, mapNum));
			break;
		case 97:
			battleEffectList.push_back(make_shared<BattleEffectE097>(*bossStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition.front(), attackDirection, camera, mapNum, 0, 0));
			break;
		case 98:
			battleEffectList.push_back(make_shared<BattleEffectE098>(*bossStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition.front(), attackDirection, camera, mapNum));
			break;
		case 99:
			for (auto& pos : attackPointList)
			{
				battleEffectList.push_back(make_shared<BattleEffectE099>(*bossStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, pos, attackDirection, camera, mapNum));
			}
			break;
		case 100:
			for (auto& pos : attackPointList)
			{
				battleEffectList.push_back(make_shared<BattleEffectE100>(*bossStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, pos, attackDirection, camera, mapNum));
			}
			break;
		case 101:
			for (auto& pos : attackPointList)
			{
				battleEffectList.push_back(make_shared<BattleEffectE101>(*bossStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, pos, attackDirection, camera, mapNum));
			}
			break;
		case 102:
			battleEffectList.push_back(make_shared<BattleEffectE102>(*bossStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition.front(), attackDirection, camera, mapNum));
			break;
		case 103:
			battleEffectList.push_back(make_shared<BattleEffectE103>(*bossStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition.front(), attackDirection, camera, mapNum));
			break;
		case 104:
			for (auto& pos : attackPointList)
			{
				battleEffectList.push_back(make_shared<BattleEffectE104>(*bossStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, pos, attackDirection, camera, mapNum));
				enemyMapList.push_back(make_shared<EnemyMap044>(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, 44, pos, camera, battleEffectList, textUIList, dropItemList, mapNum));
			}
			break;
		case 105:
			battleEffectList.push_back(make_shared<BattleEffectE105>(*bossStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition.front(), attackDirection, camera, mapNum));
			break;
		case 110:
			battleEffectList.push_back(make_shared<BattleEffectE110>(*bossStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition.front(), attackDirection, camera, mapNum));
			break;
		case 111:
			battleEffectList.push_back(make_shared<BattleEffectE111>(*bossStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition.front(), attackDirection, camera, mapNum));
			break;
		case 112:
			battleEffectList.push_back(make_shared<BattleEffectE112>(*bossStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition.front(), attackDirection, camera, mapNum,0,0));
			battleEffectList.push_back(make_shared<BattleEffectE112>(*bossStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition.front(), attackDirection, camera, mapNum,1,0));
			break;
		case 113:
			battleEffectList.push_back(make_shared<BattleEffectE113>(*bossStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition.front(), attackDirection, camera, mapNum, 0, 0));
			battleEffectList.push_back(make_shared<BattleEffectE113>(*bossStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition.front(), attackDirection, camera, mapNum, 1, 0));
			break;
		case 114:
			battleEffectList.push_back(make_shared<BattleEffectE114>(*bossStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition.front(), attackDirection, camera, mapNum, 0, 0));
			battleEffectList.push_back(make_shared<BattleEffectE114>(*bossStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition.front(), attackDirection, camera, mapNum, 1, 0));
			break;
		case 115:
			battleEffectList.push_back(make_shared<BattleEffectE115>(*bossStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition.front(), attackDirection, camera, mapNum, 0, 0));
			break;
		case 116:
			battleEffectList.push_back(make_shared<BattleEffectE116>(*bossStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition.front(), attackDirection, camera, mapNum, 0, 0));
			break;
		case 117:
			battleEffectList.push_back(make_shared<BattleEffectE117_1>(*bossStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition.front(), attackDirection, camera, mapNum));
			break;
		case 118:
			for (auto& pos : attackPointList)
			{
				battleEffectList.push_back(make_shared<BattleEffectE118>(*bossStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, pos, attackDirection, camera, mapNum));
			}
			break;
		case 120:
			battleEffectList.push_back(make_shared<BattleEffectE120_1>(*bossStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition.front(), attackDirection, camera, mapNum));
			break;
		case 121:
			battleEffectList.push_back(make_shared<BattleEffectE121>(*bossStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition.front(), attackDirection, camera, mapNum));
			break;
		case 122:
			battleEffectList.push_back(make_shared<BattleEffectE122>(*bossStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition.front(), attackDirection, camera, mapNum, 0, 0));
			break;
		case 123:
			battleEffectList.push_back(make_shared<BattleEffectE123>(*bossStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition.front(), attackDirection, camera, mapNum));
			break;
		case 124:
			battleEffectList.push_back(make_shared<BattleEffectE124_1>(*bossStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition.front(), attackDirection, camera, mapNum));
			break;
		case 125:
			battleEffectList.push_back(make_shared<BattleEffectE125>(*bossStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, attackPointList.front(), attackDirection, camera, mapNum));
			break;
		case 126:
			battleEffectList.push_back(make_shared<BattleEffectE126>(*bossStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition.front(), Direction::LEFT, camera, mapNum));
			battleEffectList.push_back(make_shared<BattleEffectE126>(*bossStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition.front(), Direction::RIGHT, camera, mapNum));
			break;
		case 127:
			for (auto& pos : attackPointList)
			{
				battleEffectList.push_back(make_shared<BattleEffectE127>(*bossStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, pos, attackDirection, camera, mapNum));
			}
			break;
		case 128:
			for (auto& pos : attackPointList)
			{
				battleEffectList.push_back(make_shared<BattleEffectE128>(*bossStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, pos, attackDirection, camera, mapNum));
			}
			break;
		case 129:
			battleEffectList.push_back(make_shared<BattleEffectE129>(*bossStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition.front(), attackDirection, camera, mapNum));
			break;
		case 130:
			battleEffectList.push_back(make_shared<BattleEffectE130>(*bossStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition.front(), attackDirection, camera, mapNum));
			break;
		}

		attackPointList.clear();
		attackTimer = 0;
		if (setStiffTime != -1)
		{
			stiffTimer = setStiffTime;
		}
		else
		{
			stiffTimer = EnemySkillInfoList::GetEnemySkillInfoList()[attackKind].stiff;
		}
		preAttackKind = attackKind;
		attackKind = -1;
		tempAttackKind = -1;
		stiffTime = -1;
		delay = -1;
		moveCounter = 0;
		werpCounter = 0;
		setAttackTime = -1;
		setStiffTime = -1;
	}
}

void BossMap::UpdateStiffTimer()
{
	stiffTimer--;
	stiffTimer = max(stiffTimer, 0);
}

void BossMap::UpdateMoveIntervalTimer()
{
	moveIntervalTimer++;
}

void BossMap::StartMove(double _speed, StartMoveKind startMoveKind)
{
	if (stiffTimer > 0)
	{
		return;
	}

	Direction nextDirection;
	array<Vector2<int>, 9> next;

	switch (startMoveKind)
	{
	case StartMoveKind::RAMDOM:
		nextDirection = (Direction)(GetRand(1000) % (int)Direction::SIZE);
		break;
	case StartMoveKind::CLOSE:
	{
		Vector2<int> diff = playerMap->GetMasuPosition() - masuPosition.front();
		array<Vector2<int>, 9> next1, next2;
		Direction nextDirection1, nextDirection2;

		if (abs(diff.x) <= abs(diff.y))
		{
			if (diff.y > 0)
			{
				for (int i = 0; i != masuPosition.size(); i++)
				{
					next1[i] = masuPosition[i] + Vector2<int>(0, 1);
				}
				nextDirection1 = Direction::DOWN;
			}
			else
			{
				for (int i = 0; i != masuPosition.size(); i++)
				{
					next1[i] = masuPosition[i] + Vector2<int>(0, -1);
				}
				nextDirection1 = Direction::UP;
			}
			if (diff.x > 0)
			{
				for (int i = 0; i != masuPosition.size(); i++)
				{
					next2[i] = masuPosition[i] + Vector2<int>(1, 0);
				}
				nextDirection2 = Direction::RIGHT;
			}
			else
			{
				for (int i = 0; i != masuPosition.size(); i++)
				{
					next2[i] = masuPosition[i] + Vector2<int>(-1, 0);
				}
				nextDirection2 = Direction::LEFT;
			}
		}
		else
		{
			if (diff.y > 0)
			{
				for (int i = 0; i != masuPosition.size(); i++)
				{
					next2[i] = masuPosition[i] + Vector2<int>(0, 1);
				}		
				nextDirection2 = Direction::DOWN;
			}
			else
			{
				for (int i = 0; i != masuPosition.size(); i++)
				{
					next2[i] = masuPosition[i] + Vector2<int>(0, -1);
				}	
				nextDirection2 = Direction::UP;
			}
			if (diff.x > 0)
			{
				for (int i = 0; i != masuPosition.size(); i++)
				{
					next1[i] = masuPosition[i] + Vector2<int>(1, 0);
				}	
				nextDirection1 = Direction::RIGHT;
			}
			else
			{
				for (int i = 0; i != masuPosition.size(); i++)
				{
					next1[i] = masuPosition[i] + Vector2<int>(-1, 0);
				}	
				nextDirection1 = Direction::LEFT;
			}
		}

		if (count_if(next1.begin(), next1.end(), [&](const Vector2<int>& pos) {return !CanMoveToNextPosition(pos,nextDirection1); }) == 0)
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
		Vector2<int> diff = playerMap->GetMasuPosition() - masuPosition.front();
		array<Vector2<int>, 9> next1, next2;
		Direction nextDirection1, nextDirection2;
		
		if (abs(diff.x) <= abs(diff.y))
		{
			if (diff.y > 0)
			{
				for (int i = 0; i != masuPosition.size(); i++)
				{
					next2[i] = masuPosition[i] + Vector2<int>(0, 1);
				}
				nextDirection2 = Direction::DOWN;
			}
			else
			{
				for (int i = 0; i != masuPosition.size(); i++)
				{
					next2[i] = masuPosition[i] + Vector2<int>(0, -1);
				}
				nextDirection2 = Direction::UP;
			}
			if (diff.x > 0)
			{
				for (int i = 0; i != masuPosition.size(); i++)
				{
					next1[i] = masuPosition[i] + Vector2<int>(1, 0);
				}
				nextDirection1 = Direction::RIGHT;
			}
			else
			{
				for (int i = 0; i != masuPosition.size(); i++)
				{
					next1[i] = masuPosition[i] + Vector2<int>(-1, 0);
				}					
				nextDirection1 = Direction::LEFT;
			}
		}
		else
		{
			if (diff.y > 0)
			{
				for (int i = 0; i != masuPosition.size(); i++)
				{
					next1[i] = masuPosition[i] + Vector2<int>(0, 1);
				}	
				nextDirection1 = Direction::DOWN;
			}
			else
			{
				for (int i = 0; i != masuPosition.size(); i++)
				{
					next1[i] = masuPosition[i] + Vector2<int>(0, -1);
				}	
				nextDirection1 = Direction::UP;
			}
			if (diff.x > 0)
			{
				for (int i = 0; i != masuPosition.size(); i++)
				{
					next2[i] = masuPosition[i] + Vector2<int>(1, 0);
				}	
				nextDirection2 = Direction::RIGHT;
			}
			else
			{
				for (int i = 0; i != masuPosition.size(); i++)
				{
					next2[i] = masuPosition[i] + Vector2<int>(-1, 0);
				}	
				nextDirection2 = Direction::LEFT;
			}
		}

		if (count_if(next1.begin(), next1.end(), [&](const Vector2<int>& pos) {return !CanMoveToNextPosition(pos,nextDirection1); }) == 0)
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
		Vector2<int> diff = playerMap->GetMasuPosition() - masuPosition.front();
		array<Vector2<int>,9> next1, next2;
		Direction nextDirection1, nextDirection2;

		if (abs(diff.x) <= abs(diff.y))
		{
			if (diff.y > 0)
			{
				for (int i = 0; i != masuPosition.size(); i++)
				{
					next1[i] = masuPosition[i] - Vector2<int>(0, 1);
				}	
				nextDirection1 = Direction::UP;
			}
			else
			{
				for (int i = 0; i != masuPosition.size(); i++)
				{
					next1[i] = masuPosition[i] - Vector2<int>(0, -1);
				}	
				nextDirection1 = Direction::DOWN;
			}
			if (diff.x > 0)
			{
				for (int i = 0; i != masuPosition.size(); i++)
				{
					next2[i] = masuPosition[i] - Vector2<int>(1, 0);
				}	
				nextDirection2 = Direction::LEFT;
			}
			else
			{
				for (int i = 0; i != masuPosition.size(); i++)
				{
					next2[i] = masuPosition[i] - Vector2<int>(-1, 0);
				}	
				nextDirection2 = Direction::RIGHT;
			}
		}
		else
		{
			if (diff.y > 0)
			{
				for (int i = 0; i != masuPosition.size(); i++)
				{
					next2[i] = masuPosition[i] - Vector2<int>(0, 1);
				}	
				nextDirection2 = Direction::UP;
			}
			else
			{
				for (int i = 0; i != masuPosition.size(); i++)
				{
					next2[i] = masuPosition[i] - Vector2<int>(0, -1);
				}	
				nextDirection2 = Direction::DOWN;
			}
			if (diff.x > 0)
			{
				for (int i = 0; i != masuPosition.size(); i++)
				{
					next1[i] = masuPosition[i] - Vector2<int>(1, 0);
				}	
				nextDirection1 = Direction::LEFT;
			}
			else
			{
				for (int i = 0; i != masuPosition.size(); i++)
				{
					next1[i] = masuPosition[i] - Vector2<int>(-1, 0);
				}	
				nextDirection1 = Direction::RIGHT;
			}
		}

		if (count_if(next1.begin(), next1.end(), [&](const Vector2<int>& pos) {return !CanMoveToNextPosition(pos,nextDirection1); }) == 0)
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
		for (int i = 0; i != masuPosition.size(); i++)
		{
			next[i] = masuPosition[i] + Vector2<int>(0, -1);
		}
		break;
	case Direction::DOWN:
		for (int i = 0; i != masuPosition.size(); i++)
		{
			next[i] = masuPosition[i] + Vector2<int>(0, 1);
		}		
		break;
	case Direction::LEFT:
		for (int i = 0; i != masuPosition.size(); i++)
		{
			next[i] = masuPosition[i] + Vector2<int>(-1, 0);
		}
		break;
	case Direction::RIGHT:
		for (int i = 0; i != masuPosition.size(); i++)
		{
			next[i] = masuPosition[i] + Vector2<int>(1, 0);
		}
		break;
	}

	if (count_if(next.begin(), next.end(), [&](const Vector2<int>& pos) {return !CanMoveToNextPosition(pos,nextDirection); }) == 0)
	{
		for (int i = 0; i != masuPosition.size(); i++)
		{
			masuPosition[i] = next[i];
		}
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

bool BossMap::StartMove(double _speed, Direction _direction)
{
	if (stiffTimer > 0)
	{
		return false;
	}

	Direction nextDirection;
	array<Vector2<int>, 9> next;

	Vector2<int> diff = playerMap->GetMasuPosition() - masuPosition.front();
	array<Vector2<int>, 9> next1, next2;
	Direction nextDirection1, nextDirection2;

	nextDirection1 = _direction;

	switch (nextDirection1)
	{
	case Direction::UP:
		for (int i = 0; i != masuPosition.size(); i++)
		{
			next1[i] = masuPosition[i] + Vector2<int>(0, -1);
		}		
		break;
	case Direction::DOWN:
		for (int i = 0; i != masuPosition.size(); i++)
		{
			next1[i] = masuPosition[i] + Vector2<int>(0, 1);
		}		
		break;
	case Direction::RIGHT:
		for (int i = 0; i != masuPosition.size(); i++)
		{
			next1[i] = masuPosition[i] + Vector2<int>(1, 0);
		}
		break;
	case Direction::LEFT:
		for (int i = 0; i != masuPosition.size(); i++)
		{
			next1[i] = masuPosition[i] + Vector2<int>(-1, 0);
		}
		break;
	}

	if (count_if(next1.begin(), next1.end(), [&](const Vector2<int>& pos) {return !CanMoveToNextPosition(pos, nextDirection1); }) == 0)
	{
		nextDirection = nextDirection1;
	}
	else
	{
		return false;
	}

	direction = nextDirection;

	switch (nextDirection)
	{
	case Direction::UP:
		for (int i = 0; i != masuPosition.size(); i++)
		{
			next[i] = masuPosition[i] + Vector2<int>(0, -1);
		}
		break;
	case Direction::DOWN:
		for (int i = 0; i != masuPosition.size(); i++)
		{
			next[i] = masuPosition[i] + Vector2<int>(0, 1);
		}
		break;
	case Direction::LEFT:
		for (int i = 0; i != masuPosition.size(); i++)
		{
			next[i] = masuPosition[i] + Vector2<int>(-1, 0);
		}
		break;
	case Direction::RIGHT:
		for (int i = 0; i != masuPosition.size(); i++)
		{
			next[i] = masuPosition[i] + Vector2<int>(1, 0);
		}
		break;
	}

	if (count_if(next.begin(), next.end(), [&](const Vector2<int>& pos) {return !CanMoveToNextPosition(pos, nextDirection); }) == 0)
	{
		for (int i = 0; i != masuPosition.size(); i++)
		{
			masuPosition[i] = next[i];
		}
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
	return true;
}

void BossMap::Move()
{
	position += velocity;

	moveTime++;
	if (moveTime == moveEndTime)
	{
		moveTime = 0;
		moveState = MoveState::STOP;
		position = Vector2<double>((double)masuPosition.front().x, (double)masuPosition.front().y)*(double)Define::MASU_SIZE + Vector2<double>((double)Define::MASU_SIZE / 2, (double)Define::MASU_SIZE / 2);
	}
}

void BossMap::UpdateDamagedTimer()
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

void BossMap::UpdateKnockBack()
{
	if (knockBackTimer % (Define::MASU_SIZE / Define::KNOCKBACK_VELOCITY) == 0)
	{
		vector<Vector2<int>> next;
		switch (knockBackDirection)
		{
		case Direction::UP:
			for (int i = 0; i != masuPosition.size(); i++)
			{
				next[i] = masuPosition[i] + Vector2<int>(0, -1);
			}
			break;
		case Direction::DOWN:
			for (int i = 0; i != masuPosition.size(); i++)
			{
				next[i] = masuPosition[i] + Vector2<int>(0, 1);
			}
			break;
		case Direction::LEFT:
			for (int i = 0; i != masuPosition.size(); i++)
			{
				next[i] = masuPosition[i] + Vector2<int>(-1, 0);
			}
			break;
		case Direction::RIGHT:
			for (int i = 0; i != masuPosition.size(); i++)
			{
				next[i] = masuPosition[i] + Vector2<int>(1, 0);
			}
			break;
		}
		if (count_if(next.begin(), next.end(), [&](const Vector2<int>& pos) {return !CanMoveToNextPosition(pos,knockBackDirection); }) == 0)
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
	if (knockBackTimer == (Define::MASU_SIZE / Define::KNOCKBACK_VELOCITY))
	{
		knockBackFlag = false;
		knockBackTimer = 0;
	}
}

void BossMap::CauseByPlayer(int sourceID, int skillKind,bool SPMAX)
{
	if (find_if(battleEffectList.begin(), battleEffectList.end(), [](BattleEffectPtr& obj) {return typeid(*obj) == typeid(BattleEffectE124_1); }) != battleEffectList.end())
	{
		battleEffectList.push_back(make_shared<BattleEffectE124_2>(*bossStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, id, playerMap->GetMasuPosition() , attackDirection, camera, mapNum));
		return;
	}

	int value;
	value = bossStatus->CauseByPlayer(playerData, sourceID, skillKind, attackTimer > 0,SPMAX);
	if (value >= 10000)
	{
		playerData->StandFlag(900);
	}

	if (bossStatus->GetHP() == 0)
	{
		deathFlag = true;
	}

	if (skillKind == 100 || skillKind == 101 || CharacterSkillInfoList::GetCharacterSkillInfoList()[skillKind].type == SkillType::ATTACK)
	{
		damagedFlag = true;
		damagedTimer = 0;
		textUIList.push_back(make_shared<DamageText>(camera, position, value));
	}
}

void BossMap::DrawHP()
{
	DrawFillBox(position.x - 48 - camera.x, position.y - 52 - camera.y, position.x - 48 + 96 * (bossStatus->GetHPRate()) - camera.x, position.y - 49 - camera.y, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::GREEN]);
}

void BossMap::Death()
{
	assert(kind != -1 && "EnemyMap::Death()");
	playerData->KillMonster(kind);
	for (auto& obj : playerData->GetCharacterStatusList())
	{
		if (!playerData->GetExistCharacterFlag()[obj->GetCharacterNum()] || obj->GetHP() == 0)
		{
			continue;
		}
		obj->AddEXP(bossStatus->GetDropEXP());
	}
	playerData->GetPlayerStatus()->AddMoney(bossStatus->GetDropMoney());
	playerData->StandFlag(200 + kind);

	textUIList.push_back(make_shared<DropEXPText>(camera, Vector2<double>(position.x, position.y - 10), bossStatus->GetDropEXP()));
	textUIList.push_back(make_shared<DropMoneyText>(camera, Vector2<double>(position.x, position.y + 10), bossStatus->GetDropMoney()));

	if (bossStatus->GetDropItem().size() != 0)
	{
		dropItemList.push_back(make_shared<DropItem>(bossStatus->GetDropItem(), masuPosition.front(), camera));
	}

	if (bossMapList.size() == 1)
	{
		objectMapList.erase(remove_if(objectMapList.begin(), objectMapList.end(), [&](ObjectMapPtr& obj) {return typeid(*obj) == typeid(ObjectMap000); }), objectMapList.end());
	}

	if (standFlag != -1 && count_if(bossMapList.begin(), bossMapList.end(), [&](BossMapPtr& obj) {return !obj->GetDeathFlag(); }) == 0)
	{
		playerData->StandFlag(standFlag);
	}
	if (specialEventNum != -1)
	{
		playerMap->SetSpecialEventNum(specialEventNum);
	}
	enemyMapList.clear();
	battleEffectList.erase(remove_if(battleEffectList.begin(), battleEffectList.end(), [](BattleEffectPtr& obj) {return obj->GetTargetType() == TargetType::PLAYER; }), battleEffectList.end());
}

bool BossMap::CanMoveToNextPosition(Vector2<int> next, Direction nextDirection)
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

	if (find_if(bossMapList.begin(), bossMapList.end(), [&](BossMapPtr& obj) {return obj->GetID() != id&&count_if(obj->GetMasuPosition().begin(), obj->GetMasuPosition().end(), [&](const Vector2<int>& pos) {return pos == next; }) > 0; }) != bossMapList.end())
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
			if (MapInfoList::GetMapInfoList()[mapNum].mapChip[next.y + 1][next.x] == n)
			{
				return false;
			}
		}
		for (auto n : MapInfoList::GetCannotThroughUpObject())
		{
			if (MapInfoList::GetMapInfoList()[mapNum].mapObject[0][next.y + 1][next.x] == n)
			{
				return false;
			}
		}
		for (auto n : MapInfoList::GetCannotThroughDown())
		{
			if (MapInfoList::GetMapInfoList()[mapNum].mapChip[next.y][next.x] == n)
			{
				return false;
			}
		}
		for (auto n : MapInfoList::GetCannotThroughDownObject())
		{
			if (MapInfoList::GetMapInfoList()[mapNum].mapObject[0][next.y][next.x] == n)
			{
				return false;
			}
		}
		break;
	case Direction::DOWN:
		for (auto n : MapInfoList::GetCannotThroughDown())
		{
			if (MapInfoList::GetMapInfoList()[mapNum].mapChip[next.y - 1][next.x] == n)
			{
				return false;
			}
		}
		for (auto n : MapInfoList::GetCannotThroughDownObject())
		{
			if (MapInfoList::GetMapInfoList()[mapNum].mapObject[0][next.y - 1][next.x] == n)
			{
				return false;
			}
		}
		for (auto n : MapInfoList::GetCannotThroughUp())
		{
			if (MapInfoList::GetMapInfoList()[mapNum].mapChip[next.y][next.x] == n)
			{
				return false;
			}
		}
		for (auto n : MapInfoList::GetCannotThroughUpObject())
		{
			if (MapInfoList::GetMapInfoList()[mapNum].mapObject[0][next.y][next.x] == n)
			{
				return false;
			}
		}
		break;
	case Direction::RIGHT:
		for (auto n : MapInfoList::GetCannotThroughRight())
		{
			if (MapInfoList::GetMapInfoList()[mapNum].mapChip[next.y][next.x - 1] == n)
			{
				return false;
			}
		}
		for (auto n : MapInfoList::GetCannotThroughRightObject())
		{
			if (MapInfoList::GetMapInfoList()[mapNum].mapObject[0][next.y][next.x - 1] == n)
			{
				return false;
			}
		}
		for (auto n : MapInfoList::GetCannotThroughLeft())
		{
			if (MapInfoList::GetMapInfoList()[mapNum].mapChip[next.y][next.x] == n)
			{
				return false;
			}
		}
		for (auto n : MapInfoList::GetCannotThroughLeftObject())
		{
			if (MapInfoList::GetMapInfoList()[mapNum].mapObject[0][next.y][next.x] == n)
			{
				return false;
			}
		}
		break;
	case Direction::LEFT:
		for (auto n : MapInfoList::GetCannotThroughLeft())
		{
			if (MapInfoList::GetMapInfoList()[mapNum].mapChip[next.y][next.x + 1] == n)
			{
				return false;
			}
		}
		for (auto n : MapInfoList::GetCannotThroughLeftObject())
		{
			if (MapInfoList::GetMapInfoList()[mapNum].mapObject[0][next.y][next.x + 1] == n)
			{
				return false;
			}
		}
		for (auto n : MapInfoList::GetCannotThroughRight())
		{
			if (MapInfoList::GetMapInfoList()[mapNum].mapChip[next.y][next.x] == n)
			{
				return false;
			}
		}
		for (auto n : MapInfoList::GetCannotThroughRightObject())
		{
			if (MapInfoList::GetMapInfoList()[mapNum].mapObject[0][next.y][next.x] == n)
			{
				return false;
			}
		}
		break;
	}

	return true;
}

void BossMap::DrawAttackPoint()
{
	Function::Alpha(160);
	for (auto& pos : attackPointList)
	{
		Vector2<int> tempPos = pos*Define::MASU_SIZE;
		DrawFillBox(tempPos.x - camera.x, tempPos.y - camera.y, tempPos.x + Define::MASU_SIZE - camera.x, tempPos.y + Define::MASU_SIZE - camera.y, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::RED]);
	}
	Function::Alpha(255);
}

void BossMap::Draw()
{
	DrawRotaGraphF(position.x - camera.x, position.y - camera.y, 1.0, 0.0, graph[kind], TRUE);
}