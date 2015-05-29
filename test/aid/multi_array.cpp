#include <catch/catch.hpp>

#include <aid/multi_array.hpp>

TEST_CASE("aid::multi_array") {

    SECTION("works almost as a C style one") {
        aid::multi_array<int, 2, 3, 2> arr = {{
            {{
                {0, 1},
                {2, 3},
                {4, 5}
            }},
            {{
                {6, 7},
                {8, 9},
                {10, 11}
            }}
        }};

        int c = 0;
        for (int i = 0; i < 2; ++i)
            for (int j = 0; j < 3; ++j)
                for (int k = 0; k < 2; ++k)
                    REQUIRE(arr[i][j][k] == c++);
    }
    
}
