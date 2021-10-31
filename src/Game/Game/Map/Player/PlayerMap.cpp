#include"../header/PlayerMap.h"
#include"../header/KeyBoard.h"
#include"../header/MapInfoList.h"
#include"../header/MapChangeInfoList.h"
#include"../header/CharacterSkillInfoList.h"
#include"../header/EnemySkillInfoList.h"
#include"../header/EventInfoList.h"
#include"../header/DropItem.h"
#include"../header/ItemInfoList.h"
#include"../header/ObjectMap.h"
#include"../header/BossMap.h"
#include"../header/SpecialEventInfoList.h"
#include"../header/PeopleInfoList.h"
#include"../header/AchieveInfoList.h"

#include"../header/BattleEffectP100.h"
#include"../header/BattleEffectP101.h"
#include"../header/BattleEffectP001.h"
#include"../header/BattleEffectP002.h"
#include"../header/BattleEffectP003.h"
#include"../header/BattleEffectP004.h"
#include"../header/BattleEffectP005.h"
#include"../header/BattleEffectP006.h"
#include"../header/BattleEffectP007.h"
#include"../header/BattleEffectP008_1.h"
#include"../header/BattleEffectP009.h"
#include"../header/BattleEffectP010.h"
#include"../header/BattleEffectP011_1.h"
#include"../header/BattleEffectP012.h"
#include"../header/BattleEffectP013.h"
#include"../header/BattleEffectP014.h"
#include"../header/BattleEffectP015.h"
#include"../header/BattleEffectP016.h"
#include"../header/BattleEffectP017.h"
#include"../header/BattleEffectP023_1.h"
#include"../header/BattleEffectP024.h"
#include"../header/DamageTextPlayer.h"

GHandle PlayerMap::graph[Define::CHARACTER_NUM][(int)Direction::SIZE * 3];
GHandle PlayerMap::conditionErrorGraph[(int)ConditionError::SIZE];

PlayerMap::PlayerMap(PlayerData* playerData, SystemMessage* systemMessage, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<EnemyMapPtr>& enemyMapList, list<PeopleMapPtr>& peopleMapList, Vector2<double>& camera, list<BattleEffectPtr>& battleEffectList, list<DropItemPtr>& dropItemList, list<TextUIPtr>& textUIList, int& mapNum, array<SaveData, Define::SAVE_DATA_NUM>& saveDataList, int loadDataNum) :playerData(playerData), systemMessage(systemMessage), enemyMapList(enemyMapList), peopleMapList(peopleMapList), camera(camera), battleEffectList(battleEffectList), mapNum(mapNum), dropItemList(dropItemList), textUIList(textUIList), objectMapList(objectMapList), bossMapList(bossMapList)
{
	id = 0;
	deathFlag = false;
	masuPosition = Vector2<int>(24, 30);

	if (loadDataNum != -1)
	{
		id = saveDataList[loadDataNum].id;
		masuPosition = saveDataList[loadDataNum].masuPosition;
	}

	position = Vector2<double>(masuPosition.x*Define::MASU_SIZE + (double)Define::MASU_SIZE / 2, masuPosition.y*Define::MASU_SIZE + (double)Define::MASU_SIZE / 2);
	direction = Direction::DOWN;
	moveState = MoveState::STOP;

	guardEffect = nullptr;

	velocity = Vector2<double>(0.0, 0.0);
	moveTime = 0;
	moveEndTime = 0;

	mapChangeFlag = false;
	attackKind = -1;

	peopleNum = -1;
	eventNum = -1;
	specialEventNum = -1;

	stiffTimer = 0;

	knockBackFlag = false;
	knockBackTimer = 0;
	knockBackVelocity = Vector2<double>(0.0, 0.0);
	knockBackDirection = Direction::UP;

	dispConditionNum = -1;
	dispConditionTimer = 0;
	guardCounter = 0;
}

PlayerMap::~PlayerMap()
{

}

void PlayerMap::Load()
{
	for (int i = 0; i < Define::CHARACTER_NUM; i++)
	{
		stringstream ss;
		ss << "data/graph/character/player/player" << i << ".png";
		int result = LoadDivGraph(ss.str().c_str(), 12, 3, (int)Direction::SIZE, 32, 32, graph[i]);
		assert(result == 0 && "PlayerMap::Load()にて画像の読み込みに失敗しました。");
	}
	conditionErrorGraph[0] = LoadGraph("data/graph/ConditionError1.png");
	assert(conditionErrorGraph[0] != 0 && "PlayerMap::Load()");
	conditionErrorGraph[1] = LoadGraph("data/graph/ConditionError2.png");
	assert(conditionErrorGraph[1] != 0 && "PlayerMap::Load()");
	conditionErrorGraph[2] = LoadGraph("data/graph/ConditionError3.png");
	assert(conditionErrorGraph[2] != 0 && "PlayerMap::Load()");
}

void PlayerMap::Update()
{
	if (!deathFlag)
	{
		CheckDeath();
		if (knockBackFlag)
		{
			UpdateKnockBack();
		}
		else
		{
			UpdateMove();
			ChangeDirection();
			StartAttack();
			ChangeCharacter();
			Guard();
		}
		UpdateStiffTimer();
		UpdateConditionError();
		MapChangeEnter();
		HappenEvent();
		PickDropItem();
	}
	
	if (guardEffect != nullptr)
	{
		guardEffect->Update();
	}

	CheckAchieve();
}

