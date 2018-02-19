/**
 * @file    unittest/pyloop/range_test.cpp
 * @brief   Testing ken3::pyloop::range() using lest.
 * @author  toda
 * @date    2017-07-21
 * @version 0.1.0
 * @remark  the target is C++11 or more
 */

#include <limits>
#include <vector>
#include "ken3/pyloop.hpp"
#include "unittest/lest.hpp"

const lest::test module[] =
{

    CASE("range with argument {stop}")
    {
        using ken3::pyloop::range;

        std::vector<int> v;

        for (auto i: range(5)) {
            v.push_back(i);
        }

        EXPECT((std::vector<int>{0, 1, 2, 3, 4} == v));
    },

    CASE("range with argument {start, stop}")
    {
        using ken3::pyloop::range;

        std::vector<int> v;

        for (auto i: range(2, 5)) {
            v.push_back(i);
        }

        EXPECT((std::vector<int>{2, 3, 4} == v));
    },

    CASE("range with argument {start, stop, step}")
    {
        using ken3::pyloop::range;

        {
            std::vector<int> v;

            for (auto i: range(0, 5, 1)) {
                v.push_back(i);
            }

            EXPECT((std::vector<int>{0, 1, 2, 3, 4} == v));
        }
        {
            std::vector<int> v;

            for (auto i: range(0, 5, 2)) {
                v.push_back(i);
            }

            EXPECT((std::vector<int>{0, 2, 4} == v));
        }
        {
            std::vector<int> v;

            for (auto i: range(0, 5, 100)) {
                v.push_back(i);
            }

            EXPECT((std::vector<int>{0} == v));
        }
        {
            std::vector<int> v;

            for (auto i: range(5, 0, -1)) {
                v.push_back(i);
            }

            EXPECT((std::vector<int>{5, 4, 3, 2, 1} == v));
        }
        {
            std::vector<int> v;

            for (auto i: range(5, -1, -1)) {
                v.push_back(i);
            }

            EXPECT((std::vector<int>{5, 4, 3, 2, 1, 0} == v));
        }
        {
            std::vector<int> v;

            for (auto i: range(5, 0, -2)) {
                v.push_back(i);
            }

            EXPECT((std::vector<int>{5, 3, 1} == v));
        }
    },

    CASE("range with non-int tparam")
    {
        using ken3::pyloop::range;

        {
            std::vector<unsigned short> v;

            for (auto i: range<unsigned short>(0, 6, 2)) {
                v.push_back(i);
                EXPECT((std::is_same<unsigned short, decltype(i)>::value));
            }

            EXPECT((std::vector<unsigned short>{0, 2, 4} == v));
        }
        {
            std::vector<long long> v;

            for (auto i: range<long long>(10, 0, -2)) {
                v.push_back(i);
                EXPECT((std::is_same<long long, decltype(i)>::value));
            }

            EXPECT((std::vector<long long>{10, 8, 6, 4, 2} == v));
        }
    },

    CASE("in case range is empty")
    {
        using ken3::pyloop::range;

        for (auto i: range(5, 0)) {
            EXPECT(false);
        }

        for (auto i: range(5, 0, 2)) {
            EXPECT(false);
        }

        for (auto i: range(0, 5, -1)) {
            EXPECT(false);
        }

        for (auto i: range(5, 5)) {
            EXPECT(false);
        }

        for (auto i: range(5, 5, -1)) {
            EXPECT(false);
        }
    },

    CASE("range avoids overflow")
    {
        using ken3::pyloop::range;

        {
            std::vector<int> v;

            for (auto i: range(std::numeric_limits<int>::min(),
                               std::numeric_limits<int>::max(),
                               std::numeric_limits<int>::max()))
            {
                v.push_back(i);
            }

            std::vector<int> expected{
                std::numeric_limits<int>::min(),
                -1,
                std::numeric_limits<int>::max() - 1
            };
            EXPECT(expected == v);
        }
        {
            std::vector<int> v;

            for (auto i: range(std::numeric_limits<int>::max() - 5,
                               std::numeric_limits<int>::max(),
                               2))
            {
                v.push_back(i);
            }

            std::vector<int> expected{
                std::numeric_limits<int>::max() - 5,
                std::numeric_limits<int>::max() - 3,
                std::numeric_limits<int>::max() - 1
            };
            EXPECT(expected == v);
        }
        {
            std::vector<int> v;

            for (auto i: range(std::numeric_limits<int>::max(),
                               std::numeric_limits<int>::min(),
                               std::numeric_limits<int>::min()))
            {
                v.push_back(i);
            }

            std::vector<int> expected{
                std::numeric_limits<int>::max(),
                -1
            };
            EXPECT(expected == v);
        }
    },

    CASE("range throws because step is 0")
    {
        using ken3::pyloop::range;

        EXPECT_THROWS_AS(range(0, 5, 0), ken3::pyloop::ValueError);
        EXPECT_THROWS_AS(range(5, 0, 0), ken3::pyloop::ValueError);
    },

};

extern lest::tests& specification();

MODULE(specification(), module)

