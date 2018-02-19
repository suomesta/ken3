/**
 * @file    ken3/cast.hpp
 * @brief   Define some util functions regarding cast.
 *          - int_cast() support strict cast between integer types.
 *          - string_to() support to convert from string to arithmetic types.
 * @author  toda
 * @date    2018-02-18
 * @version 0.1.0
 * @remark  the target is C++11 or more
 * @remark  type_util works only with header files
 *
 * @note
 * Typical usage of ken3::int_cast() is;
 *     // try to convert int into short.
 *     // conversion result is OK
 *     int i = 10;
 *     short s = ken3::int_cast<int, short>(i);
 *     std::cout << s; // => "10"
 *
 *     // try to convert long into char.
 *     // conversion result is NG, because 70000 is too large for char
 *     long l = 70000;
 *     try {
 *         char c = ken3::int_cast<long, char>(l);
 *     }
 *     catch (const std::out_of_range& e) {
 *         std::cout << "out_of_range"; // => "out_of_range"
 *     }
 *
 *     // bool is not supported
 *     std::cout << ken3::int_cast<bool, int>(true); // compile error!
 *     // parameters shall be integer
 *     std::cout << ken3::int_cast<double, int>(1.0); // compile error!
 */

#ifndef INCLUDE_GUARD_KEN3_CAST_HPP
#define INCLUDE_GUARD_KEN3_CAST_HPP

#include <string>
#include <type_traits>
#include "ken3/cast/int_cast.hpp"
#include "ken3/cast/string_to.hpp"

namespace ken3 {

/**
 * @function   int_cast
 * @brief      converter from integer into integer.
 * @tparam     FROM: input integer type. shall be integral.
 * @tparam     TO: output integer type. shall be integral.
 * @param[in]  i: appointed integer value.
 * @return     integer value converted from argument i. its type is TO
 * @throw      std::out_of_range: cannot keep original FROM value in TO
 */
template <typename FROM, typename TO>
TO int_cast(FROM i)
{
    static_assert(std::is_integral<FROM>::value, "Integer required");
    static_assert(std::is_integral<TO>::value, "Integer required");
    static_assert(!std::is_same<FROM, bool>::value, "int_cast() does not support bool");
    static_assert(!std::is_same<TO, bool>::value, "int_cast() does not support bool");

    using my_factory = int_cast_detail::factory<int_cast_detail::factory_index<FROM, TO>()>;
    return int_cast_detail::int_cast<FROM, TO>(i, my_factory{});
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @function   string_to
 * @brief      converter from string into arithmetic.
 * @tparam     T: output type. shall be arithmetic.
 * @param[in]  str: appointed string.
 * @param[in,out] pos: appointed position of string.
 * @param[in]  base: appointed base. it is applied only for integer.
 * @return     arithmetic value converted from string str. its type is T
 * @throw      std::invalid_argument: if no conversion could be performed.
 *             std::out_of_range: if the converted value is out of range.
 */
template <typename T>
T string_to(const std::string& str, std::size_t* pos=0, int base=10)
{
    static_assert(!std::is_same<T, bool>::value, "string_to() does not support bool");
    static_assert(std::is_arithmetic<T>::value, "string_to() supports only arithmetic");

    using my_factory = string_to_detail::factory<string_to_detail::factory_index<T>()>;
    return string_to_detail::string_to<T>(str, pos, base, my_factory{});
}
/////////////////////////////////////////////////////////////////////////////

} // namespace ken3 {

#endif // #ifndef INCLUDE_GUARD_KEN3_CAST_HPP

