#include "AsteroidDash.h"
#include <fstream>
#include <algorithm>
// Constructor to initialize AsteroidDash with the given parameters
AsteroidDash::AsteroidDash(const string &space_grid_file_name,
                           const string &celestial_objects_file_name,
                           const string &leaderboard_file_name,
                           const string &player_file_name,
                           const string &player_name)

        : leaderboard_file_name(leaderboard_file_name), leaderboard(Leaderboard()) {

    read_player(player_file_name, player_name);  // Initialize player using the player.dat file
    read_space_grid(space_grid_file_name);  // Initialize the grid after the player is loaded
    read_celestial_objects(celestial_objects_file_name);  // Load celestial objects
    leaderboard.read_from_file(leaderboard_file_name);
}

// Function to read the space grid from a file                                                                                                             
void AsteroidDash::read_space_grid(const string &input_file) {
    ifstream file(input_file);
    if (!file.is_open()) {
        //cerr << "Error: Unable to open space grid file." << endl;
        return;
    }
    int cell;
    vector<int> row;

    while (file >> cell) {
        row.push_back(cell);

        if (file.peek() == '\n' || file.eof()) {
            space_grid.push_back(row);
            row.clear();
        }
    }
    file.close();
}

// Function to read the player from a file
void AsteroidDash::read_player(const string &player_file_name, const string &player_name) {
    ifstream file(player_file_name);
    if (!file.is_open()) {
        //cerr << "Error: Unable to open player file." << endl;
        return;
    }

    int start_row, start_col;
    file >> start_row >> start_col;

    vector<vector<bool>> player_shape;
    string line;

    while (getline(file, line)) {
        vector<bool> row;
        for (char c : line) {
            if (c == '1') row.push_back(true);
            else if (c == '0') row.push_back(false);
        }
        if (!row.empty()) player_shape.push_back(row);
    }

    int max_ammo = 10;
    int lives = 3;

    player = new Player(player_shape, start_row, start_col, player_name, max_ammo, lives);

    file.close();
}


// Function to read celestial objects from a file
void AsteroidDash::read_celestial_objects(const string &input_file) {
    ifstream file(input_file);
    if (!file.is_open()) {
        //cerr << "Error: Unable to open celestial objects file." << endl;
        return;
    }

    bool has_valid_objects = false;
    string line;

    while (getline(file, line)) {

        if (!line.empty() && (line[0] == '[' || line[0] == '{')) {
            has_valid_objects = true;
            break;
        }
    }

    if (!has_valid_objects) {
        //cerr << "Error: File contains no valid celestial objects." << endl;
        file.close();
        return;
    }

    file.clear();
    file.seekg(0, ios::beg);

    while (getline(file, line)) {
        vector<vector<bool>> object_shape;
        int start_row = 0;
        int time_of_appearance = 0;
        ObjectType type = ASTEROID;

        if (line[0] == '[' || line[0] == '{') {

            //for read the celestial object shape
            do {
                vector<bool> row;
                for (char c : line) {
                    if (c == '1') row.push_back(true);
                    else if (c == '0') row.push_back(false);
                }
                if (!row.empty()) object_shape.push_back(row);

                if (!getline(file, line)) break;
            } while (!line.empty() && line[0] != 's' && line[0] != 't' && line[0] != 'e');
        }

        if (object_shape.empty()) {
            //cerr << "Warning: Skipping celestial object with empty shape." << endl;
            continue;
        }

        while (!line.empty() && (line[0] == 's' || line[0] == 't' || line[0] == 'e')) {
            if (line[0] == 's') {
                start_row = stoi(line.substr(2));
            } else if (line[0] == 't') {
                time_of_appearance = stoi(line.substr(2));
            } else if (line[0] == 'e') {
                string effect = line.substr(2);
                if (effect == "life") type = LIFE_UP;
                else if (effect == "ammo") type = AMMO;
            }
            if (!getline(file, line)) break;
        }

        CelestialObject* obj = new CelestialObject(object_shape, type, start_row, time_of_appearance);

        //for coordinate
        celestial_object_positions[obj] = space_grid[0].size();

        vector<vector<bool>> right_shape = rotate_right(object_shape);
        vector<vector<bool>> right_shape2 = rotate_right(right_shape);

        if (are_shapes_equal(object_shape, right_shape)) {
            // Object is fully symmetrical, no additional rotations needed
            obj->right_rotation = obj;
            obj->left_rotation = obj;

        } else if(are_shapes_equal(object_shape, right_shape2)){
            // Object has a unique right rotation, no more rotation
            CelestialObject* right_obj = new CelestialObject(right_shape, type, start_row, time_of_appearance);
            obj->right_rotation = right_obj;
            obj->left_rotation = right_obj;
            right_obj->right_rotation = obj;
            right_obj->left_rotation = obj;


        }else {
            // Objects has 3 rotation
            vector<vector<bool>> right_shape3 = rotate_right(right_shape2);
            CelestialObject* right_obj = new CelestialObject(right_shape, type, start_row, time_of_appearance);
            CelestialObject* right_obj2 = new CelestialObject(right_shape2, type, start_row, time_of_appearance);
            CelestialObject* right_obj3 = new CelestialObject(right_shape3, type, start_row, time_of_appearance);
            obj->right_rotation = right_obj;
            right_obj->left_rotation = obj;
            right_obj->right_rotation = right_obj2;
            right_obj2->left_rotation = right_obj;
            right_obj2->right_rotation = right_obj3;
            right_obj3->left_rotation = right_obj2;
            right_obj3->right_rotation = obj;
            obj->left_rotation = right_obj3;

        }

        if (celestial_objects_list_head == nullptr) {
            celestial_objects_list_head = obj;
        } else {
            CelestialObject* current = celestial_objects_list_head;
            while (current->next_celestial_object != nullptr) {
                current = current->next_celestial_object;
            }
            current->next_celestial_object = obj;
        }
        obj->next_celestial_object = nullptr;

    }
    file.close();
    link_rotations_to_next(celestial_objects_list_head);
}


