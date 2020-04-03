#pragma once

#include "../sdk.h"

namespace sdk {
	namespace interfaces {
		class client_networkable;
		class client_unknown;
		class base_general;

		using C_BaseHandle = unsigned long;

		class client_entity_list {
		public:
			virtual client_networkable*		GetClientNetworkable(int ent_num) = 0;
			virtual client_networkable*		GetClientNetworkableFromHandle(uint32_t ent) = 0;
			virtual client_unknown*			GetClientUnknownFromHandle(uint32_t ent) = 0;
			virtual base_general*			GetClientEntity(int ent_num) = 0;
			virtual base_general*			GetClientEntityFromHandle(C_BaseHandle ent) = 0;
			virtual int32_t					NumberOfEntities(bool include_non_networkable) = 0;
			virtual int32_t					GetHighestEntityIndex(void) = 0;
			virtual void					SetMaxEntities(int max_ents) = 0;
			virtual int32_t					GetMaxEntities() = 0;
		};
	};
};