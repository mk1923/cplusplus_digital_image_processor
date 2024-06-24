/**
* @file image.h
* Group Name: Fibonacci
* Name: Yibin Gao           Github_name: edsml-kg23
* Name: Ruihan He           Github_name: edsml-rh323
* Name: Yu Yin              Github_name: acse-yy923
* Name: Sara Lakatos        Github_name: acse-sl4623
* Name: Manawi Kahie        Github_name: acse-mk1923
* Name: Wenyi Yang          Github_name: acse-wy1023
* 
*/

// Image.h
#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include <vector>

class Image {
public:
    //3d slicing

/**
 * @brief Get the Width object
 * 
 * @return int width of the image
 * 
 * Process:
 * - Get the width of the image.
 */
    int getWidth() const;

/**
 * @brief Get the Height object
 * 
 * @return int height of the image
 * 
 * Process:
 * - Get the height of the image.
 */
    int getHeight() const;

/**
 * @brief Set the Pixel object
 * 
 * @param x input x coordinate
 * @param y  input y coordinate
 * @param value  input value
 * 
 *  Process:
 * - Set the pixel value at the given coordinates.
 * - If the coordinates are out of bounds, the function does nothing.
 */
    void setPixel(int x, int y, unsigned char value);

/**
 * @brief Get the Pixel object
 * 
 * @param x input x coordinate
 * @param y input y coordinate
 * @return unsigned char 
 * 
 * Process:
 * - Get the pixel value at the given coordinates.
 * - If the coordinates are out of bounds, the function returns 0.
 */
    unsigned char getPixel(int x, int y) const;

/**
 * @brief clone the image
 * 
 * @return Image reference to the cloned image
 * 
 * Process:
 * - Clone the image.
 * - Return the reference to the cloned image.
 */
    Image clone() const;

/**
 * @brief - operator overloading
 * 
 * @param other  input image
 * @return Image    resultant image
 * 
 * Process:
 * - Subtract the pixel values of the two images.
 * - Return the resultant image.
 * - If the images have different sizes, the resultant image will have the size of the larger image.
 * - If the images have different number of channels, the resultant image will have the number of channels of the larger image.
 * - If the pixel value is negative, it is set to 0.
 */
    Image operator-(const Image& other) const;

/**
 * @brief Get the File Name object
 * 
 * @return std::string  name of the file
 * 
 * Process:
 * - Get the name of the file.
 * - Return the name of the file.
 */
    std::string getFileName() const;

/**
 * @brief save the image
 * 
 * @param path  input path
 * 
 * Process:
 * - Save the image to the specified path.
 * - If the image is not saved successfully, an exception is thrown.
 */
    void save(const std::string& path) const;

/**
 * @brief Create a Empty object
 * 
 * @param width  input width
 * @param height  input height
 * @param channels  input channels
 * 
 * Process:
 * - Create an empty image with the specified width, height, and number of channels.
 */
    void createEmpty(int width, int height, int channels);

/**
 * @brief load the image
 * 
 * @param path  input path
 * 
 * Process:
 * - Load the image from the specified path.
 * - If the image is not loaded successfully, an exception is thrown.
 */
    void load(const std::string& path);

/**
 * @brief check if the image is same as the other image
 * 
 * @param other  input image
 * @return true  if the image is same
 * @return false  if the image is not same
 * 
 * Process:
 * - Check if the image is the same as the other image.
 * - Return true if the images are the same.
 * - Return false if the images are not the same.
 */
    bool isSameAs(const Image& other) const;

/**
 * @brief constructor 
 * 
 */
    unsigned char* data;
    int w, h, c;

    // Constructor
    Image(int width = 0, int height = 0, int channels = 3);

    // getter functions
/**
 * @brief Get the Pixel object
 * 
 * @param x  input x coordinate
 * @param y  input y coordinate
 * @param ch  input channel
 * @return unsigned char  pixel value
 * 
 * Process:
 * - Get the pixel value at the given coordinates and channel.
 * - If the coordinates or channel are out of bounds, the function throws an exception.
 * - Return the pixel value.
 */
    unsigned char getPixel(int x, int y, int ch) const;

/**
 * @brief Set the Pixel object
 * 
 * @param x  input x coordinate
 * @param y  input y coordinate
 * @param ch  input channel
 * @param value  input value
 * 
 * Process:
 *  - Set the pixel value at the given coordinates and channel.
 * - If the coordinates or channel are out of bounds, the function throws an exception.
 * - Set the pixel value.
 */
    void setPixel(int x, int y, int ch, unsigned char value);

    // Utility functions declarations

/**
 * @brief rgb to hsv conversion
 * 
 * @param r  input red value
 * @param g  input green value
 * @param b  input blue value
 * @param h  output hue value
 * @param s  output saturation value
 * @param v  output value
 * 
 * Process:
 * - Convert the RGB color to HSV color.
 * - Return the HSV color.
 * - The RGB color values are in the range [0, 255].
 * - The HSV color values are in the range [0, 360] for hue and [0, 1] for saturation and value.
 * - The hue value is in the range [0, 360].
 */
    static void rgbToHsv(float r, float g, float b, float &h, float &s, float &v);

/**
 * @brief hsv to rgb conversion
 * 
 * @param h  input hue value
 * @param s  input saturation value
 * @param v  input value
 * @param r  output red value
 * @param g  output green value
 * @param b  output blue value
 * 
 * Process:
 * - Convert the HSV color to RGB color.
 * - Return the RGB color.
 * - The HSV color values are in the range [0, 360] for hue and [0, 1] for saturation and value.
 * - The RGB color values are in the range [0, 255].
 * - The hue value is in the range [0, 360].
 */
    static void hsvToRgb(float h, float s, float v, int &r, int &g, int &b);

/**
 * @brief rgb to hsl conversion
 * 
 * @param r  input red value
 * @param g  input green value
 * @param b  input blue value
 * @param h  output hue value
 * @param s  output saturation value
 * @param l  output lightness value
 * 
 * Process:
 * - Convert the RGB color to HSL color.
 * - Return the HSL color.
 * - The RGB color values are in the range [0, 255].
 * - The HSL color values are in the range [0, 360] for hue and [0, 1] for saturation and lightness.
 * - The hue value is in the range [0, 360].
 * 
 */
    static void rgbToHsl(float r, float g, float b, float &h, float &s, float &l);

/**
 * @brief hsl to rgb conversion
 * 
 * @param h  input hue value
 * @param s  input saturation value
 * @param l  input lightness value
 * @param r  output red value
 * @param g  output green value
 * @param b  output blue value
 * 
 * Process:
 * - Convert the HSL color to RGB color.
 * - Return the RGB color.
 * - The HSL color values are in the range [0, 360] for hue and [0, 1] for saturation and lightness.
 * - The RGB color values are in the range [0, 255].
 */
    static void hslToRgb(float h, float s, float l, int &r, int &g, int &b);

/**
 * @brief calculate cdf
 * 
 * @param histogram  input histogram
 * @param cdf  output cdf
 * 
 * Process:
 * - Calculate the cumulative distribution function (CDF) from the histogram.
 * - The CDF is calculated by summing the histogram values.
 * - The CDF values are stored in the cdf vector.
 * - The histogram values are in the range [0, 255].
 * - The cdf values are in the range [0, total number of pixels].
 * - The cdf vector is resized to match the histogram size.
 */
    static void calculateCdf(const std::vector<int>& histogram, std::vector<int>& cdf);
};

#endif
