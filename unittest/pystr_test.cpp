/**
 * @file    pystr_test.cpp
 * @brief   Testing ken3::pystr using lest. 
 * @author  toda
 * @date    2016-06-29
 * @version 0.1.0
 * @remark  the target is C++11 or more
 * @note    This file is created by Python module to get proper required results.
 *          Please, do not modify this file by manual. 
 */

#include "ken3/pystr.hpp"
#include "unittest/lest.hpp"

namespace {

/**
 * @brief      helper function to create std::string, which is {0x00, 0x01, .., 0x0x7F}.
 * @param[in]  size: the size of createdstd::string. default is 128.
 * @return     created std::string.
 */
std::string str7F(size_t size=128)
{
    std::string s(size, '\0');
    for (size_t i = 0; i < size; i++) {
        s[i] = static_cast<char>(i);
    }
    return s;
}
/////////////////////////////////////////////////////////////////////////////

} // namespace {

const lest::test specification[] =
{

    CASE("add()")
    {
        using namespace ken3::pystr;

        EXPECT(std::string("aa") == add("a", "a"));
        EXPECT(std::string("aAaa") == add("aAa", "a"));
        EXPECT(std::string("AAAa") == add("AAA", "a"));
        EXPECT(std::string("a") == add("a", ""));
        EXPECT(std::string("a") == add("", "a"));
        EXPECT(std::string("") == add("", ""));
    },

    CASE("contains()")
    {
        using namespace ken3::pystr;

        EXPECT(true == contains("a", "a"));
        EXPECT(true == contains("aAa", "a"));
        EXPECT(false == contains("AAA", "a"));
        EXPECT(true == contains("a", ""));
        EXPECT(false == contains("", "a"));
        EXPECT(true == contains("", ""));
    },

    CASE("eq()")
    {
        using namespace ken3::pystr;

        EXPECT(true == eq("a", "a"));
        EXPECT(false == eq("A", "a"));
        EXPECT(false == eq("AAA", "a"));
        EXPECT(false == eq("a", ""));
        EXPECT(false == eq("", "a"));
        EXPECT(true == eq("", ""));
    },

    CASE("ge()")
    {
        using namespace ken3::pystr;

        EXPECT(true == ge("a", "a"));
        EXPECT(false == ge("A", "a"));
        EXPECT(true == ge("a", "A"));
        EXPECT(false == ge("AAA", "a"));
        EXPECT(true == ge("a", ""));
        EXPECT(false == ge("", "a"));
        EXPECT(true == ge("", ""));
    },

    CASE("getitem()")
    {
        using namespace ken3::pystr;

        EXPECT(std::string("a") == getitem("abc", 0));
        EXPECT(std::string("b") == getitem("abc", 1));
        EXPECT(std::string("c") == getitem("abc", 2));
        EXPECT(std::string("a") == getitem("abc", -3));
        EXPECT(std::string("b") == getitem("abc", -2));
        EXPECT(std::string("c") == getitem("abc", -1));
        EXPECT_THROWS_AS(getitem("abc", 10), IndexError);
        EXPECT_THROWS_AS(getitem("abc", -10), IndexError);
        EXPECT_THROWS_AS(getitem("", 0), IndexError);
        EXPECT_THROWS_AS(getitem("", -1), IndexError);
    },

    CASE("slice()")
    {
        using namespace ken3::pystr;

        EXPECT(std::string("") == slice("abcdefgh", None, 0));
        EXPECT(std::string("") == slice("abcdefgh", 1, 0));
        EXPECT(std::string("bcdefgh") == slice("abcdefgh", 1, 100));
        EXPECT(std::string("") == slice("abcdefgh", 100, 1));
        EXPECT(std::string("") == slice("abcdefgh", 2, 2));
        EXPECT(std::string("") == slice("abcdefgh", 200, 100));
        EXPECT(std::string("bcdefg") == slice("abcdefgh", 1, -1));
        EXPECT(std::string("abcdefgh") == slice("abcdefgh", -100, 100));
        EXPECT(std::string("") == slice("abcdefgh", 1, -100));
        EXPECT(std::string("abcdefgh") == slice("abcdefgh", 0, None));
        EXPECT(std::string("abcdefgh") == slice("abcdefgh", None, None));
        EXPECT_THROWS_AS(slice("abcdefgh", None, None, 0), ValueError);
        EXPECT(std::string("aceg") == slice("abcdefgh", None, None, 2));
        EXPECT(std::string("") == slice("abcdefgh", 1, 0, 2));
        EXPECT(std::string("bdfh") == slice("abcdefgh", 1, 100, 2));
        EXPECT(std::string("") == slice("abcdefgh", 100, 1, 2));
        EXPECT(std::string("") == slice("abcdefgh", 2, 2, 2));
        EXPECT(std::string("") == slice("abcdefgh", 200, 100, 2));
        EXPECT(std::string("bdf") == slice("abcdefgh", 1, -1, 2));
        EXPECT(std::string("aceg") == slice("abcdefgh", -100, 100, 2));
        EXPECT(std::string("") == slice("abcdefgh", 1, -100, 2));
        EXPECT(std::string("aceg") == slice("abcdefgh", 0, None, 2));
        EXPECT(std::string("hgfedcba") == slice("abcdefgh", None, None, -1));
        EXPECT(std::string("b") == slice("abcdefgh", 1, 0, -1));
        EXPECT(std::string("") == slice("abcdefgh", 1, 100, -1));
        EXPECT(std::string("hgfedc") == slice("abcdefgh", 100, 1, -1));
        EXPECT(std::string("") == slice("abcdefgh", 2, 2, -1));
        EXPECT(std::string("") == slice("abcdefgh", 200, 100, -1));
        EXPECT(std::string("") == slice("abcdefgh", 1, -1, -1));
        EXPECT(std::string("") == slice("abcdefgh", -100, 100, -1));
        EXPECT(std::string("ba") == slice("abcdefgh", 1, -100, -1));
        EXPECT(std::string("a") == slice("abcdefgh", 0, None, -1));
        EXPECT(std::string("abcdefgh") == slice("abcdefgh", None, None, None));
    },

    CASE("gt()")
    {
        using namespace ken3::pystr;

        EXPECT(false == gt("a", "a"));
        EXPECT(false == gt("A", "a"));
        EXPECT(true == gt("a", "A"));
        EXPECT(false == gt("AAA", "a"));
        EXPECT(true == gt("a", ""));
        EXPECT(false == gt("", "a"));
        EXPECT(false == gt("", ""));
    },

    CASE("le()")
    {
        using namespace ken3::pystr;

        EXPECT(true == le("a", "a"));
        EXPECT(true == le("A", "a"));
        EXPECT(false == le("a", "A"));
        EXPECT(true == le("AAA", "a"));
        EXPECT(false == le("a", ""));
        EXPECT(true == le("", "a"));
        EXPECT(true == le("", ""));
    },

    CASE("len()")
    {
        using namespace ken3::pystr;

        EXPECT(1 == len("a"));
        EXPECT(3 == len("AAA"));
        EXPECT(0 == len(""));
    },

    CASE("lt()")
    {
        using namespace ken3::pystr;

        EXPECT(false == lt("a", "a"));
        EXPECT(true == lt("A", "a"));
        EXPECT(false == lt("a", "A"));
        EXPECT(true == lt("AAA", "a"));
        EXPECT(false == lt("a", ""));
        EXPECT(true == lt("", "a"));
        EXPECT(false == lt("", ""));
    },

    CASE("mul()")
    {
        using namespace ken3::pystr;

        EXPECT(std::string("aaa") == mul("a", 3));
        EXPECT(std::string("abcabcabc") == mul("abc", 3));
        EXPECT(std::string("") == mul("", 10));
        EXPECT(std::string("") == mul("abc", 0));
        EXPECT(std::string("") == mul("abc", -1));
    },

    CASE("repr()")
    {
        using namespace ken3::pystr;

        EXPECT(std::string("'\\x00\\x01\\x02\\x03\\x04\\x05\\x06\\x07\\x08\\t\\n\\x0b\\x0c\\r\\x0e\\x0f\\x10\\x11\\x12\\x13\\x14\\x15\\x16\\x17\\x18\\x19\\x1a\\x1b\\x1c\\x1d\\x1e\\x1f !\"#$%&\\'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\\\]^_`abcdefghijklmnopqrstuvwxyz{|}~\\x7f'") == repr(str7F(128)));
        EXPECT(std::string("\"abc'abc\"") == repr("abc'abc"));
        EXPECT(std::string("'abc\"\\'abc'") == repr("abc\"'abc"));
        EXPECT(std::string("'abc'") == repr("abc"));
        EXPECT(std::string("'\\r\\n\\t'") == repr("\r\n\t"));
        EXPECT(std::string("''") == repr(""));
    },

    CASE("ne()")
    {
        using namespace ken3::pystr;

        EXPECT(false == ne("a", "a"));
        EXPECT(true == ne("a", "AAA"));
        EXPECT(true == ne("AAA", "a"));
        EXPECT(true == ne("a", ""));
        EXPECT(true == ne("", "a"));
        EXPECT(false == ne("", ""));
    },

    CASE("capitalize()")
    {
        using namespace ken3::pystr;

        EXPECT(std::string("A") == capitalize("a"));
        EXPECT(std::string("A abc") == capitalize("a abc"));
        EXPECT(std::string("A abc") == capitalize("A ABC"));
        EXPECT(std::string("A abc") == capitalize("A Abc"));
        EXPECT(std::string("Abc") == capitalize("abc"));
        EXPECT(std::string("Abc") == capitalize("ABC"));
        EXPECT(std::string("Abc") == capitalize("Abc"));
        EXPECT(std::string("98") == capitalize("98"));
        EXPECT(std::string("%$") == capitalize("%$"));
        EXPECT(std::string("") == capitalize(""));
    },

    CASE("center()")
    {
        using namespace ken3::pystr;

        EXPECT(std::string("a") == center("a", 1));
        EXPECT(std::string("a ") == center("a", 2));
        EXPECT(std::string(" a ") == center("a", 3));
        EXPECT(std::string(" a  ") == center("a", 4));
        EXPECT(std::string("aa") == center("aa", 2));
        EXPECT(std::string(" aa") == center("aa", 3));
        EXPECT(std::string(" aa ") == center("aa", 4));
        EXPECT(std::string("  aa ") == center("aa", 5));
        EXPECT(std::string("   A A   ") == center("A A ", 9));
        EXPECT(std::string("   A A    ") == center("A A ", 10));
        EXPECT(std::string("    A A    ") == center("A A ", 11));
        EXPECT(std::string("      A A      ") == center("A A ", 15));
        EXPECT(std::string("a") == center("a", 0));
        EXPECT(std::string("a") == center("a", -1));
        EXPECT(std::string("a@") == center("a", 2, "@"));
        EXPECT(std::string("@@@abc@@@@") == center("abc", 10, "@"));
        EXPECT_THROWS_AS(center("a", 1, "@@"), TypeError);
        EXPECT_THROWS_AS(center("a", 1, ""), TypeError);
        EXPECT(std::string("  ") == center("", 2));
    },

    CASE("count()")
    {
        using namespace ken3::pystr;

        EXPECT(1 == count("a", "a"));
        EXPECT(1 == count("abc", "a"));
        EXPECT(2 == count("abcab", "ab"));
        EXPECT(0 == count("", "a"));
        EXPECT(2 == count("a", ""));
        EXPECT(1 == count("", ""));
        EXPECT(0 == count("abcab", "a", 1, 3));
        EXPECT(1 == count("abcab", "a", 1, 4));
        EXPECT(0 == count("abcab", "ab", 1, 3));
        EXPECT(0 == count("abcab", "ab", 1, 4));
        EXPECT(1 == count("abcab", "a", 1));
        EXPECT(0 == count("abcab", "a", 4));
        EXPECT(3 == count("abcab", "", 1, 3));
        EXPECT(0 == count("abcab", "ab", 999));
        EXPECT(1 == count("abcab", "ab", 1, 999));
    },

    CASE("endswith() with single suffix")
    {
        using namespace ken3::pystr;

        EXPECT(true == endswith("a", "a"));
        EXPECT(false == endswith("abc", "a"));
        EXPECT(true == endswith("abc", "c"));
        EXPECT(true == endswith("abcab", "ab"));
        EXPECT(false == endswith("abcab", "ac"));
        EXPECT(false == endswith("", "a"));
        EXPECT(true == endswith("a", ""));
        EXPECT(true == endswith("", ""));
        EXPECT(false == endswith("abcab", "a", 1, 3));
        EXPECT(true == endswith("abcab", "a", 1, 4));
        EXPECT(false == endswith("abcab", "ab", 1, 3));
        EXPECT(false == endswith("abcab", "ab", 1, 4));
        EXPECT(false == endswith("abcab", "a", 1));
        EXPECT(false == endswith("abcab", "a", 4));
        EXPECT(true == endswith("abcab", "", 1, 3));
        EXPECT(false == endswith("abcab", "ab", 999));
    },

    CASE("endswith() with multiple suffixes")
    {
        using namespace ken3::pystr;

        EXPECT(true == endswith("abc", (std::vector<std::string>{"a", "b", "c"})));
        EXPECT(true == endswith("acb", (std::vector<std::string>{"a", "b", "c"})));
        EXPECT(false == endswith("ddd", (std::vector<std::string>{"a", "b", "c"})));
        EXPECT(true == endswith("abc", (std::vector<std::string>{"ab", "bc"})));
        EXPECT(false == endswith("acb", (std::vector<std::string>{"ab", "bc"})));
        EXPECT(false == endswith("abc", (std::vector<std::string>{})));
    },

    CASE("expandtabs()")
    {
        using namespace ken3::pystr;

        EXPECT(std::string("a") == expandtabs("a"));
        EXPECT(std::string("a       ") == expandtabs("a\t"));
        EXPECT(std::string("        a") == expandtabs("\ta"));
        EXPECT(std::string("        a       ") == expandtabs("\ta\t"));
        EXPECT(std::string("                        ") == expandtabs("\t\t\t"));
        EXPECT(std::string("        a  a    ") == expandtabs("\ta  a\t"));
        EXPECT(std::string("        a\na       ") == expandtabs("\ta\na\t"));
        EXPECT(std::string("a") == expandtabs("a", 4));
        EXPECT(std::string("a   ") == expandtabs("a\t", 4));
        EXPECT(std::string("    a") == expandtabs("\ta", 4));
        EXPECT(std::string("    a   ") == expandtabs("\ta\t", 4));
        EXPECT(std::string("            ") == expandtabs("\t\t\t", 4));
        EXPECT(std::string("    a  a    ") == expandtabs("\ta  a\t", 4));
        EXPECT(std::string("    a\na   ") == expandtabs("\ta\na\t", 4));
        EXPECT(std::string("a ") == expandtabs("a\t", 1));
        EXPECT(std::string("a") == expandtabs("a\t", 0));
        EXPECT(std::string("a") == expandtabs("a\t", -1));
        EXPECT(std::string("") == expandtabs(""));
    },

    CASE("find()")
    {
        using namespace ken3::pystr;

        EXPECT(0 == find("abc", "a"));
        EXPECT(-1 == find("abc", "d"));
        EXPECT(1 == find("abc", "bc"));
        EXPECT(-1 == find("abc", "ac"));
        EXPECT(0 == find("abcabc", "abc"));
        EXPECT(-1 == find("abcab", "a", 1, 3));
        EXPECT(3 == find("abcab", "a", 1, 4));
        EXPECT(-1 == find("abcab", "ab", 1, 3));
        EXPECT(-1 == find("abcab", "ab", 1, 4));
        EXPECT(3 == find("abcab", "a", 1));
        EXPECT(-1 == find("abcab", "a", 4));
        EXPECT(1 == find("abcab", "", 1, 3));
        EXPECT(-1 == find("abcab", "ab", 999));
        EXPECT(3 == find("abcab", "ab", 1, 999));
        EXPECT(-1 == find("", "a"));
        EXPECT(0 == find("a", ""));
        EXPECT(0 == find("", ""));
    },

    CASE("index()")
    {
        using namespace ken3::pystr;

        EXPECT(0 == index("abc", "a"));
        EXPECT_THROWS_AS(index("abc", "d"), ValueError);
        EXPECT(1 == index("abc", "bc"));
        EXPECT_THROWS_AS(index("abc", "ac"), ValueError);
        EXPECT(0 == index("abcabc", "abc"));
        EXPECT_THROWS_AS(index("abcab", "a", 1, 3), ValueError);
        EXPECT(3 == index("abcab", "a", 1, 4));
        EXPECT_THROWS_AS(index("abcab", "ab", 1, 3), ValueError);
        EXPECT_THROWS_AS(index("abcab", "ab", 1, 4), ValueError);
        EXPECT(3 == index("abcab", "a", 1));
        EXPECT_THROWS_AS(index("abcab", "a", 4), ValueError);
        EXPECT(1 == index("abcab", "", 1, 3));
        EXPECT_THROWS_AS(index("abcab", "ab", 999), ValueError);
        EXPECT(3 == index("abcab", "ab", 1, 999));
        EXPECT_THROWS_AS(index("", "a"), ValueError);
        EXPECT(0 == index("a", ""));
        EXPECT(0 == index("", ""));
    },

    CASE("isalnum()")
    {
        using namespace ken3::pystr;

        EXPECT(true == isalnum("a"));
        EXPECT(true == isalnum("A"));
        EXPECT(true == isalnum("abc"));
        EXPECT(true == isalnum("aBc"));
        EXPECT(false == isalnum("a c"));
        EXPECT(true == isalnum("3"));
        EXPECT(true == isalnum("3F"));
        EXPECT(false == isalnum(""));
        EXPECT(false == isalnum("@"));
        EXPECT(false == isalnum(" "));
        EXPECT(false == isalnum("3F@"));
        EXPECT(false == isalnum("\n"));
    },

    CASE("isalpha()")
    {
        using namespace ken3::pystr;

        EXPECT(true == isalpha("a"));
        EXPECT(true == isalpha("A"));
        EXPECT(true == isalpha("abc"));
        EXPECT(true == isalpha("aBc"));
        EXPECT(false == isalpha("a c"));
        EXPECT(false == isalpha("3"));
        EXPECT(false == isalpha("3F"));
        EXPECT(false == isalpha(""));
        EXPECT(false == isalpha("@"));
        EXPECT(false == isalpha(" "));
        EXPECT(false == isalpha("3F@"));
        EXPECT(false == isalpha("\n"));
    },

    CASE("isdigit()")
    {
        using namespace ken3::pystr;

        EXPECT(false == isdigit("a"));
        EXPECT(false == isdigit("A"));
        EXPECT(false == isdigit("abc"));
        EXPECT(false == isdigit("aBc"));
        EXPECT(false == isdigit("a c"));
        EXPECT(true == isdigit("3"));
        EXPECT(false == isdigit("3F"));
        EXPECT(false == isdigit(""));
        EXPECT(false == isdigit("@"));
        EXPECT(false == isdigit(" "));
        EXPECT(false == isdigit("3F@"));
        EXPECT(false == isdigit("\n"));
    },

    CASE("islower()")
    {
        using namespace ken3::pystr;

        EXPECT(true == islower("a"));
        EXPECT(false == islower("A"));
        EXPECT(true == islower("abc"));
        EXPECT(false == islower("aBc"));
        EXPECT(true == islower("a c"));
        EXPECT(false == islower("3"));
        EXPECT(false == islower("3F"));
        EXPECT(false == islower(""));
        EXPECT(false == islower("@"));
        EXPECT(false == islower(" "));
        EXPECT(false == islower("3F@"));
        EXPECT(false == islower("\n"));
    },

    CASE("isspace()")
    {
        using namespace ken3::pystr;

        EXPECT(false == isspace("a"));
        EXPECT(false == isspace("A"));
        EXPECT(false == isspace("abc"));
        EXPECT(false == isspace("aBc"));
        EXPECT(false == isspace("a c"));
        EXPECT(false == isspace("3"));
        EXPECT(false == isspace("3F"));
        EXPECT(false == isspace(""));
        EXPECT(false == isspace("@"));
        EXPECT(true == isspace(" "));
        EXPECT(false == isspace("3F@"));
        EXPECT(true == isspace("\n"));
    },

    CASE("istitle()")
    {
        using namespace ken3::pystr;

        EXPECT(false == istitle("a"));
        EXPECT(false == istitle("aaa"));
        EXPECT(false == istitle("aAa"));
        EXPECT(true == istitle("Aaa"));
        EXPECT(false == istitle("aAa AAA aaA"));
        EXPECT(false == istitle("AAa AAA AaA"));
        EXPECT(true == istitle("Aaa Bbb Ccc"));
        EXPECT(false == istitle("aAa\naaA"));
        EXPECT(false == istitle("aAa0aaA"));
        EXPECT(false == istitle("aAa-aaA"));
        EXPECT(false == istitle("aAa/aaA"));
        EXPECT(false == istitle("aAa'aaA"));
        EXPECT(false == istitle("AAa-AaA"));
        EXPECT(true == istitle("Aaa-Abc"));
        EXPECT(false == istitle(" aA a "));
        EXPECT(false == istitle(""));
    },

    CASE("isupper()")
    {
        using namespace ken3::pystr;

        EXPECT(false == isupper("a"));
        EXPECT(true == isupper("A"));
        EXPECT(false == isupper("abc"));
        EXPECT(false == isupper("aBc"));
        EXPECT(false == isupper("a c"));
        EXPECT(false == isupper("3"));
        EXPECT(true == isupper("3F"));
        EXPECT(false == isupper(""));
        EXPECT(false == isupper("@"));
        EXPECT(false == isupper(" "));
        EXPECT(true == isupper("3F@"));
        EXPECT(false == isupper("\n"));
    },

    CASE("join()")
    {
        using namespace ken3::pystr;

        EXPECT(std::string("") == join("", (std::vector<std::string>{})));
        EXPECT(std::string("") == join("a", (std::vector<std::string>{})));
        EXPECT(std::string("abc") == join("", (std::vector<std::string>{"a", "b", "c"})));
        EXPECT(std::string("aabac") == join("a", (std::vector<std::string>{"a", "b", "c"})));
        EXPECT(std::string("abbc") == join("", (std::vector<std::string>{"ab", "bc"})));
        EXPECT(std::string("ababc") == join("a", (std::vector<std::string>{"ab", "bc"})));
    },

    CASE("ljust()")
    {
        using namespace ken3::pystr;

        EXPECT(std::string("a") == ljust("a", 1));
        EXPECT(std::string("a ") == ljust("a", 2));
        EXPECT(std::string("a  ") == ljust("a", 3));
        EXPECT(std::string("a   ") == ljust("a", 4));
        EXPECT(std::string("aa") == ljust("aa", 2));
        EXPECT(std::string("aa ") == ljust("aa", 3));
        EXPECT(std::string("aa  ") == ljust("aa", 4));
        EXPECT(std::string("aa   ") == ljust("aa", 5));
        EXPECT(std::string("A A      ") == ljust("A A ", 9));
        EXPECT(std::string("A A       ") == ljust("A A ", 10));
        EXPECT(std::string("A A        ") == ljust("A A ", 11));
        EXPECT(std::string("A A            ") == ljust("A A ", 15));
        EXPECT(std::string("a") == ljust("a", 0));
        EXPECT(std::string("a") == ljust("a", -1));
        EXPECT(std::string("a@") == ljust("a", 2, "@"));
        EXPECT(std::string("abc@@@@@@@") == ljust("abc", 10, "@"));
        EXPECT_THROWS_AS(ljust("a", 1, "@@"), TypeError);
        EXPECT_THROWS_AS(ljust("a", 1, ""), TypeError);
        EXPECT(std::string("") == ljust("", 0));
        EXPECT(std::string(" ") == ljust("", 1));
        EXPECT(std::string("  ") == ljust("", 2));
    },

    CASE("lower()")
    {
        using namespace ken3::pystr;

        EXPECT(std::string("a") == lower("a"));
        EXPECT(std::string("ab") == lower("Ab"));
        EXPECT(std::string("abc") == lower("abc"));
        EXPECT(std::string("abc") == lower("aBc"));
        EXPECT(std::string("a c") == lower("a c"));
        EXPECT(std::string("3") == lower("3"));
        EXPECT(std::string("3f") == lower("3F"));
        EXPECT(std::string("") == lower(""));
        EXPECT(std::string("@") == lower("@"));
        EXPECT(std::string(" ") == lower(" "));
        EXPECT(std::string("3f@") == lower("3F@"));
        EXPECT(std::string("\n") == lower("\n"));
    },

    CASE("lstrip()")
    {
        using namespace ken3::pystr;

        EXPECT(std::string("b ab ") == lstrip("ab ab ", "a"));
        EXPECT(std::string(" ab ") == lstrip("ab ab ", "ab"));
        EXPECT(std::string(" ab ") == lstrip("ab ab ", "ba"));
        EXPECT(std::string(" ab ab") == lstrip(" ab ab", "a"));
        EXPECT(std::string(" ab ab") == lstrip(" ab ab", "ab"));
        EXPECT(std::string(" ab ab") == lstrip(" ab ab", "ba"));
        EXPECT(std::string("ab ab ") == lstrip(" ab ab "));
        EXPECT(std::string("ab ab ") == lstrip(" ab ab ", " "));
        EXPECT(std::string(" ab ab ") == lstrip(" ab ab ", ""));
        EXPECT(std::string("") == lstrip("", "a"));
        EXPECT(std::string("a") == lstrip("a", ""));
        EXPECT(std::string("") == lstrip("", ""));
    },

    CASE("partition()")
    {
        using namespace ken3::pystr;

        EXPECT((std::vector<std::string>{"", "a", "bc"}) == partition("abc", "a"));
        EXPECT((std::vector<std::string>{"a", "b", "c"}) == partition("abc", "b"));
        EXPECT((std::vector<std::string>{"ab", "c", ""}) == partition("abc", "c"));
        EXPECT((std::vector<std::string>{"abc", "", ""}) == partition("abc", "d"));
        EXPECT((std::vector<std::string>{"", "a", "b ab "}) == partition("ab ab ", "a"));
        EXPECT((std::vector<std::string>{"a", "b", " ab "}) == partition("ab ab ", "b"));
        EXPECT((std::vector<std::string>{"", "ab", " ab "}) == partition("ab ab ", "ab"));
        EXPECT((std::vector<std::string>{"ab ab ", "", ""}) == partition("ab ab ", "ba"));
        EXPECT((std::vector<std::string>{"a", "b a", "b "}) == partition("ab ab ", "b a"));
        EXPECT((std::vector<std::string>{"", " ", "ab ab "}) == partition(" ab ab ", " "));
        EXPECT_THROWS_AS(partition(" ab ab ", ""), ValueError);
        EXPECT((std::vector<std::string>{"", "", ""}) == partition("", "a"));
        EXPECT_THROWS_AS(partition("", ""), ValueError);
    },

    CASE("replace()")
    {
        using namespace ken3::pystr;

        EXPECT(std::string("aac") == replace("abc", "b", "a"));
        EXPECT(std::string("abc") == replace("abc", "d", "a"));
        EXPECT(std::string("add") == replace("abc", "bc", "dd"));
        EXPECT(std::string("abc") == replace("abc", "cb", "dd"));
        EXPECT(std::string("ad") == replace("abc", "bc", "d"));
        EXPECT(std::string("abc") == replace("abc", "cb", "d"));
        EXPECT(std::string("aaabaca") == replace("abc", "", "a"));
        EXPECT(std::string("ac") == replace("abc", "b", ""));
        EXPECT(std::string("abc") == replace("abc", "", ""));
        EXPECT(std::string("a") == replace("", "", "a"));
        EXPECT(std::string("") == replace("", "b", ""));
        EXPECT(std::string("") == replace("", "", ""));
        EXPECT(std::string("addaddadd") == replace("abcabcabc", "bc", "dd", 4));
        EXPECT(std::string("addaddadd") == replace("abcabcabc", "bc", "dd", 3));
        EXPECT(std::string("addaddabc") == replace("abcabcabc", "bc", "dd", 2));
        EXPECT(std::string("addabcabc") == replace("abcabcabc", "bc", "dd", 1));
        EXPECT(std::string("abcabcabc") == replace("abcabcabc", "bc", "dd", 0));
        EXPECT(std::string("addaddadd") == replace("abcabcabc", "bc", "dd", -1));
    },

    CASE("rfind()")
    {
        using namespace ken3::pystr;

        EXPECT(0 == rfind("abc", "a"));
        EXPECT(-1 == rfind("abc", "d"));
        EXPECT(1 == rfind("abc", "bc"));
        EXPECT(-1 == rfind("abc", "ac"));
        EXPECT(3 == rfind("abcabc", "abc"));
        EXPECT(-1 == rfind("abcab", "a", 1, 3));
        EXPECT(3 == rfind("abcab", "a", 1, 4));
        EXPECT(-1 == rfind("abcab", "ab", 1, 3));
        EXPECT(-1 == rfind("abcab", "ab", 1, 4));
        EXPECT(3 == rfind("abcab", "a", 1));
        EXPECT(-1 == rfind("abcab", "a", 4));
        EXPECT(3 == rfind("abcab", "", 1, 3));
        EXPECT(-1 == rfind("abcab", "ab", 999));
        EXPECT(3 == rfind("abcab", "ab", 1, 999));
        EXPECT(-1 == rfind("", "a"));
        EXPECT(1 == rfind("a", ""));
        EXPECT(0 == rfind("", ""));
    },

    CASE("rindex()")
    {
        using namespace ken3::pystr;

        EXPECT(0 == rindex("abc", "a"));
        EXPECT_THROWS_AS(rindex("abc", "d"), ValueError);
        EXPECT(1 == rindex("abc", "bc"));
        EXPECT_THROWS_AS(rindex("abc", "ac"), ValueError);
        EXPECT(3 == rindex("abcabc", "abc"));
        EXPECT_THROWS_AS(rindex("abcab", "a", 1, 3), ValueError);
        EXPECT(3 == rindex("abcab", "a", 1, 4));
        EXPECT_THROWS_AS(rindex("abcab", "ab", 1, 3), ValueError);
        EXPECT_THROWS_AS(rindex("abcab", "ab", 1, 4), ValueError);
        EXPECT(3 == rindex("abcab", "a", 1));
        EXPECT_THROWS_AS(rindex("abcab", "a", 4), ValueError);
        EXPECT(3 == rindex("abcab", "", 1, 3));
        EXPECT_THROWS_AS(rindex("abcab", "ab", 999), ValueError);
        EXPECT(3 == rindex("abcab", "ab", 1, 999));
        EXPECT_THROWS_AS(rindex("", "a"), ValueError);
        EXPECT(1 == rindex("a", ""));
        EXPECT(0 == rindex("", ""));
    },

    CASE("rjust()")
    {
        using namespace ken3::pystr;

        EXPECT(std::string("a") == rjust("a", 1));
        EXPECT(std::string(" a") == rjust("a", 2));
        EXPECT(std::string("  a") == rjust("a", 3));
        EXPECT(std::string("   a") == rjust("a", 4));
        EXPECT(std::string("aa") == rjust("aa", 2));
        EXPECT(std::string(" aa") == rjust("aa", 3));
        EXPECT(std::string("  aa") == rjust("aa", 4));
        EXPECT(std::string("   aa") == rjust("aa", 5));
        EXPECT(std::string("     A A ") == rjust("A A ", 9));
        EXPECT(std::string("      A A ") == rjust("A A ", 10));
        EXPECT(std::string("       A A ") == rjust("A A ", 11));
        EXPECT(std::string("           A A ") == rjust("A A ", 15));
        EXPECT(std::string("a") == rjust("a", 0));
        EXPECT(std::string("a") == rjust("a", -1));
        EXPECT(std::string("@a") == rjust("a", 2, "@"));
        EXPECT(std::string("@@@@@@@abc") == rjust("abc", 10, "@"));
        EXPECT_THROWS_AS(rjust("a", 1, "@@"), TypeError);
        EXPECT_THROWS_AS(rjust("a", 1, ""), TypeError);
        EXPECT(std::string("") == rjust("", 0));
        EXPECT(std::string(" ") == rjust("", 1));
        EXPECT(std::string("  ") == rjust("", 2));
    },

    CASE("rpartition()")
    {
        using namespace ken3::pystr;

        EXPECT((std::vector<std::string>{"", "a", "bc"}) == rpartition("abc", "a"));
        EXPECT((std::vector<std::string>{"a", "b", "c"}) == rpartition("abc", "b"));
        EXPECT((std::vector<std::string>{"ab", "c", ""}) == rpartition("abc", "c"));
        EXPECT((std::vector<std::string>{"", "", "abc"}) == rpartition("abc", "d"));
        EXPECT((std::vector<std::string>{"ab ", "a", "b "}) == rpartition("ab ab ", "a"));
        EXPECT((std::vector<std::string>{"ab a", "b", " "}) == rpartition("ab ab ", "b"));
        EXPECT((std::vector<std::string>{"ab ", "ab", " "}) == rpartition("ab ab ", "ab"));
        EXPECT((std::vector<std::string>{"", "", "ab ab "}) == rpartition("ab ab ", "ba"));
        EXPECT((std::vector<std::string>{"a", "b a", "b "}) == rpartition("ab ab ", "b a"));
        EXPECT((std::vector<std::string>{" ab ab", " ", ""}) == rpartition(" ab ab ", " "));
        EXPECT_THROWS_AS(rpartition(" ab ab ", ""), ValueError);
        EXPECT_THROWS_AS(rpartition("a", ""), ValueError);
        EXPECT((std::vector<std::string>{"", "", ""}) == rpartition("", "a"));
        EXPECT_THROWS_AS(rpartition("", ""), ValueError);
    },

    CASE("rsplit() with sep")
    {
        using namespace ken3::pystr;

        EXPECT((std::vector<std::string>{"", "bc"}) == rsplit("abc", "a"));
        EXPECT((std::vector<std::string>{"a", "c"}) == rsplit("abc", "b"));
        EXPECT((std::vector<std::string>{"ab", ""}) == rsplit("abc", "c"));
        EXPECT((std::vector<std::string>{"abc"}) == rsplit("abc", "d"));
        EXPECT((std::vector<std::string>{"", "b ", "b "}) == rsplit("ab ab ", "a"));
        EXPECT((std::vector<std::string>{"a", " a", " "}) == rsplit("ab ab ", "b"));
        EXPECT((std::vector<std::string>{"", " ", " "}) == rsplit("ab ab ", "ab"));
        EXPECT((std::vector<std::string>{"ab ab "}) == rsplit("ab ab ", "ba"));
        EXPECT((std::vector<std::string>{"a", "b "}) == rsplit("ab ab ", "b a"));
        EXPECT((std::vector<std::string>{"", "", "bb  ", "", "bb  "}) == rsplit("aabb  aabb  ", "a"));
        EXPECT((std::vector<std::string>{"aa", "", "  aa", "", "  "}) == rsplit("aabb  aabb  ", "b"));
        EXPECT((std::vector<std::string>{"aabb", "", "aabb", "", ""}) == rsplit("aabb  aabb  ", " "));
        EXPECT((std::vector<std::string>{"aab", "abb  "}) == rsplit("aabb  aabb  ", "b  a"));
        EXPECT((std::vector<std::string>{"", "ab", "ab", ""}) == rsplit(" ab ab ", " "));
        EXPECT_THROWS_AS(rsplit(" ab ab ", ""), ValueError);
        EXPECT_THROWS_AS(rsplit("a", ""), ValueError);
        EXPECT((std::vector<std::string>{""}) == rsplit("", "a"));
        EXPECT_THROWS_AS(rsplit("", ""), ValueError);
        EXPECT((std::vector<std::string>{"", "bc"}) == rsplit("abc", "a", 1));
        EXPECT((std::vector<std::string>{"a", "c"}) == rsplit("abc", "b", 1));
        EXPECT((std::vector<std::string>{"ab", ""}) == rsplit("abc", "c", 1));
        EXPECT((std::vector<std::string>{"abc"}) == rsplit("abc", "d", 1));
        EXPECT((std::vector<std::string>{"ab ", "b "}) == rsplit("ab ab ", "a", 1));
        EXPECT((std::vector<std::string>{"ab a", " "}) == rsplit("ab ab ", "b", 1));
        EXPECT((std::vector<std::string>{"ab ", " "}) == rsplit("ab ab ", "ab", 1));
        EXPECT((std::vector<std::string>{"ab ab "}) == rsplit("ab ab ", "ba", 1));
        EXPECT((std::vector<std::string>{"a", "b "}) == rsplit("ab ab ", "b a", 1));
        EXPECT((std::vector<std::string>{"aabb  a", "bb  "}) == rsplit("aabb  aabb  ", "a", 1));
        EXPECT((std::vector<std::string>{"aabb  aab", "  "}) == rsplit("aabb  aabb  ", "b", 1));
        EXPECT((std::vector<std::string>{"aabb  aabb ", ""}) == rsplit("aabb  aabb  ", " ", 1));
        EXPECT((std::vector<std::string>{"aab", "abb  "}) == rsplit("aabb  aabb  ", "b  a", 1));
        EXPECT((std::vector<std::string>{" ab ab", ""}) == rsplit(" ab ab ", " ", 1));
        EXPECT_THROWS_AS(rsplit(" ab ab ", "", 1), ValueError);
        EXPECT_THROWS_AS(rsplit("a", "", 1), ValueError);
        EXPECT((std::vector<std::string>{""}) == rsplit("", "a", 1));
        EXPECT_THROWS_AS(rsplit("", "", 1), ValueError);
        EXPECT((std::vector<std::string>{"", "bc"}) == rsplit("abc", "a", 2));
        EXPECT((std::vector<std::string>{"a", "c"}) == rsplit("abc", "b", 2));
        EXPECT((std::vector<std::string>{"ab", ""}) == rsplit("abc", "c", 2));
        EXPECT((std::vector<std::string>{"abc"}) == rsplit("abc", "d", 2));
        EXPECT((std::vector<std::string>{"", "b ", "b "}) == rsplit("ab ab ", "a", 2));
        EXPECT((std::vector<std::string>{"a", " a", " "}) == rsplit("ab ab ", "b", 2));
        EXPECT((std::vector<std::string>{"", " ", " "}) == rsplit("ab ab ", "ab", 2));
        EXPECT((std::vector<std::string>{"ab ab "}) == rsplit("ab ab ", "ba", 2));
        EXPECT((std::vector<std::string>{"a", "b "}) == rsplit("ab ab ", "b a", 2));
        EXPECT((std::vector<std::string>{"aabb  ", "", "bb  "}) == rsplit("aabb  aabb  ", "a", 2));
        EXPECT((std::vector<std::string>{"aabb  aa", "", "  "}) == rsplit("aabb  aabb  ", "b", 2));
        EXPECT((std::vector<std::string>{"aabb  aabb", "", ""}) == rsplit("aabb  aabb  ", " ", 2));
        EXPECT((std::vector<std::string>{"aab", "abb  "}) == rsplit("aabb  aabb  ", "b  a", 2));
        EXPECT((std::vector<std::string>{" ab", "ab", ""}) == rsplit(" ab ab ", " ", 2));
        EXPECT_THROWS_AS(rsplit(" ab ab ", "", 2), ValueError);
        EXPECT_THROWS_AS(rsplit("a", "", 2), ValueError);
        EXPECT((std::vector<std::string>{""}) == rsplit("", "a", 2));
        EXPECT_THROWS_AS(rsplit("", "", 2), ValueError);
        EXPECT((std::vector<std::string>{"a", "c"}) == rsplit("abc", "b", 10));
        EXPECT((std::vector<std::string>{"abc"}) == rsplit("abc", "b", 0));
        EXPECT((std::vector<std::string>{"a", "c"}) == rsplit("abc", "b", -1));
        EXPECT((std::vector<std::string>{"a", "c"}) == rsplit("abc", "b", -10000));
    },

    CASE("rsplit() without sep")
    {
        using namespace ken3::pystr;

        EXPECT((std::vector<std::string>{"abc"}) == rsplit("abc"));
        EXPECT((std::vector<std::string>{"ab", "ab"}) == rsplit("ab ab "));
        EXPECT((std::vector<std::string>{"aabb", "aabb"}) == rsplit("aabb  aabb  "));
        EXPECT((std::vector<std::string>{"ab", "ab"}) == rsplit(" ab ab "));
        EXPECT((std::vector<std::string>{"a"}) == rsplit("a"));
        EXPECT((std::vector<std::string>{}) == rsplit(""));
        EXPECT((std::vector<std::string>{"abc"}) == rsplit("abc", 1));
        EXPECT((std::vector<std::string>{"ab", "ab"}) == rsplit("ab ab ", 1));
        EXPECT((std::vector<std::string>{"aabb", "aabb"}) == rsplit("aabb  aabb  ", 1));
        EXPECT((std::vector<std::string>{" ab", "ab"}) == rsplit(" ab ab ", 1));
        EXPECT((std::vector<std::string>{"a"}) == rsplit("a", 1));
        EXPECT((std::vector<std::string>{}) == rsplit("", 1));
        EXPECT((std::vector<std::string>{"abc"}) == rsplit("abc", 2));
        EXPECT((std::vector<std::string>{"ab", "ab"}) == rsplit("ab ab ", 2));
        EXPECT((std::vector<std::string>{"aabb", "aabb"}) == rsplit("aabb  aabb  ", 2));
        EXPECT((std::vector<std::string>{"ab", "ab"}) == rsplit(" ab ab ", 2));
        EXPECT((std::vector<std::string>{"a"}) == rsplit("a", 2));
        EXPECT((std::vector<std::string>{}) == rsplit("", 2));
        EXPECT((std::vector<std::string>{"abc"}) == rsplit("abc", 10));
        EXPECT((std::vector<std::string>{"abc"}) == rsplit("abc", 0));
        EXPECT((std::vector<std::string>{"abc"}) == rsplit("abc", -1));
        EXPECT((std::vector<std::string>{"abc"}) == rsplit("abc", -10000));
    },

    CASE("rstrip()")
    {
        using namespace ken3::pystr;

        EXPECT(std::string("ab ab") == rstrip("ab ab", "a"));
        EXPECT(std::string("ab ") == rstrip("ab ab", "ab"));
        EXPECT(std::string("ab ") == rstrip("ab ab", "ba"));
        EXPECT(std::string(" ab ab ") == rstrip(" ab ab ", "a"));
        EXPECT(std::string(" ab ab ") == rstrip(" ab ab ", "ab"));
        EXPECT(std::string(" ab ab ") == rstrip(" ab ab ", "ba"));
        EXPECT(std::string(" ab ab") == rstrip(" ab ab "));
        EXPECT(std::string(" ab ab") == rstrip(" ab ab ", " "));
        EXPECT(std::string(" ab ab ") == rstrip(" ab ab ", ""));
        EXPECT(std::string("") == rstrip("", "a"));
        EXPECT(std::string("a") == rstrip("a", ""));
        EXPECT(std::string("") == rstrip("", ""));
    },

    CASE("split() with sep")
    {
        using namespace ken3::pystr;

        EXPECT((std::vector<std::string>{"", "bc"}) == split("abc", "a"));
        EXPECT((std::vector<std::string>{"a", "c"}) == split("abc", "b"));
        EXPECT((std::vector<std::string>{"ab", ""}) == split("abc", "c"));
        EXPECT((std::vector<std::string>{"abc"}) == split("abc", "d"));
        EXPECT((std::vector<std::string>{"", "b ", "b "}) == split("ab ab ", "a"));
        EXPECT((std::vector<std::string>{"a", " a", " "}) == split("ab ab ", "b"));
        EXPECT((std::vector<std::string>{"", " ", " "}) == split("ab ab ", "ab"));
        EXPECT((std::vector<std::string>{"ab ab "}) == split("ab ab ", "ba"));
        EXPECT((std::vector<std::string>{"a", "b "}) == split("ab ab ", "b a"));
        EXPECT((std::vector<std::string>{"", "", "bb  ", "", "bb  "}) == split("aabb  aabb  ", "a"));
        EXPECT((std::vector<std::string>{"aa", "", "  aa", "", "  "}) == split("aabb  aabb  ", "b"));
        EXPECT((std::vector<std::string>{"aabb", "", "aabb", "", ""}) == split("aabb  aabb  ", " "));
        EXPECT((std::vector<std::string>{"aab", "abb  "}) == split("aabb  aabb  ", "b  a"));
        EXPECT((std::vector<std::string>{"", "ab", "ab", ""}) == split(" ab ab ", " "));
        EXPECT_THROWS_AS(split(" ab ab ", ""), ValueError);
        EXPECT_THROWS_AS(split("a", ""), ValueError);
        EXPECT((std::vector<std::string>{""}) == split("", "a"));
        EXPECT_THROWS_AS(split("", ""), ValueError);
        EXPECT((std::vector<std::string>{"", "bc"}) == split("abc", "a", 1));
        EXPECT((std::vector<std::string>{"a", "c"}) == split("abc", "b", 1));
        EXPECT((std::vector<std::string>{"ab", ""}) == split("abc", "c", 1));
        EXPECT((std::vector<std::string>{"abc"}) == split("abc", "d", 1));
        EXPECT((std::vector<std::string>{"", "b ab "}) == split("ab ab ", "a", 1));
        EXPECT((std::vector<std::string>{"a", " ab "}) == split("ab ab ", "b", 1));
        EXPECT((std::vector<std::string>{"", " ab "}) == split("ab ab ", "ab", 1));
        EXPECT((std::vector<std::string>{"ab ab "}) == split("ab ab ", "ba", 1));
        EXPECT((std::vector<std::string>{"a", "b "}) == split("ab ab ", "b a", 1));
        EXPECT((std::vector<std::string>{"", "abb  aabb  "}) == split("aabb  aabb  ", "a", 1));
        EXPECT((std::vector<std::string>{"aa", "b  aabb  "}) == split("aabb  aabb  ", "b", 1));
        EXPECT((std::vector<std::string>{"aabb", " aabb  "}) == split("aabb  aabb  ", " ", 1));
        EXPECT((std::vector<std::string>{"aab", "abb  "}) == split("aabb  aabb  ", "b  a", 1));
        EXPECT((std::vector<std::string>{"", "ab ab "}) == split(" ab ab ", " ", 1));
        EXPECT_THROWS_AS(split(" ab ab ", "", 1), ValueError);
        EXPECT_THROWS_AS(split("a", "", 1), ValueError);
        EXPECT((std::vector<std::string>{""}) == split("", "a", 1));
        EXPECT_THROWS_AS(split("", "", 1), ValueError);
        EXPECT((std::vector<std::string>{"", "bc"}) == split("abc", "a", 2));
        EXPECT((std::vector<std::string>{"a", "c"}) == split("abc", "b", 2));
        EXPECT((std::vector<std::string>{"ab", ""}) == split("abc", "c", 2));
        EXPECT((std::vector<std::string>{"abc"}) == split("abc", "d", 2));
        EXPECT((std::vector<std::string>{"", "b ", "b "}) == split("ab ab ", "a", 2));
        EXPECT((std::vector<std::string>{"a", " a", " "}) == split("ab ab ", "b", 2));
        EXPECT((std::vector<std::string>{"", " ", " "}) == split("ab ab ", "ab", 2));
        EXPECT((std::vector<std::string>{"ab ab "}) == split("ab ab ", "ba", 2));
        EXPECT((std::vector<std::string>{"a", "b "}) == split("ab ab ", "b a", 2));
        EXPECT((std::vector<std::string>{"", "", "bb  aabb  "}) == split("aabb  aabb  ", "a", 2));
        EXPECT((std::vector<std::string>{"aa", "", "  aabb  "}) == split("aabb  aabb  ", "b", 2));
        EXPECT((std::vector<std::string>{"aabb", "", "aabb  "}) == split("aabb  aabb  ", " ", 2));
        EXPECT((std::vector<std::string>{"aab", "abb  "}) == split("aabb  aabb  ", "b  a", 2));
        EXPECT((std::vector<std::string>{"", "ab", "ab "}) == split(" ab ab ", " ", 2));
        EXPECT_THROWS_AS(split(" ab ab ", "", 2), ValueError);
        EXPECT_THROWS_AS(split("a", "", 2), ValueError);
        EXPECT((std::vector<std::string>{""}) == split("", "a", 2));
        EXPECT_THROWS_AS(split("", "", 2), ValueError);
        EXPECT((std::vector<std::string>{"a", "c"}) == split("abc", "b", 10));
        EXPECT((std::vector<std::string>{"abc"}) == split("abc", "b", 0));
        EXPECT((std::vector<std::string>{"a", "c"}) == split("abc", "b", -1));
        EXPECT((std::vector<std::string>{"a", "c"}) == split("abc", "b", -10000));
    },

    CASE("split() without sep")
    {
        using namespace ken3::pystr;

        EXPECT((std::vector<std::string>{"abc"}) == split("abc"));
        EXPECT((std::vector<std::string>{"ab", "ab"}) == split("ab ab "));
        EXPECT((std::vector<std::string>{"aabb", "aabb"}) == split("aabb  aabb  "));
        EXPECT((std::vector<std::string>{"ab", "ab"}) == split(" ab ab "));
        EXPECT((std::vector<std::string>{"a"}) == split("a"));
        EXPECT((std::vector<std::string>{}) == split(""));
        EXPECT((std::vector<std::string>{"abc"}) == split("abc", 1));
        EXPECT((std::vector<std::string>{"ab", "ab "}) == split("ab ab ", 1));
        EXPECT((std::vector<std::string>{"aabb", "aabb  "}) == split("aabb  aabb  ", 1));
        EXPECT((std::vector<std::string>{"ab", "ab "}) == split(" ab ab ", 1));
        EXPECT((std::vector<std::string>{"a"}) == split("a", 1));
        EXPECT((std::vector<std::string>{}) == split("", 1));
        EXPECT((std::vector<std::string>{"abc"}) == split("abc", 2));
        EXPECT((std::vector<std::string>{"ab", "ab"}) == split("ab ab ", 2));
        EXPECT((std::vector<std::string>{"aabb", "aabb"}) == split("aabb  aabb  ", 2));
        EXPECT((std::vector<std::string>{"ab", "ab"}) == split(" ab ab ", 2));
        EXPECT((std::vector<std::string>{"a"}) == split("a", 2));
        EXPECT((std::vector<std::string>{}) == split("", 2));
        EXPECT((std::vector<std::string>{"abc"}) == split("abc", 10));
        EXPECT((std::vector<std::string>{"abc"}) == split("abc", 0));
        EXPECT((std::vector<std::string>{"abc"}) == split("abc", -1));
        EXPECT((std::vector<std::string>{"abc"}) == split("abc", -10000));
    },

    CASE("splitlines()")
    {
        using namespace ken3::pystr;

        EXPECT((std::vector<std::string>{"abc"}) == splitlines("abc"));
        EXPECT((std::vector<std::string>{"a", "bc"}) == splitlines("a\rbc"));
        EXPECT((std::vector<std::string>{"a", "bc"}) == splitlines("a\nbc"));
        EXPECT((std::vector<std::string>{"a", "b", "c"}) == splitlines("a\rb\rc"));
        EXPECT((std::vector<std::string>{"a", "b", "c"}) == splitlines("a\nb\nc"));
        EXPECT((std::vector<std::string>{"a", "bc"}) == splitlines("a\r\nbc"));
        EXPECT((std::vector<std::string>{"a", "", "bc"}) == splitlines("a\n\rbc"));
        EXPECT((std::vector<std::string>{"", "", "a", "bc"}) == splitlines("\r\ra\r\nbc\n"));
        EXPECT((std::vector<std::string>{"", "", "a", "bc"}) == splitlines("\n\na\r\nbc\r"));
        EXPECT((std::vector<std::string>{"", "a", "bc"}) == splitlines("\r\na\r\nbc\r\n"));
        EXPECT((std::vector<std::string>{}) == splitlines(""));
        EXPECT((std::vector<std::string>{"abc"}) == splitlines("abc", true));
        EXPECT((std::vector<std::string>{"a\r", "bc"}) == splitlines("a\rbc", true));
        EXPECT((std::vector<std::string>{"a\n", "bc"}) == splitlines("a\nbc", true));
        EXPECT((std::vector<std::string>{"a\r\n", "bc"}) == splitlines("a\r\nbc", true));
        EXPECT((std::vector<std::string>{"a\n", "\r", "bc"}) == splitlines("a\n\rbc", true));
        EXPECT((std::vector<std::string>{"\r", "\r", "a\r\n", "bc\n"}) == splitlines("\r\ra\r\nbc\n", true));
        EXPECT((std::vector<std::string>{"\n", "\n", "a\r\n", "bc\r"}) == splitlines("\n\na\r\nbc\r", true));
        EXPECT((std::vector<std::string>{"\r\n", "a\r\n", "bc\r\n"}) == splitlines("\r\na\r\nbc\r\n", true));
        EXPECT((std::vector<std::string>{}) == splitlines("", true));
    },

    CASE("startswith() with single prefix")
    {
        using namespace ken3::pystr;

        EXPECT(true == startswith("a", "a"));
        EXPECT(true == startswith("abc", "a"));
        EXPECT(false == startswith("abc", "c"));
        EXPECT(true == startswith("abcab", "ab"));
        EXPECT(false == startswith("abcab", "ac"));
        EXPECT(false == startswith("", "a"));
        EXPECT(true == startswith("a", ""));
        EXPECT(true == startswith("", ""));
        EXPECT(false == startswith("abcab", "a", 1, 3));
        EXPECT(false == startswith("abcab", "a", 1, 4));
        EXPECT(false == startswith("abcab", "ab", 1, 3));
        EXPECT(false == startswith("abcab", "ab", 1, 4));
        EXPECT(false == startswith("abcab", "a", 1));
        EXPECT(false == startswith("abcab", "a", 4));
        EXPECT(true == startswith("abcab", "", 1, 3));
        EXPECT(false == startswith("abcab", "ab", 999));
    },

    CASE("startswith() with multiple prefixes")
    {
        using namespace ken3::pystr;

        EXPECT(true == startswith("abc", (std::vector<std::string>{"a", "b", "c"})));
        EXPECT(true == startswith("acb", (std::vector<std::string>{"a", "b", "c"})));
        EXPECT(false == startswith("ddd", (std::vector<std::string>{"a", "b", "c"})));
        EXPECT(true == startswith("abc", (std::vector<std::string>{"ab", "bc"})));
        EXPECT(false == startswith("acb", (std::vector<std::string>{"ab", "bc"})));
        EXPECT(false == startswith("abc", (std::vector<std::string>{})));
    },

    CASE("strip()")
    {
        using namespace ken3::pystr;

        EXPECT(std::string("b ab ") == strip("ab ab ", "a"));
        EXPECT(std::string(" ab ") == strip("ab ab ", "ab"));
        EXPECT(std::string(" ab ") == strip("ab ab ", "ba"));
        EXPECT(std::string(" ab ab") == strip(" ab ab", "a"));
        EXPECT(std::string(" ab ") == strip(" ab ab", "ab"));
        EXPECT(std::string(" ab ") == strip(" ab ab", "ba"));
        EXPECT(std::string("ab ab") == strip(" ab ab "));
        EXPECT(std::string("ab ab") == strip(" ab ab ", " "));
        EXPECT(std::string(" ab ab ") == strip(" ab ab ", ""));
        EXPECT(std::string("") == strip("", "a"));
        EXPECT(std::string("a") == strip("a", ""));
        EXPECT(std::string("") == strip("", ""));
    },

    CASE("swapcase()")
    {
        using namespace ken3::pystr;

        EXPECT(std::string("A") == swapcase("a"));
        EXPECT(std::string("aB") == swapcase("Ab"));
        EXPECT(std::string("ABC") == swapcase("abc"));
        EXPECT(std::string("AbC") == swapcase("aBc"));
        EXPECT(std::string("A C") == swapcase("a c"));
        EXPECT(std::string("3") == swapcase("3"));
        EXPECT(std::string("3f") == swapcase("3F"));
        EXPECT(std::string("") == swapcase(""));
        EXPECT(std::string("@") == swapcase("@"));
        EXPECT(std::string(" ") == swapcase(" "));
        EXPECT(std::string("3f@") == swapcase("3F@"));
        EXPECT(std::string("\n") == swapcase("\n"));
    },

    CASE("title()")
    {
        using namespace ken3::pystr;

        EXPECT(std::string("A") == title("a"));
        EXPECT(std::string("Aaa") == title("aaa"));
        EXPECT(std::string("Aaa") == title("aAa"));
        EXPECT(std::string("Aaa") == title("Aaa"));
        EXPECT(std::string("Aaa Aaa Aaa") == title("aAa AAA aaA"));
        EXPECT(std::string("Aaa Aaa Aaa") == title("AAa AAA AaA"));
        EXPECT(std::string("Aaa Bbb Ccc") == title("Aaa Bbb Ccc"));
        EXPECT(std::string("Aaa\nAaa") == title("aAa\naaA"));
        EXPECT(std::string("Aaa0Aaa") == title("aAa0aaA"));
        EXPECT(std::string("Aaa-Aaa") == title("aAa-aaA"));
        EXPECT(std::string("Aaa/Aaa") == title("aAa/aaA"));
        EXPECT(std::string("Aaa'Aaa") == title("aAa'aaA"));
        EXPECT(std::string("Aaa-Aaa") == title("AAa-AaA"));
        EXPECT(std::string("Aaa-Abc") == title("Aaa-Abc"));
        EXPECT(std::string(" Aa A ") == title(" aA a "));
        EXPECT(std::string("") == title(""));
    },

    CASE("upper()")
    {
        using namespace ken3::pystr;

        EXPECT(std::string("A") == upper("a"));
        EXPECT(std::string("AB") == upper("Ab"));
        EXPECT(std::string("ABC") == upper("abc"));
        EXPECT(std::string("ABC") == upper("aBc"));
        EXPECT(std::string("A C") == upper("a c"));
        EXPECT(std::string("3") == upper("3"));
        EXPECT(std::string("3F") == upper("3F"));
        EXPECT(std::string("") == upper(""));
        EXPECT(std::string("@") == upper("@"));
        EXPECT(std::string(" ") == upper(" "));
        EXPECT(std::string("3F@") == upper("3F@"));
        EXPECT(std::string("\n") == upper("\n"));
    },

    CASE("zfill()")
    {
        using namespace ken3::pystr;

        EXPECT(std::string("00001") == zfill("1", 5));
        EXPECT(std::string("-0001") == zfill("-1", 5));
        EXPECT(std::string("0000a") == zfill("a", 5));
        EXPECT(std::string("-000a") == zfill("-a", 5));
        EXPECT(std::string("00100") == zfill("100", 5));
        EXPECT(std::string("-0100") == zfill("-100", 5));
        EXPECT(std::string("01000") == zfill("1000", 5));
        EXPECT(std::string("-1000") == zfill("-1000", 5));
        EXPECT(std::string("10000") == zfill("10000", 5));
        EXPECT(std::string("-10000") == zfill("-10000", 5));
        EXPECT(std::string("-0---") == zfill("----", 5));
        EXPECT(std::string("123") == zfill("123", 0));
        EXPECT(std::string("123") == zfill("123", -1));
        EXPECT(std::string("123") == zfill("123", -100));
        EXPECT(std::string("00000") == zfill("", 5));
        EXPECT(std::string("") == zfill("", 0));
        EXPECT(std::string("") == zfill("", -1));
        EXPECT(std::string("") == zfill("", -100));
    },

};

int main(int argc, char* argv[])
{
    return lest::run(specification, argc, argv);
}
/////////////////////////////////////////////////////////////////////////////

