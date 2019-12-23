/**
 * @file    ken3/pycommon.hpp
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

#ifndef INCLUDE_GUARD_KEN3_PYCOMMON_HPP
#define INCLUDE_GUARD_KEN3_PYCOMMON_HPP

#include <stdexcept>

namespace ken3 {
namespace py {

/**
 * @class Exception
 * @brief An exception which imitates Python Exception. 
 * @extends std::runtime_error. 
 */
struct Exception : public std::runtime_error
{
    /**
     * @brief       constructor. 
     * @param[in]   msg: message for what(). 
     */
    explicit Exception(const std::string& msg);
};
/////////////////////////////////////////////////////////////////////////////

/**
 * @class ValueError
 * @brief An exception which imitates Python ValueError. 
 * @extends ken3::py::Exception. 
 */
struct ValueError : public Exception
{
    /**
     * @brief       constructor. 
     * @param[in]   msg: message for what(). 
     */
    explicit ValueError(const std::string& msg);
};
/////////////////////////////////////////////////////////////////////////////

/**
 * @class IndexError
 * @brief An exception which imitates Python IndexError. 
 * @extends ken3::py::Exception. 
 */
struct IndexError : public Exception
{
    /**
     * @brief       constructor. 
     * @param[in]   msg: message for what(). 
     */
    explicit IndexError(const std::string& msg);
};
/////////////////////////////////////////////////////////////////////////////

/**
 * @class TypeError
 * @brief An exception which imitates Python TypeError. 
 * @extends ken3::py::Exception. 
 */
struct TypeError : public Exception
{
    /**
     * @brief       constructor. 
     * @param[in]   msg: message for what(). 
     */
    explicit TypeError(const std::string& msg);
};
/////////////////////////////////////////////////////////////////////////////

} // namespace py {
} // namespace ken3 {

#endif // #ifndef INCLUDE_GUARD_KEN3_PYCOMMON_HPP
