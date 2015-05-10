#include "../ext/catch.hpp"

#include <aid/component_set.hpp>

// testing components
struct comp1 { int attr; comp1(int a) : attr(a) {} };
struct comp2 { int attr; comp2(int a) : attr(a) {} };
struct comp3 { double attr; comp3(double a) : attr(a) {} };
struct comp4 { std::string attr; comp4(std::string a) : attr(a) {} };
struct comp5 : comp2 { std::string attr2; comp5(int a, std::string b) : comp2(a), attr2(b) {} };
struct comp6 : comp2 { double attr2; comp6(int a, double b) : comp2(a), attr2(b) {} };

TEST_CASE("aid::component_set") {

    SECTION("adding components") {
        aid::component_set set_a;
        set_a.add<comp1>(123);
        set_a.add<comp5>(456, "ok");
        REQUIRE(set_a.has<comp1>());
        REQUIRE(set_a.has<comp5>());

        REQUIRE(!set_a.has<comp2>());
        REQUIRE(!set_a.has<comp6>());

        REQUIRE(set_a.get<comp1>().attr == 123);
        REQUIRE(set_a.get<comp1>().attr == 123);
        REQUIRE(set_a.get<comp5>().attr == 456);
        REQUIRE(set_a.get<comp5>().attr2 == "ok");
    }

    SECTION("checking components") {
        aid::component_set set_a;
        set_a.add<comp1>(123);
        set_a.add<comp5>(456, "ok");

        REQUIRE((set_a.has<comp1, comp5>()));
        REQUIRE((set_a.has<comp5, comp1>()));
        REQUIRE(!(set_a.has<comp1, comp4, comp5>()));

        REQUIRE(!(set_a.has<comp1, comp4, comp5>()));
        REQUIRE(!(set_a.has<comp2, comp3, comp5>()));
    }

    SECTION("adding components of base classes") {
        aid::component_set set_a;
        set_a.add<comp2>(123);
        set_a.add<comp5>(456, "5");
        set_a.add<comp6>(789, 3.141592);
        REQUIRE((set_a.has<comp2, comp5, comp6>()));
        REQUIRE(set_a.get<comp2>().attr == 123);
        REQUIRE(set_a.get<comp5>().attr == 456);
        REQUIRE(set_a.get<comp5>().attr2 == "5");
        REQUIRE(set_a.get<comp6>().attr == 789);
        REQUIRE(set_a.get<comp6>().attr2 == 3.141592);
    }

    SECTION("removing components") {
        aid::component_set set_a;
        set_a.add<comp1>(123);
        set_a.add<comp5>(456, "ok");
        REQUIRE(set_a.has<comp1>());
        REQUIRE(set_a.has<comp5>());
        
        set_a.remove<comp1>();
        REQUIRE(!set_a.has<comp1>());
        REQUIRE(set_a.has<comp5>());

        set_a.add<comp1>(789);
        REQUIRE(set_a.has<comp1>());
        REQUIRE(set_a.get<comp1>().attr == 789);
    }

    SECTION("removing components of base classes") {
        aid::component_set set_a;
        set_a.add<comp2>(123);
        set_a.add<comp5>(456, "5");
        set_a.add<comp6>(789, 3.141592);
        set_a.remove<comp2>();
        REQUIRE((set_a.has<comp5, comp6>()));
        REQUIRE(!set_a.has<comp2>());
        REQUIRE(set_a.get<comp5>().attr == 456);
        REQUIRE(set_a.get<comp6>().attr == 789);

        set_a.remove<comp5>();
        REQUIRE(set_a.has<comp6>());
        REQUIRE(!set_a.has<comp2>());
        REQUIRE(!set_a.has<comp5>());
        REQUIRE(set_a.get<comp6>().attr == 789);

        set_a.add<comp2>(321);
        REQUIRE((set_a.has<comp2, comp6>()));
        REQUIRE(!set_a.has<comp5>());
        REQUIRE(set_a.get<comp2>().attr == 321);
        REQUIRE(set_a.get<comp6>().attr == 789);

        set_a.add<comp5>(654, "n5");
        REQUIRE((set_a.has<comp2, comp5, comp6>()));
        REQUIRE(set_a.get<comp2>().attr == 321);
        REQUIRE(set_a.get<comp5>().attr == 654);
        REQUIRE(set_a.get<comp5>().attr2 == "n5");
        REQUIRE(set_a.get<comp6>().attr == 789);
        REQUIRE(set_a.get<comp6>().attr2 == 3.141592);
    }

}
