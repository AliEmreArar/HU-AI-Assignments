#include "Filter.h"
#include <algorithm>
#include <cmath>
#include <vector>
#include <numeric>
#include <math.h>

// Mean Filter
void Filter::apply_mean_filter(GrayscaleImage& image, int kernelSize) {

    GrayscaleImage original_image = image;

    int core = kernelSize/2 ;

    //For each pixel, calculate the mean value of its neighbors using a kernel.
    for (int i = 0; i < image.get_height(); i++) {
        for (int j = 0; j < image.get_width(); j++) {

            int sum = 0;

            for (int ki = -core; ki <= core; ki++) {
                for (int kj = -core; kj <= core; kj++) {

                    int ni = i + ki;
                    int nj = j + kj;

                    if (ni >= 0 && nj >= 0 && ni < image.get_height() && nj < image.get_width()) {
                        sum += original_image.get_pixel(ni, nj);
                    }
                }
            }
            //Update each pixel with the computed mean.
            image.set_pixel(i, j, floor(sum / (kernelSize * kernelSize)));
        }
    }
}

// Gaussian Smoothing Filter
void Filter::apply_gaussian_smoothing(GrayscaleImage& image, int kernelSize, double sigma) {

    GrayscaleImage original_image = image;

    int core = kernelSize / 2;
    double sigma2 = 2 * sigma * sigma;
    double sigma_pi = 1.0 / (M_PI * sigma2);

    // Precompute Gaussian kernel for the given sigma and kernel size
    std::vector<std::vector<double>> gaussian_kernel(kernelSize, std::vector<double>(kernelSize));

    double kernel_sum = 0.0;

    // Create a Gaussian kernel based on the given sigma value.
    for (int ki = -core; ki <= core; ++ki) {
        for (int kj = -core; kj <= core; ++kj) {
            gaussian_kernel[ki + core][kj + core] = sigma_pi * std::exp(-(ki * ki + kj * kj) / sigma2);
            // For each pixel, compute the weighted sum using the kernel.
            kernel_sum += gaussian_kernel[ki + core][kj + core];
        }
    }

    // Apply the Gaussian filter
    for (int i = 0; i < image.get_height(); i++) {
        for (int j = 0; j < image.get_width(); j++) {

            double sum_all = 0.0;

            for (int ki = -core; ki <= core; ki++) {
                for (int kj = -core; kj <= core; kj++) {

                    int ni = i + ki;
                    int nj = j + kj;

                    // Check if the pixel is within image bounds
                    if (ni >= 0 && nj >= 0 && ni < image.get_height() && nj < image.get_width()) {
                        sum_all += original_image.get_pixel(ni, nj) * gaussian_kernel[ki + core][kj + core];
                    }
                }
            }
            // Normalize the kernel to ensure it sums to 1 and update the pixel values with the smoothed results.
            image.set_pixel(i, j, floor(sum_all/kernel_sum));
        }
    }
}

// Unsharp Masking Filter
void Filter::apply_unsharp_mask(GrayscaleImage& image, int kernelSize, double amount) {

    GrayscaleImage original_image = image;
    // Blur the image using Gaussian smoothing, use the default sigma given in the header.
    apply_gaussian_smoothing(image, kernelSize, 1);

    for (int i = 0; i < image.get_height(); i++) {
        for (int j = 0; j < image.get_width(); j++) {

            // For each pixel, apply the unsharp mask formula: original + amount * (original - blurred).
            int scaled_edge = static_cast<int>(original_image.get_pixel(i,j) + ((original_image.get_pixel(i, j)- image.get_pixel(i,j)) * amount));
            // Clip values to ensure they are within a valid range [0-255].
            image.set_pixel(i, j, std::max(0, std::min(255, scaled_edge)));
        }
    }
}
