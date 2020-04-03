#include "aimbot.h"
namespace hacks {
	namespace aimbot {

		void OnMove( ) {
			for ( int i = 0; i < sdk::interfaces::Vars->MaxClients; i++ ) {
				auto player = reinterpret_cast< sdk::classes::base_general* >( sdk::interfaces::ClientEntityList->GetClientEntity( i ) );

				if ( !player || !handling::utils::Local )
					continue;

				if ( !player->IsAlive( ) || player->GunGameImmunity())
					continue;
			
				if ( player->ClientRenderable( )->is_dormant( ) || player == handling::utils::Local )
					continue;

				if ( player->Team( ) == handling::utils::Local->Team( ) )
					continue;

				/* two different functions to enable possibility of customization depending on mode */
				switch ( menu::config::config.AimbotMode ) {
					case 0: RunLegitBot( player ); break;
					case 1: RunRageBot( player ); break;
				}
			}
			if ( menu::config::config.RemoveRecoil ) {
				handling::utils::Command->ViewAngles -= handling::utils::Local->AimPunchAngle( ) * 2.0f;
			}
		}

		void RunLegitBot( sdk::classes::base_general* player ) {
			if ( !handling::utils::Local )
				return;

			sdk::math::vector_3d LocalEyePos = handling::utils::Local->GetBonePosition( 8 );
			sdk::math::vector_3d PlayerEyePos = player->GetBonePosition( 8 );

			sdk::math::vector_3d AimAngle = math::main::CalculateAngle( LocalEyePos, PlayerEyePos );

			float FieldOfView = math::main::CalculateDistance( handling::utils::Command->ViewAngles, AimAngle );
			if ( FieldOfView > menu::config::config.FOV || AimAngle == sdk::math::vector_3d(0, 0, 0))
				return;

			if ( handling::utils::Command->Buttons & sdk::classes::cmd_buttons::in_attack ) 
			{
				AimAngle.Clamp( );

				handling::utils::Command->ViewAngles = AimAngle;
			}
		}

		void RunRageBot( sdk::classes::base_general* player ) {
			if ( !handling::utils::Local )
				return;

			sdk::math::vector_3d LocalEyePos = handling::utils::Local->GetBonePosition( 8 );
			sdk::math::vector_3d PlayerEyePos = player->GetBonePosition( 8 );

			sdk::math::vector_3d AimAngle = math::main::CalculateAngle( LocalEyePos, PlayerEyePos );

			int FieldOfView = math::main::CalculateDistance( handling::utils::Command->ViewAngles, AimAngle );
			if ( FieldOfView > menu::config::config.FOV || AimAngle == sdk::math::vector_3d( 0, 0, 0 ) )
				return;

			AimAngle.Clamp( );

			handling::utils::Command->ViewAngles = AimAngle;

			if ( !( handling::utils::Command->Buttons & sdk::classes::cmd_buttons::in_attack ) && menu::config::config.Autoshoot ) 
			{
				handling::utils::Command->Buttons |= sdk::classes::cmd_buttons::in_attack;
			}
		}
	}
}