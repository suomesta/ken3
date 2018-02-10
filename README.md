# ken3

The c++ library ken3 includes some useful functions.

## Getting Started

All ken3 source code depends on only c++11 standard.
It is recommended to build ken3 by Bazel.

bits: handling bit data.
metric: easy and portable conversion between units.
pystr: functions which imitate python str function.
stopwatch: simple but useful stopwatch using c++11 chrono.

### Installing

The source codes are in "ken3" directory.
If you already installed Bazel, all you have to do is typing "bazel build //ken3:all" in top directory.
If you do not have Bazel, you need to create Makefile. Although source code tree is plain, Bazel is better way.

## Running the tests

"bazel test //unittest:all" in top directory.

### And coding style tests

./checker/cppcheck/cppcheck.sh does cpp source code check. It requires cppcheck in your environment.
./checker/errortest/erroetest.sh does compiling error test. It requires python3 and g++ in your environment.

## Authors

toda

