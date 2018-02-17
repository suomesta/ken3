/**
 * @file    pyloop/zip_errortest.cpp
 * @brief   Define some test function to check compile error occurs.
 * @author  toda
 * @date    2017-08-25
 * @version 0.1.0
 * @remark  the target is C++11 or more
 */

#include "ken3/pyloop.hpp"

#if 0

#elif defined D0001_TEST_FUNC_ACTIVATED
/**
 * @brief      test that compile error occurs when template 1st argument is
 *             int (not iterable).
 */
int test_func(void)
{
    int ten = 10;
    int array[10] = {};

    for (const auto& i: ken3::zip(ten, array)) {
        ;
    }

    return 0;
}
/////////////////////////////////////////////////////////////////////////////

#elif defined D0002_TEST_FUNC_ACTIVATED
/**
 * @brief      test that compile error occurs when template 2nd argument is
 *             int (not iterable).
 */
int test_func(void)
{
    int ten = 10;
    int array[10] = {};

    for (const auto& i: ken3::zip(array, ten)) {
        ;
    }

    return 0;
}
/////////////////////////////////////////////////////////////////////////////

#elif defined D0003_TEST_FUNC_ACTIVATED
/**
 * @brief      test that compile error occurs when template 1st argument is
 *             pointer (not iterable).
 */
int test_func(void)
{
    int ten = 10;
    int array[10] = {};
    int* p = &ten;

    for (const auto& i: ken3::zip(p, array)) {
        ;
    }

    return 0;
}
/////////////////////////////////////////////////////////////////////////////

#elif defined D0004_TEST_FUNC_ACTIVATED
/**
 * @brief      test that compile error occurs when template 1st argument is
 *             pointer (not iterable).
 */
int test_func(void)
{
    int ten = 10;
    int array[10] = {};
    int* p = &ten;

    for (const auto& i: ken3::zip(array, p)) {
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

