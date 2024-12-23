cmake_minimum_required(VERSION 3.30)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(ArcadeGame VERSION 1.0)


include_directories(${CMAKE_SOURCE_DIR})

set(SOURCES
    main.cpp
    game_mode.cpp
game_mode.h
	spaceinvaders.cpp
spaceinvaders.h
abst_games.h
	game_window.cpp
game_window.h
game_player.cpp
game_player.h
game_bullet.cpp
game_bullet.h
blackjack.cpp
blackjack.h
breakout.h
game_buffer.h
)

add_executable(ArcadeGame ${SOURCES})

target_compile_definitions(ArcadeGame PRIVATE UNICODE _UNICODE)