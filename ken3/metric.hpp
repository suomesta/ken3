/**
 * @file    metric.hpp
 * @brief   Define functions to calculate unit conversion.
 *          metric supports length, time, speed, angle, and ROT. 
 *          It is easy to add new units if needed.
 * @author  toda
 * @date    2017-01-24
 * @version 0.1.0
 * @remark  the target is C++11 or more
 * @remark  metric works only with this header file
 *
 * @note
 * Typical usage is;
 *     using namespace ken3::metric;
 *     // convert 1000[m] into [NM]
 *     double d = convert<Metre, NauticalMile>(1000);
 *     std::cout << d; // => "0.53995"
 *
 * Default supported units are;
 *     Length {Metre, NauticalMile, Yard, Kilometre, Kiloyard}
 *     Time {Second, Minute, Hour, Day, Week}
 *     Speed {MetrePerSecond, KilometrePerHour, Knot}
 *     Angle {Radian, Degree}
 *     ROT {RadianPerSecond, DegreePerSecond, RadianPerMinute, DegreePerMinute}
 *
 * Si is a special unit to deal with SI units;
 *     // convert 1000[SI unit(m)] into [NM]
 *     double s1 = convert<Si, NauticalMile>(1000);
 *     std::cout << s1; // => "0.53995"
 *     // convert 1[NM] into [SI unit(m)]
 *     double s2 = convert<NauticalMile, Si>(1);
 *     std::cout << s2; // => "1852"
 *
 * The procedure to add unit is;
 *     // define [cm]
 *     using Centimetre = ken3::metric::Unit<ken3::metric::Length, std::ratio<1, 100>>;
 *     // convert 1000[cm] into [m]
 *     double d = convert<Centimetre, Metre>(1000);
 *     std::cout << d; // => 10
 */

#ifndef INCLUDE_GUARD_KEN3_METRIC_HPP
#define INCLUDE_GUARD_KEN3_METRIC_HPP

#include <ratio>
#include <type_traits>

namespace ken3 {
namespace metric {

/**
 * @struct Unit.
 * @brief  template struct to hold quantity type and ratio.
 * @tparam TYPE: quantity type.
 * @tparam RATIO: ratio comparing with SI unit. must be std::ratio.
 */
template <typename TYPE, typename RATIO>
struct Unit {
    using type = TYPE;
    using ratio = RATIO;
};
/////////////////////////////////////////////////////////////////////////////

// any unit
struct Arbitrary {};
using Si = Unit<Arbitrary, std::ratio<1, 1>>; // any SI

// length unit definition
struct Length {};
using Metre        = Unit<Length, std::ratio<   1,     1>>; // SI
using NauticalMile = Unit<Length, std::ratio<1852,     1>>;
using Yard         = Unit<Length, std::ratio<9144, 10000>>;
using Kilometre    = Unit<Length, std::ratio_multiply<std::kilo, Metre::ratio>>;
using Kiloyard     = Unit<Length, std::ratio_multiply<std::kilo, Yard::ratio>>;
/////////////////////////////////////////////////////////////////////////////

// time unit definition
struct Time {};
using Second = Unit<Time, std::ratio<               1, 1>>; // SI
using Minute = Unit<Time, std::ratio<              60, 1>>;
using Hour   = Unit<Time, std::ratio<         60 * 60, 1>>;
using Day    = Unit<Time, std::ratio<    24 * 60 * 60, 1>>;
using Week   = Unit<Time, std::ratio<7 * 24 * 60 * 60, 1>>;
/////////////////////////////////////////////////////////////////////////////

// speed unit definition
struct Speed {};
using MetrePerSecond   = Unit<Speed, std::ratio_divide<typename Metre::ratio,        typename Second::ratio>>; // SI
using KilometrePerHour = Unit<Speed, std::ratio_divide<typename Kilometre::ratio,    typename Hour::ratio>>;
using Knot             = Unit<Speed, std::ratio_divide<typename NauticalMile::ratio, typename Hour::ratio>>;
/////////////////////////////////////////////////////////////////////////////

// angle unit definition
struct Angle {};
using Radian = Unit<Angle, std::ratio<1, 1>>; // SI
using Degree = Unit<Angle, std::ratio<static_cast<std::intmax_t>(INTMAX_MAX / 180 * 3.14159265358979323846), INTMAX_MAX / 180 * 180>>;
/////////////////////////////////////////////////////////////////////////////

// ROT unit definition
struct Rot {};
using RadianPerSecond = Unit<Rot, std::ratio_divide<typename Radian::ratio, typename Second::ratio>>; // SI
using DegreePerSecond = Unit<Rot, std::ratio_divide<typename Degree::ratio, typename Second::ratio>>;
using RadianPerMinute = Unit<Rot, std::ratio_divide<typename Radian::ratio, typename Minute::ratio>>;
using DegreePerMinute = Unit<Rot, std::ratio_divide<typename Degree::ratio, typename Minute::ratio>>;
/////////////////////////////////////////////////////////////////////////////

namespace metirc_detail {

// types of unit checker
template<typename>
struct is_unit : std::false_type {};
template<typename TYPE, typename RATIO>
struct is_unit<Unit<TYPE, RATIO>> : std::true_type {};

// types of ratio checker
template<typename>
struct is_ratio : std::false_type {};
template<std::intmax_t NUM, std::intmax_t DEN>
struct is_ratio<std::ratio<NUM, DEN>> : std::true_type {};
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief      convert std::ratio into scaling factor (std::ratio::num / std::ratio::den)
 *             in appointed type (normally double).
 * @tparam     RATIO: std::ratio
 * @tparam     VALUE: return value type
 * @return     scaling factor by std::ratio
 */
template <typename RATIO, typename VALUE>
constexpr VALUE scaling_factor(void)
{
    return static_cast<VALUE>(RATIO::num) / static_cast<VALUE>(RATIO::den);
}
/////////////////////////////////////////////////////////////////////////////

} // namespace metirc_detail {

/**
 * @brief      convert value in a unit into another unit value.
 * @tparam     FROM: unit of argument
 * @tparam     TO: unit of return value
 * @tparam     VALUE: input value type
 * @param[in]  value: a value in FROM-unit. its type is double or more.
 * @return     converted value from FROM-unit to TO-unit
 */
template <typename FROM, typename TO, typename VALUE>
typename std::common_type<VALUE, double>::type convert(VALUE value)
{
    // check template types
    static_assert(metirc_detail::is_unit<FROM>::value && metirc_detail::is_unit<TO>::value,
                  "FROM and TO must be metric::Unit in metric::convert().");
    static_assert(std::is_same<Arbitrary, typename FROM::type>::value ||
                  std::is_same<Arbitrary, typename TO::type>::value ||
                  std::is_same<typename FROM::type, typename TO::type>::value,
                  "Type mismatch in metric::convert().");
    static_assert(metirc_detail::is_ratio<typename FROM::ratio>::value && metirc_detail::is_ratio<typename TO::ratio>::value,
                  "FROM and TO must include std::ratio in metric::convert().");

    // create types
    using ratio = std::ratio_divide<typename FROM::ratio, typename TO::ratio>;
    using return_type = typename std::common_type<VALUE, double>::type;

    // do conversion
    return value * metirc_detail::scaling_factor<ratio, return_type>();
}
/////////////////////////////////////////////////////////////////////////////

} // namespace metric {
} // namespace ken3 {

#endif // #ifndef INCLUDE_GUARD_KEN3_METRIC_HPP

