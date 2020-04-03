#pragma once

#include "../../sdk/interfaces/interfaces.h"

namespace handling {
	namespace utils {
		class CNetvarTree {
			struct node_t;

			using MapType = std::unordered_map< std::string, std::shared_ptr< node_t > >;

			struct node_t {
				node_t( int offset ) : offset( offset ) { }

				MapType nodes;

				int offset;
			};

			MapType nodes { };
		public:
			CNetvarTree( );

			bool Init( void );

			template < typename... T > int GetOffset( const char* name, T ... args ) {
				if ( name != nullptr ) {
					auto& node = nodes[ name ];

					if ( node != nullptr ) {
						return GetOffsetRecursive( node->nodes, node->offset, args... );
					}
				}
			}

		private:

			void PopulateNodes( sdk::classes::recv_table* recv_table, MapType* map, std::ofstream& file );

			static int GetOffsetRecursive( MapType& map, int acc, const char* name ) {
				return acc + map[ name ]->offset;
			}

			template < typename... T > int GetOffsetRecursive( MapType& map, int acc, const char* name, T ... args ) {
				auto& node = map[ name ];

				return GetOffsetRecursive( node->nodes, acc + node->offset, args... );
			}
		};

		namespace n_NetvarTree {
			extern std::unique_ptr< CNetvarTree > NetvarTree;

			void Initialize( void );
		}
	};
};