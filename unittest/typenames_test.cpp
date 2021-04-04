/**
 * @file    unittest/typenames_test.cpp
 * @brief   Testing ken3::typenames using lest. 
 * @author  toda
 * @date    2021-04-04
 * @version 0.1.0
 * @remark  the target is C++11 or more
 */

#include <cstdint>
#include "ken3/typenames.hpp"
#include "unittest/lest.hpp"

const lest::test specification[] =
{

    CASE("tests of pre-registerred types")
    {
        ken3::typenames tn;

        EXPECT("bool" == tn.str_of<bool>());
        EXPECT("char" == tn.str_of<char>());
        EXPECT("signed char" == tn.str_of<signed char>());
        EXPECT("unsigned char" == tn.str_of<unsigned char>());
        EXPECT("short" == tn.str_of<short>());
        EXPECT("unsigned short" == tn.str_of<unsigned short>());
        EXPECT("int" == tn.str_of<int>());
        EXPECT("unsigned int" == tn.str_of<unsigned int>());
        EXPECT("long" == tn.str_of<long>());
        EXPECT("unsigned long" == tn.str_of<unsigned long>());
        EXPECT("long long" == tn.str_of<long long>());
        EXPECT("unsigned long long" == tn.str_of<unsigned long long>());
        EXPECT("float" == tn.str_of<float>());
        EXPECT("double" == tn.str_of<double>());
        EXPECT("long double" == tn.str_of<long double>());
        EXPECT("char16_t" == tn.str_of<char16_t>());
        EXPECT("char32_t" == tn.str_of<char32_t>());
        EXPECT("wchar_t" == tn.str_of<wchar_t>());
        EXPECT("std::nullptr_t" == tn.str_of<std::nullptr_t>());
    },

    CASE("test registering new type")
    {
        ken3::typenames tn;

        tn.register_str<std::type_index>("std::type_index");
        tn.register_str<std::string>("std::string");
        tn.register_str<typename std::unordered_map<std::type_index, std::string>::const_iterator>("std::unordered_map<std::type_index, std::string>::const_iterator");

        EXPECT("std::type_index" == tn.str_of<std::type_index>());
        EXPECT("std::string" == tn.str_of<std::string>());
        EXPECT(("std::unordered_map<std::type_index, std::string>::const_iterator" == tn.str_of<typename std::unordered_map<std::type_index, std::string>::const_iterator>()));
    },

    CASE("test throwing out_of_range")
    {
        ken3::typenames tn;

        EXPECT_THROWS_AS(tn.str_of<std::string>(), std::out_of_range);

        tn.register_str<std::string>("std::string");

        EXPECT("std::string" == tn.str_of<std::string>());
    },

    CASE("test overwriting name")
    {
        ken3::typenames tn;

        EXPECT("short" == tn.str_of<short>());

        tn.register_str<short>("int16_t");
        EXPECT("int16_t" == tn.str_of<short>());

        tn.register_str<std::string>("std::string");
        EXPECT("std::string" == tn.str_of<std::string>());

        tn.register_str<std::string>("string");
        EXPECT("string" == tn.str_of<std::string>());
    },

    CASE("test copy_map()")
    {
        ken3::typenames tn;

        auto m1 = tn.copy_map();
        EXPECT(19 == m1.size());

        tn.register_str<std::string>("std::string");
        auto m2 = tn.copy_map();
        EXPECT(20 == m2.size());

        tn.register_str<short>("int16_t");
        auto m3 = tn.copy_map();
        EXPECT(20 == m3.size());
    },

};

int main(int argc, char* argv[])
{
    return lest::run(specification, argc, argv);
}
/////////////////////////////////////////////////////////////////////////////

