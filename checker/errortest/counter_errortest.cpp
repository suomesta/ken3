/**
 * @file    counter_errortest.cpp
 * @brief   Define some test function to check compile error occurs.
 * @author  toda
 * @date    2019-04-01
 * @version 0.1.0
 * @remark  the target is C++11 or more
 */

#include "ken3/counter.hpp"

#if 0

#elif defined D0001_TEST_FUNC_ACTIVATED
/**
 * @brief      test that compile error occurs when not (MAXIMUM >= MINIMUM).
 */
int test_func(void)
{
    // MAXIMUM < MINIMUM
    ken3::counter<1, 2> c;

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