// Right rotation function
vector<vector<bool>> AsteroidDash::rotate_right(const vector<vector<bool>>& shape) {

    if (shape.empty() || shape[0].empty()) {
        //cerr << "Error: Empty or invalid shape passed to rotate_right." << endl;
        return {};
    }

    std::size_t rows = shape.size();
    std::size_t cols = shape[0].size();

    vector<vector<bool>> rotated(cols, vector<bool>(rows));

    for (std::size_t i = 0; i < rows; ++i) {
        for (std::size_t j = 0; j < cols; ++j) {
            rotated[j][rows - i - 1] = shape[i][j];
        }
    }
    return rotated;
}


// Comparison function to check if two shapes are identical
bool AsteroidDash::are_shapes_equal(const vector<vector<bool>>& shape1, const vector<vector<bool>>& shape2) {
    if (shape1.size() != shape2.size() || shape1[0].size() != shape2[0].size()) return false;
    for (size_t i = 0; i < shape1.size(); ++i) {
        for (size_t j = 0; j < shape1[0].size(); ++j) {
            if (shape1[i][j] != shape2[i][j]) return false;
        }
    }
    return true;
}

// Print the entire space grid
void AsteroidDash::print_space_grid() const {
    cout << "Tick: " << game_time<< endl;
    cout << "Lives: " << player->lives << endl;
    cout << "Ammo: " << player->current_ammo << endl;
    cout << "Score: " << current_score << endl;
    cout << "High Score: "<< current_score <<endl;

    for (const auto& row : space_grid) {
        for (int cell : row) {
            if (cell == 1) {
                cout << occupiedCellChar;
            } else {
                cout << unoccupiedCellChar;
            }
        }
        cout << endl;
    }
    cout << endl;
}


