
/*   ウインドウ抽象クラス   */

#ifndef WINDOW_H
#define WINDOW_H

#include"../Header/Define.h"

class Window
{
protected:
	static GHandle windowGraph;
	bool endFlag;
public:
	Window();
	virtual ~Window(){}
	virtual void Update() = 0;
	virtual void Draw() = 0;
	bool GetEndFlag()const { return endFlag; }
	virtual const vector<int>& GetData()const;
};

#endif