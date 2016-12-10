cmake_minimum_required(VERSION 3.6)
project(ConcurrentTHLab_1)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp LinkedList.cpp LinkedList.h Node.cpp Node.h SerialList.cpp SerialList.h MutexList.cpp MutexList.h Util.cpp Util.h SerialDriver.cpp SerialDriver.h)
add_executable(ConcurrentTHLab_1 ${SOURCE_FILES})