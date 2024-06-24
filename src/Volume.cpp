/**
* @file Volume.cpp
* Group Name: Fibonacci
* Name: Yibin Gao           Github_name: edsml-kg23
* Name: Ruihan He           Github_name: edsml-rh323
* Name: Yu Yin              Github_name: acse-yy923
* Name: Sara Lakatos        Github_name: acse-sl4623
* Name: Manawi Kahie        Github_name: acse-mk1923
* Name: Wenyi Yang          Github_name: acse-wy1023
* 
*/
// Volume.cpp
#include "Volume.h"
#include <iostream>
#include <filesystem>
#include <string>
#include <sstream>
#include <algorithm>
#include "utils.h"
namespace fs = std::filesystem;


Volume::Volume() {
    width = 0;
    height = 0;
    depth = 0;
}

Volume::Volume(const std::string& directoryPath) {
    loadVolume(directoryPath);
}

void Volume::loadVolume(const std::string& directoryPath) {
    slices.clear(); // clear the slices vector

    std::vector<std::string> filePaths;

    for (const auto& entry : fs::directory_iterator(directoryPath)) {
        if (entry.is_regular_file()) {
            // get the file path
            std::string filePath = entry.path().string();
            // get the extension of the file
            std::string extension = entry.path().extension().string();

            // convert the extension to lowercase
            std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);

            // check if the file is an image file
            if (extension == ".png" || extension == ".jpg") {
                filePaths.push_back(filePath);
            }
        }
    }

    // sort the file paths based on the number in the file name
    
   mergeSort(filePaths, 0, filePaths.size() - 1);

    // load the images from the file paths
    for (const auto& filePath : filePaths) {
        Image img;
        img.load(filePath);
        slices.push_back(img);
    }

    width = slices[0].w;
    height = slices[0].h;
    depth = slices.size();
}

// get the image slice from the volume index
Image Volume::getSlice(int index) const {
    if (index >= 0 && index < slices.size()) {
        return slices[index];
    } else {
        std::cerr << "Slice index out of range: " << index << std::endl;
        throw std::out_of_range("Slice index out of range");
    }
}

void Volume::createEmpty(int width, int height, int depth) {

    for (int z = 0; z < depth; ++z) {
        Image img;
        img.createEmpty(width, height, 1);
        slices.push_back(img);
    }
    this->width = width;
    this->height = height;
    this->depth = depth;
}


int Volume::getWidth() const {
    return width;
}

int Volume::getHeight() const {
    return height;
}

int Volume::getDepth() const {
    return depth;
}

unsigned char Volume::getVoxel(int x, int y, int z) const {
    if (x < 0 || x >= width || y < 0 || y >= height || z < 0 || z >= depth) {
        throw std::out_of_range("Voxel coordinates are out of the volume bounds.");
    }
    return slices[z].data[y * width + x];
}

void Volume::setVoxel(unsigned char v, int x, int y, int z){
    if (x < 0 || x >= width || y < 0 || y >= height || z < 0 || z >= depth) {
        throw std::out_of_range("Voxel coordinates are out of the volume bounds.");
    }
    slices[z].data[y * width + x] = v;
}

void Volume::updateSlice(int z, Image newImage) {
    if (z < 0 || z >= depth) {
        throw std::out_of_range("Index out of range in updateSlice.");
    }
    // Assuming the size of newData is equal to width * height
    std::copy(newImage.data, newImage.data + (width * height), slices[z].data);
}

void Volume::saveVolume(const std::string& outputDirectory) const {
    if (!fs::exists(outputDirectory)) {
        fs::create_directories(outputDirectory);
    }

    for (int i = 0; i < depth; ++i) {
        std::ostringstream filename;
        filename << "New_" << std::setw(4) << std::setfill('0') << (i + 1) << ".png";
        std::string fullPath = fs::path(outputDirectory) / filename.str();

        slices[i].save(fullPath);
        std::cout << "Saved: " << fullPath << std::endl;
    }
}

Image Volume::sliceXY(int zCoordinate) const {
    if (zCoordinate < 0 || zCoordinate >= getDepth()) {
        std::cerr << "Z coordinate out of range: " << zCoordinate << std::endl;
        return Image();
    }
    Image slice(getWidth(), getHeight());
    for (int y = 0; y < getHeight(); ++y) {
        for (int x = 0; x < getWidth(); ++x) {
            slice.setPixel(x, y, slices[zCoordinate].getPixel(x, y));
        }
    }
    return slice;
}

// Implementation of sliceXZ
Image Volume::sliceXZ(int yCoordinate) const {
    if (yCoordinate < 0 || yCoordinate >= getHeight()) {
        std::cerr << "Y coordinate out of range: " << yCoordinate << std::endl;
        return Image();
    }

    Image slice(getWidth(), getDepth());
    for (int z = 0; z < getDepth(); ++z) {
        for (int x = 0; x < getWidth(); ++x) {
            slice.setPixel(x, z, slices[z].getPixel(x, yCoordinate));
        }
    }
    return slice;
}

// Implementation of sliceYZ 
Image Volume::sliceYZ(int xCoordinate) const {
    if (xCoordinate < 0 || xCoordinate >= getWidth()) {
        std::cerr << "X coordinate out of range: " << xCoordinate << std::endl;
        return Image();
    }

    Image slice(getHeight(), getDepth());
    for (int z = 0; z < getDepth(); ++z) {
        for (int y = 0; y < getHeight(); ++y) {
            // Swap the axes when setting pixels: use y for x-coordinate, z for y-coordinate
            slice.setPixel(y, z, slices[z].getPixel(xCoordinate, y));
        }
    }
    return slice;
}
