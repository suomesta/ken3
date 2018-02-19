/**
 * @file    string_to_errortest.cpp
 * @brief   Define some test function to check compile error occurs.
 * @author  toda
 * @date    2018-02-18
 * @version 0.1.0
 * @remark  the target is C++11 or more
 */

#include "ken3/cast.hpp"

#if 0

#elif defined D0001_TEST_FUNC_ACTIVATED
/**
 * @brief      test that compile error occurs when template argument is
 *             bool (not supported).
 */
int test_func(void)
{
    auto i = ken3::string_to<bool>("0");

    return 0;
}
/////////////////////////////////////////////////////////////////////////////

#elif defined D0002_TEST_FUNC_ACTIVATED
/**
 * @brief      test that compile error occurs when template argument is
 *             pointer.
 */
int test_func(void)
{
    auto i = ken3::string_to<void*>("0");

    return 0;
}
/////////////////////////////////////////////////////////////////////////////

#elif defined D0003_TEST_FUNC_ACTIVATED
/**
 * @brief      test that compile error occurs when template argument is
 *             class.
 */
int test_func(void)
{
    class c{};
    auto i = ken3::string_to<c>("0");

    return 0;
}
/////////////////////////////////////////////////////////////////////////////

#elif defined D0004_TEST_FUNC_ACTIVATED
/**
 * @brief      test that compile error occurs when template argument is
 *             enum.
 */
int test_func(void)
{
    enum class e_int : int
    {
        zero = 0,
        one,
    };
    auto i = ken3::string_to<e_int>("0");

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

