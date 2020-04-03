#pragma once
#include "../sdk.h"
#include "../../handling/utils/memory.h"
namespace sdk {
	namespace interfaces {
		class debug_overlay {
		public:
			int world_to_screen( const sdk::math::vector_3d& point, sdk::math::vector_3d& screen ) {
				typedef int( __thiscall* OFn )( PVOID, const sdk::math::vector_3d&, sdk::math::vector_3d& );
				return handling::memory::ScanVFunction <OFn>( this, 13 )( this, point, screen );
			}
		};
	}
}