void PlayerMap::CheckAchieve()
{
	for (int n : playerData->GetGetAchieve())
	{
		stringstream ss;
		ss << "業績「" << AchieveInfoList::GetAchieveInfoList()[n].name << "」を達成した";
		systemMessage->AddMessage(ss.str());
	}
	playerData->ResetGetAchieve();
}

void PlayerMap::UpdateConditionError()
{
	int damage = playerData->GetCharacterStatusList()[id]->GetHP();

	for (int i = 0; i < Define::CHARACTER_NUM; i++)
	{
		if (playerData->GetExistCharacterFlag()[i])
		{
			playerData->GetCharacterStatusList()[i]->UpdateConditionError();
			playerData->GetCharacterStatusList()[i]->UpdateConditionErrorTimer();
		}
	}

	damage -= playerData->GetCharacterStatusList()[id]->GetHP();

	if (damage > 0)
	{
		textUIList.push_back(make_shared<DamageTextPlayer>(camera, position, damage));
	}

	dispConditionTimer++;
	if (dispConditionTimer % 60 == 0)
	{
		int n = dispConditionNum;
		int init = n;
		if (init == -1)
		{
			init = 0;
		}
		n = (n + 1) % (int)ConditionError::SIZE;
		bool isConditionError = false;
		while (true)
		{
			if (playerData->GetCharacterStatusList()[id]->GetConditionError()[n])
			{
				isConditionError = true;
				dispConditionNum = n;
				break;
			}
			n = (n + 1) % (int)ConditionError::SIZE;
			if (n == init)
			{
				break;
			}
		}
		if (!isConditionError)
		{
			dispConditionNum = -1;
		}
	}
}

void PlayerMap::CheckDeath()
{
	if (playerData->GetCharacterStatusList()[id]->GetHP() == 0)
	{
		if (!playerData->GetExistCharacterFlag()[1])
		{
			deathFlag = true;
			return;
		}
		int n = (id + 1) % Define::CHARACTER_NUM;
		while (true)
		{
			if (playerData->GetCharacterStatusList()[n]->GetHP() != 0)
			{
				id = n;
				dispConditionNum = -1;
				dispConditionTimer = 0;
				break;
			}
			n = (n + 1) % Define::CHARACTER_NUM;
			if (n == id)
			{
				deathFlag = true;
				break;
			}
		}
	}
}

void PlayerMap::UpdateKnockBack()
{
	if (knockBackTimer % (Define::MASU_SIZE / Define::KNOCKBACK_VELOCITY) == 0)
	{
		Vector2<int> next;
		switch (knockBackDirection)
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
		if (CanMoveToNextPosition(next,knockBackDirection))
		{
			masuPosition = next;
		}
		else
		{
			knockBackFlag = false;
			knockBackTimer = 0;
			return;
		}
	}
	position += knockBackVelocity;
	knockBackTimer++;
	if (knockBackTimer == (Define::MASU_SIZE * 3 / Define::KNOCKBACK_VELOCITY))
	{
		knockBackFlag = false;
		knockBackTimer = 0;
	}
}

void PlayerMap::PickDropItem()
{
	if (moveState != MoveState::STOP)
	{
		return;
	}

	for (auto& obj : dropItemList)
	{
		if (obj->GetMasuPosition() == masuPosition)
		{
			for (auto& n : obj->GetItemList())
			{
				if (playerData->GetPlayerStatus()->GetHoldItemList()[n] == ItemInfoList::GetItemInfoList()[n].maxHoldNum)
				{
					stringstream ss;
					ss << ItemInfoList::GetItemInfoList()[n].name << "はこれ以上所持できない。";
					systemMessage->AddMessage(ss.str());
				}
				else
				{
					playerData->GetPlayerStatus()->AddItem(n);
					stringstream ss;
					ss << ItemInfoList::GetItemInfoList()[n].name << "を手に入れた。";
					systemMessage->AddMessage(ss.str());
				}
			}
			obj->Picked();
		}
	}
}

void PlayerMap::UpdateStiffTimer()
{
	stiffTimer--;
	stiffTimer = max(0, stiffTimer);
}

void PlayerMap::Guard()
{
	if (id != 0)
	{
		if (guardEffect != nullptr)
		{
			delete guardEffect;
			guardEffect = nullptr;
		}
		return;
	}

	if (moveState != MoveState::STOP || stiffTimer > 0)
	{
		return;
	}

	if (!playerData->GetCharacterStatusList()[id]->GetConditionError()[(int)ConditionError::SLEEP]&&((KeyBoard::Push(KEY_INPUT_A) && playerData->GetCharacterStatusList()[id]->GetSetSkill()[0] == 0) || (KeyBoard::Push(KEY_INPUT_S) && playerData->GetCharacterStatusList()[id]->GetSetSkill()[1] == 0) || (KeyBoard::Push(KEY_INPUT_D) && playerData->GetCharacterStatusList()[id]->GetSetSkill()[2] == 0)))
	{
		if (guardEffect == nullptr)
		{
			guardEffect = new BattleEffectP000(this, bossMapList,objectMapList,battleEffectList, enemyMapList, id, masuPosition, direction, camera, mapNum, position);
		}
		guardCounter++;
	}
	else
	{
		if (guardEffect != nullptr)
		{
			delete guardEffect;
			guardEffect = nullptr;
			guardCounter = 0;
		}
	}
}

