#include "../header/SystemMgr.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow)
{
	SystemMgr* systemMgr = new SystemMgr();
	
	systemMgr->Loop();

	delete systemMgr;

	return 0;
}
