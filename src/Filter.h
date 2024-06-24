/**
* @file Filter.h
* Group Name: Fibonacci
* Name: Yibin Gao           Github_name: edsml-kg23
* Name: Ruihan He           Github_name: edsml-rh323
* Name: Yu Yin              Github_name: acse-yy923
* Name: Sara Lakatos        Github_name: acse-sl4623
* Name: Manawi Kahie        Github_name: acse-mk1923
* Name: Wenyi Yang          Github_name: acse-wy1023
* 
*/
#ifndef FILTER_H
#define FILTER_H

#include "Image.h"
#include "Volume.h"
#include <string>
#include <vector>


enum class Axis { X, Y, Z };


class Filter {
private:
    enum class PaddingMethod {
        Zero, // Zero padding
        Reflect, // Reflect padding
        Copy // Copy edge padding
    };

/*
 * Applies a generic edge detection filter to an image using specified gradient operators.
 * 
 * @param image Reference to an Image object containing the source image data.
 *              The function directly modifies the image object to store the result.
 * @param gx    The horizontal gradient operator (kernel) for edge detection.
 * @param gy    The vertical gradient operator (kernel) for edge detection.
 * @param padding Enum value specifying the padding method to use (Zero, Reflect, Copy).
 * 
 * Process:
 * - Computes horizontal and vertical gradients at each pixel using gx and gy kernels.
 * - Calculates the gradient magnitude as the Euclidean norm of the horizontal and vertical gradients.
 * - Normalizes the gradient magnitude to fit within the range of 0 to 255.
 * - Supports different padding methods to handle edge pixels.
 * - reference: https://chat.openai.com/share/6133745c-f97e-465e-a3a8-a39cfe72eeaa
 */
    static void applyEdgeDetection(Image &image, const int gx[3][3], const int gy[3][3],
                                   PaddingMethod padding = PaddingMethod::Reflect);

public:

/**
 * Applies a grayscale filter to the given image.
 *
 * @param image The image to apply the filter to.
 *
 * The grayscale filter converts the RGB image to a single-channel grayscale image.
 * The grayscale value is calculated using the formula:
 * gray = 0.2126 * r + 0.7152 * g + 0.0722 * b
 */
    static void grayscale(Image &image);

    /**
     * Applies a brightness filter to the given image.
     *
     * @param image The image to apply the filter to.
     * @param brightness The brightness value to apply to the image.
     * @param autoBrightness Flag to enable automatic brightness calculation.
     *
     * The brightness filter adjusts the brightness of the image by adding a constant value.
     * The brightness value can be manually set or automatically calculated based on the image.
     * The autoBrightness flag enables automatic brightness calculation based on the average pixel value.
     */
    static void brightness(Image &image, int brightness, bool autoBrightness);

    /**
     * Applies a histogram equalization filter to the given image.
     *
     * @param image The image to apply the filter to.
     * @param hsv Flag to indicate whether to use HSV or HSL color space.
     *
     * The histogram equalization filter enhances the contrast of the image by redistributing the pixel intensity values.
     * The filter is applied to the grayscale image or each channel of the RGB image separately.
     */
    static void histogramEqualization(Image &image, bool hsv);

  /**
     * Applies a threshold filter to the given image.
     *
     * @param image The image to apply the filter to.
     * @param threshold The threshold value to use for binarization.
     * @param useHsv Flag to enable thresholding in HSV color space.
     *
     * The threshold filter converts the image to a binary image based on the threshold value.
     * The filter is applied to the grayscale image or the V channel in the HSV color space.
     * Pixels with intensity values below the threshold are set to 0 (black), and above to 255 (white).
     */
    static void threshold(Image &image, int threshold, bool useHsv);

    /**
     * Adds salt-and-pepper noise to the given image.
     *
     * @param image The image to add noise to.
     * @param noisePercentage The percentage of pixels to noise.
     *
     * The salt-and-pepper noise filter randomly sets a percentage of pixels to either 0 (black) or 255 (white).
     * The noise percentage determines the number of pixels to noise in the image.
     * The filter is applied to the grayscale image or all channels in the RGB image.
     */
    static void addSaltPepperNoise(Image &image, float noisePercentage);

/**
 * Applies the image median blur filter to the given image.
 * 
 * @param image The image to apply the filter to.
 * @param kernel_size The size of the kernel used for blurring.
 * 
 * The image median blur filter calculates the median value of the RGB channels
 * for each pixel and assigns the median value to the pixel. The filter is applied
 * to the image by looping through each pixel and its surrounding pixels within
 * the specified kernel size. The median value is calculated for the red, green,
 * and blue channels separately, and then assigned to the current pixel.
 * Source reference: https://chat.openai.com/share/bfc5caa6-324f-4f8a-9967-d4a960433151
 */
    static void applyMedianFilter2D(Image& image, int kernel_size);

