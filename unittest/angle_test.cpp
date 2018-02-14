/**
 * @file    angle_test.cpp
 * @brief   Testing ken3::angle using lest. 
 * @author  toda
 * @date    2018-02-13
 * @version 0.1.0
 * @remark  the target is C++11 or more
 */

#include <tuple>
#include "ken3/angle.hpp"
#include "unittest/lest.hpp"

namespace {

// constants
constexpr double pi = 3.14159265358979323846;
constexpr double d2r = pi / 180.0;
constexpr double r2d = 180.0 / pi;

// type definitions
using angle_list = std::tuple<
    ken3::angle<true, true>,
    ken3::angle<true, false>,
    ken3::angle<false, true>,
    ken3::angle<false, false>
>;
/////////////////////////////////////////////////////////////////////////////

} // namespace {

const lest::test specification[] =
{

    CASE("minimum functions")
    {
        {
            using my_angle = std::tuple_element<0, angle_list>::type;
            using lest::approx;

            my_angle a(45.0);
            EXPECT(approx(45.0) == a());
            EXPECT(approx(45.0) == a.degree());
            EXPECT(approx(45.0 * d2r) == a.radian());
            a += my_angle(45.0);
            EXPECT(approx(90.0) == a());
            EXPECT(approx(90.0) == a.degree());
            EXPECT(approx(90.0 * d2r) == a.radian());
            a += 180.0;
            EXPECT(approx(270.0) == a());
            EXPECT(approx(270.0) == a.degree());
            EXPECT(approx(270.0 * d2r) == a.radian());
            a += 135.0;
            EXPECT(approx(45.0) == a());
            EXPECT(approx(45.0) == a.degree());
            EXPECT(approx(45.0 * d2r) == a.radian());
        }
        {
            using my_angle = std::tuple_element<1, angle_list>::type;
            using lest::approx;

            my_angle a(45.0);
            EXPECT(approx(45.0) == a());
            EXPECT(approx(45.0) == a.degree());
            EXPECT(approx(45.0 * d2r) == a.radian());
            a += my_angle(45.0);
            EXPECT(approx(90.0) == a());
            EXPECT(approx(90.0) == a.degree());
            EXPECT(approx(90.0 * d2r) == a.radian());
            a += 180.0;
            EXPECT(approx(-90.0) == a());
            EXPECT(approx(-90.0) == a.degree());
            EXPECT(approx(-90.0 * d2r) == a.radian());
            a += 135.0;
            EXPECT(approx(45.0) == a());
            EXPECT(approx(45.0) == a.degree());
            EXPECT(approx(45.0 * d2r) == a.radian());
        }
        {
            using my_angle = std::tuple_element<2, angle_list>::type;
            using lest::approx;

            my_angle a(pi * 0.25);
            EXPECT(approx(pi * 0.25) == a());
            EXPECT(approx(pi * 0.25 * r2d) == a.degree());
            EXPECT(approx(pi * 0.25) == a.radian());
            a += my_angle(pi * 0.25);
            EXPECT(approx(pi * 0.5) == a());
            EXPECT(approx(pi * 0.5 * r2d) == a.degree());
            EXPECT(approx(pi * 0.5) == a.radian());
            a += pi;
            EXPECT(approx(pi * 1.5) == a());
            EXPECT(approx(pi * 1.5 * r2d) == a.degree());
            EXPECT(approx(pi * 1.5) == a.radian());
            a += (pi * 0.75);
            EXPECT(approx(pi * 0.25) == a());
            EXPECT(approx(pi * 0.25 * r2d) == a.degree());
            EXPECT(approx(pi * 0.25) == a.radian());
        }
        {
            using my_angle = std::tuple_element<3, angle_list>::type;
            using lest::approx;

            my_angle a(pi * 0.25);
            EXPECT(approx(pi * 0.25) == a());
            EXPECT(approx(pi * 0.25 * r2d) == a.degree());
            EXPECT(approx(pi * 0.25) == a.radian());
            a += my_angle(pi * 0.25);
            EXPECT(approx(pi * 0.5) == a());
            EXPECT(approx(pi * 0.5 * r2d) == a.degree());
            EXPECT(approx(pi * 0.5) == a.radian());
            a += pi;
            EXPECT(approx(pi * -0.5) == a());
            EXPECT(approx(pi * -0.5 * r2d) == a.degree());
            EXPECT(approx(pi * -0.5) == a.radian());
            a += (pi * 0.75);
            EXPECT(approx(pi * 0.25) == a());
            EXPECT(approx(pi * 0.25 * r2d) == a.degree());
            EXPECT(approx(pi * 0.25) == a.radian());
        }
    },

    CASE("default constructor")
    {
        {
            using my_angle = std::tuple_element<0, angle_list>::type;
            using lest::approx;

            my_angle a;
            EXPECT(approx(0.0) == a());
        }
        {
            using my_angle = std::tuple_element<1, angle_list>::type;
            using lest::approx;

            my_angle a;
            EXPECT(approx(0.0) == a());
        }
        {
            using my_angle = std::tuple_element<2, angle_list>::type;
            using lest::approx;

            my_angle a;
            EXPECT(approx(0.0) == a());
        }
        {
            using my_angle = std::tuple_element<3, angle_list>::type;
            using lest::approx;

            my_angle a;
            EXPECT(approx(0.0) == a());
        }
    },

    CASE("constructor with one argument")
    {
        {
            using my_angle = std::tuple_element<0, angle_list>::type;
            using lest::approx;

            EXPECT(approx(179.0) == my_angle(-181.0)());
            EXPECT(approx(180.0) == my_angle(-180.0)());
            EXPECT(approx(181.0) == my_angle(-179.0)());
            EXPECT(approx(359.0) == my_angle(-1.0)());
            EXPECT(approx(0.0) == my_angle(0.0)());
            EXPECT(approx(1.0) == my_angle(1.0)());
            EXPECT(approx(359.0) == my_angle(359.0)());
            EXPECT(approx(0.0) == my_angle(360.0)());
            EXPECT(approx(1.0) == my_angle(361.0)());
            EXPECT(approx(1.0) == my_angle(360000001.0)());
            EXPECT(approx(359.0) == my_angle(-360000001.0)());
        }
        {
            using my_angle = std::tuple_element<1, angle_list>::type;
            using lest::approx;

            EXPECT(approx(179.0) == my_angle(-181.0)());
            EXPECT(approx(-180.0) == my_angle(-180.0)());
            EXPECT(approx(-179.0) == my_angle(-179.0)());
            EXPECT(approx(-1.0) == my_angle(-1.0)());
            EXPECT(approx(0.0) == my_angle(0.0)());
            EXPECT(approx(1.0) == my_angle(1.0)());
            EXPECT(approx(-1.0) == my_angle(359.0)());
            EXPECT(approx(0.0) == my_angle(360.0)());
            EXPECT(approx(1.0) == my_angle(361.0)());
            EXPECT(approx(1.0) == my_angle(360000001.0)());
            EXPECT(approx(-1.0) == my_angle(-360000001.0)());
        }
        {
            using my_angle = std::tuple_element<2, angle_list>::type;
            using lest::approx;

            double d = 0.001;
            EXPECT(approx(pi - d) == my_angle(-pi - d)());
            EXPECT(approx(pi) == my_angle(-pi)());
            EXPECT(approx(pi + d) == my_angle(-pi + d)());
            EXPECT(approx(pi * 2.0 - d) == my_angle(-d)());
            EXPECT(approx(0.0) == my_angle(0.0)());
            EXPECT(approx(d) == my_angle(d)());
            EXPECT(approx(pi * 2.0 - d) == my_angle(pi * 2.0 - d)());
            EXPECT(approx(0.0) == my_angle(pi * 2.0)());
            EXPECT(approx(d) == my_angle(pi * 2.0 + d)());
            EXPECT(approx(d) == my_angle(pi * 20000.0 + d)());
            EXPECT(approx(pi * 2.0 - d) == my_angle(pi * -20000.0 - d)());
        }
        {
            using my_angle = std::tuple_element<3, angle_list>::type;
            using lest::approx;

            double d = 0.001;
            EXPECT(approx(pi - d) == my_angle(-pi - d)());
            EXPECT(approx(-pi) == my_angle(-pi)());
            EXPECT(approx(-pi + d) == my_angle(-pi + d)());
            EXPECT(approx(-d) == my_angle(-d)());
            EXPECT(approx(0.0) == my_angle(0.0)());
            EXPECT(approx(d) == my_angle(d)());
            EXPECT(approx(-d) == my_angle(pi * 2.0 - d)());
            EXPECT(approx(0.0) == my_angle(pi * 2.0)());
            EXPECT(approx(d) == my_angle(pi * 2.0 + d)());
            EXPECT(approx(d) == my_angle(pi * 20000.0 + d)());
            EXPECT(approx(-d) == my_angle(pi * -20000.0 - d)());
        }
    },

    CASE("operator= with one double argument")
    {
        {
            using my_angle = std::tuple_element<0, angle_list>::type;
            using lest::approx;

            my_angle a;
            a = -181.0;
            EXPECT(approx(179.0) == a());
            a = -180.0;
            EXPECT(approx(180.0) == a());
            a = -179.0;
            EXPECT(approx(181.0) == a());
            a = -1.0;
            EXPECT(approx(359.0) == a());
            a = 0.0;
            EXPECT(approx(0.0) == a());
            a = 1.0;
            EXPECT(approx(1.0) == a());
            a = 359.0;
            EXPECT(approx(359.0) == a());
            a = 360.0;
            EXPECT(approx(0.0) == a());
            a = 361.0;
            EXPECT(approx(1.0) == a());
            a = 360000001.0;
            EXPECT(approx(1.0) == a());
            a = -360000001.0;
            EXPECT(approx(359.0) == a());
        }
        {
            using my_angle = std::tuple_element<1, angle_list>::type;
            using lest::approx;

            my_angle a;
            a = -181.0;
            EXPECT(approx(179.0) == a());
            a = -180.0;
            EXPECT(approx(-180.0) == a());
            a = -179.0;
            EXPECT(approx(-179.0) == a());
            a = -1.0;
            EXPECT(approx(-1.0) == a());
            a = 0.0;
            EXPECT(approx(0.0) == a());
            a = 1.0;
            EXPECT(approx(1.0) == a());
            a = 359.0;
            EXPECT(approx(-1.0) == a());
            a = 360.0;
            EXPECT(approx(0.0) == a());
            a = 361.0;
            EXPECT(approx(1.0) == a());
            a = 360000001.0;
            EXPECT(approx(1.0) == a());
            a = -360000001.0;
            EXPECT(approx(-1.0) == a());
        }
        {
            using my_angle = std::tuple_element<2, angle_list>::type;
            using lest::approx;

            double d = 0.001;
            my_angle a;
            a = -pi - d;
            EXPECT(approx(pi - d) == a());
            a = -pi;
            EXPECT(approx(pi) == a());
            a = -pi + d;
            EXPECT(approx(pi + d) == a());
            a = -d;
            EXPECT(approx(pi * 2.0 - d) == a());
            a = 0.0;
            EXPECT(approx(0.0) == a());
            a = d;
            EXPECT(approx(d) == a());
            a = pi * 2.0 - d;
            EXPECT(approx(pi * 2.0 - d) == a());
            a = pi * 2.0;
            EXPECT(approx(0.0) == a());
            a = pi * 2.0 + d;
            EXPECT(approx(d) == a());
            a = pi * 20000.0 + d;
            EXPECT(approx(d) == a());
            a = pi * -20000.0 - d;
            EXPECT(approx(pi * 2.0 - d) == a());
        }
        {
            using my_angle = std::tuple_element<3, angle_list>::type;
            using lest::approx;

            double d = 0.001;
            my_angle a;
            a = -pi - d;
            EXPECT(approx(pi - d) == a());
            a = -pi;
            EXPECT(approx(-pi) == a());
            a = -pi + d;
            EXPECT(approx(-pi + d) == a());
            a = -d;
            EXPECT(approx(-d) == a());
            a = 0.0;
            EXPECT(approx(0.0) == a());
            a = d;
            EXPECT(approx(d) == a());
            a = pi * 2.0 - d;
            EXPECT(approx(-d) == a());
            a = pi * 2.0;
            EXPECT(approx(0.0) == a());
            a = pi * 2.0 + d;
            EXPECT(approx(d) == a());
            a = pi * 20000.0 + d;
            EXPECT(approx(d) == a());
            a = pi * -20000.0 - d;
            EXPECT(approx(-d) == a());
        }
    },

    CASE("operator<")
    {
        {
            using my_angle = std::tuple_element<0, angle_list>::type;

            EXPECT(my_angle(0.0) < my_angle(-1.0));
            EXPECT(not (my_angle(0.0) < my_angle(0.0)));
            EXPECT(my_angle(0.0) < my_angle(1.0));
            EXPECT(not (my_angle(180.0) < my_angle(179.0)));
            EXPECT(not (my_angle(180.0) < my_angle(180.0)));
            EXPECT(my_angle(180.0) < my_angle(181.0));
        }
        {
            using my_angle = std::tuple_element<1, angle_list>::type;

            EXPECT(not (my_angle(0.0) < my_angle(-1.0)));
            EXPECT(not (my_angle(0.0) < my_angle(0.0)));
            EXPECT(my_angle(0.0) < my_angle(1.0));
            EXPECT(my_angle(180.0) < my_angle(179.0));
            EXPECT(not (my_angle(180.0) < my_angle(180.0)));
            EXPECT(my_angle(180.0) < my_angle(181.0));
        }
        {
            using my_angle = std::tuple_element<2, angle_list>::type;

            double d = 0.001;
            EXPECT(my_angle(0.0) < my_angle(-d));
            EXPECT(not (my_angle(0.0) < my_angle(0.0)));
            EXPECT(my_angle(0.0) < my_angle(d));
            EXPECT(not (my_angle(pi) < my_angle(pi - d)));
            EXPECT(not (my_angle(pi) < my_angle(pi)));
            EXPECT(my_angle(pi) < my_angle(pi + d));
        }
        {
            using my_angle = std::tuple_element<3, angle_list>::type;

            double d = 0.001;
            EXPECT(not (my_angle(0.0) < my_angle(-d)));
            EXPECT(not (my_angle(0.0) < my_angle(0.0)));
            EXPECT(my_angle(0.0) < my_angle(d));
            EXPECT(my_angle(pi) < my_angle(pi - d));
            EXPECT(not (my_angle(pi) < my_angle(pi)));
            EXPECT(my_angle(pi) < my_angle(pi + d));
        }
    },

    CASE("operator==")
    {
        {
            using my_angle = std::tuple_element<0, angle_list>::type;

            EXPECT(not (my_angle(0.0) == my_angle(-1.0)));
            EXPECT(my_angle(0.0) == my_angle(0.0));
            EXPECT(not (my_angle(0.0) == my_angle(1.0)));
        }
        {
            using my_angle = std::tuple_element<1, angle_list>::type;

            EXPECT(not (my_angle(0.0) == my_angle(-1.0)));
            EXPECT(my_angle(0.0) == my_angle(0.0));
            EXPECT(not (my_angle(0.0) == my_angle(1.0)));
        }
        {
            using my_angle = std::tuple_element<2, angle_list>::type;

            double d = 0.001;
            EXPECT(not (my_angle(0.0) == my_angle(-d)));
            EXPECT(my_angle(0.0) == my_angle(0.0));
            EXPECT(not (my_angle(0.0) == my_angle(d)));
        }
        {
            using my_angle = std::tuple_element<3, angle_list>::type;

            double d = 0.001;
            EXPECT(not (my_angle(0.0) == my_angle(-d)));
            EXPECT(my_angle(0.0) == my_angle(0.0));
            EXPECT(not (my_angle(0.0) == my_angle(d)));
        }
    },

    CASE("operator!=")
    {
        {
            using my_angle = std::tuple_element<0, angle_list>::type;

            EXPECT(my_angle(0.0) != my_angle(-1.0));
            EXPECT(not (my_angle(0.0) != my_angle(0.0)));
            EXPECT(my_angle(0.0) != my_angle(1.0));
        }
        {
            using my_angle = std::tuple_element<1, angle_list>::type;

            EXPECT(my_angle(0.0) != my_angle(-1.0));
            EXPECT(not (my_angle(0.0) != my_angle(0.0)));
            EXPECT(my_angle(0.0) != my_angle(1.0));
        }
        {
            using my_angle = std::tuple_element<2, angle_list>::type;

            double d = 0.001;
            EXPECT(my_angle(0.0) != my_angle(-d));
            EXPECT(not (my_angle(0.0) != my_angle(0.0)));
            EXPECT(my_angle(0.0) != my_angle(d));
        }
        {
            using my_angle = std::tuple_element<3, angle_list>::type;

            double d = 0.001;
            EXPECT(my_angle(0.0) != my_angle(-d));
            EXPECT(not (my_angle(0.0) != my_angle(0.0)));
            EXPECT(my_angle(0.0) != my_angle(d));
        }
    },

    CASE("operator+= with self type")
    {
        {
            using my_angle = std::tuple_element<0, angle_list>::type;
            using lest::approx;

            my_angle a;
            a += my_angle(1.0);
            EXPECT(approx(1.0) == a());
            a += my_angle(360.0);
            EXPECT(approx(1.0) == a());
        }
        {
            using my_angle = std::tuple_element<1, angle_list>::type;
            using lest::approx;

            my_angle a;
            a += my_angle(1.0);
            EXPECT(approx(1.0) == a());
            a += my_angle(360.0);
            EXPECT(approx(1.0) == a());
        }
        {
            using my_angle = std::tuple_element<2, angle_list>::type;
            using lest::approx;

            double d = 0.001;
            my_angle a;
            a += my_angle(d);
            EXPECT(approx(d) == a());
            a += my_angle(pi * 2.0);
            EXPECT(approx(d) == a());
        }
        {
            using my_angle = std::tuple_element<3, angle_list>::type;
            using lest::approx;

            double d = 0.001;
            my_angle a;
            a += my_angle(d);
            EXPECT(approx(d) == a());
            a += my_angle(pi * 2.0);
            EXPECT(approx(d) == a());
        }
    },

    CASE("operator+ with self type")
    {
        {
            using my_angle = std::tuple_element<0, angle_list>::type;
            using lest::approx;

            EXPECT(approx(1.0) == (my_angle() + my_angle(1.0))());
            EXPECT(approx(1.0) == (my_angle() + my_angle(361.0))());
        }
        {
            using my_angle = std::tuple_element<1, angle_list>::type;
            using lest::approx;

            EXPECT(approx(1.0) == (my_angle() + my_angle(1.0))());
            EXPECT(approx(1.0) == (my_angle() + my_angle(361.0))());
        }
        {
            using my_angle = std::tuple_element<2, angle_list>::type;
            using lest::approx;

            double d = 0.001;
            EXPECT(approx(d) == (my_angle() + my_angle(d))());
            EXPECT(approx(d) == (my_angle() + my_angle(pi * 2.0 + d))());
        }
        {
            using my_angle = std::tuple_element<3, angle_list>::type;
            using lest::approx;

            double d = 0.001;
            EXPECT(approx(d) == (my_angle() + my_angle(d))());
            EXPECT(approx(d) == (my_angle() + my_angle(pi * 2.0 + d))());
        }
    },

    CASE("operator+= with double")
    {
        {
            using my_angle = std::tuple_element<0, angle_list>::type;
            using lest::approx;

            my_angle a;
            a += 1.0;
            EXPECT(approx(1.0) == a());
            a += 360.0;
            EXPECT(approx(1.0) == a());
        }
        {
            using my_angle = std::tuple_element<1, angle_list>::type;
            using lest::approx;

            my_angle a;
            a += 1.0;
            EXPECT(approx(1.0) == a());
            a += 360.0;
            EXPECT(approx(1.0) == a());
        }
        {
            using my_angle = std::tuple_element<2, angle_list>::type;
            using lest::approx;

            double d = 0.001;
            my_angle a;
            a += d;
            EXPECT(approx(d) == a());
            a += (pi * 2.0);
            EXPECT(approx(d) == a());
        }
        {
            using my_angle = std::tuple_element<3, angle_list>::type;
            using lest::approx;

            double d = 0.001;
            my_angle a;
            a += (d);
            EXPECT(approx(d) == a());
            a += (pi * 2.0);
            EXPECT(approx(d) == a());
        }
    },

    CASE("operator+ with double")
    {
        {
            using my_angle = std::tuple_element<0, angle_list>::type;
            using lest::approx;

            EXPECT(approx(1.0) == (my_angle() + 1.0)());
            EXPECT(approx(1.0) == (my_angle() + 361.0)());
        }
        {
            using my_angle = std::tuple_element<1, angle_list>::type;
            using lest::approx;

            EXPECT(approx(1.0) == (my_angle() + 1.0)());
            EXPECT(approx(1.0) == (my_angle() + 361.0)());
        }
        {
            using my_angle = std::tuple_element<2, angle_list>::type;
            using lest::approx;

            double d = 0.001;
            EXPECT(approx(d) == (my_angle() + d)());
            EXPECT(approx(d) == (my_angle() + pi * 2.0 + d)());
        }
        {
            using my_angle = std::tuple_element<3, angle_list>::type;
            using lest::approx;

            double d = 0.001;
            EXPECT(approx(d) == (my_angle() + d)());
            EXPECT(approx(d) == (my_angle() + (pi * 2.0 + d))());
        }
    },

    CASE("operator-= with self type")
    {
        {
            using my_angle = std::tuple_element<0, angle_list>::type;
            using lest::approx;

            my_angle a;
            a -= my_angle(1.0);
            EXPECT(approx(359.0) == a());
            a -= my_angle(360.0);
            EXPECT(approx(359.0) == a());
        }
        {
            using my_angle = std::tuple_element<1, angle_list>::type;
            using lest::approx;

            my_angle a;
            a -= my_angle(1.0);
            EXPECT(approx(-1.0) == a());
            a -= my_angle(360.0);
            EXPECT(approx(-1.0) == a());
        }
        {
            using my_angle = std::tuple_element<2, angle_list>::type;
            using lest::approx;

            double d = 0.001;
            my_angle a;
            a -= my_angle(d);
            EXPECT(approx(pi * 2.0 - d) == a());
            a -= my_angle(pi * 2.0);
            EXPECT(approx(pi * 2.0 - d) == a());
        }
        {
            using my_angle = std::tuple_element<3, angle_list>::type;
            using lest::approx;

            double d = 0.001;
            my_angle a;
            a -= my_angle(d);
            EXPECT(approx(-d) == a());
            a -= my_angle(pi * 2.0);
            EXPECT(approx(-d) == a());
        }
    },

    CASE("operator- with self type")
    {
        {
            using my_angle = std::tuple_element<0, angle_list>::type;
            using lest::approx;

            EXPECT(approx(359.0) == (my_angle() - my_angle(1.0))());
            EXPECT(approx(359.0) == (my_angle() - my_angle(361.0))());
        }
        {
            using my_angle = std::tuple_element<1, angle_list>::type;
            using lest::approx;

            EXPECT(approx(-1.0) == (my_angle() - my_angle(1.0))());
            EXPECT(approx(-1.0) == (my_angle() - my_angle(361.0))());
        }
        {
            using my_angle = std::tuple_element<2, angle_list>::type;
            using lest::approx;

            double d = 0.001;
            EXPECT(approx(pi * 2.0 - d) == (my_angle() - my_angle(d))());
            EXPECT(approx(pi * 2.0 - d) == (my_angle() - my_angle(pi * 2.0 + d))());
        }
        {
            using my_angle = std::tuple_element<3, angle_list>::type;
            using lest::approx;

            double d = 0.001;
            EXPECT(approx(-d) == (my_angle() - my_angle(d))());
            EXPECT(approx(-d) == (my_angle() - my_angle(pi * 2.0 + d))());
        }
    },

    CASE("operator-= with double")
    {
        {
            using my_angle = std::tuple_element<0, angle_list>::type;
            using lest::approx;

            my_angle a;
            a -= 1.0;
            EXPECT(approx(359.0) == a());
            a -= 360.0;
            EXPECT(approx(359.0) == a());
        }
        {
            using my_angle = std::tuple_element<1, angle_list>::type;
            using lest::approx;

            my_angle a;
            a -= 1.0;
            EXPECT(approx(-1.0) == a());
            a -= 360.0;
            EXPECT(approx(-1.0) == a());
        }
        {
            using my_angle = std::tuple_element<2, angle_list>::type;
            using lest::approx;

            double d = 0.001;
            my_angle a;
            a -= d;
            EXPECT(approx(pi * 2.0 - d) == a());
            a -= (pi * 2.0);
            EXPECT(approx(pi * 2.0 - d) == a());
        }
        {
            using my_angle = std::tuple_element<3, angle_list>::type;
            using lest::approx;

            double d = 0.001;
            my_angle a;
            a -= (d);
            EXPECT(approx(-d) == a());
            a -= (pi * 2.0);
            EXPECT(approx(-d) == a());
        }
    },

    CASE("operator- with double")
    {
        {
            using my_angle = std::tuple_element<0, angle_list>::type;
            using lest::approx;

            EXPECT(approx(359.0) == (my_angle() - 1.0)());
            EXPECT(approx(359.0) == (my_angle() - 361.0)());
        }
        {
            using my_angle = std::tuple_element<1, angle_list>::type;
            using lest::approx;

            EXPECT(approx(-1.0) == (my_angle() - 1.0)());
            EXPECT(approx(-1.0) == (my_angle() - 361.0)());
        }
        {
            using my_angle = std::tuple_element<2, angle_list>::type;
            using lest::approx;

            double d = 0.001;
            EXPECT(approx(pi * 2.0 - d) == (my_angle() - d)());
            EXPECT(approx(pi * 2.0 - d) == (my_angle() - (pi * 2.0 + d))());
        }
        {
            using my_angle = std::tuple_element<3, angle_list>::type;
            using lest::approx;

            double d = 0.001;
            EXPECT(approx(-d) == (my_angle() - d)());
            EXPECT(approx(-d) == (my_angle() - (pi * 2.0 + d))());
        }
    },

    CASE("operator*=")
    {
        {
            using my_angle = std::tuple_element<0, angle_list>::type;
            using lest::approx;

            my_angle a(90.0);
            a *= 0.5;
            EXPECT(approx(45.0) == a());
            a *= 5.0;
            EXPECT(approx(225.0) == a());
            a *= 5.0;
            EXPECT(approx(45.0) == a());
        }
        {
            using my_angle = std::tuple_element<1, angle_list>::type;
            using lest::approx;

            my_angle a(90.0);
            a *= 0.5;
            EXPECT(approx(45.0) == a());
            a *= 5.0;
            EXPECT(approx(-135.0) == a());
            a *= 5.0;
            EXPECT(approx(45.0) == a());
        }
        {
            using my_angle = std::tuple_element<2, angle_list>::type;
            using lest::approx;

            my_angle a(pi * 0.5);
            a *= 0.5;
            EXPECT(approx(pi * 0.25) == a());
            a *= 5.0;
            EXPECT(approx(pi * 1.25) == a());
            a *= 5.0;
            EXPECT(approx(pi * 0.25) == a());
        }
        {
            using my_angle = std::tuple_element<3, angle_list>::type;
            using lest::approx;

            my_angle a(pi * 0.5);
            a *= 0.5;
            EXPECT(approx(pi * 0.25) == a());
            a *= 5.0;
            EXPECT(approx(pi * -0.75) == a());
            a *= 5.0;
            EXPECT(approx(pi * 0.25) == a());
        }
    },

    CASE("operator*")
    {
        {
            using my_angle = std::tuple_element<0, angle_list>::type;
            using lest::approx;

            my_angle a(90.0);
            EXPECT(approx(45.0) == (a * 0.5)());
            EXPECT(approx(225.0) == ((a * 0.5) * 5.0)());
            EXPECT(approx(45.0) == (((a * 0.5) * 5.0) * 5.0)());
        }
        {
            using my_angle = std::tuple_element<1, angle_list>::type;
            using lest::approx;

            my_angle a(90.0);
            EXPECT(approx(45.0) == (a * 0.5)());
            EXPECT(approx(-135.0) == ((a * 0.5) * 5.0)());
            EXPECT(approx(45.0) == (((a * 0.5) * 5.0) * 5.0)());
        }
        {
            using my_angle = std::tuple_element<2, angle_list>::type;
            using lest::approx;

            my_angle a(pi * 0.5);
            EXPECT(approx(pi * 0.25) == (a * 0.5)());
            EXPECT(approx(pi * 1.25) == ((a * 0.5) * 5.0)());
            EXPECT(approx(pi * 0.25) == (((a * 0.5) * 5.0) * 5.0)());
        }
        {
            using my_angle = std::tuple_element<3, angle_list>::type;
            using lest::approx;

            my_angle a(pi * 0.5);
            EXPECT(approx(pi * 0.25) == (a * 0.5)());
            EXPECT(approx(pi * -0.75) == ((a * 0.5) * 5.0)());
            EXPECT(approx(pi * 0.25) == (((a * 0.5) * 5.0) * 5.0)());
        }
    },

    CASE("operator/=")
    {
        {
            using my_angle = std::tuple_element<0, angle_list>::type;
            using lest::approx;

            my_angle a(90.0);
            a /= 2.0;
            EXPECT(approx(45.0) == a());
        }
        {
            using my_angle = std::tuple_element<1, angle_list>::type;
            using lest::approx;

            my_angle a(90.0);
            a /= 2.0;
            EXPECT(approx(45.0) == a());
        }
        {
            using my_angle = std::tuple_element<2, angle_list>::type;
            using lest::approx;

            my_angle a(pi * 0.5);
            a /= 2.0;
            EXPECT(approx(pi * 0.25) == a());
        }
        {
            using my_angle = std::tuple_element<3, angle_list>::type;
            using lest::approx;

            my_angle a(pi * 0.5);
            a /= 2.0;
            EXPECT(approx(pi * 0.25) == a());
        }
    },

    CASE("operator/")
    {
        {
            using my_angle = std::tuple_element<0, angle_list>::type;
            using lest::approx;

            my_angle a(90.0);
            EXPECT(approx(45.0) == (a / 2.0)());
        }
        {
            using my_angle = std::tuple_element<1, angle_list>::type;
            using lest::approx;

            my_angle a(90.0);
            EXPECT(approx(45.0) == (a / 2.0)());
        }
        {
            using my_angle = std::tuple_element<2, angle_list>::type;
            using lest::approx;

            my_angle a(pi * 0.5);
            EXPECT(approx(pi * 0.25) == (a / 2.0)());
        }
        {
            using my_angle = std::tuple_element<3, angle_list>::type;
            using lest::approx;

            my_angle a(pi * 0.5);
            EXPECT(approx(pi * 0.25) == (a / 2.0)());
        }
    },

    CASE("operator()")
    {
        // same test with "constructor with one argument"
        {
            using my_angle = std::tuple_element<0, angle_list>::type;
            using lest::approx;

            EXPECT(approx(179.0) == my_angle(-181.0)());
            EXPECT(approx(180.0) == my_angle(-180.0)());
            EXPECT(approx(181.0) == my_angle(-179.0)());
            EXPECT(approx(359.0) == my_angle(-1.0)());
            EXPECT(approx(0.0) == my_angle(0.0)());
            EXPECT(approx(1.0) == my_angle(1.0)());
            EXPECT(approx(359.0) == my_angle(359.0)());
            EXPECT(approx(0.0) == my_angle(360.0)());
            EXPECT(approx(1.0) == my_angle(361.0)());
            EXPECT(approx(1.0) == my_angle(360000001.0)());
            EXPECT(approx(359.0) == my_angle(-360000001.0)());
        }
        {
            using my_angle = std::tuple_element<1, angle_list>::type;
            using lest::approx;

            EXPECT(approx(179.0) == my_angle(-181.0)());
            EXPECT(approx(-180.0) == my_angle(-180.0)());
            EXPECT(approx(-179.0) == my_angle(-179.0)());
            EXPECT(approx(-1.0) == my_angle(-1.0)());
            EXPECT(approx(0.0) == my_angle(0.0)());
            EXPECT(approx(1.0) == my_angle(1.0)());
            EXPECT(approx(-1.0) == my_angle(359.0)());
            EXPECT(approx(0.0) == my_angle(360.0)());
            EXPECT(approx(1.0) == my_angle(361.0)());
            EXPECT(approx(1.0) == my_angle(360000001.0)());
            EXPECT(approx(-1.0) == my_angle(-360000001.0)());
        }
        {
            using my_angle = std::tuple_element<2, angle_list>::type;
            using lest::approx;

            double d = 0.001;
            EXPECT(approx(pi - d) == my_angle(-pi - d)());
            EXPECT(approx(pi) == my_angle(-pi)());
            EXPECT(approx(pi + d) == my_angle(-pi + d)());
            EXPECT(approx(pi * 2.0 - d) == my_angle(-d)());
            EXPECT(approx(0.0) == my_angle(0.0)());
            EXPECT(approx(d) == my_angle(d)());
            EXPECT(approx(pi * 2.0 - d) == my_angle(pi * 2.0 - d)());
            EXPECT(approx(0.0) == my_angle(pi * 2.0)());
            EXPECT(approx(d) == my_angle(pi * 2.0 + d)());
            EXPECT(approx(d) == my_angle(pi * 20000.0 + d)());
            EXPECT(approx(pi * 2.0 - d) == my_angle(pi * -20000.0 - d)());
        }
        {
            using my_angle = std::tuple_element<3, angle_list>::type;
            using lest::approx;

            double d = 0.001;
            EXPECT(approx(pi - d) == my_angle(-pi - d)());
            EXPECT(approx(-pi) == my_angle(-pi)());
            EXPECT(approx(-pi + d) == my_angle(-pi + d)());
            EXPECT(approx(-d) == my_angle(-d)());
            EXPECT(approx(0.0) == my_angle(0.0)());
            EXPECT(approx(d) == my_angle(d)());
            EXPECT(approx(-d) == my_angle(pi * 2.0 - d)());
            EXPECT(approx(0.0) == my_angle(pi * 2.0)());
            EXPECT(approx(d) == my_angle(pi * 2.0 + d)());
            EXPECT(approx(d) == my_angle(pi * 20000.0 + d)());
            EXPECT(approx(-d) == my_angle(pi * -20000.0 - d)());
        }
    },

    CASE("degree()")
    {
        {
            using my_angle = std::tuple_element<0, angle_list>::type;
            using lest::approx;

            EXPECT(approx(179.0) == my_angle(-181.0).degree());
            EXPECT(approx(180.0) == my_angle(-180.0).degree());
            EXPECT(approx(181.0) == my_angle(-179.0).degree());
            EXPECT(approx(359.0) == my_angle(-1.0).degree());
            EXPECT(approx(0.0) == my_angle(0.0).degree());
            EXPECT(approx(1.0) == my_angle(1.0).degree());
            EXPECT(approx(359.0) == my_angle(359.0).degree());
            EXPECT(approx(0.0) == my_angle(360.0).degree());
            EXPECT(approx(1.0) == my_angle(361.0).degree());
            EXPECT(approx(1.0) == my_angle(360000001.0).degree());
            EXPECT(approx(359.0) == my_angle(-360000001.0).degree());
        }
        {
            using my_angle = std::tuple_element<1, angle_list>::type;
            using lest::approx;

            EXPECT(approx(179.0) == my_angle(-181.0).degree());
            EXPECT(approx(-180.0) == my_angle(-180.0).degree());
            EXPECT(approx(-179.0) == my_angle(-179.0).degree());
            EXPECT(approx(-1.0) == my_angle(-1.0).degree());
            EXPECT(approx(0.0) == my_angle(0.0).degree());
            EXPECT(approx(1.0) == my_angle(1.0).degree());
            EXPECT(approx(-1.0) == my_angle(359.0).degree());
            EXPECT(approx(0.0) == my_angle(360.0).degree());
            EXPECT(approx(1.0) == my_angle(361.0).degree());
            EXPECT(approx(1.0) == my_angle(360000001.0).degree());
            EXPECT(approx(-1.0) == my_angle(-360000001.0).degree());
        }
        {
            using my_angle = std::tuple_element<2, angle_list>::type;
            using lest::approx;

            double d = 0.001;
            EXPECT(approx((pi - d) * r2d) == my_angle(-pi - d).degree());
            EXPECT(approx((pi) * r2d) == my_angle(-pi).degree());
            EXPECT(approx((pi + d) * r2d) == my_angle(-pi + d).degree());
            EXPECT(approx((pi * 2.0 - d) * r2d) == my_angle(-d).degree());
            EXPECT(approx((0.0) * r2d) == my_angle(0.0).degree());
            EXPECT(approx((d) * r2d) == my_angle(d).degree());
            EXPECT(approx((pi * 2.0 - d) * r2d) == my_angle(pi * 2.0 - d).degree());
            EXPECT(approx((0.0) * r2d) == my_angle(pi * 2.0).degree());
            EXPECT(approx((d) * r2d) == my_angle(pi * 2.0 + d).degree());
            EXPECT(approx((d) * r2d) == my_angle(pi * 20000.0 + d).degree());
            EXPECT(approx((pi * 2.0 - d) * r2d) == my_angle(pi * -20000.0 - d).degree());
        }
        {
            using my_angle = std::tuple_element<3, angle_list>::type;
            using lest::approx;

            double d = 0.001;
            EXPECT(approx((pi - d) * r2d) == my_angle(-pi - d).degree());
            EXPECT(approx((-pi) * r2d) == my_angle(-pi).degree());
            EXPECT(approx((-pi + d) * r2d) == my_angle(-pi + d).degree());
            EXPECT(approx((-d) * r2d) == my_angle(-d).degree());
            EXPECT(approx((0.0) * r2d) == my_angle(0.0).degree());
            EXPECT(approx((d) * r2d) == my_angle(d).degree());
            EXPECT(approx((-d) * r2d) == my_angle(pi * 2.0 - d).degree());
            EXPECT(approx((0.0) * r2d) == my_angle(pi * 2.0).degree());
            EXPECT(approx((d) * r2d) == my_angle(pi * 2.0 + d).degree());
            EXPECT(approx((d) * r2d) == my_angle(pi * 20000.0 + d).degree());
            EXPECT(approx((-d) * r2d) == my_angle(pi * -20000.0 - d).degree());
        }
    },

    CASE("radian()")
    {
        {
            using my_angle = std::tuple_element<0, angle_list>::type;
            using lest::approx;

            EXPECT(approx(179.0 * d2r) == my_angle(-181.0).radian());
            EXPECT(approx(180.0 * d2r) == my_angle(-180.0).radian());
            EXPECT(approx(181.0 * d2r) == my_angle(-179.0).radian());
            EXPECT(approx(359.0 * d2r) == my_angle(-1.0).radian());
            EXPECT(approx(0.0 * d2r) == my_angle(0.0).radian());
            EXPECT(approx(1.0 * d2r) == my_angle(1.0).radian());
            EXPECT(approx(359.0 * d2r) == my_angle(359.0).radian());
            EXPECT(approx(0.0 * d2r) == my_angle(360.0).radian());
            EXPECT(approx(1.0 * d2r) == my_angle(361.0).radian());
            EXPECT(approx(1.0 * d2r) == my_angle(360000001.0).radian());
            EXPECT(approx(359.0 * d2r) == my_angle(-360000001.0).radian());
        }
        {
            using my_angle = std::tuple_element<1, angle_list>::type;
            using lest::approx;

            EXPECT(approx(179.0 * d2r) == my_angle(-181.0).radian());
            EXPECT(approx(-180.0 * d2r) == my_angle(-180.0).radian());
            EXPECT(approx(-179.0 * d2r) == my_angle(-179.0).radian());
            EXPECT(approx(-1.0 * d2r) == my_angle(-1.0).radian());
            EXPECT(approx(0.0 * d2r) == my_angle(0.0).radian());
            EXPECT(approx(1.0 * d2r) == my_angle(1.0).radian());
            EXPECT(approx(-1.0 * d2r) == my_angle(359.0).radian());
            EXPECT(approx(0.0 * d2r) == my_angle(360.0).radian());
            EXPECT(approx(1.0 * d2r) == my_angle(361.0).radian());
            EXPECT(approx(1.0 * d2r) == my_angle(360000001.0).radian());
            EXPECT(approx(-1.0 * d2r) == my_angle(-360000001.0).radian());
        }
        {
            using my_angle = std::tuple_element<2, angle_list>::type;
            using lest::approx;

            double d = 0.001;
            EXPECT(approx(pi - d) == my_angle(-pi - d).radian());
            EXPECT(approx(pi) == my_angle(-pi).radian());
            EXPECT(approx(pi + d) == my_angle(-pi + d).radian());
            EXPECT(approx(pi * 2.0 - d) == my_angle(-d).radian());
            EXPECT(approx(0.0) == my_angle(0.0).radian());
            EXPECT(approx(d) == my_angle(d).radian());
            EXPECT(approx(pi * 2.0 - d) == my_angle(pi * 2.0 - d).radian());
            EXPECT(approx(0.0) == my_angle(pi * 2.0).radian());
            EXPECT(approx(d) == my_angle(pi * 2.0 + d).radian());
            EXPECT(approx(d) == my_angle(pi * 20000.0 + d).radian());
            EXPECT(approx(pi * 2.0 - d) == my_angle(pi * -20000.0 - d).radian());
        }
        {
            using my_angle = std::tuple_element<3, angle_list>::type;
            using lest::approx;

            double d = 0.001;
            EXPECT(approx(pi - d) == my_angle(-pi - d).radian());
            EXPECT(approx(-pi) == my_angle(-pi).radian());
            EXPECT(approx(-pi + d) == my_angle(-pi + d).radian());
            EXPECT(approx(-d) == my_angle(-d).radian());
            EXPECT(approx(0.0) == my_angle(0.0).radian());
            EXPECT(approx(d) == my_angle(d).radian());
            EXPECT(approx(-d) == my_angle(pi * 2.0 - d).radian());
            EXPECT(approx(0.0) == my_angle(pi * 2.0).radian());
            EXPECT(approx(d) == my_angle(pi * 2.0 + d).radian());
            EXPECT(approx(d) == my_angle(pi * 20000.0 + d).radian());
            EXPECT(approx(-d) == my_angle(pi * -20000.0 - d).radian());
        }
    },

    CASE("set()")
    {
        // same test with "constructor with one argument"
        {
            using my_angle = std::tuple_element<0, angle_list>::type;
            using lest::approx;

            my_angle a;
            a.set(-181.0);
            EXPECT(approx(179.0) == a());
            a.set(-180.0);
            EXPECT(approx(180.0) == a());
            a.set(-179.0);
            EXPECT(approx(181.0) == a());
            a.set(-1.0);
            EXPECT(approx(359.0) == a());
            a.set(0.0);
            EXPECT(approx(0.0) == a());
            a.set(1.0);
            EXPECT(approx(1.0) == a());
            a.set(359.0);
            EXPECT(approx(359.0) == a());
            a.set(360.0);
            EXPECT(approx(0.0) == a());
            a.set(361.0);
            EXPECT(approx(1.0) == a());
            a.set(360000001.0);
            EXPECT(approx(1.0) == a());
            a.set(-360000001.0);
            EXPECT(approx(359.0) == a());
        }
        {
            using my_angle = std::tuple_element<1, angle_list>::type;
            using lest::approx;

            my_angle a;
            a.set(-181.0);
            EXPECT(approx(179.0) == a());
            a.set(-180.0);
            EXPECT(approx(-180.0) == a());
            a.set(-179.0);
            EXPECT(approx(-179.0) == a());
            a.set(-1.0);
            EXPECT(approx(-1.0) == a());
            a.set(0.0);
            EXPECT(approx(0.0) == a());
            a.set(1.0);
            EXPECT(approx(1.0) == a());
            a.set(359.0);
            EXPECT(approx(-1.0) == a());
            a.set(360.0);
            EXPECT(approx(0.0) == a());
            a.set(361.0);
            EXPECT(approx(1.0) == a());
            a.set(360000001.0);
            EXPECT(approx(1.0) == a());
            a.set(-360000001.0);
            EXPECT(approx(-1.0) == a());
        }
        {
            using my_angle = std::tuple_element<2, angle_list>::type;
            using lest::approx;

            double d = 0.001;
            my_angle a;
            a.set(-pi - d);
            EXPECT(approx(pi - d) == a());
            a.set(-pi);
            EXPECT(approx(pi) == a());
            a.set(-pi + d);
            EXPECT(approx(pi + d) == a());
            a.set(-d);
            EXPECT(approx(pi * 2.0 - d) == a());
            a.set(0.0);
            EXPECT(approx(0.0) == a());
            a.set(d);
            EXPECT(approx(d) == a());
            a.set(pi * 2.0 - d);
            EXPECT(approx(pi * 2.0 - d) == a());
            a.set(pi * 2.0);
            EXPECT(approx(0.0) == a());
            a.set(pi * 2.0 + d);
            EXPECT(approx(d) == a());
            a.set(pi * 20000.0 + d);
            EXPECT(approx(d) == a());
            a.set(pi * -20000.0 - d);
            EXPECT(approx(pi * 2.0 - d) == a());
        }
        {
            using my_angle = std::tuple_element<3, angle_list>::type;
            using lest::approx;

            double d = 0.001;
            my_angle a;
            a.set(-pi - d);
            EXPECT(approx(pi - d) == a());
            a.set(-pi);
            EXPECT(approx(-pi) == a());
            a.set(-pi + d);
            EXPECT(approx(-pi + d) == a());
            a.set(-d);
            EXPECT(approx(-d) == a());
            a.set(0.0);
            EXPECT(approx(0.0) == a());
            a.set(d);
            EXPECT(approx(d) == a());
            a.set(pi * 2.0 - d);
            EXPECT(approx(-d) == a());
            a.set(pi * 2.0);
            EXPECT(approx(0.0) == a());
            a.set(pi * 2.0 + d);
            EXPECT(approx(d) == a());
            a.set(pi * 20000.0 + d);
            EXPECT(approx(d) == a());
            a.set(pi * -20000.0 - d);
            EXPECT(approx(-d) == a());
        }
    },

    CASE("set_degree()")
    {
        {
            using my_angle = std::tuple_element<0, angle_list>::type;
            using lest::approx;

            my_angle a;
            a.set_degree(-181.0);
            EXPECT(approx(179.0) == a());
            a.set_degree(-180.0);
            EXPECT(approx(180.0) == a());
            a.set_degree(-179.0);
            EXPECT(approx(181.0) == a());
            a.set_degree(-1.0);
            EXPECT(approx(359.0) == a());
            a.set_degree(0.0);
            EXPECT(approx(0.0) == a());
            a.set_degree(1.0);
            EXPECT(approx(1.0) == a());
            a.set_degree(359.0);
            EXPECT(approx(359.0) == a());
            a.set_degree(360.0);
            EXPECT(approx(0.0) == a());
            a.set_degree(361.0);
            EXPECT(approx(1.0) == a());
            a.set_degree(360000001.0);
            EXPECT(approx(1.0) == a());
            a.set_degree(-360000001.0);
            EXPECT(approx(359.0) == a());
        }
        {
            using my_angle = std::tuple_element<1, angle_list>::type;
            using lest::approx;

            my_angle a;
            a.set_degree(-181.0);
            EXPECT(approx(179.0) == a());
            a.set_degree(-180.0);
            EXPECT(approx(-180.0) == a());
            a.set_degree(-179.0);
            EXPECT(approx(-179.0) == a());
            a.set_degree(-1.0);
            EXPECT(approx(-1.0) == a());
            a.set_degree(0.0);
            EXPECT(approx(0.0) == a());
            a.set_degree(1.0);
            EXPECT(approx(1.0) == a());
            a.set_degree(359.0);
            EXPECT(approx(-1.0) == a());
            a.set_degree(360.0);
            EXPECT(approx(0.0) == a());
            a.set_degree(361.0);
            EXPECT(approx(1.0) == a());
            a.set_degree(360000001.0);
            EXPECT(approx(1.0) == a());
            a.set_degree(-360000001.0);
            EXPECT(approx(-1.0) == a());
        }
        {
            using my_angle = std::tuple_element<2, angle_list>::type;
            using lest::approx;

            double d = 0.001;
            my_angle a;
            a.set_degree((-pi - d) * r2d);
            EXPECT(approx(pi - d) == a());
            a.set_degree((-pi) * r2d);
            EXPECT(approx(pi) == a());
            a.set_degree((-pi + d) * r2d);
            EXPECT(approx(pi + d) == a());
            a.set_degree((-d) * r2d);
            EXPECT(approx(pi * 2.0 - d) == a());
            a.set_degree((0.0) * r2d);
            EXPECT(approx(0.0) == a());
            a.set_degree((d) * r2d);
            EXPECT(approx(d) == a());
            a.set_degree((pi * 2.0 - d) * r2d);
            EXPECT(approx(pi * 2.0 - d) == a());
            a.set_degree((pi * 2.0) * r2d);
            EXPECT(approx(0.0) == a());
            a.set_degree((pi * 2.0 + d) * r2d);
            EXPECT(approx(d) == a());
            a.set_degree((pi * 20000.0 + d) * r2d);
            EXPECT(approx(d) == a());
            a.set_degree((pi * -20000.0 - d) * r2d);
            EXPECT(approx(pi * 2.0 - d) == a());
        }
        {
            using my_angle = std::tuple_element<3, angle_list>::type;
            using lest::approx;

            double d = 0.001;
            my_angle a;
            a.set_degree((-pi - d) * r2d);
            EXPECT(approx(pi - d) == a());
            a.set_degree((-pi) * r2d);
            EXPECT(approx(-pi) == a());
            a.set_degree((-pi + d) * r2d);
            EXPECT(approx(-pi + d) == a());
            a.set_degree((-d) * r2d);
            EXPECT(approx(-d) == a());
            a.set_degree((0.0) * r2d);
            EXPECT(approx(0.0) == a());
            a.set_degree((d) * r2d);
            EXPECT(approx(d) == a());
            a.set_degree((pi * 2.0 - d) * r2d);
            EXPECT(approx(-d) == a());
            a.set_degree((pi * 2.0) * r2d);
            EXPECT(approx(0.0) == a());
            a.set_degree((pi * 2.0 + d) * r2d);
            EXPECT(approx(d) == a());
            a.set_degree((pi * 20000.0 + d) * r2d);
            EXPECT(approx(d) == a());
            a.set_degree((pi * -20000.0 - d) * r2d);
            EXPECT(approx(-d) == a());
        }
    },

    CASE("set_radian()")
    {
        {
            using my_angle = std::tuple_element<0, angle_list>::type;
            using lest::approx;

            my_angle a;
            a.set_radian((-181.0) * d2r);
            EXPECT(approx(179.0) == a());
            a.set_radian((-180.0) * d2r);
            EXPECT(approx(180.0) == a());
            a.set_radian((-179.0) * d2r);
            EXPECT(approx(181.0) == a());
            a.set_radian((-1.0) * d2r);
            EXPECT(approx(359.0) == a());
            a.set_radian((0.0) * d2r);
            EXPECT(approx(0.0) == a());
            a.set_radian((1.0) * d2r);
            EXPECT(approx(1.0) == a());
            a.set_radian((359.0) * d2r);
            EXPECT(approx(359.0) == a());
            a.set_radian((360.0) * d2r);
            EXPECT(approx(0.0) == a());
            a.set_radian((361.0) * d2r);
            EXPECT(approx(1.0) == a());
            a.set_radian((360000001.0) * d2r);
            EXPECT(approx(1.0) == a());
            a.set_radian((-360000001.0) * d2r);
            EXPECT(approx(359.0) == a());
        }
        {
            using my_angle = std::tuple_element<1, angle_list>::type;
            using lest::approx;

            my_angle a;
            a.set_radian((-181.0) * d2r);
            EXPECT(approx(179.0) == a());
            a.set_radian((-180.0) * d2r);
            EXPECT(approx(-180.0) == a());
            a.set_radian((-179.0) * d2r);
            EXPECT(approx(-179.0) == a());
            a.set_radian((-1.0) * d2r);
            EXPECT(approx(-1.0) == a());
            a.set_radian((0.0) * d2r);
            EXPECT(approx(0.0) == a());
            a.set_radian((1.0) * d2r);
            EXPECT(approx(1.0) == a());
            a.set_radian((359.0) * d2r);
            EXPECT(approx(-1.0) == a());
            a.set_radian((360.0) * d2r);
            EXPECT(approx(0.0) == a());
            a.set_radian((361.0) * d2r);
            EXPECT(approx(1.0) == a());
            a.set_radian((360000001.0) * d2r);
            EXPECT(approx(1.0) == a());
            a.set_radian((-360000001.0) * d2r);
            EXPECT(approx(-1.0) == a());
        }
        {
            using my_angle = std::tuple_element<2, angle_list>::type;
            using lest::approx;

            double d = 0.001;
            my_angle a;
            a.set_radian(-pi - d);
            EXPECT(approx(pi - d) == a());
            a.set_radian(-pi);
            EXPECT(approx(pi) == a());
            a.set_radian(-pi + d);
            EXPECT(approx(pi + d) == a());
            a.set_radian(-d);
            EXPECT(approx(pi * 2.0 - d) == a());
            a.set_radian(0.0);
            EXPECT(approx(0.0) == a());
            a.set_radian(d);
            EXPECT(approx(d) == a());
            a.set_radian(pi * 2.0 - d);
            EXPECT(approx(pi * 2.0 - d) == a());
            a.set_radian(pi * 2.0);
            EXPECT(approx(0.0) == a());
            a.set_radian(pi * 2.0 + d);
            EXPECT(approx(d) == a());
            a.set_radian(pi * 20000.0 + d);
            EXPECT(approx(d) == a());
            a.set_radian(pi * -20000.0 - d);
            EXPECT(approx(pi * 2.0 - d) == a());
        }
        {
            using my_angle = std::tuple_element<3, angle_list>::type;
            using lest::approx;

            double d = 0.001;
            my_angle a;
            a.set_radian(-pi - d);
            EXPECT(approx(pi - d) == a());
            a.set_radian(-pi);
            EXPECT(approx(-pi) == a());
            a.set_radian(-pi + d);
            EXPECT(approx(-pi + d) == a());
            a.set_radian(-d);
            EXPECT(approx(-d) == a());
            a.set_radian(0.0);
            EXPECT(approx(0.0) == a());
            a.set_radian(d);
            EXPECT(approx(d) == a());
            a.set_radian(pi * 2.0 - d);
            EXPECT(approx(-d) == a());
            a.set_radian(pi * 2.0);
            EXPECT(approx(0.0) == a());
            a.set_radian(pi * 2.0 + d);
            EXPECT(approx(d) == a());
            a.set_radian(pi * 20000.0 + d);
            EXPECT(approx(d) == a());
            a.set_radian(pi * -20000.0 - d);
            EXPECT(approx(-d) == a());
        }
    },

};

int main(int argc, char* argv[])
{
    return lest::run(specification, argc, argv);
}
/////////////////////////////////////////////////////////////////////////////

