#include <catch/catch.hpp>

#include <aid/fractio.hpp>

TEST_CASE("aid::fractio") {

    SECTION("evaluation works as expected") {
        aid::fractio<int> fraction1(123);
        aid::fractio<int> fraction2(4, 2);
        REQUIRE(aid::evaluate<double>(fraction1) == 123.0);
        REQUIRE(aid::evaluate<double>(fraction2) == 2.0);
    }

}
