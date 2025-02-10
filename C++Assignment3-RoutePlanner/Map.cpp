#include "Map.h"
#include <fstream>
#include <iostream>
#include <sstream>


Map::Map(){
    for (int i = 0; i < MAX_SIZE; ++i) {
        for (int j = 0; j < MAX_SIZE; ++j) {
            distanceMatrix[i][j] = -1;
        }
        visited[i] = false;
    }
}

// Loads distance data from a file and fills the distanceMatrix
void Map::loadDistanceData(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }

    std::string line;
    int row = 0;

    while (std::getline(file, line) && row < MAX_SIZE) {
        std::stringstream ss(line);
        std::string cell;
        int col = 0;

        while (std::getline(ss, cell, ',') && col < MAX_SIZE) {
            distanceMatrix[row][col] = std::stoi(cell);
            col++;
        }
        row++;
    }

    file.close();
}


// Checks if the distance between two provinces is within the allowed maxDistance
bool Map::isWithinRange(int provinceA, int provinceB, int maxDistance) const {
    if (provinceA < 0 || provinceA >= MAX_SIZE || provinceB < 0 || provinceB >= MAX_SIZE) {
        std::cerr << "Provinces are out of range is within range" << std::endl;
        return false;

    }
    int distance = distanceMatrix[provinceA][provinceB];
    return distance != -1 && distance <= maxDistance;
}

// Marks a province as visited
void Map::markAsVisited(int province) {
    if (province >= 0 && province < MAX_SIZE) {
        visited[province] = true;
        visited_counter++;
    }
}

// Checks if a province has already been visited
bool Map::isVisited(int province) const {
    if (province < 0 || province >= MAX_SIZE) {
        std::cerr << "Error: Invalid province index " << province << std::endl;
        return false;
    }
    return visited[province];
}

// Resets all provinces to unvisited
void Map::resetVisited() {
    for (bool & i : visited) {
        i = false;
    }
    visited_counter = 0;
}

// Function to count the number of visited provinces
int Map::countVisitedProvinces() const {
    return visited_counter;
}

// Function to get the distance between two provinces
int Map::getDistance(int provinceA, int provinceB) const {
    if((provinceA >= 0 && provinceA < MAX_SIZE) && (provinceB >= 0 && provinceB < MAX_SIZE)) {
        return distanceMatrix[provinceA][provinceB];
    }
    return 0;
}
