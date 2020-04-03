#include "vmt.h"

namespace handling {
	namespace utils {
		vmt_hook::vmt_hook( ) {

		}

		bool vmt_hook::Initialize( void* base ) {
			if ( !base )
				return false;

			VMTBase = static_cast< std::uintptr_t** >( base );

			if ( !VMTBase )
				return false;

			OriginalVmt = *VMTBase;

			if ( !OriginalVmt )
				return false;

			VirtualProtect( VMTBase, sizeof( std::uintptr_t ), PAGE_READWRITE, &old_protection );

			TableLength = GetVtableLength( OriginalVmt );

			if ( !TableLength )
				return false;

			replace_vmt = std::make_unique<std::uintptr_t[ ]>( TableLength + 1 );

			if ( !replace_vmt )
				return false;

			std::memset( replace_vmt.get( ), 0, TableLength * sizeof( std::uintptr_t ) + sizeof( std::uintptr_t ) );
			std::memcpy( &replace_vmt[ 1 ], OriginalVmt, TableLength * sizeof( std::uintptr_t ) );
			std::memcpy( replace_vmt.get( ), &OriginalVmt[ -1 ], sizeof( std::uintptr_t ) );

			*VMTBase = &replace_vmt[ 1 ];

			return true;
		}

		bool vmt_hook::HookFunction( const std::uint16_t index, void* function ) {
			if ( !replace_vmt || index < 0 || index > TableLength )
				return false;

			replace_vmt[ index + 1 ] = reinterpret_cast< std::uintptr_t >( function );

			return true;
		}

		bool vmt_hook::UnhookFunction( const std::uint16_t index ) {
			if ( !OriginalVmt || !replace_vmt || index < 0 || index > TableLength )
				return false;

			replace_vmt[ index + 1 ] = OriginalVmt[ index ];

			return true;
		}

		bool vmt_hook::Unhook( void ) {
			if ( !OriginalVmt )
				return false;

			VirtualProtect( VMTBase, sizeof( std::uintptr_t ), PAGE_READWRITE, &old_protection );
			*VMTBase = OriginalVmt;

			OriginalVmt = nullptr;

			return true;
		}

		std::uint32_t vmt_hook::GetVtableLength( std::uintptr_t* table ) {
			std::uintptr_t length = std::uintptr_t { };

			// walk through every function until it is no longer valid
			for ( length = 0; table[ length ]; length++ )
				if ( IS_INTRESOURCE( table[ length ] ) )
					break;

			return length;
		}
	};
};