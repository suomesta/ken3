/**
 * @file    unittest/counter_test.cpp
 * @brief   Testing ken3::counter using lest. 
 * @author  toda
 * @date    2018-04-01
 * @version 0.1.0
 * @remark  the target is C++11 or more
 */

#include "ken3/counter.hpp"
#include "unittest/lest.hpp"

const lest::test specification[] =
{

    CASE("test default constructor")
    {
        {
            using counter = ken3::counter<3>;

            counter c;

            EXPECT(0 == c());
        }
        {
            using counter = ken3::counter<3, 1>;

            counter c;

            EXPECT(1 == c());
        }
    },

    CASE("test constructor with one argument")
    {
        {
            using counter = ken3::counter<3>;

            counter c[5] = {counter{0}, counter{1}, counter{2}, counter{3}, counter{4}};

            EXPECT(0 == c[0]());
            EXPECT(1 == c[1]());
            EXPECT(2 == c[2]());
            EXPECT(3 == c[3]());
            EXPECT(3 == c[4]());
        }
        {
            using counter = ken3::counter<3, 1>;

            counter c[5] = {counter{0}, counter{1}, counter{2}, counter{3}, counter{4}};

            EXPECT(1 == c[0]());
            EXPECT(1 == c[1]());
            EXPECT(2 == c[2]());
            EXPECT(3 == c[3]());
            EXPECT(3 == c[4]());
        }
    },

    CASE("test pre-increment operator")
    {
        {
            using counter = ken3::counter<3>;

            counter c;

            EXPECT(1 == (++c)());
            EXPECT(2 == (++c)());
            EXPECT(3 == (++c)());
            EXPECT(3 == (++c)());
        }
        {
            using counter = ken3::counter<3, 1>;

            counter c;

            EXPECT(2 == (++c)());
            EXPECT(3 == (++c)());
            EXPECT(3 == (++c)());
        }
    },

    CASE("test post-increment operator")
    {
        {
            using counter = ken3::counter<3>;

            counter c;

            EXPECT(0 == (c++)());
            EXPECT(1 == (c++)());
            EXPECT(2 == (c++)());
            EXPECT(3 == (c++)());
            EXPECT(3 == (c++)());
        }
        {
            using counter = ken3::counter<3, 1>;

            counter c;

            EXPECT(1 == (c++)());
            EXPECT(2 == (c++)());
            EXPECT(3 == (c++)());
            EXPECT(3 == (c++)());
        }
    },

    CASE("test pre-decrement operator")
    {
        {
            using counter = ken3::counter<3>;

            counter c{3};

            EXPECT(2 == (--c)());
            EXPECT(1 == (--c)());
            EXPECT(0 == (--c)());
            EXPECT(0 == (--c)());
        }
        {
            using counter = ken3::counter<3, 1>;

            counter c{3};

            EXPECT(2 == (--c)());
            EXPECT(1 == (--c)());
            EXPECT(1 == (--c)());
        }
    },

    CASE("test post-decrement operator")
    {
        {
            using counter = ken3::counter<3>;

            counter c{3};

            EXPECT(3 == (c--)());
            EXPECT(2 == (c--)());
            EXPECT(1 == (c--)());
            EXPECT(0 == (c--)());
            EXPECT(0 == (c--)());
        }
        {
            using counter = ken3::counter<3, 1>;

            counter c{3};

            EXPECT(3 == (c--)());
            EXPECT(2 == (c--)());
            EXPECT(1 == (c--)());
            EXPECT(1 == (c--)());
        }
    },

    CASE("test reset()")
    {
        {
            using counter = ken3::counter<3>;

            counter c[5] = {counter{0}, counter{1}, counter{2}, counter{3}, counter{4}};

            for (auto& i: c) {
                i.reset();
            }

            EXPECT(0 == c[0]());
            EXPECT(0 == c[1]());
            EXPECT(0 == c[2]());
            EXPECT(0 == c[3]());
            EXPECT(0 == c[4]());
        }
        {
            using counter = ken3::counter<3, 1>;

            counter c[5] = {counter{0}, counter{1}, counter{2}, counter{3}, counter{4}};

            for (auto& i: c) {
                i.reset();
            }

            EXPECT(1 == c[0]());
            EXPECT(1 == c[1]());
            EXPECT(1 == c[2]());
            EXPECT(1 == c[3]());
            EXPECT(1 == c[4]());
        }
    },

    CASE("test advance()")
    {
        {
            using counter = ken3::counter<6>;

            counter c[5] = {counter{0}, counter{1}, counter{2}, counter{3}, counter{4}};

            for (auto& i: c) {
                i.advance(3);
            }

            EXPECT(3 == c[0]());
            EXPECT(4 == c[1]());
            EXPECT(5 == c[2]());
            EXPECT(6 == c[3]());
            EXPECT(6 == c[4]());
        }
        {
            using counter = ken3::counter<6, 1>;

            counter c[5] = {counter{0}, counter{1}, counter{2}, counter{3}, counter{4}};

            for (auto& i: c) {
                i.advance(3);
            }

            EXPECT(4 == c[0]());
            EXPECT(4 == c[1]());
            EXPECT(5 == c[2]());
            EXPECT(6 == c[3]());
            EXPECT(6 == c[4]());
        }
    },

    CASE("test retreat()")
    {
        {
            using counter = ken3::counter<6>;

            counter c[5] = {counter{2}, counter{3}, counter{4}, counter{5}, counter{6}};

            for (auto& i: c) {
                i.retreat(3);
            }

            EXPECT(0 == c[0]());
            EXPECT(0 == c[1]());
            EXPECT(1 == c[2]());
            EXPECT(2 == c[3]());
            EXPECT(3 == c[4]());
        }
        {
            using counter = ken3::counter<6, 1>;

            counter c[5] = {counter{2}, counter{3}, counter{4}, counter{5}, counter{6}};

            for (auto& i: c) {
                i.retreat(3);
            }

            EXPECT(1 == c[0]());
            EXPECT(1 == c[1]());
            EXPECT(1 == c[2]());
            EXPECT(2 == c[3]());
            EXPECT(3 == c[4]());
        }
    },

    CASE("test minimum()")
    {
        {
            using counter = ken3::counter<3>;

            EXPECT(0 == counter{}.minimum());
        }
        {
            using counter = ken3::counter<3, 1>;

            EXPECT(1 == counter{}.minimum());
        }
    },

    CASE("test maximum()")
    {
        {
            using counter = ken3::counter<3>;

            EXPECT(3 == counter{}.maximum());
        }
        {
            using counter = ken3::counter<6, 1>;

            EXPECT(6 == counter{}.maximum());
        }
    },

    CASE("test is_minimum()")
    {
        {
            using counter = ken3::counter<3>;

            counter c{3};

            EXPECT(false == (--c).is_minimum());
            EXPECT(false == (--c).is_minimum());
            EXPECT(true == (--c).is_minimum());
            EXPECT(true == (--c).is_minimum());
        }
        {
            using counter = ken3::counter<3, 1>;

            counter c{3};

            EXPECT(false == (--c).is_minimum());
            EXPECT(true == (--c).is_minimum());
            EXPECT(true == (--c).is_minimum());
        }
    },

    CASE("test is_maximum()")
    {
        {
            using counter = ken3::counter<3>;

            counter c;

            EXPECT(false == (++c).is_maximum());
            EXPECT(false == (++c).is_maximum());
            EXPECT(true == (++c).is_maximum());
            EXPECT(true == (++c).is_maximum());
        }
        {
            using counter = ken3::counter<3, 1>;

            counter c;

            EXPECT(false == (++c).is_maximum());
            EXPECT(true == (++c).is_maximum());
            EXPECT(true == (++c).is_maximum());
        }
    },

};

int main(int argc, char* argv[])
{
    return lest::run(specification, argc, argv);
}
/////////////////////////////////////////////////////////////////////////////