void PlayerMap::ChangeDirection()
{
	if (!KeyBoard::Push(KEY_INPUT_LSHIFT) || moveState != MoveState::STOP|| playerData->GetCharacterStatusList()[id]->GetConditionError()[(int)ConditionError::SLEEP])
	{
		return;
	}
	if (KeyBoard::Push(KEY_INPUT_UP))
	{
		direction = Direction::UP;
	}
	else if (KeyBoard::Push(KEY_INPUT_RIGHT))
	{
		direction = Direction::RIGHT;
	}
	else if (KeyBoard::Push(KEY_INPUT_LEFT))
	{
		direction = Direction::LEFT;
	}
	else if (KeyBoard::Push(KEY_INPUT_DOWN))
	{
		direction = Direction::DOWN;
	}
}

void PlayerMap::ChangeCharacter()
{
	if (!playerData->GetExistCharacterFlag()[1])
	{
		return;
	}
	if (!playerData->GetCharacterStatusList()[id]->GetConditionError()[(int)ConditionError::SLEEP] && KeyBoard::PushOnce(KEY_INPUT_E))
	{
		int n = (id + 1) % Define::CHARACTER_NUM;
		while (true)
		{
			if (playerData->GetCharacterStatusList()[n]->GetHP() > 0)
			{
				id = n;
				dispConditionNum = -1;
				dispConditionTimer = 0;
				break;
			}
			n = (n + 1) % Define::CHARACTER_NUM;
			if (n == id)
			{
				break;
			}
		}
	}
}

void PlayerMap::HappenEvent()
{
	CheckEvent();
	ThroughOnEvent();
	TalkToPeople();
}

void PlayerMap::CheckEvent()
{
	if (KeyBoard::PushOnce(KEY_INPUT_Z))
	{
		Vector2<int> checkPosition = masuPosition;
		switch (direction)
		{
		case Direction::DOWN:
			checkPosition.y++;
			break;
		case Direction::LEFT:
			checkPosition.x--;
			break;
		case Direction::RIGHT:
			checkPosition.x++;
			break;
		case Direction::UP:
			checkPosition.y--;
			break;
		}

		int num = MapInfoList::GetMapInfoList()[mapNum].event[checkPosition.y][checkPosition.x];

		if (num != -1)
		{
			if (num == 57 && direction == Direction::LEFT)
			{
				eventNum = 60;
				specialEventNum = EventInfoList::GetEventInfoList()[eventNum].specialEventNum;
				MapInfoList::GetMapInfoList()[mapNum].event[checkPosition.y][checkPosition.x] = EventInfoList::GetEventInfoList()[eventNum].nextNum;
			}
			else
			{
				if (EventInfoList::GetEventInfoList()[num].type == EventInfo::EventType::CHECK && (EventInfoList::GetEventInfoList()[num].direction.size() == 0 || find(EventInfoList::GetEventInfoList()[num].direction.begin(), EventInfoList::GetEventInfoList()[num].direction.end(), (int)direction) != EventInfoList::GetEventInfoList()[num].direction.end()))
				{
					eventNum = num;
					specialEventNum = EventInfoList::GetEventInfoList()[num].specialEventNum;
					MapInfoList::GetMapInfoList()[mapNum].event[checkPosition.y][checkPosition.x] = EventInfoList::GetEventInfoList()[num].nextNum;
				}
			}
		}
	}
}

void PlayerMap::ThroughOnEvent()
{
	if (moveState != MoveState::STOP)
	{
		return;
	}
	int num = MapInfoList::GetMapInfoList()[mapNum].event[masuPosition.y][masuPosition.x];

	if (num != -1)
	{
		if (EventInfoList::GetEventInfoList()[num].type == EventInfo::EventType::ON)
		{
			eventNum = num;
			specialEventNum = EventInfoList::GetEventInfoList()[num].specialEventNum;
			MapInfoList::GetMapInfoList()[mapNum].event[masuPosition.y][masuPosition.x] = EventInfoList::GetEventInfoList()[num].nextNum;
			for (auto& n : EventInfoList::GetEventInfoList()[num].getItems)
			{
				if (n != -1)
				{
					playerData->GetPlayerStatus()->AddItem(n);
				}
			}
		}
	}
}

void PlayerMap::TalkToPeople()
{
	if (peopleNum != -1 || stiffTimer > 0)
	{
		return;
	}
	if (KeyBoard::PushOnce(KEY_INPUT_Z))
	{
		Vector2<int> talkPosition = masuPosition;
		switch (direction)
		{
		case Direction::DOWN:
			talkPosition.y++;
			break;
		case Direction::LEFT:
			talkPosition.x--;
			break;
		case Direction::RIGHT:
			talkPosition.x++;
			break;
		case Direction::UP:
			talkPosition.y--;
			break;
		}

		auto talkPeople = find_if(peopleMapList.begin(), peopleMapList.end(), [&](PeopleMapPtr& obj) {return obj->GetMasuPosition() == talkPosition; });
		if (talkPeople != peopleMapList.end())
		{
			peopleNum = (*talkPeople)->GetPeopleKind();
			specialEventNum= PeopleInfoList::GetPeopleInfoList()[peopleNum].specialEvent;
			(*talkPeople)->Turn(direction);
			(*talkPeople)->Talked();
		}
	}
}

