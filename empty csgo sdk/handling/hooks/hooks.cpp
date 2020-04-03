#include "hooks.h"

#include "../utils/render.h"

#include "../../hacks/hacks.h"

#include "../../menu/main/menu.h"

namespace handling {
	namespace hooks {
		std::unique_ptr <handling::utils::vmt_hook> CModeHook;
		std::unique_ptr <handling::utils::vmt_hook> GPanelHook;
		std::unique_ptr <handling::utils::vmt_hook> SurfaceVGUI;

		static bool __fastcall CreateMoveHook( sdk::interfaces::client_mode* thisptr, std::uint32_t* edx, float Time, sdk::classes::user_cmd* Command ) noexcept {
			if ( !Time || !Command || !Command->CommandNumber )
				return false;

			if ( !sdk::interfaces::EngineClient->IsConnected( ) || !sdk::interfaces::EngineClient->IsInGame( ) )
				return false;

			// Run variables
			handling::utils::Command = Command;
			handling::utils::Local = reinterpret_cast< sdk::classes::base_general* >( sdk::interfaces::ClientEntityList->GetClientEntity( sdk::interfaces::EngineClient->GetLocalPlayer( ) ) );

			hacks::misc::OnMove( );

			hacks::aimbot::OnMove( );

			return false;
		}

		static void __fastcall PaintTraverseHook( std::uint32_t* ecx, std::uint32_t* edx, std::uint32_t Panel, bool ForceRepaint, bool AllowForce ) noexcept {
			static auto OriginPaintTraverse = GPanelHook->GetOriginalFunction< decltype( &PaintTraverseHook) > ( handling::hooks::funcs_indexes::paint_traverse ) ;

			static std::uint32_t PanelID;

			// Free the engine
			if ( OriginPaintTraverse )
				OriginPaintTraverse( ecx, edx, Panel, ForceRepaint, AllowForce );

			if ( !PanelID ) {
				if ( !strcmp( "MatSystemTopPanel", sdk::interfaces::GuiPanel->GetPanelName( Panel ) ) )
					PanelID = Panel;
			}

			if ( PanelID == Panel ) {
				hacks::visuals::RunVisuals( );

				menu::draw::DrawMenu( );
			}
		}

		static void __fastcall LockCursorHook( std::uint32_t* ecx, std::uint32_t* edx ) noexcept {
			static auto OriginLockCursor = SurfaceVGUI->GetOriginalFunction< decltype( &LockCursorHook ) >( handling::hooks::funcs_indexes::lock_cursor );

			if ( menu::MenuOpened ) {
				sdk::interfaces::GuiSurface->UnlockCursor( );
				sdk::interfaces::InputSystem->EnableInput( false );
				return;
			}
			else {
				sdk::interfaces::InputSystem->EnableInput( true );
			}
			if ( OriginLockCursor )
				OriginLockCursor( ecx, edx );
		}

		void RunHooks( void ) noexcept {
			CModeHook = std::make_unique <handling::utils::vmt_hook>( );
			CModeHook->Initialize( sdk::interfaces::ClientMode );
			CModeHook->HookFunction( handling::hooks::funcs_indexes::create_move, reinterpret_cast < void* > ( handling::hooks::CreateMoveHook ) );

			GPanelHook = std::make_unique <handling::utils::vmt_hook>( );
			GPanelHook->Initialize( sdk::interfaces::GuiPanel );
			GPanelHook->HookFunction( handling::hooks::funcs_indexes::paint_traverse, reinterpret_cast < void* > ( handling::hooks::PaintTraverseHook ) );

			SurfaceVGUI = std::make_unique <handling::utils::vmt_hook>( );
			SurfaceVGUI->Initialize( sdk::interfaces::GuiSurface );
			SurfaceVGUI->HookFunction( handling::hooks::funcs_indexes::lock_cursor, reinterpret_cast < void* > ( handling::hooks::LockCursorHook ) );

		}

		void ShutdownHooks( void ) noexcept {
			CModeHook->Unhook( );
			GPanelHook->Unhook( );
			SurfaceVGUI->Unhook( );
		}
	};
};
