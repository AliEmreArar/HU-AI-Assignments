#include "RoutePlanner.h"
#include <iostream>
#include <fstream>

// Array to help you out with name of the cities in order
const std::string cities[81] = { 
    "Adana", "Adiyaman", "Afyon", "Agri", "Amasya", "Ankara", "Antalya", "Artvin", "Aydin", "Balikesir", "Bilecik", 
    "Bingol", "Bitlis", "Bolu", "Burdur", "Bursa", "Canakkale", "Cankiri", "Corum", "Denizli", "Diyarbakir", "Edirne", 
    "Elazig", "Erzincan", "Erzurum", "Eskisehir", "Gaziantep", "Giresun", "Gumushane", "Hakkari", "Hatay", "Isparta", 
    "Mersin", "Istanbul", "Izmir", "Kars", "Kastamonu", "Kayseri", "Kirklareli", "Kirsehir", "Kocaeli", "Konya", "Kutahya", 
    "Malatya", "Manisa", "Kaharamanmaras", "Mardin", "Mugla", "Mus", "Nevsehir", "Nigde", "Ordu", "Rize", "Sakarya", 
    "Samsun", "Siirt", "Sinop", "Sivas", "Tekirdag", "Tokat", "Trabzon", "Tunceli", "Urfa", "Usak", "Van", "Yozgat", 
    "Zonguldak", "Aksaray", "Bayburt", "Karaman", "Kirikkale", "Batman", "Sirnak", "Bartin", "Ardahan", "Igdir", 
    "Yalova", "Karabuk", "Kilis", "Osmaniye", "Duzce" 
};

// Constructor to initialize and load constraints
RoutePlanner::RoutePlanner(const std::string& distance_data, const std::string& priority_data, const std::string& restricted_data, int maxDistance)
    : maxDistance(maxDistance), totalDistanceCovered(0), numPriorityProvinces(0), numWeatherRestrictedProvinces(0) {

    map.loadDistanceData(distance_data);
    map.resetVisited();
    loadPriorityProvinces(priority_data);
    loadWeatherRestrictedProvinces(restricted_data);
}

// Load priority provinces from txt file to an array of indices
void RoutePlanner::loadPriorityProvinces(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open priority provinces file: " << filename << std::endl;
    }

    std::string line;
    while (std::getline(file, line) && numPriorityProvinces < MAX_PRIORITY_PROVINCES) {
        size_t start = line.find('(') + 1;
        size_t end = line.find(')');
        if (start != std::string::npos && end != std::string::npos) {
            std::string index = line.substr(start, end - start);
            priorityProvinces[numPriorityProvinces++] = std::stoi(index);
        }
    }

    file.close();
}

// Load weather-restricted provinces from txt file to an array of indices
void RoutePlanner::loadWeatherRestrictedProvinces(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open weather restricted provinces file: " << filename << std::endl;
    }

    std::string line;
    while (std::getline(file, line) && numWeatherRestrictedProvinces < MAX_PRIORITY_PROVINCES) {
        size_t start = line.find('(') + 1;
        size_t end = line.find(')');
        if (start != std::string::npos && end != std::string::npos) {
            std::string index = line.substr(start, end - start);
            weatherRestrictedProvinces[numWeatherRestrictedProvinces++] = std::stoi(index);
        }
    }

    file.close();
}

// Checks if a province is a priority province
bool RoutePlanner::isPriorityProvince(int province) const {
    for (int i = 0; i < numPriorityProvinces; ++i) {
        if (priorityProvinces[i] == province) {
            return true;
        }
    }
    return false;
}

// Checks if a province is weather-restricted
bool RoutePlanner::isWeatherRestricted(int province) const {
    for (int i = 0; i < numWeatherRestrictedProvinces; ++i) {
        if (weatherRestrictedProvinces[i] == province) {
            return true;
        }
    }
    return false;
}

// Begins the route exploration from the starting point
void RoutePlanner::exploreRoute(int startingCity) {
    map.resetVisited();
    totalDistanceCovered = 0;

    map.markAsVisited(startingCity);
    route.push_back(startingCity);
    stack.push(startingCity);

    exploreFromProvince(startingCity);

    displayResults();
}

