#include <catch/catch.hpp>

#include <aid/sorting.hpp>

TEST_CASE("aid::counting_sort") {

    SECTION("sorts positive integers") {
        std::vector<int> vec { 3, 0, 2, 5, 11, 8, 9, 7, 4, 1, 6, 10 };
        std::vector<int> out(12);
        auto index_fn = [](int i) { return i; };
        aid::counting_sort(begin(vec), end(vec), begin(out), 12, index_fn);
        for (int i = 0; i < 12; ++i) {
            REQUIRE(out[i] == i);
        }
    }
    
}
