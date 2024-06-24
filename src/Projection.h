/**
* @file Projection.h
* Group Name: Fibonacci
* Name: Yibin Gao           Github_name: edsml-kg23
* Name: Ruihan He           Github_name: edsml-rh323
* Name: Yu Yin              Github_name: acse-yy923
* Name: Sara Lakatos        Github_name: acse-sl4623
* Name: Manawi Kahie        Github_name: acse-mk1923
* Name: Wenyi Yang          Github_name: acse-wy1023
* 
*/

// Projection.h
#ifndef PROJECTION_H
#define PROJECTION_H
#include "Image.h"
#include "Volume.h"

class Projection {
public:
/**
 * @brief Apply max intensity projection to 3d volume
 * 
 * @param volume  input volume
 * @param minIndex  input min index
 * @param maxIndex  input max index
 * @return Image  resultant image
 * 
 * Process:
 * - For each pixel in the output image, find the maximum intensity value along the z-axis.
 * - The output image will have the same width and height as the input volume.
 * - The intensity value at each pixel is the maximum intensity value found along the z-axis.
 * Reference: https://chat.openai.com/share/53c71398-4690-4906-a012-da51c683b7e1
 */
    static Image MIP(const Volume& volume, int minIndex, int maxIndex);

/**
 * @brief Apply min intensity projection to 3d volume
 * 
 * @param volume  input volume
 * @param minIndex  input min index
 * @param maxIndex  input max index
 * @return Image  resultant image
 * 
 * Process:
 * - For each pixel in the output image, find the minimum intensity value along the z-axis.
 * - The output image will have the same width and height as the input volume.
 * - The intensity value at each pixel is the minimum intensity value found along the z-axis.
 * Reference: https://chat.openai.com/share/53c71398-4690-4906-a012-da51c683b7e1
 */
    static Image MinIP(const Volume& volume, int minIndex, int maxIndex);

/**
 * @brief Apply average intensity projection to 3d volume
 * 
 * @param volume  input volume
 * @param minIndex  input min index
 * @param maxIndex  input max index
 * @return Image  resultant image
 * 
 * Process:
 * - For each pixel in the output image, find the average intensity value along the z-axis.
 * - The output image will have the same width and height as the input volume.
 * - The intensity value at each pixel is the average intensity value found along the z-axis.
 * Reference: https://chat.openai.com/share/53c71398-4690-4906-a012-da51c683b7e1
 */
    static Image AIP(const Volume& volume, int minIndex, int maxIndex);

/**
 * @brief Apply median intensity projection to 3d volume
 * 
 * @param volume  input volume
 * @param minIndex  input min index
 * @param maxIndex  input max index
 * @return Image  resultant image
 * 
 * Process:
 * - For each pixel in the output image, find the median intensity value along the z-axis.
 * - The output image will have the same width and height as the input volume.
 * - The intensity value at each pixel is the median intensity value found along the z-axis.
 * - The median intensity value is calculated using the quick select algorithm.
 * 
 * Reference: https://chat.openai.com/share/53c71398-4690-4906-a012-da51c683b7e1
 */
    static Image AIP_Median(const Volume& volume, int minIndex, int maxIndex);
};

#endif // PROJECTION_H
