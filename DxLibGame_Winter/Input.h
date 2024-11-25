#pragma once
#include "Vector2.h"
#include <map>
#include <string>

class Input
{
	/// <summary>
	/// 一つのイベントに対応している入力のコード
	/// 各入力媒体のコードを入れる
	/// </summary>
	struct InputCode
	{
		int keyInputCode;
		int controllerInputCode;
	};

	// 入力をつかさどるクラス
	// シングルトン
private:
	Input();
	Input(const Input&) = delete;
	void operator=(const Input&) = delete;

	// 入力を記憶
	int m_input;
	int m_beforeInput;

	Vector2 m_inputAxis;
	// イベントキーと入力値の相対表
	std::map<std::string, InputCode> m_inputEvent;

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

