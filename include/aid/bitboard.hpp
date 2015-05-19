#pragma once

#include <bitset>

namespace aid {

    template<std::size_t Rows, std::size_t Cols>
    class bitboard {
    public:

        using array_type        = std::bitset<Rows * Cols>;
        using value_type        = typename array_type::value_type;
        using reference         = typename array_type::reference;
        using const_reference   = typename array_type::const_reference;
        using size_type         = typename array_type::size_type;
        using iterator          = typename array_type::iterator;
        using const_iterator    = typename array_type::const_iterator;

        static constexpr std::size_t col_size       = Rows;
        static constexpr std::size_t row_size       = Cols;
        static constexpr std::size_t matrix_size    = Rows * Cols;

        bitboard() = default;
        bitboard(bitboard&&) = default;
        bitboard(bitboard const&) = default;
        bitboard& operator=(bitboard&&) = default;
        bitboard& operator=(bitboard const&) = default;

        reference operator()(std::size_t row, std::size_t col) {
            return bitset[row * Cols + col];
        }

        constexpr bool operator()(std::size_t row, std::size_t col) const {
            return bitset[row * Cols + col];
        }

        typename std::enable_if<
            is_vector<bitboard>::value,
            reference 
        >::type operator[](size_type i) {
            return bitset[i];
        }

        typename std::enable_if<
            is_vector<bitboard>::value,
            const_reference 
        >::type operator[](size_type i) const {
            return bitset[i];
        }

        bitboard& operator&=(bitboard const& rhs) {
            bitset &= rhs.bitset;
            return (*this);
        }

        bitboard& operator|=(bitboard const& rhs) {
            bitset |= rhs.bitset;
            return (*this);
        }

        bitboard& operator^=(bitboard const& rhs) {
            bitset ^= rhs.bitset;
            return (*this);
        }

        typename std::enable_if<
            is_row_vector<bitboard>::value,
            bitboard&
        >::type operator<<=(std::size_t s) {
            bitset <<= s;
            return (*this);
        }

        typename std::enable_if<
            is_row_vector<bitboard>::value,
            bitboard&
        >::type operator>>=(std::size_t s) {
            bitset >>= s;
            return (*this);
        }
        
        void reset() { bitset.reset(); }
        void flip() { bitset.flip(); }

        bitboard operator~() const {
            bitboard ret(*this);
            ret.bitset = ~ret.bitset;
            return ret;
        }

        bool operator==(bitboard const& rhs) const { return bitboard == rhs.bitboard; }
        bool operator!=(bitboard const& rhs) const { return !((*this) == rhs); }

        bool all() const { return bitset.all(); }
        bool none() const { return bitset.none(); }
        bool any() const { return bitset.any(); }

        constexpr size_type rows() const { return Rows; }
        constexpr size_type columns() const { return Cols; }
        constexpr size_type size() const { return Rows * Cols; }
        size_type count() const { return bitset.count(); }
        constexpr bool empty() const { return size() == 0; }

        void swap(bitboard& rhs) noexcept {
            bitset.swap(rhs.bitset);
        }

    private:

        array_type bitset;

    };

    template<std::size_t Rows, std::size_t Cols>
    struct is_matrix<aid::bitboard<Rows, Cols>> : std::true_type {};

    template<std::size_t Rows, std::size_t Cols>
    bitboard<Rows, Cols> operator<<(bitboard<Rows, Cols> lhs, std::size_t s) {
        return lhs <<= s;
    }

    template<std::size_t Rows, std::size_t Cols>
    bitboard<Rows, Cols> operator>>(bitboard<Rows, Cols> lhs, std::size_t s) {
        return lhs >>= s;
    }

    template<std::size_t Rows, std::size_t Cols>
    bitboard<Rows, Cols> operator&(bitboard<Rows, Cols> lhs, bitboard<Rows, Cols> const& rhs) {
        return lhs &= rhs;
    }

    template<std::size_t Rows, std::size_t Cols>
    bitboard<Rows, Cols> operator|(bitboard<Rows, Cols> lhs, bitboard<Rows, Cols> const& rhs) {
        return lhs |= rhs;
    }

    template<std::size_t Rows, std::size_t Cols>
    bitboard<Rows, Cols> operator^(bitboard<Rows, Cols> lhs, bitboard<Rows, Cols> const& rhs) {
        return lhs ^= rhs;
    }

}
