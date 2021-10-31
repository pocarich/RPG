#include"../header/BattleEffectE002.h"
#include"../header/PlayerMap.h"
#include"../header/EnemyMap.h"

const double BattleEffectE002::speed = 4.0;
const int BattleEffectE002::existTime = 56;

BattleEffectE002::BattleEffectE002(EnemyStatus enemyStatus, PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<BattleEffectPtr>& battleEffectList, list<EnemyMapPtr>& enemyMapList, int sourceID, Vector2<int> masuPosition, Direction direction, Vector2<double>&camera, int& mapNum) :BattleEffect(playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, ObjectType::ENEMY, sourceID, masuPosition, direction, camera, mapNum, TargetType::PLAYER),enemyStatus(enemyStatus)
{
	switch (direction)
	{
	case Direction::DOWN:
		velocity = Vector2<double>::DOWN*speed;
		break;
	case Direction::LEFT:
		velocity = Vector2<double>::LEFT*speed;
		break;
	case Direction::RIGHT:
		velocity = Vector2<double>::RIGHT*speed;
		break;
	case Direction::UP:
		velocity = Vector2<double>::UP*speed;
		break;
	}

	position = Vector2<double>(this->masuPosition.x*Define::MASU_SIZE + Define::MASU_SIZE / 2, this->masuPosition.y*Define::MASU_SIZE + Define::MASU_SIZE / 2);

}

BattleEffectE002::~BattleEffectE002()
{

}

void BattleEffectE002::Update()
{
	position += velocity;

	effectTimer++;

	if (effectTimer % (Define::MASU_SIZE / (int)speed) == 1)
	{
		Vector2<int> next;
		switch (direction)
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
		if (CanMoveToNextPosition(next,direction))
		{
			masuPosition = next;
		}
		else
		{
			disappearFlag = true;
			return;
		}
	}


	if (abs(playerMap->GetPosition().x - position.x) < ((double)Define::MASU_SIZE - 2.0) && abs(playerMap->GetPosition().y - position.y) < ((double)Define::MASU_SIZE - 2.0))
	{
		playerMap->CauseByEnemy(enemyStatus, direction, sourceID, 2);
		disappearFlag = true;
	}

	if (effectTimer == existTime)
	{
		disappearFlag = true;
	}
}

void BattleEffectE002::Draw()
{
	static const int graphKind[] = { 3,4,5,6 };
	DrawRotaGraphF((float)position.x - camera.x, (float)position.y - camera.y, 1.0, 0.0, graph[30][graphKind[(effectTimer / 3) % 4]], TRUE);
}