#include <catch/catch.hpp>

#include <aid/matrix.hpp>
#include <aid/matrix_traits.hpp>

TEST_CASE("aid::is_matrix") {

    SECTION("aid::matrix") {
        using mat = aid::matrix<int, 4, 3>;
        REQUIRE(aid::is_matrix<mat>::value == true);
        REQUIRE(aid::is_matrix<int>::value == false);
    }
    
}

TEST_CASE("aid::is_vector") {

    SECTION("with a vector") {
        using mat_a = aid::matrix<int, 4, 1>;
        using mat_b = aid::matrix<int, 1, 3>;
        using mat_c = aid::matrix<int, 1, 1>;
        REQUIRE(aid::is_vector<mat_a>::value == true);
        REQUIRE(aid::is_vector<mat_b>::value == true);
        REQUIRE(aid::is_vector<mat_c>::value == true);
    }

    SECTION("with a non vector") {
        using mat_a = aid::matrix<int, 2>;
        using mat_b = aid::matrix<int, 0>;
        using mat_c = aid::matrix<int, 4, 2>;
        REQUIRE(aid::is_vector<mat_a>::value == false);
        REQUIRE(aid::is_vector<mat_b>::value == false);
        REQUIRE(aid::is_vector<mat_c>::value == false);
    }

}

TEST_CASE("aid::is_row_vector") {

    SECTION("with a row vector") {
        using mat_a = aid::matrix<int, 1, 4>;
        using mat_b = aid::matrix<int, 1, 3>;
        using mat_c = aid::matrix<int, 1, 2>;
        using mat_d = aid::matrix<int, 1, 1>;
        REQUIRE(aid::is_row_vector<mat_a>::value == true);
        REQUIRE(aid::is_row_vector<mat_b>::value == true);
        REQUIRE(aid::is_row_vector<mat_c>::value == true);
        REQUIRE(aid::is_row_vector<mat_d>::value == true);
    }

    SECTION("with a non row vector") {
        using mat_a = aid::matrix<int, 4, 1>;
        using mat_b = aid::matrix<int, 3, 1>;
        using mat_c = aid::matrix<int, 2, 1>;
        using mat_d = aid::matrix<int, 0>;
        using mat_e = aid::matrix<int, 4, 2>;
        using mat_f = aid::matrix<int, 2, 4>;
        REQUIRE(aid::is_row_vector<mat_a>::value == false);
        REQUIRE(aid::is_row_vector<mat_b>::value == false);
        REQUIRE(aid::is_row_vector<mat_c>::value == false);
        REQUIRE(aid::is_row_vector<mat_d>::value == false);
        REQUIRE(aid::is_row_vector<mat_e>::value == false);
        REQUIRE(aid::is_row_vector<mat_f>::value == false);
    }

}

TEST_CASE("aid::is_col_vector") {

    SECTION("with a col vector") {
        using mat_a = aid::matrix<int, 4, 1>;
        using mat_b = aid::matrix<int, 3, 1>;
        using mat_c = aid::matrix<int, 2, 1>;
        using mat_d = aid::matrix<int, 1, 1>;
        REQUIRE(aid::is_col_vector<mat_a>::value == true);
        REQUIRE(aid::is_col_vector<mat_b>::value == true);
        REQUIRE(aid::is_col_vector<mat_c>::value == true);
        REQUIRE(aid::is_col_vector<mat_d>::value == true);
    }

    SECTION("with a non row vector") {
        using mat_a = aid::matrix<int, 1, 4>;
        using mat_b = aid::matrix<int, 1, 3>;
        using mat_c = aid::matrix<int, 1, 2>;
        using mat_d = aid::matrix<int, 0>;
        using mat_e = aid::matrix<int, 4, 2>;
        using mat_f = aid::matrix<int, 2, 4>;
        REQUIRE(aid::is_col_vector<mat_a>::value == false);
        REQUIRE(aid::is_col_vector<mat_b>::value == false);
        REQUIRE(aid::is_col_vector<mat_c>::value == false);
        REQUIRE(aid::is_col_vector<mat_d>::value == false);
        REQUIRE(aid::is_col_vector<mat_e>::value == false);
        REQUIRE(aid::is_col_vector<mat_f>::value == false);
    }

}
