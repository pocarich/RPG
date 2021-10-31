#include"../header/SystemMgr.h"
#include"../header/KeyBoard.h"
#include"../header/ColorMgr.h"
#include"../header/FontMgr.h"
#include"../header/SEMgr.h"
#include"../header/BGMMgr.h"

#include"../header/MapField.h"
#include"../header/PlayerMap.h"
#include"../header/MapInfoList.h"
#include"../header/MapChangeInfoList.h"
#include"../header/CharacterStatus.h"
#include"../header/BattleEffect.h"
#include"../header/EnemyMap.h"
#include"../header/EnemyStatus.h"
#include"../header/ItemInfoList.h"
#include"../header/MenuItem.h"
#include"../header/MenuSkill.h"
#include"../header/CharacterSkillInfoList.h"
#include"../header/UI.h"
#include"../header/MenuEquip.h"
#include"../header/PeopleInfoList.h"
#include"../header/PeopleMap.h"
#include"../header/EventInfoList.h"
#include"../header/ShopInfoList.h"
#include"../header/Shop.h"
#include"../header/INNInfoList.h"
#include"../header/MenuSynthesis.h"
#include"../header/MenuAchievement.h"
#include"../header/MenuSave.h"
#include"../header/MenuTitle.h"
#include"../header/MenuTop.h"
#include"../header/SynthesisInfoList.h"
#include"../header/AchieveInfoList.h"
#include"../header/DropItem.h"
#include"../header/EnemySkillInfoList.h"
#include"../header/ObjectMap.h"
#include"../header/BossMap.h"
#include"../header/BossStatus.h"
#include"../header/BossSpawnInfoList.h"
#include"../header/SpecialEventInfoList.h"
#include"../header/SpecialEvent.h"
#include"../header/Title.h"
#include"../header/TitleMapInfo.h"

SystemMgr::SystemMgr()
{
	SetMainWindowText("RPG");
	SetWindowSize(Define::WINDOW_WIDTH, Define::WINDOW_HEIGHT);
	ChangeWindowMode(TRUE);
	SetGraphMode(Define::WINDOW_WIDTH, Define::WINDOW_HEIGHT, 16);
	DxLib_Init();
	SetDrawScreen(DX_SCREEN_BACK);
	SetDrawMode(DX_DRAWMODE_BILINEAR);

	ColorMgr::Load();
	FontMgr::Load();
	SEMgr::Load();
	BGMMgr::Load();
	KeyBoard::Init();

	MapInfoList::Load();
	PlayerMap::Load();
	MapField::Load();
	MapChangeInfoList::Load();
	CharacterStatus::Load();
	BattleEffect::Load();
	EnemyMap::Load();
	EnemyStatus::Load();
	ItemInfoList::Load();
	MenuItem::Load();
	MenuSkill::Load();
	CharacterSkillInfoList::Load();
	UI::Load();
	MenuEquip::Load();
	PeopleInfoList::Load();
	PeopleMap::Load();
	EventInfoList::Load();
	ShopInfoList::Load();
	Shop::Load();
	INNInfoList::Load();
	MenuSynthesis::Load();
	MenuAchievement::Load();
	SynthesisInfoList::Load();
	AchieveInfoList::Load();
	DropItem::Load();
	EnemySkillInfoList::Load();
	ObjectMap::Load();
	BossStatus::Load();
	BossMap::Load();
	BossSpawnInfoList::Load();
	SpecialEventInfoList::Load();
	SpecialEvent::Load();
	MenuTitle::Load();
	MenuSave::Load();
	MenuTop::Load();
	Title::Load();
	TitleMapInfo::Load();

	gameMgr = new GameMgr();
	fpsMgr = new FPSMgr();
}

SystemMgr::~SystemMgr()
{
	DxLib_End();

	delete gameMgr;
	delete fpsMgr;
}

void SystemMgr::Loop()
{
	while (Process())
	{
		KeyBoard::Update();									   //キーボード入力の更新
		BGMMgr::Play();
		SEMgr::Play();
		gameMgr->Main();                                       //ゲームのメイン処理
		fpsMgr->Main();
	}
}

bool SystemMgr::Process()
{
	if (ScreenFlip())return false;								//裏画面を表画面にコピー
	if (ProcessMessage())return false;							//ウィンドウのメッセージ処理
	if (ClearDrawScreen())return false;							//裏画面のクリア
	return true;
}