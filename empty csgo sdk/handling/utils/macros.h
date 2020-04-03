#pragma once

#include "netvar.h"

#define get_netvar( func_name, type, ... ) \
	type& func_name { \
		return *reinterpret_cast <type*> ( reinterpret_cast <std::uintptr_t> ( this ) + handling::utils::n_NetvarTree::NetvarTree->GetOffset( __VA_ARGS__ ) ); \
	};

#define time_to_ticks(dt) ((std::int32_t)( 0.5f + (float)(dt) / sdk::interfaces::Vars->IntervalPerTick))
#define time_to_time(t) (sdk::interfaces::Vars->IntervalPerTick * (t))