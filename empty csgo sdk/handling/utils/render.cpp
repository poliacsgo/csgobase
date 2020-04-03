#pragma once

#include "render.h"
#include "../../sdk/interfaces/interfaces.h"

namespace handling {
	namespace utils {
		std::uint64_t GeneralFont;
		std::uint64_t TitleFont;
		std::uint64_t ControlFont;
		std::uint64_t VisualFont;

		void RenderLine( std::int32_t x, std::int32_t y, std::int32_t x2, std::int32_t y2, sdk::classes::color color ) {
			sdk::interfaces::GuiSurface->DrawSetColor( color.red, color.green, color.blue, color.alpha );
			sdk::interfaces::GuiSurface->DrawLine( x, y, x2, y2 );
		}

		void RenderText( std::int32_t x, std::int32_t y, sdk::classes::color color, std::uint64_t font, std::string_view text ) {
			const auto FinalText = std::wstring( text.begin( ), text.end( ) );

			sdk::interfaces::GuiSurface->DrawSetTextColor( color.red, color.green, color.blue, color.alpha );
			sdk::interfaces::GuiSurface->DrawSetTextFont( font );
			sdk::interfaces::GuiSurface->DrawSetTextPos( x, y );
			sdk::interfaces::GuiSurface->DrawPrintText( FinalText.c_str( ), wcslen( FinalText.c_str( ) ) );
		}

		void RenderFilledRectangle( std::int32_t x, std::int32_t y, std::int32_t w, std::int32_t h, sdk::classes::color color ) {
			sdk::interfaces::GuiSurface->DrawSetColor( color.red, color.green, color.blue, color.alpha );
			sdk::interfaces::GuiSurface->DrawFilledRect( x, y, x + w, y + h );
		}

		void RenderOutlinedRectangle( std::int32_t x, std::int32_t y, std::int32_t w, std::int32_t h, sdk::classes::color color ) {
			sdk::interfaces::GuiSurface->DrawSetColor( color.red, color.green, color.blue, color.alpha );
			sdk::interfaces::GuiSurface->DrawOutlinedRect( x, y, x + w, y + h );
		}

		void RenderOutlinedRectangleDX( std::int32_t x, std::int32_t y, std::int32_t x1, std::int32_t y1, sdk::classes::color color ) {
			sdk::interfaces::GuiSurface->DrawSetColor( color.red, color.green, color.blue, color.alpha );
			sdk::interfaces::GuiSurface->DrawOutlinedRect( x, y, x1,y1 );
		}
		void RenderRoundedRectangle( std::int32_t x, std::int32_t y, std::int32_t w, std::int32_t h, std::int32_t radius, sdk::classes::color color ) {
			constexpr int quality = 24;
			static sdk::structs::vertex verts[ quality ];
			sdk::math::vector_2d add( 0, 0 );

			for ( int i = 0; i < quality; i++ ) {
				float angle = ( static_cast < float > ( i ) / -quality ) * 6.28f - ( 6.28f / 16.f );

				verts[ i ].position.x = radius + x + add.x + ( radius * sin( angle ) );
				verts[ i ].position.y = h - radius + y + add.y + ( radius * cos( angle ) );

				switch( i ) {
					case 4: add.y = -h + ( radius * 2 ); break;
					case 10: add.x = w - ( radius * 2 ); break;
					case 16: add.y = 0; break;
					case 22: add.x = 0; break;
				}
			}
			sdk::interfaces::GuiSurface->DrawSetColor( color.red, color.green, color.blue, color.alpha );
			sdk::interfaces::GuiSurface->DrawTexturedPolygon( quality, verts );
		}

		void RunRender( void ) noexcept {
			GeneralFont = sdk::interfaces::GuiSurface->CreateGuiFont( );
			TitleFont = sdk::interfaces::GuiSurface->CreateGuiFont( );
			ControlFont = sdk::interfaces::GuiSurface->CreateGuiFont( );
			VisualFont = sdk::interfaces::GuiSurface->CreateGuiFont( );

			sdk::interfaces::GuiSurface->SetFontGlyphSet( GeneralFont, "Small Fonts", 12, 0, 0, 0, sdk::interfaces::font_flags::fontflag_antialias | sdk::interfaces::font_flags::fontflag_outline );
			sdk::interfaces::GuiSurface->SetFontGlyphSet( TitleFont, "Tahoma", 15, 600, 0, 0, sdk::interfaces::font_flags::fontflag_antialias );
			sdk::interfaces::GuiSurface->SetFontGlyphSet( ControlFont, "Roboto", 15, 0, 0, 0, sdk::interfaces::font_flags::fontflag_antialias );
			sdk::interfaces::GuiSurface->SetFontGlyphSet( VisualFont, "Roboto", 10, 0, 0, 0, sdk::interfaces::font_flags::fontflag_antialias | sdk::interfaces::font_flags::fontflag_dropshadow );

		}

		void ShutdownRender( void ) noexcept {
			GeneralFont = NULL;
			TitleFont = NULL;
			ControlFont = NULL;
			VisualFont = NULL;
		}
	};
};