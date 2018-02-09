#include <ctime>
#include <string>
#include <iostream>
#include <thread>
#include "ken3/pystr.hpp"
#include "ken3/stopwatch.hpp"

int main(int argc, char** argv)
{
    ken3::stopwatch sw(true);
    // do something --->
    std::this_thread::sleep_for(std::chrono::seconds(1));
    // <--- do something
    std::cout << sw.s(); // => about 1

    auto v = ken3::pystr::split("1 2 333");
    for (const auto& i: v) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    return 0;
}