// Function to update the space grid with player, celestial objects, and any other changes
// It is called in every game tick before moving on to the next tick.
void AsteroidDash::update_space_grid() {
    if (player->spacecraft_shape.empty() || space_grid.empty()) {
        return;
    }
    //copy space_grid
    grid = space_grid;

    //clear
    for (auto &row : space_grid) {
        std::fill(row.begin(), row.end(), 0);
    }

    if (player->spacecraft_shape.empty() || space_grid.empty()) {
        return;
    }

    CelestialObject* current = celestial_objects_list_head;

    while (current) {
        if (current->time_of_appearance > game_time) {
            //any objects shown
            break;
        }

        int right_side = game_time - current->time_of_appearance + 1;
        int current_col = space_grid[0].size() - (game_time - current->time_of_appearance + 1);
        int celestial_seen_width = std::min(right_side, static_cast<int>(current->shape[0].size()));

        if (current_col + current->shape[0].size() <= 0) {
            // Object out of bounds
            current = current->next_celestial_object;
            continue;
        }

        // update objects column
        celestial_object_positions[current] = current_col;

        for (size_t i = 0; i < current->shape.size(); ++i) {
            for (size_t j = 0; j < celestial_seen_width; ++j) {
                if (current->shape[i][j]) {
                    int row = current->starting_row + i;
                    int col = current_col + j;

                    if (row >= 0 && row < space_grid.size() && col >= 0 && col < space_grid[0].size()) {
                        space_grid[row][col] = 1;
                    }
                }
            }
        }
        current = current->next_celestial_object;
    }



    for (auto it = projectiles.begin(); it != projectiles.end();) {
        int row = it->first;
        int col = it->second;

        if (col + 1 < space_grid[0].size()) {
            if (grid[row][col+1] == 1) {
                projectiles_collissed(row, col+1);
                it = projectiles.erase(it); // Remove projectile after collision
            } else {
                space_grid[row][col + 1] = 1;
                ++it->second;
                ++it;
            }
        } else {
            it = projectiles.erase(it); // Remove projectile if out of bounds
        }
    }



    for (size_t i = 0; i < player->spacecraft_shape.size(); ++i) {
        for (size_t j = 0; j < player->spacecraft_shape[i].size(); ++j) {
            if (player->spacecraft_shape[i][j]) {
                int row = player->position_row + i;
                int col = player->position_col + j;

                if (col  < space_grid[0].size() && grid[row][col] != 0) {
                    player_collissed(row, col);
                }
                space_grid[row][col] = 1;
            }
        }
    }

    if (game_over) {
        delete_craft();
        throw GameOverException("Game Over");
    }
}


void AsteroidDash::player_collissed(int row, int col) {
    CelestialObject* colliding_object = find_celestial_at(row, col);

    if (!colliding_object) return;

    if (colliding_object->object_type == LIFE_UP) {
        player->lives++; // Increase player lives
    } else if (colliding_object->object_type == AMMO) {
        player->current_ammo = 10; // Refill ammo
    } else {
        player->lives--; // Reduce player lives
    }

    // Remove the celestial object and its rotations
    remove_celestial_object(colliding_object);
}



void AsteroidDash::projectiles_collissed(int row, int col) {

    CelestialObject* colliding_object = find_celestial_at(row, col);

    if (!colliding_object || colliding_object->object_type == AMMO || colliding_object->object_type == LIFE_UP) {
        return;
    }

    int object_row = row - colliding_object->starting_row;
    int object_col = col - celestial_object_positions[colliding_object];
    colliding_object->shape[object_row][object_col] = false;

    // if all cell boom then remove this object
    bool active = false;
    for (const auto& row : colliding_object->shape) {
        if (std::any_of(row.begin(), row.end(), [](bool cell) { return cell; })) {
            active = true;
            break;
        }
    }

    if (!active) {
        remove_celestial_object(colliding_object);

    }else {
        CelestialObject::delete_rotations(colliding_object);

        vector<vector<bool>> current_shape = colliding_object->shape;
        vector<vector<bool>> right_shape = rotate_right(current_shape);
        vector<vector<bool>> right_shape2 = rotate_right(right_shape);
        vector<vector<bool>> right_shape3 = rotate_right(right_shape2);

        if (are_shapes_equal(current_shape, right_shape)) {

            colliding_object->right_rotation = colliding_object;
            colliding_object->left_rotation = colliding_object;

        } else if (are_shapes_equal(current_shape, right_shape2)) {

            CelestialObject* right_obj = new CelestialObject(right_shape, colliding_object->object_type, colliding_object->starting_row, colliding_object->time_of_appearance);
            colliding_object->right_rotation = right_obj;
            colliding_object->left_rotation = right_obj;
            right_obj->right_rotation = colliding_object;
            right_obj->left_rotation = colliding_object;
            right_obj->next_celestial_object = colliding_object->next_celestial_object;

        } else {

            CelestialObject* right_obj = new CelestialObject(right_shape, colliding_object->object_type, colliding_object->starting_row, colliding_object->time_of_appearance);
            CelestialObject* right_obj2 = new CelestialObject(right_shape2, colliding_object->object_type, colliding_object->starting_row, colliding_object->time_of_appearance);
            CelestialObject* right_obj3 = new CelestialObject(right_shape3, colliding_object->object_type, colliding_object->starting_row, colliding_object->time_of_appearance);

            colliding_object->right_rotation = right_obj;
            right_obj->left_rotation = colliding_object;
            right_obj->right_rotation = right_obj2;
            right_obj2->left_rotation = right_obj;
            right_obj2->right_rotation = right_obj3;
            right_obj3->left_rotation = right_obj2;
            right_obj3->right_rotation = colliding_object;
            colliding_object->left_rotation = right_obj3;
            right_obj->next_celestial_object = colliding_object->next_celestial_object;
            right_obj2->next_celestial_object = colliding_object->next_celestial_object;
            right_obj3->next_celestial_object = colliding_object->next_celestial_object;
        }
    }
}


