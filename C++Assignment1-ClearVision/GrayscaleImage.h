#ifndef GRAYSCALE_IMAGE_H
#define GRAYSCALE_IMAGE_H

class GrayscaleImage {
private:
    int** data;
    int width{}, height{};


public:
    // Constructor: loads an image from a file
    GrayscaleImage(const char* filename);

    // Constructor: initializes from a 2D data matrix
    GrayscaleImage(int** inputData, int h, int w);

    // Constructor to create a blank image of given width and height
    GrayscaleImage(int w, int h);

    // Copy constructor
    GrayscaleImage(const GrayscaleImage& other);

    // Destructor
    ~GrayscaleImage();

    GrayscaleImage &operator=(const GrayscaleImage &other);

    // Operator overloads
    bool operator==(const GrayscaleImage& other) const;
    GrayscaleImage operator+(const GrayscaleImage& other) const;
    GrayscaleImage operator-(const GrayscaleImage& other) const;

    // Method to get image dimensions
    int get_width() const { return width; }
    int get_height() const { return height; }

    // Get a specific pixel value
    int get_pixel(int row, int col) const;

    // Set a specific pixel value
    void set_pixel(int row, int col, int value);

    // Function to write the image data back to a PNG file
    void save_to_file(const char* filename) const;

    // Getter function for data.
    int** get_data() const {
        return data;
    }
};

#endif // GRAYSCALE_IMAGE_H
