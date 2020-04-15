/**
 * @file    unittest/fraction_test.cpp
 * @brief   Testing ken3::fraction using lest. 
 * @author  toda
 * @date    2020-01-04
 * @version 0.1.0
 * @remark  the target is C++11 or more
 */

#include <sstream>
#include "ken3/fraction.hpp"
#include "unittest/lest.hpp"

const lest::test specification[] =
{

    CASE("default constructor")
    {
        using ken3::fraction;
        using pair_type = ken3::fraction::pair_type;

        EXPECT(pair_type(0, 1) == (fraction{}()));
    },

    CASE("two arguments constructor")
    {
        using ken3::fraction;
        using pair_type = ken3::fraction::pair_type;
        using limit = std::numeric_limits<ken3::fraction::int_type>;

        EXPECT(pair_type(1, 2) == (fraction{1, 2}()));
        EXPECT(pair_type(7, 15) == (fraction{14, 30}()));
        EXPECT(pair_type(15, 7) == (fraction{30, 14}()));
        EXPECT(pair_type(0, 1) == (fraction{0, 1}()));
        EXPECT(pair_type(0, 1) == (fraction{0, 100}()));
        EXPECT(pair_type(0, 1) == (fraction{0, -1}()));
        EXPECT(pair_type(10, 1) == (fraction{10, 1}()));
        EXPECT(pair_type(5, 1) == (fraction{10, 2}()));
        EXPECT(pair_type(-10, 1) == (fraction{10, -1}()));
        EXPECT(pair_type(-5, 1) == (fraction{10, -2}()));
        EXPECT(pair_type(-10, 1) == (fraction{-10, 1}()));
        EXPECT(pair_type(-5, 1) == (fraction{-10, 2}()));
        EXPECT(pair_type(10, 1) == (fraction{-10, -1}()));
        EXPECT(pair_type(5, 1) == (fraction{-10, -2}()));
        EXPECT_THROWS_AS((fraction{0, 0}), std::runtime_error);
        EXPECT_THROWS_AS((fraction{10, 0}), std::runtime_error);
        EXPECT_THROWS_AS((fraction{-10, 0}), std::runtime_error);
        EXPECT(pair_type(limit::max(), 2) == (fraction{limit::max(), 2}()));
        EXPECT(pair_type(limit::min(), 1) == (fraction{limit::min(), 1})());
        EXPECT_THROWS_AS((fraction{limit::min(), -1}), std::overflow_error);
        EXPECT_THROWS_AS((fraction{1, limit::min()}), std::overflow_error);
        EXPECT_THROWS_AS((fraction{-1, limit::min()}), std::overflow_error);
        EXPECT(pair_type(limit::min() / -2, 1) == (fraction{limit::min(), -2})());
    },

    CASE("operator==")
    {
        using ken3::fraction;
        using limit = std::numeric_limits<ken3::fraction::int_type>;

        EXPECT(true == ((fraction{}) == (fraction{})));
        EXPECT(true == ((fraction{1, 2}) == (fraction{1, 2})));
        EXPECT(false == ((fraction{1, 2}) == (fraction{1, 3})));
        EXPECT(false == ((fraction{1, 2}) == (fraction{2, 1})));
        EXPECT(true == ((fraction{1, 2}) == (fraction{20, 40})));
        EXPECT(true == ((fraction{1, 2}) == (fraction{-20, -40})));
        EXPECT(false == ((fraction{1, 2}) == (fraction{-20, 40})));
        EXPECT(false == ((fraction{1, 2}) == (fraction{20, -40})));
        EXPECT(true == ((fraction{limit::min(), limit::max()}) == (fraction{limit::min(), limit::max()})));
    },

    CASE("operator!=")
    {
        using ken3::fraction;
        using limit = std::numeric_limits<ken3::fraction::int_type>;

        EXPECT(false == ((fraction{}) != (fraction{})));
        EXPECT(false == ((fraction{1, 2}) != (fraction{1, 2})));
        EXPECT(true == ((fraction{1, 2}) != (fraction{1, 3})));
        EXPECT(true == ((fraction{1, 2}) != (fraction{2, 1})));
        EXPECT(false == ((fraction{1, 2}) != (fraction{20, 40})));
        EXPECT(false == ((fraction{1, 2}) != (fraction{-20, -40})));
        EXPECT(true == ((fraction{1, 2}) != (fraction{-20, 40})));
        EXPECT(true == ((fraction{1, 2}) != (fraction{20, -40})));
        EXPECT(false == ((fraction{limit::min(), limit::max()}) != (fraction{limit::min(), limit::max()})));
    },

    CASE("operator<")
    {
        using ken3::fraction;
        using limit = std::numeric_limits<ken3::fraction::int_type>;

        EXPECT(false == ((fraction{}) < (fraction{})));
        EXPECT(false == ((fraction{1, 2}) < (fraction{1, 2})));
        EXPECT(true == ((fraction{1, 3}) < (fraction{1, 2})));
        EXPECT(true == ((fraction{1, -3}) < (fraction{1, 2})));
        EXPECT(false == ((fraction{1, 3}) < (fraction{-1, 2})));
        EXPECT(false == ((fraction{1, -3}) < (fraction{-1, 2})));
        EXPECT(true == ((fraction{1, 3}) < (fraction{1, 2})));
        EXPECT(true == ((fraction{2, limit::max()}) < (fraction{3, limit::max() - 1})));
        EXPECT(true == ((fraction{limit::max() / 2 + 1, limit::max()}) < (fraction{limit::max() / 2 + 2, limit::max() - 1})));
        EXPECT(false == ((fraction{limit::max() - 10, limit::max()}) < (fraction{limit::max() - 20, limit::max() - 1})));
        EXPECT(false == ((fraction{limit::min(), limit::max()}) < (fraction{limit::min(), limit::max()})));
        EXPECT(true == ((fraction{limit::min() + 10, limit::max()}) < (fraction{limit::min() + 20, limit::max() - 1})));
    },

    CASE("operator>")
    {
        using ken3::fraction;
        using limit = std::numeric_limits<ken3::fraction::int_type>;

        EXPECT(false == ((fraction{}) > (fraction{})));
        EXPECT(false == ((fraction{1, 2}) > (fraction{1, 2})));
        EXPECT(false == ((fraction{1, 3}) > (fraction{1, 2})));
        EXPECT(false == ((fraction{1, -3}) > (fraction{1, 2})));
        EXPECT(true == ((fraction{1, 3}) > (fraction{-1, 2})));
        EXPECT(true == ((fraction{1, -3}) > (fraction{-1, 2})));
        EXPECT(false == ((fraction{1, 3}) > (fraction{1, 2})));
        EXPECT(false == ((fraction{2, limit::max()}) > (fraction{3, limit::max() - 1})));
        EXPECT(false == ((fraction{limit::max() / 2 + 1, limit::max()}) > (fraction{limit::max() / 2 + 2, limit::max() - 1})));
        EXPECT(true == ((fraction{limit::max() - 10, limit::max()}) > (fraction{limit::max() - 20, limit::max() - 1})));
        EXPECT(false == ((fraction{limit::min(), limit::max()}) > (fraction{limit::min(), limit::max()})));
        EXPECT(false == ((fraction{limit::min() + 10, limit::max()}) > (fraction{limit::min() + 20, limit::max() - 1})));
    },

    CASE("operator<=")
    {
        using ken3::fraction;
        using limit = std::numeric_limits<ken3::fraction::int_type>;

        EXPECT(true == ((fraction{}) <= (fraction{})));
        EXPECT(true == ((fraction{1, 2}) <= (fraction{1, 2})));
        EXPECT(true == ((fraction{1, 3}) <= (fraction{1, 2})));
        EXPECT(true == ((fraction{1, -3}) <= (fraction{1, 2})));
        EXPECT(false == ((fraction{1, 3}) <= (fraction{-1, 2})));
        EXPECT(false == ((fraction{1, -3}) <= (fraction{-1, 2})));
        EXPECT(true == ((fraction{1, 3}) <= (fraction{1, 2})));
        EXPECT(true == ((fraction{2, limit::max()}) <= (fraction{3, limit::max() - 1})));
        EXPECT(true == ((fraction{limit::max() / 2 + 1, limit::max()}) <= (fraction{limit::max() / 2 + 2, limit::max() - 1})));
        EXPECT(false == ((fraction{limit::max() - 10, limit::max()}) <= (fraction{limit::max() - 20, limit::max() - 1})));
        EXPECT(true == ((fraction{limit::min(), limit::max()}) <= (fraction{limit::min(), limit::max()})));
        EXPECT(true == ((fraction{limit::min() + 10, limit::max()}) <= (fraction{limit::min() + 20, limit::max() - 1})));
    },

    CASE("operator>=")
    {
        using ken3::fraction;
        using limit = std::numeric_limits<ken3::fraction::int_type>;

        EXPECT(true == ((fraction{}) >= (fraction{})));
        EXPECT(true == ((fraction{1, 2}) >= (fraction{1, 2})));
        EXPECT(false == ((fraction{1, 3}) >= (fraction{1, 2})));
        EXPECT(false == ((fraction{1, -3}) >= (fraction{1, 2})));
        EXPECT(true == ((fraction{1, 3}) >= (fraction{-1, 2})));
        EXPECT(true == ((fraction{1, -3}) >= (fraction{-1, 2})));
        EXPECT(false == ((fraction{1, 3}) >= (fraction{1, 2})));
        EXPECT(false == ((fraction{2, limit::max()}) >= (fraction{3, limit::max() - 1})));
        EXPECT(false == ((fraction{limit::max() / 2 + 1, limit::max()}) >= (fraction{limit::max() / 2 + 2, limit::max() - 1})));
        EXPECT(true == ((fraction{limit::max() - 10, limit::max()}) >= (fraction{limit::max() - 20, limit::max() - 1})));
        EXPECT(true == ((fraction{limit::min(), limit::max()}) >= (fraction{limit::min(), limit::max()})));
        EXPECT(false == ((fraction{limit::min() + 10, limit::max()}) >= (fraction{limit::min() + 20, limit::max() - 1})));
    },

    CASE("operator+=")
    {
        using ken3::fraction;
        using pair_type = ken3::fraction::pair_type;
        using limit = std::numeric_limits<ken3::fraction::int_type>;

        EXPECT(pair_type(0, 1) == (fraction{} += fraction{})());
        EXPECT(pair_type(1, 1) == (fraction{3, 10} += fraction{7, 10})());
        EXPECT(pair_type(1, 5) == (fraction{1, 15} += fraction{2, 15})());
        EXPECT(pair_type(-1, 15) == (fraction{1, 15} += fraction{2, -15})());
        EXPECT(pair_type(limit::max() / 2 + limit::max() / 2, 1) == (fraction{limit::max() / 2, 1} += fraction{limit::max() / 2, 1})());
        EXPECT_THROWS_AS((fraction{limit::max() / 2 + 1, 1} += fraction{limit::max() / 2 + 1, 1}), std::overflow_error);
        EXPECT_THROWS_AS((fraction{limit::min() / 2 - 1, 1} += fraction{limit::min() / 2 - 1, 1}), std::overflow_error);
    },

    CASE("operator-=")
    {
        using ken3::fraction;
        using pair_type = ken3::fraction::pair_type;
        using limit = std::numeric_limits<ken3::fraction::int_type>;

        EXPECT(pair_type(0, 1) == (fraction{} -= fraction{})());
        EXPECT(pair_type(-1, 1) == (fraction{-3, 10} -= fraction{7, 10})());
        EXPECT(pair_type(-1, 5) == (fraction{1, 15} -= fraction{4, 15})());
        EXPECT(pair_type(1, 3) == (fraction{1, 15} -= fraction{4, -15})());
        EXPECT(pair_type(limit::max() / -2 + limit::max() / -2, 1) == (fraction{limit::max() / -2, 1} -= fraction{limit::max() / 2, 1})());
        EXPECT_THROWS_AS((fraction{limit::max() / 2 + 1, 1} -= fraction{limit::max() / -2 - 1, 1}), std::overflow_error);
        EXPECT_THROWS_AS((fraction{limit::min() / 2 - 1, 1} -= fraction{limit::min() / -2 + 1, 1}), std::overflow_error);
    },

    CASE("operator*=")
    {
        using ken3::fraction;
        using pair_type = ken3::fraction::pair_type;
        using limit = std::numeric_limits<ken3::fraction::int_type>;

        EXPECT(pair_type(0, 1) == (fraction{} *= fraction{})());
        EXPECT(pair_type(-21, 100) == (fraction{-3, 10} *= fraction{7, 10})());
        EXPECT(pair_type(7, 50) == (fraction{-3, 10} *= fraction{-7, 15})());
        EXPECT(pair_type(1, 99 * (limit::max() / 100)) == (fraction{100, 99} *= fraction{1, limit::max() - limit::max() % 100})());
        EXPECT(pair_type(limit::min(), 1) == (fraction{limit::min(), 3} *= fraction{3, 1})());
        EXPECT_THROWS_AS((fraction{1, limit::min() / 2 - 1} *= fraction{1, 3}), std::overflow_error);
        EXPECT_THROWS_AS((fraction{limit::min(), 1} *= fraction{-1, 1}), std::overflow_error);
    },

    CASE("operator/=")
    {
        using ken3::fraction;
        using pair_type = ken3::fraction::pair_type;
        using limit = std::numeric_limits<ken3::fraction::int_type>;

        EXPECT_THROWS_AS((fraction{} /= fraction{}), std::runtime_error);
        EXPECT_THROWS_AS((fraction{1, 1} /= fraction{0, 3}), std::runtime_error);
        EXPECT(pair_type(0, 1) == (fraction{} /= fraction{5, 3})());
        EXPECT(pair_type(-21, 100) == (fraction{-3, 10} /= fraction{10, 7})());
        EXPECT(pair_type(7, 50) == (fraction{-3, 10} /= fraction{15, -7})());
        EXPECT(pair_type(1, 99 * (limit::max() / 100)) == (fraction{100, 99} /= fraction{limit::max() - limit::max() % 100, 1})());
        EXPECT(pair_type(limit::min(), 1) == (fraction{limit::min(), 3} /= fraction{1, 3})());
        EXPECT_THROWS_AS((fraction{limit::max() / 2 + 1, 1} /= fraction{1, 3}), std::overflow_error);
        EXPECT_THROWS_AS((fraction{1, limit::min() / 2 - 1} /= fraction{3, 1}), std::overflow_error);
        EXPECT_THROWS_AS((fraction{limit::min(), 1} /= fraction{-1, 1}), std::overflow_error);
    },

    CASE("operator+")
    {
        using ken3::fraction;
        using pair_type = ken3::fraction::pair_type;
        using limit = std::numeric_limits<ken3::fraction::int_type>;

        EXPECT(pair_type(0, 1) == (fraction{} + fraction{})());
        EXPECT(pair_type(1, 1) == (fraction{3, 10} + fraction{7, 10})());
        EXPECT(pair_type(1, 5) == (fraction{1, 15} + fraction{2, 15})());
        EXPECT(pair_type(-1, 15) == (fraction{1, 15} + fraction{2, -15})());
        EXPECT(pair_type(limit::max() / 2 + limit::max() / 2, 1) == (fraction{limit::max() / 2, 1} + fraction{limit::max() / 2, 1})());
        EXPECT_THROWS_AS((fraction{limit::max() / 2 + 1, 1} + fraction{limit::max() / 2 + 1, 1}), std::overflow_error);
        EXPECT_THROWS_AS((fraction{limit::min() / 2 - 1, 1} + fraction{limit::min() / 2 - 1, 1}), std::overflow_error);
    },

    CASE("operator-")
    {
        using ken3::fraction;
        using pair_type = ken3::fraction::pair_type;
        using limit = std::numeric_limits<ken3::fraction::int_type>;

        EXPECT(pair_type(0, 1) == (fraction{} - fraction{})());
        EXPECT(pair_type(-1, 1) == (fraction{-3, 10} - fraction{7, 10})());
        EXPECT(pair_type(-1, 5) == (fraction{1, 15} - fraction{4, 15})());
        EXPECT(pair_type(1, 3) == (fraction{1, 15} - fraction{4, -15})());
        EXPECT(pair_type(limit::max() / -2 + limit::max() / -2, 1) == (fraction{limit::max() / -2, 1} - fraction{limit::max() / 2, 1})());
        EXPECT_THROWS_AS((fraction{limit::max() / 2 + 1, 1} - fraction{limit::max() / -2 - 1, 1}), std::overflow_error);
        EXPECT_THROWS_AS((fraction{limit::min() / 2 - 1, 1} - fraction{limit::min() / -2 + 1, 1}), std::overflow_error);
    },

    CASE("operator*")
    {
        using ken3::fraction;
        using pair_type = ken3::fraction::pair_type;
        using limit = std::numeric_limits<ken3::fraction::int_type>;

        EXPECT(pair_type(0, 1) == (fraction{} * fraction{})());
        EXPECT(pair_type(-21, 100) == (fraction{-3, 10} * fraction{7, 10})());
        EXPECT(pair_type(7, 50) == (fraction{-3, 10} * fraction{-7, 15})());
        EXPECT(pair_type(1, 99 * (limit::max() / 100)) == (fraction{100, 99} * fraction{1, limit::max() - limit::max() % 100})());
        EXPECT(pair_type(limit::min(), 1) == (fraction{limit::min(), 3} * fraction{3, 1})());
        EXPECT_THROWS_AS((fraction{1, limit::min() / 2 - 1} * fraction{1, 3}), std::overflow_error);
        EXPECT_THROWS_AS((fraction{limit::min(), 1} * fraction{-1, 1}), std::overflow_error);
    },

    CASE("operator/")
    {
        using ken3::fraction;
        using pair_type = ken3::fraction::pair_type;
        using limit = std::numeric_limits<ken3::fraction::int_type>;

        EXPECT_THROWS_AS((fraction{} / fraction{}), std::runtime_error);
        EXPECT_THROWS_AS((fraction{1, 1} / fraction{0, 3}), std::runtime_error);
        EXPECT(pair_type(0, 1) == (fraction{} / fraction{5, 3})());
        EXPECT(pair_type(-21, 100) == (fraction{-3, 10} / fraction{10, 7})());
        EXPECT(pair_type(7, 50) == (fraction{-3, 10} / fraction{15, -7})());
        EXPECT(pair_type(1, 99 * (limit::max() / 100)) == (fraction{100, 99} / fraction{limit::max() - limit::max() % 100, 1})());
        EXPECT(pair_type(limit::min(), 1) == (fraction{limit::min(), 3} / fraction{1, 3})());
        EXPECT_THROWS_AS((fraction{limit::max() / 2 + 1, 1} / fraction{1, 3}), std::overflow_error);
        EXPECT_THROWS_AS((fraction{1, limit::min() / 2 - 1} / fraction{3, 1}), std::overflow_error);
        EXPECT_THROWS_AS((fraction{limit::min(), 1} / fraction{-1, 1}), std::overflow_error);
    },

    CASE("operator int_type()")
    {
        using ken3::fraction;
        using int_type = ken3::fraction::int_type;

        EXPECT(0 == int_type(fraction{}));
        EXPECT(0 == int_type(fraction{1, 2}));
        EXPECT(1 == int_type(fraction{2, 2}));
        EXPECT(1 == int_type(fraction{3, 2}));
        EXPECT(2 == int_type(fraction{4, 2}));
        EXPECT(-1 == int_type(fraction{2, -2}));
        EXPECT(-1 == int_type(fraction{-3, 2}));
        EXPECT(2 == int_type(fraction{-4, -2}));
    },

    CASE("operator float()")
    {
        using ken3::fraction;

        EXPECT(0.0f == float(fraction{}));
        EXPECT(0.5f == float(fraction{1, 2}));
        EXPECT(1.0f == float(fraction{2, 2}));
        EXPECT(1.5f == float(fraction{3, 2}));
        EXPECT(2.0f == float(fraction{4, 2}));
        EXPECT(-1.0f == float(fraction{2, -2}));
        EXPECT(-1.5f == float(fraction{-3, 2}));
        EXPECT(2.0f == float(fraction{-4, -2}));
    },

    CASE("operator double()")
    {
        using ken3::fraction;

        EXPECT(0.0 == double(fraction{}));
        EXPECT(0.5 == double(fraction{1, 2}));
        EXPECT(1.0 == double(fraction{2, 2}));
        EXPECT(1.5 == double(fraction{3, 2}));
        EXPECT(2.0 == double(fraction{4, 2}));
        EXPECT(-1.0 == double(fraction{2, -2}));
        EXPECT(-1.5 == double(fraction{-3, 2}));
        EXPECT(2.0 == double(fraction{-4, -2}));
    },

    CASE("operator long double()")
    {
        using ken3::fraction;

        EXPECT(0.0L == (long double)(fraction{}));
        EXPECT(0.5L == (long double)(fraction{1, 2}));
        EXPECT(1.0L == (long double)(fraction{2, 2}));
        EXPECT(1.5L == (long double)(fraction{3, 2}));
        EXPECT(2.0L == (long double)(fraction{4, 2}));
        EXPECT(-1.0L == (long double)(fraction{2, -2}));
        EXPECT(-1.5L == (long double)(fraction{-3, 2}));
        EXPECT(2.0L == (long double)(fraction{-4, -2}));
    },

    CASE("operator >>")
    {
        using ken3::fraction;
        using pair_type = ken3::fraction::pair_type;
        using limit = std::numeric_limits<ken3::fraction::int_type>;

        {
            fraction f{2, 3};
            std::stringstream ss;
            ss >> f;
            EXPECT(pair_type(2, 3) == f());
        }

        {
            fraction f{2, 3};
            std::stringstream ss("");
            ss >> f;
            EXPECT(pair_type(2, 3) == f());
        }

        {
            fraction f{};
            std::stringstream ss("2/3");
            ss >> f;
            EXPECT(pair_type(2, 3) == f());
        }

        {
            fraction f{};
            std::stringstream ss("4/6");
            ss >> f;
            EXPECT(pair_type(2, 3) == f());
        }

        {
            fraction f{};
            std::stringstream ss("2/3A");
            ss >> f;
            EXPECT(pair_type(2, 3) == f());
            EXPECT(true == ss.good());
        }

        {
            fraction f{};
            std::stringstream ss("2a3");
            ss >> f;
            EXPECT(pair_type(0, 1) == f());
        }

        {
            fraction f{};
            std::stringstream ss("2/E");
            ss >> f;
            EXPECT(pair_type(0, 1) == f());
        }

        {
            fraction f{};
            std::stringstream ss("2/");
            ss >> f;
            EXPECT(pair_type(0, 1) == f());
        }

        {
            fraction f{};
            std::stringstream ss("2");
            ss >> f;
            EXPECT(pair_type(0, 1) == f());
        }

        {
            fraction f{};
            std::stringstream ss;
            ss << limit::min() << "/" << 1;
            ss >> f;
            EXPECT(pair_type(limit::min(), 1) == f());
        }

        {
            fraction f{};
            std::stringstream ss;
            ss << 2 << "/" << limit::max();
            ss >> f;
            EXPECT(pair_type(2, limit::max()) == f());
        }
    },

    CASE("operator <<")
    {
        using ken3::fraction;

        {
            fraction f{};
            std::stringstream ss;
            ss << f;
            EXPECT(std::string("0/1") == ss.str());
        }
        {
            fraction f{6, -3};
            std::stringstream ss;
            ss << f;
            EXPECT(std::string("-2/1") == ss.str());
        }
    },

    CASE("swap()")
    {
        using ken3::fraction;
        using pair_type = ken3::fraction::pair_type;
        using limit = std::numeric_limits<ken3::fraction::int_type>;

        {
            fraction f1{};
            fraction f2{};
            f1.swap(f2);
            EXPECT(pair_type(0, 1) == f1());
            EXPECT(pair_type(0, 1) == f2());
        }
        {
            fraction f1{1, 2};
            fraction f2{-9, 3};
            f1.swap(f2);
            EXPECT(pair_type(-3, 1) == f1());
            EXPECT(pair_type(1, 2) == f2());
        }
        {
            fraction f1{limit::min(), 1};
            fraction f2{1, limit::max()};
            f1.swap(f2);
            EXPECT(pair_type(1, limit::max()) == f1());
            EXPECT(pair_type(limit::min(), 1) == f2());
        }
    },

    CASE("operator()")
    {
        using ken3::fraction;
        using pair_type = ken3::fraction::pair_type;
        using limit = std::numeric_limits<ken3::fraction::int_type>;

        EXPECT(pair_type(0, 1) == (fraction{}()));
        EXPECT(pair_type(1, 2) == (fraction{1, 2}()));
        EXPECT(pair_type(7, 15) == (fraction{14, 30}()));
        EXPECT(pair_type(15, 7) == (fraction{30, 14}()));
        EXPECT(pair_type(0, 1) == (fraction{0, 1}()));
        EXPECT(pair_type(0, 1) == (fraction{0, 100}()));
        EXPECT(pair_type(0, 1) == (fraction{0, -1}()));
        EXPECT(pair_type(10, 1) == (fraction{10, 1}()));
        EXPECT(pair_type(5, 1) == (fraction{10, 2}()));
        EXPECT(pair_type(-10, 1) == (fraction{10, -1}()));
        EXPECT(pair_type(-5, 1) == (fraction{10, -2}()));
        EXPECT(pair_type(-10, 1) == (fraction{-10, 1}()));
        EXPECT(pair_type(-5, 1) == (fraction{-10, 2}()));
        EXPECT(pair_type(10, 1) == (fraction{-10, -1}()));
        EXPECT(pair_type(5, 1) == (fraction{-10, -2}()));
        EXPECT(pair_type(limit::max(), 2) == (fraction{limit::max(), 2}()));
        EXPECT(pair_type(limit::min(), 1) == (fraction{limit::min(), 1})());
        EXPECT(pair_type(limit::min() / -2, 1) == (fraction{limit::min(), -2})());
    },

    CASE("numerator()")
    {
        using ken3::fraction;
        using pair_type = ken3::fraction::pair_type;
        using limit = std::numeric_limits<ken3::fraction::int_type>;

        EXPECT(0 == (fraction{}.numerator()));
        EXPECT(1 == (fraction{1, 2}.numerator()));
        EXPECT(7 == (fraction{14, 30}.numerator()));
        EXPECT(15 == (fraction{30, 14}.numerator()));
        EXPECT(0 == (fraction{0, 1}.numerator()));
        EXPECT(0 == (fraction{0, 100}.numerator()));
        EXPECT(0 == (fraction{0, -1}.numerator()));
        EXPECT(10 == (fraction{10, 1}.numerator()));
        EXPECT(5 == (fraction{10, 2}.numerator()));
        EXPECT(-10 == (fraction{10, -1}.numerator()));
        EXPECT(-5 == (fraction{10, -2}.numerator()));
        EXPECT(-10 == (fraction{-10, 1}.numerator()));
        EXPECT(-5 == (fraction{-10, 2}.numerator()));
        EXPECT(10 == (fraction{-10, -1}.numerator()));
        EXPECT(5 == (fraction{-10, -2}.numerator()));
        EXPECT(limit::max() == (fraction{limit::max(), 2}.numerator()));
        EXPECT(limit::min() == (fraction{limit::min(), 1}.numerator)());
        EXPECT(limit::min() / -2 == (fraction{limit::min(), -2}).numerator());
    },

    CASE("denominator()")
    {
        using ken3::fraction;
        using pair_type = ken3::fraction::pair_type;
        using limit = std::numeric_limits<ken3::fraction::int_type>;

        EXPECT(1 == (fraction{}.denominator()));
        EXPECT(2 == (fraction{1, 2}.denominator()));
        EXPECT(15 == (fraction{14, 30}.denominator()));
        EXPECT(7 == (fraction{30, 14}.denominator()));
        EXPECT(1 == (fraction{0, 1}.denominator()));
        EXPECT(1 == (fraction{0, 100}.denominator()));
        EXPECT(1 == (fraction{0, -1}.denominator()));
        EXPECT(1 == (fraction{10, 1}.denominator()));
        EXPECT(1 == (fraction{10, 2}.denominator()));
        EXPECT(1 == (fraction{10, -1}.denominator()));
        EXPECT(1 == (fraction{10, -2}.denominator()));
        EXPECT(1 == (fraction{-10, 1}.denominator()));
        EXPECT(1 == (fraction{-10, 2}.denominator()));
        EXPECT(1 == (fraction{-10, -1}.denominator()));
        EXPECT(1 == (fraction{-10, -2}.denominator()));
        EXPECT(2 == (fraction{limit::max(), 2}.denominator()));
        EXPECT(1 == (fraction{limit::min(), 1}.denominator)());
        EXPECT(1 == (fraction{limit::min(), -2}.denominator)());
    },

    CASE("set()")
    {
        using ken3::fraction;
        using pair_type = ken3::fraction::pair_type;
        using limit = std::numeric_limits<ken3::fraction::int_type>;

        fraction f;

        f.set(1, 2);
        EXPECT(pair_type(1, 2) == f());
        f.set(14, 30);
        EXPECT(pair_type(7, 15) == f());
        f.set(30, 14);
        EXPECT(pair_type(15, 7) == f());
        f.set(0, 1);
        EXPECT(pair_type(0, 1) == f());
        f.set(0, 100);
        EXPECT(pair_type(0, 1) == f());
        f.set(0, -1);
        EXPECT(pair_type(0, 1) == f());
        f.set(10, 1);
        EXPECT(pair_type(10, 1) == f());
        f.set(10, 2);
        EXPECT(pair_type(5, 1) == f());
        f.set(10, -1);
        EXPECT(pair_type(-10, 1) == f());
        f.set(10, -2);
        EXPECT(pair_type(-5, 1) == f());
        f.set(-10, 1);
        EXPECT(pair_type(-10, 1) == f());
        f.set(-10, 2);
        EXPECT(pair_type(-5, 1) == f());
        f.set(-10, -1);
        EXPECT(pair_type(10, 1) == f());
        f.set(-10, -2);
        EXPECT(pair_type(5, 1) == f());
        EXPECT_THROWS_AS(f.set(0, 0), std::runtime_error);
        EXPECT_THROWS_AS(f.set(10, 0), std::runtime_error);
        EXPECT_THROWS_AS(f.set(-10, 0), std::runtime_error);
        f.set(limit::max(), 2);
        EXPECT(pair_type(limit::max(), 2) == f());
        f.set(limit::min(), 1);
        EXPECT(pair_type(limit::min(), 1) == f());
        EXPECT_THROWS_AS(f.set(limit::min(), -1), std::overflow_error);
        EXPECT_THROWS_AS(f.set(1, limit::min()), std::overflow_error);
        EXPECT_THROWS_AS(f.set(-1, limit::min()), std::overflow_error);
        f.set(limit::min() / -2, 1);
        EXPECT(pair_type(limit::min() / -2, 1) == f());
    },

    CASE("inverse()")
    {
        using ken3::fraction;
        using pair_type = ken3::fraction::pair_type;
        using limit = std::numeric_limits<ken3::fraction::int_type>;

        {
            fraction f{};
            EXPECT_THROWS_AS(f.inverse(), std::runtime_error);
        }
        {
            fraction f{1, 2};
            f.inverse();
            EXPECT(pair_type(2, 1) == f());
        }
        {
            fraction f{-1, 2};
            f.inverse();
            EXPECT(pair_type(-2, 1) == f());
        }
        {
            fraction f{2, 10};
            f.inverse();
            EXPECT(pair_type(5, 1) == f());
        }
        {
            fraction f{0, 10};
            EXPECT_THROWS_AS(f.inverse(), std::runtime_error);
        }
        {
            fraction f{limit::min(), 1};
            EXPECT_THROWS_AS(f.inverse(), std::overflow_error);
        }
        {
            fraction f{limit::min(), -2};
            f.inverse();
            EXPECT(pair_type(1, limit::min() / -2) == f());
        }
    },

};

int main(int argc, char* argv[])
{
    return lest::run(specification, argc, argv);
}
/////////////////////////////////////////////////////////////////////////////

