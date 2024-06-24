/**
* @file Filter.cpp
* Group Name: Fibonacci
* Name: Yibin Gao           Github_name: edsml-kg23
* Name: Ruihan He           Github_name: edsml-rh323
* Name: Yu Yin              Github_name: acse-yy923
* Name: Sara Lakatos        Github_name: acse-sl4623
* Name: Manawi Kahie        Github_name: acse-mk1923
* Name: Wenyi Yang          Github_name: acse-wy1023
* 
*/

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <tuple>
#include <ctime>

#include "utils.h"
#include "Filter.h"
#include "Image.h"
#include <chrono>

// Colour correction and simple per-pixel modifiers:
void Filter::grayscale(Image &image) {
    std::cout << "\nApplying grayscale filter" << std::endl;
    int size = image.w * image.h;
    for (int i = 0; i < size; i++) {
        int r = image.data[i * image.c];
        int g = image.data[i * image.c + 1];
        int b = image.data[i * image.c + 2];
        int gray = static_cast<int>(0.2126f * r + 0.7152f * g + 0.0722f * b);
        image.data[i] = gray;
    }
    image.c = 1;
}

void Filter::brightness(Image &image, int brightness = 0, bool autoBrightness = false) {
    std::cout << "\nApplying brightness filter" << std::endl;
    int size = image.w * image.h * image.c;
    if (autoBrightness) {
        long long sum = 0;
        for (int i = 0; i < size; i++) {
            sum += image.data[i];
        }
        int avg = sum / size;
        brightness = 128 - avg;
    }
    for (int i = 0; i < size; i++) {
        int value = image.data[i] + brightness;
        if (value < 0) value = 0;
        if (value > 255) value = 255;
        image.data[i] = value;
    }
}

void Filter::histogramEqualization(Image &image, bool hsv) {
    std::cout << "\nApplying histogram equalization" << std::endl;
    const int size = image.w * image.h;
    std::vector<int> histogram(256, 0), cdf(256, 0);

    // For grayscale or single channel processing
    if (image.c == 1) {
        for (int i = 0; i < size; i++) {
            histogram[image.data[i]]++;
        }
        Image::calculateCdf(histogram, cdf);
        for (int i = 0; i < size; i++) {
            image.data[i] = static_cast<unsigned char>(cdf[image.data[i]]);
        }
    } else {
        // For color images, process each pixel
        for (int i = 0; i < size; i++) {
            float r = image.data[i * image.c] / 255.0f, g = image.data[i * image.c + 1] / 255.0f, b =
                    image.data[i * image.c + 2] / 255.0f;
            float h, s, l; // Use 'l' for consistency in naming for HSL
            if (hsv) {
                Image::rgbToHsv(r, g, b, h, s, l); // 'v' changed to 'l' for clarity
                histogram[static_cast<int>(l * 255)]++;
            } else {
                Image::rgbToHsl(r, g, b, h, s, l);
                histogram[static_cast<int>(l * 255)]++;
            }
        }
        Image::calculateCdf(histogram, cdf);
        for (int i = 0; i < size; i++) {
            float r = image.data[i * image.c] / 255.0f, g = image.data[i * image.c + 1] / 255.0f, b =
                    image.data[i * image.c + 2] / 255.0f;
            float h, s, l; // Again, 'l' for consistency
            int rInt, gInt, bInt;
            if (hsv) {
                Image::rgbToHsv(r, g, b, h, s, l);
                l = cdf[static_cast<int>(l * 255)] / 255.0f;
                Image::hsvToRgb(h, s, l, rInt, gInt, bInt); // Convert back using modified 'l'
            } else {
                Image::rgbToHsl(r, g, b, h, s, l);
                l = cdf[static_cast<int>(l * 255)] / 255.0f;
                Image::hslToRgb(h, s, l, rInt, gInt, bInt); // Convert back using modified 'l'
            }
            image.data[i * image.c] = static_cast<unsigned char>(rInt);
            image.data[i * image.c + 1] = static_cast<unsigned char>(gInt);
            image.data[i * image.c + 2] = static_cast<unsigned char>(bInt);
        }
    }
}


void Filter::threshold(Image &image, int threshold, bool useHsv = false) {
    if (image.c == 1) { // Grayscale image
        int size = image.w * image.h;
        for (int i = 0; i < size; i++) {
            image.data[i] = image.data[i] < threshold ? 0 : 255;
        }
    } else { // RGB image
        int size = image.w * image.h;
        for (int i = 0; i < size; i++) {
            float r = image.data[i * image.c] / 255.0f, g = image.data[i * image.c + 1] / 255.0f, b =
                    image.data[i * image.c + 2] / 255.0f;
            float h, s, v;
            if (useHsv) {
                Image::rgbToHsv(r, g, b, h, s, v); // Convert RGB to HSV
            } else {
                Image::rgbToHsl(r, g, b, h, s, v); // Convert RGB to HSL
            }
            int newValue = v * 255 < threshold ? 0 : 255;
            for (int j = 0; j < image.c; j++) {
                image.data[i * image.c + j] = static_cast<unsigned char>(newValue);
            }
        }
    }
}


