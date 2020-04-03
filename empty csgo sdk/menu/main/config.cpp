#include "config.h"
namespace menu {
	namespace config {
		config_t config;

		static void LoadConfig( ) {
			CreateDirectoryA( "configs", NULL );
			std::string ConfigName;
			ConfigName = "configs/";
			ConfigName += "config";
			ConfigName += std::to_string( 1 ).c_str( );
			ConfigName += ".dat";

			std::ifstream f( ConfigName.c_str( ) );
			if ( !f.good( ) ) return;

			FILE* fin = fopen( ConfigName.c_str( ), "r" );
			fread( &config, sizeof( config_t ), 1, fin );
			fclose( fin );
		}

		static void SaveConfig( ) {
			CreateDirectoryA( "configs", NULL );
			std::string ConfigName;
			ConfigName = "configs/";
			ConfigName += "config";
			ConfigName += std::to_string( 1 ).c_str( );
			ConfigName += ".dat";
			FILE* fout = fopen( ConfigName.c_str( ), "w" );
			fwrite( &config, sizeof( config ), 1, fout );
			fclose( fout );
		}
	};
};