#ifndef CRYPTO_H
#define CRYPTO_H

#include "SecretImage.h"
#include <string>
#include <vector>
#include <bitset>
#include <stdexcept>
#include <iostream>
#include <algorithm>

class Crypto {
public:
    // Function to extract LSBs from SecretImage
    static std::vector<int> extract_LSBits(SecretImage& secret_image, int message_length);

    // Function to decrypt message from LSB array
    static std::string decrypt_message(const std::vector<int>& LSB_array);

    // Function to convert a string message into LSB array (encryption)
    static std::vector<int> encrypt_message(const std::string& message);

    // Function to embed LSB array into SecretImage
    static SecretImage embed_LSBits(GrayscaleImage& image, const std::vector<int>& LSB_array);
};

#endif // CRYPTO_H