void Filter::addSaltPepperNoise(Image &image, float noisePercentage) {
    srand(static_cast<unsigned>(time(nullptr))); // Seed the random number generator
    int size = image.w * image.h;
    int noisePixels = static_cast<int>(size * noisePercentage / 100.0f); // Calculate number of pixels to noise

    for (int i = 0; i < noisePixels; i++) {
        int idx = rand() % size; // Random pixel index
        int noiseValue = (rand() % 2) * 255; // Randomly choose between 0 (black) and 255 (white)

        if (image.c == 1) { // Grayscale image
            image.data[idx] = noiseValue;
        } else { // RGB image
            image.data[idx * image.c] = noiseValue;     // R channel
            image.data[idx * image.c + 1] = noiseValue; // G channel
            image.data[idx * image.c + 2] = noiseValue; // B channel
        }
    }
}

// Blur filters:
void Filter::applyMedianFilter2D(Image &image, int kernel_size) {
    std::cout << "\nApplying image median blur filter" << std::endl;

    // Create a copy of the data of the original image
    std::vector<unsigned char> image_copy(image.data, image.data + image.w * image.h * image.c);

    // Compute the offsets for finding the neighborhood indices
    int offset = kernel_size / 2;

    // Precompute offsets to determine the neighborhood of any given pixel
    std::vector<std::tuple<int, int>> offsets;
    for (int ky = -offset; ky <= offset; ++ky) {
        for (int kx = -offset; kx <= offset; ++kx) {
            offsets.emplace_back(kx, ky);
        }
    }


    // initialise neighborhood with 0 values
    std::vector<unsigned char> neighborhood(kernel_size * kernel_size, 0);

    // Loop through each of the pixels excluding the boundary pixels
    for (int y = 0; y < image.h; ++y) {
        for (int x = 0; x < image.w; ++x) {

            // Reset neighborhood to zero values
            std::fill(neighborhood.begin(), neighborhood.end(), 0);

            for (int ch = 0; ch < image.c; ++ch) {
                // Loop through the precomputed offsets
                for (const auto &[kx, ky]: offsets) {

                    // Calculate coordinates of surrounding pixels
                    int nx = x + kx;
                    int ny = y + ky;

                    // Adjust for out of boundary neighbors to take the nearest pixel value within bounds
                    if (nx < 0)
                        nx = 0;
                    else if (nx >= image.w)
                        nx = image.w - 1;
                    if (ny < 0)
                        ny = 0;
                    else if (ny >= image.h)
                        ny = image.h - 1;

                    int pixel_index = ny * image.w * image.c + nx * image.c;
                    // std::cout << "(" << kx << ", " << ky << ") = "<< "(" << nx << ", " << ny << ") = "<<(int)image_copy[pixel_index + ch]<<std::endl;

                    // Store the pixel value corresponding to the adjusted neighborhood index in neighbors
                    neighborhood[kx + offset + (ky + offset) * kernel_size] = image_copy[pixel_index + ch];

                } // end neighborhood loop

                // Compute the median using quickSelect
                unsigned char median_value;
                int middle_index = kernel_size * kernel_size / 2;
                median_value = quickSelect(neighborhood, 0, kernel_size * kernel_size - 1, middle_index);

                // Assign the median value to each channel in the current pixel
                image.data[y * image.w * image.c + x * image.c + ch] = median_value;
            }

        }

    }

}

