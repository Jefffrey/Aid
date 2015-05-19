#pragma once

#include <type_traits>

namespace aid {

    template<typename Class>
    struct is_matrix : std::false_type {};

    template<typename Matrix>
    struct is_vector {
        static constexpr bool value =
            aid::is_matrix<typename std::decay<Matrix>::type>::value
            && ( std::decay<Matrix>::type::col_size == 1 
                 || std::decay<Matrix>::type::row_size == 1 );
    };

    template<typename Matrix>
    struct is_row_vector {
        static constexpr bool value = std::decay<Matrix>::type::col_size == 1;
    };

    template<typename Matrix>
    struct is_col_vector {
        static constexpr bool value = std::decay<Matrix>::type::row_size == 1;
    };

    template<typename Vector>
    struct is_two_dimensional_vector {
        static constexpr bool value =
               is_vector<Vector>::value
            && std::decay<Vector>::type::matrix_size == 2;
    };

    template<typename Vector>
    struct is_three_dimensional_vector {
        static constexpr bool value =
               is_vector<Vector>::value
            && std::decay<Vector>::type::matrix_size == 3;
    };

    template<typename Vector>
    struct is_four_dimensional_vector {
        static constexpr bool value =
               is_vector<Vector>::value
            && std::decay<Vector>::type::matrix_size == 4;
    };

}
