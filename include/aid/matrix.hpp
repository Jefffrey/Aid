#pragma once

#include <array>
#include <initializer_list>
#include <algorithm>
#include <type_traits>

#include <aid/matrix_traits.hpp>

namespace aid {

    // Very simple matrix class for very small 2x2, 3x3, 4x4 matrixes
    // or 2, 3, 4-dimensional vectors.
    template<
        typename ValueType, 
        std::size_t Rows, std::size_t Cols = Rows>
    class matrix {
    public:

        using matrix_type = matrix<ValueType, Rows, Cols>;
        using array_type  = std::array<ValueType, Rows * Cols>;

        using value_type        = typename array_type::value_type;
        using reference         = typename array_type::reference;
        using const_reference   = typename array_type::const_reference;
        using size_type         = typename array_type::size_type;
        using iterator          = typename array_type::iterator;
        using const_iterator    = typename array_type::const_iterator;

        static constexpr std::size_t col_size = Rows;
        static constexpr std::size_t row_size = Cols;
        static constexpr std::size_t matrix_size = Rows * Cols;

        // constructors
        matrix() = default;

        explicit matrix(value_type elem) {
            std::fill(array.begin(), array.end(), elem);
        }

        // @todo: add generator constructor

        explicit matrix(std::initializer_list<value_type> const& list) {
            std::copy(list.begin(), list.end(), array.begin());
        }

        matrix(matrix_type const&)  = default;
        matrix(matrix_type&&)       = default;

        // These iterators are not guaranteed to have any specific
        // order. The only guarantee is that every element is accessed
        // only once and the order in which elements are accessed is the
        // same for matrix of equal dimensions.
        iterator begin() { return array.begin(); }
        const_iterator begin() const { return array.begin(); }
        const_iterator cbegin() const { return array.cbegin(); }

        iterator end() { return array.end(); }
        const_iterator end() const { return array.end(); }
        const_iterator cend() const { return array.end(); }

        iterator rbegin() { return array.rbegin(); }
        const_iterator rbegin() const { return array.rbegin(); }
        const_iterator crbegin() const { return array.crbegin(); }

        iterator rend() { return array.rend(); }
        const_iterator rend() const { return array.rend(); }
        const_iterator crend() const { return array.crend(); }

        // @todo: add row major and col major iterators

        // element access
        reference operator()(size_type row, size_type col) noexcept {
            return array[row * Cols + col];
        }

        const_reference operator()(size_type row, size_type col) const noexcept {
            return array[row * Cols + col];
        }

        reference operator[](size_type i) noexcept {
            static_assert
                ( aid::is_vector<matrix_type>::value
                , "member function `operator[]` is only available for vectors" );
            return array[i];
        }

        const_reference operator[](size_type i) const noexcept {
            static_assert
                ( aid::is_vector<matrix_type>::value
                , "member function `operator[]` is only available for vectors" );
            return array[i];
        }

        // underlying data access
        value_type* data() { return array.data(); }
        value_type const* data() const { return array.data(); }
        
        // size informations
        constexpr size_type size() const noexcept { 
            return Rows * Cols;
        }

        constexpr size_type max_size() const noexcept {
            return Rows * Cols; 
        }

        constexpr bool empty() const noexcept {
            return (Rows * Cols == 0);
        }

        // swap algorithms
        void swap(matrix_type& other) noexcept {
            array.swap(other.array); 
        }

        // copy and move assignment
        matrix_type& operator=(matrix_type const&)    = default;
        matrix_type& operator=(matrix_type&&)         = default;

        // equality operators
        bool operator==(matrix_type const& rhs) const {
            return std::equal(array.begin(), array.end(), rhs.array.begin());
        }

        bool operator!=(matrix_type const& rhs) const {
            return !((*this) == rhs);
        }

    private:

        array_type array; 

    };

    template<typename ValueType, std::size_t Cols>
    using row_vector = matrix<ValueType, 1, Cols>;

    template<typename ValueType, std::size_t Rows>
    using col_vector = matrix<ValueType, Rows, 1>;

}
