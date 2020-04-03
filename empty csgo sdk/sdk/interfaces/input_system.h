#pragma once
#include "../sdk.h"
#include "../../handling/utils/memory.h"
class input_system {
public:
	void EnableInput( bool enable ) {
		typedef void( __thiscall* OFn )( PVOID, bool );
		return handling::memory::ScanVFunction <OFn>( this, 11 )( this, enable );
	}
};