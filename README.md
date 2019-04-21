# ken3

The C++ library ken3 includes many useful classes and functions.

## Getting Started

All ken3 source code depends on only c++11 standard.
Bazel is recommended to build and test ken3.

- angle: util angle class.
- biunique_map: useful expanded map class.
- bits: handling bit data.
- cast: supports some safe cast functions.
- counter: simple counter class which never overflows.
- metric: easy and flexible conversion between units.
- pyfunc: Python like functions min, max, all, any, sum, reduce, filter, and map.
- pyloop: functions to create Python like object for range-for statement.
- pystr: functions which imitate Python str function.
- stopwatch: simple but useful stopwatch using C++11 <chrono>.
- type_util: util classes and functions using C++11 <type_traits>.

## Installing

The source codes are in "ken3" directory.
If you already installed Bazel, all you have to do is typing "bazel build //ken3:all" in top directory.
If you do not have Bazel, you need to create Makefile. Although source code tree is plain, Bazel is better way.

## Running the tests

"bazel test //unittest:all" in top directory.

## And coding style tests

./checker/cppcheck/cppcheck.sh does cpp source code check. It requires cppcheck in your environment.
./checker/errortest/erroetest.sh does compiling error test. It requires python3 and g++ in your environment.
./checker/stylecheck/stylecheck.sh does coding style check. It requires python3 in your environment.

## Authors

toda
