#pragma once
#include "Vector2.h"
#include <map>
#include <string>
#include <vector>

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

	// 入力をつかさどるクラス
	// シングルトン
private:
	Input();
	Input(const Input&) = delete;
	void operator=(const Input&) = delete;

	// 入力を記憶
	int m_padInput;
	int m_beforePadInput;
	// キー入力
	char m_keyInput[256];

	Vector2 m_inputAxis;
	// イベントキーと入力値の相対表
	std::map<std::string, std::vector<Peripheral>> m_inputEvent;

public:
	static Input& GetInstance();

	/// <summary>
	/// 入力の更新
	/// </summary>
	void Update();

	/// <summary>
	/// IDの入力がそのフレームで初めて入力されたかどうか
	/// </summary>
	/// <param name="id">入力</param>
	/// <returns>true:押した瞬間 false:押してないor押しっぱなし</returns>
	bool IsTrigger(int id);

	/// <summary>
	/// IDの入力が押されているかどうか
	/// </summary>
	/// <param name="id">入力</param>
	/// <returns>true:押している false:押していない</returns>
	bool IsPressed(int id);

	Vector2 GetInputAxis();
};

