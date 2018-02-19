/**
 * @file    unittest/cast/string_to_test.cpp
 * @brief   Testing ken3::string_to() using lest.
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

    CASE("string_to() accepts any arithmetic type (except bool)")
    {
        using ken3::string_to;

        EXPECT((0 == string_to<signed char>("0")));
        EXPECT((0 == string_to<unsigned char>("0")));
        EXPECT((0 == string_to<short>("0")));
        EXPECT((0 == string_to<unsigned short>("0")));
        EXPECT((0 == string_to<int>("0")));
        EXPECT((0 == string_to<unsigned int>("0")));
        EXPECT((0 == string_to<long>("0")));
        EXPECT((0 == string_to<unsigned long>("0")));
        EXPECT((0 == string_to<long long>("0")));
        EXPECT((0 == string_to<unsigned long long>("0")));
        EXPECT((0 == string_to<char>("0")));
        EXPECT((0 == string_to<wchar_t>("0")));
        EXPECT((0 == string_to<char16_t>("0")));
        EXPECT((0 == string_to<char32_t>("0")));
        EXPECT((0 == string_to<float>("0")));
        EXPECT((0 == string_to<double>("0")));
        EXPECT((0 == string_to<long double>("0")));

        EXPECT((1 == string_to<signed char>("1")));
        EXPECT((1 == string_to<unsigned char>("1")));
        EXPECT((1 == string_to<short>("1")));
        EXPECT((1 == string_to<unsigned short>("1")));
        EXPECT((1 == string_to<int>("1")));
        EXPECT((1 == string_to<unsigned int>("1")));
        EXPECT((1 == string_to<long>("1")));
        EXPECT((1 == string_to<unsigned long>("1")));
        EXPECT((1 == string_to<long long>("1")));
        EXPECT((1 == string_to<unsigned long long>("1")));
        EXPECT((1 == string_to<char>("1")));
        EXPECT((1 == string_to<wchar_t>("1")));
        EXPECT((1 == string_to<char16_t>("1")));
        EXPECT((1 == string_to<char32_t>("1")));
        EXPECT((1 == string_to<float>("1")));
        EXPECT((1 == string_to<double>("1")));
        EXPECT((1 == string_to<long double>("1")));
    },

    CASE("test string_to() with \"-1\"")
    {
        using ken3::string_to;

        EXPECT((-1 == string_to<signed char>("-1")));
        EXPECT((-1 == string_to<short>("-1")));
        EXPECT((-1 == string_to<int>("-1")));
        EXPECT((-1 == string_to<long>("-1")));
        EXPECT((-1 == string_to<long long>("-1")));
        EXPECT_THROWS_AS((string_to<unsigned char>("-1")), std::out_of_range);
        EXPECT_THROWS_AS((string_to<unsigned short>("-1")), std::out_of_range);
        EXPECT_THROWS_AS((string_to<unsigned int>("-1")), std::out_of_range);
        EXPECT_THROWS_AS((string_to<unsigned long>("-1")), std::out_of_range);
        EXPECT_THROWS_AS((string_to<unsigned long long>("-1")), std::out_of_range);
        EXPECT((-1 == string_to<float>("-1")));
        EXPECT((-1 == string_to<double>("-1")));
        EXPECT((-1 == string_to<long double>("-1")));
    },

    CASE("test string_to() throws std::invalid_argument")
    {
        using ken3::string_to;

        EXPECT_THROWS_AS((string_to<signed char>("")), std::invalid_argument);
        EXPECT_THROWS_AS((string_to<unsigned char>("")), std::invalid_argument);
        EXPECT_THROWS_AS((string_to<short>("")), std::invalid_argument);
        EXPECT_THROWS_AS((string_to<unsigned short>("")), std::invalid_argument);
        EXPECT_THROWS_AS((string_to<int>("")), std::invalid_argument);
        EXPECT_THROWS_AS((string_to<unsigned int>("")), std::invalid_argument);
        EXPECT_THROWS_AS((string_to<long>("")), std::invalid_argument);
        EXPECT_THROWS_AS((string_to<unsigned long>("")), std::invalid_argument);
        EXPECT_THROWS_AS((string_to<long long>("")), std::invalid_argument);
        EXPECT_THROWS_AS((string_to<unsigned long long>("")), std::invalid_argument);
        EXPECT_THROWS_AS((string_to<char>("")), std::invalid_argument);
        EXPECT_THROWS_AS((string_to<wchar_t>("")), std::invalid_argument);
        EXPECT_THROWS_AS((string_to<char16_t>("")), std::invalid_argument);
        EXPECT_THROWS_AS((string_to<char32_t>("")), std::invalid_argument);
        EXPECT_THROWS_AS((string_to<float>("")), std::invalid_argument);
        EXPECT_THROWS_AS((string_to<double>("")), std::invalid_argument);
        EXPECT_THROWS_AS((string_to<long double>("")), std::invalid_argument);

        EXPECT_THROWS_AS((string_to<signed char>("A")), std::invalid_argument);
        EXPECT_THROWS_AS((string_to<unsigned char>("A")), std::invalid_argument);
        EXPECT_THROWS_AS((string_to<short>("A")), std::invalid_argument);
        EXPECT_THROWS_AS((string_to<unsigned short>("A")), std::invalid_argument);
        EXPECT_THROWS_AS((string_to<int>("A")), std::invalid_argument);
        EXPECT_THROWS_AS((string_to<unsigned int>("A")), std::invalid_argument);
        EXPECT_THROWS_AS((string_to<long>("A")), std::invalid_argument);
        EXPECT_THROWS_AS((string_to<unsigned long>("A")), std::invalid_argument);
        EXPECT_THROWS_AS((string_to<long long>("A")), std::invalid_argument);
        EXPECT_THROWS_AS((string_to<unsigned long long>("A")), std::invalid_argument);
        EXPECT_THROWS_AS((string_to<char>("A")), std::invalid_argument);
        EXPECT_THROWS_AS((string_to<wchar_t>("A")), std::invalid_argument);
        EXPECT_THROWS_AS((string_to<char16_t>("A")), std::invalid_argument);
        EXPECT_THROWS_AS((string_to<char32_t>("A")), std::invalid_argument);
        EXPECT_THROWS_AS((string_to<float>("A")), std::invalid_argument);
        EXPECT_THROWS_AS((string_to<double>("A")), std::invalid_argument);
        EXPECT_THROWS_AS((string_to<long double>("A")), std::invalid_argument);
    },

    CASE("test string_to() throws std::out_of_range")
    {
        using ken3::string_to;

        std::string largest{std::to_string(std::numeric_limits<unsigned long long>::max())};
        largest.push_back('0');
        EXPECT_THROWS_AS((string_to<signed char>(largest)), std::out_of_range);
        EXPECT_THROWS_AS((string_to<unsigned char>(largest)), std::out_of_range);
        EXPECT_THROWS_AS((string_to<short>(largest)), std::out_of_range);
        EXPECT_THROWS_AS((string_to<unsigned short>(largest)), std::out_of_range);
        EXPECT_THROWS_AS((string_to<int>(largest)), std::out_of_range);
        EXPECT_THROWS_AS((string_to<unsigned int>(largest)), std::out_of_range);
        EXPECT_THROWS_AS((string_to<long>(largest)), std::out_of_range);
        EXPECT_THROWS_AS((string_to<unsigned long>(largest)), std::out_of_range);
        EXPECT_THROWS_AS((string_to<long long>(largest)), std::out_of_range);
        EXPECT_THROWS_AS((string_to<unsigned long long>(largest)), std::out_of_range);

        std::string lowest{std::to_string(std::numeric_limits<long long>::lowest())};
        lowest.push_back('0');
        EXPECT_THROWS_AS((string_to<signed char>(lowest)), std::out_of_range);
        EXPECT_THROWS_AS((string_to<unsigned char>(lowest)), std::out_of_range);
        EXPECT_THROWS_AS((string_to<short>(lowest)), std::out_of_range);
        EXPECT_THROWS_AS((string_to<unsigned short>(lowest)), std::out_of_range);
        EXPECT_THROWS_AS((string_to<int>(lowest)), std::out_of_range);
        EXPECT_THROWS_AS((string_to<unsigned int>(lowest)), std::out_of_range);
        EXPECT_THROWS_AS((string_to<long>(lowest)), std::out_of_range);
        EXPECT_THROWS_AS((string_to<unsigned long>(lowest)), std::out_of_range);
        EXPECT_THROWS_AS((string_to<long long>(lowest)), std::out_of_range);
        EXPECT_THROWS_AS((string_to<unsigned long long>(lowest)), std::out_of_range);
    },

    CASE("test 2nd argument of string_to()")
    {
        using ken3::string_to;

        size_t pos;
        EXPECT((12 == string_to<signed char>("12", &pos)));
        EXPECT((2 == pos));
        EXPECT((12 == string_to<unsigned char>("12", &pos)));
        EXPECT((2 == pos));
        EXPECT((123 == string_to<short>("123", &pos)));
        EXPECT((3 == pos));
        EXPECT((123 == string_to<unsigned short>("123", &pos)));
        EXPECT((3 == pos));
        EXPECT((1234 == string_to<int>("1234", &pos)));
        EXPECT((4 == pos));
        EXPECT((1234 == string_to<unsigned int>("1234", &pos)));
        EXPECT((4 == pos));
        EXPECT((12345 == string_to<long>("12345", &pos)));
        EXPECT((5 == pos));
        EXPECT((12345 == string_to<unsigned long>("12345", &pos)));
        EXPECT((5 == pos));
        EXPECT((123456 == string_to<long long>("123456", &pos)));
        EXPECT((6 == pos));
        EXPECT((123456 == string_to<unsigned long long>("123456", &pos)));
        EXPECT((6 == pos));
        EXPECT((12 == string_to<char>("12", &pos)));
        EXPECT((2 == pos));
        EXPECT((123 == string_to<wchar_t>("123", &pos)));
        EXPECT((3 == pos));
        EXPECT((123 == string_to<char16_t>("123", &pos)));
        EXPECT((3 == pos));
        EXPECT((1234 == string_to<char32_t>("1234", &pos)));
        EXPECT((4 == pos));
        EXPECT((12 == string_to<float>("12", &pos)));
        EXPECT((2 == pos));
        EXPECT((123 == string_to<double>("123", &pos)));
        EXPECT((3 == pos));
        EXPECT((1234 == string_to<long double>("1234", &pos)));
        EXPECT((4 == pos));

        EXPECT((12 == string_to<signed char>("12a", &pos)));
        EXPECT((2 == pos));
        EXPECT((12 == string_to<unsigned char>("12a", &pos)));
        EXPECT((2 == pos));
        EXPECT((123 == string_to<short>("123a", &pos)));
        EXPECT((3 == pos));
        EXPECT((123 == string_to<unsigned short>("123a", &pos)));
        EXPECT((3 == pos));
        EXPECT((1234 == string_to<int>("1234a", &pos)));
        EXPECT((4 == pos));
        EXPECT((1234 == string_to<unsigned int>("1234a", &pos)));
        EXPECT((4 == pos));
        EXPECT((12345 == string_to<long>("12345a", &pos)));
        EXPECT((5 == pos));
        EXPECT((12345 == string_to<unsigned long>("12345a", &pos)));
        EXPECT((5 == pos));
        EXPECT((123456 == string_to<long long>("123456a", &pos)));
        EXPECT((6 == pos));
        EXPECT((123456 == string_to<unsigned long long>("123456a", &pos)));
        EXPECT((6 == pos));
        EXPECT((12 == string_to<char>("12a", &pos)));
        EXPECT((2 == pos));
        EXPECT((123 == string_to<wchar_t>("123a", &pos)));
        EXPECT((3 == pos));
        EXPECT((123 == string_to<char16_t>("123a", &pos)));
        EXPECT((3 == pos));
        EXPECT((1234 == string_to<char32_t>("1234a", &pos)));
        EXPECT((4 == pos));
        EXPECT((12 == string_to<float>("12a", &pos)));
        EXPECT((2 == pos));
        EXPECT((123 == string_to<double>("123a", &pos)));
        EXPECT((3 == pos));
        EXPECT((1234 == string_to<long double>("1234a", &pos)));
        EXPECT((4 == pos));

        EXPECT((12 == string_to<signed char>("12a1b", &pos)));
        EXPECT((2 == pos));
        EXPECT((12 == string_to<unsigned char>("12a1b", &pos)));
        EXPECT((2 == pos));
        EXPECT((123 == string_to<short>("123a1b", &pos)));
        EXPECT((3 == pos));
        EXPECT((123 == string_to<unsigned short>("123a1b", &pos)));
        EXPECT((3 == pos));
        EXPECT((1234 == string_to<int>("1234a1b", &pos)));
        EXPECT((4 == pos));
        EXPECT((1234 == string_to<unsigned int>("1234a1b", &pos)));
        EXPECT((4 == pos));
        EXPECT((12345 == string_to<long>("12345a1b", &pos)));
        EXPECT((5 == pos));
        EXPECT((12345 == string_to<unsigned long>("12345a1b", &pos)));
        EXPECT((5 == pos));
        EXPECT((123456 == string_to<long long>("123456a1b", &pos)));
        EXPECT((6 == pos));
        EXPECT((123456 == string_to<unsigned long long>("123456a1b", &pos)));
        EXPECT((6 == pos));
        EXPECT((12 == string_to<char>("12a1b", &pos)));
        EXPECT((2 == pos));
        EXPECT((123 == string_to<wchar_t>("123a1b", &pos)));
        EXPECT((3 == pos));
        EXPECT((123 == string_to<char16_t>("123a1b", &pos)));
        EXPECT((3 == pos));
        EXPECT((1234 == string_to<char32_t>("1234a1b", &pos)));
        EXPECT((4 == pos));
        EXPECT((12 == string_to<float>("12a1b", &pos)));
        EXPECT((2 == pos));
        EXPECT((123 == string_to<double>("123a1b", &pos)));
        EXPECT((3 == pos));
        EXPECT((1234 == string_to<long double>("1234a1b", &pos)));
        EXPECT((4 == pos));
    },

    CASE("test 3rd argument of string_to()")
    {
        using ken3::string_to;

        EXPECT((18 == string_to<signed char>("12", nullptr, 16)));
        EXPECT((18 == string_to<unsigned char>("12", nullptr, 16)));
        EXPECT((18 == string_to<short>("12", nullptr, 16)));
        EXPECT((18 == string_to<unsigned short>("12", nullptr, 16)));
        EXPECT((18 == string_to<int>("12", nullptr, 16)));
        EXPECT((18 == string_to<unsigned int>("12", nullptr, 16)));
        EXPECT((18 == string_to<long>("12", nullptr, 16)));
        EXPECT((18 == string_to<unsigned long>("12", nullptr, 16)));
        EXPECT((18 == string_to<long long>("12", nullptr, 16)));
        EXPECT((18 == string_to<unsigned long long>("12", nullptr, 16)));
        EXPECT((18 == string_to<char>("12", nullptr, 16)));
        EXPECT((18 == string_to<wchar_t>("12", nullptr, 16)));
        EXPECT((18 == string_to<char16_t>("12", nullptr, 16)));
        EXPECT((18 == string_to<char32_t>("12", nullptr, 16)));
        EXPECT((12 == string_to<float>("12", nullptr, 16)));
        EXPECT((12 == string_to<double>("12", nullptr, 16)));
        EXPECT((12 == string_to<long double>("12", nullptr, 16)));

        EXPECT((26 == string_to<signed char>("1A", nullptr, 16)));
        EXPECT((26 == string_to<unsigned char>("1A", nullptr, 16)));
        EXPECT((26 == string_to<short>("1A", nullptr, 16)));
        EXPECT((26 == string_to<unsigned short>("1A", nullptr, 16)));
        EXPECT((26 == string_to<int>("1A", nullptr, 16)));
        EXPECT((26 == string_to<unsigned int>("1A", nullptr, 16)));
        EXPECT((26 == string_to<long>("1A", nullptr, 16)));
        EXPECT((26 == string_to<unsigned long>("1A", nullptr, 16)));
        EXPECT((26 == string_to<long long>("1A", nullptr, 16)));
        EXPECT((26 == string_to<unsigned long long>("1A", nullptr, 16)));
        EXPECT((26 == string_to<char>("1A", nullptr, 16)));
        EXPECT((26 == string_to<wchar_t>("1A", nullptr, 16)));
        EXPECT((26 == string_to<char16_t>("1A", nullptr, 16)));
        EXPECT((26 == string_to<char32_t>("1A", nullptr, 16)));
        EXPECT((1 == string_to<float>("1A", nullptr, 16)));
        EXPECT((1 == string_to<double>("1A", nullptr, 16)));
        EXPECT((1 == string_to<long double>("1A", nullptr, 16)));
    },

    CASE("test several use cases string_to() fails")
    {
        using ken3::string_to;

        EXPECT((127 == string_to<signed char>("127")));
        EXPECT((1 == string_to<signed char>("1 27")));

        EXPECT((1 == string_to<int>("1.75")));
        EXPECT((1.75 == string_to<float>("1.75")));
        EXPECT((-1 == string_to<int>("-1.75")));
        EXPECT((-1.75 == string_to<float>("-1.75")));

        EXPECT((73 == string_to<int>("111", 0, 8)));

        EXPECT((0 == string_to<unsigned int>("+0")));
        EXPECT((0 == string_to<unsigned int>("0")));
        EXPECT((0 == string_to<unsigned int>("-0")));

        EXPECT((255 == string_to<unsigned char>("ff", 0, 16)));
        EXPECT((255 == string_to<unsigned char>("FF", 0, 16)));

        EXPECT((1 == string_to<unsigned long>("1 -")));
        EXPECT((1 == string_to<unsigned long>("1-")));
    },

    CASE("test several use cases string_to() works out")
    {
        using ken3::string_to;

        EXPECT_THROWS_AS((string_to<char>("128")), std::out_of_range);
        EXPECT_THROWS_AS((string_to<unsigned char>("-128")), std::out_of_range);
        EXPECT_THROWS_AS((string_to<unsigned char>("256")), std::out_of_range);

        EXPECT_THROWS_AS((string_to<unsigned char>("-1")), std::out_of_range);
        EXPECT_THROWS_AS((string_to<unsigned short>("-1")), std::out_of_range);
        EXPECT_THROWS_AS((string_to<unsigned int>("-1")), std::out_of_range);
        EXPECT_THROWS_AS((string_to<unsigned long>("-1")), std::out_of_range);
        EXPECT_THROWS_AS((string_to<unsigned long long>("-1")), std::out_of_range);

        EXPECT_THROWS_AS((string_to<float>("FF", 0, 16)), std::invalid_argument);
        EXPECT_THROWS_AS((string_to<double>("FF", 0, 16)), std::invalid_argument);
        EXPECT_THROWS_AS((string_to<long double>("FF", 0, 16)), std::invalid_argument);
    },

};

extern lest::tests& specification();

MODULE(specification(), module)

