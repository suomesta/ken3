/**
 * @file    overflow_errortest.cpp
 * @brief   Define some test function to check compile error occurs.
 * @author  toda
 * @date    2019-12-31
 * @version 0.1.0
 * @remark  the target is C++11 or more
 */

#include "ken3/overflow.hpp"

#if 0

#elif defined D0001_TEST_FUNC_ACTIVATED
/**
 * @brief      test that compile error occurs when overflow::occur_add() with non-integer.
 */
int test_func(void)
{
    using namespace ken3::overflow;

    // give double (non-integer) to occur_add()
    occur_add(1.0, 1.0);

    return 0;
}
/////////////////////////////////////////////////////////////////////////////

#elif defined D0002_TEST_FUNC_ACTIVATED
/**
 * @brief      test that compile error occurs when overflow::occur_sub() with non-integer.
 */
int test_func(void)
{
    using namespace ken3::overflow;

    // give double (non-integer) to occur_sub()
    occur_sub(1.0, 1.0);

    return 0;
}
/////////////////////////////////////////////////////////////////////////////

#elif defined D0003_TEST_FUNC_ACTIVATED
/**
 * @brief      test that compile error occurs when overflow::occur_mul() with non-integer.
 */
int test_func(void)
{
    using namespace ken3::overflow;

    // give double (non-integer) to occur_mul()
    occur_mul(1.0, 1.0);

    return 0;
}
/////////////////////////////////////////////////////////////////////////////

#elif defined D0004_TEST_FUNC_ACTIVATED
/**
 * @brief      test that compile error occurs when overflow::occur_div() with non-integer.
 */
int test_func(void)
{
    using namespace ken3::overflow;

    // give double (non-integer) to occur_div()
    occur_div(1.0, 1.0);

    return 0;
}
/////////////////////////////////////////////////////////////////////////////

#elif defined D0005_TEST_FUNC_ACTIVATED
/**
 * @brief      test that compile error occurs when overflow::occur_abs() with non-integer.
 */
int test_func(void)
{
    using namespace ken3::overflow;

    // give double (non-integer) to occur_abs()
    occur_abs(1.0);

    return 0;
}
/////////////////////////////////////////////////////////////////////////////

#elif defined D0006_TEST_FUNC_ACTIVATED
/**
 * @brief      test that compile error occurs when overflow::occur_add() with bool.
 */
int test_func(void)
{
    using namespace ken3::overflow;

    // give bool to occur_add()
    occur_add(true, false);

    return 0;
}
/////////////////////////////////////////////////////////////////////////////

#elif defined D0007_TEST_FUNC_ACTIVATED
/**
 * @brief      test that compile error occurs when overflow::occur_sub() with bool.
 */
int test_func(void)
{
    using namespace ken3::overflow;

    // give bool to occur_sub()
    occur_sub(true, false);

    return 0;
}
/////////////////////////////////////////////////////////////////////////////

#elif defined D0008_TEST_FUNC_ACTIVATED
/**
 * @brief      test that compile error occurs when overflow::occur_mul() with bool.
 */
int test_func(void)
{
    using namespace ken3::overflow;

    // give bool to occur_mul()
    occur_mul(true, false);

    return 0;
}
/////////////////////////////////////////////////////////////////////////////

#elif defined D0009_TEST_FUNC_ACTIVATED
/**
 * @brief      test that compile error occurs when overflow::occur_div() with bool.
 */
int test_func(void)
{
    using namespace ken3::overflow;

    // give bool to occur_div()
    occur_div(true, false);

    return 0;
}
/////////////////////////////////////////////////////////////////////////////

#elif defined D0010_TEST_FUNC_ACTIVATED
/**
 * @brief      test that compile error occurs when overflow::occur_abs() with bool.
 */
int test_func(void)
{
    using namespace ken3::overflow;

    // give bool to occur_abs()
    occur_abs(true);

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

