/**
 * @file    ken3/stopwatch.cpp
 * @brief   Implementation of stopwatch class. 
 *          stopwatch can measure elapsed time. 
 * @author  toda
 * @date    2018-01-17
 * @version 0.1.0
 * @remark  the target is C++11 or more.
 */

#include <ratio>
#include <utility>
#include "ken3/stopwatch.hpp"

namespace {

/**
 * @brief      helper function to convert period.
 *             own_duration will be converted from stopwatch::duration::period into TARGET_DURATION::period
 * @param[in]  own_duration: appointed duration in std::chrono::steady_clock::duration
 * @return     scaling own_duration.count()
 */
template <typename TARGET_DURATION>
double duration_in(const ken3::stopwatch::duration& own_duration) noexcept
{
    using here_ratio = std::ratio_divide<typename ken3::stopwatch::duration::period, typename TARGET_DURATION::period>;
    constexpr double scaling = static_cast<double>(here_ratio::num) / static_cast<double>(here_ratio::den);
    return own_duration.count() * scaling;
}
/////////////////////////////////////////////////////////////////////////////

} // namespace {

namespace ken3 {

/**
 * @brief      constructor with one optional argument.
 * @param[in]  start: if true, stopwatch starts in this constructor
 */
stopwatch::stopwatch(bool start/*=true*/) noexcept :
    started_(start ? std::chrono::steady_clock::now() : time_point()),
    accumulation_(duration::zero())
{
    ;
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief      operator()
 * @return     elapsed time since start time.
 *             type of return value is std::chrono::duration.
 */
stopwatch::duration stopwatch::operator()(void) const noexcept
{
    if (started_ != time_point()) { // now running
        return (std::chrono::steady_clock::now() - started_) + accumulation_;
    }
    else {
        return accumulation_;
    }
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief      swap with another
 * @param[in,out] rhs: right hand side of swap
 */
void stopwatch::swap(stopwatch& rhs) noexcept
{
    std::swap(started_, rhs.started_);
    std::swap(accumulation_, rhs.accumulation_);
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief      start stop watch. start time is recorded
 *             if stop watch is already started, then no effect
 */
void stopwatch::start(void) noexcept
{
    if (started_ != time_point()) { // now running
        ; // do nothing here
    }
    else {
        started_ = std::chrono::steady_clock::now();
    }
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief      stop stop watch.
 *             if stop watch is already stopped, then no effect
 */
void stopwatch::stop(void) noexcept
{
    if (started_ != time_point()) { // now running
        accumulation_ += std::chrono::steady_clock::now() - started_;
        started_ = time_point();
    }
    else {
        ; // do nothing here
    }
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief      reset stop watch.
 *             same behavior and argument with constructor
 */
void stopwatch::reset(bool start/*=true*/) noexcept
{
    started_ = start ? std::chrono::steady_clock::now() : time_point();
    accumulation_ = duration::zero();
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief      get elapsed time in nano seconds.
 * @return     elapsed time in nano seconds
 * @note       return value is from operator()
 */
double stopwatch::ns(void) const noexcept
{
    return duration_in<std::chrono::nanoseconds>((*this)());
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief      get elapsed time in micro seconds.
 * @return     elapsed time in micro seconds
 * @note       return value is from operator()
 */
double stopwatch::us(void) const noexcept
{
    return duration_in<std::chrono::microseconds>((*this)());
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief      get elapsed time in milli seconds.
 * @return     elapsed time in milli seconds
 * @note       return value is from operator()
 */
double stopwatch::ms(void) const noexcept
{
    return duration_in<std::chrono::milliseconds>((*this)());
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief      get elapsed time in seconds.
 * @return     elapsed time in seconds
 * @note       return value is from operator()
 */
double stopwatch::s(void) const noexcept
{
    return duration_in<std::chrono::seconds>((*this)());
}
/////////////////////////////////////////////////////////////////////////////

} // namespace ken3 {