void Filter::applyBoxFilter2D(Image &image, int kernel_size) {
    std::cout << "\nApplying image box blur filter" << std::endl;

    // Create a copy of the data of the original image
    std::vector<unsigned char> image_copy(image.data, image.data + image.w * image.h * image.c);

    // Compute the offsets for finding the neighborhood indices
    int offset = kernel_size / 2;

    // Precompute offsets to determine the neighborhood of any given pixel
    std::vector<std::tuple<int, int>> offsets;
    for (int ky = -offset; ky <= offset; ++ky) {
        for (int kx = -offset; kx <= offset; ++kx) {
            offsets.emplace_back(kx, ky);
        }
    }

    // initialise neighborhood with 0 values
    std::vector<unsigned char> neighborhood(kernel_size * kernel_size, 0);

    // Loop through each of the pixels
    for (int y = 0; y < image.h; ++y) {
        for (int x = 0; x < image.w; ++x) {

            // Reset sum for each channel
            std::vector<double> sum(image.c, 0.0);

            // Loop through the precomputed offsets
            for (const auto &[kx, ky]: offsets) {

                // Calculate coordinates of surrounding pixels
                int nx = x + kx;
                int ny = y + ky;

                // Adjust for out of boundary neighbors to take the nearest pixel value within bounds
                if (nx < 0)
                    nx = 0;
                else if (nx >= image.w)
                    nx = image.w - 1;
                if (ny < 0)
                    ny = 0;
                else if (ny >= image.h)
                    ny = image.h - 1;

                int pixel_index = ny * image.w * image.c + nx * image.c;
                // std::cout << "(" << kx << ", " << ky << ") = "<< "(" << nx << ", " << ny << ") = "<<(int)image_copy[pixel_index + ch]<<std::endl;

                // Accumulate sum for each channel
                for (int ch = 0; ch < image.c; ++ch) {
                    sum[ch] += image_copy[pixel_index + ch];
                }

            } // end neighborhood loop

            // Compute average for each channel
            double num_pixels = kernel_size * kernel_size;

            for (int ch = 0; ch < image.c; ++ch) {
                double avg_value = sum[ch] / num_pixels;
                image.data[y * image.w * image.c + x * image.c + ch] = static_cast<unsigned char>(avg_value);
            } // end channel loop

        } // end x axis loop

    } // end y axis  loop

} // end Box filter

void Filter::applyGaussianFilter2D(Image &image, int kernel_size, double sigma) {
    std::cout << "\nApplying image gaussian blur filter" << std::endl;

    // Generate 1D Gaussian kernel for X and Y axes
    std::vector<double> kernel = generate1DGaussianKernel(kernel_size, sigma);

    Image tempImage1;
    tempImage1.createEmpty(image.w, image.h, image.c);
    // Second temporary volume for the final result (optional, depending on in-place update feasibility)
    Image tempImage2;
    tempImage2.createEmpty(image.w, image.h, image.c);

    // Apply along X-axis
    apply1DConvolution2D(image, tempImage1, kernel, Axis::X);
    // Apply along Y-axis
    apply1DConvolution2D(tempImage1, tempImage2, kernel, Axis::Y);

    // Copy the blurred image back to the original image
    std::copy(tempImage2.data, tempImage2.data + tempImage2.w * tempImage2.h * tempImage2.c, image.data);
}

// Edge detection filters:

void Filter::applyEdgeDetection(Image &image, const int gx[3][3], const int gy[3][3], PaddingMethod padding) {

    std::cout << "\nApplying edge detection filter with dynamic padding" << std::endl;

    int width = image.w;
    int height = image.h;
    int channels = image.c;
    assert(image.w >= 3 && image.h >= 3);
    unsigned char *output = new unsigned char[width * height * channels];

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            float sumX = 0.0f, sumY = 0.0f;

            for (int ky = -1; ky <= 1; ky++) {
                for (int kx = -1; kx <= 1; kx++) {
                    int px = x + kx;
                    int py = y + ky;

                    // Apply padding based on the selected padding method
                    switch (padding) {
                        case PaddingMethod::Zero:
                            if (px < 0 || px >= width || py < 0 || py >= height) continue; // Skip padding
                            break;
                        case PaddingMethod::Reflect:
                            if (px < 0) px = -px - 1;
                            if (py < 0) py = -py - 1;
                            if (px >= width) px = width - (px - width) - 1;
                            if (py >= height) py = height - (py - height) - 1;
                            break;
                        case PaddingMethod::Copy:
                            if (px < 0) px = 0;
                            if (py < 0) py = 0;
                            if (px >= width) px = width - 1;
                            if (py >= height) py = height - 1;
                            break;
                    }

                    float pixel = (float) image.data[(px + py * width) * channels];
                    sumX += pixel * gx[ky + 1][kx + 1];
                    sumY += pixel * gy[ky + 1][kx + 1];
                }
            }

            float magnitude = std::min<float>(sqrt(sumX * sumX + sumY * sumY), static_cast<double> (255.0f));
            output[(x + y * width) * channels] = (unsigned char) magnitude;

            for (int c = 1; c < channels; c++) {
                output[(x + y * width) * channels + c] = output[(x + y * width) * channels];
            }
        }
    }

    std::copy(output, output + width * height * channels, image.data);

    delete[] output;
}

void Filter::robert(Image &image) {
    //record run time for robert filter
    auto start = std::chrono::high_resolution_clock::now();
    int gx[3][3] = {{1, 0,  0},
                    {0, -1, 0},
                    {0, 0,  0}};
    int gy[3][3] = {{0,  1, 0},
                    {-1, 0, 0},
                    {0,  0, 0}};
    applyEdgeDetection(image, gx, gy);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Elapsed time for robert filter: " << elapsed.count() << " s\n";
}


