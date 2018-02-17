/**
 * @file    pyloop/enumerate_errortest.cpp
 * @brief   Define some test function to check compile error occurs.
 * @author  toda
 * @date    2017-08-25
 * @version 0.1.0
 * @remark  the target is C++11 or more
 */

#include <array>
#include <string>
#include <vector>
#include "ken3/pyloop.hpp"

#if 0

#elif defined D0001_TEST_FUNC_ACTIVATED
/**
 * @brief      test that compile error occurs when template argument is
 *             int (not iterable).
 */
int test_func(void)
{
    int ten = 10;

    for (const auto& i: ken3::pyloop::enumerate(ten)) {
        ;
    }

    return 0;
}
/////////////////////////////////////////////////////////////////////////////

#elif defined D0002_TEST_FUNC_ACTIVATED
/**
 * @brief      test that compile error occurs when template argument is
 *             enum (not iterable).
 */
int test_func(void)
{
    enum class enum_class {
        e1 = 0,
        e2,
        e3,
    };
    enum_class e = enum_class::e1; 

    for (const auto& i: ken3::pyloop::enumerate(e)) {
        ;
    }

    return 0;
}
/////////////////////////////////////////////////////////////////////////////

#elif defined D0003_TEST_FUNC_ACTIVATED
/**
 * @brief      test that compile error occurs when template argument is
 *             pointer (not iterable).
 */
int test_func(void)
{
    int array[3] = {1, 22, 333};
    int* p = array;

    for (const auto& i: ken3::pyloop::enumerate(p)) {
        ;
    }

    return 0;
}
/////////////////////////////////////////////////////////////////////////////

#else
/**
 * @brief      nothing happens.
 */
int test_func(void)
{
    return 0;
}
/////////////////////////////////////////////////////////////////////////////

#endif

int main(void)
{
    test_func();

    return 0;
}
/////////////////////////////////////////////////////////////////////////////

