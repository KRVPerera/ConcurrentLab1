cmake_minimum_required(VERSION 3.4)
project(ConcurrentTHLab_1)

set(CMAKE_CXX_STANDARD 14)
set(RW_SOURCES src/ReadWriteList.cpp include/ReadWriteList.h src/ReadWriteDriver.cpp include/ReadWriteDriver.h)
set(MUTEX_SOURCES src/MutexList.cpp include/MutexList.h src/MutexDriver.cpp include/MutexDriver.h)
set(SERIAL_SOURCES src/SerialList.cpp include/SerialList.h src/SerialDriver.cpp include/SerialDriver.h)

set(GCC_FLAGS "-lpthread")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_FLAGS}")
set(SOURCE_FILES src/main.cpp src/LinkedList.cpp include/LinkedList.h src/Node.cpp include/Node.h src/Util.cpp include/Util.h ${SERIAL_SOURCES} ${MUTEX_SOURCES} ${RW_SOURCES} include/Common.h)
add_executable(ConcurrentTHLab_1 ${SOURCE_FILES})
target_link_libraries(ConcurrentTHLab_1 pthread)