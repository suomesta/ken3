/**
 * @file    ken3/metric.hpp
 * @brief   Define functions to calculate unit conversion.
 *          metric supports length, time, and speed. 
 *          It is easy to add new units if needed.
 * @author  toda
 * @date    2017-01-24
 * @version 0.1.0
 * @remark  the target is C++11 or more.
 * @remark  this module works only with this header file.
 *
 * @note
 * Typical usage is;
 *     using namespace ken3::metric;
 *     // convert 1000[m] into [NM]
 *     double d = convert<metre, nauticalmile>(1000);
 *     std::cout << d; // => "0.53995"
 *
 * Default supported units are;
 *     length {metre, nauticalmile, yard, kilometre, kiloyard}
 *     time {second, minute, hour, day, week}
 *     speed {metre_per_second, kilometre_per_hour, knot}
 *
 * si is a special unit to deal with SI units;
 *     // convert 1000[SI unit(m)] into [NM]
 *     double s1 = convert<si, nauticalmile>(1000);
 *     std::cout << s1; // => "0.53995"
 *     // convert 1[NM] into [SI unit(m)]
 *     double s2 = convert<nauticalmile, si>(1);
 *     std::cout << s2; // => "1852"
 *
 * The procedure to add unit is;
 *     // define [cm]
 *     using centimetre = ken3::metric::unit<ken3::metric::length, std::ratio<1, 100>>;
 *     // convert 1000[cm] into [m]
 *     double d = convert<centimetre, metre>(1000);
 *     std::cout << d; // => 10
 */

#ifndef INCLUDE_GUARD_KEN3_METRIC_HPP
#define INCLUDE_GUARD_KEN3_METRIC_HPP

#include <ratio>
#include <type_traits>

namespace ken3 {
namespace metric {

/**
 * @struct unit.
 * @brief  template struct to hold quantity type and ratio.
 * @tparam TYPE: quantity type.
 * @tparam RATIO: ratio comparing with SI unit. must be std::ratio.
 */
template <typename TYPE, typename RATIO>
struct unit {
    using type = TYPE;
    using ratio = RATIO;
};
/////////////////////////////////////////////////////////////////////////////

// any unit
struct arbitrary {};
using si = unit<arbitrary, std::ratio<1, 1>>; // any SI

// length unit definition
struct length {};
using metre        = unit<length, std::ratio<   1,     1>>; // SI
using nauticalmile = unit<length, std::ratio<1852,     1>>;
using yard         = unit<length, std::ratio<9144, 10000>>;
using kilometre    = unit<length, std::ratio_multiply<std::kilo, metre::ratio>>;
using kiloyard     = unit<length, std::ratio_multiply<std::kilo, yard::ratio>>;
/////////////////////////////////////////////////////////////////////////////

// time unit definition
struct time {};
using second = unit<time, std::ratio<               1, 1>>; // SI
using minute = unit<time, std::ratio<              60, 1>>;
using hour   = unit<time, std::ratio<         60 * 60, 1>>;
using day    = unit<time, std::ratio<    24 * 60 * 60, 1>>;
using week   = unit<time, std::ratio<7 * 24 * 60 * 60, 1>>;
/////////////////////////////////////////////////////////////////////////////

// speed unit definition
struct speed {};
using metre_per_second   = unit<speed, std::ratio_divide<typename metre::ratio,        typename second::ratio>>; // SI
using kilometre_per_hour = unit<speed, std::ratio_divide<typename kilometre::ratio,    typename hour::ratio>>;
using knot               = unit<speed, std::ratio_divide<typename nauticalmile::ratio, typename hour::ratio>>;
/////////////////////////////////////////////////////////////////////////////

namespace metirc_detail {

// types of unit checker
template<typename>
struct is_unit : std::false_type {};
template<typename TYPE, typename RATIO>
struct is_unit<unit<TYPE, RATIO>> : std::true_type {};

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
                  "FROM and TO must be metric::unit in metric::convert().");
    static_assert(std::is_same<arbitrary, typename FROM::type>::value ||
                  std::is_same<arbitrary, typename TO::type>::value ||
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