void PlayerMap::MapChangeEnter()
{
	if (moveState != MoveState::STOP)
	{
		return;
	}

	if (MapInfoList::GetMapInfoList()[mapNum].areaChange[masuPosition.y][masuPosition.x] != -1)
	{
		mapChangeFlag = true;
	}
}

void PlayerMap::UpdateMove()
{
	switch (moveState)
	{
	case MoveState::STOP:
		StartMove();
		break;
	default:
		Move();
	}
}

void PlayerMap::StartMove()
{
	if (KeyBoard::Push(KEY_INPUT_LSHIFT) || guardEffect != nullptr || stiffTimer > 0 || playerData->GetCharacterStatusList()[id]->GetConditionError()[(int)ConditionError::SLEEP])
	{
		return;
	}

	bool input = false;

	if (KeyBoard::Push(KEY_INPUT_UP))
	{
		if (CanMoveToNextPosition(masuPosition + Vector2<int>(0, -1),Direction::UP))
		{
			velocity = Vector2<double>::UP;
			masuPosition.y--;
			input = true;
		}
		direction = Direction::UP;
	}
	else if (KeyBoard::Push(KEY_INPUT_RIGHT))
	{
		if (CanMoveToNextPosition(masuPosition + Vector2<int>(1, 0),Direction::RIGHT))
		{
			velocity = Vector2<double>::RIGHT;
			masuPosition.x++;
			input = true;
		}
		direction = Direction::RIGHT;
	}
	else if (KeyBoard::Push(KEY_INPUT_LEFT))
	{
		if (CanMoveToNextPosition(masuPosition + Vector2<int>(-1, 0),Direction::LEFT))
		{
			velocity = Vector2<double>::LEFT;
			masuPosition.x--;
			input = true;
		}
		direction = Direction::LEFT;
	}
	else if (KeyBoard::Push(KEY_INPUT_DOWN))
	{
		if (CanMoveToNextPosition(masuPosition + Vector2<int>(0, 1),Direction::DOWN))
		{
			velocity = Vector2<double>::DOWN;
			masuPosition.y++;
			input = true;
		}
		direction = Direction::DOWN;
	}

	if (!input || KeyBoard::Push(KEY_INPUT_LSHIFT))
	{
		return;
	}

	double moveSpeed = Define::moveSpeed;
	if (playerData->GetCharacterStatusList()[id]->GetConditionError()[(int)ConditionError::STAN])
	{
		moveSpeed /= 2;
	}
	for (int i = 0; i < 3; i++)
	{
		if (playerData->GetCharacterStatusList()[id]->GetAccessory()[i] != -1)
		{
			if (ItemInfoList::GetItemInfoList()[playerData->GetCharacterStatusList()[id]->GetAccessory()[i]].option[(int)ItemInfo::ItemOption::MOVE_SPEED_RATE]>0.0001)
			{
				moveSpeed *= ItemInfoList::GetItemInfoList()[playerData->GetCharacterStatusList()[id]->GetAccessory()[i]].option[(int)ItemInfo::ItemOption::MOVE_SPEED_RATE];
			}
		}
	}

	velocity *= moveSpeed;
	moveEndTime = (int)((double)Define::MASU_SIZE / moveSpeed);
	moveState = MoveState::WALK;
}

