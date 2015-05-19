#include <catch/catch.hpp>
#include <aid/matrix.hpp>
#include <aid/algebra.hpp>

TEST_CASE("aid::x, aid::y, aid::z, aid::w") {

    SECTION("aid::row_vector") {
        aid::row_vector<int, 2> vec_a { 28, 65 };
        aid::row_vector<int, 3> vec_b { 2987, 54, 18 };
        aid::row_vector<int, 4> vec_c { 287, 75, 15, 98 };
        REQUIRE(aid::x(vec_a) == 28);
        REQUIRE(aid::x(vec_b) == 2987);
        REQUIRE(aid::x(vec_c) == 287);
        REQUIRE(aid::y(vec_a) == 65);
        REQUIRE(aid::y(vec_b) == 54);
        REQUIRE(aid::y(vec_c) == 75);
        REQUIRE(aid::z(vec_b) == 18);
        REQUIRE(aid::z(vec_c) == 15);
        REQUIRE(aid::w(vec_c) == 98);
    }

    SECTION("aid::col_vector") {
        aid::col_vector<int, 2> vec_d { 81, 765 };
        aid::col_vector<int, 3> vec_e { 87, 1, 27 };
        aid::col_vector<int, 4> vec_f { 65, 71, 97, -1 };
        REQUIRE(aid::x(vec_d) == 81);
        REQUIRE(aid::x(vec_e) == 87);
        REQUIRE(aid::x(vec_f) == 65);
        REQUIRE(aid::y(vec_d) == 765);
        REQUIRE(aid::y(vec_e) == 1);
        REQUIRE(aid::y(vec_f) == 71);
        REQUIRE(aid::z(vec_e) == 27);
        REQUIRE(aid::z(vec_f) == 97);
        REQUIRE(aid::w(vec_f) == -1);
    }

}

TEST_CASE("aid::euclidean_norm") {

    SECTION("aid::row_vector") {
        aid::row_vector<double, 2> vec_a { 28.0, 65.0 };
        REQUIRE(aid::euclidean_norm(vec_a) == 70.77428911688199);
    }

    SECTION("aid::col_vector") {
        aid::row_vector<double, 2> vec_a { 28.0, 65.0 };
        REQUIRE(aid::euclidean_norm(vec_a) == 70.77428911688199);
    }

}

