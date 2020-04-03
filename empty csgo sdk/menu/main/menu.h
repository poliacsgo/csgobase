#pragma once
#include "config.h"
#include "../../handling/utils/render.h"
namespace menu {

	namespace draw {
		extern int MenuX;
		extern int MenuY;

		extern int MenuW;
		extern int MenuH;

		void DrawMenu( );
		void DrawControls( );
		void RunDragAndResizeFeature( );
	};
	namespace controls {
		extern int ControlPushX;
		extern int ControlPushY;

		extern bool ClickedButton;

		void AddCheckbox( std::string_view name, bool* variable );
		void AddComboBox( std::string_view name, std::vector< std::string_view> items, int* variable );
		void AddSlider( std::string_view name, int max,  int* variable );

		bool Clicked( int key = 1 );
	};

	sdk::math::vector_2d GetMousePosition( );
	bool InPosition( int x, int y, int w, int h );
	extern bool MenuOpened;
};