// Helper function to explore from a specific province
void RoutePlanner::exploreFromProvince(int province) {
    int maxStackSize = 0;
    int currentStackSize = 0;
    while (!isExplorationComplete()) {

        enqueueNeighbors(province);

        if (queue.isEmpty()) {
            if (!stack.isEmpty()) {
                currentStackSize = stack.getSize();
                if (currentStackSize > maxStackSize) {
                    maxStackSize = currentStackSize;
                    max_route = route;
                }
                backtrack();

                if (!stack.isEmpty()) {
                    province = stack.peek();
                } else {
                    break;
                }
            } else {
                break;
            }
        } else {
            int nextProvince = queue.dequeue();

            if (nextProvince < 0 || nextProvince >= MAX_SIZE) {
                continue;
            }

            if (!map.isVisited(nextProvince) && map.isWithinRange(nextProvince,province,maxDistance)) {
                printWeatherRestricted(province);
                route.push_back(nextProvince);
                map.markAsVisited(nextProvince);
                stack.push(nextProvince);
                province = nextProvince;
            }
        }
    }
}


void RoutePlanner::enqueueNeighbors(int province) {
    for (int i = 0; i < MAX_SIZE; i++) {

        if (map.isWithinRange(province, i, maxDistance)) {

            if (map.isVisited(i) || isWeatherRestricted(i)) {
                continue;
            }

            if (isPriorityProvince(i)) {
                queue.enqueuePriority(i);
            } else {
                queue.enqueue(i);
            }
        }
    }
}

void RoutePlanner::backtrack() {
    if (!stack.isEmpty()) {
        stack.pop();
    }
}

bool RoutePlanner::isExplorationComplete() const {

    return(queue.isEmpty() && stack.isEmpty());
}

void RoutePlanner::displayResults() const {

    std::cout << "----------------------------" << std::endl;
    std::cout << "Journey Completed!" << std::endl;
    std::cout << "----------------------------" << std::endl;
    std::cout << "Total Number of Provinces Visited: " << max_route.size() << std::endl;
    std::cout << "Total Distance Covered: " << calculateRoad(max_route) << " km" << std::endl;

    std::cout << "Route Taken:" << std::endl;
    for (size_t i = 0; i < max_route.size(); i++) {
        std::cout << cities[max_route[i]];
        if (i < max_route.size() - 1) {
            std::cout << " -> ";
        }
    }
    std::cout << std::endl;

    int visitedPriorityProvinces = 0;
    for (int i = 0; i < numPriorityProvinces; i++) {
        if (map.isVisited(priorityProvinces[i])) {
            visitedPriorityProvinces++;
        }
    }

    std::cout << "\nPriority Provinces Status:" << std::endl;
    for (int i = 0; i < numPriorityProvinces; i++) {
        std::cout << "- " << cities[priorityProvinces[i]] << " ("
                  << (map.isVisited(priorityProvinces[i]) ? "Visited" : "Not Visited") << ")" << std::endl;
    }
    std::cout << "\nTotal Priority Provinces Visited: " << visitedPriorityProvinces << " out of " << numPriorityProvinces << std::endl;

    if (visitedPriorityProvinces == numPriorityProvinces) {
        std::cout << "Success: All priority provinces were visited." << std::endl;
    } else {
        std::cout << "Failure: Not all priority provinces were visited." << std::endl;
    }
}

void RoutePlanner::printNeighbors(int provinceIndex, int maxDistance) const {
    std::cout << "Neighbors of province " << cities[provinceIndex]<<" "<< provinceIndex << " within distance " << maxDistance << ":\n";
    for (int i = 0; i < MAX_SIZE; i++) {
        int distance = map.getDistance(provinceIndex, i);
        if (distance != -1 && distance <= maxDistance && provinceIndex != i) {
            std::cout << "- Province " << cities[i]<< " "<< i << " (Distance: " << distance << ")\n";
        }
    }
}

void RoutePlanner::printWeatherRestricted(int province) const {
    for (int i = 0; i < MAX_SIZE; i++) {
        if (map.isWithinRange(province, i, maxDistance)) {
            if(isWeatherRestricted(i)) {
                std::cout << "Province "<<cities[i]<<" is weather-restricted. Skipping."<<std::endl;
            }
        }
    }
}

int RoutePlanner::calculateRoad(std::vector<int> max_route) const {
    int distance = 0;
    int preprovince = max_route[0];
    for(int province : max_route){
        distance += map.distanceMatrix[preprovince][province];
        preprovince = province;
    }
    return distance;
}


