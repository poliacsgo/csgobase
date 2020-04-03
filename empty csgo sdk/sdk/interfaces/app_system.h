#pragma once

#include "../sdk.h"

namespace sdk {
	namespace interfaces {
		typedef void* (*create_interface_fn)(const char* p_name, std::int32_t* p_code);

		class app_system {
		public:
			virtual bool                            Connect(create_interface_fn factory) = 0;
			virtual void                            Disconnect() = 0;
			virtual void*							QueryInterface(const char* p_interface_name) = 0;
			virtual std::int32_t					Init() = 0;
			virtual void                            Shutdown() = 0;
			virtual const void*						GetDependencies() = 0;
			virtual std::int32_t					GetTier() = 0;
			virtual void                            Reconnect(create_interface_fn factory, const char* p_interface_name) = 0;
			virtual void                            UnkFunc() = 0;
		};
	};
};