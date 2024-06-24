/**
* @file Slice.h
* Group Name: Fibonacci
* Name: Yibin Gao           Github_name: edsml-kg23
* Name: Ruihan He           Github_name: edsml-rh323
* Name: Yu Yin              Github_name: acse-yy923
* Name: Sara Lakatos        Github_name: acse-sl4623
* Name: Manawi Kahie        Github_name: acse-mk1923
* Name: Wenyi Yang          Github_name: acse-wy1023
* 
*/
//Slice.h
#ifndef SLICE_H
#define SLICE_H

#include "Volume.h"
#include "Image.h"
#include <string>

class Slicer {
public:


/**
 * @brief Slice the volume in XY plane at z
 * 
 * @param volume  input volume
 * @param z  input z coordinate
 * @return Image  resultant image
 * 
 * Process:
 * - Generate a slice in the XY plane at a given z-depth.
 * - If the z-coordinate is out of range, print an error message and return an empty image.
 */

    static Image sliceXY(const Volume& volume, int z);

/**
 * @brief Slice the volume in YZ plane at x
 * 
 * @param volume  input volume
 * @param x  input x coordinate
 * @return Image  resultant image
 * Process:
 * - Generate a slice in the YZ plane at a given x-coordinate.
 * - If the x-coordinate is out of range, print an error message and return an empty image.
 */
    static Image sliceYZ(const Volume& volume, int x);

/**
 * @brief Slice the volume in XZ plane at y
 * 
 * @param volume  input volume
 * @param y  input y coordinate
 * @return Image  resultant image
 * 
 * Process:
 * - Generate a slice in the XZ plane at a given y-coordinate.
 * - If the y-coordinate is out of range, print an error message and return an empty image.
 */
    static Image sliceXZ(const Volume& volume, int y);


/**
 * @brief Generate slices at specific coordinates
 * 
 * @param volume  input volume
 * @param sliceFolder  input slice folder
 * @param xCoordinate  input x coordinate
 * @param yCoordinate  input y coordinate
 * 
 * Process:
 * - Ensure the slice folder exists.
 * - Generate and save YZ slice at xCoordinate.
 * - Generate and save XZ slice at yCoordinate.
 * 
 */
    // Declare the new method for generating slices at specific coordinates

    static void generateSlices(const Volume& volume, const std::string& sliceFolder, int xCoordinate, int yCoordinate);
};

#endif // SLICE_H
