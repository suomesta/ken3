/**
 * @file    ken3/bits.hpp
 * @brief   Implementation of bits class.
 *          bits supports to handle multiple bit data.
 * @author  toda
 * @date    2018-01-29
 * @version 0.1.0
 * @remark  the target is C++11 or more.
 *
 * @note
 * Typical usage is;
 *     bits b;
 *     b += bits(6, 1);
 *     b += bits(6, 2);
 *     b += bits(6, 3);
 *     b += bits(6, 4);
 *     b += bits(6, 5);
 *     b += bits(6, 6);
 *     b += bits(6, 7);
 *     std::cout << b.pop_msb(6); // => "1"
 *     std::cout << b.pop_msb(2); // => "0"
 *     std::cout << b.pop_msb(30); // => "137430296"
 */

#ifndef INCLUDE_GUARD_KEN3_BITS_HPP
#define INCLUDE_GUARD_KEN3_BITS_HPP

#include <cstdint>
#include <deque>
#include <string>

namespace ken3 {

/**
 * @class   bits
 * @brief   bits class deals with multiple bit data.
 *          bits supports basic operations (+, &, |, ^, ~), and some functions
 *          to get integer.
 *          integer value type used in this class is uint64_t.
 */
class bits
{
public:
    // type defines
    using storage_type = std::deque<bool>; // storage_type shall support pop_front() and pop_back()
    using size_type = storage_type::size_type;
    using int_type = std::uint64_t;
    /////////////////////////////////////////////////////////////////////////////

public:
    /**
     * @brief      constructor with size. bits are filled with 0.
     *             this is also default constructor when the argument is skipped.
     * @param[in]  size: appointed size. default is 0.
     * @note       bits(5); => "0 0000"
     *             bits; => ""
     */
    explicit bits(size_type size=0);
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      constructor with size and integer.
     * @param[in]  size: appointed size. this constructor accepts until 64 bits.
     * @param[in]  value: appointed 64 bits integer. bit is taken from LSB.
     * @note       bits(4, 0xA5); => "0101"
     *             bits(8, 0xA5); => "1010 0101"
     *             bits(100, 0x00); => "000...0" (size is 64, NOT 100)
     */
    bits(size_type size, int_type value);
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
    bits(size_type size, const unsigned char value[], size_type start);
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      constructor with string.
     * @param[in]  str: string only with '0' and '1'. the format should be same as bits.str()
     * @note       a character neither '0' nor '1' is ignored
     * @note       bits("1010"); => "1010"
     *             bits("10AB10"); => "1010"
     */
    explicit bits(const std::string& str);
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      copy-constructor, move-constructor, destructor, copy-operator=,
     *             and move-operator= are default.
     */
    bits(const bits& src) = default;
    bits(bits&& src) = default;
    ~bits(void) = default;
    bits& operator=(const bits& rhs) = default;
    bits& operator=(bits&& rhs) = default;
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      operator<
     * @param[in]  rhs: rhs of operator<
     * @return     result of operator<.
     *             result is same as (str() < rhs.str())
     */
    bool operator<(const bits& rhs) const noexcept;
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      operator==
     * @param[in]  rhs: rhs of operator==
     * @return     result of operator==.
     */
    bool operator==(const bits& rhs) const noexcept;
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      operator+=
     * @param[in]  rhs: rhs of operator+=
     * @return     result of operator+=.
     * @note       bits(4, 0x0A) += bits(4, 0x05); => "1010 0101"
     *             bits(2, 0x02) += bits(4, 0x05); => "1001 01"
     */
    bits& operator+=(const bits& rhs);
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      operator+
     * @param[in]  rhs: rhs of operator+
     * @return     result of operator+.
     * @note       bits(4, 0x0A) + bits(4, 0x05); => "1010 0101"
     *             bits(2, 0x02) + bits(4, 0x05); => "1001 01"
     */
    const bits operator+(const bits& rhs) const;
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
    bits& operator&=(const bits& rhs) noexcept;
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
    const bits operator&(const bits& rhs) const noexcept;
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
    bits& operator|=(const bits& rhs) noexcept;
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
    const bits operator|(const bits& rhs) const noexcept;
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
    bits& operator^=(const bits& rhs) noexcept;
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      operator^
     * @param[in]  rhs: rhs of operator^
     * @return     result of operator^.
     * @note       the length of lhs does not change.
     *             if rhs is shorter than lhs, some bits on LSB are not changed.
     * @note       bits(4, 0x0A) ^ bits(4, 0x05); => "1111"
     *             bits(4, 0x0A) ^ bits(2, 0x03); => "0110"
     */
    const bits operator^(const bits& rhs) const noexcept;
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      operator<<=
     * @param[in]  shift: shift value of operator<<=
     * @return     result of operator<<=.
     * @note       bits(4, 0x0A) <<= 4; => "1010 0000"
     */
    bits& operator<<=(size_type shift);
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      operator<<
     * @param[in]  shift: shift value of operator<<
     * @return     result of operator<<.
     * @note       bits(4, 0x0A) << 4; => "1010 0000"
     */
    const bits operator<<(size_type shift) const;
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      operator>>=
     * @param[in]  shift: shift value of operator>>=
     * @return     result of operator>>=.
     * @note       bits(4, 0x0A) >>= 2; => "00 1010"
     */
    bits& operator>>=(size_type shift);
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      operator>>
     * @param[in]  shift: shift value of operator>>
     * @return     result of operator>>.
     * @note       bits(4, 0x0A) >> 2; => "00 1010"
     */
    const bits operator>>(size_type shift) const;
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      operator~. inverse all bits
     * @return     result of operator~.
     * @note       ~bits(4, 0x0A); => "0101"
     */
    const bits operator~(void) const noexcept;
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      swap with another
     * @param[in,out] rhs: right hand side of swap
     */
    void swap(bits& rhs) noexcept;
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      get bits size
     * @return     bits size
     */
    size_type size(void) const noexcept;
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      is empty
     * @return     true: empty, false: not empty
     */
    bool empty(void) const noexcept;
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      convert bits data into string
     * @return     converted string.
     * @note       bits b(4, 0xA5); b.str(); => "0101"
     *             bits b(8, 0xA5); b.str(); => "1010 0101"
     *             bits b(4, [0xA5], 0); b.str(); => "1010"
     *             bits b(4, [0xA5], 4); b.str(); => "0101"
     */
    std::string str(void) const;
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      reverse bits
     * @note       bits(8, 0x12).reverse(); => "0100 1000"
     */
    void reverse(void) noexcept;
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      inverse bits
     * @note       bits(8, 0x12).inverse(); => "1110 1101"
     */
    void inverse(void) noexcept;
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      remove all bits
     */
    void clear(void) noexcept;
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      set all bits 0 or 1
     * @param[in]  value: true means 1, false means 0
     */
    void set_all(bool value) noexcept;
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      pop some bits from MSB side and get integer
     * @param[in]  length: appointed length of bits. should be <= 64
     * @return     popped integer.
     * @note       bits(8, 0x12).pop_msb(4); => return 1, remain bits(4, 0x02)
     */
    int_type pop_msb(size_type length) noexcept;
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      pop some bits from LSB side and get integer
     * @param[in]  length: appointed length of bits. should be <= 64
     * @return     popped integer.
     * @note       bits(8, 0x12).pop_lsb(4); => return 2, remain bits(4, 0x01)
     */
    int_type pop_lsb(size_type length) noexcept;
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      pick some bits from start with length and get integer
     * @param[in]  start: appointed start index of bits. starts with 0
     * @param[in]  length: appointed length of bits. should be <= 64
     * @return     referred integer.
     * @note       bits(8, 0xA5).refer(2, 4); => return 9
     */
    int_type refer(size_type start, size_type length) const noexcept;
    /////////////////////////////////////////////////////////////////////////////

private:
    std::deque<bool> value_;
    /////////////////////////////////////////////////////////////////////////////

};
/////////////////////////////////////////////////////////////////////////////

} // namespace ken3 {

#endif // #ifndef INCLUDE_GUARD_KEN3_BITS_HPP

