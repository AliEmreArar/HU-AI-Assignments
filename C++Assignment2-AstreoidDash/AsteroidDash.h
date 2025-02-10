#ifndef ASTEROIDDASH_H
#define ASTEROIDDASH_H

#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>

#include "CelestialObject.h"
#include "LeaderboardEntry.h"
#include "Leaderboard.h"
#include "Player.h"
#include <exception>

#define occupiedCellChar "██"
#define unoccupiedCellChar "▒▒"

using namespace std;

// Class that encapsulates the game play internals
class AsteroidDash {
public:

    // Constructor to initialize the game
    AsteroidDash(const string &space_grid_file_name, const string &celestial_objects_file_name,
                 const string &leaderboard_file_name, const string &player_file_name, const string &player_name);

    // Destructor. Remove dynamically allocated member variables here
    virtual ~AsteroidDash();

    void increment_time();

    unordered_map<CelestialObject*, int> celestial_object_positions;

    vector<pair<int, int>> projectiles;
    // 2D space_grid
    vector<vector<int> > space_grid;
    vector<vector<int> > grid;

    // Pointer to track the player instance
    Player *player = nullptr;

    // A reference to the head of the celestial objects linked list
    CelestialObject *celestial_objects_list_head = nullptr;

    // Current score of the game
    unsigned long current_score = 0;

    // Current game tick
    unsigned long game_time = 0;

    // Leaderboard file name to store and read the leaderboard from
    string leaderboard_file_name;

    // Leaderboard member variable
    Leaderboard leaderboard;

    // True if the game is over
    bool game_over = false;

    // Function to print the space_grid
    void print_space_grid() const;

    // Function to read the space grid from a file
    void read_space_grid(const string &input_file);

    // Function to read the player from a file
    void read_player(const string &player_file_name, const string &player_name);

    // Function to read celestial objects from a file
    // Reads the input file and calls the read_celestial_object() function for each celestial_object;
    void read_celestial_objects(const string &input_file);

    // Updates the grid based on player and celestial object states
    void update_space_grid();

    // Corresponds to the SHOOT command.
    void shoot();

    static vector<vector<bool>> rotate_right(const vector<vector<bool>> &shape);

    static bool are_shapes_equal(const vector<vector<bool>> &shape1, const vector<vector<bool>> &shape2);

    Player* get_player() const;


    void projectiles_collissed(int row, int col);

    void remove_celestial_object(CelestialObject *target);

    CelestialObject *find_celestial_at(int row, int col);

    void player_collissed(int row, int col);
    static void link_rotations_to_next(CelestialObject* head);

    void delete_craft();
};

class GameOverException : public std::exception {
private:
    std::string message;

public:

    explicit GameOverException(const std::string& msg) : message(msg) {}

    ~GameOverException() noexcept override = default;

    const char* what() const noexcept override {
        return message.c_str();
    }
};

class GameFinishedException : public std::exception {
private:
    std::string message;

public:

    explicit GameFinishedException(const std::string& msg) : message(msg) {}

    ~GameFinishedException() noexcept override = default;

    const char* what() const noexcept override {
        return message.c_str();
    }
};

#endif // ASTEROIDDASH_H
