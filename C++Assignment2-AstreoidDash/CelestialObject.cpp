#include "CelestialObject.h"


// Constructor to initialize CelestialObject with essential properties
CelestialObject::CelestialObject(const vector<vector<bool>> &shape, ObjectType type, int start_row,
                                 int time_of_appearance)
        : shape(shape), object_type(type), starting_row(start_row), time_of_appearance(time_of_appearance) {
    // TODO: Your code here
}


// Copy constructor for CelestialObject
// Copy constructor for CelestialObject
CelestialObject::CelestialObject(const CelestialObject *other)
        : shape(other->shape),  // Copy the 2D vector shape
          object_type(other->object_type),  // Copy the object type
          starting_row(other->starting_row),  // Copy the starting row
          time_of_appearance(other->time_of_appearance) {  // Copy the time of appearance

    if (other->right_rotation != nullptr && other->right_rotation != other) {
        this->right_rotation = this;
        this->left_rotation = this;

        const CelestialObject *current = other->right_rotation;
        CelestialObject *previous_copy = this;

        while (current != other) {
            CelestialObject *new_copy = new CelestialObject(current);

            previous_copy->right_rotation = new_copy;
            new_copy->left_rotation = previous_copy;

            previous_copy = new_copy;
            current = current->right_rotation;
        }

        previous_copy->right_rotation = this;
        this->left_rotation = previous_copy;
    } else {

        this->right_rotation = this;
        this->left_rotation = this;
    }
}

// Function to delete rotations of a given celestial object. It should free the dynamically allocated
// memory for each rotation.
void CelestialObject::delete_rotations(CelestialObject* target) {

    if (!target) return;

    CelestialObject* current = target;
    CelestialObject* next = nullptr;

    do {
        next = current->right_rotation;
        current->right_rotation = nullptr;
        current->left_rotation = nullptr;

        if (current != target) {
            delete current;
        }

        current = next;

    } while (current && current != target);
}
