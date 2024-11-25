#pragma once
#include "Vector2.h"
#include <map>
#include <string>

class Input
{
	/// <summary>
	/// ��̃C�x���g�ɑΉ����Ă�����͂̃R�[�h
	/// �e���͔}�̂̃R�[�h������
	/// </summary>
	struct InputCode
	{
		int keyInputCode;
		int controllerInputCode;
	};

	// ���͂������ǂ�N���X
	// �V���O���g��
private:
	Input();
	Input(const Input&) = delete;
	void operator=(const Input&) = delete;

	// ���͂��L��
	int m_input;
	int m_beforeInput;

	Vector2 m_inputAxis;
	// �C�x���g�L�[�Ɠ��͒l�̑��Ε\
	std::map<std::string, InputCode> m_inputEvent;

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

	Vector2 GetInputAxis();
};

