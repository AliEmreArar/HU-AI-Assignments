#include "GameController.h"
#include <fstream>
#include <iostream>
#include <stdexcept>

using namespace std;

// Simply instantiates the game
GameController::GameController(
        const string &space_grid_file_name,
        const string &celestial_objects_file_name,
        const string &leaderboard_file_name,
        const string &player_file_name,
        const string &player_name

) {
    game = new AsteroidDash(space_grid_file_name, celestial_objects_file_name, leaderboard_file_name, player_file_name, player_name);
    // TODO: Your code here, if you want to perform extra initializations
}

// Reads commands from the given input file, executes each command in a game tick
void GameController::play(const string &commands_file) {

    ifstream infile(commands_file);
    if (!infile.is_open()) {
        cerr << "Error: Could not open commands file: " << commands_file << endl;
        return;
    }

    Player* player = game->get_player();
    string command;

    while (getline(infile, command)) {
        bool valid_command = true;



        if (command == "PRINT_GRID") {

        } else if (command == "MOVE_UP") {
            player->move_up();
        } else if (command == "MOVE_DOWN") {
            player->move_down(game->space_grid.size());
        } else if (command == "MOVE_LEFT") {
            player->move_left();
        } else if (command == "MOVE_RIGHT") {
            player->move_right(game->space_grid[0].size());
        } else if (command == "SHOOT") {
            game->shoot();
        } else if (command == "NOP") {
            // Do nothing
        } else {
            cout << "Unknown command: " << command << endl;
            valid_command = false;
        }


        try {
            game->update_space_grid();
            if (player->lives <= 0) {
                game->game_over = true;
                throw GameOverException("Game Over");
            }
        } catch (const GameOverException& e) {
            cout << "GAME OVER!" << endl;
            game->game_time--;
            game->print_space_grid();
            break;
        }
        if (command == "PRINT_GRID") {
            game->print_space_grid();
        }

        if (valid_command) {
            game->increment_time();
        }
    }
    try {
        game->game_over = true;
        throw GameFinishedException("Game Finished");
    } catch (const GameFinishedException& e) {
        cout << "GAME FINISHED! No more commands!" << endl;
        game->game_time--;
        game->print_space_grid();
    }

    infile.close();
}

// Destructor to delete dynamically allocated member variables here
GameController::~GameController() {
    delete game;
    game = nullptr;
}


