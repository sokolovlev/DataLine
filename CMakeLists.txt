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
        "techOps.h"
        techOps.cpp
        #test.cpp
)

target_link_options(DataLine PRIVATE -static-libstdc++ -static-libgcc)


add_custom_command(
        TARGET DataLine
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:DataLine>/input"
        COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:DataLine>/tech"
        COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:DataLine>/output"
)