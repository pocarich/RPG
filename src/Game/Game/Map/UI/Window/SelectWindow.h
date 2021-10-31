
/*   �I���E�B���h�E   */

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
	int dataNum;				//��
	int koumokuNum;				//�c
	int windowLength;
	int windowHeight;
private:
	void Change();
public:
	SelectWindow(Type type_, int dataNum_, string name);	//��ށA�f�[�^�̌��A�I�����̖��O
	void Update()override;
	void Draw()override;
	const vector<int>& GetData()const override{ return dataList; }
};

#endif