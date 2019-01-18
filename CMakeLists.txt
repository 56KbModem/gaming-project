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
    link_directories(vendor/spdlog/include lib/windows/)
endif (WIN32)

#Find SFML packages
find_package(SFML 2.5 COMPONENTS graphics audio network system REQUIRED)

#Add library's
include_directories(vendor/spdlog/include vendor/tmxlite/include)

if(UNIX)
    link_directories(vendor/spdlog/include lib/macos/)
endif(UNIX)
#Add cource and header files
add_executable(Topforce main.cpp topforce.hpp gui/menu.hpp gui/main_menu.cpp gui/main_menu.hpp log.cpp log.hpp level/map_graphics.cpp level/map_graphics.hpp abstracts/screen_object.hpp abstracts/screen_object.cpp character/character.hpp character/character.cpp abstracts/moveable_screen_object.cpp abstracts/moveable_screen_object.hpp gui/topforce_window.cpp gui/topforce_window.h)


#Link library's
target_link_libraries(Topforce sfml-graphics sfml-audio sfml-network sfml-system tmxlite)
