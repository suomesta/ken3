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
    using return_type = std::pair<decltype(*std::declval<ITERATOR1>()),
                                  decltype(*std::declval<ITERATOR2>())>;

    ITERATOR1 first;
    ITERATOR2 second;

    void operator++(void)
    {
        ++first;
        ++second;
    }

    return_type operator*(void)
    {
        return return_type{*first, *second};
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
    using iterator = zip_iterator<decltype(std::begin(std::declval<ITERABLE1&>())),
                                  decltype(std::begin(std::declval<ITERABLE2&>()))>;

public:
    zip_object(ITERABLE1& iterable1, ITERABLE2& iterable2):
        iterable1_(iterable1),
        iterable2_(iterable2)
    {}

    zip_object(void) = delete;

    iterator begin(void) const
    {
        return iterator{std::begin(iterable1_), std::begin(iterable2_)};
    }

    iterator end(void) const
    {
        return iterator{std::end(iterable1_), std::end(iterable2_)};
    }

private:
    ITERABLE1& iterable1_;
    ITERABLE2& iterable2_;
};
/////////////////////////////////////////////////////////////////////////////

} // namespace zip_detail {
} // namespace pyloop {
} // namespace ken3 {

#endif // #ifndef INCLUDE_GUARD_KEN3_PYLOOP_ZIP_HPP

