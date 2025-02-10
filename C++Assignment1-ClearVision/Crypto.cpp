#include "Crypto.h"
#include "GrayscaleImage.h"


// Extract the least significant bits (LSBs) from SecretImage, calculating x, y based on message length
std::vector<int> Crypto::extract_LSBits(SecretImage& secret_image, int message_length) {

    GrayscaleImage modified_img = secret_image.reconstruct();

    int height = modified_img.get_height();
    int width = modified_img.get_width();
    int array_size = message_length * 7;

    if (array_size > height * width) {
        throw std::invalid_argument("LSB array size greater than image size");
    }

    std::vector<int> LSB_array(array_size);

    int index = array_size - 1;

    // Extract LSBs from the image pixels
    for (int i = height - 1; i >= 0; --i) {
        for (int j = width - 1; j >= 0; --j) {
            if (index < 0) {
                return LSB_array;
            }

            int pixel_value = modified_img.get_pixel(i, j);
            // Extract the least significant bit
            LSB_array[index] = pixel_value & 1;
            --index;
        }
    }
    return LSB_array;
}


// Decrypt message by converting LSB array into ASCII characters
std::string Crypto::decrypt_message(const std::vector<int>& LSB_array) {
    std::string message;

    if (LSB_array.size() % 7 != 0) {
        throw std::invalid_argument("LSB array size must be a multiple of 7");
    }

    // Converts bits to ascii character
    for (size_t i = 0; i < LSB_array.size(); i += 7) {
        std::bitset<7> bits;

        for (int j = 0; j < 7; ++j) {
            bits[6-j] = LSB_array[i + j];
        }
        char character = static_cast<char>(bits.to_ulong());

        message += character;
    }
    return message;
}

// Encrypt message by converting ASCII characters into LSBs
std::vector<int> Crypto::encrypt_message(const std::string& message) {

    std::vector<int> LSB_array;

    for (char c : message) {
        std::bitset<7> bits(c);

        for (int i = 6; i >= 0; --i) {
            LSB_array.push_back(bits[i]);
        }
    }
    return LSB_array;
}

// Embed LSB array into GrayscaleImage starting from the last bit of the image
SecretImage Crypto::embed_LSBits(GrayscaleImage& image, const std::vector<int>& LSB_array) {

    int height = image.get_height();
    int array_size = static_cast<int>(LSB_array.size());

    if (array_size > height * height) {
        throw std::invalid_argument("LSB array size greater than image size");
    }

    int index = array_size - 1;

    // Iterate over the image pixels, embedding LSBs from the array.
    for (int i = height - 1; i >= 0; --i) {
        for (int j = height - 1; j >= 0; --j) {

            if (index < 0) {
                return SecretImage(image);
            }

            int pixel_value = image.get_pixel(i, j);

            // Update LSB
            pixel_value = (pixel_value & ~1) | LSB_array[index];

            image.set_pixel(i, j, pixel_value);
            --index;
        }
    }
    return SecretImage(image);
}
