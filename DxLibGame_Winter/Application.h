#pragma once
class Application
{
	// �V���O���g���I�u�W�F�N�g
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

