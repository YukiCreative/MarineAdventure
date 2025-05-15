#pragma once

/// <summary>
/// GetFPSとかを計測した結果を効率よく記憶しておきたい
/// ここまで来たらシングルトンにしようか
/// </summary>
class Time
{
private:
	Time() {}
	Time(const Time&) = delete;
	void operator=(const Time&) = delete;

	static float s_fps;
	/// <summary>
	/// 1フレーム処理するまでに経過した時間
	/// GetFPSの逆数をとっただけの「なんちゃって」です。
	/// </summary>
	static float s_deltaTime;
	static int s_frameCount;
public:
	static Time& GetInstance();

	/// <summary>
	/// fpsやdeltaTimeを更新する
	/// 1フレームに一回だけ走らせる
	/// </summary>
	void Update();

	// これらの関数をどうしてもstaticにしてみたい
	// なんでStaticにしたし
	static float FPS();
	static float DeltaTime();
	// プログラムが始まってからのフレーム
	static int FrameCount();
};