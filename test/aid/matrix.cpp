#include <catch/catch.hpp>
#include <utility>

#include <aid/matrix.hpp>

TEST_CASE("aid::matrix") {

    SECTION("default constructor") {
        aid::matrix<int, 4> mat_a;
        aid::matrix<int, 3> mat_b;
        aid::matrix<int, 2> mat_c;
        aid::matrix<int, 1> mat_d;
        aid::matrix<int, 0> mat_e;
    }

    SECTION("fill constructor") {
        aid::matrix<int, 2, 3> mat(345);
        REQUIRE(mat(0, 0) == 345);
        REQUIRE(mat(0, 1) == 345);
        REQUIRE(mat(0, 2) == 345);
        REQUIRE(mat(1, 0) == 345);
        REQUIRE(mat(1, 1) == 345);
        REQUIRE(mat(1, 2) == 345);
    }

    SECTION("initializer list constructor") {
        aid::matrix<int, 3, 2> mat
            { 45, 4
            , 5 , 2
            , 77, 13 };
        REQUIRE(mat(0, 0) == 45);
        REQUIRE(mat(0, 1) == 4);
        REQUIRE(mat(1, 0) == 5);
        REQUIRE(mat(1, 1) == 2);
        REQUIRE(mat(2, 0) == 77);
        REQUIRE(mat(2, 1) == 13);
    }

    SECTION("copy constructor") {
        aid::matrix<int, 3, 1> mat_a {1, 2, 4};
        auto mat_b = mat_a;

        REQUIRE(mat_b(0, 0) == 1);
        REQUIRE(mat_b(1, 0) == 2);
        REQUIRE(mat_b(2, 0) == 4);

        mat_a(1, 0) = 123;
        REQUIRE(mat_a(1, 0) == 123);
        REQUIRE(mat_b(1, 0) == 2);
    }

    SECTION("move constructor") {
        aid::matrix<int, 3, 1> mat_a {1, 2, 4};
        auto mat_b = std::move(mat_a);
        REQUIRE(mat_b(0, 0) == 1);
        REQUIRE(mat_b(1, 0) == 2);
        REQUIRE(mat_b(2, 0) == 4);
    }

    SECTION("generator constructor") {
        auto gen = [](std::size_t r, std::size_t c) {
            return (r == c) ? r : -1;
        };
        aid::matrix<int, 4, 5> mat_a(gen);
        REQUIRE(mat_a(0, 0) == 0);
        REQUIRE(mat_a(1, 1) == 1);
        REQUIRE(mat_a(2, 2) == 2);
        REQUIRE(mat_a(3, 3) == 3);
    }

    SECTION("access operator") {    
        aid::matrix<int, 2> mat2x2 { 4, 6, 12, 64 };
        REQUIRE(mat2x2(0, 0) == 4);
        REQUIRE(mat2x2(0, 1) == 6);
        REQUIRE(mat2x2(1, 0) == 12);
        REQUIRE(mat2x2(1, 1) == 64);
    }

    SECTION("vector access operator") {
        aid::matrix<int, 1> vec_a { 1 };
        aid::matrix<int, 2, 1> vec_b { 123, 54 };
        aid::matrix<int, 3, 1> vec_c { 24, 64, 87 };
        aid::matrix<int, 1, 2> vec_d { 33, 56 };
        aid::matrix<int, 1, 3> vec_e { 387, 861, 65 };
        REQUIRE(vec_a[0] == 1);
        REQUIRE(vec_b[0] == 123);
        REQUIRE(vec_b[1] == 54);
        REQUIRE(vec_c[0] == 24);
        REQUIRE(vec_c[1] == 64);
        REQUIRE(vec_c[2] == 87);
        REQUIRE(vec_d[0] == 33);
        REQUIRE(vec_d[1] == 56);
        REQUIRE(vec_e[0] == 387);
        REQUIRE(vec_e[1] == 861);
        REQUIRE(vec_e[2] == 65);
    }

    SECTION("size") {
        aid::matrix<int, 4, 3> mat_a;
        aid::matrix<int, 3, 4> mat_b;
        REQUIRE(mat_a.size() == 12);
        REQUIRE(mat_b.size() == 12);
    }

    SECTION("maximum size") {
        aid::matrix<int, 4, 2> mat;
        REQUIRE(mat.max_size() == mat.size());
        REQUIRE(mat.max_size() == 8);
    }

    SECTION("empty") {
        aid::matrix<int, 4> mat_a;
        REQUIRE(mat_a.empty() == false);

        aid::matrix<int, 0> mat_b;
        REQUIRE(mat_b.empty() == true);
    }

    SECTION("swap") {
        aid::matrix<int, 1, 3> mat_a {3, 4, 1};
        aid::matrix<int, 1, 3> mat_b {6, 7, 2};
        auto mat_a_copy = mat_a;
        auto mat_b_copy = mat_b;
        mat_a.swap(mat_b);

        REQUIRE(mat_a == mat_b_copy);
        REQUIRE(mat_b == mat_a_copy);
    }

    SECTION("copy assignment") {
        aid::matrix<int, 4, 1> mat_a {1, 3, 5 , 7};
        aid::matrix<int, 4, 1> mat_b {5, 1, 87, 1};
        mat_a = mat_b;
        REQUIRE(mat_a(0, 0) == 5);
        REQUIRE(mat_a(1, 0) == 1);
        REQUIRE(mat_a(2, 0) == 87);
        REQUIRE(mat_a(3, 0) == 1);
    }

    SECTION("move assignment") {
        aid::matrix<int, 4, 1> mat_a {18, 26, 36, 9};
        aid::matrix<int, 4, 1> mat_b {177, 71, 6, 1};
        mat_a = std::move(mat_b);
        REQUIRE(mat_a(0, 0) == 177);
        REQUIRE(mat_a(1, 0) == 71);
        REQUIRE(mat_a(2, 0) == 6);
        REQUIRE(mat_a(3, 0) == 1);
    }

    SECTION("equality/inequality operator") {
        aid::matrix<int, 2> mat2x2a { 1, 2, 3, 4 };
        aid::matrix<int, 2> mat2x2b { 2, 5, 7, 1 };

        REQUIRE(mat2x2a == mat2x2a);
        REQUIRE(mat2x2b == mat2x2b);
        REQUIRE(mat2x2a != mat2x2b);
        REQUIRE(mat2x2b != mat2x2a);
    }

}

TEST_CASE("aid::row_vector") {

    SECTION("matrix equality") {
        aid::row_vector<int, 3> vec(0);
        aid::matrix<int, 1, 3> mat(0);
        REQUIRE(vec == mat);
    }

}

TEST_CASE("aid::col_vector") {

    SECTION("matrix equality") {
        aid::col_vector<int, 3> vec(0);
        aid::matrix<int, 3, 1> mat(0);
        REQUIRE(vec == mat);
    }

}
