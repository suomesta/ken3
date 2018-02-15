/**
 * @file    type_util/e2i_test.cpp
 * @brief   Testing e2i() using lest. 
 * @author  toda
 * @date    2017-07-21
 * @version 0.1.0
 * @remark  the target is C++11 or more
 */

#include "ken3/type_util.hpp"
#include "unittest/lest.hpp"

const lest::test module[] =
{

    CASE("e2i() with enum class no specified base type") 
    {
        using ken3::e2i;

        enum class ec {
            e1 = 1,
            e2,
            e3 = -1,
        };
        EXPECT((std::is_same<int, decltype(e2i(ec::e1))>::value));
        EXPECT(1 == e2i(ec::e1));
        EXPECT((std::is_same<int, decltype(e2i(ec::e2))>::value));
        EXPECT(2 == e2i(ec::e2));
        EXPECT((std::is_same<int, decltype(e2i(ec::e3))>::value));
        EXPECT(-1 == e2i(ec::e3));
    },

    CASE("e2i() with enum class specified base type") 
    {
        using ken3::e2i;

        enum class ec : short {
            e1 = 1,
            e2,
            e3 = -1,
        };
        EXPECT((std::is_same<short, decltype(e2i(ec::e1))>::value));
        EXPECT(1 == e2i(ec::e1));
        EXPECT((std::is_same<short, decltype(e2i(ec::e2))>::value));
        EXPECT(2 == e2i(ec::e2));
        EXPECT((std::is_same<short, decltype(e2i(ec::e3))>::value));
        EXPECT(-1 == e2i(ec::e3));
    },

    CASE("e2i() with enum specified base type") 
    {
        using ken3::e2i;

        enum ce : unsigned long {
            e1 = 1,
            e2,
            e3 = 0xFFFFFFFFF,
        };
        EXPECT((std::is_same<unsigned long, decltype(e2i(e1))>::value));
        EXPECT(1UL == e2i(e1));
        EXPECT((std::is_same<unsigned long, decltype(e2i(e2))>::value));
        EXPECT(2UL == e2i(e2));
        EXPECT((std::is_same<unsigned long, decltype(e2i(e3))>::value));
        EXPECT(0xFFFFFFFFFUL == e2i(e3));
    },

};

extern lest::tests& specification();

MODULE(specification(), module)

