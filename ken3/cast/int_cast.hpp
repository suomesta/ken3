/**
 * @file    ken3/cast/int_cast.hpp
 * @brief   Detail implementation of ken3::int_cast().
 * @author  toda
 * @date    2018-02-18
 * @version 0.1.0
 * @remark  the target is C++11 or more
 */

#ifndef INCLUDE_GUARD_KEN3_CAST_INT_CAST_HPP
#define INCLUDE_GUARD_KEN3_CAST_INT_CAST_HPP

#include <limits>
#include <stdexcept>

namespace ken3 {
namespace int_cast_detail {

template <size_t S> struct factory;
//                                   FROM      TO        Size
template <> struct factory<0> {}; // signed,   signed,   sizeof(FROM) <= sizeof(TO)
template <> struct factory<1> {}; // unsigned, signed,   sizeof(FROM) <= sizeof(TO)
template <> struct factory<2> {}; // signed,   unsigned, sizeof(FROM) <= sizeof(TO)
template <> struct factory<3> {}; // unsigned, unsigned, sizeof(FROM) <= sizeof(TO)
template <> struct factory<4> {}; // signed,   signed,   sizeof(FROM) >  sizeof(TO)
template <> struct factory<5> {}; // unsigned, signed,   sizeof(FROM) >  sizeof(TO)
template <> struct factory<6> {}; // signed,   unsigned, sizeof(FROM) >  sizeof(TO)
template <> struct factory<7> {}; // unsigned, unsigned, sizeof(FROM) >  sizeof(TO)
/////////////////////////////////////////////////////////////////////////////

template <typename FROM, typename TO>
constexpr size_t factory_index(void)
{
    return (
        std::is_unsigned<FROM>::value +
        std::is_unsigned<TO>::value * 2 +
        ((sizeof(FROM) > sizeof(TO)) ? 1 : 0) * 4
    );
}
/////////////////////////////////////////////////////////////////////////////

// signed,   signed,   sizeof(FROM) <= sizeof(To)
template <typename FROM, typename To>
To int_cast(FROM i, factory<0> s)
{
    return static_cast<To>(i);
}
/////////////////////////////////////////////////////////////////////////////

// unsigned, signed,   sizeof(FROM) <= sizeof(TO)
template <typename FROM, typename TO>
TO int_cast(FROM i, factory<1> s)
{
    if (i > static_cast<FROM>(std::numeric_limits<TO>::max())) {
        throw std::out_of_range("");
    }
    return static_cast<TO>(i);
}
/////////////////////////////////////////////////////////////////////////////

// signed,   unsigned, sizeof(FROM) <= sizeof(TO)
template <typename FROM, typename TO>
TO int_cast(FROM i, factory<2> s)
{
    if (i < 0) {
        throw std::out_of_range("");
    }
    return static_cast<TO>(i);
}
/////////////////////////////////////////////////////////////////////////////

// unsigned, unsigned, sizeof(FROM) <= sizeof(TO)
template <typename FROM, typename TO>
TO int_cast(FROM i, factory<3> s)
{
    return static_cast<TO>(i);
}
/////////////////////////////////////////////////////////////////////////////

// signed,   signed,   sizeof(FROM) >  sizeof(TO)
template <typename FROM, typename TO>
TO int_cast(FROM i, factory<4> s)
{
    if ((i > static_cast<FROM>(std::numeric_limits<TO>::max())) ||
        (i < static_cast<FROM>(std::numeric_limits<TO>::lowest())))
    {
        throw std::out_of_range("");
    }
    return static_cast<TO>(i);
}
/////////////////////////////////////////////////////////////////////////////

// unsigned, signed,   sizeof(From) >  sizeof(TO)
template <typename From, typename TO>
TO int_cast(From i, factory<5> s)
{
    if (i > static_cast<From>(std::numeric_limits<TO>::max())) {
        throw std::out_of_range("");
    }
    return static_cast<TO>(i);
}
/////////////////////////////////////////////////////////////////////////////

// signed,   unsigned, sizeof(FROM) >  sizeof(TO)
template <typename FROM, typename TO>
TO int_cast(FROM i, factory<6> s)
{
    if ((i > static_cast<FROM>(std::numeric_limits<TO>::max())) ||
        (i < 0))
    {
        throw std::out_of_range("");
    }
    return static_cast<TO>(i);
}
/////////////////////////////////////////////////////////////////////////////

// unsigned, unsigned, sizeof(FROM) >  sizeof(TO)
template <typename FROM, typename TO>
TO int_cast(FROM i, factory<7> s)
{
    if (i > static_cast<FROM>(std::numeric_limits<TO>::max())) {
        throw std::out_of_range("");
    }
    return static_cast<TO>(i);
}
/////////////////////////////////////////////////////////////////////////////

} // namespace int_cast_detail {
} // namespace ken3 {

#endif // #ifndef INCLUDE_GUARD_KEN3_CAST_INT_CAST_HPP

