/**
 * @file    type_util/array_size_test.cpp
 * @brief   Testing ken3::array_size<> using lest. 
 * @author  toda
 * @date    2017-07-21
 * @version 0.1.0
 * @remark  the target is C++11 or more
 */

#include "ken3/type_util.hpp"
#include "unittest/lest.hpp"

const lest::test module[] =
{

    CASE("array_size<> with non-const array") 
    {
        using ken3::array_size;

        int array[3] = {1, 2, 3};
        EXPECT(3UL == array_size<decltype(array)>::value);
    },

    CASE("array_size<> with const array") 
    {
        using ken3::array_size;

        const double array[3] = {1.0, 2.0, 3.0};
        EXPECT(3UL == array_size<decltype(array)>::value);
    },

};

extern lest::tests& specification();

MODULE(specification(), module)

