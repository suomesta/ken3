/**
 * @file    unittest/scope_exit_test.cpp
 * @brief   Testing ken3::stopwatch using lest. 
 * @author  toda
 * @date    2018-01-26
 * @version 0.1.0
 * @remark  the target is C++11 or more
 */

#include "ken3/scope_exit.hpp"
#include "unittest/lest.hpp"

const lest::test specification[] =
{

    CASE("typical usage")
    {
        using ken3::scope_exit;

        int i = 0;
        {
            EXPECT(0 == i);
            scope_exit se(
                [&i]() { i++; }
            );
            EXPECT(0 == i);
        }
        EXPECT(1 == i);
    },

    CASE("two scope_exit")
    {
        using ken3::scope_exit;

        int i = 5;
        {
            EXPECT(5 == i);
            scope_exit se1(
                [&i]() { i++; }
            );
            EXPECT(5 == i);
            scope_exit se2(
                [&i]() { i *= 0; }
            );
            EXPECT(5 == i);
        } // calls ~se2() and ~se1() in turn
        EXPECT(1 == i);
    },

    CASE("confirm empty function")
    {
        using ken3::scope_exit;

        {
            scope_exit se({});
        }
        EXPECT(true);
    },

    CASE("confirm nullptr std::function")
    {
        using ken3::scope_exit;

        {
            scope_exit se(nullptr);
        }
        EXPECT(true);
    },

};

int main(int argc, char* argv[])
{
    return lest::run(specification, argc, argv);
}
/////////////////////////////////////////////////////////////////////////////

