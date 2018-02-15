/**
 * @file    type_util_test.cpp
 * @brief   Testing ken3::type_util using lest. 
 * @author  toda
 * @date    2017-07-21
 * @version 0.1.0
 * @remark  the target is C++11 or more
 */

#include "unittest/lest.hpp"

lest::tests& specification(void)
{
    static lest::tests tests;
    return tests;
}
/////////////////////////////////////////////////////////////////////////////

int main(int argc, char* argv[])
{
    return lest::run(specification(), argc, argv);
}
/////////////////////////////////////////////////////////////////////////////

