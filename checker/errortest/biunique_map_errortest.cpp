/**
 * @file    biunique_map_errortest.cpp
 * @brief   Define some test function to check compile error occurs.
 * @author  toda
 * @date    2017-07-07
 * @version 0.1.0
 * @remark  the target is C++11 or more
 */

#include "../../ken3/biunique_map.hpp"

#if 0

#elif defined D0001_TEST_FUNC_ACTIVATED
/**
 * @brief      test that compile error occurs because of unknown type.
 */
int test_func(void)
{
    using ken3::biunique_map;

    // appoint wrong type
    biunique_map<int,
                 int,
                 static_cast<ken3::biunique_map_type>(4),
                 ken3::biunique_map_policy::silence> m;

    return 0;
}
/////////////////////////////////////////////////////////////////////////////

#elif defined D0002_TEST_FUNC_ACTIVATED
/**
 * @brief      test that compile error occurs because of unknown policy.
 */
int test_func(void)
{
    using ken3::biunique_map;

    // appoint wrong policy
    biunique_map<int,
                 int,
                 ken3::biunique_map_type::ordered_no_default,
                 static_cast<ken3::biunique_map_policy>(2)> m;

    return 0;
}
/////////////////////////////////////////////////////////////////////////////

#elif defined D0003_TEST_FUNC_ACTIVATED
/**
 * @brief      test that compile error occurs if first does not have operator<.
 */
int test_func(void)
{
    using ken3::biunique_map;

    struct no_lesser
    {
    private:
        bool operator<(const no_lesser& rhs) const;
    };

    // appoint no lesser struct as first type of map
    biunique_map<no_lesser, int> m = {{no_lesser{}, 0}, {no_lesser{}, 1}};

    return 0;
}
/////////////////////////////////////////////////////////////////////////////

#elif defined D0004_TEST_FUNC_ACTIVATED
/**
 * @brief      test that compile error occurs if first does not support hash.
 */
int test_func(void)
{
    using ken3::biunique_map;

    struct no_hash
    {
    };

    // appoint no has struct as first type of unordered_map
    biunique_map<no_hash, int, ken3::biunique_map_type::unordered_no_default> m{};

    return 0;
}
/////////////////////////////////////////////////////////////////////////////

#elif defined D0005_TEST_FUNC_ACTIVATED
/**
 * @brief      test that compile error occurs if second does not have operator==.
 */
int test_func(void)
{
    using ken3::biunique_map;

    struct no_equal
    {
    private:
        bool operator==(const no_equal& rhs) const;
    };

    // appoint no equal struct as second type
    biunique_map<int, no_equal> m = {{0, no_equal{}}, {1, no_equal{}}};

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

