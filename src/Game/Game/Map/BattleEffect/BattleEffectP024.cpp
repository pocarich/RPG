#include"../header/BattleEffectP024.h"
#include"../header/PlayerMap.h"
#include"../header/EnemyMap.h"
#include"../header/Function.h"
#include"../header/ObjectMap.h"
#include"../header/BossMap.h"

BattleEffectP024::BattleEffectP024(PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<BattleEffectPtr>& battleEffectList, list<EnemyMapPtr>& enemyMapList, int sourceID, Vector2<int> masuPosition, Direction direction, Vector2<double>&camera, int& mapNum, bool SPMAX) :BattleEffect(playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, ObjectType::PLAYER, sourceID, masuPosition, direction, camera, mapNum, TargetType::ENEMY),SPMAX(SPMAX)
{
	position = Vector2<double>(this->masuPosition.x*Define::MASU_SIZE + Define::MASU_SIZE / 2, this->masuPosition.y*Define::MASU_SIZE + Define::MASU_SIZE / 2);
	alpha = 255;
}

BattleEffectP024::~BattleEffectP024()
{

}

void BattleEffectP024::Update()
{
	effectTimer++;
	if (effectTimer == 41)
	{
		for (auto& obj : enemyMapList)
		{
			if (abs(obj->GetPosition().x - position.x) <= Define::WINDOW_WIDTH / 2 && abs(obj->GetPosition().y - position.y) <= Define::WINDOW_HEIGHT / 2)
			{
				obj->CauseByPlayer(sourceID, 24,SPMAX);
			}
		}
		for (auto& obj : objectMapList)
		{
			Vector2<int> diff = masuPosition - obj->GetMasuPosition();
			if (obj->GetCanDestroy() && abs(diff.x) <= (Define::WINDOW_WIDTH / (2 * Define::MASU_SIZE)) && abs(diff.y) <= (Define::WINDOW_HEIGHT / (2 * Define::MASU_SIZE)))
			{
				obj->CauseByPlayer(sourceID, 24,SPMAX);
			}
		}
		for (auto& obj : bossMapList)
		{
			if (abs(obj->GetPosition().x - position.x) <= Define::WINDOW_WIDTH / 2 && abs(obj->GetPosition().y - position.y) <= Define::WINDOW_HEIGHT / 2)
			{
				obj->CauseByPlayer(sourceID, 24,SPMAX);
			}
		}
	}
	if (effectTimer == 120)
	{
		disappearFlag = true;
	}
}

void BattleEffectP024::Draw()
{
	if (effectTimer < 70)
	{
		DrawRotaGraphF((float)position.x - camera.x, (float)position.y - camera.y, 1.0, 0.0, graph[26][(effectTimer / 5) % 14], TRUE);
	}
	else
	{
		Function::Alpha(alpha);
		DrawRotaGraphF((float)position.x - camera.x, (float)position.y - camera.y, 1.0, 0.0, graph[26][13], TRUE);
		Function::Alpha(255);
		alpha -= 5;
		alpha = max(0, alpha);
	}
}