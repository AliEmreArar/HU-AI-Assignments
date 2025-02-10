#ifndef ROUTEPLANNER_H
#define ROUTEPLANNER_H

#include "Map.h"
#include "Stack.h"
#include "Queue.h"
#include <vector>
#include <string>

class RoutePlanner {

public:
    Map map;
    Stack stack;
    Queue queue;
    int maxDistance;              // Maximum allowed travel distance
    int totalDistanceCovered;     // Tracks the total distance of the route
    std::vector<int> route;
    std::vector<int> max_route;// Vector to store the route in order of visitation

    // Constants for priority and weather-restricted provinces
    static const int MAX_PRIORITY_PROVINCES = 10;
    static const int MAX_WEATHER_RESTRICTED_PROVINCES = 10;

    // Arrays to store priority and restricted provinces
    int priorityProvinces[MAX_PRIORITY_PROVINCES]{};
    int weatherRestrictedProvinces[MAX_WEATHER_RESTRICTED_PROVINCES]{};
    int numPriorityProvinces;      // Count of priority provinces loaded
    int numWeatherRestrictedProvinces; // Count of restricted provinces loaded

    RoutePlanner(const std::string& distance_data, const std::string& priority_data, const std::string& restricted_data, int maxDistance); // Constructor

    // Starts exploring the route from the starting province
    void exploreRoute(int start);

    // Displays the final results of the journey
    void displayResults() const;

    void printNeighbors(int provinceIndex, int maxDistance) const;

    void printWeatherRestricted(int province) const;

    // Helper functions
    void exploreFromProvince(int province);  // Explores from a specific province
    void enqueueNeighbors(int province);     // Adds reachable neighbors to the queue
    void backtrack();                        // Backtracks if no further moves are possible
    bool isExplorationComplete() const;      // Checks if exploration is complete

    // Constraint-related functions
    void loadPriorityProvinces(const std::string& filename);
    void loadWeatherRestrictedProvinces(const std::string& filename);
    bool isPriorityProvince(int province) const;
    bool isWeatherRestricted(int province) const;
    int calculateRoad(std::vector<int> max_route) const;
};

#endif // ROUTEPLANNER_H
