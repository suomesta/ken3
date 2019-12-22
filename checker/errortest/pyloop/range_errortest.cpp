/**
 * @file    pyloop/range_errortest.cpp
 * @brief   Define some test function to check compile error occurs.
 * @author  toda
 * @date    2017-08-25
 * @version 0.1.0
 * @remark  the target is C++11 or more
 */

#include <string>
#include "ken3/pyloop.hpp"

#if 0

#elif defined D0001_TEST_FUNC_ACTIVATED
/**
 * @brief      test that compile error occurs when template argument is
 *             bool (range does not accept).
 */
int test_func(void)
{
    for (const auto& i: ken3::py::range<bool>(true)) {
        ;
    }

    return 0;
}
/////////////////////////////////////////////////////////////////////////////

#elif defined D0002_TEST_FUNC_ACTIVATED
/**
 * @brief      test that compile error occurs when template argument is
 *             not integral (std::string).
 */
int test_func(void)
{
    for (const auto& i: ken3::py::range(std::string("abc"))) {
        ;
    }

    return 0;
}
/////////////////////////////////////////////////////////////////////////////

#elif defined D0003_TEST_FUNC_ACTIVATED
/**
 * @brief      test that compile error occurs when template argument is
 *             not integral (struct).
 */
int test_func(void)
{
    struct S{};

    for (const auto& i: ken3::py::range(S{})) {
        ;
    }

    return 0;
}
/////////////////////////////////////////////////////////////////////////////

#elif defined D0004_TEST_FUNC_ACTIVATED
/**
 * @brief      test that compile error occurs when template argument is
 *             not integral (pointer).
 */
int test_func(void)
{
    int i = 0;
    int* p = &i;

    for (const auto& i: ken3::py::range(p)) {
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

