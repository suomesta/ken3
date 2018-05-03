/**
 * @file    ken3/bits.cpp
 * @brief   Implementation of bits class.
 *          bits supports to handle multiple bit data.
 * @author  toda
 * @date    2018-01-29
 * @version 0.1.0
 * @remark  the target is C++11 or more.
 */

#include <algorithm>
#include <iterator>
#include <limits>
#include "ken3/bits.hpp"

namespace ken3 {

/**
 * @brief      constructor with size. bits are filled with 0.
 *             this is also default constructor when the argument is skipped.
 * @param[in]  size: appointed size. default is 0.
 * @note       bits(5); => "0 0000"
 *             bits; => ""
 */
bits::bits(size_type size/*=0*/)
{
    for (size_type i = 0; i < size; i++) {
        value_.push_front(false);
    }
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief      constructor with size and integer.
 * @param[in]  size: appointed size. this constructor accepts until 64 bits.
 * @param[in]  value: appointed 64 bits integer. bit is taken from LSB.
 * @note       bits(4, 0xA5); => "0101"
 *             bits(8, 0xA5); => "1010 0101"
 *             bits(100, 0x00); => "000...0" (size is 64, NOT 100)
 */
bits::bits(size_type size, int_type value)
{
    size_type value_size = std::min(size, sizeof(int_type) * 8);

    int_type flag = 1;
    for (size_type i = 0; i < value_size; i++) {
        value_.push_front(value & flag);
        flag <<= 1;
    }
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief      constructor with size and unsigned char array.
 * @param[in]  size: appointed size.
 * @param[in]  value: appointed array data. its size must be at least (size + start)
 * @param[in]  start: start index to be read in value.
 * @note       if too large value and start are given, construction does not complete
 * @note       bits(4, [0xA5], 0); => "1010"
 *             bits(4, [0xA5], 4); => "0101"
 *             bits(8, [0xA5, 0xA5], 4); => "0101 1010"
 */
bits::bits(size_type size, const unsigned char value[], size_type start)
{
    for (size_type i = 0; i < size; i++) {
        size_type index = start + i;
        value_.push_back(value[index/8] & (0x01 << (7 - index % 8)));

        if (index >= std::numeric_limits<size_type>::max()) {
            break;
        }
    }
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief      constructor with string.
 * @param[in]  str: string only with '0' and '1'. the format should be same as bits.str()
 * @note       a character neither '0' nor '1' is ignored
 * @note       bits("1010"); => "1010"
 *             bits("10AB10"); => "1010"
 */
bits::bits(const std::string& str)
{
    for (const auto& i: str) {
        if      (i == '1') {
            value_.push_back(true);
        }
        else if (i == '0') {
            value_.push_back(false);
        }
        else {
            ; // do nothing
        }
    }
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief      operator<
 * @param[in]  rhs: rhs of operator<
 * @return     result of operator<.
 *             result is same as (str() < rhs.str())
 */
bool bits::operator<(const bits& rhs) const noexcept
{
    return value_ < rhs.value_;
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief      operator==
 * @param[in]  rhs: rhs of operator==
 * @return     result of operator==.
 */
bool bits::operator==(const bits& rhs) const noexcept
{
    return value_ == rhs.value_;
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief      operator+=
 * @param[in]  rhs: rhs of operator+=
 * @return     result of operator+=.
 * @note       bits(4, 0x0A) += bits(4, 0x05); => "1010 0101"
 *             bits(2, 0x02) += bits(4, 0x05); => "1001 01"
 */
bits& bits::operator+=(const bits& rhs)
{
    value_.insert(value_.end(), rhs.value_.begin(), rhs.value_.end());
    return *this;
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief      operator+
 * @param[in]  rhs: rhs of operator+
 * @return     result of operator+.
 * @note       bits(4, 0x0A) + bits(4, 0x05); => "1010 0101"
 *             bits(2, 0x02) + bits(4, 0x05); => "1001 01"
 */
const bits bits::operator+(const bits& rhs) const
{
    bits ret = *this;
    ret += rhs;
    return ret;
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief      operator&=
 * @param[in]  rhs: rhs of operator&=
 * @return     result of operator&=.
 * @note       the length of lhs does not change.
 *             if rhs is shorter than lhs, some bits on LSB side are not changed.
 * @note       bits(4, 0x0F) &= bits(4, 0x05); => "0101"
 *             bits(4, 0x0F) &= bits(2, 0x01); => "0111"
 */
bits& bits::operator&=(const bits& rhs) noexcept
{
    storage_type::iterator i = value_.begin();
    storage_type::const_iterator j = rhs.value_.cbegin();
    for (; i != value_.end() && j != rhs.value_.cend(); ++i, ++j) {
        *i &= *j;
    }
    return *this;
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief      operator&
 * @param[in]  rhs: rhs of operator&
 * @return     result of operator&.
 * @note       the length of lhs does not change.
 *             if rhs is shorter than lhs, some bits on LSB side are not changed.
 * @note       bits(4, 0x0F) & bits(4, 0x05); => "0101"
 *             bits(4, 0x0F) & bits(2, 0x01); => "0111"
 */
const bits bits::operator&(const bits& rhs) const noexcept
{
    bits ret = *this;
    ret &= rhs;
    return ret;
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief      operator|=
 * @param[in]  rhs: rhs of operator|=
 * @return     result of operator|=.
 * @note       the length of lhs does not change.
 *             if rhs is shorter than lhs, some bits on LSB side are not changed.
 * @note       bits(4, 0x0A) |= bits(4, 0x05); => "1111"
 *             bits(4, 0x0A) |= bits(2, 0x03); => "1110"
 */
bits& bits::operator|=(const bits& rhs) noexcept
{
    storage_type::iterator i = value_.begin();
    storage_type::const_iterator j = rhs.value_.cbegin();
    for (; i != value_.end() && j != rhs.value_.cend(); ++i, ++j) {
        *i |= *j;
    }
    return *this;
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief      operator|
 * @param[in]  rhs: rhs of operator|
 * @return     result of operator|.
 * @note       the length of lhs does not change.
 *             if rhs is shorter than lhs, some bits on LSB side are not changed.
 * @note       bits(4, 0x0A) | bits(4, 0x05); => "1111"
 *             bits(4, 0x0A) | bits(2, 0x03); => "1110"
 */
const bits bits::operator|(const bits& rhs) const noexcept
{
    bits ret = *this;
    ret |= rhs;
    return ret;
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief      operator^=
 * @param[in]  rhs: rhs of operator^=
 * @return     result of operator^=.
 * @note       the length of lhs does not change.
 *             if rhs is shorter than lhs, some bits on LSB side are not changed.
 * @note       bits(4, 0x0A) ^= bits(4, 0x0F); => "0101"
 *             bits(4, 0x0A) ^= bits(2, 0x03); => "0110"
 */
bits& bits::operator^=(const bits& rhs) noexcept
{
    storage_type::iterator i = value_.begin();
    storage_type::const_iterator j = rhs.value_.cbegin();
    for (; i != value_.end() && j != rhs.value_.cend(); ++i, ++j) {
        *i ^= *j;
    }
    return *this;
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief      operator^
 * @param[in]  rhs: rhs of operator^
 * @return     result of operator^.
 * @note       the length of lhs does not change.
 *             if rhs is shorter than lhs, some bits on LSB side are not changed.
 * @note       bits(4, 0x0A) ^ bits(4, 0x05); => "1111"
 *             bits(4, 0x0A) ^ bits(2, 0x03); => "0110"
 */
const bits bits::operator^(const bits& rhs) const noexcept
{
    bits ret = *this;
    ret ^= rhs;
    return ret;
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief      operator<<=
 * @param[in]  shift: shift value of operator<<=
 * @return     result of operator<<=.
 * @note       bits(4, 0x0A) <<= 4; => "1010 0000"
 */
bits& bits::operator<<=(size_type shift)
{
    for (size_type i = 0; i < shift; i++) {
        value_.push_back(false);
    }
    return *this;
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief      operator<<
 * @param[in]  shift: shift value of operator<<
 * @return     result of operator<<.
 * @note       bits(4, 0x0A) << 4; => "1010 0000"
 */
const bits bits::operator<<(size_type shift) const
{
    bits ret = *this;
    ret <<= shift;
    return ret;
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief      operator>>=
 * @param[in]  shift: shift value of operator>>=
 * @return     result of operator>>=.
 * @note       bits(4, 0x0A) >>= 2; => "00 1010"
 */
bits& bits::operator>>=(size_type shift)
{
    for (size_type i = 0; i < shift; i++) {
        value_.push_front(false);
    }
    return *this;
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief      operator>>
 * @param[in]  shift: shift value of operator>>
 * @return     result of operator>>.
 * @note       bits(4, 0x0A) >> 2; => "00 1010"
 */
const bits bits::operator>>(size_type shift) const
{
    bits ret = *this;
    ret >>= shift;
    return ret;
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief      operator~. inverse all bits
 * @return     result of operator~.
 * @note       ~bits(4, 0x0A); => "0101"
 */
const bits bits::operator~(void) const noexcept
{
    bits ret = *this;
    for (auto& i: ret.value_) {
        i = !i;
    }
    return ret;
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief      swap with another
 * @param[in,out] rhs: right hand side of swap
 */
void bits::swap(bits& rhs) noexcept
{
    value_.swap(rhs.value_);
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief      get bits size
 * @return     bits size
 */
bits::size_type bits::size(void) const noexcept
{
    return value_.size();
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief      is empty
 * @return     true: empty, false: not empty
 */
bool bits::empty(void) const noexcept
{
    return value_.empty();
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief      convert bits data into string
 * @return     converted string.
 * @note       bits b(4, 0xA5); b.str(); => "0101"
 *             bits b(8, 0xA5); b.str(); => "1010 0101"
 *             bits b(4, [0xA5], 0); b.str(); => "1010"
 *             bits b(4, [0xA5], 4); b.str(); => "0101"
 */
std::string bits::str(void) const
{
    std::string str;
    str.reserve(value_.size());

    for (const auto& i: value_) {
        str.push_back(i ? '1' : '0');
    }

    return str;
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief      reverse bits
 * @note       bits(8, 0x12).reverse(); => "0100 1000"
 */
void bits::reverse(void) noexcept
{
    std::reverse(value_.begin(), value_.end());
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief      inverse bits
 * @note       bits(8, 0x12).inverse(); => "1110 1101"
 */
void bits::inverse(void) noexcept
{
    for (auto& i: value_) {
        i = !i;
    }
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief      remove all bits
 */
void bits::clear(void) noexcept
{
    value_.clear();
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief      set all bits 0 or 1
 * @param[in]  value: true means 1, false means 0
 */
void bits::set_all(bool value) noexcept
{
    for (auto& i: value_) {
        i = value;
    }
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief      pop some bits from MSB side and get integer
 * @param[in]  length: appointed length of bits. should be <= 64
 * @return     popped integer.
 * @note       bits(8, 0x12).pop_msb(4); => return 1, remain bits(4, 0x02)
 */
bits::int_type bits::pop_msb(size_type length) noexcept
{
    size_type pop_size = std::min({length, value_.size(), sizeof(int_type) * 8});

    int_type ret = 0;
    for (size_type i = 0; i < pop_size; i++) {
        ret = (ret << 1) + (value_.front() ? 1 : 0);

        value_.pop_front();
    }

    return ret;
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief      pop some bits from LSB side and get integer
 * @param[in]  length: appointed length of bits. should be <= 64
 * @return     popped integer.
 * @note       bits(8, 0x12).pop_lsb(4); => return 2, remain bits(4, 0x01)
 */
bits::int_type bits::pop_lsb(size_type length) noexcept
{
    size_type pop_size = std::min({length, value_.size(), sizeof(int_type) * 8});

    int_type ret = 0;
    for (size_type i = 0; i < pop_size; i++) {
        ret += ((value_.back() ? 1 : 0) << i);

        value_.pop_back();
    }

    return ret;
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief      pick some bits from start with length and get integer
 * @param[in]  start: appointed start index of bits. starts with 0
 * @param[in]  length: appointed length of bits. should be <= 64
 * @return     referred integer.
 * @note       bits(8, 0xA5).refer(2, 4); => return 9
 */
bits::int_type bits::refer(size_type start, size_type length) const noexcept
{
    if (start >= value_.size()) {
        return 0;
    }

    size_type refer_size = std::min({length, value_.size() - start, sizeof(int_type) * 8});
    storage_type::const_iterator iter = std::next(value_.cbegin(), start); // at this moment, iter < value_.end()

    int_type ret = 0;
    for (size_type i = 0; i < refer_size; i++) {
        ret <<= 1;
        ret += (*iter ? 1 : 0);

        ++iter;
    }

    return ret;
}
/////////////////////////////////////////////////////////////////////////////

} // namespace ken3 {

