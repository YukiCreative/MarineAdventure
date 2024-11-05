#pragma once
class Application
{
	// シングルトンオブジェクト
private:
	Application() = default;
	Application(const Application&) = delete;
	void operator=(const Application&) = delete;

public:
	static Application& GetInstance();

	bool Init();
	void Run();
	void Exit();
};

