#include "SecretImage.h"

// Constructor: split image into upper and lower triangular arrays
SecretImage::SecretImage(const GrayscaleImage& image) {

    height = image.get_height();
    width = image.get_width();

    // Dynamically allocate the memory for the upper and lower triangular matrices.
    upper_triangular = new int[height*(height+1)/2];
    lower_triangular = new int[(height-1)* height/2];

    // Fill both matrices with the pixels from the GrayscaleImage.
    int counter = 0;
    for (int i = 0; i < height; i++) {
        for (int j = i; j < height; j++) {
            // find algorithm, Actually we could use a counter for this placement
            upper_triangular[counter] = image.get_pixel(i,j);
            counter++;
        }
    }
    int counter2 = 0;
    for (int i = 1; i < height; i++) {
        for (int j = 0; j < i; j++) {
            // find algorithm, Actually we could use a counter for this placement
            lower_triangular[counter2] = image.get_pixel(i,j);
            counter2++;
        }
    }
}

// Constructor: instantiate based on data read from file
SecretImage::SecretImage(int w, int h, int * upper, int * lower) {

    height = h;
    width = w;

    // Instead of dynamically allocating, we just assign the pointers.
    upper_triangular = upper;
    lower_triangular = lower;
}


// Destructor: free the arrays
SecretImage::~SecretImage() {

    if (upper_triangular != nullptr) {
        delete[] upper_triangular;
        upper_triangular = nullptr;
    }
    if (lower_triangular != nullptr) {
        delete[] lower_triangular;
        lower_triangular = nullptr;
    }
}


// Reconstructs and returns the full image from upper and lower triangular matrices.
GrayscaleImage SecretImage::reconstruct() const {

    GrayscaleImage image(width, height);

    for (int i = 0; i < height; i++) {
        for (int j = i; j < height; j++) {
            // find algorithm
            image.set_pixel(i,j,upper_triangular[i*(2*height-i+1)/2+j-i]);
        }
    }
    for (int i = 1; i < height; i++) {
        for (int j = 0; j < i; j++) {
            // find algorithm
            image.set_pixel(i,j,lower_triangular[((i-1)*i/2)+j]);
        }
    }
    return image;
}

// Save the filtered image back to the triangular arrays
void SecretImage::save_back(const GrayscaleImage& image) {

    // Update the lower and upper triangular matrices
    for (int i = 0; i < height; i++) {
        for (int j = i; j < height; j++) {
            upper_triangular[i*(2*height-i+1)/2+j-i] = image.get_pixel(i, j);
        }
    }

    for (int i = 1; i < height; i++) {
        for (int j = 0; j < i; j++) {
            lower_triangular[(i - 1) * i / 2 + j] = image.get_pixel(i, j);
        }
    }
}

// Save the upper and lower triangular arrays to a file
void SecretImage::save_to_file(const std::string& filename) {

    std::ofstream file;
    file.open(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open the file!" << std::endl;
        return;
    }
    // Write width and height on the first line, separated by a single space.
    file << width << " " << height << std::endl;

    int upper_index = 0;
    // Write the upper_triangular array to the second line.
    for (int i = 0; i < height*(height+1)/2; i++) {
        if( i == (height*(height+1)/2)-1) {
            file << upper_triangular[upper_index];
        }
        else {
            file << upper_triangular[upper_index] << " ";
            upper_index++;
        }
    }
    file << std::endl;

    int lower_index = 0;
    // Write the lower_triangular array to the third line.
    for (int i = 0; i < (height-1)* height/2; i++) {
        if( i == ((height-1)*(height)/2)-1) {
            file << lower_triangular[lower_index];
        }
        else {
            file << lower_triangular[lower_index] << " ";
            lower_index++;
        }
    }
    file << std::endl;
    file.close();
}

// Static function to load a SecretImage from a file
SecretImage SecretImage::load_from_file(const std::string& filename) {
    

    std::ifstream file;
    file.open(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open the file!" << std::endl;
    }
    // Read width and height from the first line, separated by a space.
    int width, height;
    file >> width >> height;

    // Calculate the sizes of the upper and lower triangular arrays.
    int upper_size = height * (height + 1) / 2;
    int lower_size = (height - 1) * height / 2;

    // Allocate memory for both arrays.
    int* upper_triangular = new int[upper_size];
    int* lower_triangular = new int[lower_size];

    // Read the upper_triangular array from the second line
    for (int i = 0; i < upper_size; ++i) {
        file >> upper_triangular[i];
    }
    // Read the lower_triangular array from the third line
    for (int j = 0; j < lower_size; ++j) {
        file >> lower_triangular[j];
    }

    file.close();
    return {width, height, upper_triangular, lower_triangular};
}

// Returns a pointer to the upper triangular part of the secret image.
int * SecretImage::get_upper_triangular() const {
    return upper_triangular;
}

// Returns a pointer to the lower triangular part of the secret image.
int * SecretImage::get_lower_triangular() const {
    return lower_triangular;
}

// Returns the width of the secret image.
int SecretImage::get_width() const {
    return width;
}

// Returns the height of the secret image.
int SecretImage::get_height() const {
    return height;
}