  /**
 * Applies a box blur filter to the given image.
 *
 * @param image The image to apply the filter to.
 * @param kernel_size The size of the kernel used for blurring.
 * 
 *
 * Applies a simple box blur filter to the image using the specified kernel size.
 * The box blur filter is a simple averaging of the surrounding pixels.
 * The kernel size determines the number of surrounding pixels to consider.
 */
    static void applyBoxFilter2D(Image& image, int kernel_size);

/**
 * Applies a Gaussian blur filter to the given image.
 *
 * @param image The image to apply the filter to.
 * @param kernel_size The size of the kernel used for blurring.
 * @param sigma The standard deviation of the Gaussian distribution.
 * 
 * Generates a Gaussian kernel using the specified kernel size.
 * Applies the Gaussian kernel to the image to perform the blur.
 */
    static void applyGaussianFilter2D(Image& image, int kernel_size, double sigma = 2.0);

/*
 * Applies the Sobel edge detection filter to an image.
 * 
 * @param image Reference to an Image object that will be processed.
 *              The result is stored directly in this object.
 * 
 * Process:
 * - Utilizes predefined Sobel operators for horizontal and vertical gradient calculation.
 * - Invokes applyEdgeDetection with the Sobel operators to detect edges in the image.
 * - reference: https://en.wikipedia.org/wiki/Sobel_operator
 */
    static void sobel(Image &image);

/*
 * Applies the Robert Cross edge detection filter to an image.
 * 
 * @param image Reference to an Image object that will be processed.
 *              The result is stored directly in this object.
 * 
 * Process:
 * - Uses predefined Robert Cross operators for horizontal and vertical gradient calculation.
 * - Invokes applyEdgeDetection with the Robert Cross operators to perform the edge detection.
 * - reference: https://en.wikipedia.org/wiki/Roberts_Cross
 */
    static void robert(Image &image);

/*
 * Applies the Scharr edge detection filter to an image.
 * 
 * @param image Reference to an Image object that will be processed.
 *              The result is stored directly in this object.
 * 
 * Process:
 * - Uses predefined Scharr operators for more accurate horizontal and vertical gradient calculation.
 * - Invokes applyEdgeDetection with the Scharr operators to perform the edge detection.
 * - reference: https://theailearner.com/tag/scharr-operator/
 */
    static void scharr(Image &image);

/*
 * Applies the Prewitt edge detection filter to an image.
 * 
 * @param image Reference to an Image object that will be processed.
 *              The result is stored directly in this object.
 * 
 * Process:
 * - Uses predefined Prewitt operators for horizontal and vertical gradient calculation.
 * - Invokes applyEdgeDetection with the Prewitt operators to perform the edge detection.
 * - reference: https://en.wikipedia.org/wiki/Prewitt_operator
 */
    static void prewitt(Image &image);

/**
 * @brief Apply a Guassian filter to a 3d volume
 * 
 * @param volume Reference to the Volume object to be filtered.
 *               The volume is updated in-place with the filtered results.
 * @param kernelSize The size of the Gaussian kernel to be used for filtering, which should be a positive odd integer.
 * @param sigma  The standard deviation of the Gaussian kernel.
 *
 * This function applies a Gaussian filter to the given 3D volume using a separable approach.
 * It first generates a 1D Gaussian kernel based on the specified kernel size and sigma (standard deviation).
 * The filtering is performed in three steps, applying the 1D convolution along the X, Y, and Z axes sequentially.
 * This separable approach is more efficient than a direct 3D convolution, especially for larger kernel sizes.
 * The original volume is updated with the filtered results.
 */
    static void applyGaussianFilter3D(Volume& volume, int kernelSize, double sigma);

/**
 * @brief Apply a median filter to a 3d volume
 * 
 * @param volume Reference to the Volume object to be filtered.
 *               The volume is updated in-place with the filtered results.
 * @param kernelSize The size of the cubic neighborhood around each voxel considered for median filtering,
 *                   which should be a positive odd integer to ensure a single median value can be computed.
 *
 * This function filters the given 3D volume using a median filter. The function operates by moving through each voxel
 * in the volume, considering a cubic neighborhood around it defined by the kernel size. It calculates the median value
 * within this neighborhood and sets the voxel's new value to this median.
 */
    static void applyMedianFilter3D(Volume& volume, int kernelSize);

};
#endif

