#ifndef SECRET_IMAGE_H
#define SECRET_IMAGE_H

#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <limits>

#include "GrayscaleImage.h"

class SecretImage {
    
private:
    int *upper_triangular; // Array for upper triangular part (including diagonal)
    int *lower_triangular; // Array for lower triangular part (excluding diagonal)
    int width{}, height{};

public:
    // Constructor: takes a GrayscaleImage and splits it into two triangular arrays
    SecretImage(const GrayscaleImage &image);

    // Constructor: instantiate based on data read from file
    SecretImage(int w, int h, int *upper, int *lower);

    // Destructor
    ~SecretImage();

    // Function to reconstruct the image from two arrays
    GrayscaleImage reconstruct() const;

    // Save back to triangular arrays after filtering
    void save_back(const GrayscaleImage &image);

    // Saves a secret image into the given file
    void save_to_file(const std::string &filename);

    // Reads a secret image from the given file
    static SecretImage load_from_file(const std::string &filename);

    // Getters and setters for private instance variables
    int *get_upper_triangular() const;
    int *get_lower_triangular() const;
    int get_width() const;
    int get_height() const;
};

#endif // SECRET_IMAGE_H
