#pragma once

#include <bitset>

namespace aid {

    template<std::size_t Rows, std::size_t Cols>
    class bitboard {
    public:

        using bitset_type   = std::bitset<Rows * Cols>;
        using reference     = bitset_type::reference;

        bitboard() = default;
        bitboard(bitboard const&) = default;

        bitboard(bitboard&&) 
            noexcept(std::is_nothrow_move_constructible(bitset_type)::value)
            = default;

        bitboard& operator=(bitboard const&) = default;

        bitboard& operator=(bitboard&&)
            noexcept(std::is_nothrow_move_assignable(bitset_type)::value)
            = default;

        reference operator()(std::size_t row, std::size_t col) {
            return bitset[row * Cols + col];
        }

        constexpr bool operator()(std::size_t row, std::size_t col) const {
            return bitset[row * Cols + col];
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

        bitboard& operator<<=(std::size_t s) {
            bitset <<= s;
            return (*this);
        }

        bitboard& operator>>=(std::size_t s) {
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

        constexpr std::size_t rows() const { return Rows; }
        constexpr std::size_t columns() const { return Cols; }
        constexpr std::size_t size() const { return Rows * Cols; }
        std::size_t count() const { return bitset.count(); }

        void swap(bitboard& rhs) noexcept {
            bitset.swap(rhs.bitset);
        }

    private:

        std::bitset<Rows * Cols> bitset;

    };

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
