#include "Rigid.h"

Rigid::Rigid() :
	accel(),
	position(),
	weight(0.0f),
	airResistance(0.0f),
	waterResistance(0.0f),
	force()
{
}

void Rigid::Update()
{
	// 抵抗を考えて移動する
	// ma - kvってこと？
	// 加速度を求めたいので、
	// 力Fを加えてもらって、そこから計算をすることになるかな

	// まずFとmから、aを出す
	// F = maより、a = F / m;
	// 割り算するのかー
	accel = force / weight;
	// 次に、抵抗を出す
	// 自分が今水中にいるのか、地上にいるのかで使う定数を変える

}
