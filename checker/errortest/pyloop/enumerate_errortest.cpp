/**
 * @file    pyloop/enumerate_errortest.cpp
 * @brief   Define some test function to check compile error occurs.
 * @author  toda
 * @date    2017-08-25
 * @version 0.1.0
 * @remark  the target is C++11 or more
 */

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

    for (auto i: ken3::pyloop::enumerate(ten)) {
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

    for (auto i: ken3::pyloop::enumerate(e)) {
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

    for (auto i: ken3::pyloop::enumerate(p)) {
        ;
    }

    return 0;
}
/////////////////////////////////////////////////////////////////////////////

#elif defined D0004_TEST_FUNC_ACTIVATED
/**
 * @brief      test that compile error occurs when try to modify const array
 *             through enumerate.
 */
int test_func(void)
{
    const int array[3] = {1, 22, 333};

    for (auto i: ken3::pyloop::enumerate(array)) {
        i.second += 1;
    }

    return 0;
}
/////////////////////////////////////////////////////////////////////////////

#elif defined D0005_TEST_FUNC_ACTIVATED
/**
 * @brief      test that compile error occurs when try to modify const STL
 *             through enumerate.
 */
int test_func(void)
{
    const std::vector<int> v{1, 22, 333};

    for (auto i: ken3::pyloop::enumerate(v)) {
        i.second += 1;
    }

    return 0;
}
/////////////////////////////////////////////////////////////////////////////

#elif defined D0006_TEST_FUNC_ACTIVATED
/**
 * @brief      test that compile error occurs when try to modify const std::string
 *             through enumerate.
 */
int test_func(void)
{
    const std::string s = "ABC";

    for (auto i: ken3::pyloop::enumerate(s)) {
        i.second += 1;
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

