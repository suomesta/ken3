/**
 * @file    unittest/biconv_test.cpp
 * @brief   Testing ken3::biconv using lest. 
 * @author  toda
 * @date    2021-08-28
 * @version 0.1.0
 * @remark  the target is C++11 or more
 */

#include "ken3/biconv.hpp"
#include "unittest/lest.hpp"

const lest::test specification[] =
{

    CASE("minimum function")
    {
        ken3::biconv<char, int> bc{{'A', 10}, {'B', 11}, {'C', 12}};

        EXPECT(10 == bc.convert('A'));
        EXPECT('C' == bc.rconvert(12));
    },

    CASE("convert() with one argument")
    {
        ken3::biconv<char, int> bc{{'A', 10}, {'B', 11}, {'C', 12}};

        EXPECT(10 == bc.convert('A'));
        EXPECT(11 == bc.convert('B'));
        EXPECT(12 == bc.convert('C'));
        EXPECT_THROWS_AS(bc.convert('D'), std::out_of_range);
    },

    CASE("convert() with two arguments")
    {
        ken3::biconv<char, int> bc{{'A', 10}, {'B', 11}, {'C', 12}};

        EXPECT(10 == bc.convert('A', 0));
        EXPECT(11 == bc.convert('B', 0));
        EXPECT(12 == bc.convert('C', 0));
        EXPECT(0 == bc.convert('D', 0));
    },

    CASE("rconvert() with one argument")
    {
        ken3::biconv<char, int> bc{{'A', 10}, {'B', 11}, {'C', 12}};

        EXPECT('A' == bc.rconvert(10));
        EXPECT('B' == bc.rconvert(11));
        EXPECT('C' == bc.rconvert(12));
        EXPECT_THROWS_AS(bc.rconvert(13), std::out_of_range);
    },

    CASE("rconvert() with two arguments")
    {
        ken3::biconv<char, int> bc{{'A', 10}, {'B', 11}, {'C', 12}};

        EXPECT('A' == bc.rconvert(10, '\0'));
        EXPECT('B' == bc.rconvert(11, '\0'));
        EXPECT('C' == bc.rconvert(12, '\0'));
        EXPECT('\0' == bc.rconvert(13, '\0'));
    },

    CASE("containF()")
    {
        ken3::biconv<char, int> bc{{'A', 10}, {'B', 11}, {'C', 12}};

        EXPECT(true == bc.containF('A'));
        EXPECT(true == bc.containF('B'));
        EXPECT(true == bc.containF('C'));
        EXPECT(false == bc.containF('D'));
    },

    CASE("containS()")
    {
        ken3::biconv<char, int> bc{{'A', 10}, {'B', 11}, {'C', 12}};

        EXPECT(true == bc.containS(10));
        EXPECT(true == bc.containS(11));
        EXPECT(true == bc.containS(12));
        EXPECT(false == bc.containS(13));
    },

    CASE("empty")
    {
        ken3::biconv<char, int> bc{};

        EXPECT(false == bc.containF('A'));
        EXPECT(false == bc.containS(10));
    },

};

int main(int argc, char* argv[])
{
    return lest::run(specification, argc, argv);
}
/////////////////////////////////////////////////////////////////////////////

