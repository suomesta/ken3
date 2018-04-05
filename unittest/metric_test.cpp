/**
 * @file    unittest/metric_test.cpp
 * @brief   Testing ken3::metric using lest. 
 * @author  toda
 * @date    2017-01-24
 * @version 0.1.0
 * @remark  the target is C++11 or more
 */

#include <type_traits>
#include "ken3/metric.hpp"
#include "unittest/lest.hpp"

const lest::test specification[] =
{

    CASE("basic functions")
    {
        using namespace ken3::metric;
        using lest::approx;

        EXPECT(approx(1.0 / 1852.0) == (convert<metre, nauticalmile>(1.0)));
    },

    CASE("length")
    {
        using namespace ken3::metric;
        using lest::approx;

        // with metre
        EXPECT(approx(1.0 / 1.0) == (convert<metre, si>(1.0)));
        EXPECT(approx(2.0 / 1.0) == (convert<metre, metre>(2.0)));
        EXPECT(approx(3.0 / 1852.0) == (convert<metre, nauticalmile>(3.0)));
        EXPECT(approx(4.0 / 0.9144) == (convert<metre, yard>(4.0)));
        EXPECT(approx(5.0 / 1000.0) == (convert<metre, kilometre>(5.0)));
        EXPECT(approx(6.0 / 914.4) == (convert<metre, kiloyard>(6.0)));
        EXPECT(approx(6.0 * 1.0) == (convert<si, metre>(6.0)));
        EXPECT(approx(5.0 * 1.0) == (convert<metre, metre>(5.0)));
        EXPECT(approx(4.0 * 1852.0) == (convert<nauticalmile, metre>(4.0)));
        EXPECT(approx(3.0 * 0.9144) == (convert<yard, metre>(3.0)));
        EXPECT(approx(2.0 * 1000.0) == (convert<kilometre, metre>(2.0)));
        EXPECT(approx(1.0 * 914.4) == (convert<kiloyard, metre>(1.0)));
        // without metre
        EXPECT(approx(1.0 * 1852.0 / 0.9144) == (convert<nauticalmile, yard>(1.0)));
        EXPECT(approx(2.0 * 1852.0 / 1000.0) == (convert<nauticalmile, kilometre>(2.0)));
        EXPECT(approx(3.0 * 1852.0 / 914.4) == (convert<nauticalmile, kiloyard>(3.0)));
        EXPECT(approx(3.0 * 0.9144 / 1852.0) == (convert<yard, nauticalmile>(3.0)));
        EXPECT(approx(2.0 * 0.9144 / 1000.0) == (convert<yard, kilometre>(2.0)));
        EXPECT(approx(1.0 * 0.9144 / 914.4) == (convert<yard, kiloyard>(1.0)));
        EXPECT(approx(1.0 * 1000.0 / 1852.0) == (convert<kilometre, nauticalmile>(1.0)));
        EXPECT(approx(2.0 * 1000.0 / 0.9144) == (convert<kilometre, yard>(2.0)));
        EXPECT(approx(3.0 * 1000.0 / 914.4) == (convert<kilometre, kiloyard>(3.0)));
        EXPECT(approx(3.0 * 914.4 / 1852.0) == (convert<kiloyard, nauticalmile>(3.0)));
        EXPECT(approx(2.0 * 914.4 / 0.9144) == (convert<kiloyard, yard>(2.0)));
        EXPECT(approx(1.0 * 914.4 / 1000.0) == (convert<kiloyard, kilometre>(1.0)));
    },

    CASE("time")
    {
        using namespace ken3::metric;
        using lest::approx;

        // with second
        EXPECT(approx(1.0 / 1.0) == (convert<second, si>(1.0)));
        EXPECT(approx(2.0 / 1.0) == (convert<second, second>(2.0)));
        EXPECT(approx(3.0 / 60.0) == (convert<second, minute>(3.0)));
        EXPECT(approx(4.0 / 3600.0) == (convert<second, hour>(4.0)));
        EXPECT(approx(5.0 / 86400.0) == (convert<second, day>(5.0)));
        EXPECT(approx(6.0 / 604800.0) == (convert<second, week>(6.0)));
        EXPECT(approx(6.0 * 1.0) == (convert<si, second>(6.0)));
        EXPECT(approx(5.0 * 1.0) == (convert<second, second>(5.0)));
        EXPECT(approx(4.0 * 60.0) == (convert<minute, second>(4.0)));
        EXPECT(approx(3.0 * 3600.0) == (convert<hour, second>(3.0)));
        EXPECT(approx(2.0 * 86400.0) == (convert<day, second>(2.0)));
        EXPECT(approx(1.0 * 604800.0) == (convert<week, second>(1.0)));
        // without second
        EXPECT(approx(1.0 * 60.0 / 3600.0) == (convert<minute, hour>(1.0)));
        EXPECT(approx(2.0 * 60.0 / 86400.0) == (convert<minute, day>(2.0)));
        EXPECT(approx(3.0 * 60.0 / 604800.0) == (convert<minute, week>(3.0)));
        EXPECT(approx(3.0 * 3600.0 / 60.0) == (convert<hour, minute>(3.0)));
        EXPECT(approx(2.0 * 3600.0 / 86400.0) == (convert<hour, day>(2.0)));
        EXPECT(approx(1.0 * 3600.0 / 604800.0) == (convert<hour, week>(1.0)));
        EXPECT(approx(1.0 * 86400.0 / 60.0) == (convert<day, minute>(1.0)));
        EXPECT(approx(2.0 * 86400.0 / 3600.0) == (convert<day, hour>(2.0)));
        EXPECT(approx(3.0 * 86400.0 / 604800.0) == (convert<day, week>(3.0)));
        EXPECT(approx(3.0 * 604800.0 / 60.0) == (convert<week, minute>(3.0)));
        EXPECT(approx(2.0 * 604800.0 / 3600.0) == (convert<week, hour>(2.0)));
        EXPECT(approx(1.0 * 604800.0 / 86400.0) == (convert<week, day>(1.0)));
    },

    CASE("speed")
    {
        using namespace ken3::metric;
        using lest::approx;

        // with metre_per_second
        EXPECT(approx(1.0 / 1.0) == (convert<metre_per_second, si>(1.0)));
        EXPECT(approx(2.0 / 1.0) == (convert<metre_per_second, metre_per_second>(2.0)));
        EXPECT(approx(3.0 / (1000.0 / 3600.0)) == (convert<metre_per_second, kilometre_per_hour>(3.0)));
        EXPECT(approx(4.0 / (1852.0 / 3600.0)) == (convert<metre_per_second, knot>(4.0)));
        EXPECT(approx(4.0 * 1.0) == (convert<si, metre_per_second>(4.0)));
        EXPECT(approx(3.0 * 1.0) == (convert<metre_per_second, metre_per_second>(3.0)));
        EXPECT(approx(2.0 * (1000.0 / 3600.0)) == (convert<kilometre_per_hour, metre_per_second>(2.0)));
        EXPECT(approx(1.0 * (1852.0 / 3600.0)) == (convert<knot, metre_per_second>(1.0)));
        // without metre_per_second
        EXPECT(approx(1.0 * (1000.0 / 3600.0) / (1852.0 / 3600.0)) == (convert<kilometre_per_hour, knot>(1.0)));
        EXPECT(approx(1.0 * (1852.0 / 3600.0) / (1000.0 / 3600.0)) == (convert<knot, kilometre_per_hour>(1.0)));
    },

    CASE("add unit")
    {
        using namespace ken3::metric;
        using lest::approx;

        // define [cm]
        using centimetre = ken3::metric::unit<ken3::metric::length, std::ratio<1, 100>>;

        EXPECT(approx(10.0) == (convert<centimetre, metre>(1000)));
    },

    CASE("return value type")
    {
        using namespace ken3::metric;

        auto c = convert<si, si>(static_cast<char>(1));
        EXPECT((std::is_same<double, decltype(c)>::value));
        auto s = convert<si, si>(static_cast<short>(1));
        EXPECT((std::is_same<double, decltype(s)>::value));
        auto i = convert<si, si>(static_cast<int>(1));
        EXPECT((std::is_same<double, decltype(i)>::value));
        auto l = convert<si, si>(static_cast<long>(1));
        EXPECT((std::is_same<double, decltype(l)>::value));
        auto ll = convert<si, si>(static_cast<long long>(1));
        EXPECT((std::is_same<double, decltype(ll)>::value));
        auto f = convert<si, si>(static_cast<float>(1));
        EXPECT((std::is_same<double, decltype(f)>::value));
        auto d = convert<si, si>(static_cast<double>(1));
        EXPECT((std::is_same<double, decltype(d)>::value));
        auto ld = convert<si, si>(static_cast<long double>(1));
        EXPECT((std::is_same<long double, decltype(ld)>::value));
    },

};

int main(int argc, char* argv[])
{
    return lest::run(specification, argc, argv);
}
/////////////////////////////////////////////////////////////////////////////

