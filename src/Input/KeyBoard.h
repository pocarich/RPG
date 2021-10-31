
/*   �L�[�{�[�h���͂̊Ǘ�   */

#pragma once

#include"Define.h"
#include"ColorMgr.h"
#include"FontMgr.h"

class KeyBoard
{
	static char key[256];							//�L�[���͏�Ԃ̊i�[
	static bool keyPushPre[256];					//�L�[���͍X�V�O�̓��͏�Ԃ�ۑ�
	static bool keyPushOnce[256];					//�L�[���͏�Ԃ̊i�[(����������Ȃ�)
	static bool canUpdateKeyPushPre;				//keyPushPre�̍X�V���\��(����key�X�V��true,����X�V�O��key�̏��������s���Ă��Ȃ�����)
private:
	KeyBoard() {};
	KeyBoard(const KeyBoard&) {};
	KeyBoard& operator =(const KeyBoard&) {};

	static void UpdateKeyPushOnce();				//keyPushOnce�̍X�V
	static void UpdateKeyPushPre();					//keyPushPre�̍X�V
	static void UpdateKey();						//key�̍X�V
	static bool CheckKey(char);						//char->bool
public:
	static void Init();
	static void Update();							//�L�[���͍X�V�֘A�̊֐��̓���
	static bool PushOnce(int);						//�L�[����(�񒷉���)
	static bool Push(int);							//�L�[����(�������Ή�)
};