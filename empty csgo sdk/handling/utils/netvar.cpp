#include "netvar.h"
#include <fstream>

namespace handling {
	namespace utils {
		CNetvarTree::CNetvarTree( ) {

		}

		bool CNetvarTree::Init( void ) {
			if ( !sdk::interfaces::ClientDll )
				return false;

			sdk::classes::client_class* client_class = sdk::interfaces::ClientDll->GetAllClasses( );

			if ( !client_class )
				return false;

			std::ofstream output = std::ofstream( "netvars_dump.txt" );

			while ( client_class != nullptr ) {
				auto class_info = std::make_shared< node_t >( 0 );

				auto recv_table = client_class->recvtable_ptr;

				PopulateNodes( recv_table, &class_info->nodes, output );

				nodes.emplace( recv_table->table_name, class_info );

				client_class = client_class->next_ptr;
			}

			return true;
		}

		void CNetvarTree::PopulateNodes( sdk::classes::recv_table* recv_table, MapType* map, std::ofstream& file ) {
			for ( auto i = 0; i < recv_table->props_count; i++ ) {
				sdk::classes::recv_prop* prop = &recv_table->props[ i ];

				auto prop_info = std::make_shared< node_t >( prop->offset );

				if ( prop->prop_type == 6 )
					PopulateNodes( prop->data_table, &prop_info->nodes, file );

				map->emplace( prop->prop_name, prop_info );
			}
		}

		namespace n_NetvarTree {
			std::unique_ptr< CNetvarTree > NetvarTree;

			void Initialize( void ) {
				NetvarTree = std::make_unique< CNetvarTree >( );

				NetvarTree->Init( );
			}
		}
	};
};