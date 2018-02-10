/**
 * @file    metric_compile_error.cpp
 * @brief   Define some test function to check compile error occurs.
 * @author  toda
 * @date    2017-07-07
 * @version 0.1.0
 * @target  C++11
 */

#include "../../ken3/metric.hpp"

#if 0

#elif defined D0001_TEST_FUNC_ACTIVATED
/**
 * @brief      test that compile error occurs when unit does not match.
 */
int test_func(void)
{
    using namespace ken3::metric;

    // try to convert from length to time
    convert<Metre, Second>(0.0);

    return 0;
}
/////////////////////////////////////////////////////////////////////////////

#elif defined D0002_TEST_FUNC_ACTIVATED
/**
 * @brief      test that compile error occurs if unit does not match.
 */
int test_func(void)
{
    using namespace ken3::metric;

    // try to convert from length to speed
    convert<Metre, MetrePerSecond>(0.0);

    return 0;
}
/////////////////////////////////////////////////////////////////////////////

#elif defined D0003_TEST_FUNC_ACTIVATED
/**
 * @brief      test that compile error occurs if unit does not match.
 */
int test_func(void)
{
    using namespace ken3::metric;

    // try to convert from length to angle
    convert<Metre, Radian>(0.0);

    return 0;
}
/////////////////////////////////////////////////////////////////////////////

#elif defined D0004_TEST_FUNC_ACTIVATED
/**
 * @brief      test that compile error occurs if unit does not match.
 */
int test_func(void)
{
    using namespace ken3::metric;

    // try to convert from length to ROT
    convert<Metre, RadianPerSecond>(0.0);

    return 0;
}
/////////////////////////////////////////////////////////////////////////////

#elif defined D0005_TEST_FUNC_ACTIVATED
/**
 * @brief      test that compile error occurs if new unit includes 0.
 */
int test_func(void)
{
    using namespace ken3::metric;

    // define new unit
    using newUnit = ken3::metric::Unit<ken3::metric::Length, std::ratio<1, 0>>;
    convert<Metre, newUnit>(0.0);

    return 0;
}
/////////////////////////////////////////////////////////////////////////////

#elif defined D0006_TEST_FUNC_ACTIVATED
/**
 * @brief      test that compile error occurs if new unit includes 0.
 */
int test_func(void)
{
    using namespace ken3::metric;

    // define new unit
    using newUnit = ken3::metric::Unit<ken3::metric::Length, std::ratio<0, 1>>;
    convert<Metre, newUnit>(0.0);

    return 0;
}
/////////////////////////////////////////////////////////////////////////////

#elif defined D0007_TEST_FUNC_ACTIVATED
/**
 * @brief      test that compile error occurs if Unit's quantity is wrong.
 */
int test_func(void)
{
    using namespace ken3::metric;

    // define new unit
    using newUnit = ken3::metric::Unit<int, std::ratio<0, 1>>;
    convert<Metre, newUnit>(0.0);

    return 0;
}
/////////////////////////////////////////////////////////////////////////////

#elif defined D0008_TEST_FUNC_ACTIVATED
/**
 * @brief      test that compile error occurs if Unit's ratio is wrong.
 */
int test_func(void)
{
    using namespace ken3::metric;

    // define new unit
    using newUnit = ken3::metric::Unit<ken3::metric::Length, int>;
    convert<Metre, newUnit>(0.0);

    return 0;
}
/////////////////////////////////////////////////////////////////////////////

#elif defined D0009_TEST_FUNC_ACTIVATED
/**
 * @brief      test that compile error occurs if Unit is wrong.
 */
int test_func(void)
{
    using namespace ken3::metric;

    // define new unit
    using newUnit = int;
    convert<Metre, newUnit>(0.0);

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