void Filter::prewitt(Image &image) {
    auto start = std::chrono::high_resolution_clock::now();
    int gx[3][3] = {{-1, 0, 1},
                    {-1, 0, 1},
                    {-1, 0, 1}};
    int gy[3][3] = {{-1, -1, -1},
                    {0,  0,  0},
                    {1,  1,  1}};
    applyEdgeDetection(image, gx, gy);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Elapsed time for prewitt filter: " << elapsed.count() << " s\n";
}

void Filter::scharr(Image &image) {
    //record run time for scharr filter
    auto start = std::chrono::high_resolution_clock::now();
    int gx[3][3] = {{-3,  0, 3},
                    {-10, 0, 10},
                    {-3,  0, 3}};
    int gy[3][3] = {{-3, -10, -3},
                    {0,  0,   0},
                    {3,  10,  3}};
    applyEdgeDetection(image, gx, gy);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Elapsed time for scharr filter: " << elapsed.count() << " s\n";
}

void Filter::sobel(Image &image) {
    //record run time for sobel filter
    auto start = std::chrono::high_resolution_clock::now();
    int gx[3][3] = {{-1, 0, 1},
                    {-2, 0, 2},
                    {-1, 0, 1}};
    int gy[3][3] = {{-1, -2, -1},
                    {0,  0,  0},
                    {1,  2,  1}};
    applyEdgeDetection(image, gx, gy);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Elapsed time for sobel filter: " << elapsed.count() << " s\n";
}

void Filter::applyGaussianFilter3D(Volume &volume, int kernelSize, double sigma) {
    std::vector<double> kernel = generate1DGaussianKernel(kernelSize, sigma);

    int width = volume.getWidth();
    int height = volume.getHeight();
    int depth = volume.getDepth();

    // First temporary volume for the intermediate result
    Volume tempVolume1;
    tempVolume1.createEmpty(width, height, depth);
    // Second temporary volume for the final result (optional, depending on in-place update feasibility)
    Volume tempVolume2;
    tempVolume2.createEmpty(width, height, depth);

    // Apply along X-axis
    apply1DConvolution3D(volume, tempVolume1, kernel, Axis::X);
    // Apply along Y-axis
    apply1DConvolution3D(tempVolume1, tempVolume2, kernel, Axis::Y);
    // Apply along Z-axis (using tempVolume2 as input and writing back to tempVolume1 for the final result)
    apply1DConvolution3D(tempVolume2, tempVolume1, kernel, Axis::Z);

    // Replace the original volume data with the filtered data
    for (int z = 0; z < depth; ++z) {
        Image slice = tempVolume1.getSlice(z);
        volume.updateSlice(z, slice);
    }

}

void Filter::applyMedianFilter3D(Volume &volume, int kernelSize) {
    int width = volume.getWidth();
    int height = volume.getHeight();
    int depth = volume.getDepth();

    // Initialize a new volume data to store the filtered results
    Volume filteredVolume;
    filteredVolume.createEmpty(width, height, depth);

    int offset = kernelSize / 2;
    std::array<int, 256> histogram; // Histogram for 8-bit values

    // Precompute neighborhood offsets
    std::vector<std::tuple<int, int, int>> offsets;
    for (int dz = -offset; dz <= offset; ++dz) {
        for (int dy = -offset; dy <= offset; ++dy) {
            for (int dx = -offset; dx <= offset; ++dx) {
                offsets.emplace_back(dx, dy, dz);
            }
        }
    }

    // Apply median filter
    for (int z = 0; z < depth; ++z) {
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                std::fill(histogram.begin(), histogram.end(), 0);
                int neighborhoodCount = 0;

                // Use precomputed offsets to collect neighborhood values
                for (const auto &[dx, dy, dz]: offsets) {

                    // nearest mode
                    int nz = std::min(std::max(z + dz, 0), depth - 1);
                    int ny = std::min(std::max(y + dy, 0), height - 1);
                    int nx = std::min(std::max(x + dx, 0), width - 1);

                    unsigned char voxelValue = volume.getVoxel(nx, ny, nz);
                    histogram[voxelValue]++;
                    neighborhoodCount++;

                }

                // Find the median from the histogram
                int count = 0;
                unsigned char medianValue = 0;
                for (int i = 0; i < 256; i++) {
                    count += histogram[i];
                    if (count >= (neighborhoodCount / 2)) {
                        medianValue = i;
                        break;
                    }
                }
                filteredVolume.setVoxel(medianValue, x, y, z);
            }
        }
    }

    // Replace old slices with the new filtered data
    for (int z = 0; z < depth; ++z) {
        volume.updateSlice(z, filteredVolume.getSlice(z));
    }
}

