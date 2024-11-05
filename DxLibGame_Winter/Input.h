#pragma once
class Input
{
	// 入力をつかさどるクラス
	// シングルトン
private:
	Input();
	Input(const Input&) = delete;
	void operator=(const Input&) = delete;

	// 入力を記憶
	int m_input;
	int m_beforeInput;

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
};

