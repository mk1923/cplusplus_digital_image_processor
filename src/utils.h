/**
* @file utils.h
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

#include <iostream>
#include <vector>
#include <cmath>
#include <vector>
#include "Image.h" // Make sure this is correctly included for Image class definition
#include "Volume.h" // Include the header file that defines the "Volume" class
#include "Filter.h" // Include if necessary for Axis enum

/**
 * @brief Partitions the array for the quicksort algorithm.
 * 
 * @param arr  Reference to the vector of unsigned char elements to be partitioned.
 * @param left  The starting index of the segment of the array to be partitioned.
 * @param right  The ending index of the segment of the array to be partitioned.
 * @return int  The index position of the pivot element after partitioning.
 *
 * This function takes the last element as pivot, places the pivot element at its correct
 * position in the sorted array, and places all smaller (smaller than pivot) to the left of
 * the pivot and all greater elements to the right of the pivot. This is a helper function
 * used by the quicksort algorithm for sorting elements within an array.
 * Reference: 
 * Quickselect algorithm: https://chat.openai.com/share/4db4258a-0cc1-4d63-b2fd-8191371133e1
 */
int partition(std::vector<unsigned char>& arr, int left, int right);

/**
 * @brief Apply quick select algorithm to find the k-th smallest element
 * 
 * @param arr  Reference to the vector of unsigned char elements from which to select.
 * @param left  The starting index of the segment within the array to perform the selection.
 * @param right  The ending index of the segment within the array to perform the selection.
 * @param k  The index (0-based) of the smallest element to find. For example, k = 0 will find the smallest element,
 *           and k = length of array - 1 will find the largest element.
 * @return unsigned char  The k-th smallest element in the specified segment of the array.
 *
 * Quickselect is a selection algorithm to find the k-th smallest element in an unordered list.Quickselect
 * uses the same overall approach as quicksort, choosing one element as a pivot and partitioning the
 * data in two based on the pivot, accordingly as less than or greater than the pivot.
 */
unsigned char quickSelect(std::vector<unsigned char>& arr, int left, int right, int k);

/**
 * @brief Generate 1D Gaussian kernel
 * 
 * @param kernelSize  The size of the kernel. It determines the length of the generated Gaussian kernel vector.
 *                    The kernel size should be a positive odd integer to ensure symmetry around the center.
 * @param sigma  The standard deviation of the Gaussian distribution.
 * @return std::vector<double>  A vector of doubles representing the normalized 1D Gaussian kernel.
 *
 * This function generates a 1D Gaussian kernel with a specified size and standard deviation (sigma).
 * The generated kernel is normalized so that the sum of its elements equals 1, ensuring that the
 * application of the kernel does not change the overall brightness of the image.
 */
std::vector<double> generate1DGaussianKernel(int kernelSize, double sigma);

/**
 * @brief Applies a 1D convolution to a 2D image along a specified axis.
 *
 * @param inputImage  The input image to be convolved. This image remains unchanged.
 * @param outputImage  The output image where the result of the convolution is stored.
 * @param kernel  The convolution kernel as a vector of doubles. The kernel should be normalized.
 * @param axis  The axis along which to apply the convolution, specified as an `Axis` type.
 *              This can be `Axis::X` for horizontal or `Axis::Y` for vertical convolution.
 *
 * This function applies a 1D convolution to the input image using the specified kernel.
 * The convolution can be performed either horizontally (along the X axis) or vertically
 * (along the Y axis) as specified by the `axis` parameter. The function handles edge pixels
 * by replicating the nearest edge value, ensuring that the output image has the same dimensions
 * as the input. The output image is then filled with the results of the convolution.
 */
void apply1DConvolution2D(Image& inputImage, Image& outputImage, const std::vector<double>& kernel, Axis axis);

/**
 * @brief Apply 1D convolution to a volume
 * 
 * @param inputVolume  Input volume for convolution.
 * @param outputVolume  Volume to store the convolved data.
 * @param kernel  Convolution kernel, normalized to ensure intensity preservation.
 * @param axis  Axis along which the convolution is applied (X, Y, or Z).
 *
 * Performs 1D convolution across one axis of a 3D volume with a specified kernel. It's used
 * to apply filters like Gaussian blur in a separable manner. The function ensures edges are
 * handled by replicating edge values, maintaining the volume's dimensions.
 */
void apply1DConvolution3D(Volume& inputVolume, Volume& outputVolume, const std::vector<double>& kernel, Axis axis);

/**
 * @brief Merge two sorted arrays
 * 
 * @param arr  input array
 * @param left  input left index
 * @param middle  input middle index
 * @param right  input right index
 */
void merge(std::vector<std::string>& filePaths, int left, int middle, int right);

/**
 * @brief Merge sort the array
 * 
 * @param arr  input array
 * @param left  input left index
 * @param right  input right index
 */
void mergeSort(std::vector<std::string>& filePaths, int left, int right);

/**
 * @brief Extract the filename without extension
 * 
 * @param filename  input filename
 * @return std::string  resultant filename
 */
std::string extractFilenameWithoutExtension(const std::string &filename);

/**
 * @brief Convert number to string
 * 
 * @param number  input number
 * @return std::string  resultant string
 */
std::string convertNumberToString(int number);

/**
 * @brief Create output directory
 * 
 * @param path     input path
 */
void createOutputDirectory(const std::string &path);

/**
 * @brief Extract the filename from the path
 * 
 * @param path  input path
 * @return std::string  resultant filename
 */
std::string extractFilename(const std::string &path);

#endif // UTILS_H

