/**
 * @file    unittest/cast/int_cast_test.cpp
 * @brief   Testing ken3::int_cast() using lest.
 * @author  toda
 * @date    2018-02-18
 * @version 0.1.0
 * @remark  the target is C++11 or more
 */

#include <limits>
#include "ken3/cast.hpp"
#include "unittest/lest.hpp"

const lest::test module[] =
{

    CASE("int_cast() accepts any integer type (except bool)")
    {
        using ken3::int_cast;

        EXPECT(((0 == int_cast<signed char, int>(0))));
        EXPECT((0 == int_cast<unsigned char, int>(0)));
        EXPECT((0 == int_cast<short, int>(0)));
        EXPECT((0 == int_cast<unsigned short, int>(0)));
        EXPECT((0 == int_cast<int, int>(0)));
        EXPECT((0 == int_cast<unsigned int, int>(0)));
        EXPECT((0 == int_cast<long, int>(0)));
        EXPECT((0 == int_cast<unsigned long, int>(0)));
        EXPECT((0 == int_cast<long long, int>(0)));
        EXPECT((0 == int_cast<unsigned long long, int>(0)));
        EXPECT((0 == int_cast<char, int>(0)));
        EXPECT((0 == int_cast<wchar_t, int>(0)));
        EXPECT((0 == int_cast<char16_t, int>(0)));
        EXPECT((0 == int_cast<char32_t, int>(0)));

        EXPECT((0 == int_cast<int, signed char>(0)));
        EXPECT((0 == int_cast<int, unsigned char>(0)));
        EXPECT((0 == int_cast<int, short>(0)));
        EXPECT((0 == int_cast<int, unsigned short>(0)));
        EXPECT((0 == int_cast<int, int>(0)));
        EXPECT((0 == int_cast<int, unsigned int>(0)));
        EXPECT((0 == int_cast<int, long>(0)));
        EXPECT((0 == int_cast<int, unsigned long>(0)));
        EXPECT((0 == int_cast<int, long long>(0)));
        EXPECT((0 == int_cast<int, unsigned long long>(0)));
        EXPECT((0 == int_cast<int, char>(0)));
        EXPECT((0 == int_cast<int, wchar_t>(0)));
        EXPECT((0 == int_cast<int, char16_t>(0)));
        EXPECT((0 == int_cast<int, char32_t>(0)));
    },

    CASE("int_cast() can cast maximum value of FROM type")
    {
        using ken3::int_cast;

        long long imax;
        {
            using type = signed char;
            imax = std::numeric_limits<type>::max();
            EXPECT((imax == int_cast<type, long long>(std::numeric_limits<type>::max())));
        }
        {
            using type = short;
            imax = std::numeric_limits<type>::max();
            EXPECT((imax == int_cast<type, long long>(std::numeric_limits<type>::max())));
        }
        {
            using type = int;
            imax = std::numeric_limits<type>::max();
            EXPECT((imax == int_cast<type, long long>(std::numeric_limits<type>::max())));
        }
        {
            using type = long;
            imax = std::numeric_limits<type>::max();
            EXPECT((imax == int_cast<type, long long>(std::numeric_limits<type>::max())));
        }
        {
            using type = long long;
            imax = std::numeric_limits<type>::max();
            EXPECT((imax == int_cast<type, long long>(std::numeric_limits<type>::max())));
        }

        unsigned long long umax;
        {
            using type = unsigned char;
            umax = std::numeric_limits<type>::max();
            EXPECT((umax == int_cast<type, unsigned long long>(std::numeric_limits<type>::max())));
        }
        {
            using type = unsigned short;
            umax = std::numeric_limits<type>::max();
            EXPECT((umax == int_cast<type, unsigned long long>(std::numeric_limits<type>::max())));
        }
        {
            using type = unsigned int;
            umax = std::numeric_limits<type>::max();
            EXPECT((umax == int_cast<type, unsigned long long>(std::numeric_limits<type>::max())));
        }
        {
            using type = unsigned long;
            umax = std::numeric_limits<type>::max();
            EXPECT((umax == int_cast<type, unsigned long long>(std::numeric_limits<type>::max())));
        }
        {
            using type = unsigned long long;
            umax = std::numeric_limits<type>::max();
            EXPECT((umax == int_cast<type, unsigned long long>(std::numeric_limits<type>::max())));
        }
    },

    CASE("int_cast() can cast minimum value of FROM type")
    {
        using ken3::int_cast;

        long long imin;
        {
            using type = signed char;
            imin = std::numeric_limits<type>::lowest();
            EXPECT((imin == int_cast<type, long long>(std::numeric_limits<type>::lowest())));
        }
        {
            using type = short;
            imin = std::numeric_limits<type>::lowest();
            EXPECT((imin == int_cast<type, long long>(std::numeric_limits<type>::lowest())));
        }
        {
            using type = int;
            imin = std::numeric_limits<type>::lowest();
            EXPECT((imin == int_cast<type, long long>(std::numeric_limits<type>::lowest())));
        }
        {
            using type = long;
            imin = std::numeric_limits<type>::lowest();
            EXPECT((imin == int_cast<type, long long>(std::numeric_limits<type>::lowest())));
        }
        {
            using type = long long;
            imin = std::numeric_limits<type>::lowest();
            EXPECT((imin == int_cast<type, long long>(std::numeric_limits<type>::lowest())));
        }

        unsigned long long umin;
        {
            using type = unsigned char;
            umin = std::numeric_limits<type>::lowest();
            EXPECT((umin == int_cast<type, unsigned long long>(std::numeric_limits<type>::lowest())));
        }
        {
            using type = unsigned short;
            umin = std::numeric_limits<type>::lowest();
            EXPECT((umin == int_cast<type, unsigned long long>(std::numeric_limits<type>::lowest())));
        }
        {
            using type = unsigned int;
            umin = std::numeric_limits<type>::lowest();
            EXPECT((umin == int_cast<type, unsigned long long>(std::numeric_limits<type>::lowest())));
        }
        {
            using type = unsigned long;
            umin = std::numeric_limits<type>::lowest();
            EXPECT((umin == int_cast<type, unsigned long long>(std::numeric_limits<type>::lowest())));
        }
        {
            using type = unsigned long long;
            umin = std::numeric_limits<type>::lowest();
            EXPECT((umin == int_cast<type, unsigned long long>(std::numeric_limits<type>::lowest())));
        }
    },

    CASE("several use cases int_cast() successes to cast")
    {
        using ken3::int_cast;

        {
            signed char from = 12;
            int to = 12;
            EXPECT((to == int_cast<decltype(from), decltype(to)>(from)));
        }
        {
            int from = 12;
            signed char to = 12;
            EXPECT((to == int_cast<decltype(from), decltype(to)>(from)));
        }
        {
            short from = -250;
            int to = -250;
            EXPECT((to == int_cast<decltype(from), decltype(to)>(from)));
        }
        {
            int from = -250;
            short to = -250;
            EXPECT((to == int_cast<decltype(from), decltype(to)>(from)));
        }
        {
            unsigned char from = 12;
            int to = 12;
            EXPECT((to == int_cast<decltype(from), decltype(to)>(from)));
        }
        {
            int from = 12;
            unsigned char to = 12;
            EXPECT((to == int_cast<decltype(from), decltype(to)>(from)));
        }
        {
            long long from = 1800000000;
            unsigned long long to = 1800000000;
            EXPECT((to == int_cast<decltype(from), decltype(to)>(from)));
        }
    },

    CASE("several use cases int_cast() throws std::out_of_range")
    {
        using ken3::int_cast;

        {
            int from = 300;
            signed char to;
            EXPECT_THROWS_AS((int_cast<decltype(from), decltype(to)>(from)), std::out_of_range);
        }
        {
            int from = 1800000000;
            short to;
            EXPECT_THROWS_AS((int_cast<decltype(from), decltype(to)>(from)), std::out_of_range);
        }
        {
            signed char from = -1;
            unsigned long long to;
            EXPECT_THROWS_AS((int_cast<decltype(from), decltype(to)>(from)), std::out_of_range);
        }
        {
            signed char from = -127;
            unsigned long long to;
            EXPECT_THROWS_AS((int_cast<decltype(from), decltype(to)>(from)), std::out_of_range);
        }
        {
            short from = -1;
            unsigned short to;
            EXPECT_THROWS_AS((int_cast<decltype(from), decltype(to)>(from)), std::out_of_range);
        }
    },

};

extern lest::tests& specification();

MODULE(specification(), module)

