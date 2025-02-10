#include "GameWorld.h"

GameWorld::GameWorld() : mapTree(), shaperTree() {}

void GameWorld::initializeGame(std::vector<Isle *> places, std::vector<RealmShaper *> players)
{
    shaperTree.initializeTree(players);
    mapTree.initializeMap(places);
}

Map& GameWorld::getMapTree()
{
    return mapTree;
}
ShaperTree& GameWorld::getShaperTree()
{
    return shaperTree;
}

bool GameWorld::hasAccess(RealmShaper *realmShaper, Isle *isle)
{
    bool hasAccess = false;

    if (!realmShaper || !isle)
    {
        std::cout << "[Access Control] RealmShaper or Isle is null!" << std::endl;
        return false;
    }

    int playerDepth = shaperTree.getDepth(realmShaper);
    int totalShaperTreeHeight = shaperTree.getDepth();
    int totalMapDepth = mapTree.getDepth();
    //int isleHeight = mapTree.getHeight(isle);
    if (playerDepth == -1)
    {
        std::cout << "[Access Control] RealmShaper not found!" << std::endl;
        return false;
    }

    int minDepthAccess = mapTree.calculateMinMapDepthAccess(playerDepth, totalShaperTreeHeight, totalMapDepth);
    int isleDepth = mapTree.getIsleDepth(isle);
    //std::cout << "[Debug] Player Depth: " << playerDepth << " isle height: "<< isleHeight<< ", Total Shaper Tree Height: " << totalShaperTreeHeight << ", Total Map Depth: " << totalMapDepth << ", Min Depth Access: " << minDepthAccess << ", Isle Depth: " << isleDepth << std::endl;

    hasAccess = isleDepth >= minDepthAccess;
    return hasAccess;
}

void GameWorld::exploreArea(RealmShaper *realmShaper, Isle *isle)
{

    if (!hasAccess(realmShaper, isle))
    {
        std::cout << "[Explore Area] " << realmShaper->getName() << " does not have access to explore area " << *isle << std::endl;
        return;
    }

    if (!realmShaper->current_isle_name()) {
        realmShaper->set_current_isle_name(isle);

    }
    // if realmShaper explore another isle, previous isle count must be decreasing.
    if(realmShaper->current_isle_name()) {
        if(realmShaper->current_isle_name() != isle) {
            realmShaper->current_isle_name()->decreaseShaperCount();
            realmShaper->set_current_isle_name(isle);
            //std::cout<< "fddddddddfgggggfggffffffffffffffffffffff  " << realmShaper->current_isle_name()->getShaperCount()<< std::endl;
        }
    }

    realmShaper->collectItem(isle->getItem());

    std::cout << "[Explore Area] " << realmShaper->getName() << " visited " << isle->getName() << std::endl;
    std::cout << "[Energy] " << realmShaper->getName() << "'s new energy level is " << realmShaper->getEnergyLevel() << std::endl;

    if (isle->increaseShaperCount())
    {
        std::cout << "[Overcrowding] " << isle->getName() << " self-destructed, it will be removed from the map" << std::endl;
        mapTree.remove(isle);
        //std::cout<<mapTree.lastBalance <<"   "<< mapTree.balancedNumber<< std::endl;
        if(mapTree.lastBalance && mapTree.balancedNumber % 3 == 0) {
            mapTree.populateWithItems();
            mapTree.dropItemBFS();
            mapTree.lastBalance = false;
        }
    }
}

void GameWorld::craft(RealmShaper *shaper, const std::string &isleName){
    if (shaper->hasEnoughEnergy())
    {
        std::cout << "[Energy] " << shaper->getName() << " has enough energy points: " << shaper->getEnergyLevel() << std::endl;
        Isle *newIsle = new Isle(isleName);
        mapTree.insert(newIsle);
        //std::cout<<mapTree.lastBalance <<"   "<< mapTree.balancedNumber<< std::endl;

        if(mapTree.lastBalance && mapTree.balancedNumber % 3 == 0) {
            mapTree.populateWithItems();
            mapTree.dropItemBFS();
            mapTree.lastBalance = false;
        }

        shaper->loseEnergy();
        std::cout << "[Craft] " << shaper->getName() << " crafted new Isle " << isleName << std::endl;
    }
    else
    {
        std::cout << "[Energy] " << shaper->getName() << " does not have enough energy points: " << shaper->getEnergyLevel() << std::endl;
    }
}
/*
void GameWorld::displayGameState()
{
    mapTree.displayMap();
    shaperTree.displayTree();
}
*/

void GameWorld::processGameEvents(const std::string &accessLogs, const std::string &duelLogs)
{
    std::ifstream accessFile(accessLogs);
    std::ifstream duelFile(duelLogs);

    if (!accessFile.is_open() || !duelFile.is_open())
    {
        std::cerr << "Error: Could not open log files." << std::endl;
        return;
    }

    std::string accessLine, duelLine;

    while (std::getline(accessFile, accessLine))
    {
        if (!accessLine.empty() && accessLine[0] != '#')
            break;
    }

    while (std::getline(duelFile, duelLine))
    {
        if (!duelLine.empty() && duelLine[0] != '#')
            break;
    }

    int accessCount = 0;

    do
    {
        if (accessLine.empty())
            continue;

        std::istringstream accessStream(accessLine);
        std::string shaperName, isleName;
        accessStream >> shaperName >> isleName;

        RealmShaper *shaper = shaperTree.findPlayer(shaperName);
        Isle *isle = mapTree.findIsle(isleName);

        if (shaper && isle)
        {
            exploreArea(shaper, isle);
            accessCount++;
        }

        if (isle == nullptr && shaper != nullptr)
        {
            craft(shaper, isleName);
            accessCount++;
        }

        if (accessCount % 5 == 0 && !duelLine.empty())
        {
            std::istringstream duelStream(duelLine);
            std::string challengerName;
            bool result;
            duelStream >> challengerName >> result;

            RealmShaper *challenger = shaperTree.findPlayer(challengerName);

            if (challenger)
            {
                shaperTree.duel(challenger, result);
            }


            if (!std::getline(duelFile, duelLine))
                duelLine.clear();
        }
    } while (std::getline(accessFile, accessLine));


    while (std::getline(duelFile, duelLine))
    {

        std::istringstream duelStream(duelLine);
        std::string challengerName;
        bool result;
        duelStream >> challengerName >> result;

        RealmShaper *challenger = shaperTree.findPlayer(challengerName);

        if (challenger)
        {
            shaperTree.duel(challenger, result);
        }
    }

    //displayGameState();
}


void GameWorld::saveGameState(const std::string &currentIsles, const std::string &currentWorld, const std::string &currentShapers, const std::string &currentPlayerTree)
{
    mapTree.writeIslesToFile(currentIsles);
    mapTree.writeToFile(currentWorld);
    shaperTree.writeToFile(currentPlayerTree);
    shaperTree.writeShapersToFile(currentShapers);
}