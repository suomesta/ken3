/**
 * @file    type_util/array_size_errortest.cpp
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
    size_t size = ken3::array_size<decltype(i)>::value;

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
    size_t size = ken3::array_size<decltype(p)>::value;

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
    size_t size = ken3::array_size<decltype(array)>::value;

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
    size_t size = ken3::array_size<decltype(s)>::value;

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
    size_t size = ken3::array_size<decltype(v)>::value;

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
    size_t size = ken3::array_size<decltype(nullptr)>::value;

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
    size_t size = ken3::array_size<c>::value;

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
    size_t size = ken3::array_size<decltype(array)>::value;

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

