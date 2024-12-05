#include <DxLib.h>
#include "Application.h"

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// Applicationオブジェクトを実行する
	Application& instance = Application::GetInstance();
	if (!instance.Init())
	{
		return -1;
	}
	instance.Run();
	instance.Exit();

	return 0;				// ソフトの終了 
}