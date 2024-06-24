/**
* @file utils.cpp
* Group Name: Fibonacci
* Name: Yibin Gao           Github_name: edsml-kg23
* Name: Ruihan He           Github_name: edsml-rh323
* Name: Yu Yin              Github_name: acse-yy923
* Name: Sara Lakatos        Github_name: acse-sl4623
* Name: Manawi Kahie        Github_name: acse-mk1923
* Name: Wenyi Yang          Github_name: acse-wy1023
* 
*/

#ifndef UTILS_H
#define UTILS_H

#include <cmath>
#include <iostream>
#include "Filter.h" // Include the header file that defines the "Axis" enum// Include the header file that defines the "Volume" class
#include "utils.h"


int partition(std::vector<unsigned char>& arr, int left, int right) {
    unsigned char pivot = arr[right];
    int i = left - 1;
    for (int j = left; j < right; j++) {
        if (arr[j] < pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[right]);
    return i + 1;
}

unsigned char quickSelect(std::vector<unsigned char>& arr, int left, int right, int k) {
    if (left == right) return arr[left];

    int pivotIndex = partition(arr, left, right);
    if (k == pivotIndex) {
        return arr[k];
    } else if (k < pivotIndex) {
        return quickSelect(arr, left, pivotIndex - 1, k);
    } else {
        return quickSelect(arr, pivotIndex + 1, right, k);
    }
}

std::vector<double> generate1DGaussianKernel(int kernelSize, double sigma) {
    std::vector<double> kernel(kernelSize);
    double sum = 0.0;
    int halfSize = kernelSize / 2;

    for(int i = 0; i < kernelSize; ++i) {
        double x = i - halfSize;
        kernel[i] = std::exp(-(x * x) / (2 * sigma * sigma)) / (std::sqrt(2 * M_PI) * sigma);
        sum += kernel[i];
    }

    // Normalize the kernel
    for(double &value : kernel) {
        value /= sum;
    }

    return kernel;
}

void apply1DConvolution2D(Image& inputImage, Image& outputImage, const std::vector<double>& kernel, Axis axis) {
    int width = inputImage.w;
    int height = inputImage.h;
    int channels = inputImage.c;
    int halfSize = kernel.size() / 2;

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            for (int ch = 0; ch < channels; ++ch) {
                double sum = 0.0;
                double kernelSum = 0.0;
                for (int k = -halfSize; k <= halfSize; ++k) {
                    int nx = x, ny = y;

                    // Determine the index based on the axis
                    switch (axis) {
                        case Axis::X: nx = std::max(0, std::min(x + k, width - 1)); break;
                        case Axis::Y: ny = std::max(0, std::min(y + k, height - 1)); break;
                    }

                    sum += inputImage.getPixel(nx, ny, ch) * kernel[k + halfSize];
                    kernelSum += kernel[k + halfSize];
                }
                unsigned char filteredValue = static_cast<unsigned char>(std::round(sum / kernelSum));
                outputImage.setPixel(x, y, ch, filteredValue);
            }
        }
    }
}


void apply1DConvolution3D(Volume& inputVolume, Volume& outputVolume, const std::vector<double>& kernel, Axis axis) {
    int width = inputVolume.getWidth();
    int height = inputVolume.getHeight();
    int depth = inputVolume.getDepth();
    int halfSize = kernel.size() / 2;

    for (int z = 0; z < depth; ++z) {
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                double sum = 0.0;
                double kernelSum = 0.0;
                for (int k = -halfSize; k <= halfSize; ++k) {
                    int nx = x, ny = y, nz = z;

                    // Determine the index based on the axis
                    switch (axis) {
                        case Axis::X: nx = std::max(0, std::min(x + k, width - 1)); break;
                        case Axis::Y: ny = std::max(0, std::min(y + k, height - 1)); break;
                        case Axis::Z: nz = std::max(0, std::min(z + k, depth - 1)); break;
                    }

                    sum += inputVolume.getVoxel(nx, ny, nz) * kernel[k + halfSize];
                    kernelSum += kernel[k + halfSize];
                }
                unsigned char filteredValue = static_cast<unsigned char>(std::round(sum / kernelSum));
                outputVolume.setVoxel(filteredValue, x, y, z);
            }
        }
    }
}

// sort the file paths based on the number in the file name
void merge(std::vector<std::string>& filePaths, int left, int middle, int right) {
    int n1 = middle - left + 1;
    int n2 = right - middle;

    std::vector<std::string> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = filePaths[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = filePaths[middle + 1 + j];

    int i = 0;
    int j = 0;
    int k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            filePaths[k] = L[i];
            i++;
        } else {
            filePaths[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        filePaths[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        filePaths[k] = R[j];
        j++;
        k++;
    }
}

// merge sort the file paths
void mergeSort(std::vector<std::string>& filePaths, int left, int right) {
    if (left >= right) {
        return; //
    }
    int middle = left + (right - left) / 2;
    mergeSort(filePaths, left, middle);
    mergeSort(filePaths, middle + 1, right);
    merge(filePaths, left, middle, right);
}


std::string extractFilename(const std::string &path) {
    // Find the position of the last directory separator
    size_t lastSlashPos = path.find_last_of('/');
    if (lastSlashPos == std::string::npos) {
        // No directory separator found, return the whole path
        return path;
    } else {
        // Return the substring after the last directory separator
        return path.substr(lastSlashPos + 1);
    }
}

std::string extractFilenameWithoutExtension(const std::string &filename) {
    // Find the position of the last dot (.)
    size_t lastDotPos = filename.find_last_of('.');
    if (lastDotPos == std::string::npos) {
        // No dot found, return the whole filename
        return filename;
    } else {
        // Return the substring before the last dot
        return filename.substr(0, lastDotPos);
    }
}

std::string convertNumberToString(int number) {
    if (number < 0) {
        return "minus" + std::to_string(-number);
    } else {
        return "plus" + std::to_string(number);
    }
}

void createOutputDirectory(const std::string &path) {
    std::string command = "mkdir -p " + path;
    system(command.c_str());
}
#endif // UTILS_H