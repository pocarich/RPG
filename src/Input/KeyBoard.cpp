#include"../header/KeyBoard.h"

char KeyBoard::key[256];					
bool KeyBoard::keyPushPre[256];					
bool KeyBoard::keyPushOnce[256];			
bool KeyBoard::canUpdateKeyPushPre;

void KeyBoard::Init()
{
	canUpdateKeyPushPre = false;
}

void KeyBoard::UpdateKey()                                              //キー入力状態の更新
{
	if (canUpdateKeyPushPre)UpdateKeyPushPre();                         //keyへの不正アクセス防止のため初回のみ更新しない
	GetHitKeyStateAll(key);                                             //キー入力の更新
	canUpdateKeyPushPre = true;                                         //二回目以降はkeyPushPreの更新を許可
}

void KeyBoard::UpdateKeyPushPre()                                       //キー入力更新前の入力状態を保存
{
	for (int i = 0; i < 256; i++)
	{
		keyPushPre[i] = CheckKey(key[i]);
	}
}

void KeyBoard::UpdateKeyPushOnce()                                      //キー入力状態の更新(長押し判定なし)
{
	for (int i = 0; i < 256; i++)
	{
		keyPushOnce[i] = !keyPushPre[i] && key[i] ? true : false;       //キーが押された瞬間のみtrue
	}
}

void KeyBoard::Update()                                                 //キー入力更新関連の関数の統括
{
	UpdateKey();
	UpdateKeyPushOnce();
}

bool KeyBoard::CheckKey(char key)										//char->boolに変換
{
	return key ? true : false;
}

bool KeyBoard::PushOnce(int keyCode)									//スペースキーが押されているか
{
	return keyPushOnce[keyCode];
}

bool KeyBoard::Push(int keyCode)
{
	return CheckKey(key[keyCode]);
}