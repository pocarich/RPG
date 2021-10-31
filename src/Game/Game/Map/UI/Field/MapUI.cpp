#include"../header/MapUI.h"
#include"../header/MapInfoList.h"
#include"../header/ColorMgr.h"
#include"../header/Function.h"
#include"../header/BossMap.h"
#include"../header/DropItem.h"
#include"../header/ObjectMap.h"
#include"../header/EnemyMap.h"
#include"../header/PeopleMap.h"

MapUI::MapUI(PlayerMap* playerMap, list<EnemyMapPtr>& enemyMapList, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<PeopleMapPtr>& peopleMapList, list<DropItemPtr>& dropItemMapList, int& mapNum) :playerMap(playerMap), enemyMapList(enemyMapList), bossMapList(bossMapList),peopleMapList(peopleMapList),dropItemMapList(dropItemMapList),objectMapList(objectMapList),mapNum(mapNum)
{
	Cash();
}

MapUI::~MapUI()
{

}

void MapUI::Update()
{

}

void MapUI::Cash()
{
	for (int i = 0; i != cash.size(); i++)for (int j = 0; j != cash[i].size(); j++)
	{
		cash[i][j].clear();
	}
	for (int i = 0; i < MapInfoList::GetMapInfoList()[mapNum].heightNum; i++)for (int j = 0; j < MapInfoList::GetMapInfoList()[mapNum].widthNum; j++)
	{
		if (!MapInfoList::GetMapInfoList()[mapNum].areaChange[i][j])
		{
			cash[i][j].push_back(CashKind::CANNOT);
		}
		else
		{
			cash[i][j].push_back(CashKind::CAN);
			if (find(MapInfoList::GetCannotThroughUp().begin(), MapInfoList::GetCannotThroughUp().end(), MapInfoList::GetMapInfoList()[mapNum].mapChip[i][j]) != MapInfoList::GetCannotThroughUp().end() || find(MapInfoList::GetCannotThroughUpObject().begin(), MapInfoList::GetCannotThroughUpObject().end(), MapInfoList::GetMapInfoList()[mapNum].mapObject[0][i][j]) != MapInfoList::GetCannotThroughUpObject().end())
			{
				cash[i][j].push_back(CashKind::UP);
			}
			if (find(MapInfoList::GetCannotThroughRight().begin(), MapInfoList::GetCannotThroughRight().end(), MapInfoList::GetMapInfoList()[mapNum].mapChip[i][j]) != MapInfoList::GetCannotThroughRight().end() || find(MapInfoList::GetCannotThroughRightObject().begin(), MapInfoList::GetCannotThroughRightObject().end(), MapInfoList::GetMapInfoList()[mapNum].mapObject[0][i][j]) != MapInfoList::GetCannotThroughRightObject().end())
			{
				cash[i][j].push_back(CashKind::RIGHT);
			}
			if (find(MapInfoList::GetCannotThroughLeft().begin(), MapInfoList::GetCannotThroughLeft().end(), MapInfoList::GetMapInfoList()[mapNum].mapChip[i][j]) != MapInfoList::GetCannotThroughLeft().end() || find(MapInfoList::GetCannotThroughLeftObject().begin(), MapInfoList::GetCannotThroughLeftObject().end(), MapInfoList::GetMapInfoList()[mapNum].mapObject[0][i][j]) != MapInfoList::GetCannotThroughLeftObject().end())
			{
				cash[i][j].push_back(CashKind::LEFT);
			}
			if (find(MapInfoList::GetCannotThroughDown().begin(), MapInfoList::GetCannotThroughDown().end(), MapInfoList::GetMapInfoList()[mapNum].mapChip[i][j]) != MapInfoList::GetCannotThroughDown().end() || find(MapInfoList::GetCannotThroughDownObject().begin(), MapInfoList::GetCannotThroughDownObject().end(), MapInfoList::GetMapInfoList()[mapNum].mapObject[0][i][j]) != MapInfoList::GetCannotThroughDownObject().end())
			{
				cash[i][j].push_back(CashKind::DOWN);
			}
		}
	}
}

