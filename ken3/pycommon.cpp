/**
 * @file    ken3/pycommon.cpp
 * @brief   Define some classes which are used in other py*** codes.
 *          ken3::py::Exception <=> python's Exception
 *          ken3::py::ValueError <=> python's ValueError
 *          ken3::py::IndexError <=> python's IndexError
 *          ken3::py::TypeError <=> python's TypeError
 * @author  toda
 * @date    2019-12-22
 * @version 0.1.0
 * @remark  the target is C++11 or more.
 */

#include "ken3/pycommon.hpp"

namespace ken3 {
namespace py {

/**
 * @brief       constructor. 
 * @param[in]   msg: message for what(). 
 */
Exception::Exception(const std::string& msg) :
    std::runtime_error(std::string("Exception: ") + msg)
{
    ;
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief       constructor. 
 * @param[in]   msg: message for what(). 
 */
ValueError::ValueError(const std::string& msg) :
    Exception(std::string("ValueError: ") + msg)
{
    ;
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief       constructor. 
 * @param[in]   msg: message for what(). 
 */
IndexError::IndexError(const std::string& msg) :
    Exception(std::string("IndexError: ") + msg)
{
    ;
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief       constructor. 
 * @param[in]   msg: message for what(). 
 */
TypeError::TypeError(const std::string& msg) :
    Exception(std::string("TypeError: ") + msg)
{
    ;
}
/////////////////////////////////////////////////////////////////////////////

} // namespace py {
} // namespace ken3 {
