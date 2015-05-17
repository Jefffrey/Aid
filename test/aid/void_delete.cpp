#include <catch/catch.hpp>

#include <aid/void_delete.hpp>

TEST_CASE("aid::void_delete") {

    SECTION("works on `std::unique_ptr`") {
        std::unique_ptr<void, aid::void_delete<int>> ptr(new int(42));
        REQUIRE(*static_cast<int*>(ptr.get()) == 42);
    }

}
