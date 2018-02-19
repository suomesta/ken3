/**
 * @file    ken3/cast/string_to.hpp
 * @brief   Detail implementation of ken3::string_to().
 * @author  toda
 * @date    2018-02-18
 * @version 0.1.0
 * @remark  the target is C++11 or more
 */

#ifndef INCLUDE_GUARD_KEN3_CAST_STRING_TO_HPP
#define INCLUDE_GUARD_KEN3_CAST_STRING_TO_HPP

#include <algorithm>
#include <iterator>
#include <limits>
#include "ken3/cast/int_cast.hpp"

namespace ken3 {
namespace string_to_detail {

// switcher for each type
template<size_t T> struct factory;
template<> struct factory<1> {}; // for float
template<> struct factory<2> {}; // for double
template<> struct factory<3> {}; // for long double
template<> struct factory<4> {}; // for smaller than int
template<> struct factory<5> {}; // for int
template<> struct factory<6> {}; // for long
template<> struct factory<7> {}; // for long long
template<> struct factory<8> {}; // for smaller than unsigned long
template<> struct factory<9> {}; // for unsigned long
template<> struct factory<10> {}; // for unsigned long long
/////////////////////////////////////////////////////////////////////////////

// get index value of switcher
template <typename T>
constexpr size_t factory_index(void)
{
    return (
        std::is_same<T, float>::value ? 1 :
        (std::is_same<T, double>::value ? 2 :
        (std::is_same<T, long double>::value ? 3 :
        ((std::is_signed<T>::value && (sizeof(T) < sizeof(int))) ? 4 :
        ((std::is_signed<T>::value && (sizeof(T) == sizeof(int))) ? 5 :
        ((std::is_signed<T>::value && (sizeof(T) == sizeof(long))) ? 6 :
        ((std::is_signed<T>::value && (sizeof(T) == sizeof(long long))) ? 7 :
        ((std::is_unsigned<T>::value && (sizeof(T) < sizeof(unsigned long))) ? 8 :
        ((std::is_unsigned<T>::value && (sizeof(T) == sizeof(unsigned long))) ? 9 :
        ((std::is_unsigned<T>::value && (sizeof(T) == sizeof(unsigned long long))) ? 10 :
        0)))))))))
    );
}
/////////////////////////////////////////////////////////////////////////////

// convert to float
// no extra operation
template <typename T>
T string_to(const std::string& str, size_t* pos, int base, factory<1> dummy)
{
    return std::stof(str, pos);
}
/////////////////////////////////////////////////////////////////////////////

// convert to double
// no extra operation
template <typename T>
T string_to(const std::string& str, size_t* pos, int base, factory<2> dummy)
{
    return std::stod(str, pos);
}
/////////////////////////////////////////////////////////////////////////////

// convert to long double
// no extra operation
template <typename T>
T string_to(const std::string& str, size_t* pos, int base, factory<3> dummy)
{
    return std::stold(str, pos);
}
/////////////////////////////////////////////////////////////////////////////

// convert to the type which is smaller than int
// range check is needed
template <typename T>
T string_to(const std::string& str, size_t* pos, int base, factory<4> dummy)
{
    size_t instance_pos;
    int tmp = std::stoi(str, &instance_pos, base);

    // range check
    if (tmp > std::numeric_limits<T>::max() ||
        tmp < std::numeric_limits<T>::lowest() )
    {
        throw std::out_of_range("");        
    }

    T ret = static_cast<T>(tmp);
    if (pos != nullptr) {
        *pos = instance_pos;
    }
    return ret;
}
/////////////////////////////////////////////////////////////////////////////

// convert to int
// no extra operation
template <typename T>
T string_to(const std::string& str, size_t* pos, int base, factory<5> dummy)
{
    return std::stoi(str, pos, base);
}
/////////////////////////////////////////////////////////////////////////////

// convert to long
// no extra operation
template <typename T>
T string_to(const std::string& str, size_t* pos, int base, factory<6> dummy)
{
    return std::stol(str, pos, base);
}
/////////////////////////////////////////////////////////////////////////////

// convert to long long
// no extra operation
template <typename T>
T string_to(const std::string& str, size_t* pos, int base, factory<7> dummy)
{
    return std::stoll(str, pos, base);
}
/////////////////////////////////////////////////////////////////////////////

// convert to the type which is smaller than unsigned long
// range check and negative check are needed
template <typename T>
T string_to(const std::string& str, size_t* pos, int base, factory<8> dummy)
{
    size_t instance_pos;
    unsigned long tmp = std::stoul(str, &instance_pos, base);

    // negative check
    if (tmp != 0) {
        auto end = std::next(str.cbegin(), instance_pos);
        if (std::find(str.cbegin(), end, '-') != end) {
            throw std::out_of_range("");
        }
    }

    // range check
    if (tmp > std::numeric_limits<T>::max()) {
        throw std::out_of_range("");        
    }

    T ret = static_cast<T>(tmp);
    if (pos != nullptr) {
        *pos = instance_pos;
    }
    return ret;
}
/////////////////////////////////////////////////////////////////////////////

// convert to unsigned long
// negative check is needed
template <typename T>
T string_to(const std::string& str, size_t* pos, int base, factory<9> dummy)
{
    size_t instance_pos;
    unsigned long ret = std::stoul(str, &instance_pos, base);

    // negative check
    if (ret != 0) {
        auto end = std::next(str.cbegin(), instance_pos);
        if (std::find(str.cbegin(), end, '-') != end) {
            throw std::out_of_range("");
        }
    }

    if (pos != nullptr) {
        *pos = instance_pos;
    }
    return ret;
}
/////////////////////////////////////////////////////////////////////////////

// convert to unsigned long long
// negative check is needed
template <typename T>
T string_to(const std::string& str, size_t* pos, int base, factory<10> dummy)
{
    size_t instance_pos;
    unsigned long long ret = std::stoull(str, &instance_pos, base);

    // negative check
    if (ret != 0) {
        auto end = std::next(str.cbegin(), instance_pos);
        if (std::find(str.cbegin(), end, '-') != end) {
            throw std::out_of_range("");
        }
    }

    if (pos != nullptr) {
        *pos = instance_pos;
    }
    return ret;
}
/////////////////////////////////////////////////////////////////////////////

} // namespace string_to_detail {
} // namespace ken3 {

#endif // #ifndef INCLUDE_GUARD_KEN3_CAST_STRING_TO_HPP

