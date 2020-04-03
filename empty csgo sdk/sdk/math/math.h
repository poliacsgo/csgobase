#pragma once
#include "../sdk.h"
#define M_PI 3.14159265358979323846
#define M_PI_F		((float)(M_PI))
#define DEG2RAD( x  )  ( (float)(x) * (float)(M_PI_F / 180.f) )
#define RAD2DEG(x)  ((float)(x) * (float)(180.f / M_PI_F))

namespace math {
	namespace main {
		void AngleVectors( const sdk::math::vector_3d& angles, sdk::math::vector_3d* forward );
		float CalculateDistance( const sdk::math::vector_3d& viewAngle, const sdk::math::vector_3d& aimAngle );
		sdk::math::vector_3d CalculateAngle( const sdk::math::vector_3d& vecSource, const sdk::math::vector_3d& vecDestination );
	}
}