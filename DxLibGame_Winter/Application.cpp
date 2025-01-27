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
	// コンソール用
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

	// 画面全体をクリアする
	ClearDrawScreen();

	// ここにゲームの処理を書く

	// Inputクラスの更新処理
	inputInstance.Update();
	sound.Update();

	// SceneControllerの処理
	sceneController.Update();
	sceneController.Draw();
}

Application& Application::GetInstance()
{
	// ここにstaticをおいておけば一つだけ、
	// アプリケーション終了時まで存在するはず
	static Application instance;
	return instance;
}

// このクラスでDxLibの処理を実装する
bool Application::Init()
{
	/*コンソールDebug用*/
#if _DEBUG
	AllocConsole();							// コンソール
	freopen_s(&out, "CON", "w", stdout);	// stdout
	freopen_s(&in, "CON", "r", stdin);		// stdin
#endif

	// フルスクリーンでなく、ウィンドウモードで開くようにする
	// こういった関数はウィンドウが開く前(DXLib_Init()の前)に処理しておく必要がある
	ChangeWindowMode(Game::kDefaultWindowMode);

	// 画面のサイズを変更する
	// 第三引数は色に使う情報量(ビット)
	SetGraphMode(Game::kScreenWidth, Game::kScreenHeight, Game::kColorBitNum);

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return false;			// エラーが起きたらfalse
	}

	// 描画先を裏画面にする
	SetDrawScreen(DX_SCREEN_BACK);

	return true;
}

void Application::Run()
{
	Time& timeInstance = Time::GetInstance();
	// ロードしておく
	SoundStore::GetInstance();

	// ゲームループ
	while (ProcessMessage() == 0)
	{
		// 今回のループが始まった時間を覚えておく
		LONGLONG time = GetNowHiPerformanceCount();

		// Timeの更新
		timeInstance.Update();

		int playSpeed = 1;
		if (Input::GetInstance().IsPressed("Srow_Debug"))
		{
			playSpeed = 5;
		}

		// このifはスローの処理
		if (!(Time::FrameCount() % playSpeed))
		{
			GameLoop();
		}

		// 画面の切り替わりを待つ
		ScreenFlip();

		// 60FPSに固定
		while (GetNowHiPerformanceCount() - time < Game::kMillisecondsPerFrame);

		// もし終了していたらループを抜ける
		if (!m_isRunning) break;
	}
}

void Application::Terminate()
{
	DxLib_End();				// ＤＸライブラリ使用の終了処理

#if _DEBUG//コンソールDebug用
	fclose(out); fclose(in); FreeConsole();//コンソール解放
#endif
}
