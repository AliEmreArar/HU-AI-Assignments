#include "GrayscaleImage.h"
#include <iostream>
#include <cstring>  // For memcpy
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include <stdexcept>


// Constructor: load from a file
GrayscaleImage::GrayscaleImage(const char* filename) {
    // Image loading code using stbi
    int channels;
    unsigned char* image = stbi_load(filename, &width, &height, &channels, STBI_grey);

    if (image == nullptr) {
        std::cerr << "Error: Could not load image " << filename << std::endl;
        exit(1);
    }

    // Allocate memory for the 2D matrix dynamically
    data = new int*[height];  // Create an array of row pointers
    for (int i = 0; i < height; ++i) {
        data[i] = new int[width];  // Allocate memory for each row
    }

    // Fill the matrix with pixel values from the loaded image
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            data[i][j] = static_cast<int>(image[i * width + j]);  // Access pixel value and store it
        }
    }

    // Free the stbi image after copying data
    stbi_image_free(image);
}


// Constructor: initialize from a pre-existing data matrix
GrayscaleImage::GrayscaleImage(int** inputData, int h, int w) : width(w), height(h) {
    // Allocate memory for the 2D matrix
    data = new int*[height];
    for (int i = 0; i < height; ++i) {
        data[i] = new int[width];
    }

    // Copy values from inputData to data
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            data[i][j] = inputData[i][j];
        }
    }
}


// Constructor to create a blank image of given width and height
GrayscaleImage::GrayscaleImage(int w, int h) : width(w), height(h) {
    // Allocate memory for the 2D matrix
    data = new int*[height];
    for (int i = 0; i < height; ++i) {
        data[i] = new int[width];
        // Initialize each pixel to 0
        std::fill_n(data[i], width, 0);
    }
}

// Copy constructor
GrayscaleImage::GrayscaleImage(const GrayscaleImage& other) {
    // Assign width and height values from other
    width = other.width;
    height = other.height;

    // Allocate memory for the 2D matrix
    data = new int*[height];
    for (int i = 0; i < height; ++i) {
        data[i] = new int[width];
        // Copy pixel values from the other image
        std::copy(other.data[i], other.data[i] + width, data[i]);
    }
}

// Destructor
GrayscaleImage::~GrayscaleImage() {
    // Free the dynamically allocated memory
    if (data != nullptr) {
        for (int i = 0; i < height; ++i) {
            delete[] data[i];
        }
        delete[] data;
    }
}

// Assignment operator
GrayscaleImage& GrayscaleImage::operator=(const GrayscaleImage& other) {

    if (this == &other) {
        return *this;
    }

    for (int i = 0; i < height; ++i) {
        delete[] data[i];
    }
    delete[] data;

    width = other.width;
    height = other.height;

    data = new int*[height];
    for (int i = 0; i < height; ++i) {
        data[i] = new int[width];
        std::copy(other.data[i], other.data[i] + width, data[i]);
    }

    return *this;
}


// Equality operator
bool GrayscaleImage::operator==(const GrayscaleImage& other) const {
    // Check the size
    if (width != other.width || height != other.height) {
        return false;
    }

    // Check the pixel value
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (data[i][j] != other.data[i][j]) {
                return false;
            }
        }
    }
    return true;
}


// Addition operator
GrayscaleImage GrayscaleImage::operator+(const GrayscaleImage& other) const {

    GrayscaleImage result(width, height);

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            int pixel_sum = data[i][j] + other.data[i][j];
            result.data[i][j] = std::max(0, std::min(255, pixel_sum));  // Clamping
        }
    }
    return result;
}


// Subtraction operator
GrayscaleImage GrayscaleImage::operator-(const GrayscaleImage& other) const {

    GrayscaleImage result(width, height);

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            int pixel_sub = data[i][j] - other.data[i][j];

            // Clamp the result between 0 and 255
            result.data[i][j] = std::max(0, std::min(255, pixel_sub));
        }
    }
    return result;
}


// Get a specific pixel value
int GrayscaleImage::get_pixel(int row, int col) const {
    return data[row][col];
}

// Set a specific pixel value
void GrayscaleImage::set_pixel(int row, int col, int value) {
    data[row][col] = value;
}

// Function to save the image to a PNG file
void GrayscaleImage::save_to_file(const char* filename) const {
    // Create a buffer to hold the image data in the format stb_image_write expects
    unsigned char* imageBuffer = new unsigned char[width * height];

    // Fill the buffer with pixel data (convert int to unsigned char)
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            imageBuffer[i * width + j] = static_cast<unsigned char>(data[i][j]);
        }
    }

    // Write the buffer to a PNG file
    if (!stbi_write_png(filename, width, height, 1, imageBuffer, width)) {
        std::cerr << "Error: Could not save image to file " << filename << std::endl;
    }

    // Clean up the allocated buffer
    delete[] imageBuffer;
}
