#pragma once
#include "Vector2.h"
#include <map>
#include <string>
#include <vector>
#include <array>

class Input
{
	enum class PeripheralType
	{
		kKeyboard,
		kPad,
	};

	struct Peripheral
	{
		PeripheralType type;
		int inputCode;
	};

	struct KeyInput
	{
		char state[256] = {};
	};

	// ���͂������ǂ�N���X
	// �V���O���g��
private:
	Input();
	Input(const Input&) = delete;
	void operator=(const Input&) = delete;

	// ���͂��L��
	int m_padInput;
	int m_beforePadInput;
	// �L�[����
	KeyInput m_keyInput;
	KeyInput m_beforeKeyInput;

	Vector2 m_inputAxis;
	// �C�x���g�L�[�Ɠ��͒l�̑��Ε\
	std::map<std::string, std::vector<Peripheral>> m_inputEvent;

public:
	static Input& GetInstance();

	/// <summary>
	/// ���͂̍X�V
	/// </summary>
	void Update();

	/// <summary>
	/// ID�̓��͂����̃t���[���ŏ��߂ē��͂��ꂽ���ǂ���
	/// </summary>
	/// <param name="key">����</param>
	/// <returns>true:�������u�� false:�����ĂȂ�or�������ςȂ�</returns>
	bool IsTrigger(std::string key) const;

	/// <summary>
	/// ID�̓��͂�������Ă��邩�ǂ���
	/// </summary>
	/// <param name="key">����</param>
	/// <returns>true:�����Ă��� false:�����Ă��Ȃ�</returns>
	bool IsPressed(std::string key) const;

	Vector2 GetInputAxis() const;
};