#include "Time.h"
#include <DxLib.h>

namespace Time
{
	float DeltaTime()
	{
		// GetFPS�Ŏ擾�����l�̋t����Ԃ������ł����͂�
		return 1 / GetFPS();
	}
}