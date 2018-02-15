/**
 * @file    type_util.hpp
 * @brief   Define some util functions and types using <type_traits>.
 *
 *          ken3::array_size<> gives array size. it causes compile error
 *          if template parameter is not array.
 *          ken3::e2i() converts enum into base integer type.
 * @author  toda
 * @date    2017-07-04
 * @version 0.1.0
 * @remark  the target is C++11 or more
 * @remark  type_util works only with this header file
 *
 * @note
 * usage of ken3::array_size<> is,
 *     int a[3] = {1, 2, 3};
 *     size_t s = ken3::array_size<decltype(a)>::value); // s is 3
 *     int* p = array;
 *     s = ken3::array_size<decltype(p)>::value); // compile error!
 *
 * usage of ken3::e2i() is,
 *     enum class enum_i : int { zero = 0 };
 *     enum_i e = enumi::zero;
 *     auto i = ken3::e2i(e); // type of i is int
 */

#ifndef INCLUDE_GUARD_KEN3_TYPE_UTIL_HPP
#define INCLUDE_GUARD_KEN3_TYPE_UTIL_HPP

#include <type_traits>

namespace ken3 {

/**
 * @struct     array_size
 * @brief      inheritance from std::extent<>.
 *             member constant "value" is set to the size of ARRAY
 * @tparam     ARRAY: shall be array type. if not, then compile error occurs
 */
template <typename ARRAY>
struct array_size : std::extent<ARRAY>
{
    static_assert(std::is_array<ARRAY>::value, "array_size::ARRAY is not array");
};
/////////////////////////////////////////////////////////////////////////////

/**
 * @function   e2i
 * @brief      converter from enum into integer.
 * @param[in]  e: appointed enum value.
 * @tparam     ENUM: appointed enum type. shall be enum.
 * @return     integer value converted from argument e. its type is base integer type of e
 * @note       if ENUM is non-scoped and non-type-specified enum (e.g. classic enum),
 *             the type of return value cannot be expected. just compiler decides.
 */
template <typename ENUM>
typename std::enable_if<std::is_enum<ENUM>::value, typename std::underlying_type<ENUM>::type>::type e2i(ENUM e)
{
    return static_cast<typename std::underlying_type<ENUM>::type>(e);
}
/////////////////////////////////////////////////////////////////////////////

} // namespace ken3 {

#endif // #ifndef INCLUDE_GUARD_KEN3_TYPE_UTIL_HPP

