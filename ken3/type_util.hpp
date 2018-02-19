/**
 * @file    ken3/type_util.hpp
 * @brief   Define some util functions and types using <type_traits>.
 *
 *          ken3::array_size<> gives array size. it causes compile error
 *          if template parameter is not array.
 *          ken3::array_get() is similar function to std::get. its target
 *          is array.
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
 *     int* p = a;
 *     s = ken3::array_size<decltype(p)>::value); // compile error!
 *
 * usage of ken3::array_get() is,
 *     int a[3] = {1, 2, 3};
 *     int i = ken3::array_get<1>(a); // i is 2
 *     i = ken3::array_get<3>(a); // compile error!
 *     int* p = a;
 *     i = ken3::array_get<1>(p); // compile error!
 *
 * usage of ken3::e2i() is,
 *     enum class enum_i : int { zero = 0 };
 *     enum_i e = enumi::zero;
 *     auto i = ken3::e2i(e); // type of i is int
 */

#ifndef INCLUDE_GUARD_KEN3_TYPE_UTIL_HPP
#define INCLUDE_GUARD_KEN3_TYPE_UTIL_HPP

#include <cstddef>
#include <type_traits>

namespace ken3 {

namespace type_util_detail {

template <bool BOOL>
using bool_type = typename std::conditional<BOOL, std::true_type, std::false_type>::type;

template <typename ARRAY>
struct is_flat_array : public bool_type<std::is_array<ARRAY>::value && (std::rank<ARRAY>::value == 1UL)>
{
};

} // namespace type_util_detail {

/**
 * @struct     array_size
 * @brief      inheritance from std::extent<>.
 *             member constant "value" is set to the size of ARRAY
 * @tparam     ARRAY: shall be array type. if not, then compile error occurs
 */
template <typename ARRAY>
struct array_size : std::extent<ARRAY>
{
    static_assert(type_util_detail::is_flat_array<ARRAY>::value, "array_size::ARRAY is not flat array");
};
/////////////////////////////////////////////////////////////////////////////

/**
 * @function   array_get (non-const)
 * @brief      get array item in a similar way to std::get().
 * @tparam     I: appointed index. if I >= array_size, then compile error occurs
 * @tparam     ARRAY: shall be array type. if not, then compile error occurs
 * @param[in,out] a: appointed array instance.
 */
template <size_t I, typename ARRAY>
typename std::enable_if<type_util_detail::is_flat_array<ARRAY>::value, typename std::remove_extent<ARRAY>::type>::type& array_get(ARRAY& a)
{
    static_assert(I < array_size<ARRAY>::value, "index is out of bounds");
    return a[I];
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @function   array_get (const)
 * @brief      get array item in a similar way to std::get().
 * @tparam     I: appointed index. if I >= array_size, then compile error occurs
 * @tparam     ARRAY: shall be array type. if not, then compile error occurs
 * @param[in]  a: appointed array instance.
 */
template <size_t I, typename ARRAY>
const typename std::enable_if<type_util_detail::is_flat_array<ARRAY>::value, typename std::remove_extent<ARRAY>::type>::type& array_get(const ARRAY& a)
{
    static_assert(I < array_size<ARRAY>::value, "index is out of bounds");
    return a[I];
}
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
