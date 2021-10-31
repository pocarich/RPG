
/*   メッセージウィンドウ   */

#ifndef MESSAGEWINDOW_H
#define MESSAGEWINDOW_H

#include"../Header/Define.h"
#include"../Header/Window.h"

#define MOJI_MAX_X 38		//一行当たりの表示可能文字数
#define MOJI_MAX_Y 3		//表示可能行数
#define NEXT_MOJI_TIME 1	//文字送りのフレーム数
#define DELAY_TIME 30

/*
	/:改行
	@:Z待ち
	#:文末
	$:間
	%:名前非表示
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