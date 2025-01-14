#pragma once
class Application
{
	// シングルトンオブジェクト
private:
	Application();
	Application(const Application&) = delete;
	void operator=(const Application&) = delete;

	bool m_isRunning;
public:
	static Application& GetInstance();

	bool Init();
	void Run();
	// main以外で呼ばないで
	void Terminate();

	// こっちがゲームを終える時の処理
	// Terminateと紛らわしくて御免
	void Quit() { m_isRunning = false; };
};

