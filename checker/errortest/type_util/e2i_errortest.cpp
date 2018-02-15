/**
 * @file    type_util/e2i_errortest.cpp
 * @brief   Define some test function to check compile error occurs.
 * @author  toda
 * @date    2017-07-21
 * @version 0.1.0
 * @remark  the target is C++11 or more
 */

#include "../../../ken3/type_util.hpp"

#if 0

#elif defined D0001_TEST_FUNC_ACTIVATED
/**
 * @brief      test that compile error occurs when template argument is
 *             int (not enum).
 */
int test_func(void)
{
    int i = 0;
    auto a = ken3::e2i(i);

    return 0;
}
/////////////////////////////////////////////////////////////////////////////

#elif defined D0002_TEST_FUNC_ACTIVATED
/**
 * @brief      test that compile error occurs when template argument is
 *             pointer (not enum).
 */
int test_func(void)
{
    int* p = nullptr;
    auto a = ken3::e2i(p);

    return 0;
}
/////////////////////////////////////////////////////////////////////////////

#elif defined D0003_TEST_FUNC_ACTIVATED
/**
 * @brief      test that compile error occurs when template argument is
 *             class (not enum).
 */
int test_func(void)
{
    class c
    {
    };
    auto a = ken3::e2i(c{});

    return 0;
}
/////////////////////////////////////////////////////////////////////////////

#elif defined D0004_TEST_FUNC_ACTIVATED
/**
 * @brief      test that compile error occurs when template argument is
 *             nullptr (not enum).
 */
int test_func(void)
{
    auto a = ken3::e2i(nullptr);

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
    return test_func();
}
/////////////////////////////////////////////////////////////////////////////

