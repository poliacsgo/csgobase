#pragma once
#include "menu.h"
#include <windows.h>
#include <iostream>
#include <fstream>
#include <sstream>

//credits kmeth
class config_t {
public:
	bool Bunnyhop = false;
	bool Box = false;
	bool Name = false;
	bool Health = false;
	int AimbotMode = 0;
	int FOV = 0;
	bool Autoshoot = false;
	bool RemoveRecoil = false;
	bool AutoStrafe = false;
};
namespace menu {
	namespace config {
		extern config_t config;

		static void LoadConfig( );
		static void SaveConfig( );
	};
};