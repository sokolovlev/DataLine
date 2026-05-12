cmake_minimum_required(VERSION 4.0)
project(DataLine)

set(CMAKE_CXX_STANDARD 20)

add_executable(DataLine main.cpp
        SeparatorClass.cpp
        SeparatorClass.h
        setLimit.h

        ManagerClass.cpp
        ManagerClass.h

        MergeSortedClass.cpp
        MergeSortedClass.h
        ConfigClass.cpp
        ConfigClass.h
        #test.cpp
)

#file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/input)
#file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/tech)
#file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/output)

#include(FetchContent)
#
#FetchContent_Declare(
#        googletest
#        GIT_REPOSITORY https://github.com/google/googletest.git
#        GIT_TAG        v1.17.0
#)
#
#if(_WIN32)
#    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
#endif()

#FetchContent_MakeAvailable(googletest)

#add_executable(my_tests test.cpp)
#target_link_libraries(my_tests PRIVATE gtest_main)

#enable_testing()
#add_test(NAME MyTests COMMAND my_tests)