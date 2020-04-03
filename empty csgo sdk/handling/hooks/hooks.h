#pragma once

#include "../handling.h"

#include "../utils/vmt.h"

#include "../../sdk/interfaces/interfaces.h"

namespace handling {
	namespace hooks {
		enum funcs_indexes {
			create_move = 24,
			paint_traverse = 41,
			lock_cursor = 67
		};

		static bool __fastcall CreateMoveHook( sdk::interfaces::client_mode* thisptr, std::uint32_t* edx, float Time, sdk::classes::user_cmd* Command ) noexcept;
		static void __fastcall PaintTraverseHook( std::uint32_t* ecx, std::uint32_t* edx, std::uint32_t Panel, bool ForceRepaint, bool AllowForce ) noexcept;
		static void __fastcall LockCursorHook( std::uint32_t* ecx, std::uint32_t* edx ) noexcept;

		void RunHooks( void ) noexcept;
		void ShutdownHooks( void ) noexcept;
	};
};