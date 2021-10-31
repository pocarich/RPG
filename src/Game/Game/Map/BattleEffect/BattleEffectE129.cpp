#include"../header/BattleEffectE129.h"
#include"../header/PlayerMap.h"
#include"../header/EnemyMap.h"
#include"../header/Function.h"

BattleEffectE129::BattleEffectE129(BossStatus bossStatus, PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<BattleEffectPtr>& battleEffectList, list<EnemyMapPtr>& enemyMapList, int sourceID, Vector2<int> masuPosition, Direction direction, Vector2<double>&camera, int& mapNum) :BattleEffect(playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, ObjectType::PLAYER, sourceID, masuPosition, direction, camera, mapNum, TargetType::PLAYER), bossStatus(bossStatus)
{
	position = Vector2<double>(this->masuPosition.x*Define::MASU_SIZE + Define::MASU_SIZE / 2, this->masuPosition.y*Define::MASU_SIZE + Define::MASU_SIZE / 2);
	alpha = 255;
}

BattleEffectE129::~BattleEffectE129()
{

}

void BattleEffectE129::Update()
{
	effectTimer++;
	if (effectTimer == 25)
	{
		playerMap->CauseByBoss(bossStatus, direction, sourceID, 129);
	}
	if (effectTimer == 120)
	{
		disappearFlag = true;
	}
}

void BattleEffectE129::Draw()
{
	if (effectTimer < 70)
	{
		DrawRotaGraphF(Define::WINDOW_WIDTH / 2, Define::WINDOW_HEIGHT / 2, 1.0, 0.0, graph[77][(effectTimer / 5) % 14], TRUE);
	}
	else
	{
		Function::Alpha(alpha);
		DrawRotaGraphF(Define::WINDOW_WIDTH / 2, Define::WINDOW_HEIGHT / 2, 1.0, 0.0, graph[77][11], TRUE);
		Function::Alpha(255);
		alpha -= 5;
		alpha = max(0, alpha);
	}
}