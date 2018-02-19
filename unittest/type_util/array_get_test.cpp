/**
 * @file    unittest/type_util/array_get_test.cpp
 * @brief   Testing ken3::array_get() using lest.
 * @author  toda
 * @date    2017-07-21
 * @version 0.1.0
 * @remark  the target is C++11 or more
 */

#include "ken3/type_util.hpp"
#include "unittest/lest.hpp"

const lest::test module[] =
{

    CASE("array_get() with non-const array")
    {
        using ken3::array_get;

        short array[3] = {11, 222, 3333};
        EXPECT(11 == array_get<0>(array));
        EXPECT(222 == array_get<1>(array));
        EXPECT(3333 == array_get<2>(array));

        EXPECT((std::is_same<short&, decltype(array_get<0>(array))>::value));
        EXPECT((std::is_same<short&, decltype(array_get<1>(array))>::value));
        EXPECT((std::is_same<short&, decltype(array_get<2>(array))>::value));
    },

    CASE("array_get() with const array")
    {
        using ken3::array_get;

        const short array[3] = {11, 222, 3333};
        EXPECT(11 == array_get<0>(array));
        EXPECT(222 == array_get<1>(array));
        EXPECT(3333 == array_get<2>(array));

        EXPECT((std::is_same<const short&, decltype(array_get<0>(array))>::value));
        EXPECT((std::is_same<const short&, decltype(array_get<1>(array))>::value));
        EXPECT((std::is_same<const short&, decltype(array_get<2>(array))>::value));
    },

};

extern lest::tests& specification();

MODULE(specification(), module)

