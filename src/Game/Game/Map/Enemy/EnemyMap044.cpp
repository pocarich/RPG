#include"../header/EnemyMap044.h"
#include"../header/PlayerMap.h"
#include"../header/EnemySkillInfoList.h"

EnemyMap044::EnemyMap044(PlayerData* playerData, PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<EnemyMapPtr>& enemyMapList, list<PeopleMapPtr>& peopleMapList, int id, Vector2<int> masuPosition, Vector2<double>& camera, list<BattleEffectPtr>& battleEffectList, list<TextUIPtr>& textUIList, list<DropItemPtr>& dropItemList, int& mapNum) :EnemyMap(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, id, masuPosition, camera, battleEffectList, textUIList, dropItemList, mapNum)
{
	enemyStatus = new EnemyStatus(44);
	kind = 44;
	tempAttackKind = -1;
	deathTimer = 0;
}

EnemyMap044::~EnemyMap044()
{

}

void EnemyMap044::Update()
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
			if (!noticeFlag)
			{
				UpdateMoveUnnotice();
				Notice();
			}
			else
			{
				if (attackKind == -1)
				{
					UpdateNotice();
				}
				else
				{
					UpdateAttackTimer();
				}
			}
			break;
		default:
			Move();
			break;
		}
	}

	if (deathTimer < deathTime)
	{
		deathTimer++;
		if (deathTimer == deathTime)
		{
			noticeFlag = true;
			attackKind = 106;
			for (int i = -7; i < 8; i++)for (int j = -7; j < 8; j++)
			{
				if (Vector2<int>(i, j).length() <= 7)
				{
					attackPointList.push_back(masuPosition + Vector2<int>(i, j));
				}
			}
		}
	}
	if (deathTimer == deathTime&&attackKind == -1)
	{
		enemyStatus->Death();
		deathFlag = true;
	}
}

void EnemyMap044::UpdateNotice()
{
	if (stiffTimer > 0)
	{
		return;
	}

	if (tempAttackKind == -1)
	{
		UpdateTempAttackKind();
	}
	else
	{
		switch (tempAttackKind)
		{
		case 82:
		{
			Vector2<int> diff = playerMap->GetMasuPosition() - masuPosition;

			if (abs(masuPosition.x - playerMap->GetMasuPosition().x) + abs(masuPosition.y - playerMap->GetMasuPosition().y) <= 2)
			{
				attackKind = 82;
				tempAttackKind = -1;

				if (abs(diff.x) <= abs(diff.y))
				{
					if (diff.y < 0)
					{
						attackDirection = Direction::UP;

						Vector2<int> tempPos = masuPosition + Vector2<int>(0, -1);
						for (int i = -1; i < 2; i++)for (int j = -1; j < 2; j++)
						{
							attackPointList.push_back(tempPos + Vector2<int>(i, j));
						}
					}
					else
					{
						attackDirection = Direction::DOWN;
						Vector2<int> tempPos = masuPosition + Vector2<int>(0, 1);
						for (int i = -1; i < 2; i++)for (int j = -1; j < 2; j++)
						{
							attackPointList.push_back(tempPos + Vector2<int>(i, j));
						}
					}
				}
				else
				{
					if (diff.x > 0)
					{
						attackDirection = Direction::RIGHT;
						Vector2<int> tempPos = masuPosition + Vector2<int>(1, 0);
						for (int i = -1; i < 2; i++)for (int j = -1; j < 2; j++)
						{
							attackPointList.push_back(tempPos + Vector2<int>(i, j));
						}
					}
					else
					{
						attackDirection = Direction::LEFT;
						Vector2<int> tempPos = masuPosition + Vector2<int>(-1, 0);
						for (int i = -1; i < 2; i++)for (int j = -1; j < 2; j++)
						{
							attackPointList.push_back(tempPos + Vector2<int>(i, j));
						}
					}
				}
			}
			else if (abs(diff.x) > 2 || abs(diff.y)>2)
			{
				StartMove(enemyStatus->GetMoveSpeedNotice(), StartMoveKind::CLOSE);
			}
			else
			{
				StartMove(enemyStatus->GetMoveSpeedNotice(), StartMoveKind::ALIGNMENT);
			}
		}
		break;
		case 83:
		{
			Vector2<int> diff = playerMap->GetMasuPosition() - masuPosition;
			if (diff.length() <= 7)
			{
				attackKind = 83;
				tempAttackKind = -1;
				attackPointList.push_back(playerMap->GetMasuPosition());
			}
			else
			{
				StartMove(enemyStatus->GetMoveSpeedNotice(), StartMoveKind::CLOSE);
			}
		}
		break;
		}

	}
}

void EnemyMap044::UpdateTempAttackKind()
{
	Vector2<int> diff = playerMap->GetMasuPosition() - masuPosition;

	if (diff.length() <= 4)
	{
		tempAttackKind = 82;
	}
	else
	{
		tempAttackKind = 83;
	}
}