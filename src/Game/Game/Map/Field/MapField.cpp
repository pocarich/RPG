#include"../header/MapField.h"
#include"../header/MapInfoList.h"
#include"../header/MapChangeInfoList.h"
#include"../header/Function.h"
#include"../header/EventInfoList.h"

GHandle MapField::mapBackChip[20 * 30];
GHandle MapField::mapObjectChip[20 * 20];
GHandle MapField::pointer;

MapField::MapField(PlayerMap* playerMap,int& mapNum, Vector2<double>& camera) :playerMap(playerMap),mapNum(mapNum), camera(camera)
{
	pointerCounter = 0;
	kirakiraCounter = 0;
}

MapField::~MapField()
{

}

void MapField::Load()
{
	int result = LoadDivGraph("data/graph/map/objectChip.png", 400, 20, 20, 32, 32, mapObjectChip);

	assert(result == 0 && "MapField::Load()‚É‚Ä‰æ‘œ‚Ì“Ç‚Ýž‚Ý‚ÉŽ¸”s‚µ‚Ü‚µ‚½B");

	result = LoadDivGraph("data/graph/map/haikeiChip.png", 600, 20, 30, 32, 32, mapBackChip);

	assert(result == 0 && "MapField::Load()‚É‚Ä‰æ‘œ‚Ì“Ç‚Ýž‚Ý‚ÉŽ¸”s‚µ‚Ü‚µ‚½B");

	pointer = LoadGraph("data/graph/map/pointer.png");
	assert(pointer != 0 && "MapField::Load()‚É‚Ä‰æ‘œ‚Ì“Ç‚Ýž‚Ý‚ÉŽ¸”s‚µ‚Ü‚µ‚½B");
}

void MapField::Update()
{
	UpdatePointerCounter();
}

void MapField::UpdatePointerCounter()
{
	pointerCounter++;
}

void MapField::Draw()
{
	static const double pointerRotateAngle[] = { M_PI,M_PI / 2 * 3,M_PI / 2,0.0 };

	int lengthY = Define::WINDOW_HEIGHT / Define::MASU_SIZE;
	int lengthX = Define::WINDOW_WIDTH / Define::MASU_SIZE;
	lengthX += 4;
	lengthY += 4;

	int startX = playerMap->GetMasuPosition().x - lengthX / 2;
	int startY = playerMap->GetMasuPosition().y - lengthY / 2;
	int endX= playerMap->GetMasuPosition().x + lengthX / 2;
	int endY= playerMap->GetMasuPosition().y + lengthY / 2;

	for (int i = startY; i < endY; i++)for (int j = startX; j < endX; j++)
	{
		if (0 <= i&&i < MapInfoList::GetMapInfoList()[mapNum].heightNum && 0 <= j&&j < MapInfoList::GetMapInfoList()[mapNum].widthNum)
		{
			DrawGraphF((float)Define::MASU_SIZE*j - camera.x, (float)Define::MASU_SIZE*i - camera.y, mapBackChip[MapInfoList::GetMapInfoList()[mapNum].mapChip[i][j]], TRUE);
		}
	}

	for (int i = startY; i < endY; i++)for (int j = startX; j < endX; j++)
	{
		if (0 <= i&&i < MapInfoList::GetMapInfoList()[mapNum].heightNum && 0 <= j&&j < MapInfoList::GetMapInfoList()[mapNum].widthNum)
		{
			DrawGraphF(Define::MASU_SIZE*j - camera.x, Define::MASU_SIZE*i - camera.y, mapObjectChip[MapInfoList::GetMapInfoList()[mapNum].mapObject[0][i][j]], TRUE);
		}
	}

	for (int i = startY; i < endY; i++)for (int j = startX; j < endX; j++)
	{
		if (0 <= i&&i < MapInfoList::GetMapInfoList()[mapNum].heightNum && 0 <= j&&j < MapInfoList::GetMapInfoList()[mapNum].widthNum)
		{
			DrawGraphF(Define::MASU_SIZE*j - camera.x, Define::MASU_SIZE*i - camera.y, mapObjectChip[MapInfoList::GetMapInfoList()[mapNum].mapObject[1][i][j]], TRUE);
		}
	}

	if (pointerCounter % 60 < 30)
	{
		Function::Alpha(180);
		for (int i = 0; i < MapInfoList::GetMapInfoList()[mapNum].heightNum; i++)for (int j = 0; j < MapInfoList::GetMapInfoList()[mapNum].widthNum; j++)
		{
			if (MapInfoList::GetMapInfoList()[mapNum].areaChange[i][j] != -1)
			{
				DrawRotaGraph(Define::MASU_SIZE*j - camera.x + Define::MASU_SIZE / 2, Define::MASU_SIZE*i - camera.y + Define::MASU_SIZE / 2, 0.8, pointerRotateAngle[(int)MapChangeInfoList::GetMapChangeInfoList()[MapInfoList::GetMapInfoList()[mapNum].areaChange[i][j]].direction], pointer, TRUE);
			}
		}
		Function::Alpha(255);
	}

	for (int i = startY; i < endY; i++)for (int j = startX; j < endX; j++)
	{
		if (0 <= i&&i < MapInfoList::GetMapInfoList()[mapNum].heightNum && 0 <= j&&j < MapInfoList::GetMapInfoList()[mapNum].widthNum)
		{
			if (MapInfoList::GetMapInfoList()[mapNum].event[i][j] == -1)
			{
				continue;
			}

			switch (EventInfoList::GetEventInfoList()[MapInfoList::GetMapInfoList()[mapNum].event[i][j]].graphKind)
			{
			case 0:
				DrawGraph(Define::MASU_SIZE*j - camera.x, Define::MASU_SIZE*i - camera.y, mapObjectChip[2 * 20 + 12], TRUE);
				break;
			case 1:
				DrawGraph(Define::MASU_SIZE*j - camera.x, Define::MASU_SIZE*i - camera.y, mapObjectChip[2 * 20 + 11], TRUE);
				break;
			case 2:
				DrawGraph(Define::MASU_SIZE*j - camera.x, Define::MASU_SIZE*i - camera.y, mapObjectChip[2 * 20 + 15 + (kirakiraCounter / 5) % 3], TRUE);
				break;
			case 3:
				DrawGraph(Define::MASU_SIZE*j - camera.x, Define::MASU_SIZE*i - camera.y, mapObjectChip[6 * 20 + 15], TRUE);
				break;
			}
		}
	}
	
	kirakiraCounter++;
}