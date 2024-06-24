/**
* @file Volume.h
* Group Name: Fibonacci
* Name: Yibin Gao           Github_name: edsml-kg23
* Name: Ruihan He           Github_name: edsml-rh323
* Name: Yu Yin              Github_name: acse-yy923
* Name: Sara Lakatos        Github_name: acse-sl4623
* Name: Manawi Kahie        Github_name: acse-mk1923
* Name: Wenyi Yang          Github_name: acse-wy1023
* 
*/

// Volume.h
#ifndef VOLUME_H
#define VOLUME_H

#include "Image.h"
#include <vector>
#include <string>

class Volume {
public:
/**
 * @brief Construct a new Volume object
 * 
 */
    Volume(); // use the directory path to load the volume

/**
 * @brief Construct a new Volume object from the directory path
 * 
 * @param directoryPath  input directory path
 */
    Volume(const std::string& directoryPath);

/**
 * @brief Get the Slice object
 * 
 * @param index  input index
 * @return Image  resultant image
 */
    Image getSlice(int index) const; // get the image slice from the volume index

/**
 * @brief load the volume from the directory path
 * 
 * @param directoryPath  input directory path
 */
    void loadVolume(const std::string& directoryPath); // load the volume from the directory path

/**
 * @brief Create a Empty object
 * 
 * @param width  input width
 * @param height  input height
 * @param depth  input depth
 */
    void createEmpty(int width, int height, int depth);

/**
 * @brief Get the Width object
 * 
 * @return int  resultant width
 */
    int getWidth() const;

/**
 * @brief Get the Height object
 * 
 * @return int  resultant height
 */
    int getHeight() const;

/**
 * @brief Get the Depth object
 * 
 * @return int  resultant depth
 */
    int getDepth() const;

/**
 * @brief Get the Voxel object
 * 
 * @param x  input x
 * @param y  input y   
 * @param z  input z
 * @return unsigned char  resultant unsigned char
 */
    unsigned char getVoxel(int x, int y, int z) const;

/**
 * @brief Set the Voxel object
 * 
 * @param v  input v
 * @param x  input x
 * @param y  input y
 * @param z  input z
 */
    void setVoxel(unsigned char v, int x, int y, int z);

/**
 * @brief Update the Slice object
 * 
 * @param z  input z
 * @param newData  input newData
 */
    void updateSlice(int z, Image newData);

/**
 * @brief save the volume to the output directory
 * 
 * @param outputDirectory  input output directory
 */
    void saveVolume(const std::string& outputDirectory) const;
    
    // Added methods
/**
 * @brief slice the volume in the XY plane
 * 
 * @param zCoordinate  input z coordinate
 * @return Image  resultant image
 */
    Image sliceXY(int zCoordinate) const;

/**
 * @brief slice the volume in the XZ plane
 * 
 * @param yCoordinate  input y coordinate
 * @return Image  resultant image
 */
    Image sliceXZ(int yCoordinate) const;

/**
 * @brief slice the volume in the YZ plane
 * 
 * @param xCoordinate  input x coordinate
 * @return Image  resultant image
 */
    Image sliceYZ(int xCoordinate) const;

/**
 * @brief Get the Slices object
 * 
 * @return const std::vector<Image>& resultant vector of images 
 */
    // Inline definition of getSlices
    const std::vector<Image>& getSlices() const { return slices; }

private:
    int width, height, depth;
    std::vector<Image> slices; // store the slices of the volume
};

#endif
