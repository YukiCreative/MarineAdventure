#include "Vector2.h"
#include <DxLib.h>

Vector2::operator DxLib::VECTOR() const
{
	return VGet(x, y, 0.0f);
}
