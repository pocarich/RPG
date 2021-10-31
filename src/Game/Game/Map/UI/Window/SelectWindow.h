
/*   選択ウィンドウ   */

#ifndef SELECTWINDOW_H
#define SELECTWINDOW_H

#include"../Header/Define.h"
#include"../Header/Window.h"

#define WINDOW_BASE_X 790
#define WINDOW_BASE_Y 490

class SelectWindow :public Window
{
public:
	enum struct Type
	{
		NORMAL, 
		NUM,
		ALPHABET 
	};
private:
	vector<int> dataList;
	vector<string> nameList;
	Type type;
	int dataPoint;
	int dataNum;				//横
	int koumokuNum;				//縦
	int windowLength;
	int windowHeight;
private:
	void Change();
public:
	SelectWindow(Type type_, int dataNum_, string name);	//種類、データの個数、選択肢の名前
	void Update()override;
	void Draw()override;
	const vector<int>& GetData()const override{ return dataList; }
};

#endif