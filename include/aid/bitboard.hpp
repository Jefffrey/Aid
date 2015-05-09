#pragma once

#include <bitset>

namespace aid {

    template<std::size_t Rows, std::size_t Cols>
    class bitboard {
    public:

        // aliases
        using bitboard_type = bitboard<Rows, Cols>;
        using reference     = bitboard_type::reference;

        // constructors
        bitboard() = default;
        bitboard(bitboard_type const&) = default;
        bitboard(bitboard_type&&) = default;

        // assignment
        bitboard_type& operator=(bitboard_type const&) = default;
        bitboard_type& operator=(bitboard_type&&) = default;

        // element access
        reference operator()(std::size_t row, std::size_t col) {
            return bitset[row * Cols + col];
        }

        constexpr bool operator()(std::size_t row, std::size_t col) const {
            return bitset[row * Cols + col];
        }

        // bitwise operations
        bitboard_type& operator&=(bitboard_type const& rhs) {
            bitset &= rhs.bitset;
            return (*this);
        }

        bitboard_type& operator|=(bitboard_type const& rhs) {
            bitset |= rhs.bitset;
            return (*this);
        }

        bitboard_type& operator^=(bitboard_type const& rhs) {
            bitset ^= rhs.bitset;
            return (*this);
        }

        bitboard_type& operator<<=(std::size_t s) {
            bitset <<= s;
            return (*this);
        }

        bitboard_type& operator>>=(std::size_t s) {
            bitset >>= s;
            return (*this);
        }
        
        void reset() { bitset.reset(); }
        void flip() { bitset.flip(); }

        bitboard_type operator~() const {
            bitboard_type ret(*this);
            ret.bitset = ~ret.bitset;
            return ret;
        }

        // equality & inequality
        bool operator==(bitboard_type const& rhs) const { return bitboard == rhs.bitboard; }
        bool operator!=(bitboard_type const& rhs) const { return !((*this) == rhs); }

        // bit query
        bool all() const { return bitset.all(); }
        bool none() const { return bitset.none(); }
        bool any() const { return bitset.any(); }

        // size
        constexpr std::size_t rows() const { return Rows; }
        constexpr std::size_t columns() const { return Cols; }
        constexpr std::size_t size() const { return Rows * Cols; }
        std::size_t count() const { return bitset.count(); }

    private:

        std::bitset<Rows * Cols> bitset;

    };

    // bitwise non member operators
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
