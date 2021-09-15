/**
 * @file    ken3/scope_exit.cpp
 * @brief   Implementation of scope_exit class. 
 *          scope_exit instance calls registered function in destructor. 
 *          It is useful to do exit operation certaily.
 * @author  toda
 * @date    2021-09-15
 * @version 0.1.0
 * @remark  the target is C++11 or more.
 */

#include "ken3/scope_exit.hpp"

namespace ken3 {

/**
 * @brief      constructor with one argument. registers a function
 * @param[in]  func_in: a function to be registered
 */
scope_exit::scope_exit(scope_exit::func func_in) :
    f_(func_in)
{
    ;
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief      destructor. calls registered function
 */
scope_exit::~scope_exit()
{
    f_();
}
/////////////////////////////////////////////////////////////////////////////

} // namespace ken3 {
