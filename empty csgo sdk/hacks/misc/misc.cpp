#pragma once

#include "misc.h"

namespace hacks {
	namespace misc {
		namespace movement {
			void DuckLimitBypass( )  {
				handling::utils::Command->Buttons |= sdk::classes::cmd_buttons::in_bullrush;
			}
			void AutoStrafe( ) {
				if ( !menu::config::config.AutoStrafe )
					return;

				if ( !handling::utils::Local || !handling::utils::Local->Health( ) )
					return;


				if ( !( handling::utils::Local->Flags( ) & sdk::classes::entity_flags::fl_onground ) ) {
					if ( handling::utils::Command->MousedX < 0 )
						handling::utils::Command->SideMove = -450.0f;
					if ( handling::utils::Command->MousedX > 0 )
						handling::utils::Command->SideMove = 450.0f;
				}
			}
			void BunnyHop( ) {

				if ( !menu::config::config.Bunnyhop )
					return;

				if ( !handling::utils::Local || !handling::utils::Local->Health( ) )
					return;
	
				if ( !( handling::utils::Command->Buttons & sdk::classes::cmd_buttons::in_jump ) )
					return;


				/* super basic bunnyhop */
				handling::utils::Command->Buttons &= ~sdk::classes::cmd_buttons::in_jump;

				if ( handling::utils::Local->Flags( ) & sdk::classes::entity_flags::fl_onground )
				{
					handling::utils::Command->Buttons |= sdk::classes::cmd_buttons::in_jump;
				}

			}

			void OnMove( )  {
				movement::BunnyHop( );

				movement::AutoStrafe( );

				movement::DuckLimitBypass( );
			}
		}
		void OnMove( ) {
			movement::OnMove( );
		}
	};
};
