#include <iostream>
//
//#include "Questions.h"
#include "Isle.h"
#include "GameWorld.h"
#include "RealmShaper.h"

#define NUMBER_OF_INPUTS 4
#define NUMBER_OF_OUTPUTS 4

int main(int argc, char **argv)
{
    /*
    Questions quiz = Questions();
    RealmShaper* player = new RealmShaper("husland", 1000);
    quiz.singlePlayerDemo(player);

    return 0;
    */

    if (argc < (NUMBER_OF_INPUTS + NUMBER_OF_OUTPUTS + 1))
    {
        std::cerr << "[Main] " << "Not enough arguments" << std::endl;
    }

    std::string placesFile = argv[1];
    std::string playersFile = argv[2];

    std::vector<Isle *> places = Isle::readFromFile(placesFile);
    std::vector<RealmShaper *> players = RealmShaper::readFromFile(playersFile);
    GameWorld gameWorld = GameWorld();
    gameWorld.initializeGame(places, players);
    //gameWorld.displayGameState();
    gameWorld.processGameEvents(argv[3], argv[4]);
    gameWorld.saveGameState(argv[5], argv[6], argv[7], argv[8]);
}