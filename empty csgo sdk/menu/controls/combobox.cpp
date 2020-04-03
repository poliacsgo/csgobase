#include "../main/menu.h"
namespace menu {
	namespace controls {
		void AddComboBox( std::string_view name, std::vector< std::string_view> items, int* variable ) {

			int ControlBounds[ 4 ] {
				controls::ControlPushX,
				controls::ControlPushY + 15,
				menu::draw::MenuW / 3.07,
				16
			};

			static std::string NameSelected = "";
			bool ComboOpen = false;
			bool PressedCombo = false;
			static bool SelectedOpen = false;

			if ( menu::InPosition( ControlBounds[ 0 ], ControlBounds[ 1 ], ControlBounds[ 2 ], ControlBounds[ 3 ] ) ) {
				if ( menu::controls::ClickedButton ) {
					PressedCombo = true;
					NameSelected = name;
				}
			}

			if ( PressedCombo ) 
				SelectedOpen = !SelectedOpen;

			if ( NameSelected == name )
				ComboOpen = SelectedOpen;

			if ( menu::InPosition( ControlBounds[ 0 ], ControlBounds[ 1 ] - 10, ControlBounds[ 2 ], ControlBounds[ 3 ] + 10 ) ) {
				handling::utils::RenderText( ControlBounds[ 0 ], ControlBounds[ 1 ] - 17, sdk::classes::color( 255, 255, 255 ), handling::utils::ControlFont, name ); // current selected item hovered
			}

			handling::utils::RenderText( ControlBounds[ 0 ], ControlBounds[ 1 ] - 17, sdk::classes::color( 210, 210, 210 ), handling::utils::ControlFont, name ); // current selected item not hovered

			handling::utils::RenderRoundedRectangle( ControlBounds[ 0 ], ControlBounds[ 1 ], ControlBounds[ 2 ], ControlBounds[ 3 ], 2, sdk::classes::color( 70, 70, 70 ) ); // combobox header

			handling::utils::RenderText( ControlBounds[ 0 ] + 3, ControlBounds[ 1 ], sdk::classes::color( 255, 255, 255 ), handling::utils::ControlFont, items.at( *variable ) ); // current selected item

			if ( ComboOpen ) {

				handling::utils::RenderRoundedRectangle( ControlBounds[ 0 ], ControlBounds[ 1 ] + 24, ControlBounds[ 2 ], (items.size() * 17), 2, sdk::classes::color( 35, 35, 35 ) ); //background for items
				
				for ( int i = 0; i < items.size( ); i++ ) {
					auto item = items.at( i );

					int ComboItemRect[ 4 ] = 
					{ 
						ControlBounds[ 0 ],
						ControlBounds[ 1 ] + 24 + ( i * 17 ),
						ControlBounds[ 2 ],
						ControlBounds[ 3 ] 
					};


					if ( GetKeyState( VK_LBUTTON ) & 0x8000 && menu::InPosition( ComboItemRect[ 0 ], ComboItemRect[ 1 ], ComboItemRect[ 2 ], ComboItemRect[ 3 ] ) )
						 *variable = i;


					if ( *variable == i ) {
						handling::utils::RenderText( ComboItemRect[ 0 ] + 4, ComboItemRect[ 1 ], sdk::classes::color( 255, 160, 0 ), handling::utils::ControlFont, items.at( i ) ); // current selected item
					}
					else {
						handling::utils::RenderText( ComboItemRect[ 0 ] + 4, ComboItemRect[ 1 ], sdk::classes::color( 255, 255, 255 ), handling::utils::ControlFont, items.at( i ) ); // unselected items
					}
				}
			}

			if ( ComboOpen )
				controls::ControlPushY += 43 + items.size( ) * 18;
			else
				controls::ControlPushY += 37;
		}
	};
};