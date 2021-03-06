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
endif ()

#OSX specific parameters
if (APPLE)
    link_directories(vendor/spdlog/include lib/unix/)
endif ()

#Unix/Linux specific parameters
if (UNIX AND NOT APPLE)
    set(SFML_DIR "/usr/local/lib/SFML-2.5.1/lib/cmake/SFML")
    link_directories(vendor/spdlog/include lib/unix/)
endif ()

#Find SFML packages
find_package(SFML 2.5 COMPONENTS graphics audio network system REQUIRED)

#Add library's
include_directories(vendor/spdlog/include vendor/tmxlite/include)

#Add source and header files
if (CMAKE_BUILD_TYPE MATCHES Debug)
    add_executable(Topforce main.cpp Topforce.hpp gui/Menu.hpp gui/MainMenu.cpp gui/MainMenu.hpp Log.cpp Log.hpp level/MapGraphics.cpp level/MapGraphics.hpp abstracts/ScreenObject.hpp abstracts/ScreenObject.cpp character/Player.hpp character/Player.cpp abstracts/MoveableScreenObject.cpp abstracts/MoveableScreenObject.hpp gui/TopforceWindow.cpp gui/TopforceWindow.hpp character/Weapon.cpp character/Weapon.hpp gamemodes/FreeForAll.cpp gamemodes/FreeForAll.hpp abstracts/GameMode.cpp abstracts/GameMode.hpp gui/HUD.cpp gui/HUD.hpp SoundManager.cpp SoundManager.hpp ImageManager.cpp ImageManager.hpp networking/Client.hpp networking/Client.cpp abstracts/Character.cpp abstracts/Character.hpp gui/ScoreBoard.cpp gui/ScoreBoard.hpp gui/ScoreBox.cpp gui/ScoreBox.hpp)
endif()

if (CMAKE_BUILD_TYPE MATCHES Release)
    add_executable(Topforce main.cpp Topforce.hpp gui/Menu.hpp gui/MainMenu.cpp gui/MainMenu.hpp Log.cpp Log.hpp level/MapGraphics.cpp level/MapGraphics.hpp abstracts/ScreenObject.hpp abstracts/ScreenObject.cpp character/Player.hpp character/Player.cpp abstracts/MoveableScreenObject.cpp abstracts/MoveableScreenObject.hpp gui/TopforceWindow.cpp gui/TopforceWindow.hpp character/Weapon.cpp character/Weapon.hpp gamemodes/FreeForAll.cpp gamemodes/FreeForAll.hpp abstracts/GameMode.cpp abstracts/GameMode.hpp gui/HUD.cpp gui/HUD.hpp SoundManager.cpp SoundManager.hpp ImageManager.cpp ImageManager.hpp networking/Client.hpp networking/Client.cpp abstracts/Character.cpp abstracts/Character.hpp gui/ScoreBoard.cpp gui/ScoreBoard.hpp gui/ScoreBox.cpp gui/ScoreBox.hpp)
endif()

if (CMAKE_BUILD_TYPE MATCHES Server)
    add_definitions(-DDEBUG=1)
    add_executable(Topforce networking/main.cpp networking/server.hpp networking/server.cpp Log.cpp Log.hpp)
endif()

#Link library's
target_link_libraries(Topforce sfml-graphics sfml-audio sfml-network sfml-system tmxlite)