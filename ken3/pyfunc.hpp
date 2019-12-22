/**
 * @file    ken3/pyfunc.hpp
 * @brief   Define functions which imitate Python's built-in functions. 
 *          py::bool_cast(), py::min(), py::max(), py::all(), py::any(), py::sum(), 
 *          py::reduce(), py::map(), and py::filter() behave almost
 *          same as Python's same named function.
 * @author  toda
 * @date    2018-03-13
 * @version 0.1.0
 * @remark  the target is C++11 or more.
 * @remark  this module works only with this header file.
 *
 * @note
 * Typical usage is;
 *     using namespace ken3::py;
 *
 *     // Python like bool()
 *     std::cout << bool_cast(std::vector<int>{}); // => 0
 *     std::cout << bool_cast(std::vector<int>{1}); // => 1
 *
 *     // Python like min()
 *     std::cout << min(std::vector<int>{1, 2, 3}); // => 1
 *
 *     // Python like max()
 *     std::cout << max(std::vector<int>{1, 2, 3}); // => 3
 *
 *     // Python like all()
 *     std::cout << all(std::vector<int>{}); // => 1
 *     std::cout << all(std::vector<int>{0, 0}); // => 0
 *     std::cout << all(std::vector<int>{0, 1}); // => 1
 *     std::cout << all(std::vector<int>{1, 1}); // => 1
 *
 *     // Python like any()
 *     std::cout << any(std::vector<int>{}); // => 0
 *     std::cout << any(std::vector<int>{0, 0}); // => 0
 *     std::cout << any(std::vector<int>{0, 1}); // => 1
 *     std::cout << any(std::vector<int>{1, 1}); // => 1
 *
 *     // Python like sum()
 *     std::cout << sum(std::vector<int>{}); // => 0
 *     std::cout << sum(std::vector<int>{1, 2, 3}); // => 6
 *     std::cout << sum(std::vector<std::string>{"A", "B"}); // => AB
 *
 *     // Python like reduce()
 *     std::cout << reduce(std::plus<int>(), std::vector<int>{1, 2, 3}); // => 6
 *     std::cout << reduce(std::plus<int>(), std::vector<int>{1, 2, 3}, 10); // => 16
 *     std::cout << reduce(std::plus<int>(), std::vector<int>{}); // => TypeError
 *
 *     // Python like map()
 *     std::cout << map(::toupper, std::string("aABbCcdD")); // => AABBCCDD
 *
 *     // Python like filter()
 *     auto f = [](char c) -> bool {
 *         return static_cast<bool>(c);
 *     };
 *     std::string s = "ABC";
 *     s[1] = '\0';
 *     std::cout << filter(f, s); // => AC
 */

#ifndef INCLUDE_GUARD_KEN3_PYFUNC_HPP
#define INCLUDE_GUARD_KEN3_PYFUNC_HPP

#include <algorithm>
#include <iterator>
#include <numeric>
#include <stdexcept>
#include <string>
#include <type_traits>
#include "pycommon.hpp"

