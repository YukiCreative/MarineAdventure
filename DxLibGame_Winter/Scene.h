#pragma once
#include <list>

class Scene
{
	class ScreenEffect
	{
	private:
		using UpdateFunc_t = void (ScreenEffect::*) ();
	public:
		void Update();
		void Draw();
	};
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
	virtual void Draw() = 0;
};