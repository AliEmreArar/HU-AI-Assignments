#ifndef LEADERBOARDENTRY_H
#define LEADERBOARDENTRY_H

#include <ctime>
#include <string>

using namespace std;

// Basic node class for the leaderboard linked list
class LeaderboardEntry {

public:

    // Constructor
    LeaderboardEntry(unsigned long score, time_t lastPlayed, const string &playerName);

    // Score of the player
    unsigned long score;

    // Last played time
    time_t last_played;

    // Player name
    string player_name;

    // Next entry in the linked list
    LeaderboardEntry *next = nullptr;
};

#endif //LEADERBOARDENTRY_H
