#include "Application.h"
#include <DxLib.h>
#include "game.h"
#include "Input.h"

Application& Application::GetInstance()
{
	// ������static�������Ă����Έ�����A
	// �A�v���P�[�V�����I�����܂ő��݂���͂�
	static Application instance;
	return instance;
}

// ���̃N���X��DxLib�̏�������������
bool Application::Init()
{
	// �t���X�N���[���łȂ��A�E�B���h�E���[�h�ŊJ���悤�ɂ���
	// �����������֐��̓E�B���h�E���J���O(DXLib_Init()�̑O)�ɏ������Ă����K�v������
	ChangeWindowMode(Game::kDefaultWindowMode);

	// ��ʂ̃T�C�Y��ύX����
	// ��O�����͐F�Ɏg������(�r�b�g)
	SetGraphMode(Game::kScreenWidth, Game::kScreenHeight, Game::kColorBitNum);

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return false;			// �G���[���N������false
	}

	// �`���𗠉�ʂɂ���
	SetDrawScreen(DX_SCREEN_BACK);

	// Input�N���X���C���X�^���X��
	// �Q�Ƃ�Ԃ��Ă������󂯎���ĂȂ����ǋ�����
	Input::GetInstance();

	return true;
}

void Application::Run()
{
	Input& inputInstance = Input::GetInstance();
	// �Q�[�����[�v
	while (ProcessMessage() == 0)
	{
		// ����̃��[�v���n�܂������Ԃ��o���Ă���
		LONGLONG time = GetNowHiPerformanceCount();

		// ��ʑS�̂��N���A����
		ClearDrawScreen();

		// �����ɃQ�[���̏���������

		// Input�N���X�̍X�V����
		inputInstance.Update();

		// Input�̃e�X�g
		if (inputInstance.IsTrigger(PAD_INPUT_1))
		{
			printfDx("Z�����ꂽ�u��");
		}

		// ��ʂ̐؂�ւ���҂�
		ScreenFlip();

		// 60FPS�ɌŒ�
		while (GetNowHiPerformanceCount() - time < 16667);
	}
}

void Application::Exit()
{
	DxLib_End();				// �c�w���C�u�����g�p�̏I������
}
