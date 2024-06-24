/**
* @file Slice.cpp
* Group Name: Fibonacci
* Name: Yibin Gao           Github_name: edsml-kg23
* Name: Ruihan He           Github_name: edsml-rh323
* Name: Yu Yin              Github_name: acse-yy923
* Name: Sara Lakatos        Github_name: acse-sl4623
* Name: Manawi Kahie        Github_name: acse-mk1923
* Name: Wenyi Yang          Github_name: acse-wy1023
* 
*/

//Slice.cpp
#include "Slice.h"
#include <iostream>
#include "Volume.h"
#include <filesystem>

namespace fs = std::filesystem;


// Generate a slice in the XY plane at a given z-depth
Image Slicer::sliceXY(const Volume& volume, int z) {
    if (z < 0 || z >= volume.getDepth()) {
        std::cerr << "Z coordinate out of range for sliceXY" << std::endl;
        return Image();
    }
    return volume.getSlices()[z]; // Use the getter here
}

// Generate a slice in the YZ plane at a given x-coordinate
Image Slicer::sliceYZ(const Volume& volume, int x) {
    if (x < 0 || x >= volume.getWidth()) {
        std::cerr << "X coordinate out of range for sliceYZ" << std::endl;
        return Image();
    }
    Image slice(volume.getHeight(), volume.getDepth(), 3); // Assuming 3 channels for RGB
    for (int y = 0; y < volume.getHeight(); ++y) {
        for (int z = 0; z < volume.getDepth(); ++z) {
            slice.setPixel(y, z, volume.getSlices()[z].getPixel(x, y)); // Use the getter here
        }
    }
    return slice;
}

// Generate a slice in the XZ plane at a given y-coordinate
Image Slicer::sliceXZ(const Volume& volume, int y) {
    if (y < 0 || y >= volume.getHeight()) {
        std::cerr << "Y coordinate out of range for sliceXZ" << std::endl;
        return Image();
    }
    Image slice(volume.getWidth(), volume.getDepth(), 3); // Assuming 3 channels for RGB
    for (int x = 0; x < volume.getWidth(); ++x) {
        for (int z = 0; z < volume.getDepth(); ++z) {
            slice.setPixel(x, z, volume.getSlices()[z].getPixel(x, y)); // Use the getter here
        }
    }
    return slice;
}

// Method for generating slices at specific coordinates
void Slicer::generateSlices(const Volume& volume, const std::string& sliceFolder, int xCoordinate, int yCoordinate) {
    // Ensure the slice folder exists
    fs::path fsSliceFolder = sliceFolder;
    if (!fs::exists(fsSliceFolder)) {
        fs::create_directories(fsSliceFolder);
    }

    // Generate and save YZ slice at xCoordinate
    Image yzSlice = sliceYZ(volume, xCoordinate);
    fs::path yzFilename = fsSliceFolder / ("slice_yz_x" + std::to_string(xCoordinate) + ".png");
    yzSlice.save(yzFilename.string());

    // Generate and save XZ slice at yCoordinate
    Image xzSlice = sliceXZ(volume, yCoordinate);
    fs::path xzFilename = fsSliceFolder / ("slice_xz_y" + std::to_string(yCoordinate) + ".png");
    xzSlice.save(xzFilename.string());

    std::cout << "Slices generated at specified coordinates." << std::endl;
}
