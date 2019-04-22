/**
 * @file    unittest/type_util/const_reference_test.cpp
 * @brief   Testing is_const_reference<>, is_const_lvalue_reference<>,
 *          is_const_rvalue_reference<>, and is_const_pointer<> using lest. 
 * @author  toda
 * @date    2019-04-21
 * @version 0.1.0
 * @remark  the target is C++11 or more
 */

#include "ken3/type_util.hpp"
#include "unittest/lest.hpp"

const lest::test module[] =
{

    CASE("is_const_reference<>") 
    {
        using ken3::is_const_reference;
        struct empty {};

        EXPECT(false == is_const_reference<int>::value);
        EXPECT(false == is_const_reference<const int>::value);
        EXPECT(false == is_const_reference<int*>::value);
        EXPECT(false == is_const_reference<const int*>::value);
        EXPECT(false == is_const_reference<int&>::value);
        EXPECT(false == is_const_reference<int&&>::value);
        EXPECT(true == is_const_reference<const int&>::value);
        EXPECT(true == is_const_reference<const int&&>::value);

        EXPECT(false == is_const_reference<empty>::value);
        EXPECT(false == is_const_reference<const empty>::value);
        EXPECT(false == is_const_reference<empty*>::value);
        EXPECT(false == is_const_reference<const empty*>::value);
        EXPECT(false == is_const_reference<empty&>::value);
        EXPECT(false == is_const_reference<empty&&>::value);
        EXPECT(true == is_const_reference<const empty&>::value);
        EXPECT(true == is_const_reference<const empty&&>::value);
    },

    CASE("is_const_lvalue_reference<>") 
    {
        using ken3::is_const_lvalue_reference;
        struct empty {};

        EXPECT(false == is_const_lvalue_reference<int>::value);
        EXPECT(false == is_const_lvalue_reference<const int>::value);
        EXPECT(false == is_const_lvalue_reference<int*>::value);
        EXPECT(false == is_const_lvalue_reference<const int*>::value);
        EXPECT(false == is_const_lvalue_reference<int&>::value);
        EXPECT(false == is_const_lvalue_reference<int&&>::value);
        EXPECT(true == is_const_lvalue_reference<const int&>::value);
        EXPECT(false == is_const_lvalue_reference<const int&&>::value);

        EXPECT(false == is_const_lvalue_reference<empty>::value);
        EXPECT(false == is_const_lvalue_reference<const empty>::value);
        EXPECT(false == is_const_lvalue_reference<empty*>::value);
        EXPECT(false == is_const_lvalue_reference<const empty*>::value);
        EXPECT(false == is_const_lvalue_reference<empty&>::value);
        EXPECT(false == is_const_lvalue_reference<empty&&>::value);
        EXPECT(true == is_const_lvalue_reference<const empty&>::value);
        EXPECT(false == is_const_lvalue_reference<const empty&&>::value);
    },

    CASE("is_const_rvalue_reference<>") 
    {
        using ken3::is_const_rvalue_reference;
        struct empty {};

        EXPECT(false == is_const_rvalue_reference<int>::value);
        EXPECT(false == is_const_rvalue_reference<const int>::value);
        EXPECT(false == is_const_rvalue_reference<int*>::value);
        EXPECT(false == is_const_rvalue_reference<const int*>::value);
        EXPECT(false == is_const_rvalue_reference<int&>::value);
        EXPECT(false == is_const_rvalue_reference<int&&>::value);
        EXPECT(false == is_const_rvalue_reference<const int&>::value);
        EXPECT(true == is_const_rvalue_reference<const int&&>::value);

        EXPECT(false == is_const_rvalue_reference<empty>::value);
        EXPECT(false == is_const_rvalue_reference<const empty>::value);
        EXPECT(false == is_const_rvalue_reference<empty*>::value);
        EXPECT(false == is_const_rvalue_reference<const empty*>::value);
        EXPECT(false == is_const_rvalue_reference<empty&>::value);
        EXPECT(false == is_const_rvalue_reference<empty&&>::value);
        EXPECT(false == is_const_rvalue_reference<const empty&>::value);
        EXPECT(true == is_const_rvalue_reference<const empty&&>::value);
    },

    CASE("is_const_pointer<>") 
    {
        using ken3::is_const_pointer;
        struct empty {};

        EXPECT(false == is_const_pointer<int>::value);
        EXPECT(false == is_const_pointer<const int>::value);
        EXPECT(false == is_const_pointer<int*>::value);
        EXPECT(true == is_const_pointer<const int*>::value);
        EXPECT(false == is_const_pointer<int&>::value);
        EXPECT(false == is_const_pointer<int&&>::value);
        EXPECT(false == is_const_pointer<const int&>::value);
        EXPECT(false == is_const_pointer<const int&&>::value);

        EXPECT(false == is_const_pointer<empty>::value);
        EXPECT(false == is_const_pointer<const empty>::value);
        EXPECT(false == is_const_pointer<empty*>::value);
        EXPECT(true == is_const_pointer<const empty*>::value);
        EXPECT(false == is_const_pointer<empty&>::value);
        EXPECT(false == is_const_pointer<empty&&>::value);
        EXPECT(false == is_const_pointer<const empty&>::value);
        EXPECT(false == is_const_pointer<const empty&&>::value);
    },

};

extern lest::tests& specification();

MODULE(specification(), module)

