
/*   ���b�Z�[�W�E�B���h�E   */

#ifndef MESSAGEWINDOW_H
#define MESSAGEWINDOW_H

#include"../Header/Define.h"
#include"../Header/Window.h"

#define MOJI_MAX_X 38		//��s������̕\���\������
#define MOJI_MAX_Y 3		//�\���\�s��
#define NEXT_MOJI_TIME 1	//��������̃t���[����
#define DELAY_TIME 30

/*
	/:���s
	@:Z�҂�
	#:����
	$:��
	%:���O��\��
*/

class MessageWindow:public Window
{
	string name;
	vector<string> messageList;
	int timer;
	int delayTimer;
	int charNum;
	int strNum;
	bool pushEnterFlag;
	bool dispName;
private:
	void UpdateMessage();
	void UpdateTimer();

public:
	MessageWindow(string name, vector<string> messageList);
	MessageWindow(string name, string message);
	void Update()override;
	void Draw()override;
};

#endif