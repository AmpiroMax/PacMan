cmake_minimum_required(VERSION 3.10)

project(sfml-pacman)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

# Перечисляем все файлы проекта
set(SOURCES
    main.cpp
    src/Entity.cpp
    src/GameUI.cpp
    src/Ghost.cpp
    src/Level.cpp
    src/PacMan.cpp
    src/WorldObjects.cpp
)

add_executable(sfml-pacman ${SOURCES})

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
target_link_libraries(sfml-pacman sfml-system sfml-window sfml-graphics sfml-network sfml-audio)