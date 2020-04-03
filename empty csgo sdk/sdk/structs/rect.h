#pragma once
#include "../sdk.h"

namespace sdk {
	namespace structs {
		struct rect_t
		{
			struct { int x, y, w, h; };

			rect_t( ) = default;
			~rect_t( ) = default;

			rect_t( int x, int y, int w, int h ) : x( x ), y( y ), w( w ), h( h ) {}
			rect_t( const sdk::math::vector_2d& tl, const sdk::math::vector_2d& br ) : x( tl.x ), y( tl.y ), w( br.x - tl.x ), h( tl.y - br.y ) {}

			rect_t( const rect_t& ) = default;
			rect_t& operator=( const rect_t& ) = default;

			rect_t( rect_t&& ) = default;
			rect_t& operator=( rect_t&& ) = default;

			int right( ) const
			{
				return x + w;
			}

			int bottom( ) const
			{
				return y + h;
			}

			DECLSPEC_NOINLINE bool is_in_bounds( const sdk::math::vector_2d& pt ) const
			{
				if ( this->x > pt.x )        return false;
				if ( this->y > pt.y )        return false;
				if ( this->right( ) < pt.x )  return false;
				if ( this->bottom( ) < pt.y ) return false;

				return true;
			}
		};
	};
};