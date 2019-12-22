/**
 * @file    ken3/pyloop.hpp
 * @brief   Define some util functions, those work as like Python's
 *          enumerate, range, and zip.
 * @author  toda
 * @date    2017-08-25
 * @version 0.1.0
 * @remark  the target is C++11 or more.
 * @remark  this module works only with this header file.
 *
 * @note
 * Typical usage of ken3::py::enumerate is;
 *     std::vector<int> v{1, 22, 333};
 *     for (auto i: ken3::py::enumerate(v)) {
 *         std::cout << i.first << " " << i.second << std::endl;
 *         // => "0 1"
 *         // => "1 22"
 *         // => "2 333"
 *     }
 *
 * Typical usage of ken3::py::range is;
 *     for (auto i: ken3::py::range(3)) {
 *         std::cout << i << " ";
 *         // => "0 1 2 "
 *     }
 *
 *     for (auto i: ken3::py::range(1, 4)) {
 *         std::cout << i << " ";
 *         // => "1 2 3 "
 *     }
 *
 *     for (auto i: ken3::py::range(1, 4, 2)) {
 *         std::cout << i << " ";
 *         // => "1 3 "
 *     }
 *
 * Typical usage of ken3::py::zip is;
 *     std::vector<int> v1{1, 2, 3};
 *     std::vector<int> v2{4, 5, 6};
 *     for (auto i: ken3::py::zip(v1, v2)) {
 *         std::cout << i.first << " " << i.second << std::endl;
 *         // => "1 4"
 *         // => "2 5"
 *         // => "3 6"
 *     }
 *
 *     int a1[3] = {7, 8, 9};
 *     int a2[4] = {10, 11, 12, 13};
 *     for (auto i: ken3::py::zip(a1, a2)) {
 *         std::cout << i.first << " " << i.second << std::endl;
 *         // => "7 10"
 *         // => "8 11"
 *         // => "9 12"
 *         // truncated in shorter size of a1 or a2
 *     }
 */

#ifndef INCLUDE_GUARD_KEN3_PYLOOP_HPP
#define INCLUDE_GUARD_KEN3_PYLOOP_HPP

#include <string>
#include "ken3/pycommon.hpp"
#include "ken3/pyloop/enumerate.hpp"
#include "ken3/pyloop/range.hpp"
#include "ken3/pyloop/zip.hpp"

namespace ken3 {
namespace py {

/**
 * @function   enumerate
 * @brief      create and return enumerate object.
 * @tparam     ITERABLE: type of argument. should accept std::begin() and std::end().
 * @param[in]  iterable: appointed iterable object. shall be left const reference.
 * @param[in]  start: start value of count. default is 0.
 * @return     created enumerate object. this works in range-for statement.
 */
template <typename ITERABLE>
enumerate_detail::enumerate_object<ITERABLE> enumerate(ITERABLE& iterable, enumerate_detail::count_type<ITERABLE> start=0)
{
    return enumerate_detail::enumerate_object<ITERABLE>(iterable, start);
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @function   enumerate with (start, stop, step)
 * @brief      create and return range object.
 * @tparam     T: type of element. shall be integral type (exclude bool).
 * @param[in]  start: start value of range.
 * @param[in]  stop: stop value of range.
 * @param[in]  step: step value of range.
 * @return     created range object. this works in range-for statement.
 * @throw      ken3::py::ValueError: if step is 0.
 */
template <typename T=int>
range_detail::range_object<T> range(T start, T stop, T step)
{
    return range_detail::range_object<T>(start, stop, step, static_cast<ken3::py::ValueError*>(nullptr));
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @function   enumerate with (start, stop)
 * @brief      create and return range object.
 * @tparam     T: type of element. shall be integral type (exclude bool).
 * @param[in]  start: start value of range.
 * @param[in]  stop: stop value of range.
 * @return     created range object. this works in range-for statement.
 * @note       step is set to 1 automatically.
 */
template <typename T=int>
range_detail::range_object<T> range(T start, T stop)
{
    return range_detail::range_object<T>(start, stop, 1, static_cast<ValueError*>(nullptr));
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @function   enumerate with (stop)
 * @brief      create and return range object.
 * @tparam     T: type of element. shall be integral type (exclude bool).
 * @param[in]  stop: stop value of range.
 * @return     created range object. this works in range-for statement.
 * @note       start is set to 0, step is set to 1 automatically.
 */
template <typename T=int>
range_detail::range_object<T> range(T stop)
{
    return range_detail::range_object<T>(0, stop, 1, static_cast<ValueError*>(nullptr));
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @function   zip
 * @brief      create and return zip object.
 * @tparam     ITERABLE1: type of iterable1. should accept std::begin() and std::end().
 * @tparam     ITERABLE2: type of iterable2. should accept std::begin() and std::end().
 * @param[in]  iterable1: appointed iterable object 1 of 2. shall be left const reference.
 * @param[in]  iterable2: appointed iterable object 2 of 2. shall be left const reference.
 * @return     created zip object. this works in range-for statement.
 */
template <typename ITERABLE1, typename ITERABLE2>
zip_detail::zip_object<ITERABLE1, ITERABLE2> zip(ITERABLE1& iterable1, ITERABLE2& iterable2)
{
    return zip_detail::zip_object<ITERABLE1, ITERABLE2>(iterable1, iterable2);
}
/////////////////////////////////////////////////////////////////////////////

} // namespace py {
} // namespace ken3 {

#endif // #ifndef INCLUDE_GUARD_KEN3_PYLOOP_HPP
