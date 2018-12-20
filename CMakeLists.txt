cmake_minimum_required(VERSION 3.12)
project(Topforce)

set(CMAKE_CXX_STANDARD 17)

#Set extra flags
set(GCC_COVERAGE_COMPILE_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")

#Windows specific parametes
if (WIN32)
    set(SFML_DIR "C:/SFML-2.5.1/lib/cmake/SFML")
    set(SFML_STATIC_LIBRARIES TRUE)
endif (WIN32)

#Find SFML packages
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

#Add spdlog library
include_directories(vendor/spdlog/include)
link_directories(vendor/spdlog/include)

#Add cource and header files
add_executable(Topforce main.cpp Headers.hpp)

#Link library's
target_link_libraries(Topforce sfml-graphics sfml-audio)
