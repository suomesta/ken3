/**
 * @file    int_cast_errortest.cpp
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
 *             bool in FROM.
 */
int test_func(void)
{
    auto i = ken3::int_cast<bool, int>(true);

    return 0;
}
/////////////////////////////////////////////////////////////////////////////

#elif defined D0002_TEST_FUNC_ACTIVATED
/**
 * @brief      test that compile error occurs when template argument is
 *             bool in TO.
 */
int test_func(void)
{
    auto i = ken3::int_cast<int, bool>(0);

    return 0;
}
/////////////////////////////////////////////////////////////////////////////

#elif defined D0003_TEST_FUNC_ACTIVATED
/**
 * @brief      test that compile error occurs when template argument is
 *             float in FROM.
 */
int test_func(void)
{
    auto i = ken3::int_cast<float, int>(0.0f);

    return 0;
}
/////////////////////////////////////////////////////////////////////////////

#elif defined D0004_TEST_FUNC_ACTIVATED
/**
 * @brief      test that compile error occurs when template argument is
 *             float in TO.
 */
int test_func(void)
{
    auto i = ken3::int_cast<int, float>(0);

    return 0;
}
/////////////////////////////////////////////////////////////////////////////

#elif defined D0005_TEST_FUNC_ACTIVATED
/**
 * @brief      test that compile error occurs when template argument is
 *             double in FROM.
 */
int test_func(void)
{
    auto i = ken3::int_cast<double, int>(0.0);

    return 0;
}
/////////////////////////////////////////////////////////////////////////////

#elif defined D0006_TEST_FUNC_ACTIVATED
/**
 * @brief      test that compile error occurs when template argument is
 *             double in TO.
 */
int test_func(void)
{
    auto i = ken3::int_cast<int, double>(0);

    return 0;
}
/////////////////////////////////////////////////////////////////////////////

#elif defined D0007_TEST_FUNC_ACTIVATED
/**
 * @brief      test that compile error occurs when template argument is
 *             long double in FROM.
 */
int test_func(void)
{
    auto i = ken3::int_cast<long double, int>(0.0);

    return 0;
}
/////////////////////////////////////////////////////////////////////////////

#elif defined D0008_TEST_FUNC_ACTIVATED
/**
 * @brief      test that compile error occurs when template argument is
 *             long double in TO.
 */
int test_func(void)
{
    auto i = ken3::int_cast<int, long double>(0);

    return 0;
}
/////////////////////////////////////////////////////////////////////////////

#elif defined D0009_TEST_FUNC_ACTIVATED
/**
 * @brief      test that compile error occurs when template argument is
 *             void* in FROM.
 */
int test_func(void)
{
    auto i = ken3::int_cast<void*, int>(nullptr);

    return 0;
}
/////////////////////////////////////////////////////////////////////////////

#elif defined D0010_TEST_FUNC_ACTIVATED
/**
 * @brief      test that compile error occurs when template argument is
 *             void* in TO.
 */
int test_func(void)
{
    auto i = ken3::int_cast<int, void*>(0);

    return 0;
}
/////////////////////////////////////////////////////////////////////////////

#elif defined D0011_TEST_FUNC_ACTIVATED
/**
 * @brief      test that compile error occurs when template argument is
 *             a class object in FROM.
 */
int test_func(void)
{
    class c{};
    auto i = ken3::int_cast<c, int>(c{});

    return 0;
}
/////////////////////////////////////////////////////////////////////////////

#elif defined D0012_TEST_FUNC_ACTIVATED
/**
 * @brief      test that compile error occurs when template argument is
 *             a class object in TO.
 */
int test_func(void)
{
    class c{};
    auto i = ken3::int_cast<int, c>(0);

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

