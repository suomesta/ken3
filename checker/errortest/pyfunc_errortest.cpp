/**
 * @file    pyfunc_errortest.cpp
 * @brief   Define some test function to check compile error occurs.
 * @author  toda
 * @date    2018-03-13
 * @version 0.1.0
 * @remark  the target is C++11 or more
 */

#include <functional>
#include "ken3/pyfunc.hpp"

#if 0

#elif defined D0001_TEST_FUNC_ACTIVATED
/**
 * @brief      test that compile error occurs when bool_cast() is neither bool castable nor iterable.
 */
int test_func(void)
{
    using namespace ken3::py;

    // first argument is neither bool castable nor iterable
    struct tmp {};
    tmp t;
    bool_cast(t);

    return 0;
}
/////////////////////////////////////////////////////////////////////////////

#elif defined D0002_TEST_FUNC_ACTIVATED
/**
 * @brief      test that compile error occurs when min() first argument is not iterable.
 */
int test_func(void)
{
    using namespace ken3::py;

    // first argument is not iterable
    min(0);

    return 0;
}
/////////////////////////////////////////////////////////////////////////////

#elif defined D0003_TEST_FUNC_ACTIVATED
/**
 * @brief      test that compile error occurs when min() first argument does not have operator<.
 */
int test_func(void)
{
    using namespace ken3::py;

    // second argument is not function
    struct tmp {};
    tmp array[3];
    min(array);

    return 0;
}
/////////////////////////////////////////////////////////////////////////////

#elif defined D0004_TEST_FUNC_ACTIVATED
/**
 * @brief      test that compile error occurs when min() second argument is not function.
 */
int test_func(void)
{
    using namespace ken3::py;

    // second argument is not function
    int array[3] = {0, 1, 2};
    min(array, 0);

    return 0;
}
/////////////////////////////////////////////////////////////////////////////

#elif defined D0005_TEST_FUNC_ACTIVATED
/**
 * @brief      test that compile error occurs when min() second argument does not have return value.
 */
int test_func(void)
{
    using namespace ken3::py;

    // second argument does not have return value
    auto no_return = [](int i) {
        ;
    };
    int array[3] = {0, 1, 2};
    min(array, no_return);

    return 0;
}
/////////////////////////////////////////////////////////////////////////////

#elif defined D0006_TEST_FUNC_ACTIVATED
/**
 * @brief      test that compile error occurs when max() first argument is not iterable.
 */
int test_func(void)
{
    using namespace ken3::py;

    // first argument is not iterable
    max(0);

    return 0;
}
/////////////////////////////////////////////////////////////////////////////

#elif defined D0007_TEST_FUNC_ACTIVATED
/**
 * @brief      test that compile error occurs when max() first argument does not have operator<.
 */
int test_func(void)
{
    using namespace ken3::py;

    // second argument is not function
    struct tmp {};
    tmp array[3];
    max(array);

    return 0;
}
/////////////////////////////////////////////////////////////////////////////

#elif defined D0008_TEST_FUNC_ACTIVATED
/**
 * @brief      test that compile error occurs when max() second argument is not function.
 */
int test_func(void)
{
    using namespace ken3::py;

    // second argument is not function
    int array[3] = {0, 1, 2};
    max(array, 0);

    return 0;
}
/////////////////////////////////////////////////////////////////////////////

#elif defined D0009_TEST_FUNC_ACTIVATED
/**
 * @brief      test that compile error occurs when max() second argument does not have return value.
 */
int test_func(void)
{
    using namespace ken3::py;

    // second argument does not have return value
    auto no_return = [](int i) {
        ;
    };
    int array[3] = {0, 1, 2};
    max(array, no_return);

    return 0;
}
/////////////////////////////////////////////////////////////////////////////

#elif defined D0010_TEST_FUNC_ACTIVATED
/**
 * @brief      test that compile error occurs when all() the argument is not iterable.
 */
int test_func(void)
{
    using namespace ken3::py;

    // the argument is not iterable
    all(1);

    return 0;
}
/////////////////////////////////////////////////////////////////////////////

#elif defined D0011_TEST_FUNC_ACTIVATED
/**
 * @brief      test that compile error occurs when all() the argument cannot be converted into bool.
 */
int test_func(void)
{
    using namespace ken3::py;

    // the argument cannot be converted into bool
    struct tmp {};
    tmp array[3];
    all(array);

    return 0;
}
/////////////////////////////////////////////////////////////////////////////

#elif defined D0012_TEST_FUNC_ACTIVATED
/**
 * @brief      test that compile error occurs when any() the argument is not iterable.
 */
int test_func(void)
{
    using namespace ken3::py;

    // the argument is not iterable
    any(1);

    return 0;
}
/////////////////////////////////////////////////////////////////////////////

#elif defined D0013_TEST_FUNC_ACTIVATED
/**
 * @brief      test that compile error occurs when any() the argument cannot be converted into bool.
 */
int test_func(void)
{
    using namespace ken3::py;

    // the argument cannot be converted into bool
    struct tmp {};
    tmp array[3];
    any(array);

    return 0;
}
/////////////////////////////////////////////////////////////////////////////

