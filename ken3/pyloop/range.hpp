/**
 * @file    ken3/pyloop/range.hpp
 * @brief   Detail implementation of ken3::enumerate().
 * @author  toda
 * @date    2017-08-25
 * @version 0.1.0
 * @remark  the target is C++11 or more
 */

#ifndef INCLUDE_GUARD_KEN3_PYLOOP_RANGE_HPP
#define INCLUDE_GUARD_KEN3_PYLOOP_RANGE_HPP

#include <exception>
#include <limits>
#include <type_traits>

namespace ken3 {
namespace pyloop {
namespace range_detail {

// range iterator, which supports operator++, operator*, and operator!=.
// this struct is made in range_object::begin() or range_object::end().
template <typename T>
struct range_iterator
{
    const T step_;
    T value_;

    void operator++(void)
    {
        if (step_ > 0) {
            if ((std::numeric_limits<T>::max() - step_) < value_) { // avoid overflow
                value_ = std::numeric_limits<T>::max();
            }
            else {
                value_ += step_;
            }
        }
        else {
            if ((std::numeric_limits<T>::min() - step_) > value_) { // avoid overflow
                value_ = std::numeric_limits<T>::min();
            }
            else {
                value_ += step_;
            }
        }
    }

    T operator*(void) const
    {
        return value_;
    }

    bool operator!=(const range_iterator& rhs) const
    {
        // intended to work in range-for statement
        return (step_ > 0) ? (value_ < rhs.value_) : (value_ > rhs.value_);
    }
};
/////////////////////////////////////////////////////////////////////////////

// range object, which supports begin() and end()
template <typename T>
class range_object
{
    static_assert(std::is_integral<T>::value, "range accepts only integer");
    static_assert(!std::is_same<T, bool>::value, "range does not accept bool");
    using iterator = range_iterator<T>;

public:
    template <typename VALUEERROR>
    range_object(T start, T stop, T step, VALUEERROR* dummy):
        start_(start),
        stop_(stop),
        step_(step)
    {
        static_assert(std::is_base_of<std::runtime_error, VALUEERROR>::value, "requires std::runtime_error");

        if (step_ == 0) {
            throw VALUEERROR("range() arg 3 must not be zero");
        }
    }

    iterator begin(void) const
    {
        if (valid()) {
            return iterator{step_, start_};
        }
        else {
            return iterator{1, 0};
        }
    }

    iterator end(void) const
    {
        if (valid()) {
            return iterator{step_, stop_};
        }
        else {
            return iterator{1, 0};
        }
    }

private:
    bool valid(void) const
    {
        return (step_ > 0) ? (stop_ > start_) : (start_ > stop_);
    }

    const T start_;
    const T stop_;
    const T step_;
};
/////////////////////////////////////////////////////////////////////////////

} // namespace range_detail {
} // namespace pyloop {
} // namespace ken3 {

#endif // #ifndef INCLUDE_GUARD_KEN3_PYLOOP_RANGE_HPP

