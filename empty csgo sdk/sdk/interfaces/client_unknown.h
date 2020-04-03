#pragma once
#include "../sdk.h"

namespace sdk {
	namespace interfaces {
		class client_thinkable;
		class client_alpha_property;

		class client_networkable;
		class client_unknown;
		class base_general;

		class client_renderable;

		using C_BaseHandle = unsigned long;

		class handle_entity
		{
		public:
			virtual ~handle_entity( ) {}
			virtual void SetRefEHandle( const C_BaseHandle& handle ) = 0;
			virtual const C_BaseHandle& GetRefEHandle( ) const = 0;
		};

		class collideable
		{
		public:
			virtual handle_entity* GetEntityHandle( ) = 0;
			virtual sdk::math::vector_3d& OBBMins( ) const = 0;
			virtual sdk::math::vector_3d& OBBMaxs( ) const = 0;
		};

		class client_unknown : public handle_entity
		{
		public:
			virtual collideable* GetCollideable( ) = 0;
			virtual client_networkable* GetClientNetworkable( ) = 0;
			virtual client_renderable* GetClientRenderable( ) = 0;
			virtual base_general* GetIClientEntity( ) = 0;
			virtual base_general* GetBaseEntity( ) = 0;
			virtual client_thinkable* GetClientThinkable( ) = 0;
			virtual client_alpha_property* GetClientAlphaProperty( ) = 0;
		};
	};
};