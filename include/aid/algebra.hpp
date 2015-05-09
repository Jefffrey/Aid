#pragma once

#include <aid/matrix.hpp> 
#include <aid/matrix_traits.hpp>

namespace aid {

    template<typename Vector>
    auto x(Vector&& vec) -> decltype(vec[0]) {
        static_assert
            ( aid::is_two_dimensional_vector<Vector>::value
            || aid::is_three_dimensional_vector<Vector>::value
            || aid::is_four_dimensional_vector<Vector>::value
            , "function `x` is only available for 2/3/4 dimensional vectors" );
        return vec[0];
    }

    template<typename Vector>
    auto y(Vector&& vec) -> decltype(vec[1]) {
        static_assert
            (  aid::is_two_dimensional_vector<Vector>::value
            || aid::is_three_dimensional_vector<Vector>::value
            || aid::is_four_dimensional_vector<Vector>::value
            , "function `y` is only available for 2/3/4 dimensional vectors" );
        return vec[1];
    }

    template<typename Vector>
    auto z(Vector&& vec) -> decltype(vec[2]) {
        static_assert
            (  aid::is_three_dimensional_vector<Vector>::value
            || aid::is_four_dimensional_vector<Vector>::value
            , "function `z` is only available for 3/4 dimensional vectors" );
        return vec[2];
    }

    template<typename Vector>
    auto w(Vector&& vec) -> decltype(vec[3]) {
        static_assert
            ( aid::is_four_dimensional_vector<Vector>::value
            , "function `w` is only available for 4 dimensional vectors" );
        return vec[3];
    }

}
