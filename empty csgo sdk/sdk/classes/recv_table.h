#pragma once

#include "../sdk.h"

namespace sdk {
	namespace classes {
		class variant;
		class recv_table;
		class recv_prop;
		class recv_proxy_data;

		using recv_var_proxy_fn = void(*)(const recv_proxy_data* data, void* struct_ptr, void* out_ptr);
		using array_length_recv_proxy_fn = void(*)(void* struct_ptr, std::int32_t object_id, std::int32_t current_array_length);
		using data_table_recv_var_proxy_fn = void(*)(const recv_prop* prop, void** out_ptr, void* data_ptr, std::int32_t object_id);

		enum send_prop_type {
			_int = 0,
			_float,
			_vec,
			_vec_xy,
			_string,
			_array,
			_data_table,
			_int_64,
		};

		class variant {
		public:
			union {
				float m_float;
				long m_int;
				char* m_string;
				void* m_data;
				float m_vector[3];
				__int64 m_int64;
			};

			send_prop_type type;
		};

		class recv_proxy_data {
		public:
			const recv_prop* recv_prop;
			variant value;
			std::int32_t element_index;
			std::int32_t object_id;
		};

		class recv_prop {
		public:
			char* prop_name;
			send_prop_type prop_type;
			std::int32_t prop_flags;
			std::int32_t buffer_size;
			std::int32_t is_inside_of_array;
			const void* extra_data_ptr;
			recv_prop* array_prop;
			array_length_recv_proxy_fn array_length_proxy;
			recv_var_proxy_fn proxy_fn;
			data_table_recv_var_proxy_fn data_table_proxy_fn;
			recv_table* data_table;
			std::int32_t offset;
			std::int32_t element_stride;
			std::int32_t elements_count;
			const char* parent_array_prop_name;
		};

		class recv_table {
		public:
			recv_prop* props;
			std::int32_t props_count;
			void* decoder_ptr;
			char* table_name;
			bool is_initialized;
			bool is_in_main_list;

			inline recv_prop* get_prop(std::int32_t i) {
				return &this->props[i];
			}
		};
	};
};