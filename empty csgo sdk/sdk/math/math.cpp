#pragma once
#include "math.h"
namespace math {
	namespace main {
		void AngleVectors( const sdk::math::vector_3d& angles, sdk::math::vector_3d* forward ) {
			assert( forward );

			float sp, sy, cp, cy;

			sy = sin( DEG2RAD( angles[ 1 ] ) );
			cy = cos( DEG2RAD( angles[ 1 ] ) );

			sp = sin( DEG2RAD( angles[ 0 ] ) );
			cp = cos( DEG2RAD( angles[ 0 ] ) );

			forward->x = cp * cy;
			forward->y = cp * sy;
			forward->z = -sp;
		}

		float CalculateDistance( const sdk::math::vector_3d& viewAngle, const sdk::math::vector_3d& aimAngle ) {
			sdk::math::vector_3d ang, aim;

			main::AngleVectors( viewAngle, &aim );
			main::AngleVectors( aimAngle, &ang );

			return RAD2DEG( acos( aim.Dot( ang ) / aim.LengthSqr( ) ) );
		}

		sdk::math::vector_3d CalculateAngle( const sdk::math::vector_3d& vecSource, const sdk::math::vector_3d& vecDestination ) {
			sdk::math::vector_3d qAngles;
			sdk::math::vector_3d delta = sdk::math::vector_3d( ( vecSource[ 0 ] - vecDestination[ 0 ] ), ( vecSource[ 1 ] - vecDestination[ 1 ] ), ( vecSource[ 2 ] - vecDestination[ 2 ] ) );
			float hyp = sqrtf( delta[ 0 ] * delta[ 0 ] + delta[ 1 ] * delta[ 1 ] );
			qAngles[ 0 ] = ( float ) ( atan( delta[ 2 ] / hyp ) * ( 180.0f / M_PI ) );
			qAngles[ 1 ] = ( float ) ( atan( delta[ 1 ] / delta[ 0 ] ) * ( 180.0f / M_PI ) );
			qAngles[ 2 ] = 0.f;
			if ( delta[ 0 ] >= 0.f )
				qAngles[ 1 ] += 180.f;

			return qAngles;
		}
	}
}