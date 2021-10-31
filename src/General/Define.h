#pragma once

#include<Dxlib.h>
#include<fstream>
#include<sstream>
#include<memory>
#include<string>
#include<array>
#include<vector>
#include<list>
#include<unordered_map>
#include<unordered_set>
#include<map>
#include<typeinfo>
#include<assert.h>
#include<algorithm>
#include<numeric>
#include<functional>
#include<assert.h>
#include<cstdio>
#include<iostream>
#include<Windows.h>
#include<queue>
#include<set>
#include<iomanip>
#include<random>

#define _USE_MATH_DEFINES
#include<math.h>

#define STR(var) #var

using namespace std;

class Define
{
public:
	//system
	static const int FPS = 60;
	static const int WINDOW_WIDTH = 800;
	static const int WINDOW_HEIGHT = 600;
	static const int SAVE_DATA_NUM = 12;

	//playerStatus
	static const int PLAYER_SKILL_MAX = 100;
	static const int PLAYER_SKILL_LEVEL_MAX = 5;

	//data
	static const int ITEM_KIND = 160;
	static const int ITEM_ICON_KIND = 30;

	//eevnt
	static const int EVENT_SHOP_START = 1000;
	static const int EVENT_SHOP_END = 1009;
	static const int EVENT_INN_START = 1010;
	static const int EVENT_INN_END = 1019;

	//playerData
	static const int CHARACTER_NUM = 2;
	static const int MAX_LEVEL = 50;
	static const int FLAG_NUM = 1000;
	static const int RECIPE_NUM = 100;
	static const int ACHIEVE_NUM = 100;

	//map
	static const int MAP_WIDTH_MAX = 150;
	static const int MAP_HEIGHT_MAX = 150;
	static const int MASU_SIZE = 32;
	static const int ENEMY_POP_INTERVAL = 20;
	static const int ENEMY_POP_MIN_DISTANCE = 7;
	static const int ENEMY_POP_MAX_DISTANCE = 10;
	static const int ENEMY_COUNT_DISTANCE = 12;
	static const int ENEMY_DESPAWN_DISTANCE = 15;
	static const int ENEMY_MAX = 100;
	static const int ENEMY_REPOP_TIME = 1800;
	static const int EVENT_IN_TIME = 100;

	//player
	static const double moveSpeed;

	//enemy
	static const int ENEMY_KIND_NUM = 45;
	static const int SHOW_ENEMY_HP_TIME = 120;

	//boss
	static const int BOSS_KIND_NUM = 9;

	//people
	static const int PEOPLE_KIND_MAX = 31;
	static const int PEOPLE_MOVE_SPEED = 2;
	static const int PEOPLE_MOVE_INTERVAL = 120;
	static const int PEOPLE_MOVE_DISTANCE_FROM_DEFAULT_POSITION = 2;

	//attack
	static const int ATTRIBUTE_NUM = 5;
	static const int KNOCKBACK_VELOCITY = 8;

	//ui
	static const int messageShowTime = 180;

	//playerSkill
	static const int STIFF_TIME_ATTACK100 = 15;
	static const int STIFF_TIME_ATTACK101 = 25;
	static const int HEEL_SP_ATTACK100 = 2;
	static const int HEEL_SP_ATTACK101 = 4;
	static const int WIND_MAX = 2;
	static const int SPLASH_MAX = 1;
	static const double GUARD_REDUCE_RATE;
	static const int JUST_GUARD_TIME = 3;
	static const double NEED_GUARD_SP;

	//enemySkill
	static const int ENEMY_ATTACK_DELAY_TIME = 60;
	static const int ENEMY_SKILL_ATTRIBUTE_NUM = 5;

	//conditionError
	static const int POISON_TIME = 1800;
	static const int POISON_DAMAGE_INTERVAL = 360;
	static const double POISON_DAMAGE_RATE;
	static const int SLEEP_TIME = 600;
	static const int STAN_TIME = 600;
private:
	Define() {};
	Define(const Define&) {};
	Define& operator =(const Define&) {};
};

enum struct Direction
{
	DOWN,
	LEFT,
	RIGHT,
	UP,
	SIZE
};

enum struct MoveState
{
	STOP,
	WALK,
	DASH,
	SIZE
};

enum struct TargetType
{
	PLAYER,
	ENEMY
};

enum struct ObjectType
{
	PLAYER,
	ENEMY,
	PEOPLE
};

enum struct SkillType
{
	ATTACK,
	SUPPORT
};

enum struct PlayerSkillAttribute
{
	TYPE,
	KNOCKBACK
};

enum struct EnemySkillAttribute
{
	TYPE,
	KNOCKBACK
};

enum struct ConditionError
{
	POISON,
	SLEEP,
	STAN,
	SIZE
};

typedef int GHandle;
typedef int MHandle;
typedef int FHandle;
typedef int Color;
typedef int Font;

class MapObject;
typedef shared_ptr<MapObject> MapObjectPtr;
class PlayerMap;
typedef shared_ptr<PlayerMap> PlayerMapPtr;
class MonsterMap;
typedef shared_ptr<MonsterMap> MonsterMapPtr;
class BattleObject;
typedef shared_ptr<BattleObject> BattleObjectPtr;
class PlayerBattle;
typedef shared_ptr<PlayerBattle> PlayerBattlePtr;
class MonsterBattle;
typedef shared_ptr<MonsterBattle> MonsterBattlePtr;
class Window;
typedef shared_ptr<Window> WindowPtr;
class BattleEffect;
typedef shared_ptr<BattleEffect> BattleEffectPtr;
class EnemyMap;
typedef shared_ptr<EnemyMap> EnemyMapPtr;
class PeopleMap;
typedef shared_ptr<PeopleMap> PeopleMapPtr;
class TextUI;
typedef shared_ptr<TextUI> TextUIPtr;
class DropItem;
typedef shared_ptr<DropItem> DropItemPtr;
class BossMap;
typedef shared_ptr<BossMap> BossMapPtr;
class ObjectMap;
typedef shared_ptr<ObjectMap> ObjectMapPtr;