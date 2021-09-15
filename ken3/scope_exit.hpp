/**
 * @file    ken3/scope_exit.hpp
 * @brief   Implementation of scope_exit class. 
 *          scope_exit instance calls registered function in destructor. 
 *          It is useful to do exit operation certaily.
 * @author  toda
 * @date    2021-09-15
 * @version 0.1.0
 * @remark  the target is C++11 or more.
 *
 * @note
 * One useful example is;
 *     FILE* fp = fopen('filename', 'r');
 *     {
 *         scope_exit close_file(
 *             [=]() {
 *                 if (fp != nullptr) {
 *                     fclose(fp);
 *                     fp = nullptr;
 *                 }
 *              }
 *         );
 *
 *         ; // do something
 *
 *     } // when exiting scope, call registered lambda and close fp cetainly
 */

#ifndef INCLUDE_GUARD_KEN3_SCOPE_EXIT_HPP
#define INCLUDE_GUARD_KEN3_SCOPE_EXIT_HPP

#include <functional>

namespace ken3 {

/**
 * @class   scope_exit
 * @brief   scope_exit class holds a function and calls it in its destructor.
 */
class scope_exit
{
private:
    // type definitions
    using func = std::function<void()>;
    /////////////////////////////////////////////////////////////////////////////

public:
    /**
     * @brief      constructor with one argument. registers a function
     * @param[in]  func_in: a function to be registered
     */
    explicit scope_exit(func func_in);
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      destructor. calls registered function
     */
    ~scope_exit();
    /////////////////////////////////////////////////////////////////////////////

private:
    func f_; // registered function
};
/////////////////////////////////////////////////////////////////////////////

} // namespace ken3 {

#endif // #ifndef INCLUDE_GUARD_KEN3_SCOPE_EXIT_HPP
