/**
 * @file    pyloop/zip_errortest.cpp
 * @brief   Define some test function to check compile error occurs.
 * @author  toda
 * @date    2017-08-25
 * @version 0.1.0
 * @remark  the target is C++11 or more
 */

#include <string>
#include <vector>
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

#elif defined D0005_TEST_FUNC_ACTIVATED
/**
 * @brief      test that compile error occurs when try to modify const array
 *             through zip.first.
 */
int test_func(void)
{
    const int array[3] = {1, 2, 3};
    int dummy[3] = {1, 2, 3};

    for (const auto& i: ken3::zip(array, dummy)) {
        i.first += 1;
    }

    return 0;
}
/////////////////////////////////////////////////////////////////////////////

#elif defined D0006_TEST_FUNC_ACTIVATED
/**
 * @brief      test that compile error occurs when try to modify const array
 *             through zip.second.
 */
int test_func(void)
{
    int dummy[3] = {1, 2, 3};
    const int array[3] = {1, 2, 3};

    for (const auto& i: ken3::zip(dummy, array)) {
        i.second += 1;
    }

    return 0;
}
/////////////////////////////////////////////////////////////////////////////

#elif defined D0007_TEST_FUNC_ACTIVATED
/**
 * @brief      test that compile error occurs when try to modify const STL
 *             through zip.first.
 */
int test_func(void)
{
    const std::vector<int> v{1, 2, 3};
    std::vector<int> dummy{1, 2, 3};

    for (const auto& i: ken3::zip(v, dummy)) {
        i.first += 1;
    }

    return 0;
}
/////////////////////////////////////////////////////////////////////////////

#elif defined D0008_TEST_FUNC_ACTIVATED
/**
 * @brief      test that compile error occurs when try to modify const STL
 *             through zip.second.
 */
int test_func(void)
{
    std::vector<int> dummy{1, 2, 3};
    const std::vector<int> v{1, 2, 3};

    for (const auto& i: ken3::zip(dummy, v)) {
        i.second += 1;
    }

    return 0;
}
/////////////////////////////////////////////////////////////////////////////

#elif defined D0009_TEST_FUNC_ACTIVATED
/**
 * @brief      test that compile error occurs when try to modify const std::string
 *             through zip.first.
 */
int test_func(void)
{
    const std::string s = "ABC";
    std::string dummy = "ABC";

    for (const auto& i: ken3::zip(s, dummy)) {
        i.first += 1;
    }

    return 0;
}
/////////////////////////////////////////////////////////////////////////////

#elif defined D0010_TEST_FUNC_ACTIVATED
/**
 * @brief      test that compile error occurs when try to modify const std::string
 *             through zip.second.
 */
int test_func(void)
{
    std::string dummy = "ABC";
    const std::string s = "ABC";

    for (const auto& i: ken3::zip(dummy, s)) {
        i.second += 1;
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

