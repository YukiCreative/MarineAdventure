#pragma once
class Input
{
	// ���͂������ǂ�N���X
	// �V���O���g��
private:
	Input();
	Input(const Input&) = delete;
	void operator=(const Input&) = delete;

	// ���͂��L��
	int m_input;
	int m_beforeInput;

public:
	static Input& GetInstance();

	/// <summary>
	/// ���͂̍X�V
	/// </summary>
	void Update();

	/// <summary>
	/// ID�̓��͂����̃t���[���ŏ��߂ē��͂��ꂽ���ǂ���
	/// </summary>
	/// <param name="id">����</param>
	/// <returns>true:�������u�� false:�����ĂȂ�or�������ςȂ�</returns>
	bool IsTrigger(int id);

	/// <summary>
	/// ID�̓��͂�������Ă��邩�ǂ���
	/// </summary>
	/// <param name="id">����</param>
	/// <returns>true:�����Ă��� false:�����Ă��Ȃ�</returns>
	bool IsPressed(int id);
};

