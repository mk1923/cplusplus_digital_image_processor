/**
* @file Projection.cpp
* Group Name: Fibonacci
* Name: Yibin Gao           Github_name: edsml-kg23
* Name: Ruihan He           Github_name: edsml-rh323
* Name: Yu Yin              Github_name: acse-yy923
* Name: Sara Lakatos        Github_name: acse-sl4623
* Name: Manawi Kahie        Github_name: acse-mk1923
* Name: Wenyi Yang          Github_name: acse-wy1023
* 
*/
// Projection.cpp
#include "Projection.h"
#include <limits>
#include <iostream>
#include <vector>
#include "utils.h"

// Helper function to adjust user index to internal index (starting from 0)
int adjustIndex(int userIndex, int sliceCount) {
    if (userIndex < 1 || userIndex > sliceCount) {
        throw std::out_of_range("Index out of range");
    }
    return userIndex - 1; // Adjust for zero-based indexing
}


// Maximum Intensity Projection
Image Projection::MIP(const Volume& volume, int minIndex = 1, int maxIndex = -1) {
    // Adjust for zero-based indexing and entire volume processing
    int adjustedMinIndex = adjustIndex(minIndex, volume.getDepth());
    int adjustedMaxIndex = (maxIndex == -1) ? volume.getDepth() - 1 : adjustIndex(maxIndex, volume.getDepth());
    Image result;
    result.createEmpty(volume.getSlice(0).w, volume.getSlice(0).h, volume.getSlice(0).c);

    for (int i = adjustedMinIndex; i <= adjustedMaxIndex; ++i) {
        Image slice = volume.getSlice(i);
        for (int j = 0; j < slice.w * slice.h * slice.c; ++j) {
            result.data[j] = std::max(result.data[j], slice.data[j]);
        }
    }
    return result;
}

// Minimum Intensity Projection
Image Projection::MinIP(const Volume& volume, int minIndex = 1, int maxIndex = -1) {
    // Adjust for zero-based indexing and entire volume processing
    int adjustedMinIndex = adjustIndex(minIndex, volume.getDepth());
    int adjustedMaxIndex = (maxIndex == -1) ? volume.getDepth() - 1 : adjustIndex(maxIndex, volume.getDepth());
    Image result;
    result.createEmpty(volume.getSlice(0).w, volume.getSlice(0).h, volume.getSlice(0).c);
    // Initialize the result image with the maximum value
    std::fill_n(result.data, result.w * result.h * result.c, std::numeric_limits<unsigned char>::max());

    for (int i = adjustedMinIndex; i <= adjustedMaxIndex; ++i) {
        Image slice = volume.getSlice(i);
        for (int j = 0; j < slice.w * slice.h * slice.c; ++j) {
            result.data[j] = std::min(result.data[j], slice.data[j]);
        }
    }
    return result;
}

// Average Intensity Projection
Image Projection::AIP(const Volume& volume, int minIndex = 1, int maxIndex = -1) {
    int adjustedMinIndex = adjustIndex(minIndex, volume.getDepth());
    int adjustedMaxIndex = (maxIndex == -1) ? volume.getDepth() - 1 : adjustIndex(maxIndex, volume.getDepth());
    Image result;
    result.createEmpty(volume.getSlice(0).w, volume.getSlice(0).h, volume.getSlice(0).c);
    std::vector<int> tempBuffer(result.w * result.h * result.c, 0);

    for (int i = adjustedMinIndex; i <= adjustedMaxIndex; ++i) {
        Image slice = volume.getSlice(i);
        for (int j = 0; j < slice.w * slice.h * slice.c; ++j) {
            tempBuffer[j] += slice.data[j];
        }
    }

    int numSlices = adjustedMaxIndex - adjustedMinIndex;
    for (size_t j = 0; j < tempBuffer.size(); ++j) {
        result.data[j] = static_cast<unsigned char>(tempBuffer[j] / (numSlices + 1));
    }
    return result;
}

// Average Intensity Projection with self implemented quick select algorithm
Image Projection::AIP_Median(const Volume& volume, int minIndex = 1, int maxIndex = -1) {
    int adjustedMinIndex = adjustIndex(minIndex, volume.getDepth());
    int adjustedMaxIndex = (maxIndex == -1) ? volume.getDepth() - 1 : adjustIndex(maxIndex, volume.getDepth());
    Image result;
    result.createEmpty(volume.getSlice(0).w, volume.getSlice(0).h, volume.getSlice(0).c);

    std::vector<unsigned char> pixelValues(volume.getDepth());

    for (int j = 0; j < result.w * result.h * result.c; ++j) {
        for (int i = adjustedMinIndex; i <= adjustedMaxIndex; ++i) {
            pixelValues[i] = volume.getSlice(i).data[j];
        }

        // use quickselect to find the median value
        unsigned char median = quickSelect(pixelValues, 0, pixelValues.size() - 1, pixelValues.size() / 2);
        result.data[j] = median;
    }

    return result;
}