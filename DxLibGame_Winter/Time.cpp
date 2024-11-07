#include "Time.h"
#include <DxLib.h>

namespace Time
{
	float DeltaTime()
	{
		// GetFPS‚Åæ“¾‚µ‚½’l‚Ì‹t”‚ğ•Ô‚·ˆ—‚Å‚¢‚¢‚Í‚¸
		return 1 / GetFPS();
	}
}