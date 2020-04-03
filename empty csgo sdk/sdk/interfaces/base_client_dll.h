#pragma once

#include "app_system.h"

#include "../interfaces/global_vars.h"

namespace sdk {
    namespace interfaces {
        // https://github.com/ValveSoftware/source-sdk-2013/blob/master/sp/src/public/cdll_int.h

        class base_client_dll {
        public:
            virtual std::int32_t                Connect(sdk::interfaces::create_interface_fn appSystemFactory, sdk::interfaces::global_vars* pGlobals) = 0;
            virtual std::int32_t                Disconnect(void) = 0;
            virtual std::int32_t                Init(sdk::interfaces::create_interface_fn appSystemFactory, sdk::interfaces::global_vars* pGlobals) = 0;
            virtual void                        PostInit() = 0;
            virtual void                        Shutdown(void) = 0;
            virtual void                        LevelInitPreEntity(char const* pMapName) = 0;
            virtual void                        LevelInitPostEntity() = 0;
            virtual void                        LevelShutdown(void) = 0;
            virtual sdk::classes::client_class* GetAllClasses(void) = 0;
        };
    };
};