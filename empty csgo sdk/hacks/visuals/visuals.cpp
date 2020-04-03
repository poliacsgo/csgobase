#include "visuals.h"

namespace hacks {
	namespace visuals {
		void RunVisuals( ) {

			for ( int i = 0; i < sdk::interfaces::Vars->MaxClients; i++ ) {
				auto player = reinterpret_cast< sdk::classes::base_general* >( sdk::interfaces::ClientEntityList->GetClientEntity( i ) );

				if ( !player || player == handling::utils::Local )
					continue;

				if ( player->ClientRenderable( )->is_dormant( ) || !player->IsAlive( ) )
					continue;

				if ( player->Team( ) == handling::utils::Local->Team( ) )
					continue;

				sdk::interfaces::player_info_t info;
				sdk::interfaces::EngineClient->GetPlayerInfo( player->ClientRenderable( )->ent_index( ), &info );

				sdk::structs::rect_t box;
				if ( !BoundingBox( player, box ) ) 
					continue;

				if ( menu::config::config.Box )
					DrawBox( box );

				if ( menu::config::config.Health )
					DrawHealth( player, box );

				if ( menu::config::config.Name )
					DrawName( info, box );
			}
		}

		void DrawName( sdk::interfaces::player_info_t info, sdk::structs::rect_t& box ) {
			handling::utils::RenderText( box.x + ( box.w / 2 ) - 7, box.y - 11, sdk::classes::color( 255, 255, 255 ), handling::utils::VisualFont, info.szName );
		}

		void DrawBox( sdk::structs::rect_t& box ) {
			handling::utils::RenderOutlinedRectangleDX( box.x - 1, box.y - 1, box.right( ) + 1, box.bottom( ) + 1, sdk::classes::color( 0, 0, 0, 160 ) );
			handling::utils::RenderOutlinedRectangleDX( box.x, box.y, box.right(), box.bottom(), sdk::classes::color( 255, 255, 255 ) );
			handling::utils::RenderOutlinedRectangleDX( box.x + 1, box.y + 1, box.right( ) - 1, box.bottom( ) - 1, sdk::classes::color( 0, 0, 0, 160 ) );
		}

		void DrawHealth( sdk::classes::base_general* player, sdk::structs::rect_t& box ) {
			handling::utils::RenderText( box.right( ) + 2, box.y, sdk::classes::color( 255, 255, 255 ), handling::utils::VisualFont, "Health: " + std::to_string( player->Health( ) ));
		}

		bool BoundingBox( sdk::classes::base_general* player, sdk::structs::rect_t& box ) {

			const sdk::math::vector_3d flb {}, brt {}, blb {}, frt {}, frb {}, brb {}, blt {}, flt {}, out {};

			const sdk::math::vector_3d origin = player->Origin( );
			const sdk::math::vector_3d mins = player->GetCollideable( )->OBBMins( ) + origin;
			const sdk::math::vector_3d maxs = player->GetCollideable( )->OBBMaxs( ) + origin;

			sdk::math::vector_3d points[ ] = {
				sdk::math::vector_3d( mins.x, mins.y, mins.z ),
				sdk::math::vector_3d( mins.x, maxs.y, mins.z ),
				sdk::math::vector_3d( maxs.x, maxs.y, mins.z ),
				sdk::math::vector_3d( maxs.x, mins.y, mins.z ),
				sdk::math::vector_3d( maxs.x, maxs.y, maxs.z ),
				sdk::math::vector_3d( mins.x, maxs.y, maxs.z ),
				sdk::math::vector_3d( mins.x, mins.y, maxs.z ),
				sdk::math::vector_3d( maxs.x, mins.y, maxs.z )
			};

			sdk::math::vector_3d scr_array[ ] = { blb, brb, frb, flb, frt, brt, blt, flt };

			for ( auto i = 0; i <= 7; ++i )
				if ( sdk::interfaces::DebugOverlay->world_to_screen( points[ i ], scr_array[ i ] ) )
					return false;

			auto left = scr_array[ 3 ].x, right = scr_array[ 3 ].x, top = scr_array[ 3 ].y, bottom = scr_array[ 3 ].y;

			for ( auto i = 0; i <= 7; i++ )
			{
				if ( top > scr_array[ i ].y )
					top = scr_array[ i ].y;

				if ( bottom < scr_array[ i ].y )
					bottom = scr_array[ i ].y;

				if ( left > scr_array[ i ].x )
					left = scr_array[ i ].x;

				if ( right < scr_array[ i ].x )
					right = scr_array[ i ].x;
			}

			box.x = left;
			box.y = top;
			box.w = right - left;
			box.h = bottom - top;

			return true;

		}

	}
}