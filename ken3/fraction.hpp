/**
 * @file    ken3/fraction.hpp
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

#ifndef INCLUDE_GUARD_KEN3_FRACTION_HPP
#define INCLUDE_GUARD_KEN3_FRACTION_HPP

#include <cstdint>
#include <stdexcept>
#include <iostream>
#include <utility>

namespace ken3 {

/**
 * @class   fraction
 * @brief   fraction class consists of two integers. The one is numerator, the
 *          other is denominator. The denominator is always > 0. Integer type
 *          for both is std::intmax_t.
 */
class fraction
{
public:
    using int_type = std::intmax_t;
    using pair_type = std::pair<int_type, int_type>;
    /////////////////////////////////////////////////////////////////////////////

public:
    /**
     * @brief      default constructor.
     *             fraction 0/1 is constructed.
     */
    fraction() noexcept = default;
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      constructor with numerator and denominator.
     * @param[in]  numerator: appointed numerator.
     * @param[in]  denominator: appointed denominator.
     * @throw      std::runtime_error: denominator == 0, or
     *                                 std::abs(minimum value) is required.
     */
    fraction(int_type numerator, int_type denominator);
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      copy constructor, move constructor, destructor, copy operator=,
     *             and move operator= are nothing special.
     */
    fraction(const fraction& src) noexcept = default;
    fraction(fraction&& src) noexcept = default;
    ~fraction(void) noexcept = default;
    fraction& operator=(const fraction& rhs) noexcept = default;
    fraction& operator=(fraction&& rhs) noexcept = default;
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      operator==
     * @param[in]  rhs: right hand side of operator==
     * @return     result of operator==
     */
    bool operator==(const fraction& rhs) const noexcept;
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      operator!=
     * @param[in]  rhs: right hand side of operator!=
     * @return     result of operator!=
     */
    bool operator!=(const fraction& rhs) const noexcept;
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      operator<
     * @param[in]  rhs: right hand side of operator<
     * @return     result of operator<
     */
    bool operator<(const fraction& rhs) const noexcept;
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      operator>
     * @param[in]  rhs: right hand side of operator>
     * @return     result of operator>
     */
    bool operator>(const fraction& rhs) const noexcept;
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      operator<=
     * @param[in]  rhs: right hand side of operator<=
     * @return     result of operator<=
     */
    bool operator<=(const fraction& rhs) const noexcept;
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      operator>=
     * @param[in]  rhs: right hand side of operator>=
     * @return     result of operator>=
     */
    bool operator>=(const fraction& rhs) const noexcept;
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      operator+=
     * @param[in]  rhs: right hand side of operator+=
     * @return     result of operator+=
     * @throw      std::overflow_error: when overflow occurs.
     */
    fraction& operator+=(const fraction& rhs);
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      operator-=
     * @param[in]  rhs: right hand side of operator-=
     * @return     result of operator-=
     * @throw      std::overflow_error: when overflow occurs.
     */
    fraction& operator-=(const fraction& rhs);
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      operator*=
     * @param[in]  rhs: right hand side of operator*=
     * @return     result of operator*=
     * @throw      std::overflow_error: when overflow occurs.
     */
    fraction& operator*=(const fraction& rhs);
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      operator/=
     * @param[in]  rhs: right hand side of operator/=
     * @return     result of operator/=
     * @throw      std::overflow_error: when overflow occurs.
     *             std::runtime_error: numerator of rhs == 0.
     */
    fraction& operator/=(const fraction& rhs);
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      operator+
     * @param[in]  rhs: right hand side of operator+
     * @return     result of operator+
     * @throw      std::overflow_error: when overflow occurs.
     */
    const fraction operator+(const fraction& rhs) const;
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      operator-
     * @param[in]  rhs: right hand side of operator-
     * @return     result of operator-
     * @throw      std::overflow_error: when overflow occurs.
     */
    const fraction operator-(const fraction& rhs) const;
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      operator*
     * @param[in]  rhs: right hand side of operator*
     * @return     result of operator*
     * @throw      std::overflow_error: when overflow occurs.
     */
    const fraction operator*(const fraction& rhs) const;
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      operator/
     * @param[in]  rhs: right hand side of operator/
     * @return     result of operator/
     * @throw      std::overflow_error: when overflow occurs.
     *             std::runtime_error: numerator of rhs == 0.
     */
    const fraction operator/(const fraction& rhs) const;
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      cast to std::intmax_t
     * @return     casted std::intmax_t
     */
    operator int_type(void) const noexcept;
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      cast to float
     * @return     casted float
     */
    operator float(void) const noexcept;
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      cast to double
     * @return     casted double
     */
    operator double(void) const noexcept;
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      cast to long double
     * @return     casted long double
     */
    operator long double(void) const noexcept;
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
    friend std::istream& operator>>(std::istream& is, fraction& self);
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      operator<< for out-stream
     * @param[in,out] os: out-stream
     * @param[in]  self: input for out-stream
     * @return     argument out-stream
     * @note       the format of fraction is "1/2" when numerator is 1 and
     *             denominator is 2.
     */
    friend std::ostream& operator<<(std::ostream& os, const fraction& self);
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      swap two fractions
     * @param[in,out] rhs: counter part of swap
     */
    void swap(fraction& rhs) noexcept;
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      operator(). getter of numerator and denominator.
     * @return     std::pair<std::intmax_t, std::intmax_t>. The first is numerator
     *             and second is denominator.
     */
    pair_type operator()(void) const noexcept;
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      getter of numerator.
     * @return     numerator
     */
    int_type numerator(void) const noexcept;
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      getter of denominator.
     * @return     denominator
     */
    int_type denominator(void) const noexcept;
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      setter of numerator and denominator.
     * @param[in]  numerator: appointed numerator
     * @param[in]  denominator: appointed denominator
     * @throw      std::runtime_error: new denominator == 0, or
     *                                 std::abs(minimum value) is required.
     */
    void set(int_type numerator, int_type denominator);
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      inverse. (ex. 2/3 -> 3/2)
     * @throw      std::runtime_error: new denominator == 0, or
     *                                 std::abs(minimum value) is required.
     */
    void inverse(void);
    /////////////////////////////////////////////////////////////////////////////

private:
    /**
     * @brief      reduce. (ex. 2/4 -> 1/2)
     */
    void reduce(void) noexcept;
    /////////////////////////////////////////////////////////////////////////////

private:
    int_type numerator_ = 0;
    int_type denominator_ = 1;
    /////////////////////////////////////////////////////////////////////////////

};
/////////////////////////////////////////////////////////////////////////////

} // namespace ken3 {

#endif // #ifndef INCLUDE_GUARD_KEN3_FRACTION_HPP
