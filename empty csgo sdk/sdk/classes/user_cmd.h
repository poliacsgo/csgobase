#pragma once

#include "../math/vector_3d.h"

namespace sdk {
	namespace classes {
		// https://github.com/pmrowla/hl2sdk-csgo/blob/master/game/shared/usercmd.h

		enum cmd_buttons {
			in_attack = (1 << 0),
			in_jump = (1 << 1),
			in_duck = (1 << 2),
			in_forward = (1 << 3),
			in_back = (1 << 4),
			in_use = (1 << 5),
			in_cancel = (1 << 6),
			in_left = (1 << 7),
			in_right = (1 << 8),
			in_moveleft = (1 << 9),
			in_moveright = (1 << 10),
			in_attack2 = (1 << 11),
			in_run = (1 << 12),
			in_reload = (1 << 13),
			in_alt1 = (1 << 14),
			in_alt2 = (1 << 15),
			in_score = (1 << 16),
			in_speed = (1 << 17),
			in_walk = (1 << 18),
			in_zoom = (1 << 19),
			in_weapon1 = (1 << 20),
			in_weapon2 = (1 << 21),
			in_bullrush = (1 << 22),
			in_grenade1 = (1 << 23),
			in_grenade2 = (1 << 24),
			in_attack3 = (1 << 25)
		};

		class user_cmd {
		public:
			char 				 _pad0[0x4];
			std::int32_t 		 CommandNumber;
			std::int32_t 		 TickCount;
			sdk::math::vector_3d ViewAngles;
			sdk::math::vector_3d AimDirection;
			float 				 ForwardMove;
			float 				 SideMove;
			float 				 UpMove;
			std::int32_t 		 Buttons;
			std::int32_t 		 Impulse;
			std::int32_t 		 WeaponSelect;
			std::int32_t 		 WeaponSubType;
			std::int32_t 		 RandomSeed;
			short 				 MousedX;
			short 				 MousedY;
			bool 				 HasBeenPredicted;
		};
	};
};