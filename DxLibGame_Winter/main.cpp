#include <DxLib.h>
#include "Application.h"

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// Application�I�u�W�F�N�g�����s����
	Application& instance = Application::GetInstance();
	if (!instance.Init())
	{
		return -1;
	}
	instance.Run();
	instance.Exit();

	return 0;				// �\�t�g�̏I�� 
}