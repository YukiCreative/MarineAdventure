#pragma once

/// <summary>
/// GetFPS�Ƃ����v���������ʂ������悭�L�����Ă�������
/// �����܂ŗ�����V���O���g���ɂ��悤��
/// </summary>
class Time
{
private:
	Time() {}
	Time(const Time&) = delete;
	void operator=(const Time&) = delete;

	static float s_fps;
	/// <summary>
	/// 1�t���[����������܂łɌo�߂�������
	/// GetFPS�̋t�����Ƃ��������́u�Ȃ񂿂���āv�ł��B
	/// </summary>
	static float s_deltaTime;
	static int s_frameCount;
public:
	static Time& GetInstance();

	/// <summary>
	/// fps��deltaTime���X�V����
	/// 1�t���[���Ɉ�񂾂����点��
	/// </summary>
	void Update();

	// �����̊֐����ǂ����Ă�static�ɂ��Ă݂���
	// �Ȃ��Static�ɂ�����
	static float FPS();
	static float DeltaTime();
	// �v���O�������n�܂��Ă���̃t���[��
	static int FrameCount();
};