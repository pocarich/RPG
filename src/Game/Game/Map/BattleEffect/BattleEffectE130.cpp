#include"../header/BattleEffectE130.h"
#include"../header/PlayerMap.h"
#include"../header/EnemyMap.h"
#include"../header/Function.h"
#include"../header/ColorMgr.h"

BattleEffectE130::BattleEffectE130(BossStatus bossStatus, PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<BattleEffectPtr>& battleEffectList, list<EnemyMapPtr>& enemyMapList, int sourceID, Vector2<int> masuPosition, Direction direction, Vector2<double>&camera, int& mapNum) :BattleEffect(playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, ObjectType::PLAYER, sourceID, masuPosition, direction, camera, mapNum, TargetType::PLAYER), bossStatus(bossStatus)
{
	position = Vector2<double>(this->masuPosition.x*Define::MASU_SIZE + Define::MASU_SIZE / 2, this->masuPosition.y*Define::MASU_SIZE + Define::MASU_SIZE / 2);
	alpha = 0;
	fureaSize = 3.0;
}

BattleEffectE130::~BattleEffectE130()
{

}

void BattleEffectE130::Update()
{
	effectTimer++;
	if (effectTimer >= 600 && effectTimer % 5 == 0)
	{
		playerMap->CauseByBoss(bossStatus, direction, sourceID, 130);
	}
}

void BattleEffectE130::Draw()
{
	static const int graphKind[] = { 2,3,4,5 };
	if (effectTimer < 180)
	{
		double size = 0.75 + 0.25*sin(2 * M_PI / 10 * effectTimer);
		DrawRotaGraphF((float)position.x - camera.x, (float)position.y - camera.y - 64 , size, 0.0, graph[32][graphKind[(effectTimer / 3) % 4]], TRUE);
	}
	else if (effectTimer < 360)
	{
		double size = 1.6 + 0.4*sin(2 * M_PI / 10 * effectTimer);
		DrawRotaGraphF((float)position.x - camera.x, (float)position.y - camera.y - 96, size, 0.0, graph[32][graphKind[(effectTimer / 3) % 4]], TRUE);
	}
	else
	{
		double size = 2.5 + 0.5*sin(2 * M_PI / 10 * effectTimer);
		DrawRotaGraphF((float)position.x - camera.x, (float)position.y - camera.y - 128, size, 0.0, graph[32][graphKind[(effectTimer / 3) % 4]], TRUE);
	}
	if (effectTimer > 600)
	{
		fureaSize += 1;
		fureaSize = min(100, fureaSize);
		DrawRotaGraphF((float)position.x - camera.x, (float)position.y - camera.y - 128, fureaSize, 0.0, graph[32][graphKind[(effectTimer / 3) % 4]], TRUE);

		Function::Alpha(alpha);
		DrawFillBox(0, 0, Define::WINDOW_WIDTH, Define::WINDOW_HEIGHT, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE]);
		Function::Alpha(255);
		alpha += 3;
		alpha = max(0, alpha);
	}
}