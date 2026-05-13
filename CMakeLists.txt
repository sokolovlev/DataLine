cmake_minimum_required(VERSION 4.0)
project(DataLine)

set(CMAKE_CXX_STANDARD 20)


if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(COMPILER_64_BIT TRUE)
else()
    SET(COMPILER_64_BIT FALSE)
endif()


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


if (MINGW)
    function(copy_mingw_dlls TARGET_NAME)
        get_filename_component(MINGW_BIN_DIR "${CMAKE_CXX_COMPILER}" DIRECTORY)
        if(COMPILLER_64_BIT)
            set(DLL_NAMES
                    "libstdc++-6.dll"
                    "libgcc_s_seh-1.dll"
                    "libwinpthread-1.dll"  #"libgcc_s_dw2-1.dll"  # Для MinGW 32-bit
            )

            foreach(DLL_NAME ${DLL_NAMES})
                set(DLL_PATHS
                        "${MINGW_BIN_DIR}/${DLL_NAME}"
                        "${MINGW_BIN_DIR}/../bin/${DLL_NAME}"
                        "${MINGW_BIN_DIR}/../${DLL_NAME}"
                        "C:/msys64/mingw64/bin/${DLL_NAME}"
                        "C:/mingw-w64/mingw64/bin/${DLL_NAME}"
                )

                set(DLL_FOUND "")
                foreach(PATH ${DLL_PATHS})
                    if(EXISTS "${PATH}")
                        set(DLL_FOUND "${PATH}")
                        break()
                    endif()
                endforeach()

                if(DLL_FOUND)
                    message(STATUS "Found ${DLL_NAME}: ${DLL_FOUND}")
                    add_custom_command(
                            TARGET ${TARGET_NAME} POST_BUILD
                            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                            "${DLL_FOUND}"
                            $<TARGET_FILE_DIR:${TARGET_NAME}>
                            COMMENT "Copying ${DLL_NAME} to output directory"
                    )
                else()
                    message(WARNING "Could not find ${DLL_NAME}")
                endif()
            endforeach()
        endif()
    endfunction()

    copy_mingw_dlls(your_target_name)
endif()

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