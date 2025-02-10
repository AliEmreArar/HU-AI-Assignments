cmake_minimum_required(VERSION 3.10)

project(HUSLAND VERSION 1.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Enable debugging flags
set(CMAKE_CXX_FLAGS_DEBUG "-g")

# Add source files
set(SOURCES
    main.cpp
    Map.cpp
    Isle.cpp
    RealmShaper.cpp
    RealmShapers.cpp
    GameWorld.cpp
    #Questions.cpp
)

set(HEADERS
    Map.h
    Isle.h
    RealmShaper.h
    RealmShapers.h
    GameWorld.h
    #Questions.h
)

# Add the executable
add_executable(HUSLAND ${SOURCES} ${HEADERS})

# Include directories (for headers)
target_include_directories(HUSLAND PRIVATE ${CMAKE_SOURCE_DIR})

# Set build type to Debug
set(CMAKE_BUILD_TYPE Debug)
