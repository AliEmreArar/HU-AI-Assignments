#include "GrayscaleImage.h"
#include "SecretImage.h"
#include "Filter.h"
#include "Crypto.h"
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

// Utility function to remove the file extension from a given filename
std::string remove_extension(const std::string& filename) {
    size_t last_dot = filename.find_last_of(".");
    return (last_dot != std::string::npos && last_dot > 0) ? filename.substr(0, last_dot) : filename;
}

// Applies a mean filter to the input image and saves the result
void apply_mean_filter(const char* input_image, int kernel_size) {
    GrayscaleImage img(input_image);
    Filter::apply_mean_filter(img, kernel_size);
    std::string output_filename = "mean_filtered_" + remove_extension(input_image) + "_" + std::to_string(kernel_size) + ".png";
    img.save_to_file(output_filename.c_str());
}

// Applies Gaussian smoothing to the input image and saves the result
void apply_gaussian_smoothing(const char* input_image, int kernel_size, double sigma) {
    GrayscaleImage img(input_image);
    Filter::apply_gaussian_smoothing(img, kernel_size, sigma);
    std::string output_filename = "gaussian_filtered_" + remove_extension(input_image) + "_" + std::to_string(kernel_size) + "_" + std::to_string(sigma) + ".png";
    img.save_to_file(output_filename.c_str());
}

// Applies an unsharp mask to the input image to enhance sharpness and saves the result
void apply_unsharp_mask(const char* input_image, int kernel_size, double amount) {
    GrayscaleImage img(input_image);
    Filter::apply_unsharp_mask(img, kernel_size, amount);
    std::string output_filename = "unsharp_filtered_" + remove_extension(input_image) + "_" + std::to_string(kernel_size) + "_" + std::to_string(amount) + ".png";
    img.save_to_file(output_filename.c_str());
}

// Adds two images together and saves the resulting image
void add_images(const char* img1, const char* img2) {
    GrayscaleImage image1(img1), image2(img2);
    GrayscaleImage result = image1 + image2;
    std::string output_filename = "added_" + remove_extension(img1) + "_" + remove_extension(img2) + ".png";
    result.save_to_file(output_filename.c_str());
}

// Subtracts the second image from the first and saves the resulting image
void subtract_images(const char* img1, const char* img2) {
    GrayscaleImage image1(img1), image2(img2);
    GrayscaleImage result = image1 - image2;
    std::string output_filename = "subtracted_" + remove_extension(img1) + "_" + remove_extension(img2) + ".png";
    result.save_to_file(output_filename.c_str());
}

// Compares two images and prints whether they are identical
void compare_images(const char* img1, const char* img2) {
    GrayscaleImage image1(img1), image2(img2);
    bool are_equal = (image1 == image2);
    std::cout << (are_equal ? "Images are equal." : "Images are not equal.") << std::endl;
}

// Converts a GrayscaleImage to a SecretImage and saves it in a disguised format
void disguise_image(const char* input_image) {
    GrayscaleImage img(input_image);
    SecretImage secret_img(img);
    std::string output_filename = "secret_image_" + remove_extension(input_image) + ".dat";
    secret_img.save_to_file(output_filename.c_str());
}

// Reconstructs a GrayscaleImage from a previously saved SecretImage file
void reveal_image(const char* input_file) {
    SecretImage secret_img = SecretImage::load_from_file(input_file);
    GrayscaleImage reconstructed = secret_img.reconstruct();
    std::string output_filename = "reconstructed_" + remove_extension(input_file) + ".png";
    reconstructed.save_to_file(output_filename.c_str());
}

// Encrypts a message into the image using the least significant bits (LSB) steganography
void encrypt_image(const char* input_image, const char* message) {
    GrayscaleImage img(input_image);
    SecretImage secret_img = Crypto::embed_LSBits(img, Crypto::encrypt_message(message));
    GrayscaleImage modified_img = secret_img.reconstruct();
    std::string output_filename = "modified_secret_image_" + remove_extension(input_image) + ".png";
    modified_img.save_to_file(output_filename.c_str());
}

// Extracts an encrypted message from the image and decrypts it
void decrypt_image(const char* input_image, int message_length) {
    SecretImage secret_img(input_image);
    std::string message = Crypto::decrypt_message(Crypto::extract_LSBits(secret_img, message_length));
    std::cout << "Decrypted Message: " << message << std::endl;
}

int main(int argc, char** argv) {
    // Check if enough arguments are provided
    if (argc < 2) {
        throw std::invalid_argument(
            "Usage: clearvision <operation> <arg1> <arg2> .. \n"
            "Modes of operation: \n\n"
            "clearvision mean <img> <kernel_size> \n"
            "clearvision gauss <img> <kernel_size> <sigma> \n"
            "clearvision unsharp <img> <kernel_size> <amount> \n"
            "clearvision add <img1> <img2> \n"
            "clearvision sub <img1> <img2> \n"
            "clearvision equals <img1> <img2> \n"
            "clearvision disguise <img> <msg> \n"
            "clearvision reveal <img> <msg> \n"
            "clearvision enc <img> <msg> \n"
            "clearvision dec <img> <msg_len>"
        );
    }

    std::string operation = argv[1];

    try {
        // Parse and execute the specified operation
        if (operation == "mean") {
            if (argc < 4) throw std::invalid_argument("Usage: clearvision mean <img> <kernel_size>");
            apply_mean_filter(argv[2], std::stoi(argv[3]));

        } else if (operation == "gauss") {
            if (argc < 5) throw std::invalid_argument("Usage: clearvision gauss <img> <kernel_size> <sigma>");
            apply_gaussian_smoothing(argv[2], std::stoi(argv[3]), std::stof(argv[4]));

        } else if (operation == "unsharp") {
            if (argc < 5) throw std::invalid_argument("Usage: clearvision unsharp <img> <kernel_size> <amount>");
            apply_unsharp_mask(argv[2], std::stoi(argv[3]), std::stof(argv[4]));

        } else if (operation == "add") {
            if (argc < 4) throw std::invalid_argument("Usage: clearvision add <img1> <img2>");
            add_images(argv[2], argv[3]);

        } else if (operation == "sub") {
            if (argc < 4) throw std::invalid_argument("Usage: clearvision sub <img1> <img2>");
            subtract_images(argv[2], argv[3]);

        } else if (operation == "equals") {
            if (argc < 4) throw std::invalid_argument("Usage: clearvision equals <img1> <img2>");
            compare_images(argv[2], argv[3]);

        } else if (operation == "disguise") {
            if (argc < 3) throw std::invalid_argument("Usage: clearvision disguise <img>");
            disguise_image(argv[2]);

        } else if (operation == "reveal") {
            if (argc < 3) throw std::invalid_argument("Usage: clearvision reveal <dat>");
            reveal_image(argv[2]);

        } else if (operation == "enc") {
            if (argc < 4) throw std::invalid_argument("Usage: clearvision enc <img> <message>");
            encrypt_image(argv[2], argv[3]);

        } else if (operation == "dec") {
            if (argc < 4) throw std::invalid_argument("Usage: clearvision dec <img> <msg_len>");
            decrypt_image(argv[2], std::stoi(argv[3]));

        } else {
            throw std::invalid_argument("Invalid operation.");
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
