#pragma once
#include <list>
#include <memory>

/// <summary>
/// シーンで、画面をフェードさせたり、カメラを揺らしたりしたい
/// </summary>
class ScreenEffectController
{
private:
	/// <summary>
	/// 四角形を画面いっぱい描画するだけ
	/// </summary>
	class FadePanel
	{
	private:
		uint8_t m_alpha;
		unsigned int m_color;
	public:
		FadePanel() = default;
		void Draw() const;
	};

	// 仕様
	// 初期化時にコンストラクタでパラメータを決める
	// リストをキューとして使い、リストの先頭にあるものだけ実行する
	// 終わったら、その旨を伝えて削除してもらう
	class ScreenEffect
	{
	protected:
		bool m_isFinished = false;
	public:
		virtual void Update() = 0;
		bool IsFinished() const { return m_isFinished; }
	};

	class ScreenFade : public ScreenEffect
	{
		//friend FadePanel;
	private:
		// どれだけ時間かけるか
		int m_lifeFrame;
		// 最終的に到達する透明度
		float m_percent;
		unsigned int m_color;
	public:
		ScreenFade(int frame, float fadePercent, unsigned int color);
		void Update() override;
	};

	std::shared_ptr<FadePanel> m_fadePanel;

	// list第一層：スクリーン効果のキュー。終わらないと次に行かない
	// 第二層：スクリーン効果（複数同時に実行できる）
	using ScreenEffects_t = std::list<std::list<std::shared_ptr<ScreenEffect>>>;
	ScreenEffects_t m_screenEffects;

public:
	void Update();
	void Draw() const;
};

