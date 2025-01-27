#include "Application.h"
#include <DxLib.h>
#include "game.h"
#include "Input.h"
#include "SceneController.h"
#include "Time.h"
#include "SoundManager.h"
#include "SoundStore.h"
#include "Music.h"

#if _DEBUG
namespace
{
	// �R���\�[���p
	FILE* in = 0;
	FILE* out = 0;
}
#endif

Application::Application() :
	m_isRunning(true),
	m_frameCount(0)
{
}

void Application::GameLoop()
{
	Input& inputInstance = Input::GetInstance();
	SceneController& sceneController = SceneController::GetInstance();
	SoundManager& sound = SoundManager::GetInstance();

	// ��ʑS�̂��N���A����
	ClearDrawScreen();

	// �����ɃQ�[���̏���������

	// Input�N���X�̍X�V����
	inputInstance.Update();
	sound.Update();

	// SceneController�̏���
	sceneController.Update();
	sceneController.Draw();
}

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
	/*�R���\�[��Debug�p*/
#if _DEBUG
	AllocConsole();							// �R���\�[��
	freopen_s(&out, "CON", "w", stdout);	// stdout
	freopen_s(&in, "CON", "r", stdin);		// stdin
#endif

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

	return true;
}

void Application::Run()
{
	Time& timeInstance = Time::GetInstance();
	// ���[�h���Ă���
	SoundStore::GetInstance();

	// �Q�[�����[�v
	while (ProcessMessage() == 0)
	{
		// ����̃��[�v���n�܂������Ԃ��o���Ă���
		LONGLONG time = GetNowHiPerformanceCount();

		// Time�̍X�V
		timeInstance.Update();

		int playSpeed = 1;
		if (Input::GetInstance().IsPressed("Srow_Debug"))
		{
			playSpeed = 5;
		}

		// ����if�̓X���[�̏���
		if (!(Time::FrameCount() % playSpeed))
		{
			GameLoop();
		}

		// ��ʂ̐؂�ւ���҂�
		ScreenFlip();

		// 60FPS�ɌŒ�
		while (GetNowHiPerformanceCount() - time < Game::kMillisecondsPerFrame);

		// �����I�����Ă����烋�[�v�𔲂���
		if (!m_isRunning) break;
	}
}

void Application::Terminate()
{
	DxLib_End();				// �c�w���C�u�����g�p�̏I������

#if _DEBUG//�R���\�[��Debug�p
	fclose(out); fclose(in); FreeConsole();//�R���\�[�����
#endif
}
