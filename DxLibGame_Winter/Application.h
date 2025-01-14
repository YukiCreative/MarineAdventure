#pragma once
class Application
{
	// �V���O���g���I�u�W�F�N�g
private:
	Application();
	Application(const Application&) = delete;
	void operator=(const Application&) = delete;

	bool m_isRunning;
public:
	static Application& GetInstance();

	bool Init();
	void Run();
	// main�ȊO�ŌĂ΂Ȃ���
	void Terminate();

	// ���������Q�[�����I���鎞�̏���
	// Terminate�ƕ���킵���Č��
	void Quit() { m_isRunning = false; };
};

