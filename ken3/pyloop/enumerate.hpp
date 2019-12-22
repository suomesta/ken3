/**
 * @file    ken3/pyloop/enumerate.hpp
 * @brief   Detail implementation of ken3::enumerate().
 * @author  toda
 * @date    2017-08-25
 * @version 0.1.0
 * @remark  the target is C++11 or more.
 */

#ifndef INCLUDE_GUARD_KEN3_PYLOOP_ENUMERATE_HPP
#define INCLUDE_GUARD_KEN3_PYLOOP_ENUMERATE_HPP

#include <iterator>
#include <utility>

namespace ken3 {
namespace py {
namespace enumerate_detail {

// enumerate iterator, which supports operator++, operator*, and operator!=.
// this struct is made in enumerate_object::begin() or enumerate_object::end().
template <typename ITERATOR>
struct enumerate_iterator
{
    using self_type = enumerate_iterator<ITERATOR>;
    using size_type = typename std::iterator_traits<ITERATOR>::difference_type;
    using return_type = std::pair<size_type, decltype(*std::declval<ITERATOR>())>;

    size_type first;
    ITERATOR second;

    void operator++(void)
    {
        ++first;
        ++second;
    }

    return_type operator*(void)
    {
        return return_type{first, *second};
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
public:
    using iterator_type = enumerate_iterator<decltype(std::begin(std::declval<ITERABLE&>()))>;

    explicit enumerate_object(ITERABLE& iterable):
        iterable_(iterable)
    {}

    enumerate_object(void) = delete;

    iterator_type begin(void) const
    {
        return iterator_type{0, std::begin(iterable_)};
    }

    iterator_type end(void) const
    {
        return iterator_type{std::distance(std::begin(iterable_), std::end(iterable_)),
                             std::end(iterable_)};
    }

private:
    ITERABLE& iterable_;
};
/////////////////////////////////////////////////////////////////////////////

} // namespace enumerate_detail {
} // namespace py {
} // namespace ken3 {

#endif // #ifndef INCLUDE_GUARD_KEN3_PYLOOP_ENUMERATE_HPP
