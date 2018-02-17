/**
 * @file    pyloop/enumerate.hpp
 * @brief   Detail implementation of ken3::enumerate().
 * @author  toda
 * @date    2017-08-25
 * @version 0.1.0
 * @remark  the target is C++11 or more
 */

#ifndef INCLUDE_GUARD_KEN3_PYLOOP_ENUMERATE_HPP
#define INCLUDE_GUARD_KEN3_PYLOOP_ENUMERATE_HPP

#include <iterator>
#include <utility>

namespace ken3 {
namespace pyloop {
namespace enumerate_detail {

// enumerate iterator, which supports operator++, operator*, and operator!=.
// this struct is made in enumerate_object::begin() or enumerate_object::end().
template <typename ITERATOR>
struct enumerate_iterator
{
    using self_type = enumerate_iterator<ITERATOR>;
    using size_type = typename std::iterator_traits<ITERATOR>::difference_type;

    size_type first;
    ITERATOR second;

    void operator++(void)
    {
        ++first;
        ++second;
    }

    auto operator*(void) -> std::pair<size_type, decltype(*second)>
    {
        return std::pair<size_type, decltype(*second)>{first, *second};
    }

    bool operator!=(const self_type& rhs) const
    {
        return second != rhs.second;
    }
};
/////////////////////////////////////////////////////////////////////////////

// enumerate object, which supports begin() and end()
template <typename ITERABLE>
class enumerate_object
{
private:
    const ITERABLE& iterable_;

public:
    using iterator_type = enumerate_iterator<decltype(std::begin(iterable_))>;

    enumerate_object(void) = delete;

    explicit enumerate_object(const ITERABLE& iterable):
        iterable_(iterable)
    {}

    iterator_type begin(void) const
    {
        return iterator_type{0, std::begin(iterable_)};
    }

    iterator_type end(void) const
    {
        return iterator_type{std::distance(std::begin(iterable_), std::end(iterable_)),
                             std::end(iterable_)};
    }
};
/////////////////////////////////////////////////////////////////////////////

} // namespace enumerate_detail {
} // namespace pyloop {
} // namespace ken3 {

#endif // #ifndef INCLUDE_GUARD_KEN3_PYLOOP_ENUMERATE_HPP

