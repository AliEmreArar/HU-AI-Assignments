#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include "Map.h"
#include "RealmShapers.h"

class GameWorld
{
private:
    Map mapTree;
    ShaperTree shaperTree;

public:
    // Constructor decleration
    GameWorld();

    // Getters
    Map& getMapTree();
    ShaperTree& getShaperTree();

    // Initilizes game by initilizing the trees
    void initializeGame(std::vector<Isle *> isles, std::vector<RealmShaper *> realmShapers);

    // Checks access for a realmShaper for an isle
    bool hasAccess(RealmShaper *realmShaper, Isle *isle);

    // Player explores existing area
    void exploreArea(RealmShaper *realmShaper, Isle *isle);

    // Player crafts none-existing Isle
    void craft(RealmShaper *shaper, const std::string &isleName);

    // Displays game state in terminal
    //void displayGameState();

    // 
    void processGameEvents(const std::string &accessLogs, const std::string &duelLogs);

    // Saves (writes) current game state to output files
    void saveGameState(const std::string &currentIsles, const std::string &currentWorld, const std::string &currentShapers, const std::string &currentPlayerTree);

    // TODO: Declare and implement functions to read and parse Access and Duel logs
};

#endif