void MapUI::Draw()
{
	Function::Alpha(200);
	bool exist[31][31] = { false };

	{
		DrawFillBox(635 + 15 * 5, 10 + 15 * 5, 635 + 16 * 5, 10 + 16 * 5, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE]);
		exist[15][15] = true;
	}

	for (auto& obj : enemyMapList)
	{
		Vector2<int> offset = Vector2<int>(15, 15) + (obj->GetMasuPosition() - playerMap->GetMasuPosition());
		if (0 <= offset.x&&offset.x < 31 && 0 <= offset.y&&offset.y < 31)
		{
			DrawFillBox(635 + offset.x * 5, 10 + offset.y * 5, 635 + (offset.x + 1) * 5, 10 + (offset.y + 1) * 5, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::RED]);
			exist[offset.y][offset.x] = true;
		}
	}

	for (auto& obj : bossMapList)
	{
		Vector2<int> offset = Vector2<int>(15, 15) + (obj->GetMasuPosition().front() - playerMap->GetMasuPosition());
		if (0 <= offset.x&&offset.x < 31 && 0 <= offset.y&&offset.y < 31)
		{
			DrawFillBox(635 + offset.x * 5, 10 + offset.y * 5, 635 + (offset.x + 1) * 5, 10 + (offset.y + 1) * 5, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::PURPLE]);
			exist[offset.y][offset.x] = true;
		}
	}

	for (auto& obj : peopleMapList)
	{
		Vector2<int> offset = Vector2<int>(15, 15) + (obj->GetMasuPosition() - playerMap->GetMasuPosition());
		if (0 <= offset.x&&offset.x < 31 && 0 <= offset.y&&offset.y < 31)
		{
			DrawFillBox(635 + offset.x * 5, 10 + offset.y * 5, 635 + (offset.x + 1) * 5, 10 + (offset.y + 1) * 5, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::ORANGE]);
			exist[offset.y][offset.x] = true;
		}
	}

	for (auto& obj : objectMapList)
	{
		Vector2<int> offset = Vector2<int>(15, 15) + (obj->GetMasuPosition() - playerMap->GetMasuPosition());
		if (0 <= offset.x&&offset.x < 31 && 0 <= offset.y&&offset.y < 31)
		{
			if (obj->GetDispMiniMap() == 1)
			{
				DrawFillBox(635 + offset.x * 5, 10 + offset.y * 5, 635 + (offset.x + 1) * 5, 10 + (offset.y + 1) * 5, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::GRAY]);
			}
			else
			{
				DrawFillBox(635 + offset.x * 5, 10 + offset.y * 5, 635 + (offset.x + 1) * 5, 10 + (offset.y + 1) * 5, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::BLACK]);
			}
			exist[offset.y][offset.x] = true;
		}
	}

	for (auto& obj : dropItemMapList)
	{
		Vector2<int> offset = Vector2<int>(15, 15) + (obj->GetMasuPosition() - playerMap->GetMasuPosition());
		if (0 <= offset.x&&offset.x < 31 && 0 <= offset.y&&offset.y < 31)
		{
			DrawFillBox(635 + offset.x * 5, 10 + offset.y * 5, 635 + (offset.x + 1) * 5, 10 + (offset.y + 1) * 5, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::YELLOW]);
			exist[offset.y][offset.x] = true;
		}
	}

	for (int i = 0; i < 31; i++)for (int j = 0; j < 31; j++)
	{
		if (exist[i][j])
		{
			continue;
		}
		Vector2<int> position = Vector2<int>(playerMap->GetMasuPosition().x - 15 + j, playerMap->GetMasuPosition().y - 15 + i);
	
		if (!(0 <= position.x && position.x < MapInfoList::GetMapInfoList()[mapNum].widthNum && 0 <= position.y&&position.y < MapInfoList::GetMapInfoList()[mapNum].heightNum))
		{
			Function::Alpha(160);
			DrawFillBox(635 + j * 5, 10 + i * 5, 635 + (j + 1) * 5, 10 + (i + 1) * 5, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::BLACK]);
			Function::Alpha(255);
		}
		else if (MapInfoList::GetMapInfoList()[mapNum].areaChange[position.y][position.x] != -1)
		{
			Function::Alpha(200);
			DrawFillBox(635 + j * 5, 10 + i * 5, 635 + (j + 1) * 5, 10 + (i + 1) * 5, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::GREEN]);
			Function::Alpha(255);
		}
		else if (MapInfoList::GetMapInfoList()[mapNum].canThrough[position.y][position.x])
		{
			Function::Alpha(160);
			DrawFillBox(635 + j * 5, 10 + i * 5, 635 + (j + 1) * 5, 10 + (i + 1) * 5, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::LIGHTBLUE]);
			Function::Alpha(255);
			for (int k = 0; k != cash[position.y][position.x].size(); k++)
			{
				switch (cash[position.y][position.x][k])
				{
				case CashKind::UP:
					Function::Alpha(160);
					DrawFillBox(635 + j * 5, 10 + i * 5, 635 + (j + 1) * 5, 11 + i * 5, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::BLACK]);
					Function::Alpha(255);
					break;
				case CashKind::RIGHT:
					Function::Alpha(160);
					DrawFillBox(639 + j * 5, 10 + i * 5, 635 + (j + 1) * 5, 10 + (i + 1) * 5, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::BLACK]);
					Function::Alpha(255);
					break;
				case CashKind::LEFT:
					Function::Alpha(160);
					DrawFillBox(635 + j * 5, 10 + i * 5, 636 + j * 5, 10 + (i + 1) * 5, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::BLACK]);
					Function::Alpha(255);
					break;
				case CashKind::DOWN:
					Function::Alpha(160);
					DrawFillBox(635 + j * 5, 14 + i * 5, 635 + (j + 1) * 5, 10 + (i + 1) * 5, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::BLACK]);
					Function::Alpha(255);
					break;
				}
			}
		}
		else
		{
			Function::Alpha(160);
			DrawFillBox(635 + j * 5, 10 + i * 5, 635 + (j + 1) * 5, 10 + (i + 1) * 5, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::BLACK]);
			Function::Alpha(255);
		}
	}
	Function::Alpha(255);

}