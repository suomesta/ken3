/**
 * @file    unittest/overflow_test.cpp
 * @brief   Testing ken3::overflow using lest. 
 * @author  toda
 * @date    2019-12-30
 * @version 0.1.0
 * @remark  the target is C++11 or more
 */

#include <cstdint>
#include "ken3/overflow.hpp"
#include "unittest/lest.hpp"

const lest::test specification[] =
{

    CASE("tests for int8_t")
    {
        using namespace ken3::overflow;
        int8_t a, b;

        a = 1;
        b = 64;
        EXPECT(false == occur_add(a, b));
        EXPECT(false == occur_sub(a, b));
        EXPECT(false == occur_mul(a, b));
        EXPECT(false == occur_div(a, b));
        EXPECT(false == occur_abs(a));
        EXPECT(false == occur_abs(b));

        a = 64;
        b = 64;
        EXPECT(true == occur_add(a, b));
        EXPECT(false == occur_sub(a, b));
        EXPECT(true == occur_mul(a, b));
        EXPECT(false == occur_div(a, b));
        EXPECT(false == occur_abs(a));
        EXPECT(false == occur_abs(b));

        a = -100;
        b = 64;
        EXPECT(false == occur_add(a, b));
        EXPECT(true == occur_sub(a, b));
        EXPECT(true == occur_mul(a, b));
        EXPECT(false == occur_div(a, b));
        EXPECT(false == occur_abs(a));
        EXPECT(false == occur_abs(b));

        a = -128;
        b = -1;
        EXPECT(true == occur_add(a, b));
        EXPECT(false == occur_sub(a, b));
        EXPECT(true == occur_mul(a, b));
        EXPECT(true == occur_div(a, b));
        EXPECT(true == occur_abs(a));
        EXPECT(false == occur_abs(b));

        a = 0;
        b = 0;
        EXPECT(false == occur_add(a, b));
        EXPECT(false == occur_sub(a, b));
        EXPECT(false == occur_mul(a, b));
        EXPECT(false == occur_div(a, b));
        EXPECT(false == occur_abs(a));
        EXPECT(false == occur_abs(b));
    },

    CASE("tests for uint8_t")
    {
        using namespace ken3::overflow;
        int8_t a, b;

        a = 64;
        b = 1;
        EXPECT(false == occur_add(a, b));
        EXPECT(false == occur_sub(a, b));
        EXPECT(false == occur_mul(a, b));
        EXPECT(false == occur_div(a, b));
        EXPECT(false == occur_abs(a));
        EXPECT(false == occur_abs(b));

        a = 150;
        b = 150;
        EXPECT(true == occur_add(a, b));
        EXPECT(false == occur_sub(a, b));
        EXPECT(true == occur_mul(a, b));
        EXPECT(false == occur_div(a, b));
        EXPECT(false == occur_abs(a));
        EXPECT(false == occur_abs(b));

        a = 100;
        b = 200;
        EXPECT(true) == occur_add(a, b));
        EXPECT(true == occur_sub(a, b));
        EXPECT(true == occur_mul(a, b));
        EXPECT(false == occur_div(a, b));
        EXPECT(false == occur_abs(a));
        EXPECT(false == occur_abs(b));

        a = 0;
        b = 0;
        EXPECT(false == occur_add(a, b));
        EXPECT(false == occur_sub(a, b));
        EXPECT(false == occur_mul(a, b));
        EXPECT(false == occur_div(a, b));
        EXPECT(false == occur_abs(a));
        EXPECT(false == occur_abs(b));
    },

};

int main(int argc, char* argv[])
{
    return lest::run(specification, argc, argv);
}
/////////////////////////////////////////////////////////////////////////////

