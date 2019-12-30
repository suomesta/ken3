/**
 * @file    ken3/overflow.hpp
 * @brief   Define functions to check overflow conditions.
 *          Five functions (occur_add(), occur_sub(), occur_mul(), occur_div(),
 *          occur_abs()) are defined. All those informs overflow condition by
 *          return value, true means overflow occurs.
 *          Dividing by zero is out of scope of occur_div().
 * @author  toda
 * @date    2019-12-17
 * @version 0.1.0
 * @remark  the target is C++11 or more.
 * @remark  this module works only with this header file.
 *
 * @note
 * Typical usage is;
 *     signed char x = -128, y = -1;
 *     std::cout << ken3::overflow::occur_add(x, y); // => true
 *     std::cout << ken3::overflow::occur_sub(x, y); // => false
 *     std::cout << ken3::overflow::occur_mul(x, y); // => true
 *     std::cout << ken3::overflow::occur_div(x, y); // => true
 *     std::cout << ken3::overflow::occur_abs(x); // => true
 *     std::cout << ken3::overflow::occur_abs(y); // => false
 *
 *     unsigned char x = 3, y = 240;
 *     std::cout << ken3::overflow::occur_add(x, y); // => false
 *     std::cout << ken3::overflow::occur_sub(x, y); // => true
 *     std::cout << ken3::overflow::occur_mul(x, y); // => true
 *     std::cout << ken3::overflow::occur_div(x, y); // => false
 *     std::cout << ken3::overflow::occur_abs(x); // => false
 *     std::cout << ken3::overflow::occur_abs(y); // => false
 *
 *     unsigned char x = 1, y = 0;
 *     // not take care of dividing by zero 
 *     std::cout << ken3::overflow::occur_div(x, y); // => false
 */

#ifndef INCLUDE_GUARD_KEN3_OVERFLOW_HPP
#define INCLUDE_GUARD_KEN3_OVERFLOW_HPP

#include <limits>
#include <type_traits>

