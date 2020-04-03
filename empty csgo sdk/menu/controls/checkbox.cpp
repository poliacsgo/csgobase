#include "../main/menu.h"

namespace menu {
	namespace controls {
		void AddCheckbox( std::string_view name, bool* variable ) {

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

			handling::utils::RenderRoundedRectangle( ControlBounds[ 0 ], ControlBounds[ 1 ], 12, 12, 3, sdk::classes::color( 70, 70, 70 ) ); // checkbox unselected

			if ( *variable ) {
				handling::utils::RenderRoundedRectangle( ControlBounds[ 0 ] + 2, ControlBounds[ 1 ] + 2, 8, 8, 3, sdk::classes::color( 255, 160, 0 ) ); // checkbox selected
				handling::utils::RenderText( ControlBounds[ 0 ] + 19, ControlBounds[ 1 ] - 2, sdk::classes::color( 255, 255, 255 ), handling::utils::ControlFont, name ); // control name selected

			}
			else {
				handling::utils::RenderRoundedRectangle( ControlBounds[ 0 ], ControlBounds[ 1 ], 12, 12, 3, sdk::classes::color( 70, 70, 70 ) ); // checkbox unselected
				handling::utils::RenderText( ControlBounds[ 0 ] + 19, ControlBounds[ 1 ] - 2, sdk::classes::color( 210, 210, 210 ), handling::utils::ControlFont, name ); // control name unse;ected
			}

			if ( menu::InPosition( ControlBounds[ 0 ], ControlBounds[ 1 ], ControlBounds[ 2 ], ControlBounds[ 3 ] ) )
				handling::utils::RenderText( ControlBounds[ 0 ] + 19, ControlBounds[ 1 ] - 2, sdk::classes::color( 255, 255, 255 ), handling::utils::ControlFont, name ); // control name hovered

			controls::ControlPushY += 18;
		}
	};
};