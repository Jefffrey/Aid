#pragma once

#include <array>

namespace aid {

    namespace detail {

        template<typename Type, std::size_t First, std::size_t... Rest>
        struct multi_array {
            using type = std::array<typename multi_array<Type, Rest...>::type, First>;
        };

        template<typename Type, std::size_t First>
        struct multi_array<Type, First> {
            using type = std::array<Type, First>;
        };

    }

    template<typename Type, std::size_t... Ns>
    using multi_array = typename detail::multi_array<Type, Ns...>::type;

}
