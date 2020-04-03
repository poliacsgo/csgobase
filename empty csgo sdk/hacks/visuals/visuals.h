#pragma once
#include "../../handling/utils/variables.h"
#include "../../menu/main/menu.h"

namespace hacks {
	namespace visuals {
		void RunVisuals( );

		void DrawBox( sdk::structs::rect_t& box );
		void DrawHealth( sdk::classes::base_general* player, sdk::structs::rect_t& box );
		void DrawName( sdk::interfaces::player_info_t info, sdk::structs::rect_t& box );
		bool BoundingBox( sdk::classes::base_general* player, sdk::structs::rect_t& box );

	}
}