namespace ken3 {
namespace py {

namespace pyfunc_detail {

template <typename T>
struct remove_cvr
{
    using type = typename std::remove_cv<typename std::remove_reference<T>::type>::type;
};
/////////////////////////////////////////////////////////////////////////////

template <typename T>
bool bool_cast(const T& t, std::true_type dummy)
{
    return bool(t);
}
/////////////////////////////////////////////////////////////////////////////

template <typename T>
bool bool_cast(const T& t, std::false_type dummy)
{
    return std::begin(t) != std::end(t);
}
/////////////////////////////////////////////////////////////////////////////

} // namespace pyfunc_detail {

/**
 * @brief      Python like bool().
 * @tparam     T: appointed type.
 * @param[in]  t: appointed value.
 * @return     result of bool().
 *             nullptr, NULL, 0 in arithmetic, and empty iterable object return false.
 *             otherwise true.
 */
template <typename T>
bool bool_cast(const T& t)
{
    constexpr bool bool_convertible = std::is_convertible<T, bool>::value;
    using true_false_type = typename std::integral_constant<bool, bool_convertible>::type;

    return pyfunc_detail::bool_cast(t, true_false_type{});
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief      Python like bool() with nullptr.
 * @param[in]  t: nullptr.
 * @return     false.
 */
template <>
bool bool_cast(const std::nullptr_t& t)
{
    return false;
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief      Python like min().
 * @tparam     ITERABLE: iterable object. ex.) STL container and array
 * @tparam     COMPARE: compare function
 * @param[in]  iterable: target container of min().
 * @param[in]  compare: comparison funstion.
 * @return     result of min()
 * @throw      ken3::py::ValueError: in case iterable is empty
 * @note       unfortunately argument default in Python's min() is not supported.
 */
template <typename ITERABLE,
          typename COMPARE=std::less<const decltype(*std::begin(std::declval<const ITERABLE&>()))&>>
const decltype(*std::begin(std::declval<const ITERABLE&>()))& min(const ITERABLE& iterable, COMPARE compare=COMPARE())
{
    auto last = std::end(iterable);
    auto ret = std::min_element(std::begin(iterable), last, compare);
    if (ret == last) {
        throw ValueError("min() arg is an empty sequence");
    }
    return *ret;
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief      Python like max().
 * @tparam     ITERABLE: iterable object. ex.) STL container and array
 * @tparam     COMPARE: compare function
 * @param[in]  iterable: target container of max().
 * @param[in]  compare: comparison funstion.
 * @return     result of max()
 * @throw      ken3::py::ValueError: in case iterable is empty
 * @note       unfortunately argument default in Python's max() is not supported.
 */
template <typename ITERABLE,
          typename COMPARE=std::less<const decltype(*std::begin(std::declval<const ITERABLE&>()))&>>
const decltype(*std::begin(std::declval<const ITERABLE&>()))& max(const ITERABLE& iterable, COMPARE compare=COMPARE())
{
    auto last = std::end(iterable);
    auto ret = std::max_element(std::begin(iterable), last, compare);
    if (ret == last) {
        throw ValueError("max() arg is an empty sequence");
    }
    return *ret;
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief      Python like all().
 * @tparam     ITERABLE: iterable object. ex.) STL container and array
 * @param[in]  iterable: target container of all().
 * @return     result of all().
 *             if iterable is empty, then return true
 */
template <typename ITERABLE>
bool all(const ITERABLE& iterable)
{
    using item_type = const decltype(*std::begin(iterable))&;
    return std::all_of(std::begin(iterable), std::end(iterable), [](item_type x) { return bool_cast(x); });
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief      Python like any().
 * @tparam     ITERABLE: iterable object. ex.) STL container and array
 * @param[in]  iterable: target container of any().
 * @return     result of any().
 *             if iterable is empty, then return false
 */
template <typename ITERABLE>
bool any(const ITERABLE& iterable)
{
    using item_type = const decltype(*std::begin(iterable))&;
    return std::any_of(std::begin(iterable), std::end(iterable), [](item_type x) { return bool_cast(x); });
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief      Python like sum().
 * @tparam     ITERABLE: iterable object. ex.) STL container and array
 * @tparam     T: initial value type. normally same as return value type
 * @param[in]  iterable: target container of sum().
 * @param[in]  start: initial value.
 * @return     result of sum()
 */
template <typename ITERABLE, typename T=int>
typename pyfunc_detail::remove_cvr<decltype(*std::begin(std::declval<const ITERABLE&>()))>::type sum(const ITERABLE& iterable, T start=T())
{
    typename pyfunc_detail::remove_cvr<decltype(*std::begin(iterable))>::type s = start;
    return std::accumulate(std::begin(iterable), std::end(iterable), s);
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief      Python like reduce().
 * @tparam     FUNC: function
 * @tparam     ITERABLE: iterable object. ex.) STL container and array
 * @param[in]  func: function to be target container of reduce().
 * @param[in]  iterable: target container of reduce().
 * @return     result of reduce()
 * @throw      ken3::py::TypeError: in case iterable is empyt
 */
template <typename FUNC, typename ITERABLE>
typename pyfunc_detail::remove_cvr<decltype(*std::begin(std::declval<const ITERABLE&>()))>::type reduce(FUNC func, const ITERABLE& iterable)
{
    auto start = std::begin(iterable);
    auto last = std::end(iterable);

    if (start != last) {
        return std::accumulate(std::next(start, 1), last, *start, func);
    }
    else {
        throw TypeError("reduce() of empty sequence with no initial value");
    }
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief      Python like reduce().
 * @tparam     FUNC: function
 * @tparam     ITERABLE: iterable object. ex.) STL container and array
 * @tparam     T: initial value type. normally same as return value type
 * @param[in]  func: function to be target container of reduce().
 * @param[in]  iterable: target container of reduce().
 * @param[in]  initial: initial value.
 * @return     result of reduce()
 */
template <typename FUNC, typename ITERABLE, typename T>
typename pyfunc_detail::remove_cvr<decltype(*std::begin(std::declval<const ITERABLE&>()))>::type reduce(FUNC func, const ITERABLE& iterable, T initial)
{
    return std::accumulate(std::begin(iterable), std::end(iterable), initial, func);
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief      Python like map().
 * @tparam     FUNC: function
 * @tparam     ITERABLE: iterable object which accepcts back_inserter. ex.) std::vector
 * @param[in]  func: function to be target container of map().
 * @param[in]  iterable: target container of map().
 * @return     result of map()
 */
template <typename FUNC, typename ITERABLE>
ITERABLE map(FUNC func, const ITERABLE& iterable)
{
    ITERABLE ret;
    std::transform(std::begin(iterable), std::end(iterable), std::back_inserter(ret), func);
    return ret;
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief      Python like filter().
 * @tparam     FUNC: function
 * @tparam     ITERABLE: iterable object which accepcts back_inserter. ex.) std::vector
 * @param[in]  func: function to be target container of filter().
 * @param[in]  iterable: target container of filter().
 * @return     result of filter()
 */
template <typename FUNC, typename ITERABLE>
ITERABLE filter(FUNC func, const ITERABLE& iterable)
{
    ITERABLE ret;
    std::copy_if(std::begin(iterable), std::end(iterable), std::back_inserter(ret), func);
    return ret;
}
/////////////////////////////////////////////////////////////////////////////

} // namespace py {
} // namespace ken3 {

#endif // #ifndef INCLUDE_GUARD_KEN3_PYFUNC_HPP
