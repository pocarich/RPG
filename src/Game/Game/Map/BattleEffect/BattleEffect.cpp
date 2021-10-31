#include"../header/BattleEffect.h"
#include"../header/Function.h"
#include"../header/PlayerMap.h"
#include"../header/EnemyMap.h"
#include"../header/MapInfoList.h"
#include"../header/EventInfoList.h"
#include"../header/ObjectMap.h"

GHandle BattleEffect::graph[100][30];

BattleEffect::BattleEffect(PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<BattleEffectPtr>& battleEffectList, list<EnemyMapPtr>& enemyMapList, ObjectType sourceType, int sourceID, Vector2<int> masuPosition, Direction direction, Vector2<double>&camera, int& mapNum, TargetType targetType) :playerMap(playerMap), battleEffectList(battleEffectList), enemyMapList(enemyMapList), sourceID(sourceID), sourceType(sourceType), masuPosition(masuPosition), direction(direction), camera(camera), mapNum(mapNum), targetType(targetType), bossMapList(bossMapList), objectMapList(objectMapList)
{
	effectTimer = 0;
	disappearFlag = false;
	position = Vector2<double>(masuPosition.x*Define::MASU_SIZE + Define::MASU_SIZE / 2, masuPosition.y*Define::MASU_SIZE + Define::MASU_SIZE / 2);
}

BattleEffect::~BattleEffect()
{

}

void BattleEffect::Load()
{
	ifstream ifs;
	string str;

	vector<int> widthList;
	vector<int> heightList;
	vector<int> xList;
	vector<int> yList;

	ifs.open("data/csv/effect/EffectGraph.csv");
	assert(!ifs.fail() && "BattleEffect::Load()Ç…Çƒé∏îsÇµÇ‹ÇµÇΩÅB");

	while (getline(ifs, str))
	{
		int width;
		int height;
		int x;
		int y;

		auto element = Function::split(str, ',');
		assert(element.size() == 4 && "BattleEffect::Load()Ç…Çƒé∏îsÇµÇ‹ÇµÇΩÅB");
		for (int i = 0; i != element.size(); i++)
		{
			stringstream ss;
			ss << element[i];
			switch (i)
			{
			case 0:
				ss >> width;
				break;
			case 1:
				ss >> height;
				break;
			case 2:
				ss >> x;
				break;
			case 3:
				ss >> y;
				break;
			}
		}

		widthList.push_back(width);
		heightList.push_back(height);
		xList.push_back(x);
		yList.push_back(y);
	}

	ifs.close();

	for (int i = 0; i != widthList.size(); i++)
	{
		stringstream ss;
		ss << "data/graph/map/effect/effectGraph" << Function::NumToStringFillZero(i, 3) << ".png";
		int result = LoadDivGraph(ss.str().c_str(), xList[i] * yList[i], xList[i], yList[i], widthList[i], heightList[i], graph[i]);

		assert(result == 0 && "BattleEffect::Load()Ç…ÇƒâÊëúÇÃì«Ç›çûÇ›Ç…é∏îsÇµÇ‹ÇµÇΩ(1)ÅB");
	}
}

bool BattleEffect::CanMoveToNextPosition(Vector2<int> next,Direction nextDirection)
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
		if (!obj->GetCanDestroy()&&!obj->GetCanThrough()&&obj->GetMasuPosition() == next)
		{
			return false;
		}
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