cmake_minimum_required(VERSION 3.6)
project(ConcurrentTHLab_1)

set(CMAKE_CXX_STANDARD 14)
set(RW_SOURCES ReadWriteList.cpp ReadWriteList.h ReadWriteDriver.cpp ReadWriteDriver.h)
set(MUTEX_SOURCES MutexList.cpp MutexList.h MutexDriver.cpp MutexDriver.h)
set(SERIAL_SOURCES SerialList.cpp SerialList.h SerialDriver.cpp SerialDriver.h)

set(GCC_FLAGS "-lpthread")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_FLAGS}")
set(SOURCE_FILES main.cpp LinkedList.cpp LinkedList.h Node.cpp Node.h Util.cpp Util.h ${SERIAL_SOURCES} ${MUTEX_SOURCES} ${RW_SOURCES})
add_executable(ConcurrentTHLab_1 ${SOURCE_FILES})
target_link_libraries(ConcurrentTHLab_1 pthread)