bool PlayerMap::CanMoveToNextPosition(Vector2<int> nextPosition,Direction nextDirection)
{
	if (!MapInfoList::GetMapInfoList()[mapNum].canThrough[nextPosition.y][nextPosition.x])
	{
		return false;
	}

	if (MapInfoList::GetMapInfoList()[mapNum].event[nextPosition.y][nextPosition.x] != -1)
	{
		if (!EventInfoList::GetEventInfoList()[MapInfoList::GetMapInfoList()[mapNum].event[nextPosition.y][nextPosition.x]].canThrough)
		{
			return false;
		}
	}

	for (auto& obj : objectMapList)
	{
		if (!obj->GetCanThrough() && obj->GetMasuPosition() == nextPosition)
		{
			return false;
		}
	}

	if (find_if(bossMapList.begin(), bossMapList.end(), [&](BossMapPtr& obj) {return count_if(obj->GetMasuPosition().begin(), obj->GetMasuPosition().end(), [&](const Vector2<int>& pos) {return pos == nextPosition; }) > 0; }) != bossMapList.end())
	{
		return false;
	}

	if (find_if(enemyMapList.begin(), enemyMapList.end(), [&](EnemyMapPtr& obj) {return obj->GetMasuPosition() == nextPosition; }) != enemyMapList.end())
	{
		return false;
	}

	if (find_if(peopleMapList.begin(), peopleMapList.end(), [&](PeopleMapPtr& obj) {return obj->GetMasuPosition() == nextPosition; }) != peopleMapList.end())
	{
		return false;
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

void PlayerMap::Move()
{
	position += velocity;

	moveTime++;
	if (moveTime == moveEndTime)
	{
		moveTime = 0;
		moveState = MoveState::STOP;
		position = Vector2<double>((double)masuPosition.x, (double)masuPosition.y)*(double)Define::MASU_SIZE + Vector2<double>((double)Define::MASU_SIZE / 2, (double)Define::MASU_SIZE / 2);
	}
}

void PlayerMap::StartAttack()
{
	if (guardEffect != nullptr || stiffTimer > 0|| playerData->GetCharacterStatusList()[id]->GetConditionError()[(int)ConditionError::SLEEP])
	{
		return;
	}

	if (attackKind == -1)
	{
		if (KeyBoard::PushOnce(KEY_INPUT_W))
		{
			switch (id)
			{
			case 0:
				attackKind = 100;
				break;
			case 1:
				attackKind = 101;
				break;
			}
		}
		else if (KeyBoard::PushOnce(KEY_INPUT_A))
		{
			if (playerData->GetCharacterStatusList()[id]->GetSetSkill()[0] != -1)
			{
				if (playerData->GetCharacterStatusList()[id]->GetSP() >= CharacterSkillInfoList::GetCharacterSkillInfoList()[playerData->GetCharacterStatusList()[id]->GetSetSkill()[0]].paySP[playerData->GetCharacterStatusList()[id]->GetSkillLevel()[playerData->GetCharacterStatusList()[id]->GetSetSkill()[0]] - 1])
				{
					attackKind = playerData->GetCharacterStatusList()[id]->GetSetSkill()[0];
				}
			}
		}
		else if (KeyBoard::PushOnce(KEY_INPUT_S))
		{
			if (playerData->GetCharacterStatusList()[id]->GetSetSkill()[1] != -1)
			{
				if (playerData->GetCharacterStatusList()[id]->GetSP() >= CharacterSkillInfoList::GetCharacterSkillInfoList()[playerData->GetCharacterStatusList()[id]->GetSetSkill()[1]].paySP[playerData->GetCharacterStatusList()[id]->GetSkillLevel()[playerData->GetCharacterStatusList()[id]->GetSetSkill()[1]] - 1])
				{
					attackKind = playerData->GetCharacterStatusList()[id]->GetSetSkill()[1];
				}
			}
		}
		else if (KeyBoard::PushOnce(KEY_INPUT_D))
		{
			if (playerData->GetCharacterStatusList()[id]->GetSetSkill()[2] != -1)
			{
				if (playerData->GetCharacterStatusList()[id]->GetSP() >= CharacterSkillInfoList::GetCharacterSkillInfoList()[playerData->GetCharacterStatusList()[id]->GetSetSkill()[2]].paySP[playerData->GetCharacterStatusList()[id]->GetSkillLevel()[playerData->GetCharacterStatusList()[id]->GetSetSkill()[2]] - 1])
				{
					attackKind = playerData->GetCharacterStatusList()[id]->GetSetSkill()[2];
				}
			}
		}
	}

	if (moveState != MoveState::STOP)
	{
		return;
	}

	if (attackKind!=-1)
	{
		Attack();
	}
}

void PlayerMap::Draw()
{
	if (!deathFlag)
	{
		int animationFrame;
		if (moveState == MoveState::WALK || moveState == MoveState::DASH)
		{
			animationFrame = ((moveTime + 8) / 4) % 3;
		}
		else
		{
			animationFrame = 1;
		}
		DrawRotaGraphF(Define::WINDOW_WIDTH / 2.0, Define::WINDOW_HEIGHT / 2.0, 1.0, 0.0, graph[id][(int)direction * 3 + animationFrame], TRUE);
	}
	else
	{
		DrawRotaGraphF(Define::WINDOW_WIDTH / 2.0, Define::WINDOW_HEIGHT / 2.0, 1.0, -M_PI / 2, graph[id][(int)Direction::RIGHT * 3 + 1], TRUE);
	}

	if (dispConditionNum != -1)
	{
		if (dispConditionTimer % 60 < 30)
		{
			DrawRotaGraph(Define::WINDOW_WIDTH / 2.0 + 16, Define::WINDOW_HEIGHT / 2.0 - 16, 0.7, 0.0, conditionErrorGraph[dispConditionNum], TRUE);
		}
	}

	if (guardEffect != nullptr)
	{
		guardEffect->Draw();
	}
}

void PlayerMap::MapChange()
{
	int areaChangeNum = MapInfoList::GetMapInfoList()[mapNum].areaChange[masuPosition.y][masuPosition.x];
	mapNum = MapChangeInfoList::GetMapChangeInfoList()[areaChangeNum].nextMapNum;
	masuPosition.x = MapChangeInfoList::GetMapChangeInfoList()[areaChangeNum].nextX;
	masuPosition.y = MapChangeInfoList::GetMapChangeInfoList()[areaChangeNum].nextY;
	position = Vector2<double>((double)masuPosition.x, (double)masuPosition.y)*(double)Define::MASU_SIZE + Vector2<double>((double)Define::MASU_SIZE / 2, (double)Define::MASU_SIZE / 2);
	direction = MapChangeInfoList::GetMapChangeInfoList()[areaChangeNum].nextDirection;
}

void PlayerMap::ResetEvent()
{
	peopleNum = -1;
	eventNum = -1;
	specialEventNum = -1;
}

void PlayerMap::ResetSpecialEvent()
{
	if (!((Define::EVENT_SHOP_START <= specialEventNum&& specialEventNum <= Define::EVENT_SHOP_END) || (Define::EVENT_INN_START <= specialEventNum&& specialEventNum <= Define::EVENT_INN_END)))
	{
		masuPosition = SpecialEventInfoList::GetSpecialEventInfoList()[specialEventNum].masuPosition;
		position = Vector2<double>(masuPosition.x*Define::MASU_SIZE + (double)Define::MASU_SIZE / 2, masuPosition.y*Define::MASU_SIZE + (double)Define::MASU_SIZE / 2);
		direction = Direction::DOWN;
		moveState = MoveState::STOP;
	}

	velocity = Vector2<double>(0.0, 0.0);
	moveTime = 0;
	moveEndTime = 0;
}

void PlayerMap::Attack()
{
	bool attackedFlag = true;
	switch (attackKind)
	{
	case 1:
		battleEffectList.push_back(make_shared<BattleEffectP001>(this, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition, direction, camera, mapNum, playerData->GetCharacterStatusList()[id]->GetSP() == playerData->GetCharacterStatusList()[id]->GetMAX_SP()));
		break;
	case 2:
		battleEffectList.push_back(make_shared<BattleEffectP002>(this, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition, direction, camera, mapNum, playerData->GetCharacterStatusList()[id]->GetSP() == playerData->GetCharacterStatusList()[id]->GetMAX_SP()));
		break;
	case 3:
		battleEffectList.push_back(make_shared<BattleEffectP003>(this, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition, direction, camera, mapNum, playerData->GetCharacterStatusList()[id]->GetSP() == playerData->GetCharacterStatusList()[id]->GetMAX_SP()));
		break;
	case 4:
		battleEffectList.push_back(make_shared<BattleEffectP004>(this, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition, direction, camera, mapNum, playerData->GetCharacterStatusList()[id]->GetSP() == playerData->GetCharacterStatusList()[id]->GetMAX_SP()));
		break;
	case 5:
		battleEffectList.push_back(make_shared<BattleEffectP005>(this, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition, direction, camera, mapNum, playerData->GetCharacterStatusList()[id]->GetSP() == playerData->GetCharacterStatusList()[id]->GetMAX_SP()));
		break;
	case 6:
		battleEffectList.push_back(make_shared<BattleEffectP006>(this, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition, direction, camera, mapNum, playerData->GetCharacterStatusList()[id]->GetSP() == playerData->GetCharacterStatusList()[id]->GetMAX_SP()));
		break;
	case 7:
		battleEffectList.push_back(make_shared<BattleEffectP007>(this, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition, direction, camera, mapNum, playerData->GetCharacterStatusList()[id]->GetSP() == playerData->GetCharacterStatusList()[id]->GetMAX_SP()));
		break;
	case 8:
		battleEffectList.push_back(make_shared<BattleEffectP008_1>(this, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition, direction, camera, mapNum, playerData->GetCharacterStatusList()[id]->GetSP() == playerData->GetCharacterStatusList()[id]->GetMAX_SP()));
		break;
	case 9:
		battleEffectList.push_back(make_shared<BattleEffectP009>(this, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition, direction, camera, mapNum, playerData->GetCharacterStatusList()[id]->GetSP() == playerData->GetCharacterStatusList()[id]->GetMAX_SP()));
		break;
	case 10:
		battleEffectList.push_back(make_shared<BattleEffectP010>(this, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition, direction, camera, mapNum, playerData->GetCharacterStatusList()[id]->GetSP() == playerData->GetCharacterStatusList()[id]->GetMAX_SP()));
		break;
	case 11:
		battleEffectList.push_back(make_shared<BattleEffectP011_1>(this, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition, direction, camera, mapNum, playerData->GetCharacterStatusList()[id]->GetSP() == playerData->GetCharacterStatusList()[id]->GetMAX_SP()));
		break;
	case 12:
		battleEffectList.push_back(make_shared<BattleEffectP012>(this, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition, direction, camera, mapNum, playerData->GetCharacterStatusList()[id]->GetSP() == playerData->GetCharacterStatusList()[id]->GetMAX_SP()));
		break;
	case 13:
		battleEffectList.push_back(make_shared<BattleEffectP013>(this, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition, direction, camera, mapNum, playerData->GetCharacterStatusList()[id]->GetSP() == playerData->GetCharacterStatusList()[id]->GetMAX_SP()));
		break;
	case 14:
		if (count_if(battleEffectList.begin(), battleEffectList.end(), [&](BattleEffectPtr& obj) {return typeid(*obj) == typeid(BattleEffectP014); }) < Define::WIND_MAX)
		{
			battleEffectList.push_back(make_shared<BattleEffectP014>(this, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition, direction, camera, mapNum, position, 0, playerData->GetCharacterStatusList()[id]->GetSP() == playerData->GetCharacterStatusList()[id]->GetMAX_SP()));
			battleEffectList.push_back(make_shared<BattleEffectP014>(this, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition, direction, camera, mapNum, position, 1, playerData->GetCharacterStatusList()[id]->GetSP() == playerData->GetCharacterStatusList()[id]->GetMAX_SP()));
		}
		else
		{
			attackedFlag = false;
		}
		break;
	case 15:
	{
		bool canCreate = true;

		switch (direction)
		{
		case Direction::DOWN:
			canCreate = MapInfoList::GetMapInfoList()[mapNum].canThrough[masuPosition.y + 1][masuPosition.x];
			break;
		case Direction::LEFT:
			canCreate = MapInfoList::GetMapInfoList()[mapNum].canThrough[masuPosition.y][masuPosition.x - 1];
			break;
		case Direction::RIGHT:
			canCreate = MapInfoList::GetMapInfoList()[mapNum].canThrough[masuPosition.y][masuPosition.x + 1];
			break;
		case Direction::UP:
			canCreate = MapInfoList::GetMapInfoList()[mapNum].canThrough[masuPosition.y - 1][masuPosition.x];
			break;
		}

		if (canCreate)
		{
			battleEffectList.push_back(make_shared<BattleEffectP015>(this, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition, direction, camera, mapNum, 0, playerData->GetCharacterStatusList()[id]->GetSP() == playerData->GetCharacterStatusList()[id]->GetMAX_SP()));
		}
		else
		{
			attackedFlag = false;
		}
	}
	break;
	case 16:
	{
		bool canCreate[3] = { true ,true,true };

		switch (direction)
		{
		case Direction::DOWN:
			canCreate[0] = MapInfoList::GetMapInfoList()[mapNum].canThrough[masuPosition.y + 1][masuPosition.x+1];
			canCreate[1] = MapInfoList::GetMapInfoList()[mapNum].canThrough[masuPosition.y + 1][masuPosition.x];
			canCreate[2] = MapInfoList::GetMapInfoList()[mapNum].canThrough[masuPosition.y + 1][masuPosition.x-1];
			break;
		case Direction::LEFT:
			canCreate[0] = MapInfoList::GetMapInfoList()[mapNum].canThrough[masuPosition.y+1][masuPosition.x - 1];
			canCreate[1] = MapInfoList::GetMapInfoList()[mapNum].canThrough[masuPosition.y][masuPosition.x - 1];
			canCreate[2] = MapInfoList::GetMapInfoList()[mapNum].canThrough[masuPosition.y-1][masuPosition.x - 1];
			break;
		case Direction::RIGHT:
			canCreate[0] = MapInfoList::GetMapInfoList()[mapNum].canThrough[masuPosition.y-1][masuPosition.x + 1];
			canCreate[1] = MapInfoList::GetMapInfoList()[mapNum].canThrough[masuPosition.y][masuPosition.x + 1];
			canCreate[2] = MapInfoList::GetMapInfoList()[mapNum].canThrough[masuPosition.y+1][masuPosition.x + 1];
			break;
		case Direction::UP:
			canCreate[0] = MapInfoList::GetMapInfoList()[mapNum].canThrough[masuPosition.y - 1][masuPosition.x-1];
			canCreate[1] = MapInfoList::GetMapInfoList()[mapNum].canThrough[masuPosition.y - 1][masuPosition.x];
			canCreate[2] = MapInfoList::GetMapInfoList()[mapNum].canThrough[masuPosition.y - 1][masuPosition.x+1];
			break;
		}

		bool create = false;

		for (int i = 0; i < 3; i++)
		{
			if (canCreate[i])
			{
				create = true;
				Vector2<int> offset = Vector2<int>(0, 0);

				switch (i)
				{
				case 0:
					switch (direction)
					{
					case Direction::DOWN:
						offset = Vector2<int>(1, 0);
						break;
					case Direction::LEFT:
						offset = Vector2<int>(0, 1);
						break;
					case Direction::RIGHT:
						offset = Vector2<int>(0, -1);
						break;
					case Direction::UP:
						offset = Vector2<int>(-1, 0);
						break;
					}
					break;
				case 1:
					break;
				case 2:
					switch (direction)
					{
					case Direction::DOWN:
						offset = Vector2<int>(-1, 0);
						break;
					case Direction::LEFT:
						offset = Vector2<int>(0, -1);
						break;
					case Direction::RIGHT:
						offset = Vector2<int>(0, 1);
						break;
					case Direction::UP:
						offset = Vector2<int>(1, 0);
						break;
					}
					break;
				}
				battleEffectList.push_back(make_shared<BattleEffectP016>(this, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition + offset , direction, camera, mapNum, 0, playerData->GetCharacterStatusList()[id]->GetSP() == playerData->GetCharacterStatusList()[id]->GetMAX_SP()));
			}
		}

		if(!create)
		{
			attackedFlag = false;
		}
	}
	break;
	case 17:
		if (count_if(battleEffectList.begin(), battleEffectList.end(), [&](BattleEffectPtr& obj) {return typeid(*obj) == typeid(BattleEffectP017); }) < Define::SPLASH_MAX)
		{
			battleEffectList.push_back(make_shared<BattleEffectP017>(this, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition, direction, camera, mapNum, playerData->GetCharacterStatusList()[id]->GetSP() == playerData->GetCharacterStatusList()[id]->GetMAX_SP()));
		}
		else
		{
			attackedFlag = false;
		}
		break;
	case 23:
	{
		bool canCreate = true;

		switch (direction)
		{
		case Direction::DOWN:
			canCreate = MapInfoList::GetMapInfoList()[mapNum].canThrough[masuPosition.y + 1][masuPosition.x];
			break;
		case Direction::LEFT:
			canCreate = MapInfoList::GetMapInfoList()[mapNum].canThrough[masuPosition.y][masuPosition.x - 1];
			break;
		case Direction::RIGHT:
			canCreate = MapInfoList::GetMapInfoList()[mapNum].canThrough[masuPosition.y][masuPosition.x + 1];
			break;
		case Direction::UP:
			canCreate = MapInfoList::GetMapInfoList()[mapNum].canThrough[masuPosition.y - 1][masuPosition.x];
			break;
		}

		if (canCreate)
		{
			battleEffectList.push_back(make_shared<BattleEffectP023_1>(this, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition, direction, camera, mapNum, playerData->GetCharacterStatusList()[id]->GetSP() == playerData->GetCharacterStatusList()[id]->GetMAX_SP()));
		}
		else
		{
			attackedFlag = false;
		}
	}
	break;
	case 24:
		battleEffectList.push_back(make_shared<BattleEffectP024>(this, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition, direction, camera, mapNum, playerData->GetCharacterStatusList()[id]->GetSP() == playerData->GetCharacterStatusList()[id]->GetMAX_SP()));
		break;
	case 100:
		battleEffectList.push_back(make_shared<BattleEffectP100>(this, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition, direction, camera, mapNum, playerData->GetCharacterStatusList()[id]->GetSP() == playerData->GetCharacterStatusList()[id]->GetMAX_SP()));
		break;
	case 101:
		battleEffectList.push_back(make_shared<BattleEffectP101>(this, bossMapList, objectMapList, battleEffectList, enemyMapList, id, masuPosition, direction, camera, mapNum, playerData->GetCharacterStatusList()[id]->GetSP() == playerData->GetCharacterStatusList()[id]->GetMAX_SP()));
		break;
	}

	if (attackedFlag)
	{
		switch (attackKind)
		{
		case 100:
			stiffTimer = Define::STIFF_TIME_ATTACK100;
			break;
		case 101:
			stiffTimer = Define::STIFF_TIME_ATTACK101;
			break;
		default:
			stiffTimer = CharacterSkillInfoList::GetCharacterSkillInfoList()[attackKind].stiff[playerData->GetCharacterStatusList()[id]->GetSkillLevel()[attackKind] - 1];
			playerData->GetCharacterStatusList()[id]->PaySP(attackKind);
			break;
		}
		stiffTimer -= playerData->GetCharacterStatusList()[id]->GetReduceStiff();
		stiffTimer = max(stiffTimer, 0);
		if (playerData->GetCharacterStatusList()[id]->GetConditionError()[(int)ConditionError::STAN])
		{
			stiffTimer *= 2;
		}
		if (playerData->GetCharacterStatusList()[id]->GetWeapon() != -1)
		{
			if (ItemInfoList::GetItemInfoList()[playerData->GetCharacterStatusList()[id]->GetWeapon()].option[(int)ItemInfo::ItemOption::REDUCE_STIFF_PERCENT] > 0.001)
			{
				stiffTimer *= ItemInfoList::GetItemInfoList()[playerData->GetCharacterStatusList()[id]->GetWeapon()].option[(int)ItemInfo::ItemOption::REDUCE_STIFF_PERCENT];
			}
		}
	}


	attackKind = -1;
}

void PlayerMap::CauseByEnemy(EnemyStatus enemyStatus, Direction attackDirection, int sourceID, int skillKind)
{
	int value;
	value = playerData->GetCharacterStatusList()[id]->CauseByEnemy(enemyStatus, sourceID, skillKind, stiffTimer > 0, guardEffect != nullptr,guardCounter);

	if (EnemySkillInfoList::GetEnemySkillInfoList()[skillKind].attribute[(int)EnemySkillAttribute::KNOCKBACK] == 1)
	{
		switch (attackDirection)
		{
		case Direction::DOWN:
			knockBackVelocity = Vector2<double>::DOWN*Define::KNOCKBACK_VELOCITY;
			break;
		case Direction::LEFT:
			knockBackVelocity = Vector2<double>::LEFT*Define::KNOCKBACK_VELOCITY;
			break;
		case Direction::RIGHT:
			knockBackVelocity = Vector2<double>::RIGHT*Define::KNOCKBACK_VELOCITY;
			break;
		case Direction::UP:
			knockBackVelocity = Vector2<double>::UP*Define::KNOCKBACK_VELOCITY;
			break;
		}

		knockBackFlag = true;
	}

	textUIList.push_back(make_shared<DamageTextPlayer>(camera, position, value));
}

void PlayerMap::CauseByBoss(BossStatus bossStatus, Direction attackDirection, int sourceID, int skillKind)
{
	int value;
	value = playerData->GetCharacterStatusList()[id]->CauseByBoss(bossStatus, sourceID, skillKind, stiffTimer > 0, guardEffect != nullptr, guardCounter);

	if (EnemySkillInfoList::GetEnemySkillInfoList()[skillKind].attribute[(int)EnemySkillAttribute::KNOCKBACK] == 1)
	{
		switch (attackDirection)
		{
		case Direction::DOWN:
			knockBackVelocity = Vector2<double>::DOWN*Define::KNOCKBACK_VELOCITY;
			break;
		case Direction::LEFT:
			knockBackVelocity = Vector2<double>::LEFT*Define::KNOCKBACK_VELOCITY;
			break;
		case Direction::RIGHT:
			knockBackVelocity = Vector2<double>::RIGHT*Define::KNOCKBACK_VELOCITY;
			break;
		case Direction::UP:
			knockBackVelocity = Vector2<double>::UP*Define::KNOCKBACK_VELOCITY;
			break;
		}

		knockBackFlag = true;
	}
	textUIList.push_back(make_shared<DamageTextPlayer>(camera, position, value));
}

void PlayerMap::Save(array<SaveData, Define::SAVE_DATA_NUM>& saveDataList, int saveDataNum)
{
	saveDataList[saveDataNum].id = id;
	saveDataList[saveDataNum].masuPosition = masuPosition;
}