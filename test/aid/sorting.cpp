#include <catch/catch.hpp>

#include <aid/sorting.hpp>
#include <string>

TEST_CASE("aid::counting_sort") {

    SECTION("sorts positive integers") {
        auto vec = std::vector<int>{ 3, 0, 2, 5, 11, 8, 9, 7, 4, 1, 6, 10 };
        auto out = std::vector<int>(12);
        auto index_fn = [](int i) { return i; };
        aid::counting_sort(begin(vec), end(vec), begin(out), 12, index_fn);
        for (int i = 0; i < 12; ++i) {
            REQUIRE(out[i] == i);
        }
    }

    SECTION("sorts negative integers") {
        auto vec = std::vector<int>{ -3, 0, -2, -5, -11, -8, -9, -7, -4, -1, -6, -10 };
        auto out = std::vector<int>(12);
        auto index_fn = [](int i) { return i + 11; };
        aid::counting_sort(begin(vec), end(vec), begin(out), 12, index_fn);
        for (int i = 0; i < 12; ++i) {
            REQUIRE(out[i] == i - 11);
        }
    }

    SECTION("is stable") {
        struct node { int body; std::string satellite; };
        auto vec = std::vector<node>{
            {1, "1fst"}, {3, "3fst"}, {0, "0fst"}, {3, "3snd"}, {3, "3trd"}
        };

        auto out = std::vector<node>(5);
        auto index_fn = [](node const& n) { return n.body; };
        aid::counting_sort(begin(vec), end(vec), begin(out), 4, index_fn);

        REQUIRE(out[0].body == 0); REQUIRE(out[0].satellite == "0fst");
        REQUIRE(out[1].body == 1); REQUIRE(out[1].satellite == "1fst");
        REQUIRE(out[2].body == 3); REQUIRE(out[2].satellite == "3fst");
        REQUIRE(out[3].body == 3); REQUIRE(out[3].satellite == "3snd");
        REQUIRE(out[4].body == 3); REQUIRE(out[4].satellite == "3trd");
    }
    
}
