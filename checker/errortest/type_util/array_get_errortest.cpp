/**
 * @file    type_util/array_get_errortest.cpp
 * @brief   Define some test function to check compile error occurs.
 * @author  toda
 * @date    2017-07-21
 * @version 0.1.0
 * @remark  the target is C++11 or more
 */

#include <array>
#include <string>
#include <vector>
#include "ken3/type_util.hpp"

#if 0

#elif defined D0001_TEST_FUNC_ACTIVATED
/**
 * @brief      test that compile error occurs when template argument is
 *             int (not array).
 */
int test_func(void)
{
    int i = 0;
    auto a = ken3::array_get<0>(i)>;

    return 0;
}
/////////////////////////////////////////////////////////////////////////////

#elif defined D0002_TEST_FUNC_ACTIVATED
/**
 * @brief      test that compile error occurs when template argument is
 *             pointer (not array).
 */
int test_func(void)
{
    int array[3] = {1, 2, 3};
    int* p = array;
    auto a = ken3::array_get<0>(p)>;

    return 0;
}
/////////////////////////////////////////////////////////////////////////////

#elif defined D0003_TEST_FUNC_ACTIVATED
/**
 * @brief      test that compile error occurs when template argument is
 *             std::array (not array).
 */
int test_func(void)
{
    std::array<int, 3> array{1, 2, 3};
    auto a = ken3::array_get<0>(array)>;

    return 0;
}
/////////////////////////////////////////////////////////////////////////////

#elif defined D0004_TEST_FUNC_ACTIVATED
/**
 * @brief      test that compile error occurs when template argument is
 *             std::string (not array).
 */
int test_func(void)
{
    std::string s{"str"};
    auto a = ken3::array_get<0>(s)>;

    return 0;
}
/////////////////////////////////////////////////////////////////////////////

#elif defined D0005_TEST_FUNC_ACTIVATED
/**
 * @brief      test that compile error occurs when template argument is
 *             std::vector (not array).
 */
int test_func(void)
{
    std::vector<int> v{1, 2, 3};
    auto a = ken3::array_get<0>(v)>;

    return 0;
}
/////////////////////////////////////////////////////////////////////////////

#elif defined D0006_TEST_FUNC_ACTIVATED
/**
 * @brief      test that compile error occurs when template argument is
 *             decltype(nullptr) (not array).
 */
int test_func(void)
{
    auto a = ken3::array_get<0>(nullptr)>;

    return 0;
}
/////////////////////////////////////////////////////////////////////////////

#elif defined D0007_TEST_FUNC_ACTIVATED
/**
 * @brief      test that compile error occurs when template argument is
 *             class (not array).
 */
int test_func(void)
{
    class c
    {
    };
    auto a = ken3::array_get<0>(c)>;

    return 0;
}
/////////////////////////////////////////////////////////////////////////////

#elif defined D0008_TEST_FUNC_ACTIVATED
/**
 * @brief      test that compile error occurs when template argument is
 *             2-dimension array.
 */
int test_func(void)
{
    int array[2][2] = {{0, 1}, {2, 3}};
    auto a = ken3::array_get<0>(array)>;

    return 0;
}
/////////////////////////////////////////////////////////////////////////////

#elif defined D0009_TEST_FUNC_ACTIVATED
/**
 * @brief      test that compile error occurs when index is out of bounds.
 */
int test_func(void)
{
    int array[3] = {1, 2, 3};
    auto a = ken3::array_get<3>(array)>;

    return 0;
}
/////////////////////////////////////////////////////////////////////////////

#elif defined D0010_TEST_FUNC_ACTIVATED
/**
 * @brief      test that compile error occurs when index is out of bounds
 *             once more.
 */
int test_func(void)
{
    int array[3] = {1, 2, 3};
    auto a = ken3::array_get<100>(array)>;

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