namespace ken3 {
namespace overflow {

namespace overflow_detail {

/**
 * @brief      check overflow condition of (x + y) with signed integer.
 * @param[in]  x: lhs of (x + y)
 * @param[in]  y: rhs of (x + y)
 * @tparam     T: signed integer type
 * @return     true: overflow occurs by (x + y). false: no overflow
 */
template <typename T>
bool occur_add(T x, T y, typename std::enable_if<std::is_signed<T>::value>::type * =nullptr) noexcept
{
    using limit = std::numeric_limits<T>;

    return (
        ((y > 0) && (x > (limit::max() - y))) ||
        ((y < 0) && (x < (limit::min() - y)))
    );
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief      check overflow condition of (x + y) with unsigned integer.
 * @param[in]  x: lhs of (x + y)
 * @param[in]  y: rhs of (x + y)
 * @tparam     T: unsigned integer type
 * @return     true: overflow occurs by (x + y). false: no overflow
 */
template <typename T>
bool occur_add(T x, T y, typename std::enable_if<std::is_unsigned<T>::value>::type * =nullptr) noexcept
{
    using limit = std::numeric_limits<T>;

    return (x > (limit::max() - y));
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief      check overflow condition of (x - y) with signed integer.
 * @param[in]  x: lhs of (x - y)
 * @param[in]  y: rhs of (x - y)
 * @tparam     T: signed integer type
 * @return     true: overflow occurs by (x - y). false: no overflow
 */
template <typename T>
bool occur_sub(T x, T y, typename std::enable_if<std::is_signed<T>::value>::type * =nullptr) noexcept
{
    using limit = std::numeric_limits<T>;

    return (
        ((y > 0) && (x < (limit::min() + y))) ||
        ((y < 0) && (x > (limit::max() + y)))
    );
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief      check overflow condition of (x - y) with unsigned integer.
 * @param[in]  x: lhs of (x - y)
 * @param[in]  y: rhs of (x - y)
 * @tparam     T: unsigned integer type
 * @return     true: overflow occurs by (x - y). false: no overflow
 */
template <typename T>
bool occur_sub(T x, T y, typename std::enable_if<std::is_unsigned<T>::value>::type * =nullptr) noexcept
{
    using limit = std::numeric_limits<T>;

    return (x < (limit::min() + y));
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief      check overflow condition of (x * y) with signed integer.
 * @param[in]  x: lhs of (x * y)
 * @param[in]  y: rhs of (x * y)
 * @tparam     T: signed integer type
 * @return     true: overflow occurs by (x * y). false: no overflow
 */
template <typename T>
bool occur_mul(T x, T y, typename std::enable_if<std::is_signed<T>::value>::type * =nullptr) noexcept
{
    using limit = std::numeric_limits<T>;

    return (
        ((y >   0) && ((x > (limit::max() / y)) || (x < (limit::min() / y)))) ||
        ((y == -1) && (x == limit::min())) ||
        ((y <  -1) && ((x > (limit::min() / y)) || (x < (limit::max() / y))))
    );
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief      check overflow condition of (x * y) with unsigned integer.
 * @param[in]  x: lhs of (x * y)
 * @param[in]  y: rhs of (x * y)
 * @tparam     T: unsigned integer type
 * @return     true: overflow occurs by (x * y). false: no overflow
 */
template <typename T>
bool occur_mul(T x, T y, typename std::enable_if<std::is_unsigned<T>::value>::type * =nullptr) noexcept
{
    using limit = std::numeric_limits<T>;

    return ((y > 0) && (x > (limit::max() / y)));
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief      check overflow condition of (x / y) with signed integer.
 * @param[in]  x: lhs of (x / y)
 * @param[in]  y: rhs of (x / y)
 * @tparam     T: signed integer type
 * @return     true: overflow occurs by (x / y). false: no overflow
 * @note       dividing by zero is out of scope of this function (retuen false).
 */
template <typename T>
bool occur_div(T x, T y, typename std::enable_if<std::is_signed<T>::value>::type * =nullptr) noexcept
{
    using limit = std::numeric_limits<T>;

    return ((x == limit::min()) && (y == -1));
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief      check overflow condition of (x / y) with unsigned integer.
 * @param[in]  x: lhs of (x / y)
 * @param[in]  y: rhs of (x / y)
 * @tparam     T: unsigned integer type
 * @return     true: overflow occurs by (x / y). false: no overflow
 * @note       dividing by zero is out of scope of this function (retuen false).
 */
template <typename T>
bool occur_div(T x, T y, typename std::enable_if<std::is_unsigned<T>::value>::type * =nullptr) noexcept
{
    return false;
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief      check overflow condition of abs(x) with signed integer.
 * @param[in]  x: argument of abs(x)
 * @tparam     T: signed integer type
 * @return     true: overflow occurs by abs(x). false: no overflow
 */
template <typename T>
bool occur_abs(T x, typename std::enable_if<std::is_signed<T>::value>::type * =nullptr) noexcept
{
    using limit = std::numeric_limits<T>;

    return (x == limit::min());
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief      check overflow condition of abs(x) with unsigned integer.
 * @param[in]  x: argument of abs(x)
 * @tparam     T: unsigned integer type
 * @return     true: overflow occurs by abs(x). false: no overflow
 */
template <typename T>
bool occur_abs(T x, typename std::enable_if<std::is_unsigned<T>::value>::type * =nullptr) noexcept
{
    return false;
}
/////////////////////////////////////////////////////////////////////////////

} // namespace overflow_detail {

/**
 * @brief      check overflow condition of (x + y).
 * @param[in]  x: lhs of (x + y)
 * @param[in]  y: rhs of (x + y)
 * @tparam     T: integer type
 * @return     true: overflow occurs by (x + y). false: no overflow
 */
template <typename T>
bool occur_add(T x, T y) noexcept
{
    static_assert(std::is_integral<T>::value, "Allow only integer");
    static_assert(not std::is_same<T, bool>::value, "bool is not allowed");

    return overflow_detail::occur_add(x, y);
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief      check overflow condition of (x - y).
 * @param[in]  x: lhs of (x - y)
 * @param[in]  y: rhs of (x - y)
 * @tparam     T: integer type
 * @return     true: overflow occurs by (x - y). false: no overflow
 */
template <typename T>
bool occur_sub(T x, T y) noexcept
{
    static_assert(std::is_integral<T>::value, "Allow only integer");
    static_assert(not std::is_same<T, bool>::value, "bool is not allowed");

    return overflow_detail::occur_sub(x, y);
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief      check overflow condition of (x * y).
 * @param[in]  x: lhs of (x * y)
 * @param[in]  y: rhs of (x * y)
 * @tparam     T: integer type
 * @return     true: overflow occurs by (x * y). false: no overflow
 */
template <typename T>
bool occur_mul(T x, T y) noexcept
{
    static_assert(std::is_integral<T>::value, "Allow only integer");
    static_assert(not std::is_same<T, bool>::value, "bool is not allowed");

    return overflow_detail::occur_mul(x, y);
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief      check overflow condition of (x / y).
 * @param[in]  x: lhs of (x / y)
 * @param[in]  y: rhs of (x / y)
 * @tparam     T: integer type
 * @return     true: overflow occurs by (x / y). false: no overflow
 * @note       dividing by zero is out of scope of this function (retuen false).
 */
template <typename T>
bool occur_div(T x, T y) noexcept
{
    static_assert(std::is_integral<T>::value, "Allow only integer");
    static_assert(not std::is_same<T, bool>::value, "bool is not allowed");

    return overflow_detail::occur_div(x, y);
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief      check overflow condition of abs(x).
 * @param[in]  x: argument of abs(x)
 * @tparam     T: integer type
 * @return     true: overflow occurs by abs(x). false: no overflow
 */
template <typename T>
bool occur_abs(T x) noexcept
{
    static_assert(std::is_integral<T>::value, "Allow only integer");
    static_assert(not std::is_same<T, bool>::value, "bool is not allowed");

    return overflow_detail::occur_abs(x);
}
/////////////////////////////////////////////////////////////////////////////

} // namespace overflow {
} // namespace ken3 {

#endif // #ifndef INCLUDE_GUARD_KEN3_OVERFLOW_HPP
