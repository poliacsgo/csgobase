#pragma once

namespace sdk {
	namespace interfaces {
        // https://github.com/pmrowla/hl2sdk-csgo/blob/master/public/globalvars_base.h

        class global_vars {
        public:
            float          RealTime;
            std::int32_t   FrameCount;
            float          AbsoluteFrameTime;
            float          AbsoluteFrameStartTimestddev;
            float          CurrentTime;
            float          FrameTime;
            std::int32_t   MaxClients;
            std::int32_t   TickCount;
            float          IntervalPerTick;
            float          InterpolationAmount;
            std::int32_t   SimTicksThisFrame;
            std::int32_t   NetworkProtocol;
            void*          SaveData;
            bool           Client;
            bool           RemoteClient;
        private:
            // 100 (i.e., tickcount is rounded down to this base and then the "delta" from this base is networked
            std::int32_t   TimestampNetworkingBase;
            // 32 (entindex() % nTimestampRandomizeWindow ) is subtracted from gpGlobals->tickcount to set the networking basis, prevents
            //  all of the entities from forcing a new PackedEntity on the same tick (i.e., prevents them from getting lockstepped on this)
            std::int32_t   TimestampRandomizeWindow;
        };
	};
};