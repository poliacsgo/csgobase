#pragma once

#include <Windows.h>
#include <assert.h>
#include <stdio.h>
#include <map>
#include <cstdint>
#include <stdexcept>
#include <memory>

#define NOMINMAX

namespace handling {
	namespace utils {
		namespace detail {
			class protect_guard {
			public:
				protect_guard(void* base, size_t len, std::uint32_t flags) {
					_base = base;
					_length = len;
					if (!VirtualProtect(base, len, flags, (PDWORD)&_old))
						throw std::runtime_error("failed to protect region.");
				}
				~protect_guard() {
					VirtualProtect(_base, _length, _old, (PDWORD)&_old);
				}
			private:
				void* _base;
				size_t _length;
				std::uint32_t _old;
			};
		}

		class vmt_hook {
		public:
			// class initializer
			vmt_hook( );

			// sets up hook and replaces the vtable with new one
			bool Initialize( void* base );

			// hook a specific index ( all index are shifted by one because of rtti )
			bool HookFunction( const std::uint16_t index, void* function );

			// unhook specific index
			bool UnhookFunction( const std::uint16_t index );

			// restore old vtables ( unhook all function )
			bool Unhook( void );

			// get a pointer to the original function given an index
			template <typename T = void*> T GetOriginalFunction( const std::uint16_t index ) {
				return reinterpret_cast< T >( OriginalVmt[ index ] );
			}

		private:
			// calculates the length of the table
			std::uint32_t GetVtableLength( std::uintptr_t* table );

			std::uintptr_t** VMTBase = nullptr;
			std::uint16_t TableLength = 0;
			std::uintptr_t* OriginalVmt = nullptr;
			std::unique_ptr<uintptr_t[ ]> replace_vmt = nullptr;
			DWORD old_protection { };
		};
	};
};