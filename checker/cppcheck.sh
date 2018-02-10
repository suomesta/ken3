cd `dirname $0`

cppcheck --enable=all --suppress=unusedFunction --std=c++11 ../ken3/*.hpp ../ken3/*.cpp ../ken3/*/*.hpp ../ken3/*/*.cpp ../ken3/*/*/*.hpp ../ken3/*/*/*.cpp

