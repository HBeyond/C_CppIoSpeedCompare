cmake_minimum_required(VERSION 3.2)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

###############################################################################
# 1. Project Basic
###############################################################################
# project name and version
set(PRJ_VERSION_MAJOR 0)
set(PRJ_VERSION_MINOR 1)
set(PRJ_VERSION_PATCH 0)
set(PRJ_VERSION ${PRJ_VERSION_MAJOR}.${PRJ_VERSION_MINOR}.${PRJ_VERSION_PATCH})
project(readWriteSpeed VERSION ${PRJ_VERSION})

# parse and print project version info
if (${CMAKE_VERSION} VERSION_LESS 3.12)
    set(CMAKE_PROJECT_VERSION ${PRJ_VERSION})
    set(CMAKE_PROJECT_VERSION_MAJOR ${PRJ_VERSION_MAJOR})
    set(CMAKE_PROJECT_VERSION_MINOR ${PRJ_VERSION_MINOR})
    set(CMAKE_PROJECT_VERSION_PATCH ${PRJ_VERSION_PATCH})
endif ()
message(STATUS "Project Version: " ${CMAKE_PROJECT_VERSION})

###############################################################################
# 2. Options
###############################################################################
set(OUTPUT_PREFIX "" CACHE PATH "Output prefix")
set(EXE_OUTPUT_PATH "bin" CACHE STRING "Executable output path")
set(LIB_OUTPUT_PATH "lib" CACHE STRING "Library output path")
set(APP_NAME "${PROJECT_NAME}" CACHE STRING "Application name")

###############################################################################
# 3. Libraries
###############################################################################
# find packages for basic libraries
find_package(Gflags REQUIRED)           # gflags
find_package(Glog REQUIRED)             # glog
find_package(OpenCV 3 REQUIRED)         # OpenCV

# dependency include directories and libraries
# dependency includes
 list(APPEND DEPEND_INCLUDES
        ${GLOG_INCLUDE_DIRS}
        ${GFLAGS_INCLUDE_DIRS}
        ${OpenCV_INCLUDE_DIRS}
        )

# dependent libs, append them into a list named APPEND DEPEND_LIBS
list(APPEND DEPEND_LIBS
        ${GLOG_LIBRARIES}
        ${GFLAGS_LIBRARIES}
        ${OpenCV_LIBRARIES}
        )

###############################################################################
# 4. Build Setting
###############################################################################
# default built type
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE RELEASE)
endif ()
message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")

# build setting
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# output bin and lib path
if (NOT OUTPUT_PREFIX)
    set(OUTPUT_PREFIX ${CMAKE_BINARY_DIR})
endif ()
if (NOT EXE_OUTPUT_PATH)
    set(EXE_OUTPUT_PATH "bin")
endif ()
if (NOT LIB_OUTPUT_PATH)
    set(LIB_OUTPUT_PATH "lib")
endif ()
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_PREFIX}/${EXE_OUTPUT_PATH})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_PREFIX}/${LIB_OUTPUT_PATH})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_PREFIX}/${LIB_OUTPUT_PATH})
MESSAGE("Executable Output Path: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
MESSAGE("Library Output Path: ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")
# application name
if (NOT APP_NAME)
    set(APP_NAME ${PROJECT_NAME})
endif ()

# install prefix
set(CMAKE_INSTALL_PREFIX ${OUTPUT_PREFIX})

# add some other folder to contain some other excutable file
# subdirectory must contain sub-level CMakeLists.txt
add_subdirectory(1_C_Read)
add_subdirectory(3_C_Write)
add_subdirectory(5_Cpp_Read)
add_subdirectory(7_Cpp_Write)
