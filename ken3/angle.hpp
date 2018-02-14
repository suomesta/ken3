/**
 * @file    angle.hpp
 * @brief   Implementation of angle class. 
 *          angle class holds angle value, which is normalized. 
 *          its unit is degree or radian (defined by template parameter),
 *          and it is easy to convert the other unit.
 * @author  toda
 * @date    2018-02-13
 * @version 0.1.0
 * @remark  the target is C++11 or more
 * @remark  angle class is exception free as long as std::fmod() does not throw any exceptions.
 *
 * @note
 * Typical usage is;
 *     angle<true> deg(45.0);
 *     deg += angle<true>(45.0);
 *     std::cout << deg(); // => 90
 *     std::cout << deg.degree(); // => 90
 *     std::cout << deg.radian(); // => 90
 *     deg += 350.0;
 *     std::cout << deg(); // => 80
 *
 *     angle<false> rad(1.0);
 *     std::cout << rad(); // => 1
 *     std::cout << rad.degree(); // => 57.2958
 *     std::cout << rad.radian(); // => 1
 *     rad += 7;
 *     std::cout << rad(); // => 1.71681
 *
 * It's a good idea that define new type like following;
 * using degree = angle<true>;
 * using radian = angle<false>;
 */

#ifndef INCLUDE_GUARD_KEN3_ANGLE_HPP
#define INCLUDE_GUARD_KEN3_ANGLE_HPP

#include <cmath>
#include <limits>

namespace ken3 {

/**
 * @class   angle
 * @brief   angle class holds angle value, which is normalized. 
 *          its unit is degree or radian (defined by template parameter DEGREE),
 *          and it is easy to convert the other unit.
 *          the range of value could be defined by template parameter STARTS_ZERO.
 *          following table shows how template paramters define the implementation.
 *          +----------------------++--------------------------+
 *          |        tparam        ||      implementation      |
 *          +--------+-------------++--------+-----------------+
 *          | DEGREE | STARTS_ZERO || unit   |      range      |
 *          +--------+-------------++--------+-----------------+
 *          |  true  |    true     || degree | [0.0, 360.0)    |
 *          |  true  |    false    || degree | [-180.0, 180.0) |
 *          |  false |    true     || radian | [0.0, 2pi)      |
 *          |  false |    false    || radian | [-pi, pi)       |
 *          +--------+-------------++--------+-----------------+
 * @tparam  DEGREE: if true, value is in degrees. else, in radians.
 * @tparam  STARTS_ZERO: if true, minimum normalized value is 0.0.
 */
template <bool DEGREE, bool STARTS_ZERO=true>
class angle
{
private:
    // constants
    static constexpr double pi = 3.14159265358979323846;
    /////////////////////////////////////////////////////////////////////////////

