#include <catch/catch.hpp>
#include <aid/matrix.hpp>
#include <aid/algebra.hpp>

TEST_CASE("vector component access") {
    aid::row_vector<int, 2> vec_a { 28, 65 };
    aid::row_vector<int, 3> vec_b { 2987, 54, 18 };
    aid::row_vector<int, 4> vec_c { 287, 75, 15, 98 };
    aid::col_vector<int, 2> vec_d { 81, 765 };
    aid::col_vector<int, 3> vec_e { 87, 1, 27 };
    aid::col_vector<int, 4> vec_f { 65, 71, 97, -1 };
    REQUIRE(aid::x(vec_a) == 28);
    REQUIRE(aid::x(vec_b) == 2987);
    REQUIRE(aid::x(vec_c) == 287);
    REQUIRE(aid::x(vec_d) == 81);
    REQUIRE(aid::x(vec_e) == 87);
    REQUIRE(aid::x(vec_f) == 65);
    REQUIRE(aid::y(vec_a) == 65);
    REQUIRE(aid::y(vec_b) == 54);
    REQUIRE(aid::y(vec_c) == 75);
    REQUIRE(aid::y(vec_d) == 765);
    REQUIRE(aid::y(vec_e) == 1);
    REQUIRE(aid::y(vec_f) == 71);
    REQUIRE(aid::z(vec_b) == 18);
    REQUIRE(aid::z(vec_c) == 15);
    REQUIRE(aid::z(vec_e) == 27);
    REQUIRE(aid::z(vec_f) == 97);
    REQUIRE(aid::w(vec_c) == 98);
    REQUIRE(aid::w(vec_f) == -1);
}

TEST_CASE("matrix negation") {
    aid::matrix<int, 3, 5> mat
        { 0, -2, 3, 87, -1233
        , 34, 97, -12, 87, 98
        , 0, 0, 1, 2, -1 };
    aid::matrix<int, 3, 5> mat_res
        { 0, 2, -3, -87, 1233
        , -34, -97, 12, -87, -98
        , 0, 0, -1, -2, 1 };
    REQUIRE((-mat) == mat_res);
}

TEST_CASE("matrix addition") {
    aid::matrix<int, 3, 4> mat_a
        { 3, 4, -1, 0
        , 82, -245, -44, -2344
        , 0, 0, 1, 0 };
    aid::matrix<int, 3, 4> mat_b
        { 33, 276, 0, 18
        , 38, -38, -438, 97
        , 0, 23, -1, 29 };
    auto mat_res = mat_a + mat_b;
    REQUIRE(mat_res(0, 0) == 36);
    REQUIRE(mat_res(0, 1) == 280);
    REQUIRE(mat_res(0, 2) == -1);
    REQUIRE(mat_res(0, 3) == 18);
    REQUIRE(mat_res(1, 0) == 120);
    REQUIRE(mat_res(1, 1) == -283);
    REQUIRE(mat_res(1, 2) == -482);
    REQUIRE(mat_res(1, 3) == -2247);
    REQUIRE(mat_res(2, 0) == 0);
    REQUIRE(mat_res(2, 1) == 23);
    REQUIRE(mat_res(2, 2) == 0);
    REQUIRE(mat_res(2, 3) == 29);
}
