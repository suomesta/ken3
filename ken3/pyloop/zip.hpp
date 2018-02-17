/**
 * @file    pyloop/zip.hpp
 * @brief   Detail implementation of ken3::zip().
 * @author  toda
 * @date    2017-08-25
 * @version 0.1.0
 * @remark  the target is C++11 or more
 */

#ifndef INCLUDE_GUARD_KEN3_PYLOOP_ZIP_HPP
#define INCLUDE_GUARD_KEN3_PYLOOP_ZIP_HPP

#include <iterator>
#include <utility>

namespace ken3 {
namespace pyloop {
namespace zip_detail {

// zip iterator, which supports operator++, operator*, and operator!=.
// this struct is made in zip_object::begin() or zip_object::end().
template <typename ITERATOR1, typename ITERATOR2>
struct zip_iterator
{
    ITERATOR1 first;
    ITERATOR2 second;

    void operator++(void)
    {
        ++first;
        ++second;
    }

    auto operator*(void) -> std::pair<decltype(*first), decltype(*second)>
    {
        return std::pair<decltype(*first), decltype(*second)>{*first, *second};
    }

    bool operator!=(const zip_iterator& rhs) const
    {
        return ((first != rhs.first) && (second != rhs.second));
    }
};
/////////////////////////////////////////////////////////////////////////////

// zip object, which supports begin() and end()
template <typename ITERABLE1, typename ITERABLE2>
class zip_object
{
private:
    const ITERABLE1& iterable1_;
    const ITERABLE2& iterable2_;

    using iterator = zip_iterator<decltype(std::begin(iterable1_)), decltype(std::begin(iterable2_))>;

public:
    zip_object(const ITERABLE1& iterable1, const ITERABLE2& iterable2):
        iterable1_(iterable1),
        iterable2_(iterable2)
    {}

    iterator begin(void) const
    {
        return iterator{std::begin(iterable1_), std::begin(iterable2_)};
    }

    iterator end(void) const
    {
        return iterator{std::end(iterable1_), std::end(iterable2_)};
    }
};
/////////////////////////////////////////////////////////////////////////////

} // namespace zip_detail {
} // namespace pyloop {
} // namespace ken3 {

#endif // #ifndef INCLUDE_GUARD_KEN3_PYLOOP_ZIP_HPP

