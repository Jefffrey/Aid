#include <catch/catch.hpp>

#include <aid/bitboard.hpp>

TEST_CASE("aid::bitboard") {

    SECTION("constructors") {
        std::string str = 
            "01001"
            "01111"
            "11010";

        aid::bitboard<3, 5> a(str);
        REQUIRE(a(0, 0) == false);
        REQUIRE(a(0, 1) == true);
        REQUIRE(a(0, 2) == false);
        REQUIRE(a(0, 3) == false);
        REQUIRE(a(0, 4) == true);
        REQUIRE(a(1, 0) == false);
        REQUIRE(a(1, 1) == true);
        REQUIRE(a(1, 2) == true);
        REQUIRE(a(1, 3) == true);
        REQUIRE(a(1, 4) == true);
        REQUIRE(a(2, 0) == true);
        REQUIRE(a(2, 1) == true);
        REQUIRE(a(2, 2) == false);
        REQUIRE(a(2, 3) == true);
        REQUIRE(a(2, 4) == false);

        aid::bitboard<3, 5> b(str.data());
        REQUIRE(b == a);

        aid::bitboard<3, 5> c = b;
        REQUIRE(c == b);
        REQUIRE(c == a);

        auto d = std::move(c);
        REQUIRE(d == b);
        REQUIRE(d == a);
    }

}
