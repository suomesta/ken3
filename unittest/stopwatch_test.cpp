/**
 * @file    unittest/stopwatch_test.cpp
 * @brief   Testing ken3::stopwatch using lest. 
 * @author  toda
 * @date    2018-01-26
 * @version 0.1.0
 * @remark  the target is C++11 or more
 */

#include <thread>
#include "ken3/stopwatch.hpp"
#include "unittest/lest.hpp"

namespace {

/**
 * @brief      check whether elapsed time is within range or not.
 *             the range is [expected time, expected time * 1.05].
 * @param[in]  elapsed: actual elapsed time.
 * @param[in]  expected: expected time.
 * @return     true: within range, false: not within range.
 */
bool within_range(double elapsed, double estimated)
{
    return ((estimated <= elapsed) && (elapsed <= estimated * 1.05));
}

} // namespace {

const lest::test specification[] =
{

    CASE("minimum functions")
    {
        using ken3::stopwatch;

        stopwatch sw(true);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        EXPECT(within_range(sw.ms(), 100.0));

        sw.stop();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        EXPECT(within_range(sw.ms(), 100.0));

        sw.start();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        EXPECT(within_range(sw.ms(), 200.0));

        sw.stop();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        EXPECT(within_range(sw.ms(), 200.0));
    },

    CASE("constructor")
    {
        using ken3::stopwatch;

        {
            stopwatch sw(true);
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            EXPECT(within_range(sw.ms(), 100.0));
        }

        {
            stopwatch sw(false);
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            EXPECT(within_range(sw.ms(), 0.0));
        }

        {
            stopwatch sw;
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            EXPECT(within_range(sw.ms(), 100.0));
        }
    },

    CASE("copy constructor")
    {
        using ken3::stopwatch;

        stopwatch sw1(true);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        stopwatch sw2(sw1);
        EXPECT(within_range(sw2.ms(), 100.0));
    },

    CASE("move constructor")
    {
        using ken3::stopwatch;

        stopwatch sw1(true);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        stopwatch sw2(std::move(sw1));
        EXPECT(within_range(sw2.ms(), 100.0));
    },

    CASE("copy operator=")
    {
        using ken3::stopwatch;

        stopwatch sw1(true);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        stopwatch sw2(false);
        sw2 = sw1;
        EXPECT(within_range(sw2.ms(), 100.0));
    },

    CASE("move operator=")
    {
        using ken3::stopwatch;

        stopwatch sw1(true);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        stopwatch sw2(false);
        sw2 = std::move(sw1);
        EXPECT(within_range(sw2.ms(), 100.0));
    },

    CASE("operator()")
    {
        using ken3::stopwatch;

        stopwatch sw(true);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        auto duration = sw();
        std::chrono::duration<double> d = duration;
        EXPECT(within_range(d.count(), 0.1));
    },

    CASE("swap()")
    {
        using ken3::stopwatch;

        stopwatch sw1(true);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        stopwatch sw2(true);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        EXPECT(within_range(sw1.ms(), 200.0));
        EXPECT(within_range(sw2.ms(), 100.0));
        sw1.swap(sw2);
        EXPECT(within_range(sw1.ms(), 100.0));
        EXPECT(within_range(sw2.ms(), 200.0));
    },

    CASE("start()")
    {
        using ken3::stopwatch;

        stopwatch sw(false);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        sw.start();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        EXPECT(within_range(sw.ms(), 100.0));

        sw.start(); // no effect
        EXPECT(within_range(sw.ms(), 100.0));
    },

    CASE("stop()")
    {
        using ken3::stopwatch;

        stopwatch sw(true);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        sw.stop();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        EXPECT(within_range(sw.ms(), 100.0));

        sw.stop(); // no effect
        EXPECT(within_range(sw.ms(), 100.0));
    },

    CASE("clear()")
    {
        using ken3::stopwatch;

        {
            stopwatch sw(true);
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            sw.clear(true);
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            EXPECT(within_range(sw.ms(), 100.0));
        }

        {
            stopwatch sw(true);
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            sw.clear(false);
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            EXPECT(within_range(sw.ms(), 0.0));
        }

        {
            stopwatch sw;
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            sw.clear();
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            EXPECT(within_range(sw.ms(), 100.0));
        }
    },

    CASE("ns()")
    {
        using ken3::stopwatch;

        stopwatch sw(true);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        EXPECT(within_range(sw.ns(), 100000000.0));
    },

    CASE("us()")
    {
        using ken3::stopwatch;

        stopwatch sw(true);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        EXPECT(within_range(sw.us(), 100000.0));
    },

    CASE("ms()")
    {
        using ken3::stopwatch;

        stopwatch sw(true);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        EXPECT(within_range(sw.ms(), 100.0));
    },

    CASE("s()")
    {
        using ken3::stopwatch;

        stopwatch sw(true);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        EXPECT(within_range(sw.s(), 0.1));
    },

};

int main(int argc, char* argv[])
{
    return lest::run(specification, argc, argv);
}
/////////////////////////////////////////////////////////////////////////////

