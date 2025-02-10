cmake_minimum_required(VERSION 3.22)
project(AsteroidDash)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)

# Enable debugging flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

add_executable(AsteroidDash
        AsteroidDash.cpp
        AsteroidDash.h
        CelestialObject.cpp
        CelestialObject.h
        GameController.cpp
        GameController.h
        Leaderboard.cpp
        Leaderboard.h
        LeaderboardEntry.cpp
        LeaderboardEntry.h
        Player.cpp
        Player.h
        main.cpp
)
