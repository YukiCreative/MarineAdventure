#include "Application.h"
#include <DxLib.h>
#include "game.h"
#include "Input.h"

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

	// Inputクラスをインスタンス化
	// 参照を返しているやつを受け取ってないけど許して
	Input::GetInstance();

	return true;
}

void Application::Run()
{
	Input& inputInstance = Input::GetInstance();
	// ゲームループ
	while (ProcessMessage() == 0)
	{
		// 今回のループが始まった時間を覚えておく
		LONGLONG time = GetNowHiPerformanceCount();

		// 画面全体をクリアする
		ClearDrawScreen();

		// ここにゲームの処理を書く

		// Inputクラスの更新処理
		inputInstance.Update();

		// Inputのテスト
		if (inputInstance.IsTrigger(PAD_INPUT_1))
		{
			printfDx("Z押された瞬間");
		}

		// 画面の切り替わりを待つ
		ScreenFlip();

		// 60FPSに固定
		while (GetNowHiPerformanceCount() - time < 16667);
	}
}

void Application::Exit()
{
	DxLib_End();				// ＤＸライブラリ使用の終了処理
}
