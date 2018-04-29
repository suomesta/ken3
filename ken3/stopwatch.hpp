/**
 * @file    ken3/stopwatch.hpp
 * @brief   Implementation of stopwatch class. 
 *          stopwatch can measure elapsed time. 
 * @author  toda
 * @date    2018-01-17
 * @version 0.1.0
 * @remark  the target is C++11 or more.
 * @remark  stopwatch class is completely exception free.
 *
 * @note
 * Typical usage is;
 *     ken3::stopwatch sw(true);
 *     // do something --->
 *     std::this_thread::sleep_for(std::chrono::seconds(1));
 *     // <--- do something
 *     std::cout << sw.s(); // => about 1
 *
 * stopwatch supports to stop/start running.
 *     ken3::stopwatch sw(true);
 *     std::this_thread::sleep_for(std::chrono::milliseconds(100));
 *     sw.stop();
 *     // sleep for 200 ms does not affect stopwatch, because it has been stopped
 *     std::this_thread::sleep_for(std::chrono::milliseconds(200));
 *     sw.start();
 *     std::this_thread::sleep_for(std::chrono::milliseconds(400));
 *     std::cout << sw.ms(); // => about 500
 */

#ifndef INCLUDE_GUARD_KEN3_STOPWATCH_HPP
#define INCLUDE_GUARD_KEN3_STOPWATCH_HPP

#include <chrono>

namespace ken3 {

/**
 * @class   stopwatch
 * @brief   stopwatch can measure elapsed time based on C++11 <chrono>.
 *          stopwatch supports start/stop, and getter of elapsed time in
 *          ns, us, ms, and s.
 * @note    this class is completely exception free..
 */
class stopwatch
{
public:
    // type defines
    using duration = std::chrono::steady_clock::duration;
    using time_point = std::chrono::steady_clock::time_point;
    /////////////////////////////////////////////////////////////////////////////

public:
    /**
     * @brief      constructor with one optional argument.
     * @param[in]  start: if true, stopwatch starts in this constructor
     */
    explicit stopwatch(bool start=true) noexcept;
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      copy-constructor, move-constructor, destructor, copy-operator=,
     *             and move-operator= are default.
     */
    stopwatch(const stopwatch& src) = default;
    stopwatch(stopwatch&& src) = default;
    ~stopwatch(void) = default;
    stopwatch& operator=(const stopwatch& rhs) = default;
    stopwatch& operator=(stopwatch&& rhs) = default;
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      operator()
     * @return     elapsed time since start time.
     *             type of return value is std::chrono::duration.
     */
    duration operator()(void) const noexcept;
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      swap with another
     * @param[in,out] rhs: right hand side of swap
     */
    void swap(stopwatch& rhs) noexcept;
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      start stop watch. start time is recorded
     *             if stop watch is already started, then no effect
     */
    void start(void) noexcept;
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      stop stop watch.
     *             if stop watch is already stopped, then no effect
     */
    void stop(void) noexcept;
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      clear stop watch.
     *             same behavior and argument with constructor
     */
    void clear(bool start=true) noexcept;
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      get elapsed time in nano seconds.
     * @return     elapsed time in nano seconds
     * @note       return value is from operator()
     */
    double ns(void) const noexcept;
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      get elapsed time in micro seconds.
     * @return     elapsed time in micro seconds
     * @note       return value is from operator()
     */
    double us(void) const noexcept;
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      get elapsed time in milli seconds.
     * @return     elapsed time in milli seconds
     * @note       return value is from operator()
     */
    double ms(void) const noexcept;
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      get elapsed time in seconds.
     * @return     elapsed time in seconds
     * @note       return value is from operator()
     */
    double s(void) const noexcept;
    /////////////////////////////////////////////////////////////////////////////

private:
    bool running_; // a flag which indicates stopwatch is running or stopped
    time_point started_; // start time point. this is valid only when running_ is true
    duration accumulation_; // accumulation time. this is valid only when running_ is false
};
/////////////////////////////////////////////////////////////////////////////

} // namespace ken3 {

#endif // #ifndef INCLUDE_GUARD_KEN3_STOPWATCH_HPP

