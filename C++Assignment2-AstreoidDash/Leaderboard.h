#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include <ctime>
#include <string>
#include "LeaderboardEntry.h"

#define MAX_LEADERBOARD_SIZE 10

using namespace std;

class Leaderboard {
public:

    // Pointer to the head of the linked list
    LeaderboardEntry *head_leaderboard_entry = nullptr;

    // Read the stored leaderboard status from the given file
    void read_from_file(const string &filename);

    // Write the latest leaderboard status to the given file
    void write_to_file(const string &filename);

    // Print the current leaderboard status to the standard output
    void print_leaderboard();

    //  Insert a new LeaderboardEntry instance into the leaderboard
    void insert(LeaderboardEntry *new_entry);

    // Free dynamically allocated memory used for storing leaderboard entries
    virtual ~Leaderboard();
};


#endif //LEADERBOARD_H
