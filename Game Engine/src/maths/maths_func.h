#pragma once
#pragma warning (disable : 4244) // Possible loss of data conversion from double to float

#define _USE_MATH_DEFINES
#include <math.h>

namespace valk {
	namespace maths {
		inline float toRadians(float degrees)
		{
			return degrees * (M_PI / 180.0f);
		}
	}
}
