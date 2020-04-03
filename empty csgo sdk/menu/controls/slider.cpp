#include "../main/menu.h"

namespace menu {
	namespace controls {
		void AddSlider( std::string_view name, int max, int* variable ) {

			int ControlBounds[ 4 ] {
				controls::ControlPushX,
				controls::ControlPushY,
				menu::draw::MenuW / 3.07,
				16
			};
			if ( menu::InPosition( ControlBounds[ 0 ], ControlBounds[ 1 ], ControlBounds[ 2 ], ControlBounds[ 3 ] ) ) {
				if ( menu::controls::ClickedButton ) {
					*variable = !*variable;
				}
			}

			if ( menu::InPosition( ControlBounds[ 0 ], ControlBounds[ 1 ] - 10, ControlBounds[ 2 ], ControlBounds[ 3 ] + 10 ) ) {
				handling::utils::RenderText( ControlBounds[ 0 ], ControlBounds[ 1 ] - 2, sdk::classes::color( 255, 255, 255 ), handling::utils::ControlFont, name ); // current selected item hovered
			}

			handling::utils::RenderText( ControlBounds[ 0 ], ControlBounds[ 1 ] - 2, sdk::classes::color( 210, 210, 210 ), handling::utils::ControlFont, name ); // current selected item not hovered

			handling::utils::RenderRoundedRectangle( ControlBounds[ 0 ], ControlBounds[ 1 ] + 14, ControlBounds[ 2 ], ControlBounds[ 3 ], 2, sdk::classes::color( 70, 70, 70 ) ); // slider body

			float PixelDivisibe = ControlBounds[ 2 ] - 1.f;
			float PixelValue = max / PixelDivisibe;

			if ( GetAsyncKeyState( VK_LBUTTON ) && menu::InPosition( ControlBounds[ 0 ], ControlBounds[ 1 ] + 14, ControlBounds[ 2 ] + 5, ControlBounds[ 3 ] ) )
				*variable = ( menu::GetMousePosition( ).x - ( ControlBounds[ 0 ] ) ) * PixelValue;

			if ( *variable > max ) *variable = max;
			if ( *variable < 0.f ) *variable = 0.f;

			int PossiblePosition = ( menu::GetMousePosition( ).x - menu::draw::MenuX - 19);

			int PossibleValue = ( menu::GetMousePosition( ).x - ( ControlBounds[ 0 ] ) ) * PixelValue;

			std::string NamePlusValue = std::string( name ).c_str( );

			if ( menu::InPosition( ControlBounds[ 0 ], ControlBounds[ 1 ] + 14, ControlBounds[ 2 ], ControlBounds[ 3 ] ) && !( GetAsyncKeyState( VK_LBUTTON ) & 0x8000 ) ) {
				handling::utils::RenderRoundedRectangle( ControlBounds[ 0 ], ControlBounds[ 1 ] + 14, PossiblePosition, ControlBounds[ 3 ], 2, sdk::classes::color( 255, 160, 0, 70 ) ); // possible location of slider
				NamePlusValue += ": ";
				NamePlusValue += std::to_string( PossibleValue );
			}
			else if ( menu::InPosition( ControlBounds[ 0 ], ControlBounds[ 1 ] + 14, ControlBounds[ 2 ], ControlBounds[ 3 ] )  && GetAsyncKeyState( VK_LBUTTON ) & 0x8000 ) {
				NamePlusValue += ": ";
				NamePlusValue += std::to_string( *variable );
			}

			if (*variable > 0 && ( *variable / PixelValue ) > 2) // draws inverted if this isnt here
				handling::utils::RenderRoundedRectangle( ControlBounds[ 0 ], ControlBounds[ 1 ] + 14, ( *variable / PixelValue ), ControlBounds[ 3 ], 2, sdk::classes::color( 255, 160, 0 ) ); // location of slider

			handling::utils::RenderText( ControlBounds[ 0 ], ControlBounds[ 1 ] - 2, sdk::classes::color( 210, 210, 210 ), handling::utils::ControlFont, (std::string_view) ( NamePlusValue ) ); // current selected item not hovered










			controls::ControlPushY += 37;
		}
	};
};