#elif defined D0014_TEST_FUNC_ACTIVATED
/**
 * @brief      test that compile error occurs when sum() first argument is not iterable.
 */
int test_func(void)
{
    using namespace ken3::py;

    // first argument is not iterable
    sum(1);

    return 0;
}
/////////////////////////////////////////////////////////////////////////////

#elif defined D0015_TEST_FUNC_ACTIVATED
/**
 * @brief      test that compile error occurs when sum() first argument does not accept accumulate.
 */
int test_func(void)
{
    using namespace ken3::py;

    // first argument does not accept accumulate
    struct tmp {};
    tmp array[3];
    sum(array);

    return 0;
}
/////////////////////////////////////////////////////////////////////////////

#elif defined D0016_TEST_FUNC_ACTIVATED
/**
 * @brief      test that compile error occurs when sum() second argument does not match.
 */
int test_func(void)
{
    using namespace ken3::py;

    // second argument does not match
    struct tmp {};
    int array[3] = {1, 2, 3};
    tmp t;
    sum(array, t);

    return 0;
}
/////////////////////////////////////////////////////////////////////////////

#elif defined D0017_TEST_FUNC_ACTIVATED
/**
 * @brief      test that compile error occurs when reduce() first argument is not function.
 */
int test_func(void)
{
    using namespace ken3::py;

    // first argument is not function
    int array[3] = {1, 2, 3};
    reduce(1, array);

    return 0;
}
/////////////////////////////////////////////////////////////////////////////

#elif defined D0018_TEST_FUNC_ACTIVATED
/**
 * @brief      test that compile error occurs when reduce() first argument does not have return value.
 */
int test_func(void)
{
    using namespace ken3::py;

    // first argument does not have return value
    auto no_return = [](int i, int j) {
        ;
    };
    int array[3] = {1, 2, 3};
    reduce(no_return, array);

    return 0;
}
/////////////////////////////////////////////////////////////////////////////

#elif defined D0019_TEST_FUNC_ACTIVATED
/**
 * @brief      test that compile error occurs when reduce() second argument is not iterable.
 */
int test_func(void)
{
    using namespace ken3::py;

    // second argument is not iterable
    reduce(std::plus<int>(), 1);

    return 0;
}
/////////////////////////////////////////////////////////////////////////////

#elif defined D0020_TEST_FUNC_ACTIVATED
/**
 * @brief      test that compile error occurs when reduce() third argument does not match.
 */
int test_func(void)
{
    using namespace ken3::py;

    // third argument does not match
    struct tmp {};
    int array[3] = {1, 2, 3};
    tmp t;
    reduce(std::plus<int>(), array, t);

    return 0;
}
/////////////////////////////////////////////////////////////////////////////

#elif defined D0021_TEST_FUNC_ACTIVATED
/**
 * @brief      test that compile error occurs when map() first argument is not function.
 */
int test_func(void)
{
    using namespace ken3::py;

    // first argument is not function
    int array[3] = {1, 2, 3};
    map(1, array);

    return 0;
}
/////////////////////////////////////////////////////////////////////////////

#elif defined D0022_TEST_FUNC_ACTIVATED
/**
 * @brief      test that compile error occurs when map() first argument does not have return value.
 */
int test_func(void)
{
    using namespace ken3::py;

    // first argument does not have return value
    auto no_return = [](int i) {
        ;
    };
    int array[3] = {1, 2, 3};
    map(no_return, array);

    return 0;
}
/////////////////////////////////////////////////////////////////////////////

#elif defined D0023_TEST_FUNC_ACTIVATED
/**
 * @brief      test that compile error occurs when map() second argument is not iterable.
 */
int test_func(void)
{
    using namespace ken3::py;

    // second argument is not iterable
    auto exp2 = [](int i) -> int {
        return i * i;
    };
    map(exp2, 1);

    return 0;
}
/////////////////////////////////////////////////////////////////////////////

#elif defined D0024_TEST_FUNC_ACTIVATED
/**
 * @brief      test that compile error occurs when filter() first argument is not function.
 */
int test_func(void)
{
    using namespace ken3::py;

    // first argument is not function
    int array[3] = {1, 2, 3};
    filter(1, array);

    return 0;
}
/////////////////////////////////////////////////////////////////////////////

#elif defined D0025_TEST_FUNC_ACTIVATED
/**
 * @brief      test that compile error occurs when filter() first argument does not have return value.
 */
int test_func(void)
{
    using namespace ken3::py;

    // first argument does not have return value
    auto no_return = [](int i) {
        ;
    };
    int array[3] = {1, 2, 3};
    filter(no_return, array);

    return 0;
}
/////////////////////////////////////////////////////////////////////////////

#elif defined D0026_TEST_FUNC_ACTIVATED
/**
 * @brief      test that compile error occurs when filter() second argument is not iterable.
 */
int test_func(void)
{
    using namespace ken3::py;

    // second argument is not iterable
    auto f = [](int i) -> bool {
        return static_cast<bool>(i);
    };
    filter(f, 1);

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

