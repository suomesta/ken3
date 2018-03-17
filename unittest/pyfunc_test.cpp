/**
 * @file    unittest/pyfunc_test.cpp
 * @brief   Testing ken3::pyfunc using lest. 
 * @author  toda
 * @date    2018-03-13
 * @version 0.1.0
 * @remark  the target is C++11 or more
 */

#include <algorithm>
#include <array>
#include <cctype>
#include <complex>
#include <functional>
#include <list>
#include <set>
#include <string>
#include <vector>
#include "ken3/pyfunc.hpp"
#include "unittest/lest.hpp"

const lest::test specification[] =
{

    CASE("min() with one argument")
    {
        using ken3::pyfunc::min;

        {
            int a[5] = {1, -3, 0, 5, 4};
            EXPECT(-3 == min(a));
        }
        {
            std::array<int, 5> a = {1, -3, 0, 5, 4};
            EXPECT(-3 == min(a));
        }
        {
            std::list<int> l = {1, -3, 0, 5, 4};
            EXPECT(-3 == min(l));
        }
        {
            std::set<int> s = {1, -3, 0, 5, 4};
            EXPECT(-3 == min(s));
        }
        {
            std::vector<int> v = {1, -3, 0, 5, 4};
            EXPECT(-3 == min(v));
        }
        {
            std::vector<double> v = {1.5, -3.5, 0.5, 5.5, 4.5};
            EXPECT(-3.5 == min(v));
        }
        {
            std::string s = "BbAaCc";
            EXPECT('A' == min(s));
        }
        {
            int a[5] = {1, -3, -5, -5, 4};
            EXPECT(-5 == min(a));
        }
        {
            unsigned int a[5] = {1, 3, 5, 5, 4};
            EXPECT(1U == min(a));
        }
        {
            std::string a[5] = {"", "ABC", "ABC", "DEF", "abc"};
            EXPECT("" == min(a));
        }
        {
            std::string a[5] = {"DEF", "DEF", "DEF", "ABC", "abc"};
            EXPECT("ABC" == min(a));
        }
        {
            struct one_digit {
                int int_;
                one_digit(int initial) :
                    int_(initial)
                { ; }
                bool operator<(const one_digit& rhs) const {
                    return (int_ % 10) < (rhs.int_ % 10);
                }
            };
            one_digit a[5] = {one_digit(15), one_digit(51), one_digit(77), one_digit(23), one_digit(32)};
            EXPECT(51 == min(a).int_);
        }
        {
            struct one_digit {
                int int_;
                one_digit(int initial) :
                    int_(initial)
                { ; }
                bool operator<(const one_digit& rhs) const {
                    return (int_ % 10) < (rhs.int_ % 10);
                }
            };
            one_digit a[5] = {one_digit(11), one_digit(21), one_digit(31), one_digit(41), one_digit(51)};
            EXPECT(11 == min(a).int_);
        }
        {
            std::vector<int> v = {1};
            EXPECT(1 == min(v));
        }
        {
            std::vector<int> v;
            EXPECT_THROWS_AS(min(v), ken3::pyfunc::ValueError);
        }
        {
            std::vector<int> v = {1, -3, 0, 5, 4};
            EXPECT((std::is_same<const int&, decltype(min(v))>::value));
        }
        {
            std::vector<double> v = {1.5, -3.5, 0.5, 5.5, 4.5};
            EXPECT((std::is_same<const double&, decltype(min(v))>::value));
        }
        {
            std::string a[5] = {"", "ABC", "ABC", "DEF", "abc"};
            EXPECT((std::is_same<const std::string&, decltype(min(a))>::value));
        }
    },

    CASE("min() with two argument")
    {
        using ken3::pyfunc::min;

        {
            auto comp = [](const std::string& lhs, const std::string& rhs) -> bool {
                std::string lhs2(lhs);
                std::transform(lhs2.begin(), lhs2.end(), lhs2.begin(), ::toupper);
                std::string rhs2(rhs);
                std::transform(rhs2.begin(), rhs2.end(), rhs2.begin(), ::toupper);
                return lhs2 < rhs2;
            };
            std::string a[5] = {"ABCD", "AbCD", "abc", "BBB", "EEE"};
            EXPECT("abc" == min(a, comp));
        }
        {
            auto comp = [](const std::string& lhs, const std::string& rhs) -> bool {
                std::string lhs2(lhs);
                std::transform(lhs2.begin(), lhs2.end(), lhs2.begin(), ::toupper);
                std::string rhs2(rhs);
                std::transform(rhs2.begin(), rhs2.end(), rhs2.begin(), ::toupper);
                return lhs2 < rhs2;
            };
            std::string a[5] = {"abc", "ABC", "AbC", "Abc", "aBC"};
            EXPECT("abc" == min(a, comp));
        }
        {
            auto comp = [](int lhs, int rhs) -> bool {
                return (lhs % 10) < (rhs % 10);
            };
            int a[5] = {15, 51, 77, 23, 32};
            EXPECT(51 == min(a, comp));
        }
        {
            auto comp = [](int lhs, int rhs) -> bool {
                return (lhs % 10) < (rhs % 10);
            };
            int a[5] = {11, 21, 31, 41, 51};
            EXPECT(11 == min(a, comp));
        }
        {
            std::vector<int> v = {1};
            EXPECT(1 == min(v, std::less<int>()));
        }
        {
            std::vector<int> v;
            EXPECT_THROWS_AS(min(v, std::less<int>()), ken3::pyfunc::ValueError);
        }
        {
            auto comp = [](int lhs, int rhs) -> bool {
                return (lhs % 10) < (rhs % 10);
            };
            std::vector<int> v = {11, 21, 31, 41, 51};
            EXPECT((std::is_same<const int&, decltype(min(v, comp))>::value));
        }
        {
            auto comp = [](const std::string& lhs, const std::string& rhs) -> bool {
                std::string lhs2(lhs);
                std::transform(lhs2.begin(), lhs2.end(), lhs2.begin(), ::toupper);
                std::string rhs2(rhs);
                std::transform(rhs2.begin(), rhs2.end(), rhs2.begin(), ::toupper);
                return lhs2 < rhs2;
            };
            std::string a[5] = {"ABCD", "AbCD", "abc", "BBB", "EEE"};
            EXPECT((std::is_same<const std::string&, decltype(min(a, comp))>::value));
        }
    },

    CASE("max() with one argument")
    {
        using ken3::pyfunc::max;

        {
            int a[5] = {1, -3, 0, 5, 4};
            EXPECT(5 == max(a));
        }
        {
            std::array<int, 5> a = {1, -3, 0, 5, 4};
            EXPECT(5 == max(a));
        }
        {
            std::list<int> l = {1, -3, 0, 5, 4};
            EXPECT(5 == max(l));
        }
        {
            std::set<int> s = {1, -3, 0, 5, 4};
            EXPECT(5 == max(s));
        }
        {
            std::vector<int> v = {1, -3, 0, 5, 4};
            EXPECT(5 == max(v));
        }
        {
            std::string s = "BbAaCc";
            EXPECT('c' == max(s));
        }
        {
            int a[5] = {1, -3, 4, -5, 4};
            EXPECT(4 == max(a));
        }
        {
            unsigned int a[5] = {1, 3, 1, 5, 4};
            EXPECT(5U == max(a));
        }
        {
            std::string a[5] = {"", "ABC", "ABC", "DEF", "abc"};
            EXPECT("abc" == max(a));
        }
        {
            std::string a[5] = {"DEF", "def", "DEF", "ABC", "abc"};
            EXPECT("def" == max(a));
        }
        {
            struct one_digit {
                int int_;
                one_digit(int initial) :
                    int_(initial)
                { ; }
                bool operator<(const one_digit& rhs) const {
                    return (int_ % 10) < (rhs.int_ % 10);
                }
            };
            one_digit a[5] = {one_digit(15), one_digit(51), one_digit(17), one_digit(23), one_digit(32)};
            EXPECT(17 == max(a).int_);
        }
        {
            struct one_digit {
                int int_;
                one_digit(int initial) :
                    int_(initial)
                { ; }
                bool operator<(const one_digit& rhs) const {
                    return (int_ % 10) < (rhs.int_ % 10);
                }
            };
            one_digit a[5] = {one_digit(11), one_digit(21), one_digit(31), one_digit(41), one_digit(51)};
            EXPECT(11 == max(a).int_);
        }
        {
            std::vector<int> v = {1};
            EXPECT(1 == max(v));
        }
        {
            std::vector<int> v;
            EXPECT_THROWS_AS(max(v), ken3::pyfunc::ValueError);
        }
        {
            std::vector<int> v = {1, -3, 0, 5, 4};
            EXPECT((std::is_same<const int&, decltype(max(v))>::value));
        }
        {
            std::vector<double> v = {1.5, -3.5, 0.5, 5.5, 4.5};
            EXPECT((std::is_same<const double&, decltype(max(v))>::value));
        }
        {
            std::string a[5] = {"", "ABC", "ABC", "DEF", "abc"};
            EXPECT((std::is_same<const std::string&, decltype(max(a))>::value));
        }
    },

    CASE("max() with two argument")
    {
        using ken3::pyfunc::max;

        {
            auto comp = [](const std::string& lhs, const std::string& rhs) -> bool {
                std::string lhs2(lhs);
                std::transform(lhs2.begin(), lhs2.end(), lhs2.begin(), ::toupper);
                std::string rhs2(rhs);
                std::transform(rhs2.begin(), rhs2.end(), rhs2.begin(), ::toupper);
                return lhs2 < rhs2;
            };
            std::string a[5] = {"ABCD", "eed", "abc", "BBB", "EEE"};
            EXPECT("EEE" == max(a, comp));
        }
        {
            auto comp = [](const std::string& lhs, const std::string& rhs) -> bool {
                std::string lhs2(lhs);
                std::transform(lhs2.begin(), lhs2.end(), lhs2.begin(), ::toupper);
                std::string rhs2(rhs);
                std::transform(rhs2.begin(), rhs2.end(), rhs2.begin(), ::toupper);
                return lhs2 < rhs2;
            };
            std::string a[5] = {"abc", "ABC", "AbC", "Abc", "aBC"};
            EXPECT("abc" == max(a, comp));
        }
        {
            auto comp = [](int lhs, int rhs) -> bool {
                return (lhs % 10) < (rhs % 10);
            };
            int a[5] = {15, 51, 17, 23, 32};
            EXPECT(17 == max(a, comp));
        }
        {
            auto comp = [](int lhs, int rhs) -> bool {
                return (lhs % 10) < (rhs % 10);
            };
            int a[5] = {11, 21, 31, 41, 51};
            EXPECT(11 == max(a, comp));
        }
        {
            std::vector<int> v = {1};
            EXPECT(1 == max(v, std::less<int>()));
        }
        {
            std::vector<int> v;
            EXPECT_THROWS_AS(max(v, std::less<int>()), ken3::pyfunc::ValueError);
        }
        {
            auto comp = [](int lhs, int rhs) -> bool {
                return (lhs % 10) < (rhs % 10);
            };
            std::vector<int> v = {11, 21, 31, 41, 51};
            EXPECT((std::is_same<const int&, decltype(max(v, comp))>::value));
        }
        {
            auto comp = [](const std::string& lhs, const std::string& rhs) -> bool {
                std::string lhs2(lhs);
                std::transform(lhs2.begin(), lhs2.end(), lhs2.begin(), ::toupper);
                std::string rhs2(rhs);
                std::transform(rhs2.begin(), rhs2.end(), rhs2.begin(), ::toupper);
                return lhs2 < rhs2;
            };
            std::string a[5] = {"ABCD", "AbCD", "abc", "BBB", "EEE"};
            EXPECT((std::is_same<const std::string&, decltype(max(a, comp))>::value));
        }
    },

    CASE("all()")
    {
        using ken3::pyfunc::all;

        {
            int a[5] = {1, -3, 0, 5, 4};
            EXPECT(false == all(a));
        }
        {
            int a[5] = {1, -3, 1, 5, 4};
            EXPECT(true == all(a));
        }
        {
            std::array<int, 5> a = {1, -3, 0, 0, 4};
            EXPECT(false == all(a));
        }
        {
            std::array<int, 5> a = {1, -3, 5, 5, 4};
            EXPECT(true == all(a));
        }
        {
            std::list<int> l = {1, 0, 0, 5, 4};
            EXPECT(false == all(l));
        }
        {
            std::set<int> s = {1, -3, -1, 5, 4};
            EXPECT(true == all(s));
        }
        {
            std::vector<int> v = {1, -3, 0, 5, 4, 2};
            EXPECT(false == all(v));
        }
        {
            std::vector<int> v = {1, -3, 2, 5, 4, 2};
            EXPECT(true == all(v));
        }
        {
            std::string s = "BbAaCc";
            s.at(2) = '\0';
            EXPECT(false == all(s));
        }
        {
            std::string s = "BbAaCc";
            EXPECT(true == all(s));
        }
        {
            struct always_true {
                operator bool(void) const {
                    return true;
                }
            };
            always_true a[3];
            EXPECT(true == all(a));
        }
        {
            struct always_false {
                operator bool(void) const {
                    return false;
                }
            };
            always_false a[3];
            EXPECT(false == all(a));
        }
        {
            bool a[3] = {true, false, true};
            EXPECT(false == all(a));
        }
        {
            bool a[3] = {true, true, true};
            EXPECT(true == all(a));
        }
        {
            std::vector<bool> v = {true, false, true};
            EXPECT(false == all(v));
        }
        {
            std::vector<bool> v = {true, true, true};
            EXPECT(true == all(v));
        }
        {
            double a[3] = {1.0, 0.0, -1.0};
            EXPECT(false == all(a));
        }
        {
            double a[3] = {2.0, 3.0, 4.0};
            EXPECT(true == all(a));
        }
        {
            std::vector<double> v = {1.0, 0.0, -1.0};
            EXPECT(false == all(v));
        }
        {
            std::vector<double> v = {2.0, 3.0, 4.0};
            EXPECT(true == all(v));
        }
        {
            std::vector<int> v = {0};
            EXPECT(false == all(v));
        }
        {
            std::vector<int> v = {1};
            EXPECT(true == all(v));
        }
        {
            std::vector<int> v;
            EXPECT(true == all(v));
        }
    },

    CASE("any()")
    {
        using ken3::pyfunc::any;

        {
            int a[3] = {0, 0, 0};
            EXPECT(false == any(a));
        }
        {
            int a[3] = {1, -3, 0};
            EXPECT(true == any(a));
        }
        {
            std::array<int, 3> a = {0, 0, 0};
            EXPECT(false == any(a));
        }
        {
            std::array<int, 3> a = {0, -3, 0};
            EXPECT(true == any(a));
        }
        {
            std::list<int> l = {0, 0, 0};
            EXPECT(false == any(l));
        }
        {
            std::set<int> s = {1, -3, 0};
            EXPECT(true == any(s));
        }
        {
            std::string s = "BbA";
            s.at(0) = '\0';
            s.at(1) = '\0';
            s.at(2) = '\0';
            EXPECT(false == any(s));
        }
        {
            std::string s = "BbA";
            s.at(0) = '\0';
            EXPECT(true == any(s));
        }
        {
            struct always_true {
                operator bool(void) const {
                    return true;
                }
            };
            always_true a[3];
            EXPECT(true == any(a));
        }
        {
            struct always_false {
                operator bool(void) const {
                    return false;
                }
            };
            always_false a[3];
            EXPECT(false == any(a));
        }
        {
            bool a[3] = {false, false, false};
            EXPECT(false == any(a));
        }
        {
            bool a[3] = {true, false, true};
            EXPECT(true == any(a));
        }
        {
            std::vector<bool> v = {false, false, false};
            EXPECT(false == any(v));
        }
        {
            std::vector<bool> v = {true, true, true};
            EXPECT(true == any(v));
        }
        {
            double a[3] = {0.0, 0.0, 0.0};
            EXPECT(false == any(a));
        }
        {
            double a[3] = {2.0, 3.0, 4.0};
            EXPECT(true == any(a));
        }
        {
            std::vector<double> v = {0.0, 0.0, 0.0};
            EXPECT(false == any(v));
        }
        {
            std::vector<double> v = {2.0, 0.0, 4.0};
            EXPECT(true == any(v));
        }
        {
            std::vector<int> v = {0};
            EXPECT(false == any(v));
        }
        {
            std::vector<int> v = {1};
            EXPECT(true == any(v));
        }
        {
            std::vector<int> v;
            EXPECT(false == any(v));
        }
    },

    CASE("sum() with one argument")
    {
        using ken3::pyfunc::sum;

        {
            int a[4] = {1, 3, 5, 7};
            EXPECT(16 == sum(a));
        }
        {
            std::vector<int> v = {1, 3, 5, 7, 0};
            EXPECT(16 == sum(v));
        }
        {
            std::list<int> l = {1, 7, 5, 3};
            EXPECT(16 == sum(l));
        }
        {
            std::vector<double> v = {1.0, 2.5, 3.5, 4.5};
            EXPECT(11.5 == sum(v));
            EXPECT((std::is_same<double, decltype(sum(v))>::value));
        }
        {
            std::vector<int> v = {11};
            EXPECT(11 == sum(v));
        }
        {
            std::vector<int> v = {};
            EXPECT(0 == sum(v));
        }
        {
            int a[4] = {1, 3, 5, 7};
            EXPECT((std::is_same<int, decltype(sum(a))>::value));
        }
        {
            std::vector<double> v = {};
            EXPECT(0.0 == sum(v));
            EXPECT((std::is_same<double, decltype(sum(v))>::value));
        }
    },

    CASE("sum() with two arguments")
    {
        using ken3::pyfunc::sum;

        {
            int a[4] = {1, 3, 5, 7};
            EXPECT(26 == sum(a, 10));
        }
        {
            std::vector<int> v = {1, 3, 5, 7, 0};
            EXPECT(6 == sum(v, -10));
        }
        {
            std::list<int> l = {1, 7, 5, 3};
            EXPECT(26 == sum(l, 10));
        }
        {
            double d[3] = {1.0, 2.5, 3.5};
            EXPECT(7.5 == sum(d, 0.5));
            EXPECT((std::is_same<double, decltype(sum(d, 0.5))>::value));
        }
        {
            std::vector<double> v = {1.0, 2.5, 3.5};
            EXPECT(7.5 == sum(v, 0.5));
            EXPECT((std::is_same<double, decltype(sum(v, 0.5))>::value));
        }
        {
            std::string s[4] = {"Hello", " ", "World", "!"};
            EXPECT("Hello World!" == sum(s, ""));
        }
        {
            std::string s[3] = {" ", "World", "!"};
            EXPECT("Hello World!" == sum(s, "Hello"));
            EXPECT((std::is_same<std::string, decltype(sum(s, "Hello"))>::value));
        }
        {
            std::complex<double> c[3] = {{1.0, -1.0}, {2.0, -2.0}, {10.0, -3.0}};
            EXPECT(std::complex<double>(13.0, -6.0) == sum(c, std::complex<double>()));
        }
        {
            std::complex<double> c[3] = {{1.0, -1.0}, {2.0, -2.0}, {10.0, -3.0}};
            EXPECT(std::complex<double>(23.0, 4.0) == sum(c, std::complex<double>(10.0, 10.0)));
        }
        {
            std::vector<int> v = {11};
            EXPECT(13 == sum(v, 2));
        }
        {
            std::vector<int> v = {};
            EXPECT(2 == sum(v, 2));
            EXPECT((std::is_same<int, decltype(sum(v, 2))>::value));
        }
        {
            std::vector<double> v = {};
            EXPECT(2.0 == sum(v, 2));
            EXPECT((std::is_same<double, decltype(sum(v, 2))>::value));
        }
    },

    CASE("reduce() with two arguments")
    {
        using ken3::pyfunc::reduce;

        {
            std::vector<int> v{1, 2, 3, 4};
            EXPECT(10 == reduce(std::plus<int>(), v));
        }
        {
            std::vector<int> v{1, 2, 3, 4};
            EXPECT(24 == reduce(std::multiplies<int>(), v));
        }
        {
            std::vector<double> v{1.25, 2.25, 3.25, 4.25};
            EXPECT(11.0 == reduce(std::plus<double>(), v));
        }
        {
            std::vector<double> v{1.0, 2.5, 3.0, 4.0};
            EXPECT(30.0 == reduce(std::multiplies<double>(), v));
        }
        {
            std::vector<std::string> v{"Hello", " ", "World", "!"};
            EXPECT("Hello World!" == reduce(std::plus<std::string>(), v));
        }
        {
            auto digit_plus = [](int i1, int i2) -> int {
                return i1 * 10 + i2;
            };
            std::vector<int> v{1, 2, 3, 4};
            EXPECT(1234 == reduce(digit_plus, v));
        }
        {
            auto reverse_plus = [](const std::string& s1, const std::string& s2) -> std::string {
                return s2 + s1;
            };
            std::vector<std::string> v{"Hello", " ", "World", "!"};
            EXPECT("!World Hello" == reduce(reverse_plus, v));
        }
        {
            std::vector<int> v;
            EXPECT_THROWS_AS(reduce(std::plus<int>(), v), ken3::pyfunc::TypeError);
        }
        {
            std::vector<int> v;
            EXPECT_THROWS_AS(reduce(std::multiplies<int>(), v), ken3::pyfunc::TypeError);
        }
        {
            std::vector<int> v{1, 2, 3, 4};
            EXPECT((std::is_same<int, decltype(reduce(std::multiplies<int>(), v))>::value));
        }
        {
            std::vector<double> v{1.25, 2.25, 3.25, 4.25};
            EXPECT((std::is_same<double, decltype(reduce(std::multiplies<double>(), v))>::value));
        }
        {
            std::vector<std::string> v{"Hello", " ", "World", "!"};
            EXPECT((std::is_same<std::string, decltype(reduce(std::multiplies<std::string>(), v))>::value));
        }
    },

    CASE("reduce() with three arguments")
    {
        using ken3::pyfunc::reduce;

        {
            std::vector<int> v{1, 2, 3, 4};
            EXPECT(15 == reduce(std::plus<int>(), v, 5));
        }
        {
            std::vector<int> v{1, 2, 3, 4};
            EXPECT(120 == reduce(std::multiplies<int>(), v, 5));
        }
        {
            std::vector<double> v{1.25, 2.25, 3.25, 4.25};
            EXPECT(16.25 == reduce(std::plus<double>(), v, 5.25));
        }
        {
            std::vector<double> v{1.0, 2.5, 3.0, 4.0};
            EXPECT(150.0 == reduce(std::multiplies<double>(), v, 5.0));
        }
        {
            std::vector<std::string> v{" ", "World", "!"};
            EXPECT("Hello World!" == reduce(std::plus<std::string>(), v, std::string("Hello")));
        }
        {
            auto digit_plus = [](int i1, int i2) -> int {
                return i1 * 10 + i2;
            };
            std::vector<int> v{2, 3, 4};
            EXPECT(1234 == reduce(digit_plus, v, 1));
        }
        {
            auto reverse_plus = [](const std::string& s1, const std::string& s2) -> std::string {
                return s2 + s1;
            };
            std::vector<std::string> v{" ", "World", "!"};
            EXPECT("!World Hello" == reduce(reverse_plus, v, std::string("Hello")));
        }
        {
            std::vector<int> v;
            EXPECT(5 == reduce(std::plus<int>(), v, 5));
        }
        {
            std::vector<int> v;
            EXPECT(5 == reduce(std::multiplies<int>(), v, 5));
        }
        {
            std::vector<int> v{1, 2, 3, 4};
            EXPECT((std::is_same<int, decltype(reduce(std::multiplies<int>(), v, 0))>::value));
        }
        {
            std::vector<double> v{1.25, 2.25, 3.25, 4.25};
            EXPECT((std::is_same<double, decltype(reduce(std::multiplies<double>(), v, 0))>::value));
        }
        {
            std::vector<std::string> v{" ", "World", "!"};
            EXPECT((std::is_same<std::string, decltype(reduce(std::multiplies<std::string>(), v, "Hello"))>::value));
        }
    },


    CASE("map() with three arguments")
    {
        using ken3::pyfunc::map;

        {
            auto exp2 = [](int i) -> int {
                return i * i;
            };
            std::vector<int> v{1, 2, 3, 4};
            EXPECT((std::vector<int>{1, 4, 9, 16} == map(exp2, v)));
        }
        {
            auto exp2 = [](int i) -> int {
                return i * i;
            };
            std::list<int> v{1, 2, 3, 4};
            EXPECT((std::list<int>{1, 4, 9, 16} == map(exp2, v)));
        }
        {
            auto exp2 = [](double d) -> double {
                return d * d;
            };
            std::vector<double> v{2.5};
            EXPECT((std::vector<double>{6.25} == map(exp2, v)));
        }
        {
            std::string s = "aABbCcdD";
            EXPECT(std::string("AABBCCDD") == map(::toupper, s));
        }
        {
            auto exp2 = [](int i) -> int {
                return i * i;
            };
            std::vector<int> v{1, 2, 3, 4};
            EXPECT((std::is_same<std::vector<int>, decltype(map(exp2, v))>::value));
        }
        {
            auto exp2 = [](int i) -> int {
                return i * i;
            };
            const std::vector<int> v{1, 2, 3, 4};
            EXPECT((std::is_same<std::vector<int>, decltype(map(exp2, v))>::value));
        }
        {
            std::string s = "aABbCcdD";
            EXPECT((std::is_same<std::string, decltype(map(::toupper, s))>::value));
        }
        {
            const std::string s = "aABbCcdD";
            EXPECT((std::is_same<std::string, decltype(map(::toupper, s))>::value));
        }
    },



    CASE("filter() with three arguments")
    {
        using ken3::pyfunc::filter;

        {
            auto f = [](int i) -> bool {
                return static_cast<bool>(i);
            };
            std::vector<int> v{1, 0, 3, 0};
            EXPECT((std::vector<int>{1, 3} == filter(f, v)));
        }
        {
            auto f = [](int i) -> bool {
                return static_cast<bool>(i);
            };
            std::list<int> v{1, 0, 3, 0};
            EXPECT((std::list<int>{1, 3} == filter(f, v)));
        }
        {
            auto f = [](double d) -> bool {
                return static_cast<bool>(d);
            };
            std::vector<double> v{0.0, 2.5};
            EXPECT((std::vector<double>{2.5} == filter(f, v)));
        }
        {
            auto f = [](char c) -> bool {
                return static_cast<char>(c);
            };
            std::string s = "ABCD";
            s[2] = '\0';
            EXPECT(std::string("ABD") == filter(f, s));
        }
        {
            auto f = [](int i) -> bool {
                return static_cast<bool>(i);
            };
            std::vector<int> v{1, 0, 3, 0};
            EXPECT((std::is_same<std::vector<int>, decltype(filter(f, v))>::value));
        }
        {
            auto f = [](int i) -> bool {
                return static_cast<bool>(i);
            };
            const std::vector<int> v{1, 0, 3, 0};
            EXPECT((std::is_same<std::vector<int>, decltype(filter(f, v))>::value));
        }
        {
            auto f = [](char c) -> bool {
                return static_cast<char>(c);
            };
            std::string s = "ABCD";
            s[2] = '\0';
            EXPECT((std::is_same<std::string, decltype(filter(f, s))>::value));
        }
        {
            auto f = [](char c) -> bool {
                return static_cast<char>(c);
            };
            std::string tmp = "ABCD";
            tmp[2] = '\0';
            const std::string s = tmp;
            EXPECT((std::is_same<std::string, decltype(filter(f, s))>::value));
        }
    },



};

int main(int argc, char* argv[])
{
    return lest::run(specification, argc, argv);
}
/////////////////////////////////////////////////////////////////////////////

