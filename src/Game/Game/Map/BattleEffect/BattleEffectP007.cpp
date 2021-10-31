#include"../header/BattleEffectP007.h"
#include"../header/PlayerMap.h"
#include"../header/EnemyMap.h"
#include"../header/ObjectMap.h"
#include"../header/BossMap.h"

BattleEffectP007::BattleEffectP007(PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<BattleEffectPtr>& battleEffectList, list<EnemyMapPtr>& enemyMapList, int sourceID, Vector2<int> masuPosition, Direction direction, Vector2<double>&camera, int& mapNum,bool SPMAX) :BattleEffect(playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, ObjectType::PLAYER, sourceID, masuPosition, direction, camera, mapNum, TargetType::ENEMY),SPMAX(SPMAX)
{
	position = Vector2<double>(this->masuPosition.x*Define::MASU_SIZE + Define::MASU_SIZE / 2, this->masuPosition.y*Define::MASU_SIZE + Define::MASU_SIZE / 2);
}

BattleEffectP007::~BattleEffectP007()
{

}

void BattleEffectP007::Update()
{
	effectTimer++;
	if (effectTimer == 1)
	{
		for (auto& obj : enemyMapList)
		{
			if (abs(obj->GetPosition().x - position.x) <= Define::WINDOW_WIDTH / 2 && abs(obj->GetPosition().y - position.y) <= Define::WINDOW_HEIGHT / 2)
			{
				obj->CauseByPlayer(sourceID, 7,SPMAX);
			}
		}
		for (auto& obj : objectMapList)
		{
			Vector2<int> diff = masuPosition - obj->GetMasuPosition();
			if (obj->GetCanDestroy() && abs(diff.x)<=(Define::WINDOW_WIDTH/(2*Define::MASU_SIZE))&& abs(diff.y) <= (Define::WINDOW_HEIGHT / (2 * Define::MASU_SIZE)))
			{
				obj->CauseByPlayer(sourceID, 7,SPMAX);
			}
		}
		for (auto& obj : bossMapList)
		{
			if (abs(obj->GetPosition().x - position.x) <= Define::WINDOW_WIDTH / 2 && abs(obj->GetPosition().y - position.y) <= Define::WINDOW_HEIGHT / 2)
			{
				obj->CauseByPlayer(sourceID, 7,SPMAX);
			}
		}
	}
	if (effectTimer == 48)
	{
		disappearFlag = true;
	}
}

void BattleEffectP007::Draw()
{
	DrawRotaGraphF((float)position.x - camera.x, (float)position.y - camera.y, 1.0, 0.0, graph[12][(effectTimer / 3) % 16], TRUE);
}