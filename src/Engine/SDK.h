#pragma once
#include "SDK_utils.h"
#include <string>

namespace Unity {
	class Time {
	public:
		DO_METHOD(void, set_timeScale, (float value)) { 0x0FF65380, 0x0 };
	};
}


