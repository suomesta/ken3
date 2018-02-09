/**
 * @file    metric_test.cpp
 * @brief   Implementation of MetricTest class and main function. 
 * @author  toda
 * @date    2017-01-24
 * @version 0.1.0
 * @remark  the target is C++11 or more
 */

#include <cmath>
#include <limits>
#include <type_traits>
#include "ken3/metric.hpp"
#include "unittest/lest.hpp"

namespace {

// constants
constexpr double rad2deg = 3.14159265358979323846 / 180.0;

/**
 * @brief      check whether two values are almost same or not.
 * @tparam     T: value type.
 * @param[in]  lhs: left hand side.
 * @param[in]  rhs: right hand side.
 * @return     true: almost same, false: not same.
 */
template <typename T>
bool eq(T lhs, T rhs)
{
    static constexpr int scale = 1;
    return std::abs(lhs - rhs) < (std::numeric_limits<T>::epsilon() * std::abs(lhs + rhs) * scale);
}
/////////////////////////////////////////////////////////////////////////////

} // namespace {

const lest::test specification[] =
{

    CASE("basic functions")
    {
        using namespace ken3::metric;

        EXPECT(eq(1.0 / 1852.0, convert<Metre, NauticalMile>(1.0)));
    },

    CASE("length")
    {
        using namespace ken3::metric;

        // with Metre
        EXPECT(eq(1.0 / 1.0, convert<Metre, Si>(1.0)));
        EXPECT(eq(2.0 / 1.0, convert<Metre, Metre>(2.0)));
        EXPECT(eq(3.0 / 1852.0, convert<Metre, NauticalMile>(3.0)));
        EXPECT(eq(4.0 / 0.9144, convert<Metre, Yard>(4.0)));
        EXPECT(eq(5.0 / 1000.0, convert<Metre, Kilometre>(5.0)));
        EXPECT(eq(6.0 / 914.4, convert<Metre, Kiloyard>(6.0)));
        EXPECT(eq(6.0 * 1.0, convert<Si, Metre>(6.0)));
        EXPECT(eq(5.0 * 1.0, convert<Metre, Metre>(5.0)));
        EXPECT(eq(4.0 * 1852.0, convert<NauticalMile, Metre>(4.0)));
        EXPECT(eq(3.0 * 0.9144, convert<Yard, Metre>(3.0)));
        EXPECT(eq(2.0 * 1000.0, convert<Kilometre, Metre>(2.0)));
        EXPECT(eq(1.0 * 914.4, convert<Kiloyard, Metre>(1.0)));
        // without Metre
        EXPECT(eq(1.0 * 1852.0 / 0.9144, convert<NauticalMile, Yard>(1.0)));
        EXPECT(eq(2.0 * 1852.0 / 1000.0, convert<NauticalMile, Kilometre>(2.0)));
        EXPECT(eq(3.0 * 1852.0 / 914.4, convert<NauticalMile, Kiloyard>(3.0)));
        EXPECT(eq(3.0 * 0.9144 / 1852.0, convert<Yard, NauticalMile>(3.0)));
        EXPECT(eq(2.0 * 0.9144 / 1000.0, convert<Yard, Kilometre>(2.0)));
        EXPECT(eq(1.0 * 0.9144 / 914.4, convert<Yard, Kiloyard>(1.0)));
        EXPECT(eq(1.0 * 1000.0 / 1852.0, convert<Kilometre, NauticalMile>(1.0)));
        EXPECT(eq(2.0 * 1000.0 / 0.9144, convert<Kilometre, Yard>(2.0)));
        EXPECT(eq(3.0 * 1000.0 / 914.4, convert<Kilometre, Kiloyard>(3.0)));
        EXPECT(eq(3.0 * 914.4 / 1852.0, convert<Kiloyard, NauticalMile>(3.0)));
        EXPECT(eq(2.0 * 914.4 / 0.9144, convert<Kiloyard, Yard>(2.0)));
        EXPECT(eq(1.0 * 914.4 / 1000.0, convert<Kiloyard, Kilometre>(1.0)));
    },

    CASE("time")
    {
        using namespace ken3::metric;

        // with Second
        EXPECT(eq(1.0 / 1.0, convert<Second, Si>(1.0)));
        EXPECT(eq(2.0 / 1.0, convert<Second, Second>(2.0)));
        EXPECT(eq(3.0 / 60.0, convert<Second, Minute>(3.0)));
        EXPECT(eq(4.0 / 3600.0, convert<Second, Hour>(4.0)));
        EXPECT(eq(5.0 / 86400.0, convert<Second, Day>(5.0)));
        EXPECT(eq(6.0 / 604800.0, convert<Second, Week>(6.0)));
        EXPECT(eq(6.0 * 1.0, convert<Si, Second>(6.0)));
        EXPECT(eq(5.0 * 1.0, convert<Second, Second>(5.0)));
        EXPECT(eq(4.0 * 60.0, convert<Minute, Second>(4.0)));
        EXPECT(eq(3.0 * 3600.0, convert<Hour, Second>(3.0)));
        EXPECT(eq(2.0 * 86400.0, convert<Day, Second>(2.0)));
        EXPECT(eq(1.0 * 604800.0, convert<Week, Second>(1.0)));
        // without Second
        EXPECT(eq(1.0 * 60.0 / 3600.0, convert<Minute, Hour>(1.0)));
        EXPECT(eq(2.0 * 60.0 / 86400.0, convert<Minute, Day>(2.0)));
        EXPECT(eq(3.0 * 60.0 / 604800.0, convert<Minute, Week>(3.0)));
        EXPECT(eq(3.0 * 3600.0 / 60.0, convert<Hour, Minute>(3.0)));
        EXPECT(eq(2.0 * 3600.0 / 86400.0, convert<Hour, Day>(2.0)));
        EXPECT(eq(1.0 * 3600.0 / 604800.0, convert<Hour, Week>(1.0)));
        EXPECT(eq(1.0 * 86400.0 / 60.0, convert<Day, Minute>(1.0)));
        EXPECT(eq(2.0 * 86400.0 / 3600.0, convert<Day, Hour>(2.0)));
        EXPECT(eq(3.0 * 86400.0 / 604800.0, convert<Day, Week>(3.0)));
        EXPECT(eq(3.0 * 604800.0 / 60.0, convert<Week, Minute>(3.0)));
        EXPECT(eq(2.0 * 604800.0 / 3600.0, convert<Week, Hour>(2.0)));
        EXPECT(eq(1.0 * 604800.0 / 86400.0, convert<Week, Day>(1.0)));
    },

    CASE("speed")
    {
        using namespace ken3::metric;

        // with MetrePerSecond
        EXPECT(eq(1.0 / 1.0, convert<MetrePerSecond, Si>(1.0)));
        EXPECT(eq(2.0 / 1.0, convert<MetrePerSecond, MetrePerSecond>(2.0)));
        EXPECT(eq(3.0 / (1000.0 / 3600.0), convert<MetrePerSecond, KilometrePerHour>(3.0)));
        EXPECT(eq(4.0 / (1852.0 / 3600.0), convert<MetrePerSecond, Knot>(4.0)));
        EXPECT(eq(4.0 * 1.0, convert<Si, MetrePerSecond>(4.0)));
        EXPECT(eq(3.0 * 1.0, convert<MetrePerSecond, MetrePerSecond>(3.0)));
        EXPECT(eq(2.0 * (1000.0 / 3600.0), convert<KilometrePerHour, MetrePerSecond>(2.0)));
        EXPECT(eq(1.0 * (1852.0 / 3600.0), convert<Knot, MetrePerSecond>(1.0)));
        // without MetrePerSecond
        EXPECT(eq(1.0 * (1000.0 / 3600.0) / (1852.0 / 3600.0), convert<KilometrePerHour, Knot>(1.0)));
        EXPECT(eq(1.0 * (1852.0 / 3600.0) / (1000.0 / 3600.0), convert<Knot, KilometrePerHour>(1.0)));
    },

    CASE("angle")
    {
        using namespace ken3::metric;

        // with Radian
        EXPECT(eq(1.0 / 1.0, convert<Radian, Si>(1.0)));
        EXPECT(eq(2.0 / 1.0, convert<Radian, Radian>(2.0)));
        EXPECT(eq(3.0 / rad2deg, convert<Radian, Degree>(3.0)));
        EXPECT(eq(3.0 * 1.0, convert<Si, Radian>(3.0)));
        EXPECT(eq(2.0 * 1.0, convert<Radian, Radian>(2.0)));
        EXPECT(eq(1.0 * rad2deg, convert<Degree, Radian>(1.0)));
    },

    CASE("ROT")
    {
        using namespace ken3::metric;

        // with RadianPerSecond
        EXPECT(eq(1.0 / 1.0, convert<RadianPerSecond, Si>(1.0)));
        EXPECT(eq(2.0 / 1.0, convert<RadianPerSecond, RadianPerSecond>(2.0)));
        EXPECT(eq(3.0 / rad2deg, convert<RadianPerSecond, DegreePerSecond>(3.0)));
        EXPECT(eq(4.0 / (1.0 / 60.0), convert<RadianPerSecond, RadianPerMinute>(4.0)));
        EXPECT(eq(5.0 / (rad2deg / 60.0), convert<RadianPerSecond, DegreePerMinute>(5.0)));
        EXPECT(eq(5.0 * 1.0, convert<Si, RadianPerSecond>(5.0)));
        EXPECT(eq(4.0 * 1.0, convert<RadianPerSecond, RadianPerSecond>(4.0)));
        EXPECT(eq(3.0 * rad2deg, convert<DegreePerSecond, RadianPerSecond>(3.0)));
        EXPECT(eq(2.0 * (1.0 / 60.0), convert<RadianPerMinute, RadianPerSecond>(2.0)));
        EXPECT(eq(1.0 * (rad2deg / 60.0), convert<DegreePerMinute, RadianPerSecond>(1.0)));
        // without RadianPerSecond
        EXPECT(eq(1.0 * rad2deg / (1.0 / 60.0), convert<DegreePerSecond, RadianPerMinute>(1.0)));
        EXPECT(eq(2.0 * rad2deg / (rad2deg / 60.0), convert<DegreePerSecond, DegreePerMinute>(2.0)));
        EXPECT(eq(2.0 * (1.0 / 60.0) / rad2deg, convert<RadianPerMinute, DegreePerSecond>(2.0)));
        EXPECT(eq(1.0 * (1.0 / 60.0) / (rad2deg / 60.0), convert<RadianPerMinute, DegreePerMinute>(1.0)));
        EXPECT(eq(1.0 * (rad2deg / 60.0) / rad2deg, convert<DegreePerMinute, DegreePerSecond>(1.0)));
        EXPECT(eq(2.0 * (rad2deg / 60.0) / (1.0 / 60.0), convert<DegreePerMinute, RadianPerMinute>(2.0)));
    },

    CASE("add unit")
    {
        using namespace ken3::metric;

        // define [cm]
        using Centimetre = ken3::metric::Unit<ken3::metric::Length, std::ratio<1, 100>>;

        EXPECT(eq(10.0, convert<Centimetre, Metre>(1000)));
    },

    CASE("return value type")
    {
        using namespace ken3::metric;

        auto c = convert<Si, Si>(static_cast<char>(1));
        EXPECT((std::is_same<double, decltype(c)>::value));
        auto s = convert<Si, Si>(static_cast<short>(1));
        EXPECT((std::is_same<double, decltype(s)>::value));
        auto i = convert<Si, Si>(static_cast<int>(1));
        EXPECT((std::is_same<double, decltype(i)>::value));
        auto l = convert<Si, Si>(static_cast<long>(1));
        EXPECT((std::is_same<double, decltype(l)>::value));
        auto ll = convert<Si, Si>(static_cast<long long>(1));
        EXPECT((std::is_same<double, decltype(ll)>::value));
        auto f = convert<Si, Si>(static_cast<float>(1));
        EXPECT((std::is_same<double, decltype(f)>::value));
        auto d = convert<Si, Si>(static_cast<double>(1));
        EXPECT((std::is_same<double, decltype(d)>::value));
        auto ld = convert<Si, Si>(static_cast<long double>(1));
        EXPECT((std::is_same<long double, decltype(ld)>::value));
    },

};

int main(int argc, char* argv[])
{
    return lest::run(specification, argc, argv);
}
/////////////////////////////////////////////////////////////////////////////

