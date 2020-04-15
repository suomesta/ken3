/**
 * @file    ken3/fraction.cpp
 * @brief   Implementation of fraction class.
 *          fraction supports to calculate fraction based on integer.
 * @author  toda
 * @date    2019-12-13
 * @version 0.1.0
 * @remark  the target is C++11 or more.
 *
 * @note
 * Typical usage is;
 *     fraction f12(1, 2);
 *     std::cout << f12; // => "1/2"
 *     std::cout << double(f12); // => "0.5"
 *     fraction f13(1, 3);
 *     std::cout << (f12 + f13); // => "5/6"
 */

#include <cinttypes> // for std::intmax_t abs(std::intmax_t n)
#include <limits>
#include "ken3/fraction.hpp"
#include "ken3/overflow.hpp"

namespace ken3 {
namespace fraction_detail {

/**
 * @brief      check whether overflow occurs or not as a result of x + y.
 * @param[in]  x: lhs
 * @param[in]  y: rhs
 * @throw      std::overflow_error: (x + y) makes overflow.
 */
void check_overflow_add(ken3::fraction::int_type x, ken3::fraction::int_type y)
{
    if (ken3::overflow::occur_add(x, y)) {
        throw std::overflow_error("");
    }
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief      check whether overflow occurs or not as a result of x - y.
 * @param[in]  x: lhs
 * @param[in]  y: rhs
 * @throw      std::overflow_error: (x - y) makes overflow.
 */
void check_overflow_sub(ken3::fraction::int_type x, ken3::fraction::int_type y)
{
    if (ken3::overflow::occur_sub(x, y)) {
        throw std::overflow_error("");
    }
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief      check whether overflow occurs or not as a result of x * y.
 * @param[in]  x: lhs
 * @param[in]  y: rhs
 * @throw      std::overflow_error: (x * y) makes overflow.
 */
void check_overflow_mul(ken3::fraction::int_type x, ken3::fraction::int_type y)
{
    if (ken3::overflow::occur_mul(x, y)) {
        throw std::overflow_error("");
    }
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief      check whether overflow occurs or not as a result of std::abs(x).
 * @param[in]  x: value
 * @throw      std::overflow_error: std::abs(x) makes overflow.
 */
void check_overflow_abs(ken3::fraction::int_type x)
{
    if (ken3::overflow::occur_abs(x)) {
        throw std::overflow_error("");
    }
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief      calculate gcd of x and y after passing pre-coditions.
 * @param[in]  x: lhs. should be > 0
 * @param[in]  y: rhs. should be > 0
 * @return     calculated gcd.
 */
ken3::fraction::int_type gcd_impl(ken3::fraction::int_type x, ken3::fraction::int_type y) noexcept
{
    while (y != 0) {
        ken3::fraction::int_type tmp = y;
        y = x % y;
        x = tmp;
    }

    return x;
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief      calculate gcd of x and y.
 * @param[in]  x: lhs. should be from numerator. if negative, then std::abs(lhs) is used
 * @param[in]  y: rhs. should be from denominator (> 0)
 * @return     calculated gcd.
 *             if one of x or y is 0, return 1.
 *             (x=100, y=15) => (gcd=5)
 *             (x=-100, y=15) => (gcd=5)
 *             (x=0, y=15) => (gcd=1)
 *             (x=min, y=15) => (gcd=1)
 *             (x=min, y=2) => (gcd=2)
 */
ken3::fraction::int_type gcd(ken3::fraction::int_type x, ken3::fraction::int_type y) noexcept
{
    using limit = std::numeric_limits<ken3::fraction::int_type>;

    if (x == 0) {
        return 1;
    }
    else if (x == limit::min()) {
        if (x % y == 0) {
            return y;
        }
        else {
            return 1;
        }
    }
    else {
        if (x % y == 0) {
            return y;
        }
        else {
            return gcd_impl(std::abs(x), y);
        }
    }
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief      calculate lcm of x and y.
 * @param[in]  x: lhs. should be from numerator. if negative, then std::abs(lhs) is used
 * @param[in]  y: rhs. should be from denominator (> 0)
 * @return     calculated lcm.
 *             if one of x or y is 0, return 0.
 * @throw      std::overflow_error: lcm is too large for ken3::fraction::int_type.
 */
ken3::fraction::int_type lcm(ken3::fraction::int_type x, ken3::fraction::int_type y)
{
    x /= gcd(x, y);
    check_overflow_mul(x, y);
    return x * y;
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief      check the fraction is minimum value or not.
 *             minimum value is limit::min()/1.
 * @param[in]  f: appointed fraction
 * @return     true: f is minimum value. false: not nimimum value.
 */
bool is_min(const ken3::fraction& f) noexcept
{
    using limit = std::numeric_limits<ken3::fraction::int_type>;

    return ((f.numerator() == limit::min()) && (f.denominator() == 1));
};

} // namespace fraction_detail {

/**
 * @brief      constructor with numerator and denominator.
 * @param[in]  numerator: appointed numerator.
 * @param[in]  denominator: appointed denominator. should be > 0.
 * @throw      std::runtime_error: denominator == 0, or
 *                                 std::abs(minimum value) is required.
 */
fraction::fraction(int_type numerator, int_type denominator)
{
    using limit = std::numeric_limits<int_type>;
    using namespace fraction_detail;

    if (denominator > 0) {
        numerator_ = numerator;
        denominator_ = denominator;
    }
    else if (denominator == 0) {
        throw std::runtime_error("0 is not allowed in the denominator");
    }
    else if (denominator > limit::min()) {
        if (numerator == limit::min()) {
            if ((denominator < -1) && 
                (numerator % denominator == 0))
            {
                numerator_ = numerator / denominator;
                denominator_ = 1;
            }
            else {
                throw std::overflow_error("");
            }
        }
        else {
            numerator_ = -numerator;
            denominator_ = -denominator;
        }
    }
    else { // (denominator == limit::min())
        if (numerator == limit::min()) {
            numerator_ = 1;
            denominator_ = 1;
        }
        else if ((std::abs(numerator) > 1) &&
                 (denominator % std::abs(numerator) == 0))
        {
            numerator_ /= -std::abs(numerator);
            denominator_ /= -std::abs(numerator);
        }
        else {
            throw std::overflow_error("");
        }
    }
    reduce();
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief      operator==
 * @param[in]  rhs: right hand side of operator==
 * @return     result of operator==
 */
bool fraction::operator==(const fraction& rhs) const noexcept
{
    return (numerator_ == rhs.numerator()) && (denominator_ == rhs.denominator());
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief      operator!=
 * @param[in]  rhs: right hand side of operator!=
 * @return     result of operator!=
 */
bool fraction::operator!=(const fraction& rhs) const noexcept
{
    return not (*this == rhs);
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief      operator<
 * @param[in]  rhs: right hand side of operator<
 * @return     result of operator<
 */
bool fraction::operator<(const fraction& rhs) const noexcept
{
    using namespace fraction_detail;

    // deal with zero
    if ((numerator_ == 0) || (rhs.numerator() == 0)) {
        return (numerator_ < rhs.numerator());
    }

    // deal with minimum value
    else if (is_min(rhs)) {
        return false;
    }
    else if (is_min(*this)) {
        return true;
    }

    // deal with different sign
    int8_t sign_lhs = (numerator_ > 0) ? 1 : -1; 
    int8_t sign_rhs = (rhs.numerator() > 0) ? 1 : -1;
    if (sign_lhs != sign_rhs) {
        return (sign_lhs < sign_rhs);
    }

    // deal with different integer part
    int_type int_lhs = int_type(*this);
    int_type int_rhs = int_type(rhs);
    if (int_lhs != int_rhs) {
        return (int_lhs < int_rhs);
    }

    // final. deal with decimal part
    int_type deci_lhs = numerator_ % denominator_;
    int_type deci_rhs = rhs.numerator() % rhs.denominator();
    if ((deci_lhs == 0) || (deci_rhs == 0)) {
        return (deci_lhs < deci_rhs);
    }
    else {
        return fraction(rhs.denominator(), deci_rhs) < fraction(denominator_, deci_lhs);
    }
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief      operator>
 * @param[in]  rhs: right hand side of operator>
 * @return     result of operator>
 */
bool fraction::operator>(const fraction& rhs) const noexcept
{
    return (rhs < *this);
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief      operator<=
 * @param[in]  rhs: right hand side of operator<=
 * @return     result of operator<=
 */
bool fraction::operator<=(const fraction& rhs) const noexcept
{
    return not (*this > rhs);
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief      operator>=
 * @param[in]  rhs: right hand side of operator>=
 * @return     result of operator>=
 */
bool fraction::operator>=(const fraction& rhs) const noexcept
{
    return not (*this < rhs);
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief      operator+=
 * @param[in]  rhs: right hand side of operator+=
 * @return     result of operator+=
 * @throw      std::overflow_error: when overflow occurs.
 */
fraction& fraction::operator+=(const fraction& rhs)
{
    using namespace fraction_detail;

    int_type denominator = lcm(denominator_, rhs.denominator());
    check_overflow_mul(numerator_, denominator / denominator_);
    check_overflow_mul(rhs.numerator(), denominator / rhs.denominator());
    check_overflow_add(numerator_ * (denominator / denominator_),
                       rhs.numerator() * (denominator / rhs.denominator()));
    numerator_ = numerator_ * (denominator / denominator_) +
                 rhs.numerator() * (denominator / rhs.denominator());
    denominator_ = denominator;
    reduce();
    return *this;
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief      operator-=
 * @param[in]  rhs: right hand side of operator-=
 * @return     result of operator-=
 * @throw      std::overflow_error: when overflow occurs.
 */
fraction& fraction::operator-=(const fraction& rhs)
{
    using namespace fraction_detail;

    int_type denominator = lcm(denominator_, rhs.denominator());
    check_overflow_mul(numerator_, denominator / denominator_);
    check_overflow_mul(rhs.numerator(), denominator / rhs.denominator());
    check_overflow_sub(numerator_ * (denominator / denominator_),
                       rhs.numerator() * (denominator / rhs.denominator()));
    numerator_ = numerator_ * (denominator / denominator_) -
                 rhs.numerator() * (denominator / rhs.denominator());
    denominator_ = denominator;
    reduce();
    return *this;
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief      operator*=
 * @param[in]  rhs: right hand side of operator*=
 * @return     result of operator*=
 * @throw      std::overflow_error: when overflow occurs.
 */
fraction& fraction::operator*=(const fraction& rhs)
{
    using namespace fraction_detail;

    int_type gcd14 = gcd(numerator_, rhs.denominator());
    int_type gcd23 = gcd(rhs.numerator(), denominator_);
    check_overflow_mul(numerator_ / gcd14, rhs.numerator() / gcd23);
    check_overflow_mul(denominator_ / gcd23, rhs.denominator() / gcd14);
    numerator_ = (numerator_ / gcd14) * (rhs.numerator() / gcd23);
    denominator_ = (denominator_ / gcd23) * (rhs.denominator() / gcd14);
    reduce();
    return *this;
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief      operator/=
 * @param[in]  rhs: right hand side of operator/=
 * @return     result of operator/=
 * @throw      std::overflow_error: when overflow occurs.
 *             std::runtime_error: numerator of rhs == 0.
 */
fraction& fraction::operator/=(const fraction& rhs)
{
    using limit = std::numeric_limits<int_type>;

    if (rhs.numerator() != limit::min()) {
        fraction tmp = (rhs);
        tmp.inverse();
        this->operator*=(tmp);
    }
    else { // (rhs.numerator() == limit::min())
        if (numerator_ == limit::min()) {
            numerator_ = rhs.denominator();
            reduce();
        }
        else if (std::abs(numerator_) == 0) {
            ;
        }
        else {
            if ((std::abs(numerator_) == 1) ||
                (rhs.numerator() % numerator_ == 0))
            {
                throw std::overflow_error("");
            }
            else {
                *this = fraction(1, denominator_) *
                        fraction(rhs.denominator(), rhs.numerator() / numerator_);
            }
        }
    }

    return *this;
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief      operator+
 * @param[in]  rhs: right hand side of operator+
 * @return     result of operator+
 * @throw      std::overflow_error: when overflow occurs.
 */
const fraction fraction::operator+(const fraction& rhs) const
{
    fraction result = *this;
    result += rhs;
    return result;
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief      operator-
 * @param[in]  rhs: right hand side of operator-
 * @return     result of operator-
 * @throw      std::overflow_error: when overflow occurs.
 */
const fraction fraction::operator-(const fraction& rhs) const
{
    fraction result = *this;
    result -= rhs;
    return result;
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief      operator*
 * @param[in]  rhs: right hand side of operator*
 * @return     result of operator*
 * @throw      std::overflow_error: when overflow occurs.
 */
const fraction fraction::operator*(const fraction& rhs) const
{
    fraction result = *this;
    result *= rhs;
    return result;
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief      operator/
 * @param[in]  rhs: right hand side of operator/
 * @return     result of operator/
 * @throw      std::overflow_error: when overflow occurs.
 *             std::runtime_error: numerator of rhs == 0.
 */
const fraction fraction::operator/(const fraction& rhs) const
{
    fraction result = *this;
    result /= rhs;
    return result;
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief      cast to std::intmax_t
 * @return     casted std::intmax_t
 */
fraction::operator fraction::int_type(void) const noexcept
{
    return numerator_ / denominator_;
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief      cast to float
 * @return     casted float
 */
fraction::operator float(void) const noexcept
{
    return (float)numerator_ / (float)denominator_;
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief      cast to double
 * @return     casted double
 */
fraction::operator double(void) const noexcept
{
    return (double)numerator_ / (double)denominator_;
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief      cast to long double
 * @return     casted long double
 */
fraction::operator long double(void) const noexcept
{
    return (long double)numerator_ / (long double)denominator_;
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief      operator>> for in-stream
 * @param[in,out] is: in-stream
 * @param[out] self: derived value from in-stream are set
 * @return     argument in-stream
 * @throw      std::runtime_error: new denominator == 0, or
 *                                 std::abs(minimum value) is required.
 * @note       the format of fraction is "1/2" when numerator is 1 and
 *             denominator is 2.
 */
std::istream& operator>>(std::istream& is, fraction& self)
{
    fraction::int_type numerator = 0;
    char slash = '\0';
    fraction::int_type denominator = 0;

    if (is.good()) {
        is >> numerator;
        if (not is.fail() && is.good()) {
            slash = is.get();
            if (not is.fail() && (slash == '/') && is.good()) {
                is >> denominator;
                if (not is.fail()) {
                    self.set(numerator, denominator); // todo result check
                }
            }
        }
    }

    return is;
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief      operator<< for out-stream
 * @param[in,out] os: out-stream
 * @param[in]  self: input for out-stream
 * @return     argument out-stream
 * @note       the format of fraction is "1/2" when numerator is 1 and
 *             denominator is 2.
 */
std::ostream& operator<<(std::ostream& os, const fraction& self)
{
    return os << self.numerator() << "/" << self.denominator();
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief      swap two fractions
 * @param[in,out] rhs: counter part of swap
 */
void fraction::swap(fraction& rhs) noexcept
{
    std::swap(numerator_, rhs.numerator_);
    std::swap(denominator_, rhs.denominator_);
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief      operator(). getter of numerator and denominator.
 * @return     std::pair<std::intmax_t, std::intmax_t>. The first is numerator
 *             and second is denominator.
 */
fraction::pair_type fraction::operator()(void) const noexcept
{
    return pair_type{numerator_, denominator_};
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief      getter of numerator.
 * @return     numerator
 */
fraction::int_type fraction::numerator(void) const noexcept
{
    return numerator_;
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief      getter of denominator.
 * @return     denominator
 */
fraction::int_type fraction::denominator(void) const noexcept
{
    return denominator_;
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief      setter of numerator and denominator.
 * @param[in]  numerator: appointed numerator
 * @param[in]  denominator: appointed denominator
 * @throw      std::runtime_error: new denominator == 0, or
 *                                 std::abs(minimum value) is required.
 */
void fraction::set(int_type numerator, int_type denominator)
{
    *this = fraction(numerator, denominator);
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief      inverse. (ex. 2/3 -> 3/2)
 * @throw      std::runtime_error: new denominator == 0, or
 *                                 std::abs(minimum value) is required.
 */
void fraction::inverse(void)
{
    *this = fraction(denominator_, numerator_);
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief      reduce. (ex. 2/4 -> 1/2)
 */
void fraction::reduce(void) noexcept
{
    using limit = std::numeric_limits<int_type>;
    using namespace fraction_detail;

    if (numerator_ == 0) {
        denominator_ = 1;
    }
    else if (numerator_ == limit::min()) {
        if (numerator_ % denominator_ == 0) {
            numerator_ /= denominator_;
            denominator_ = 1;
        }
    }
    else {
        int_type g = gcd(std::abs(numerator_), denominator_);
        numerator_ /= g;
        denominator_ /= g;
    }
}
/////////////////////////////////////////////////////////////////////////////

} // namespace ken3 {
