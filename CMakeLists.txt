cmake_minimum_required(VERSION 3.28)
project(dino)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(BUILD_SHARED_LIBS FALSE)
set(CMAKE_SOURCE_DIR src/)


include(FetchContent)

FetchContent_Declare(
        fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt
        GIT_TAG 10.2.1
)
FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML
        GIT_TAG 2.6.1
)

FetchContent_MakeAvailable(fmt SFML)



add_executable(
        dino 
        src/main.cpp 
        src/Object.h src/Object.cpp
        src/Score.h src/Score.cpp
        src/Game.h src/Game.cpp
        src/Menu.h src/Menu.cpp 
        src/Run.h src/Run.cpp
        src/ObjectManager.h src/ObjectManager.cpp
        src/Button.h src/Button.cpp

        src/Dino.h src/Dino.cpp

        src/assets.h
)

target_link_libraries(dino fmt sfml-window sfml-graphics sfml-audio)

