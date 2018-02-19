/**
 * @file    unittest/pyloop/zip_test.cpp
 * @brief   Testing ken3::pyloop::zip() using lest.
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

    CASE("zip with array")
    {
        using ken3::pyloop::zip;

        int a1[3] = {1, 2, 3};
        int a2[3] = {4, 5, 6};

        std::vector<int> firsts;
        std::vector<int> seconds;

        for (auto i: zip(a1, a2)) {
            firsts.push_back(i.first);
            seconds.push_back(i.second);
        }

        EXPECT((std::vector<int>{1, 2, 3} == firsts));
        EXPECT((std::vector<int>{4, 5, 6} == seconds));
    },

    CASE("zip with STL containers")
    {
        using ken3::pyloop::zip;

        {
            std::array<int, 3> a{1, 2, 3};
            std::vector<int> v{4, 5, 6};

            std::vector<int> firsts;
            std::vector<int> seconds;

            for (auto i: zip(a, v)) {
                firsts.push_back(i.first);
                seconds.push_back(i.second);
            }

            EXPECT((std::vector<int>{1, 2, 3} == firsts));
            EXPECT((std::vector<int>{4, 5, 6} == seconds));
        }
        {
            std::set<int> s{1, 4, 2, 8, 5, 7};
            std::map<char, int> m{{'A', 10}, {'B', 11}, {'C', 12},
                                  {'D', 13}, {'E', 14}, {'F', 15}};

            std::vector<int> firsts;
            std::vector<char> secondfirsts;
            std::vector<int> secondseconds;

            for (auto i: zip(s, m)) {
                firsts.push_back(i.first);
                secondfirsts.push_back(i.second.first);
                secondseconds.push_back(i.second.second);
            }

            EXPECT((std::vector<int>{1, 2, 4, 5, 7, 8} == firsts));
            EXPECT((std::vector<char>{'A', 'B', 'C', 'D', 'E', 'F'} == secondfirsts));
            EXPECT((std::vector<int>{10, 11, 12, 13, 14, 15} == secondseconds));
        }
    },

    CASE("zip with std::string")
    {
        using ken3::pyloop::zip;

        std::string s1 = "ABC";
        std::string s2 = "abc";

        std::vector<char> firsts;
        std::vector<char> seconds;

        for (auto i: zip(s1, s2)) {
            firsts.push_back(i.first);
            seconds.push_back(i.second);
        }

        EXPECT((std::vector<char>{'A', 'B', 'C'} == firsts));
        EXPECT((std::vector<char>{'a', 'b', 'c'} == seconds));
    },

    CASE("zip with const array")
    {
        using ken3::pyloop::zip;

        const int a1[3] = {1, 2, 3};
        const int a2[3] = {4, 5, 6};

        std::vector<int> firsts;
        std::vector<int> seconds;

        for (auto i: zip(a1, a2)) {
            firsts.push_back(i.first);
            seconds.push_back(i.second);
        }

        EXPECT((std::vector<int>{1, 2, 3} == firsts));
        EXPECT((std::vector<int>{4, 5, 6} == seconds));
    },

    CASE("zip with const STL containers")
    {
        using ken3::pyloop::zip;

        {
            const std::array<int, 3> a{1, 2, 3};
            const std::vector<int> v{4, 5, 6};

            std::vector<int> firsts;
            std::vector<int> seconds;

            for (auto i: zip(a, v)) {
                firsts.push_back(i.first);
                seconds.push_back(i.second);
            }

            EXPECT((std::vector<int>{1, 2, 3} == firsts));
            EXPECT((std::vector<int>{4, 5, 6} == seconds));
        }
        {
            const std::set<int> s{1, 4, 2, 8, 5, 7};
            const std::map<char, int> m{{'A', 10}, {'B', 11}, {'C', 12},
                                        {'D', 13}, {'E', 14}, {'F', 15}};

            std::vector<int> firsts;
            std::vector<char> secondfirsts;
            std::vector<int> secondseconds;

            for (auto i: zip(s, m)) {
                firsts.push_back(i.first);
                secondfirsts.push_back(i.second.first);
                secondseconds.push_back(i.second.second);
            }

            EXPECT((std::vector<int>{1, 2, 4, 5, 7, 8} == firsts));
            EXPECT((std::vector<char>{'A', 'B', 'C', 'D', 'E', 'F'} == secondfirsts));
            EXPECT((std::vector<int>{10, 11, 12, 13, 14, 15} == secondseconds));
        }
    },

    CASE("zip with const std::string")
    {
        using ken3::pyloop::zip;

        const std::string s1 = "ABC";
        const std::string s2 = "abc";

        std::vector<char> firsts;
        std::vector<char> seconds;

        for (auto i: zip(s1, s2)) {
            firsts.push_back(i.first);
            seconds.push_back(i.second);
        }

        EXPECT((std::vector<char>{'A', 'B', 'C'} == firsts));
        EXPECT((std::vector<char>{'a', 'b', 'c'} == seconds));
    },

    CASE("modify zip items with array")
    {
        using ken3::pyloop::zip;

        int a1[3] = {1, 2, 3};
        int a2[3] = {4, 5, 6};

        for (auto i: zip(a1, a2)) {
            i.first *= 2;
            i.second *= 2;
        }

        EXPECT(2 == a1[0]);
        EXPECT(4 == a1[1]);
        EXPECT(6 == a1[2]);
        EXPECT(8 == a2[0]);
        EXPECT(10 == a2[1]);
        EXPECT(12 == a2[2]);
    },

    CASE("modify zip items with STL containers")
    {
        using ken3::pyloop::zip;

        {
            std::array<int, 3> a{1, 2, 3};
            std::vector<int> v{4, 5, 6};

            for (auto i: zip(a, v)) {
                i.first *= 2;
                i.second *= 2;
            }

            EXPECT((std::array<int, 3>{2, 4, 6} == a));
            EXPECT((std::vector<int>{8, 10, 12} == v));
        }
        {
            std::set<int> s{1, 4, 2, 8, 5, 7};
            std::map<char, int> m{{'A', 10}, {'B', 11}, {'C', 12},
                                  {'D', 13}, {'E', 14}, {'F', 15}};

            for (auto i: zip(s, m)) {
                i.second.second -= 10;
            }

            EXPECT((std::map<char, int>{{'A', 0}, {'B', 1}, {'C', 2}, {'D', 3}, {'E', 4}, {'F', 5}} == m));
        }
    },

    CASE("modify zip items with std::string")
    {
        using ken3::pyloop::zip;

        std::string s1 = "ABC";
        std::string s2 = "abc";

        for (auto i: zip(s1, s2)) {
            i.first += 3;
            i.second += 3;
        }

        EXPECT(std::string("DEF") == s1);
        EXPECT(std::string("def") == s2);
    },

    CASE("zip with empty STL containers")
    {
        using ken3::pyloop::zip;

        {
            std::array<int, 0> a;
            std::vector<int> v;

            for (auto i: zip(a, v)) {
                EXPECT(false);
            }
        }
        {
            std::set<int> s;
            std::map<char, int> m;

            for (auto i: zip(s, m)) {
                EXPECT(false);
            }
        }
    },

    CASE("zip with empty std::string")
    {
        using ken3::pyloop::zip;

        std::string s1 = "";
        std::string s2 = "";

        for (auto i: zip(s1, s2)) {
            EXPECT(false);
        }
    },

    CASE("zip when first argument is larger than the second")
    {
        using ken3::pyloop::zip;

        {
            int a[5] = {1, 2, 3, 4, 5};
            std::string s = "ABC";
            std::vector<int> firsts;
            std::vector<char> seconds;

            for (auto i: zip(a, s)) {
                firsts.push_back(i.first);
                seconds.push_back(i.second);
            }

            EXPECT((std::vector<int>{1, 2, 3} == firsts));
            EXPECT((std::vector<char>{'A', 'B', 'C'} == seconds));
        }
        {
            std::array<int, 5> a{1, 2, 3, 4, 5};
            std::vector<int> v{4, 5, 6};
            std::vector<int> firsts;
            std::vector<int> seconds;

            for (auto i: zip(a, v)) {
                firsts.push_back(i.first);
                seconds.push_back(i.second);
            }

            EXPECT((firsts == std::vector<int>{1, 2, 3}));
            EXPECT((seconds == std::vector<int>{4, 5, 6}));
        }
        {
            std::set<int> s{1, 4, 2, 8, 5, 7};
            std::map<char, int> m{{'A', 10}, {'B', 11}, {'C', 12}};
            std::vector<int> firsts;
            std::vector<char> secondfirsts;
            std::vector<int> secondseconds;

            for (auto i: zip(s, m)) {
                firsts.push_back(i.first);
                secondfirsts.push_back(i.second.first);
                secondseconds.push_back(i.second.second);
            }

            EXPECT((std::vector<int>{1, 2, 4} == firsts));
            EXPECT((std::vector<char>{'A', 'B', 'C'} == secondfirsts));
            EXPECT((std::vector<int>{10, 11, 12} == secondseconds));
        }
    },

    CASE("zip when second argument is larger than the first")
    {
        using ken3::pyloop::zip;

        {
            int a[3] = {1, 2, 3};
            std::string s = "ABCDEF";
            std::vector<int> firsts;
            std::vector<char> seconds;

            for (auto i: zip(a, s)) {
                firsts.push_back(i.first);
                seconds.push_back(i.second);
            }

            EXPECT((std::vector<int>{1, 2, 3} == firsts));
            EXPECT((std::vector<char>{'A', 'B', 'C'} == seconds));
        }
        {
            std::array<int, 3> a{1, 2, 3};
            std::vector<int> v{4, 5, 6, 7, 8};
            std::vector<int> firsts;
            std::vector<int> seconds;

            for (auto i: zip(a, v)) {
                firsts.push_back(i.first);
                seconds.push_back(i.second);
            }

            EXPECT((firsts == std::vector<int>{1, 2, 3}));
            EXPECT((seconds == std::vector<int>{4, 5, 6}));
        }
        {
            std::set<int> s{1, 4, 2};
            std::map<char, int> m{{'A', 10}, {'B', 11}, {'C', 12},
                                  {'D', 13}, {'E', 14}, {'F', 15}};
            std::vector<int> firsts;
            std::vector<char> secondfirsts;
            std::vector<int> secondseconds;

            for (auto i: zip(s, m)) {
                firsts.push_back(i.first);
                secondfirsts.push_back(i.second.first);
                secondseconds.push_back(i.second.second);
            }

            EXPECT((std::vector<int>{1, 2, 4} == firsts));
            EXPECT((std::vector<char>{'A', 'B', 'C'} == secondfirsts));
            EXPECT((std::vector<int>{10, 11, 12} == secondseconds));
        }
    },

    CASE("zip when two arguments are same instance")
    {
        using ken3::pyloop::zip;

        std::vector<int> v{1, 2, 3};
        std::vector<int> firsts;
        std::vector<int> seconds;

        for (auto i: zip(v, v)) {
            firsts.push_back(i.first);
            seconds.push_back(i.second);
        }

        EXPECT((std::vector<int>{1, 2, 3} == firsts));
        EXPECT((std::vector<int>{1, 2, 3} == seconds));
    },

};

extern lest::tests& specification();

MODULE(specification(), module)

