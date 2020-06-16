cmake_minimum_required(VERSION 3.10)
project(boostGrepCommand LANGUAGES CXX)

set(BOOST_MIN_VERSION "1.66.0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

find_package(Boost ${BOOST_MIN_VERSION} COMPONENTS
        context coroutine date_time thread system program_options regex REQUIRED)

link_directories(${Boost_LIBRARY_DIRS})
include_directories(${Boost_INCLUDE_DIRS})

set(DEPENDENCIES ${CMAKE_DL_LIBS} ${Boost_LIBRARIES})

set(ReSOURCES main.cpp)

add_executable(boostGrepCommand ${ReSOURCES})

target_link_libraries(boostGrepCommand ${DEPENDENCIES})

set_target_properties(
        boostGrepCommand PROPERTIES
        FOLDER Bin
        OUTPUT_NAME boost-grepCommand
)