CelestialObject* AsteroidDash::find_celestial_at(int row, int col) {
    CelestialObject* current = celestial_objects_list_head;

    while (current) {
        int current_col = celestial_object_positions[current];
        int start_row = current->starting_row;

        for (size_t i = 0; i < current->shape.size(); ++i) {
            for (size_t j = 0; j < current->shape[i].size(); ++j) {
                if (current->shape[i][j]) {
                    if (row == start_row + i && col == current_col + j) {
                        return current;
                    }
                }
            }
        }
        current = current->next_celestial_object;
    }

    return nullptr; // No celestial object found
}

// Remove Celestial Object and Its Rotations
void AsteroidDash::remove_celestial_object(CelestialObject* target) {
    if (!target) return;

    // Remove target from linked list
    if (celestial_objects_list_head == target) {
        celestial_objects_list_head = target->next_celestial_object;
    } else {
        CelestialObject* current = celestial_objects_list_head;
        while (current && current->next_celestial_object != target) {
            current = current->next_celestial_object;
        }
        if (current) {
            current->next_celestial_object = target->next_celestial_object;
        }
    }

    // Delete rotations and target itself
    CelestialObject::delete_rotations(target);
    target->next_celestial_object = nullptr;
    delete target;
}


// Corresponds to the SHOOT command.
// It should shoot if the player has enough ammo.
// It should decrease the player's ammo
void AsteroidDash::shoot() {
    if (player->current_ammo > 0) {
        player->current_ammo--;

        if(player->spacecraft_shape.empty()) {
            return;
        }

        std::size_t player_height = player->spacecraft_shape.size();
        std::size_t player_width = player->spacecraft_shape[0].size();
        int projectile_row = player->position_row + player_height / 2;
        int projectile_col = player->position_col + player_width;

        if (projectile_row < space_grid.size() && projectile_col < space_grid[0].size()) {
            projectiles.emplace_back(projectile_row, projectile_col);
        }
    }
}

Player* AsteroidDash::get_player() const {
    return player;
}

// Destructor. Remove dynamically allocated member variables here.
AsteroidDash::~AsteroidDash() {
    delete player;

    CelestialObject* current = celestial_objects_list_head;

    while (current != nullptr) {

        CelestialObject* next = current->next_celestial_object;

        // Delete the rotations of the current celestial object
        CelestialObject::delete_rotations(current);

        delete current;

        current = next;
    }

    celestial_objects_list_head = nullptr;
}

void AsteroidDash::increment_time() {
    ++game_time;
}

void AsteroidDash::link_rotations_to_next(CelestialObject* head) {
    if (!head) return;

    CelestialObject* current = head;

    while (current) {
        CelestialObject* next_object = current->next_celestial_object;

        if (!next_object) {
            current = current->next_celestial_object;
            continue;
        }

        CelestialObject* rotation = current->right_rotation;

        while (rotation && rotation != current) {
            if (!rotation->right_rotation) {
                //cerr << "Error: Missing right_rotation in rotation chain." << endl;
                break;
            }

            rotation->next_celestial_object = next_object;
            rotation = rotation->right_rotation;
        }

        current = current->next_celestial_object;
    }
}

void AsteroidDash::delete_craft() {
    if (!player || player->spacecraft_shape.empty() || space_grid.empty()) {
        return;
    }

    int start_row = player->position_row;
    int start_col = player->position_col;

    for (size_t i = 0; i < player->spacecraft_shape.size(); ++i) {
        for (size_t j = 0; j < player->spacecraft_shape[i].size(); ++j) {
            if (player->spacecraft_shape[i][j]) {
                int row = start_row + i;
                int col = start_col + j;

                if (row >= 0 && row < space_grid.size() && col >= 0 && col < space_grid[0].size()) {
                    space_grid[row][col] = 0;
                }
            }
        }
    }
}
