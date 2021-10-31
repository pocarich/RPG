
/*   キーボード入力の管理   */

#pragma once

#include"Define.h"
#include"ColorMgr.h"
#include"FontMgr.h"

class KeyBoard
{
	static char key[256];							//キー入力状態の格納
	static bool keyPushPre[256];					//キー入力更新前の入力状態を保存
	static bool keyPushOnce[256];					//キー入力状態の格納(長押し判定なし)
	static bool canUpdateKeyPushPre;				//keyPushPreの更新が可能か(初回key更新後true,初回更新前はkeyの初期化が行われていないため)
private:
	KeyBoard() {};
	KeyBoard(const KeyBoard&) {};
	KeyBoard& operator =(const KeyBoard&) {};

	static void UpdateKeyPushOnce();				//keyPushOnceの更新
	static void UpdateKeyPushPre();					//keyPushPreの更新
	static void UpdateKey();						//keyの更新
	static bool CheckKey(char);						//char->bool
public:
	static void Init();
	static void Update();							//キー入力更新関連の関数の統括
	static bool PushOnce(int);						//キー入力(非長押し)
	static bool Push(int);							//キー入力(長押し対応)
};