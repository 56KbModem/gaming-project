cmake_minimum_required(VERSION 3.12)
project(Topforce)

set(CMAKE_CXX_STANDARD 17)

#Set extra flags
set(GCC_COVERAGE_COMPILE_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")

if (CMAKE_BUILD_TYPE MATCHES Debug)
    add_definitions(-DDEBUG=1)
endif()

#Windows specific parameters
if (WIN32)
    set(CMAKE_EXE_LINKER_FLAGS "-static")
    set(SFML_DIR "C:/SFML-2.5.1/lib/cmake/SFML")
    set(SFML_STATIC_LIBRARIES TRUE)
endif (WIN32)

#Find SFML packages
find_package(SFML 2.5 COMPONENTS graphics audio network REQUIRED)

#Add spdlog library
include_directories(vendor/spdlog/include)
link_directories(vendor/spdlog/include)

#Add cource and header files
if (CMAKE_BUILD_TYPE MATCHES Debug)
    add_executable(Topforce main.cpp topforce.hpp gui/menu.hpp gui/main_menu.cpp gui/main_menu.hpp log.cpp log.hpp networking/client.hpp networking/client.cpp)
endif()

if (CMAKE_BUILD_TYPE MATCHES Server)
    add_executable(Topforce networking/main.cpp networking/topForceServer.hpp networking/topForceServer.cpp log.cpp log.hpp)
endif()

#Link library's
target_link_libraries(Topforce sfml-graphics sfml-audio sfml-network)
