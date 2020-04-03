#pragma once

#include "../handling.h"

namespace handling {
	namespace utils {
		extern std::uint64_t GeneralFont;
		extern std::uint64_t TitleFont;
		extern std::uint64_t ControlFont;
		extern std::uint64_t VisualFont;

		void RenderLine( std::int32_t x, std::int32_t y, std::int32_t x2, std::int32_t y2, sdk::classes::color color );
		void RenderText( std::int32_t x, std::int32_t y, sdk::classes::color color, std::uint64_t font, std::string_view text );
		void RenderFilledRectangle( std::int32_t x, std::int32_t y, std::int32_t w, std::int32_t h, sdk::classes::color color);
		void RenderOutlinedRectangle( std::int32_t x, std::int32_t y, std::int32_t w, std::int32_t h, sdk::classes::color color );
		void RenderRoundedRectangle( std::int32_t x, std::int32_t y, std::int32_t w, std::int32_t h, std::int32_t radius, sdk::classes::color color );
		void RenderOutlinedRectangleDX( std::int32_t x, std::int32_t y, std::int32_t x1, std::int32_t y1, sdk::classes::color color );

		void RunRender(void) noexcept;
		void ShutdownRender(void) noexcept;
	};
};