cmake_minimum_required(VERSION 3.29)
project(DroneALPHA)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)

# Add source files
set(SOURCES
        main.cpp
        Map.cpp
        Queue.cpp
        RoutePlanner.cpp
        Stack.cpp
)

# Add header files (for clarity, not strictly required by CMake)
set(HEADERS
        Map.h
        Queue.h
        RoutePlanner.h
        Stack.h
)

# Include directories
include_directories(.)

# Define the executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Define custom commands for running the program with arguments
add_custom_target(run
        COMMAND ${PROJECT_NAME} 250 5 distance_data.csv priority_provinces.txt weather_restricted_provinces.txt
        DEPENDS ${PROJECT_NAME}
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMENT "Running DroneALPHA with arguments..."
)

# Define custom commands for running Valgrind
add_custom_target(valgrind
        COMMAND valgrind --leak-check=full --track-origins=yes ./${PROJECT_NAME} 250 5 distance_data.csv priority_provinces.txt weather_restricted_provinces.txt
        DEPENDS ${PROJECT_NAME}
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMENT "Running Valgrind on DroneALPHA..."
)

# Define custom commands for running GDB
add_custom_target(gdb
        COMMAND gdb --args ./${PROJECT_NAME} 250 5 distance_data.csv priority_provinces.txt weather_restricted_provinces.txt
        DEPENDS ${PROJECT_NAME}
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMENT "Running GDB on DroneALPHA..."
)
