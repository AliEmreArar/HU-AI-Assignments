#include "Leaderboard.h"
#include <fstream>
#include <sstream>
#include <ctime>
#include <iomanip>
#include <iostream>

// Read the stored leaderboard status from the given file such that the "head_leaderboard_entry" member
// variable will point to the highest all-times score, and all other scores will be reachable from it
// via the "next_leaderboard_entry" member variable pointer.

void Leaderboard::read_from_file(const std::string &filename) {
    std::ifstream infile(filename);
    if (!infile.is_open()) {
        head_leaderboard_entry = nullptr;
        return;
    }

    unsigned long score;
    time_t timestamp;
    std::string player_name;
    head_leaderboard_entry = nullptr;

    while (infile >> score >> timestamp >> player_name) {
        LeaderboardEntry* new_entry = new LeaderboardEntry(score, timestamp, player_name);
        insert(new_entry);
    }
}


// Write the latest leaderboard status to the given file in the format specified in the PA instructions
void Leaderboard::write_to_file(const std::string &filename) {
    std::ofstream outfile(filename);
    if (!outfile.is_open()) {
        return;
    }

    LeaderboardEntry* current = head_leaderboard_entry;
    while (current != nullptr) {
        outfile << current->score << " " << current->last_played << " " << current->player_name << "\n";
        current = current->next;
    }
}


// Print the current leaderboard status to the standard output in the format specified in the PA instructions
void Leaderboard::print_leaderboard() {
    std::cout << "Leaderboard\n-----------\n";

    LeaderboardEntry* current = head_leaderboard_entry;
    int rank = 1;
    while (current != nullptr) {
        std::tm* time_info = std::localtime(&current->last_played);
        char formatted_time[20];
        std::strftime(formatted_time, sizeof(formatted_time), "%H:%M:%S/%d.%m.%Y", time_info);

        std::cout << rank << ". " << current->player_name << " " << current->score << " " << formatted_time << "\n";
        current = current->next;
        rank++;
    }
}


//  Insert a new LeaderboardEntry instance into the leaderboard, such that the order of the high-scores
//  is maintained, and the leaderboard size does not exceed 10 entries at any given time (only the
//  top 10 all-time high-scores should be kept in descending order by the score).
void Leaderboard::insert(LeaderboardEntry *new_entry) {
    if (head_leaderboard_entry == nullptr || new_entry->score > head_leaderboard_entry->score) {
        new_entry->next = head_leaderboard_entry;
        head_leaderboard_entry = new_entry;
    } else {
        LeaderboardEntry* current = head_leaderboard_entry;
        while (current->next != nullptr && current->next->score >= new_entry->score) {
            current = current->next;
        }
        new_entry->next = current->next;
        current->next = new_entry;
    }


    int count = 1;
    LeaderboardEntry* temp = head_leaderboard_entry;
    while (temp->next != nullptr) {
        if (count == 10) {
            delete temp->next;
            temp->next = nullptr;
            break;
        }
        temp = temp->next;
        count++;
    }
}


// Free dynamically allocated memory used for storing leaderboard entries
Leaderboard::~Leaderboard() {
    LeaderboardEntry* current = head_leaderboard_entry;
    while (current != nullptr) {
        LeaderboardEntry* temp = current;
        current = current->next;
        delete temp;
    }
}

