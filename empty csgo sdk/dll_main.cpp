#include "sdk/sdk.h"

#include "handling/handling.h"

#include "handling/utils/render.h"
#include "handling/utils/netvar.h"

#include "handling/hooks/hooks.h"

bool ShutdownDllHandling( void ) noexcept 
{
#ifdef _DEBUG
	fclose( stdout );
	fclose( stdin );
	FreeConsole( );
#endif

	handling::utils::ShutdownRender( );	
	sdk::interfaces::ShutdownInterfaces( );
	handling::hooks::ShutdownHooks( );
	handling::utils::n_NetvarTree::NetvarTree = nullptr;

	return TRUE;
}

unsigned long __stdcall  RunDllHandling( void* ModuleHandle ) noexcept 
{
#ifdef _DEBUG
	AllocConsole( );
	freopen( ( "CONIN$" ), ( "r" ), stdin );
	freopen( ( "CONOUT$" ), ( "w" ), stdout );
	SetConsoleTitleA( "debug console" );
#endif

	sdk::interfaces::RunInterfaces( );
	handling::hooks::RunHooks( );
	handling::utils::RunRender( );
	handling::utils::n_NetvarTree::Initialize( );

	while ( !GetAsyncKeyState( VK_END ) )
		std::this_thread::sleep_for( std::chrono::milliseconds( 25 ) );

	if ( !ShutdownDllHandling( ) )
		return FALSE;

	FreeLibraryAndExitThread( static_cast< HMODULE >( ModuleHandle ), 0 );


	return TRUE;
}

int __stdcall DllMain( const HMODULE HinstDll, const unsigned long ReasonForCall, const void* Reserved ) {
	if ( HinstDll )
		DisableThreadLibraryCalls( HinstDll );

	if ( ReasonForCall == 1 ) {
		const auto cheat_thread = CreateThread( 0, 0, RunDllHandling, HinstDll, 0, 0 );

		if ( !cheat_thread )
			return 0;

		CloseHandle( cheat_thread );
	}

	return 1;
}