    // type definitions
    using self_type = angle<DEGREE, STARTS_ZERO>;
    /////////////////////////////////////////////////////////////////////////////

public:
    /**
     * @brief      default constructor. initial value is 0.0
     */
    angle(void) noexcept :
        v_(0.0)
    {
        ;
    }
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      constructor with one argument. initialized by argument
     * @param[in]  value: initial value
     */
    explicit angle(double value) noexcept :
        v_(normalize(value))
    {
        ;
    }
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      copy-constructor, move-constructor, destructor, copy-operator=,
     *             and move-operator= are default.
     */
    angle(const self_type& src) = default;
    angle(self_type&& src) = default;
    ~angle(void) = default;
    self_type& operator=(const self_type& rhs) = default;
    self_type& operator=(self_type&& rhs) = default;
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      operator= with one double argument
     * @param[in]  value: new value to be assigned
     */
    self_type& operator=(double value) noexcept
    {
        v_ = normalize(value);
        return *this;
    }
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      operator<
     * @param[in]  rhs: rhs of operator<
     * @return     result of operator<
     */
    bool operator<(const self_type&rhs) const noexcept
    {
        return v_ < rhs();
    }
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      operator==
     * @param[in]  rhs: rhs of operator==
     * @return     result of operator==
     * @note       following does not always return true, because of normalization
     *             angle(1.0 / 3.0) == angle(1.0 / 3.0 + 360.0)
     */
    bool operator==(const self_type&rhs) const noexcept
    {
        return v_ == rhs();
    }
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      operator!=
     * @param[in]  rhs: rhs of operator!=
     * @return     result of operator!=
     * @note       following does not always return false, because of normalization
     *             angle(1.0 / 3.0) != angle(1.0 / 3.0 + 360.0)
     */
    bool operator!=(const self_type&rhs) const noexcept
    {
        return v_ != rhs();
    }
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      operator+=
     * @param[in]  rhs: rhs of operator+=
     * @return     result of operator+=.
     */
    self_type& operator+=(const self_type& rhs)
    {
        v_ = normalize(v_ + rhs());
        return *this;
    }
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      operator+= with one double argument
     * @param[in]  rhs: raw value of operator+=
     * @return     result of operator+=.
     */
    self_type& operator+=(double rhs)
    {
        v_ = normalize(v_ + rhs);
        return *this;
    }
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      operator+
     * @param[in]  rhs: rhs of operator+
     * @return     result of operator+.
     */
    const self_type operator+(const self_type& rhs) const
    {
        self_type ret = *this;
        ret += rhs;
        return ret;
    }
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      operator+ with one double argument
     * @param[in]  rhs: raw value of operator+
     * @return     result of operator+.
     */
    const self_type operator+(double rhs) const
    {
        self_type ret = *this;
        ret += rhs;
        return ret;
    }
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      operator-=
     * @param[in]  rhs: rhs of operator-=
     * @return     result of operator-=.
     */
    self_type& operator-=(const self_type& rhs)
    {
        v_ = normalize(v_ - rhs());
        return *this;
    }
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      operator-= with one double argument
     * @param[in]  rhs: raw value of operator-=
     * @return     result of operator-=.
     */
    self_type& operator-=(double rhs)
    {
        v_ = normalize(v_ - rhs);
        return *this;
    }
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      operator-
     * @param[in]  rhs: rhs of operator-
     * @return     result of operator-.
     */
    const self_type operator-(const self_type& rhs) const
    {
        self_type ret = *this;
        ret -= rhs;
        return ret;
    }
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      operator- with one double argument
     * @param[in]  rhs: raw value of operator-
     * @return     result of operator-.
     */
    const self_type operator-(double rhs) const
    {
        self_type ret = *this;
        ret -= rhs;
        return ret;
    }
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      operator*=
     * @param[in]  rhs: raw value of operator*=
     * @return     result of operator*=.
     */
    self_type& operator*=(double rhs)
    {
        v_ = normalize(v_ * rhs);
        return *this;
    }
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      operator*
     * @param[in]  rhs: raw value of operator*
     * @return     result of operator*.
     */
    const self_type operator*(double rhs) const
    {
        self_type ret = *this;
        ret *= rhs;
        return ret;
    }
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      operator/=
     * @param[in]  rhs: raw value of operator/=
     * @return     result of operator/=.
     * @note       if rhs == 0.0, then results unknown behavior
     */
    self_type& operator/=(double rhs)
    {
        v_ = normalize(v_ / rhs);
        return *this;
    }
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      operator/
     * @param[in]  rhs: raw value of operator/
     * @return     result of operator/.
     * @note       if rhs == 0.0, then results unknown behavior
     */
    const self_type operator/(double rhs) const
    {
        self_type ret = *this;
        ret /= rhs;
        return ret;
    }
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      operator()
     * @return     current value in own unit.
     */
    double operator()(void) const noexcept
    {
        return v_;
    }
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      get value in degrees
     * @return     current value in degrees.
     */
    double degree(void) const noexcept
    {
        return DEGREE ? v_ : rad2deg(v_);
    }
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      get value in radians
     * @return     current value in radians.
     */
    double radian(void) const noexcept
    {
        return DEGREE ? deg2rad(v_) : v_;
    }
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      set value in own unit
     * @param[in]  value: appointed value in own unit
     */
    void set(double value) noexcept
    {
        v_ = normalize(value);
    }
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      set value in degrees
     * @param[in]  degree: appointed value in degrees
     */
    void set_degree(double degree) noexcept
    {
        v_ = normalize(DEGREE ? degree : deg2rad(degree));
    }
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      set value in radians
     * @param[in]  radian: appointed value in radians
     */
    void set_radian(double radian) noexcept
    {
        v_ = normalize(DEGREE ? rad2deg(radian) : radian);
    }
    /////////////////////////////////////////////////////////////////////////////

private:
    /**
     * @brief      normalize angle value
     * @param[in]  value: appointed value in own unit
     * @return     normalized value
     */
    double normalize(double value) const noexcept
    {
        static constexpr double unit = DEGREE ? 180.0 : pi;

        double ret = std::fmod(value, 2.0 * unit);
        if (ret < 0.0) {
            ret += (2.0 * unit);
        }
        else if (ret < std::numeric_limits<double>::epsilon()) {
            ret = 0.0;
        }

        if (not STARTS_ZERO) {
            if (ret >= unit) {
                ret -= (2.0 * unit);
            }
        }

        return ret;
    }
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      convert degree to radian
     * @param[in]  degree: appointed value in degrees
     * @return     converted radian value
     */
    double deg2rad(double degree) const noexcept
    {
        return degree / 180.0 * pi;
    }
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      convert radian to degree
     * @param[in]  degree: appointed value in radians
     * @return     converted degree value
     */
    double rad2deg(double radian) const noexcept
    {
        return radian / pi * 180.0;
    }
    /////////////////////////////////////////////////////////////////////////////

private:
    double v_;
};
/////////////////////////////////////////////////////////////////////////////

} // namespace ken3 {

#endif // #ifndef INCLUDE_GUARD_KEN3_ANGLE_HPP

