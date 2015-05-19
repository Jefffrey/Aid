#pragma once

#include <algorithm>
#include <functional>

#include <aid/matrix.hpp> 
#include <aid/matrix_traits.hpp>

namespace aid {

    template<typename Vector>
    auto x(Vector&& vec) {
        static_assert
            ( aid::is_two_dimensional_vector<Vector>::value
            || aid::is_three_dimensional_vector<Vector>::value
            || aid::is_four_dimensional_vector<Vector>::value
            , "function `x` is only available for 2/3/4 dimensional vectors" );
        return vec[0];
    }

    template<typename Vector>
    auto y(Vector&& vec) {
        static_assert
            (  aid::is_two_dimensional_vector<Vector>::value
            || aid::is_three_dimensional_vector<Vector>::value
            || aid::is_four_dimensional_vector<Vector>::value
            , "function `y` is only available for 2/3/4 dimensional vectors" );
        return vec[1];
    }

    template<typename Vector>
    auto z(Vector&& vec) {
        static_assert
            (  aid::is_three_dimensional_vector<Vector>::value
            || aid::is_four_dimensional_vector<Vector>::value
            , "function `z` is only available for 3/4 dimensional vectors" );
        return vec[2];
    }

    template<typename Vector>
    auto w(Vector&& vec) {
        static_assert
            ( aid::is_four_dimensional_vector<Vector>::value
            , "function `w` is only available for 4 dimensional vectors" );
        return vec[3];
    }

    template<typename Matrix>
    typename std::enable_if<
        is_matrix<Matrix>::value,
        Matrix
    >::type operator-(Matrix mat) {
        std::transform(mat.begin(), mat.end(), mat.begin(), std::negate<void>());
        return mat;
    }

    template<typename Matrix>
    typename std::enable_if<
        is_matrix<Matrix>::value,
        Matrix&
    >::type operator+=(Matrix& lhs, Matrix const& rhs) {
        std::transform(lhs.begin(), lhs.end(), rhs.begin(), lhs.begin(), std::plus<void>());
        return lhs;
    }

    template<typename Matrix>
    typename std::enable_if<
        is_matrix<Matrix>::value,
        Matrix
    >::type operator+(Matrix lhs, Matrix const& rhs) {
        return lhs += rhs;
    }

    template<typename Matrix>
    typename std::enable_if<
        is_matrix<Matrix>::value,
        Matrix&
    >::type operator-=(Matrix& lhs, Matrix const& rhs) {
        std::transform(lhs.begin(), lhs.end(), rhs.begin(), lhs.begin(), std::minus<void>());
        return lhs;
    }

    template<typename Matrix>
    typename std::enable_if<
        is_matrix<Matrix>::value,
        Matrix
    >::type operator-(Matrix lhs, Matrix const& rhs) {
        return lhs -= rhs;
    }

    template<typename Matrix, typename ScalarType>
    typename std::enable_if<
        is_matrix<Matrix>::value,
        Matrix&
    >::type operator*=(Matrix& lhs, ScalarType const& rhs) {
        using namespace std::placeholders;
        std::transform(lhs.begin(), lhs.end(), lhs.begin(), std::bind(std::multiplies<void>(), _1, rhs));
        return lhs;
    }

    template<typename Matrix, typename ScalarType>
    typename std::enable_if<
        is_matrix<Matrix>::value,
        Matrix
    >::type operator*(Matrix lhs, ScalarType const& rhs) {
        return lhs *= rhs;
    }

    template<typename Matrix, typename ScalarType>
    typename std::enable_if<
        is_matrix<Matrix>::value,
        Matrix
    >::type operator*(ScalarType const& lhs, Matrix rhs) {
        return rhs *= lhs;
    }

    template<typename Matrix, typename ScalarType>
    typename std::enable_if<
        is_matrix<Matrix>::value,
        Matrix&
    >::type operator/=(Matrix& lhs, ScalarType const& rhs) {
        using namespace std::placeholders;
        std::transform(lhs.begin(), lhs.end(), lhs.begin(), std::bind(std::divides<void>(), _1, rhs));
        return lhs;
    }

    template<typename Matrix, typename ScalarType>
    typename std::enable_if<
        is_matrix<Matrix>::value,
        Matrix
    >::type operator/(Matrix lhs, ScalarType const& rhs) {
        return lhs /= rhs;
    }

}
