#include <catch/catch.hpp>

#include <aid/bitboard.hpp>

TEST_CASE("aid::bitboard") {

    SECTION("compiles") {
        aid::bitboard<3, 5> b;
    }

}
