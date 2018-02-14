/**
 * @file    bits_test.cpp
 * @brief   Testing ken3::bits using lest. 
 * @author  toda
 * @date    2018-01-29
 * @version 0.1.0
 * @remark  the target is C++11 or more
 */

#include "ken3/bits.hpp"
#include "unittest/lest.hpp"

const lest::test specification[] =
{

    CASE("minimum functions")
    {
        using ken3::bits;

        bits b;
        b += bits(6, 1);
        b += bits(6, 2);
        b += bits(6, 3);
        b += bits(6, 4);
        b += bits(6, 5);
        b += bits(6, 6);
        b += bits(6, 7);
        EXPECT(1UL == b.pop_msb(6));
        EXPECT(0UL == b.pop_msb(2));
        EXPECT(137430296UL == b.pop_msb(30));
        EXPECT(4UL == b.size());
    },

    CASE("constructor with size")
    {
        using ken3::bits;

        {
            bits b(5);
            EXPECT(5UL == b.size());
            EXPECT("00000" == b.str());
            EXPECT(0UL == b.refer(0, 5));
        }
        {
            bits b(0);
            EXPECT(0UL == b.size());
            EXPECT("" == b.str());
            EXPECT(0UL == b.refer(0, 1));
        }
        {
            bits b;
            EXPECT(0UL == b.size());
            EXPECT("" == b.str());
            EXPECT(0UL == b.refer(0, 1));
        }
    },

    CASE("constructor with size and integer")
    {
        using ken3::bits;

        {
            bits b(4, 0xA5);
            EXPECT(4UL == b.size());
            EXPECT("0101" == b.str());
            EXPECT(5UL == b.refer(0, 4));
        }
        {
            bits b(8, 0xA5);
            EXPECT(8UL == b.size());
            EXPECT("10100101" == b.str());
            EXPECT(165UL == b.refer(0, 8));
        }
        {
            bits b(100, 0x00);
            EXPECT(64UL == b.size());
            EXPECT("0000000000000000000000000000000000000000000000000000000000000000" == b.str());
            EXPECT(0UL == b.refer(0, 64));
        }
    },

    CASE("constructor with size and unsigned char array")
    {
        using ken3::bits;

        {
            unsigned char src[1] = {0xA5};
            bits b(4, src, 0);
            EXPECT(4UL == b.size());
            EXPECT("1010" == b.str());
            EXPECT(10UL == b.refer(0, 4));
        }
        {
            unsigned char src[1] = {0xA5};
            bits b(8, src, 0);
            EXPECT(8UL == b.size());
            EXPECT("10100101" == b.str());
            EXPECT(165UL == b.refer(0, 8));
        }
        {
            unsigned char src[1] = {0xA5};
            bits b(4, src, 4);
            EXPECT(4UL == b.size());
            EXPECT("0101" == b.str());
            EXPECT(5UL == b.refer(0, 4));
        }
        {
            unsigned char src[2] = {0xA5, 0xA5};
            bits b(8, src, 4);
            EXPECT(8UL == b.size());
            EXPECT("01011010" == b.str());
            EXPECT(90UL == b.refer(0, 8));
        }
    },

    CASE("constructor with string")
    {
        using ken3::bits;

        {
            bits b("");
            EXPECT(0UL == b.size());
            EXPECT("" == b.str());
            EXPECT(0UL == b.refer(0, 1));
        }
        {
            bits b("1010");
            EXPECT(4UL == b.size());
            EXPECT("1010" == b.str());
            EXPECT(10UL == b.refer(0, 4));
        }
        {
            bits b("01AB01");
            EXPECT(4UL == b.size());
            EXPECT("0101" == b.str());
            EXPECT(5UL == b.refer(0, 4));
        }
    },

    CASE("operator<")
    {
        using ken3::bits;

        {
            bits b1("");
            bits b2("");
            EXPECT(false == (b1 < b2));
            EXPECT(false == (b2 < b1));
        }
        {
            bits b1("0");
            bits b2("1");
            EXPECT(true == (b1 < b2));
            EXPECT(false == (b2 < b1));
        }
        {
            bits b1("0");
            bits b2("00");
            EXPECT(true == (b1 < b2));
            EXPECT(false == (b2 < b1));
        }
        {
            bits b1("01");
            bits b2("000");
            EXPECT(false == (b1 < b2));
            EXPECT(true == (b2 < b1));
        }
    },

    CASE("operator==")
    {
        using ken3::bits;

        {
            bits b1("");
            bits b2("");
            EXPECT(true == (b1 == b2));
            EXPECT(true == (b2 == b1));
        }
        {
            bits b1("0");
            bits b2("0");
            EXPECT(true == (b1 == b2));
            EXPECT(true == (b2 == b1));
        }
        {
            bits b1("0");
            bits b2("1");
            EXPECT(false == (b1 == b2));
            EXPECT(false == (b2 == b1));
        }
        {
            bits b1("0000");
            bits b2("0000");
            EXPECT(true == (b1 == b2));
            EXPECT(true == (b2 == b1));
        }
        {
            bits b1("000");
            bits b2("0000");
            EXPECT(false == (b1 == b2));
            EXPECT(false == (b2 == b1));
        }
        {
            bits b1("0000");
            bits b2("0010");
            EXPECT(false == (b1 == b2));
            EXPECT(false == (b2 == b1));
        }
    },

    CASE("operator+=")
    {
        using ken3::bits;

        {
            bits b1(4, 0x0A);
            bits b2(4, 0x05);
            b1 += b2;
            EXPECT(8UL == b1.size());
            EXPECT("10100101" == b1.str());
            EXPECT(165UL == b1.refer(0, 8));
        }
        {
            bits b1(2, 0x02);
            bits b2(4, 0x05);
            b1 += b2;
            EXPECT(6UL == b1.size());
            EXPECT("100101" == b1.str());
            EXPECT(37UL == b1.refer(0, 8));
        }
        {
            bits b1(4, 0x0A);
            bits b2;
            b1 += b2;
            EXPECT(4UL == b1.size());
            EXPECT("1010" == b1.str());
            EXPECT(10UL == b1.refer(0, 4));
        }
        {
            bits b1;
            bits b2(4, 0x05);
            b1 += b2;
            EXPECT(4UL == b1.size());
            EXPECT("0101" == b1.str());
            EXPECT(5UL == b1.refer(0, 4));
        }
    },

    CASE("operator+")
    {
        using ken3::bits;

        {
            bits b1(4, 0x0A);
            bits b2(4, 0x05);
            EXPECT(8UL == (b1 + b2).size());
            EXPECT("10100101" == (b1 + b2).str());
            EXPECT(165UL == (b1 + b2).refer(0, 8));
        }
        {
            bits b1(2, 0x02);
            bits b2(4, 0x05);
            EXPECT(6UL == (b1 + b2).size());
            EXPECT("100101" == (b1 + b2).str());
            EXPECT(37UL == (b1 + b2).refer(0, 8));
        }
        {
            bits b1(4, 0x0A);
            bits b2;
            EXPECT(4UL == (b1 + b2).size());
            EXPECT("1010" == (b1 + b2).str());
            EXPECT(10UL == (b1 + b2).refer(0, 4));
        }
        {
            bits b1;
            bits b2(4, 0x05);
            EXPECT(4UL == (b1 + b2).size());
            EXPECT("0101" == (b1 + b2).str());
            EXPECT(5UL == (b1 + b2).refer(0, 4));
        }
        {
            bits b = bits(2, 0x00) + bits(2, 0x01) + bits(2, 0x02) + bits(2, 0x03);
            EXPECT(8UL == b.size());
            EXPECT("00011011" == b.str());
            EXPECT(27UL == b.refer(0, 8));
        }
    },

    CASE("operator&=")
    {
        using ken3::bits;

        {
            bits b1(4, 0x0F);
            bits b2(4, 0x05);
            b1 &= b2;
            EXPECT(4UL == b1.size());
            EXPECT("0101" == b1.str());
            EXPECT(5UL == b1.refer(0, 4));
        }
        {
            bits b1(4, 0x0F);
            bits b2(2, 0x01);
            b1 &= b2;
            EXPECT(4UL == b1.size());
            EXPECT("0111" == b1.str());
            EXPECT(7UL == b1.refer(0, 4));
        }
        {
            bits b1(4, 0x0F);
            bits b2(8, 0xA5);
            b1 &= b2;
            EXPECT(4UL == b1.size());
            EXPECT("1010" == b1.str());
            EXPECT(10UL == b1.refer(0, 4));
        }
    },

    CASE("operator&")
    {
        using ken3::bits;

        {
            bits b1(4, 0x0F);
            bits b2(4, 0x05);
            EXPECT(4UL == (b1 & b2).size());
            EXPECT("0101" == (b1 & b2).str());
            EXPECT(5UL == (b1 & b2).refer(0, 4));
        }
        {
            bits b1(4, 0x0F);
            bits b2(2, 0x01);
            EXPECT(4UL == (b1 & b2).size());
            EXPECT("0111" == (b1 & b2).str());
            EXPECT(7UL == (b1 & b2).refer(0, 4));
        }
        {
            bits b1(4, 0x0F);
            bits b2(8, 0xA5);
            EXPECT(4UL == (b1 & b2).size());
            EXPECT("1010" == (b1 & b2).str());
            EXPECT(10UL == (b1 & b2).refer(0, 4));
        }
    },

    CASE("operator|=")
    {
        using ken3::bits;

        {
            bits b1(4, 0x03);
            bits b2(4, 0x05);
            b1 |= b2;
            EXPECT(4UL == b1.size());
            EXPECT("0111" == b1.str());
            EXPECT(7UL == b1.refer(0, 4));
        }
        {
            bits b1(4, 0x03);
            bits b2(2, 0x03);
            b1 |= b2;
            EXPECT(4UL == b1.size());
            EXPECT("1111" == b1.str());
            EXPECT(15UL == b1.refer(0, 4));
        }
        {
            bits b1(4, 0x03);
            bits b2(8, 0x3F);
            b1 |= b2;
            EXPECT(4UL == b1.size());
            EXPECT("0011" == b1.str());
            EXPECT(3UL == b1.refer(0, 4));
        }
    },

    CASE("operator|")
    {
        using ken3::bits;

        {
            bits b1(4, 0x03);
            bits b2(4, 0x05);
            EXPECT(4UL == (b1 | b2).size());
            EXPECT("0111" == (b1 | b2).str());
            EXPECT(7UL == (b1 | b2).refer(0, 4));
        }
        {
            bits b1(4, 0x03);
            bits b2(2, 0x03);
            EXPECT(4UL == (b1 | b2).size());
            EXPECT("1111" == (b1 | b2).str());
            EXPECT(15UL == (b1 | b2).refer(0, 4));
        }
        {
            bits b1(4, 0x03);
            bits b2(8, 0x3F);
            EXPECT(4UL == (b1 | b2).size());
            EXPECT("0011" == (b1 | b2).str());
            EXPECT(3UL == (b1 | b2).refer(0, 4));
        }
    },

    CASE("operator^=")
    {
        using ken3::bits;

        {
            bits b1(4, 0x03);
            bits b2(4, 0x05);
            b1 ^= b2;
            EXPECT(4UL == b1.size());
            EXPECT("0110" == b1.str());
            EXPECT(6UL == b1.refer(0, 4));
        }
        {
            bits b1(4, 0x03);
            bits b2(2, 0x03);
            b1 ^= b2;
            EXPECT(4UL == b1.size());
            EXPECT("1111" == b1.str());
            EXPECT(15UL == b1.refer(0, 4));
        }
        {
            bits b1(4, 0x03);
            bits b2(8, 0x3F);
            b1 ^= b2;
            EXPECT(4UL == b1.size());
            EXPECT("0000" == b1.str());
            EXPECT(0UL == b1.refer(0, 4));
        }
    },

    CASE("operator^")
    {
        using ken3::bits;

        {
            bits b1(4, 0x03);
            bits b2(4, 0x05);
            EXPECT(4UL == (b1 ^ b2).size());
            EXPECT("0110" == (b1 ^ b2).str());
            EXPECT(6UL == (b1 ^ b2).refer(0, 4));
        }
        {
            bits b1(4, 0x03);
            bits b2(2, 0x03);
            EXPECT(4UL == (b1 ^ b2).size());
            EXPECT("1111" == (b1 ^ b2).str());
            EXPECT(15UL == (b1 ^ b2).refer(0, 4));
        }
        {
            bits b1(4, 0x03);
            bits b2(8, 0x3F);
            EXPECT(4UL == (b1 ^ b2).size());
            EXPECT("0000" == (b1 ^ b2).str());
            EXPECT(0UL == (b1 ^ b2).refer(0, 4));
        }
    },

    CASE("operator<<=")
    {
        using ken3::bits;

        {
            bits b(4, 0x0A);
            b <<= 4;
            EXPECT(8UL == b.size());
            EXPECT("10100000" == b.str());
            EXPECT(160UL == b.refer(0, 8));
        }
        {
            bits b(4, 0x0A);
            b <<= 0;
            EXPECT(4UL == b.size());
            EXPECT("1010" == b.str());
            EXPECT(10UL == b.refer(0, 4));
        }
        {
            bits b;
            b <<= 4;
            EXPECT(4UL == b.size());
            EXPECT("0000" == b.str());
            EXPECT(0UL == b.refer(0, 4));
        }
    },

    CASE("operator<<")
    {
        using ken3::bits;

        {
            bits b(4, 0x0A);
            EXPECT(8UL == (b << 4).size());
            EXPECT("10100000" == (b << 4).str());
            EXPECT(160UL == (b << 4).refer(0, 8));
        }
        {
            bits b(4, 0x0A);
            EXPECT(4UL == (b << 0).size());
            EXPECT("1010" == (b << 0).str());
            EXPECT(10UL == (b << 0).refer(0, 4));
        }
        {
            bits b;
            EXPECT(4UL == (b << 4).size());
            EXPECT("0000" == (b << 4).str());
            EXPECT(0UL == (b << 4).refer(0, 4));
        }
    },

    CASE("operator>>=")
    {
        using ken3::bits;

        {
            bits b(4, 0x0A);
            b >>= 4;
            EXPECT(8UL == b.size());
            EXPECT("00001010" == b.str());
            EXPECT(10UL == b.refer(0, 8));
        }
        {
            bits b(4, 0x0A);
            b >>= 0;
            EXPECT(4UL == b.size());
            EXPECT("1010" == b.str());
            EXPECT(10UL == b.refer(0, 4));
        }
        {
            bits b;
            b >>= 4;
            EXPECT(4UL == b.size());
            EXPECT("0000" == b.str());
            EXPECT(0UL == b.refer(0, 4));
        }
    },

    CASE("operator>>")
    {
        using ken3::bits;

        {
            bits b(4, 0x0A);
            EXPECT(8UL == (b >> 4).size());
            EXPECT("00001010" == (b >> 4).str());
            EXPECT(10UL == (b >> 4).refer(0, 8));
        }
        {
            bits b(4, 0x0A);
            EXPECT(4UL == (b >> 0).size());
            EXPECT("1010" == (b >> 0).str());
            EXPECT(10UL == (b >> 0).refer(0, 4));
        }
        {
            bits b;
            EXPECT(4UL == (b >> 4).size());
            EXPECT("0000" == (b >> 4).str());
            EXPECT(0UL == (b >> 4).refer(0, 4));
        }
    },

    CASE("operator~")
    {
        using ken3::bits;

        {
            bits b(4, 0x0A);
            EXPECT(4UL == (~b).size());
            EXPECT("0101" == (~b).str());
            EXPECT(5UL == (~b).refer(0, 4));
        }
        {
            bits b;
            EXPECT(0UL == (~b).size());
            EXPECT("" == (~b).str());
            EXPECT(0UL == (~b).refer(0, 1));
        }
    },

    CASE("swap")
    {
        using ken3::bits;

        {
            bits b1(4, 0x0A);
            bits b2(8, 0x55);
            b1.swap(b2);
            EXPECT(8UL == b1.size());
            EXPECT("01010101" == b1.str());
            EXPECT(85UL == b1.refer(0, 8));
            EXPECT(4UL == b2.size());
            EXPECT("1010" == b2.str());
            EXPECT(10UL == b2.refer(0, 8));
        }
        {
            bits b1(8, 0xAA);
            bits b2;
            b1.swap(b2);
            EXPECT(0UL == b1.size());
            EXPECT("" == b1.str());
            EXPECT(0UL == b1.refer(0, 1));
            EXPECT(8UL == b2.size());
            EXPECT("10101010" == b2.str());
            EXPECT(170UL == b2.refer(0, 8));
        }
    },

    CASE("size")
    {
        using ken3::bits;

        {
            bits b(4, 0x0A);
            EXPECT(4UL == b.size());
            b += bits(4, 0x05);
            EXPECT(8UL == b.size());
            b <<= 4;
            EXPECT(12UL == b.size());
        }
        {
            bits b;
            EXPECT(0UL == b.size());
        }
    },

    CASE("empty")
    {
        using ken3::bits;

        {
            bits b(4, 0x0A);
            EXPECT(not b.empty());
            b += bits(4, 0x05);
            EXPECT(not b.empty());
            b.clear();
            EXPECT(b.empty());
            b <<= 4;
            EXPECT(not b.empty());
        }
        {
            bits b;
            EXPECT(b.empty());
        }
    },

    CASE("str")
    {
        using ken3::bits;

        {
            bits b(4, 0x0A);
            EXPECT("1010" == b.str());
            b += bits(4, 0x05);
            EXPECT("10100101" == b.str());
            b <<= 4;
            EXPECT("101001010000" == b.str());
        }
        {
            bits b;
            EXPECT("" == b.str());
        }
    },

    CASE("reverse")
    {
        using ken3::bits;

        {
            bits b(4, 0x0A);
            b.reverse();
            EXPECT(4UL == b.size());
            EXPECT("0101" == b.str());
            EXPECT(5UL == b.refer(0, 4));
        }
        {
            bits b;
            b.reverse();
            EXPECT(0UL == b.size());
            EXPECT("" == b.str());
            EXPECT(0UL == b.refer(0, 1));
        }
    },

    CASE("inverse")
    {
        using ken3::bits;

        {
            bits b(4, 0x0A);
            b.inverse();
            EXPECT(4UL == b.size());
            EXPECT("0101" == b.str());
            EXPECT(5UL == b.refer(0, 4));
        }
        {
            bits b;
            b.inverse();
            EXPECT(0UL == b.size());
            EXPECT("" == b.str());
            EXPECT(0UL == b.refer(0, 1));
        }
    },

    CASE("inverse")
    {
        using ken3::bits;

        {
            bits b(4, 0x0A);
            EXPECT(4UL == b.size());
            b.clear();
            EXPECT(0UL == b.size());
        }
        {
            bits b;
            b.clear();
            EXPECT(0UL == b.size());
        }
    },

    CASE("set_all")
    {
        using ken3::bits;

        {
            bits b(4, 0x0A);
            b.set_all(true);
            EXPECT(4UL == b.size());
            EXPECT("1111" == b.str());
            EXPECT(15UL == b.refer(0, 4));
        }
        {
            bits b(4, 0x0A);
            b.set_all(false);
            EXPECT(4UL == b.size());
            EXPECT("0000" == b.str());
            EXPECT(0UL == b.refer(0, 4));
        }
        {
            bits b;
            b.set_all(true);
            EXPECT(0UL == b.size());
            EXPECT("" == b.str());
            EXPECT(0UL == b.refer(0, 1));
        }
    },

    CASE("pop_msb")
    {
        using ken3::bits;

        {
            bits b(8, 0xA5);
            bits::int_type ret = b.pop_msb(4);
            EXPECT(10UL == ret);
            EXPECT(4UL == b.size());
            EXPECT("0101" == b.str());
            EXPECT(5UL == b.refer(0, 4));
        }
        {
            bits b(8, 0xA5);
            bits::int_type ret = b.pop_msb(2);
            EXPECT(2UL == ret);
            EXPECT(6UL == b.size());
            EXPECT("100101" == b.str());
            EXPECT(37UL == b.refer(0, 6));
        }
        {
            bits b(8, 0xA5);
            bits::int_type ret = b.pop_msb(8);
            EXPECT(165UL == ret);
            EXPECT(0UL == b.size());
            EXPECT("" == b.str());
            EXPECT(0UL == b.refer(0, 1));
        }
        {
            bits b;
            bits::int_type ret = b.pop_msb(16);
            EXPECT(0UL == ret);
            EXPECT(0UL == b.size());
            EXPECT("" == b.str());
            EXPECT(0UL == b.refer(0, 1));
        }
        {
            bits b(100);
            bits::int_type ret = b.pop_msb(100);
            EXPECT(0UL == ret);
            EXPECT(36UL == b.size());
            EXPECT("000000000000000000000000000000000000" == b.str());
            EXPECT(0UL == b.refer(0, 36));
        }
    },

    CASE("pop_lsb")
    {
        using ken3::bits;

        {
            bits b(8, 0xA5);
            bits::int_type ret = b.pop_lsb(4);
            EXPECT(5UL == ret);
            EXPECT(4UL == b.size());
            EXPECT("1010" == b.str());
            EXPECT(10UL == b.refer(0, 4));
        }
        {
            bits b(8, 0xA5);
            bits::int_type ret = b.pop_lsb(2);
            EXPECT(1UL == ret);
            EXPECT(6UL == b.size());
            EXPECT("101001" == b.str());
            EXPECT(41UL == b.refer(0, 6));
        }
        {
            bits b(8, 0xA5);
            bits::int_type ret = b.pop_lsb(8);
            EXPECT(165UL == ret);
            EXPECT(0UL == b.size());
            EXPECT("" == b.str());
            EXPECT(0UL == b.refer(0, 1));
        }
        {
            bits b;
            bits::int_type ret = b.pop_lsb(16);
            EXPECT(0UL == ret);
            EXPECT(0UL == b.size());
            EXPECT("" == b.str());
            EXPECT(0UL == b.refer(0, 1));
        }
        {
            bits b(100);
            bits::int_type ret = b.pop_lsb(100);
            EXPECT(0UL == ret);
            EXPECT(36UL == b.size());
            EXPECT("000000000000000000000000000000000000" == b.str());
            EXPECT(0UL == b.refer(0, 36));
        }
    },

    CASE("refer")
    {
        using ken3::bits;

        {
            bits b("10100101");
            EXPECT(165UL == b.refer(0, 8));
            EXPECT(165UL == b.refer(0, 100));
            EXPECT(10UL == b.refer(0, 4));
            EXPECT(9UL == b.refer(2, 4));
            EXPECT(5UL == b.refer(4, 4));
            EXPECT(0UL == b.refer(0, 0));
            EXPECT(0UL == b.refer(2, 0));
            EXPECT(0UL == b.refer(100, 8));
        }
        {
            const unsigned char a[9] = {0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA};
            bits b(sizeof(a) * 8, a, 0);
            EXPECT(0xAAAAAAAAAAAAAAAA == b.refer(0, 65));
        }
    },

};

int main(int argc, char* argv[])
{
    return lest::run(specification, argc, argv);
}
/////////////////////////////////////////////////////////////////////////////

