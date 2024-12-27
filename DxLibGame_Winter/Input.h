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
	KeyInput m_keyInput;
	KeyInput m_beforeKeyInput;

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
	/// <param name="key">入力</param>
	/// <returns>true:押した瞬間 false:押してないor押しっぱなし</returns>
	bool IsTrigger(std::string key) const;

	/// <summary>
	/// IDの入力が押されているかどうか
	/// </summary>
	/// <param name="key">入力</param>
	/// <returns>true:押している false:押していない</returns>
	bool IsPressed(std::string key) const;

	Vector2 GetInputAxis() const;
};