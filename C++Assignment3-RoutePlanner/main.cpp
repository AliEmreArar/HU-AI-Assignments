#include "RoutePlanner.h"
#include <iostream>
#include <string>

int main(int argc, char** argv) {
    if (argc < 6) {
        std::cerr << "Usage: " << argv[0] << " <maxDistance> <startingCity> <distance_data> <priority_data> <restricted_data>" << std::endl;
        return 1;
    }
    // Parse the maximum allowed travel distance and the starting city index
    int maxDistance = std::stoi(argv[1]);
    int startingCity = std::stoi(argv[2]);
    // Parse the file paths
    std::string distance_data = argv[3]; // Path to the distance data file
    std::string priority_data = argv[4]; // Path to the txt file involves priority proviences
    std::string restricted_data = argv[5]; // Path to the xt file involves weather restricted proviences

    // Initialize the RoutePlanner with the file and max distance constraint
    RoutePlanner planner(distance_data, priority_data, restricted_data, maxDistance);

    // Start exploring the route from the specified starting city
    planner.exploreRoute(startingCity);

    return 0;
}
