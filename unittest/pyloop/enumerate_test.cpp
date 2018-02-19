/**
 * @file    pyloop/enumerate_test.cpp
 * @brief   Testing ken3::pyloop::enumerate() using lest.
 * @author  toda
 * @date    2017-07-21
 * @version 0.1.0
 * @remark  the target is C++11 or more
 */

#include <array>
#include <map>
#include <set>
#include <string>
#include <vector>
#include "ken3/pyloop.hpp"
#include "unittest/lest.hpp"

const lest::test module[] =
{

    CASE("enumerate with array")
    {
        using ken3::pyloop::enumerate;

        int array[3] = {1, 2, 3};

        std::vector<int> firsts;
        std::vector<int> seconds;

        for (auto i: enumerate(array)) {
            firsts.push_back(i.first);
            seconds.push_back(i.second);
        }

        EXPECT((std::vector<int>{0, 1, 2} == firsts));
        EXPECT((std::vector<int>{1, 2, 3} == seconds));
    },

    CASE("enumerate with STL containers")
    {
        using ken3::pyloop::enumerate;

        {
            std::array<int, 3> a{1, 2, 3};

            std::vector<int> firsts;
            std::vector<int> seconds;

            for (auto i: enumerate(a)) {
                firsts.push_back(i.first);
                seconds.push_back(i.second);
            }

            EXPECT((std::vector<int>{0, 1, 2} == firsts));
            EXPECT((std::vector<int>{1, 2, 3} == seconds));
        }
        {
            std::map<char, int> m{{'A', 10}, {'B', 11}, {'C', 12},
                                  {'D', 13}, {'E', 14}, {'F', 15}};

            std::vector<int> firsts;
            std::vector<char> secondfirsts;
            std::vector<int> secondseconds;

            for (auto i: enumerate(m)) {
                firsts.push_back(i.first);
                secondfirsts.push_back(i.second.first);
                secondseconds.push_back(i.second.second);
            }

            EXPECT((std::vector<int>{0, 1, 2, 3, 4, 5} == firsts));
            EXPECT((std::vector<char>{'A', 'B', 'C', 'D', 'E', 'F'} == secondfirsts));
            EXPECT((std::vector<int>{10, 11, 12, 13, 14, 15} == secondseconds));
        }
        {
            std::set<int> s{1, 4, 2, 8, 5, 7};

            std::vector<int> firsts;
            std::vector<int> seconds;

            for (auto i: enumerate(s)) {
                firsts.push_back(i.first);
                seconds.push_back(i.second);
            }

            EXPECT((std::vector<int>{0, 1, 2, 3, 4, 5} == firsts));
            EXPECT((std::vector<int>{1, 2, 4, 5, 7, 8} == seconds));
        }
        {
            std::vector<int> v{1, 2, 3};

            std::vector<int> firsts;
            std::vector<int> seconds;

            for (auto i: enumerate(v)) {
                firsts.push_back(i.first);
                seconds.push_back(i.second);
            }

            EXPECT((std::vector<int>{0, 1, 2} == firsts));
            EXPECT((std::vector<int>{1, 2, 3} == seconds));
        }
    },

    CASE("enumerate with std::string")
    {
        using ken3::pyloop::enumerate;

        std::string str = "ABCD";

        std::vector<int> firsts;
        std::vector<char> seconds;

        for (auto i: enumerate(str)) {
            firsts.push_back(i.first);
            seconds.push_back(i.second);
        }

        EXPECT((std::vector<int>{0, 1, 2, 3} == firsts));
        EXPECT((std::vector<char>{'A', 'B', 'C', 'D'} == seconds));
    },

    CASE("enumerate with const array")
    {
        using ken3::pyloop::enumerate;

        const int array[3] = {1, 2, 3};

        std::vector<int> firsts;
        std::vector<int> seconds;

        for (auto i: enumerate(array)) {
            firsts.push_back(i.first);
            seconds.push_back(i.second);
        }

        EXPECT((std::vector<int>{0, 1, 2} == firsts));
        EXPECT((std::vector<int>{1, 2, 3} == seconds));
    },

    CASE("enumerate with const STL containers")
    {
        using ken3::pyloop::enumerate;

        {
            const std::array<int, 3> a{1, 2, 3};

            std::vector<int> firsts;
            std::vector<int> seconds;

            for (auto i: enumerate(a)) {
                firsts.push_back(i.first);
                seconds.push_back(i.second);
            }

            EXPECT((std::vector<int>{0, 1, 2} == firsts));
            EXPECT((std::vector<int>{1, 2, 3} == seconds));
        }
        {
            const std::map<char, int> m{{'A', 10}, {'B', 11}, {'C', 12},
                                        {'D', 13}, {'E', 14}, {'F', 15}};

            std::vector<int> firsts;
            std::vector<char> secondfirsts;
            std::vector<int> secondseconds;

            for (auto i: enumerate(m)) {
                firsts.push_back(i.first);
                secondfirsts.push_back(i.second.first);
                secondseconds.push_back(i.second.second);
            }

            EXPECT((std::vector<int>{0, 1, 2, 3, 4, 5} == firsts));
            EXPECT((std::vector<char>{'A', 'B', 'C', 'D', 'E', 'F'} == secondfirsts));
            EXPECT((std::vector<int>{10, 11, 12, 13, 14, 15} == secondseconds));
        }
        {
            const std::set<int> s{1, 4, 2, 8, 5, 7};

            std::vector<int> firsts;
            std::vector<int> seconds;

            for (auto i: enumerate(s)) {
                firsts.push_back(i.first);
                seconds.push_back(i.second);
            }

            EXPECT((std::vector<int>{0, 1, 2, 3, 4, 5} == firsts));
            EXPECT((std::vector<int>{1, 2, 4, 5, 7, 8} == seconds));
        }
        {
            const std::vector<int> v{1, 2, 3};

            std::vector<int> firsts;
            std::vector<int> seconds;

            for (auto i: enumerate(v)) {
                firsts.push_back(i.first);
                seconds.push_back(i.second);
            }

            EXPECT((std::vector<int>{0, 1, 2} == firsts));
            EXPECT((std::vector<int>{1, 2, 3} == seconds));
        }
    },

    CASE("enumerate with const std::string")
    {
        using ken3::pyloop::enumerate;

        const std::string str = "ABCD";

        std::vector<int> firsts;
        std::vector<char> seconds;

        for (auto i: enumerate(str)) {
            firsts.push_back(i.first);
            seconds.push_back(i.second);
        }

        EXPECT((std::vector<int>{0, 1, 2, 3} == firsts));
        EXPECT((std::vector<char>{'A', 'B', 'C', 'D'} == seconds));
    },

    CASE("modify enumerate items with array")
    {
        using ken3::pyloop::enumerate;

        int array[3] = {1, 2, 3};

        for (auto i: enumerate(array)) {
            i.second *= 2;
        }

        EXPECT(2 == array[0]);
        EXPECT(4 == array[1]);
        EXPECT(6 == array[2]);
    },

    CASE("modify enumerate items with STL containers")
    {
        using ken3::pyloop::enumerate;

        {
            std::array<int, 3> a{1, 2, 3};

            for (auto i: enumerate(a)) {
                i.second *= 2;
            }

            EXPECT((std::array<int, 3>{2, 4, 6} == a));
        }
        {
            std::map<char, int> m{{'A', 10}, {'B', 11}, {'C', 12},
                                  {'D', 13}, {'E', 14}, {'F', 15}};

            for (auto i: enumerate(m)) {
                i.second.second -= 10;
            }

            EXPECT((std::map<char, int>{{'A', 0}, {'B', 1}, {'C', 2}, {'D', 3}, {'E', 4}, {'F', 5}} == m));
        }
        {
            std::vector<int> v{1, 2, 3};

            for (auto i: enumerate(v)) {
                i.second *= 2;
            }

            EXPECT((std::vector<int>{2, 4, 6} == v));
        }
    },

    CASE("modify enumerate items with std::string")
    {
        using ken3::pyloop::enumerate;

        std::string str = "ABCD";

        for (auto i: enumerate(str)) {
            i.second += ('a' - 'A');
        }

        EXPECT(std::string("abcd") == str);
    },

    CASE("enumerate with zero sized containers")
    {
        using ken3::pyloop::enumerate;

        {
            std::array<int, 0> a;

            for (auto i: enumerate(a)) {
                EXPECT(false);
            }
        }
        {
            std::map<char, int> m;

            for (auto i: enumerate(m)) {
                EXPECT(false);
            }
        }
        {
            std::set<int> s;

            for (auto i: enumerate(s)) {
                EXPECT(false);
            }
        }
        {
            std::vector<int> v;

            for (auto i: enumerate(v)) {
                EXPECT(false);
            }
        }
        {
            std::string s;

            for (auto i: enumerate(s)) {
                EXPECT(false);
            }
        }
    },

};

extern lest::tests& specification();

MODULE(specification(), module)

