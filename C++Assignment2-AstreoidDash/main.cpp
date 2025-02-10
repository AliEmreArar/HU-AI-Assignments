#include "GameController.h"

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
    #include<windows.h>
#endif

// Main function that reads the necessary file names and the player name
// from command line arguments
int main(int argc, char** argv) {
    
    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
        SetConsoleOutputCP(CP_UTF8);
    #endif
    
    string space_grid_file = argv[1];
    string celestial_objects_file = argv[2];
    string player_file = argv[3];
    string commands_file = argv[4];
    string leaderboard_file = argv[5]; 
    string player_name = argv[6]; 

    GameController * controller = new GameController(
        space_grid_file,
        celestial_objects_file,
        leaderboard_file,
        player_file,
        player_name);
		
    controller->play(commands_file);
    delete controller;

}