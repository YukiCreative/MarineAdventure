#pragma once
#include <list>
#include <memory>

class Scene
{
protected:

	// 仕様
	// 初期化時にコンストラクタでパラメータを決める
	// リストをキューとして使い、リストの先頭にあるものだけ実行する
	// 終わったら、その旨を伝えて削除してもらう
	class ScreenEffect
	{
	protected:
		using UpdateFunc_t = void (ScreenEffect::*) ();
		bool m_isFinished = false;
	public:
		virtual void Update() = 0;
		virtual void Draw() const = 0;
		bool IsFinished() const { return m_isFinished; }
	};

	class ScreenFade : public ScreenEffect
	{
	private:
		// どれだけ時間かけるか
		int m_lifeFrame;
		// 最終的に到達する透明度
		float m_percent;
		unsigned int m_color;
	public:
		ScreenFade(int frame, float fadePercent, unsigned int color);
		void Update() override;
		void Draw() const override;
	};

	// list第一層：スクリーン効果のキュー。終わらないと次に行かない
	// 第二層：スクリーン効果（複数同時に実行できる）
	using ScreenEffects_t = std::list<std::list<std::shared_ptr<ScreenEffect>>>;
	ScreenEffects_t m_screenEffects;
public:
	/// <summary>
	/// 明示的にデストラクタをvirtualにしないといけないと聞いて
	/// </summary>
	virtual ~Scene() {}
	/// <summary>
	/// 更新処理
	/// </summary>
	virtual void Update() = 0;
	/// <summary>
	/// 描画
	/// </summary>
	virtual void Draw() const = 0;

	void UpdateScreenEffect()
	{
		if (m_screenEffects.empty()) return;

		bool isFinished = true;
		for (auto& effect : m_screenEffects.front())
		{
			isFinished &= effect->IsFinished();
		}
		// 今のキューのすべての画像効果が終わったら
		if (isFinished)
		{
			// 取り出す
			m_screenEffects.pop_front();
		}
		// 気を取り直してUpdate
		for (auto& effect : m_screenEffects.front())
		{
			effect->Update();
		}
	}

	void DrawScreenEffect() const
	{
		if (m_screenEffects.empty()) return;
		for (auto& effect : m_screenEffects.front())
		{
			effect->Draw();
		}
	}
};