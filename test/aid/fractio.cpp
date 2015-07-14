#include <catch/catch.hpp>

#include <aid/fractio.hpp>

TEST_CASE("aid::fractio") {

    SECTION("evaluation works as expected") {
        aid::fractio<int> fraction1(123);
        aid::fractio<int> fraction2(4, 2);
        REQUIRE(aid::fractio_cast<double>(fraction1) == 123.0);
        REQUIRE(aid::fractio_cast<double>(fraction2) == 2.0);
    }

    SECTION("implicit conversion from integral types to fractio types") {
        aid::fractio<int> fractio1 = 123;
        aid::fractio<unsigned> fractio2 = 123u;
        aid::fractio<long> fractio3 = 123l;
        aid::fractio<long long> fractio4 = 123ll;
        REQUIRE(fractio1 == 123);
        REQUIRE(fractio2 == 123u);
        REQUIRE(fractio3 == 123l);
        REQUIRE(fractio4 == 123ll);
    }

    SECTION("inversion") {
        aid::fractio<int> fractio1(16, 14);
        aid::fractio<int> fractio2(1, 14);
        auto inverse1 = aid::inverse(fractio1);
        auto inverse2 = aid::inverse(fractio2);
        REQUIRE(inverse1.numerator() == 14);
        REQUIRE(inverse1.denominator() == 16);
        REQUIRE(inverse2.numerator() == 14);
        REQUIRE(inverse2.denominator() == 1);
    }

    SECTION("multiplication") {
        aid::fractio<int> fractio1(7, 3);
        aid::fractio<int> fractio2(12, 14);
        REQUIRE((fractio1 * 0) == 0);
        REQUIRE(aid::fractio_cast<double>(fractio1 * fractio2) == 2.0);
    }

    SECTION("division") {
        aid::fractio<int> fractio1 = 3;
        aid::fractio<int> fractio2 = 9;
        REQUIRE(aid::fractio_cast<double>(fractio2 / fractio1) == 3.0);
    }

}