TEST_CASE("unary operator-") {

    SECTION("aid::matrix") {
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

}

TEST_CASE("binary operator+") {

    SECTION("aid::matrix") {
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

}

TEST_CASE("operator+=") {

    SECTION("aid::matrix") {
        aid::matrix<int, 3, 4> mat_res
            { 3, 4, -1, 0
            , 82, -245, -44, -2344
            , 0, 0, 1, 0 };
        aid::matrix<int, 3, 4> mat_b
            { 33, 276, 0, 18
            , 38, -38, -438, 97
            , 0, 23, -1, 29 };
        mat_res += mat_b;
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

}

TEST_CASE("binary operator-") {

    SECTION("aid::matrix") {
        aid::matrix<int, 3, 4> mat_a
            { 3, 4, -1, 0
            , 82, -245, -44, -2344
            , 0, 0, 1, 0 };
        aid::matrix<int, 3, 4> mat_b
            { 33, 276, 0, 18
            , 38, -38, -438, 97
            , 0, 23, -1, 29 };
        auto mat_res = mat_a - mat_b;
        REQUIRE(mat_res(0, 0) == -30);
        REQUIRE(mat_res(0, 1) == -272);
        REQUIRE(mat_res(0, 2) == -1);
        REQUIRE(mat_res(0, 3) == -18);
        REQUIRE(mat_res(1, 0) == 44);
        REQUIRE(mat_res(1, 1) == -207);
        REQUIRE(mat_res(1, 2) == 394);
        REQUIRE(mat_res(1, 3) == -2441);
        REQUIRE(mat_res(2, 0) == 0);
        REQUIRE(mat_res(2, 1) == -23);
        REQUIRE(mat_res(2, 2) == 2);
        REQUIRE(mat_res(2, 3) == -29);
    }

}

TEST_CASE("operator-=") {

    SECTION("aid::matrix") {
        aid::matrix<int, 3, 4> mat_res
            { 3, 4, -1, 0
            , 82, -245, -44, -2344
            , 0, 0, 1, 0 };
        aid::matrix<int, 3, 4> mat_b
            { 33, 276, 0, 18
            , 38, -38, -438, 97
            , 0, 23, -1, 29 };
        mat_res -= mat_b;
        REQUIRE(mat_res(0, 0) == -30);
        REQUIRE(mat_res(0, 1) == -272);
        REQUIRE(mat_res(0, 2) == -1);
        REQUIRE(mat_res(0, 3) == -18);
        REQUIRE(mat_res(1, 0) == 44);
        REQUIRE(mat_res(1, 1) == -207);
        REQUIRE(mat_res(1, 2) == 394);
        REQUIRE(mat_res(1, 3) == -2441);
        REQUIRE(mat_res(2, 0) == 0);
        REQUIRE(mat_res(2, 1) == -23);
        REQUIRE(mat_res(2, 2) == 2);
        REQUIRE(mat_res(2, 3) == -29);
    }

}

TEST_CASE("operator*=") {

    SECTION("aid::matrix") {
        aid::matrix<int, 2, 3> mat_res
            { 2, -34, 0
            , 0, 1, 45 };

        aid::matrix<int, 2, 3> mat_cpy = mat_res;
        mat_res *= 1;
        REQUIRE(mat_res == mat_cpy);
        
        mat_res *= -3;
        REQUIRE(mat_res(0, 0) == -6);
        REQUIRE(mat_res(0, 1) == 102);
        REQUIRE(mat_res(0, 2) == 0);
        REQUIRE(mat_res(1, 0) == 0);
        REQUIRE(mat_res(1, 1) == -3);
        REQUIRE(mat_res(1, 2) == -135);

        mat_res *= 0;
        REQUIRE((mat_res == aid::matrix<int, 2, 3>(0)));
    }

}

TEST_CASE("operator*") {

    SECTION("aid::matrix") {
        aid::matrix<int, 2, 3> mat_a
            { 2, -34, 0
            , 0, 1, 45 };

        auto mat_res = mat_a * -3;
        REQUIRE(mat_res(0, 0) == -6);
        REQUIRE(mat_res(0, 1) == 102);
        REQUIRE(mat_res(0, 2) == 0);
        REQUIRE(mat_res(1, 0) == 0);
        REQUIRE(mat_res(1, 1) == -3);
        REQUIRE(mat_res(1, 2) == -135);

        auto mat_res2 = -3 * mat_a;
        REQUIRE(mat_res(0, 0) == -6);
        REQUIRE(mat_res(0, 1) == 102);
        REQUIRE(mat_res(0, 2) == 0);
        REQUIRE(mat_res(1, 0) == 0);
        REQUIRE(mat_res(1, 1) == -3);
        REQUIRE(mat_res(1, 2) == -135);

        REQUIRE((mat_a * 1) == mat_a);
        REQUIRE((1 * mat_a) == mat_a);
        REQUIRE((mat_a * -1) == -mat_a);
        REQUIRE((-1 * mat_a) == -mat_a);
    }

}

TEST_CASE("operator/=") {

    SECTION("aid::matrix") {
        aid::matrix<int, 2, 3> mat_res
            { 12, -36, 0
            , 0, -24, 60 };

        aid::matrix<int, 2, 3> mat_cpy = mat_res;
        mat_res /= 1;
        REQUIRE(mat_res == mat_cpy);
        
        mat_res /= -3;
        REQUIRE(mat_res(0, 0) == -4);
        REQUIRE(mat_res(0, 1) == 12);
        REQUIRE(mat_res(0, 2) == 0);
        REQUIRE(mat_res(1, 0) == 0);
        REQUIRE(mat_res(1, 1) == 8);
        REQUIRE(mat_res(1, 2) == -20);
    }

}

TEST_CASE("operator/") {

    SECTION("aid::matrix") {
        aid::matrix<int, 2, 3> mat_a
            { 12, -36, 0
            , 0, -24, 60 };

        auto mat_res = mat_a / -3;
        REQUIRE(mat_res(0, 0) == -4);
        REQUIRE(mat_res(0, 1) == 12);
        REQUIRE(mat_res(0, 2) == 0);
        REQUIRE(mat_res(1, 0) == 0);
        REQUIRE(mat_res(1, 1) == 8);
        REQUIRE(mat_res(1, 2) == -20);

        REQUIRE((mat_a / 1) == mat_a);
        REQUIRE((mat_a / -1) == -mat_a);
    }

}
