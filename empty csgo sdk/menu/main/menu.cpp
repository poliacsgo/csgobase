#include "menu.h"

namespace menu {
	bool MenuOpened = false;

	sdk::math::vector_2d GetMousePosition( ) {
		POINT position;
		if ( !GetCursorPos( &position ) )
			return sdk::math::vector_2d(0, 0);

		if ( !ScreenToClient( FindWindowA( 0, "Counter-Strike: Global Offensive" ), &position ) )
			return sdk::math::vector_2d( 0, 0 );

		return sdk::math::vector_2d( position.x, position.y );
	}

	bool InPosition( int x, int y, int w, int h ) {
		POINT position;
		if ( !GetCursorPos( &position ) )
			return false;

		if ( !ScreenToClient( FindWindowA( 0, "Counter-Strike: Global Offensive" ), &position ) )
			return false;

		if ( position.x <= x || position.y <= y || position.x >= x + w || position.y >= y + h )
			return false;

		return true;
	}

	namespace draw {
		int MenuX = 200;
		int MenuY = 200;

		int MenuW = 400;
		int MenuH = 350;

		void DrawMenu( ) {

			if ( !GetKeyState( VK_INSERT ) ) {
				menu::MenuOpened = false;
				return;
			}

			menu::MenuOpened = true;

			RunDragAndResizeFeature( );

			handling::utils::RenderRoundedRectangle( MenuX - 2, MenuY - 2, MenuW + 4, MenuH + 4, 6, sdk::classes::color( 0, 0, 0, 200 ) ); // background outside
			handling::utils::RenderRoundedRectangle( MenuX, MenuY, MenuW, MenuH, 6, sdk::classes::color( 50, 50, 50, 250 ) ); // background inside
			handling::utils::RenderRoundedRectangle( MenuX, MenuY, MenuW, 25, 6, sdk::classes::color( 70, 70, 70 ) ); //header
			handling::utils::RenderLine( MenuX + 5, MenuY + 24, MenuX + MenuW - 6, MenuY + 24, sdk::classes::color( 255, 160, 0, 250 ) ); // underline of header
			handling::utils::RenderText( MenuX + 7, MenuY + 5, sdk::classes::color( 255, 255, 255 ), handling::utils::TitleFont, "Empty SDK Cheat Base" ); //title

			DrawControls( );
		}

		void DrawControls( ) {
			menu::controls::ClickedButton = menu::controls::Clicked( VK_LBUTTON );
			controls::ControlPushX = draw::MenuX + 20;
			controls::ControlPushY = draw::MenuY + 40;

			menu::controls::AddComboBox( "Aim Mode", { "Legit", "Rage" }, &menu::config::config.AimbotMode );
			
			switch ( menu::config::config.AimbotMode ) {
				case 0: menu::controls::AddSlider( "Field Of View", 5, &menu::config::config.FOV ); break;
				case 1: {
					menu::controls::AddSlider( "Field Of View", 180, &menu::config::config.FOV );
					menu::controls::AddCheckbox( "Autoshoot", &menu::config::config.Autoshoot );
				} break;
			}

			menu::controls::AddCheckbox( "Remove Recoil", &menu::config::config.RemoveRecoil );
			menu::controls::AddCheckbox( "Bunnyhop", &menu::config::config.Bunnyhop );

			if ( menu::config::config.Bunnyhop )
				menu::controls::AddCheckbox( "Autostrafe", &menu::config::config.AutoStrafe );

			menu::controls::AddCheckbox( "Box", &menu::config::config.Box );
			menu::controls::AddCheckbox( "Name", &menu::config::config.Name );
			menu::controls::AddCheckbox( "Health", &menu::config::config.Health );
		}

		void RunDragAndResizeFeature( ) {
			if ( GetAsyncKeyState( VK_LBUTTON ) & 0x8000 && menu::InPosition( MenuX + MenuW - 20, MenuY + MenuH - 20, 40, 40 ) ) {
				MenuW = menu::GetMousePosition( ).x - MenuX + 8;
				MenuH = menu::GetMousePosition( ).y - MenuY + 8;
			}

			/* make sure size isn't too large */
			if ( MenuW < 300 ) MenuW = 300;
			if ( MenuW > 900 ) MenuW = 900;
			if ( MenuH < 300 ) MenuH = 300;
			if ( MenuH > 900 ) MenuH = 900;

			/* dragging */
			static int DragPosX = 0;
			static int DragPosY = 0;
			bool Clicked = false;
			static bool DraggingMenu = false;

			if ( GetAsyncKeyState( VK_LBUTTON ) )
				Clicked = true;

			if ( DraggingMenu && !Clicked )
				DraggingMenu = false;

			if ( DraggingMenu && Clicked ) {
				MenuX = menu::GetMousePosition( ).x - DragPosX;
				MenuY = menu::GetMousePosition( ).y - DragPosY;
			}

			if ( menu::InPosition( MenuX, MenuY, MenuW, 25 ) ) {
				DraggingMenu = true;
				DragPosX = menu::GetMousePosition( ).x - MenuX;
				DragPosY = menu::GetMousePosition( ).y - MenuY;
			}
		}
	};
	namespace controls {
		int ControlPushX;
		int ControlPushY;
		bool ClickedButton = false;

		bool Clicked( int key ) {
			static bool down = false;
			bool out = GetAsyncKeyState( key ) && !down;
			down = GetAsyncKeyState( key );
			return out;
		}
	};
};