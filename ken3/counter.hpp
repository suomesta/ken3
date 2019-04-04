/**
 * @file    ken3/counter.hpp
 * @brief   Implementation of counter class. 
 *          counter is util counter class, which never over flows. 
 * @author  toda
 * @date    2019-04-01
 * @version 0.1.0
 * @remark  the target is C++11 or more.
 * @remark  this module works only with this header file.
 *
 * @note
 * Typical usage is;
 *     ken3::counter<2> c;
 *     std::cout << c(); // => 0
 *     std::cout << c.is_maximum(); // => 0
 *     c++;
 *     std::cout << c(); // => 1
 *     std::cout << c.is_maximum(); // => 0
 *     c++;
 *     std::cout << c(); // => 2
 *     std::cout << c.is_maximum(); // => 1
 *     c++;
 *     std::cout << c(); // => 2
 *     std::cout << c.is_maximum(); // => 1
 */

#ifndef INCLUDE_GUARD_KEN3_COUNTER_HPP
#define INCLUDE_GUARD_KEN3_COUNTER_HPP

#include <cstddef>

namespace ken3 {

/**
 * @class   counter
 * @brief   counter is a util counter class.
 *          this class holds one counter value. This counter value is
 *          always in range [MINIMUM, MAXIMUM].
 * @tparam  MAXIMUM: maximum value of counter value
 * @tparam  MINIMUM: minimum value of counter value. default is 0.
 *                   must be (MAXIMUM >= MINIMUM)
 * @note    this class is completely exception free.
 */
template <size_t MAXIMUM, size_t MINIMUM=0>
class counter
{
    static_assert(MAXIMUM >= MINIMUM, "Must be (MAXIMUM >= MINIMUM)");

private:
    using self_type = counter<MAXIMUM, MINIMUM>;
    /////////////////////////////////////////////////////////////////////////////

public:
    /**
     * @brief      default-constructor
     *             value is set to MINIMUM.
     */
    counter(void) :
        value_(MINIMUM)
    {
        ;
    }
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      constructor with initial value
     *             value is set to ini.
     * @param[in]  ini: appointed initial value
      */
    explicit counter(size_t ini)
    {
        if (ini < MINIMUM) {
            value_ = MINIMUM;
        }
        else if (ini > MAXIMUM) {
            value_ = MAXIMUM;
        }
        else {
            value_ = ini;
        }
    }
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      copy-constructor, move-constructor, destructor,
     *             copy-operator=, and move-operator= are default.
     */
    counter(const self_type& src) = default;
    counter(self_type&& src) = default;
    self_type& operator=(const self_type& rhs) = default;
    self_type& operator=(self_type&& rhs) = default;
    ~counter(void) = default;
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      operator()
     * @return     current counter value
     */
    size_t operator()(void) const
    {
        return value_;
    }
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      pre-increment operator.
     *             counter value increase. if counter value has reached MAXIMUM, then nothing happens.
     * @return     own reference
     */
    self_type& operator++()
    {
        if (value_ < MAXIMUM) {
            value_++;
        }
        return *this;
    }
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      post-increment operator.
     *             counter value increase. if counter value has reached MAXIMUM, then nothing happens.
     * @return     own value
     * @note       pre-increment is faster than this function. if return value is not used, should use pre-increment instead.
     */
    const self_type operator++(int)
    {
        self_type prev = *this; 
        operator++();
        return prev;
    }
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      pre-decrement operator.
     *             counter value decrease. if counter value is 0, then nothing happens.
     * @return     own reference
     */
    self_type& operator--()
    {
        if (value_ > MINIMUM) {
            value_--;
        }
        return *this;
    }
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      post-decrement operator.
     *             counter value decrease. if counter value is 0, then nothing happens.
     * @return     own value
     * @note       pre-decrement is faster than this function. if return value is not used, should use pre-decrement instead.
     */
    const self_type operator--(int)
    {
        self_type prev = *this; 
        operator--();
        return prev;
    }
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      reset counter value to MINIMUM.
     */
    void reset(void)
    {
        value_ = MINIMUM;
    }
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      advance counter value by n
     *             counter value never exceeds MAXIMUM.
     * @param[in]  n: appointed increment value
     */
    void advance(size_t n)
    {
        if ((MAXIMUM - value_) > n) {
            value_ += n;
        }
        else {
            value_ = MAXIMUM;
        }
    }
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      retreat counter value by n
     *             counter value never exceeds 0.
     * @param[in]  n: appointed decrement value
     */
    void retreat(size_t n)
    {
        if (value_ > n) {
            value_ -= n;
        }
        else {
            value_ = MINIMUM;
        }
    }
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      get MINIMUM
     * @return     minimum counter value. same as tparam MINIMUM
     */
    constexpr size_t minimum(void) const
    {
        return MINIMUM;
    }
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      get MAXIMUM
     * @return     maximum counter value. same as tparam MAXIMUM
     */
    constexpr size_t maximum(void) const
    {
        return MAXIMUM;
    }
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      check whether current counter value is equal to MINIMUM or not
     * @return     true: counter value == MINIMUM, false: counter value != MINIMUM
     */
    bool is_minimum(void) const
    {
        return (value_ == MINIMUM);
    }
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      check whether current counter value is equal to MAXIMUM or not
     * @return     true: counter value == MAXIMUM, false: counter value != MAXIMUM
     */
    bool is_maximum(void) const
    {
        return (value_ == MAXIMUM);
    }
    /////////////////////////////////////////////////////////////////////////////

private:
    size_t value_ = 0;
};
/////////////////////////////////////////////////////////////////////////////

} // namespace ken3 {

#endif // #ifndef INCLUDE_GUARD_KEN3_COUNTER_HPP
