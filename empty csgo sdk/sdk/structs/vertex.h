#pragma once

#include "../math/vector_2d.h"

namespace sdk {
    namespace structs {
        struct vertex {
            vertex() {}

            vertex(const sdk::math::vector_2d& pos, const sdk::math::vector_2d& coord = sdk::math::vector_2d(0, 0)) {
                position = pos;
                texcoord = coord;
            }

            void Init(const sdk::math::vector_2d& pos, const sdk::math::vector_2d& coord = sdk::math::vector_2d(0, 0)) {
                position = pos;
                texcoord = coord;
            }

            sdk::math::vector_2d position;
            sdk::math::vector_2d texcoord;
        };
    };
};