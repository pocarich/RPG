#include"../header/KeyBoard.h"

char KeyBoard::key[256];					
bool KeyBoard::keyPushPre[256];					
bool KeyBoard::keyPushOnce[256];			
bool KeyBoard::canUpdateKeyPushPre;

void KeyBoard::Init()
{
	canUpdateKeyPushPre = false;
}

void KeyBoard::UpdateKey()                                              //�L�[���͏�Ԃ̍X�V
{
	if (canUpdateKeyPushPre)UpdateKeyPushPre();                         //key�ւ̕s���A�N�Z�X�h�~�̂��ߏ���̂ݍX�V���Ȃ�
	GetHitKeyStateAll(key);                                             //�L�[���͂̍X�V
	canUpdateKeyPushPre = true;                                         //���ڈȍ~��keyPushPre�̍X�V������
}

void KeyBoard::UpdateKeyPushPre()                                       //�L�[���͍X�V�O�̓��͏�Ԃ�ۑ�
{
	for (int i = 0; i < 256; i++)
	{
		keyPushPre[i] = CheckKey(key[i]);
	}
}

void KeyBoard::UpdateKeyPushOnce()                                      //�L�[���͏�Ԃ̍X�V(����������Ȃ�)
{
	for (int i = 0; i < 256; i++)
	{
		keyPushOnce[i] = !keyPushPre[i] && key[i] ? true : false;       //�L�[�������ꂽ�u�Ԃ̂�true
	}
}

void KeyBoard::Update()                                                 //�L�[���͍X�V�֘A�̊֐��̓���
{
	UpdateKey();
	UpdateKeyPushOnce();
}

bool KeyBoard::CheckKey(char key)										//char->bool�ɕϊ�
{
	return key ? true : false;
}

bool KeyBoard::PushOnce(int keyCode)									//�X�y�[�X�L�[��������Ă��邩
{
	return keyPushOnce[keyCode];
}

bool KeyBoard::Push(int keyCode)
{
	return CheckKey(key[keyCode]);
}