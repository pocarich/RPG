#include"../header/BattleEffectP014.h"
#include"../header/PlayerMap.h"
#include"../header/EnemyMap.h"
#include"../header/ObjectMap.h"
#include"../header/BossMap.h"

const double BattleEffectP014::speed = 4.0;
const int BattleEffectP014::hitInterval = 8;
const int BattleEffectP014::existTime = 600;

BattleEffectP014::BattleEffectP014(PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<BattleEffectPtr>& battleEffectList, list<EnemyMapPtr>& enemyMapList, int sourceID, Vector2<int> masuPosition, Direction direction, Vector2<double>&camera, int& mapNum, Vector2<double>& playerPosition,int posKind,bool SPMAX) :BattleEffect(playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, ObjectType::PLAYER, sourceID, masuPosition, direction, camera, mapNum, TargetType::ENEMY), playerPosition(playerPosition),SPMAX(SPMAX)
{
	switch (posKind)
	{
	case 0:
		this->masuPosition += Vector2<int>(1, 1);
		offset = Vector2<double>(Define::MASU_SIZE, Define::MASU_SIZE);
		posNum = 4;
		break;
	case 1:
		this->masuPosition -= Vector2<int>(1, 1);
		posNum = 0;
		offset = Vector2<double>(-Define::MASU_SIZE, -Define::MASU_SIZE);
		break;
	default:
		assert(0 && "BattleEffectP014::BattleEffectP014()");
		break;
	}
}

BattleEffectP014::~BattleEffectP014()
{

}

void BattleEffectP014::Update()
{
	effectTimer++;

	switch (posNum % 8)
	{
	case 0:
		offset.y+=speed;
		break;
	case 1:
		offset.y += speed;
		break;
	case 2:
		offset.x += speed;
		break;
	case 3:
		offset.x += speed;
		break;
	case 4:
		offset.y -= speed;
		break;
	case 5:
		offset.y -= speed;
		break;
	case 6:
		offset.x -= speed;
		break;
	case 7:
		offset.x -= speed;
		break;
	}

	if (effectTimer % (Define::MASU_SIZE / (int)speed) == 0)
	{
		posNum++;
	}
	if (effectTimer %hitInterval == 1)
	{
		Vector2<double> tempPos = playerPosition + offset;
		for (auto& obj : enemyMapList)
		{
			if (abs(obj->GetPosition().x - tempPos.x) < ((double)Define::MASU_SIZE - 2.0) && abs(obj->GetPosition().y - tempPos.y) < ((double)Define::MASU_SIZE - 2.0))
			{
				obj->CauseByPlayer(sourceID, 14,SPMAX);
			}
		}
		for (auto& obj : bossMapList)
		{
			if (abs(obj->GetPosition().x - tempPos.x) < ((double)Define::MASU_SIZE*2 - 2.0) && abs(obj->GetPosition().y - tempPos.y) < ((double)Define::MASU_SIZE*2 - 2.0))
			{
				obj->CauseByPlayer(sourceID, 14,SPMAX);
			}
		}
		Vector2<int> tempMasuPos = Vector2<int>(tempPos.x / Define::MASU_SIZE, tempPos.y / Define::MASU_SIZE);
		for (auto& obj : objectMapList)
		{
			if (obj->GetCanDestroy() && tempMasuPos == obj->GetMasuPosition())
			{
				obj->CauseByPlayer(sourceID, 14,SPMAX);
			}
		}
	}
	if (effectTimer == existTime)
	{
		disappearFlag = true;
	}
}

void BattleEffectP014::Draw()
{
	static const int graphKind[] = { 1,2,3,4,5,6 };
	Vector2<double> tempPos = playerPosition + offset;
	DrawRotaGraphF((float)tempPos.x - camera.x, (float)tempPos.y - camera.y, 1.0, 0.0, graph[20][graphKind[effectTimer % 6]], TRUE);
}