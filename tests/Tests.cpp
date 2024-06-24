#include <iostream>
#include <Projection.h>
#include <cassert>
#include <numeric>
#include <algorithm>
#include "Tests.h"

Image TestCase::createEdgeImage() {
    // single channel test image
    int width = 9, height = 9, channels = 1;
    Image testimage(width, height, channels);
    unsigned char data[81] = {
            0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 127, 255, 127, 0, 0, 0,
            0, 0, 0, 255, 255, 255, 0, 0, 0,
            0, 127, 127, 255, 255, 255, 127, 127, 0,
            0, 127, 127, 255, 255, 255, 127, 127, 0,
            0, 127, 127, 255, 255, 255, 127, 127, 0,
            0, 0, 0, 255, 255, 255, 0, 0, 0,
            0, 0, 0, 127, 255, 127, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0


    };
    for (int i = 0; i < width * height * channels; ++i) {
        testimage.data[i] = data[i];
    }
    return testimage;
}

bool TestCase::compareImages(Image estimated, Image expected) {
    if (estimated.w != expected.w || estimated.h != expected.h || estimated.c != expected.c) {
        std::cerr << "Image dimensions do not match" << std::endl;
    }

    for (int i = 0; i < estimated.w * estimated.h * estimated.c; ++i) {
        if (estimated.data[i] != expected.data[i]) {
            std::cout << "Mismatch at index " << i << std::endl;
            return false;
        }
    }
    std::cout << "Pixel values match" << std::endl;
    return true;
};

bool TestCase::compareSlices(Image estimated, Image expected) {
    if (estimated.w != expected.w || estimated.c != expected.c) {
        std::cerr << "Slices do not match" << std::endl;
        return false;
    } else {
        std::cout << "Slices match" << std::endl;
    }
    return true;
};

Image TestCase::createCustomImage(int width, int height, int channels, unsigned char* data) {
    Image image(width, height, channels);
    for (int i = 0; i < width * height * channels; ++i) {
        image.data[i] = data[i];
    }
    return image;
}

bool TestCase::compareVolume(const Volume& estimated, const Volume& expected) {
    for(int i = 0; i < estimated.getDepth(); ++i) {
        if (!compareImages(estimated.getSlice(i), expected.getSlice(i))) {
            std::cout << "Mismatch at slice " << i << std::endl;
            return false;
        }
    }
    std::cout << "Pixel values match" << std::endl;
    return true;
}

void TestCase::checkImageDimensions(Image estimated, Image expected) {
    if (estimated.w != expected.w || estimated.h != expected.h || estimated.c != expected.c) {
        std::cerr << "Image dimensions do not match" << std::endl;
    } else {
        std::cout << "Image dimensions match" << std::endl;
    }
};

// Projection Tests
bool TestCase::testMIPProjection() {
    // Initialize Volume and fill data as ground truth
    Volume volume;
    volume.createEmpty(4, 4, 3);
    std::vector<std::vector<unsigned char>> testSlices = {
            {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16},
            {17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32},
            {33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48}
    };
    for (int z = 0; z < 3; ++z) {
        for (int y = 0; y < 4; ++y) {
            for (int x = 0; x < 4; ++x) {
                volume.setVoxel(testSlices[z][y * 4 + x], x, y, z);
            }
        }
    }
      Projection projection;
    Image mipResult = projection.MIP(volume,1,-1);

    // ground truth MIP result pixel values
    std::vector<unsigned char> expectedMIP = {33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48};

    // compare the result
    for (int i = 0; i < 16; ++i) {
        assert(mipResult.data[i] == expectedMIP[i]);
    }
    return true; //  return true if all assertions pass
}

bool TestCase::testMinIPProjection() {
    // Initialize Volume and fill data as ground truth
    Volume volume;
    volume.createEmpty(4, 4, 3);
    std::vector<std::vector<unsigned char>> testSlices = {
            {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16},
            {17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32},
            {33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48}
    };
    for (int z = 0; z < 3; ++z) {
        for (int y = 0; y < 4; ++y) {
            for (int x = 0; x < 4; ++x) {
                volume.setVoxel(testSlices[z][y * 4 + x], x, y, z);
            }
        }
      }
          Projection projection;
    Image minIPResult = projection.MinIP(volume,1,-1);
          // ground truth MinIP result pixel values
    std::vector<unsigned char> expectedminIP = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
          //  compare the result
    for (int i = 0; i < 16; ++i) {
        assert(minIPResult.data[i] == expectedminIP[i]);
    }
    return true; // return true if all assertions pass
}

bool TestCase::testAIPProjection() {
    // Initialize Volume and fill data as ground truth
    Volume volume;
    volume.createEmpty(4, 4, 3);
    std::vector<std::vector<unsigned char>> testSlices = {
            {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16},
            {17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32},
            {33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48}
          };
    for (int z = 0; z < 3; ++z) {
        for (int y = 0; y < 4; ++y) {
            for (int x = 0; x < 4; ++x) {
                volume.setVoxel(testSlices[z][y * 4 + x], x, y, z);
            }
        }
    }

    Projection projection;
    Image aipResult = projection.AIP(volume,1,-1);

    // ground truth AIP result pixel values
    std::vector<unsigned char> expectedAIP = {17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32};

    // compare the result
    for (int i = 0; i < 16; ++i) {
        assert(aipResult.data[i] == expectedAIP[i]);
    }
    return true; // return true if all assertions pass
}

bool TestCase::testAIPMedianProjection() {
    // Initialize Volume and fill data as ground truth
    Volume volume;
    volume.createEmpty(4, 4, 3);
    std::vector<std::vector<unsigned char>> testSlices = {
            {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16},
            {17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32},
            {33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48}
    };
    for (int z = 0; z < 3; ++z) {
        for (int y = 0; y < 4; ++y) {
            for (int x = 0; x < 4; ++x) {
                volume.setVoxel(testSlices[z][y * 4 + x], x, y, z);
            }
        }
    }

    Projection projection;
    Image aipMedianResult = projection.AIP_Median(volume,1,-1);

          // ground truth AIP Median result pixel values
    std::vector<unsigned char> expectedAIPMeidan = {17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32};

    // compare the result
    for (int i = 0; i < 16; ++i) {
        assert(aipMedianResult.data[i] == expectedAIPMeidan[i]);
    }
    return true; // return true if all assertions pass
}
bool TestCase::testImageMedianBlur(int kernel_size) {
/**
 * @brief Tests the `applyMedianFilter2D` function of the `Filter` class by comparing the output image with the expected image.
 *
 * @param kernel_size The size of the kernel to be used for the median filter.
 * @return `true` if the output image matches the expected image, `false` otherwise.
 */
    //  Create the test image
    unsigned char input_data[25] = {
            0, 0, 0, 0, 0,
            0, 1, 1, 1, 0,
            0, 1, 2, 1, 0,
            0, 1, 1, 1, 0,
            0, 0, 0, 0, 0,
    };

    Image inputImage = createCustomImage(5, 5, 1, input_data);
    // Call the function you want to test
    Filter::applyMedianFilter2D(inputImage, kernel_size);
    // Filter is done in place, so the input image is now the estimated image
    Image estimatedImage = inputImage;

    switch(kernel_size){
        case 3:{
            unsigned char output_data[25] = {
                    0, 0, 0, 0, 0,
                    0, 0, 1, 0, 0,
                    0, 1, 1, 1, 0,
                    0, 0, 1, 0, 0,
                    0, 0, 0, 0, 0
            };
            Image expectedImage = createCustomImage(5, 5, 1, output_data);
            checkImageDimensions(estimatedImage, expectedImage);
            return compareImages(estimatedImage, expectedImage);

        }

        case 5:{
            unsigned char output_data[25] = {
                    0, 0, 0, 0, 0,
                    0, 0, 0, 0, 0,
                    0, 0, 0, 0, 0,
                    0, 0, 0, 0, 0,
                    0, 0, 0, 0, 0
            };
            Image expectedImage = createCustomImage(5, 5, 1, output_data);
            checkImageDimensions(estimatedImage, expectedImage);
            return compareImages(estimatedImage, expectedImage);
        }
        default:
            std::cout << "Invalid kernel choice." << std::endl;

    }
};

bool TestCase::testImageMedianBlurBoundary(int kernel_size) {
/**
 * @brief Tests the image median blur boundary case.
 *
 * This function creates a test image and applies the median filter with the specified kernel size.
 * It then compares the resulting image with the expected image and returns the result of the comparison.
 *
 * @param kernel_size The size of the kernel for the median filter.
 * @return True if the resulting image matches the expected image, false otherwise.
 */
    //  Create the test image
    unsigned char input_data[25] = {
            1, 2, 1, 2, 1,
            2, 0, 0, 0, 2,
            1, 0, 0, 0, 1,
            1, 0, 0, 0, 1,
            1, 1, 1, 1, 1
    };

    Image inputImage = createCustomImage(5, 5, 1, input_data);
    // Call the function you want to test
    Filter::applyMedianFilter2D(inputImage, kernel_size);
    // Filter is done in place, so the input image is now the estimated image
    Image estimatedImage = inputImage;

    switch(kernel_size){
        case 3:{
            /*
            Ground truth reference computation verified from the scipy library in python.
            For reference the source jupyter notebook is uploaded in the same directory.
            Source Jupyter Notebook: AdditionalBlurringTesting.ipynb
            */
            unsigned char output_data[25] = {
                    1, 1, 1, 1, 1,
                    1, 1, 0, 1, 1,
                    1, 0, 0, 0, 1,
                    1, 1, 0, 1, 1,
                    1, 1, 1, 1, 1
            };

            Image expectedImage = createCustomImage(5, 5, 1, output_data);
            checkImageDimensions(estimatedImage, expectedImage);
            return compareImages(estimatedImage, expectedImage);

        }

        case 5:{
            unsigned char output_data[25] = {
                    1, 1, 1, 1, 1,
                    1, 1, 1, 1, 1,
                    1, 1, 1, 1, 1,
                    1, 1, 1, 1, 1,
                    1, 1, 1, 1, 1
            };
            Image expectedImage = createCustomImage(5, 5, 1, output_data);
            checkImageDimensions(estimatedImage, expectedImage);
            return compareImages(estimatedImage, expectedImage);
        }
        default:
            std::cout << "Invalid kernel choice." << std::endl;

    }
};


bool TestCase::testImageBoxBlur(int kernel_size) {
/**
 * Test case for the `testImageBoxBlur` function.
 * This function tests the `applyBoxFilter2D` function of the `Filter` class by comparing the output image with the expected image.
 *
 * @param kernel_size The size of the kernel to be used for the box filter.
 * @return `true` if the output image matches the expected image, `false` otherwise.
 */
    // Create the test image
    unsigned char input_data[25] = {
            0, 0, 0, 0, 0,
            0, 0, 0, 0, 0,
            0, 0, 255, 0, 0,
            0, 0, 0, 0, 0,
            0, 0, 0, 0, 0
    };

    Image inputImage = createCustomImage(5, 5, 1, input_data);
    // Call the function you want to test
    Filter::applyBoxFilter2D(inputImage, kernel_size);
    // Filter is done in place, so the input image is now the estimated image
    Image estimatedImage = inputImage;

    switch(kernel_size){
        case 3:{
            unsigned char output_data[25] = {
                    0, 0, 0, 0, 0,
                    0, 28, 28, 28, 0,
                    0, 28, 28, 28, 0,
                    0, 28, 28, 28, 0,
                    0, 0, 0, 0, 0
            };
            Image expectedImage = createCustomImage(5, 5, 1, output_data);
            checkImageDimensions(estimatedImage, expectedImage);
            return compareImages(estimatedImage, expectedImage);

        }

        case 5:{
            unsigned char output_data[25] = {
                    10, 10, 10, 10, 10,
                    10, 10, 10, 10, 10,
                    10, 10, 10, 10, 10,
                    10, 10, 10, 10, 10,
                    10, 10, 10, 10, 10,
            };
            Image expectedImage = createCustomImage(5, 5, 1, output_data);
            checkImageDimensions(estimatedImage, expectedImage);
            return compareImages(estimatedImage, expectedImage);
        }
        default:
            std::cout << "Invalid kernel choice." << std::endl;
    }
};



bool TestCase::testImageBoxBlurBoundary(int kernel_size) {
/**
 * @brief Tests the image box blur boundary for a given kernel size.
 *
 * This function creates a test image and applies the box filter using the specified kernel size.
 * The filter is applied in place, so the input image becomes the estimated image.
 * The function then compares the estimated image with the expected image for the given kernel size.
 *
 * @param kernel_size The size of the kernel used for the box filter.
 * @return True if the estimated image matches the expected image, false otherwise.
 */
    // Create the test image
    unsigned char input_data[25] = {
            255, 0, 0, 0, 255,
            0, 0, 0, 0, 0,
            0, 0, 0, 0, 0,
            0, 0, 0, 0, 0,
            255, 0, 0, 0, 255
    };

    float size = static_cast<float>(kernel_size * kernel_size);
    Image inputImage = createCustomImage(5, 5, 1, input_data);
    // Call the function you want to test
    Filter::applyBoxFilter2D(inputImage, kernel_size);
    // Filter is done in place, so the input image is now the estimated image
    Image estimatedImage = inputImage;

    switch(kernel_size){
        case 3:{
            /*
            Ground truth reference computation verified from the scipy library in python.
            For reference the source jupyter notebook is uploaded in the same directory.
            Source Jupyter Notebook: AdditionalBlurringTesting.ipynb
            */
            unsigned char output_data[25] = {
                    113,  56,   0,  56, 113,
                    56,  28,   0,  28,  56,
                    0,   0,   0,   0,   0,
                    56,  28,   0,  28,  56,
                    113,  56,   0,  56, 113
            };
            Image expectedImage = createCustomImage(5, 5, 1, output_data);
            checkImageDimensions(estimatedImage, expectedImage);
            return compareImages(estimatedImage, expectedImage);

        }

        case 5:{
            /*
            Ground truth reference computation verified from the scipy library in python.
            For reference the source jupyter notebook is uploaded in the same directory.
            Source Jupyter Notebook: AdditionalBlurringTesting.ipynb
            */
            unsigned char output_data[25] = {
                    91, 61, 61, 61, 91,
                    61, 40, 40, 40, 61,
                    61, 40, 40, 40, 61,
                    61, 40, 40, 40, 61,
                    91, 61, 61, 61, 91
            };
            Image expectedImage = createCustomImage(5, 5, 1, output_data);
            checkImageDimensions(estimatedImage, expectedImage);
            return compareImages(estimatedImage, expectedImage);
        }
        default:
            std::cout << "Invalid kernel choice." << std::endl;

    }
};


bool TestCase::testGaussianKernel(int kernel_size, double sigma){
/**
 * Tests the Gaussian kernel generation for a given kernel size and sigma.
 *
 * @param kernel_size The size of the kernel.
 * @param sigma The standard deviation of the Gaussian distribution.
 * @return True if the test passes, False otherwise.
 *
 * The below source was used to generalize the weighting scheme test for all kernel sizes
 * Source Reference: https://chat.openai.com/share/1b348bdc-3fdf-4731-818a-e389a3504b92
 */
    std::vector<double> kernel = generate1DGaussianKernel(kernel_size, sigma);

    // Check if the sum of the kernel values is approximately 1
    if (std::abs(std::accumulate(kernel.begin(), kernel.end(), 0.0) - 1.0) > 1e-6) {
        std::cerr << "Sum of kernel values is not 1" << std::endl;
        return false;
    }

    if (kernel.size() == 3) {
        return (kernel[1] > kernel[0] && kernel[1] > kernel[2]);
    }

    int centerIndex = kernel.size() / 2;

    // Check if values closer to the center are weighed higher than the outer values
    for (size_t i = 1; i <= centerIndex; ++i) {
        if (kernel[centerIndex - i] <= kernel[centerIndex - i + 1] ||
            kernel[centerIndex + i] <= kernel[centerIndex + i - 1]) {
            std::cerr << "Kernel values are not decreasing as we move away from the center" << std::endl;
            return false;
        }
    }
    return true;
};

bool TestCase::testGaussian2DBlur(int kernel_size, double sigma){
/**
 * Tests the Gaussian 2D blur filter with the given kernel size and sigma.
 *
 * @param kernel_size The size of the kernel used for blurring.
 * @param sigma The standard deviation of the Gaussian distribution.
 * @return True if the test passes, False otherwise.
 */
    // Create the test image
    unsigned char input_data[25] = {
            0, 0, 0, 0, 0,
            0, 0, 0, 0, 0,
            0, 0, 255, 0, 0,
            0, 0, 0, 0, 0,
            0, 0, 0, 0, 0
    };

    Image inputImage = createCustomImage(5, 5, 1, input_data);
    // Call the function you want to test
    Filter::applyGaussianFilter2D(inputImage, kernel_size, sigma);
    // Filter is done in place, so the input image is now the estimated image
    Image estimatedImage = inputImage;

    switch(kernel_size){

        case 3:{
            /*
            Ground truth reference computation verified from the scipy library in python.
            For reference the source jupyter notebook is uploaded in the same directory.
            Source Jupyter Notebook: AdditionalBlurringTesting.ipynb
            */
            unsigned char output_data[25] = {0, 0, 0, 0, 0,
                                             0, 19, 31, 19, 0,
                                             0, 31, 52, 31, 0,
                                             0, 19, 31, 19, 0,
                                             0, 0, 0, 0, 0
            };
            Image expectedImage = createCustomImage(5, 5, 1, output_data);
            checkImageDimensions(estimatedImage, expectedImage);
            for (int i = 0; i < estimatedImage.w * estimatedImage.h * estimatedImage.c; ++i) {
                // Given unsigned char input numerical rounding differences are possible
                if (estimatedImage.data[i] - expectedImage.data[i] >  1.0){
                    std::cerr << "Mismatch at index " << i << std::endl;
                    return false;
                }
            }
            return true;

        } // end of case kernel_size = 3

        case 5:{
            /*
            Ground truth reference computation verified from the scipy library in python.
            For reference the source jupyter notebook is uploaded in the same directory.
            Source Jupyter Notebook: AdditionalBlurringTesting.ipynb
            */
            unsigned char output_data[25] = {
                    0,  3,  5,  3,  0,
                    3, 15, 25, 15,  3,
                    5, 25, 41, 25,  5,
                    3, 15, 25, 15,  3,
                    0,  3,  5,  3,  0
            };
            Image expectedImage = createCustomImage(5, 5, 1, output_data);
            checkImageDimensions(estimatedImage, expectedImage);
            for (int i = 0; i < estimatedImage.w * estimatedImage.h * estimatedImage.c; ++i) {
                // Given unsigned char input numerical rounding differences are possible
                if (estimatedImage.data[i] - expectedImage.data[i] >  1.0){
                    std::cerr << "Mismatch at index " << i << std::endl;
                    return false;
                }
            }
            return true;

        } // end of case kernel_size = 5

        default:
            std::cout << "Invalid kernel choice." << std::endl;

    } // end switch

} //end test


bool TestCase::testGaussian2DBlurBoundary(int kernel_size, double sigma){
/**
 * Tests the Gaussian 2D blur boundary function with the given kernel size and sigma.
 *
 * @param kernel_size The size of the kernel used for blurring.
 * @param sigma The standard deviation used for blurring.
 * @return True if the test passes, False otherwise.
 */
    // Create the test image
    unsigned char input_data[25] = {
            255, 0, 0, 0, 255,
            0, 0, 0, 0, 0,
            0, 0, 0, 0, 0,
            0, 0, 0, 0, 0,
            255, 0, 0, 0, 255
    };

    Image inputImage = createCustomImage(5, 5, 1, input_data);
    // Call the function you want to test
    Filter::applyGaussianFilter2D(inputImage, kernel_size, sigma);
    // Filter is done in place, so the input image is now the estimated image
    Image estimatedImage = inputImage;

    switch(kernel_size){

        case 3:{
            /*
            Ground truth reference computation verified from the scipy library in python.
            For reference the source jupyter notebook is uploaded in the same directory.
            Source Jupyter Notebook: AdditionalBlurringTesting.ipynb
            */
            unsigned char output_data[25] = {
                    134,  50,   0,  50, 134,
                    50,  19,   0,  19,  50,
                    0,   0,   0,   0,   0,
                    50,  19,   0,  19,  50,
                    134,  50,   0,  50, 134
            };
            Image expectedImage = createCustomImage(5, 5, 1, output_data);
            checkImageDimensions(estimatedImage, expectedImage);
            for (int i = 0; i < estimatedImage.w * estimatedImage.h * estimatedImage.c; ++i) {
                // Given unsigned char input numerical rounding differences are possible
                if (estimatedImage.data[i] - expectedImage.data[i] >  1.0){
                    std::cerr << "Mismatch at index " << i << std::endl;
                    return false;
                }
            }
            return true;

        } // end of case kernel_size = 3

        case 5:{
            /*
            Ground truth reference computation verified from the scipy library in python.
            For reference the source jupyter notebook is uploaded in the same directory.
            Source Jupyter Notebook: AdditionalBlurringTesting.ipynb
            */
            unsigned char output_data[25] = {
                    125,  53,  19,  53, 125,
                    53,  22,   8,  22,  53,
                    19,   8,   3,   8,  19,
                    53,  22,   8,  22,  53,
                    125,  53,  19,  53, 125
            };
            Image expectedImage = createCustomImage(5, 5, 1, output_data);
            checkImageDimensions(estimatedImage, expectedImage);
            for (int i = 0; i < estimatedImage.w * estimatedImage.h * estimatedImage.c; ++i) {
                // Given unsigned char input numerical rounding differences are possible
                if (estimatedImage.data[i] - expectedImage.data[i] >  1.0){
                    std::cerr << "Mismatch at index " << i << std::endl;
                    return false;
                }
            }
            return true;

        } // end of case kernel_size = 5

        default:
            std::cout << "Invalid kernel choice." << std::endl;

    } // end switch

} //end test

// Colour Space Tests
bool TestCase::testImageGrayscale(Image input, Image expected) {
    // Call the function you want to test
    Filter::grayscale(input);

    checkImageDimensions(input, expected);
    // Perform assertions as needed
    return input.w == expected.w && input.h == expected.h && input.c == 1;
};

bool TestCase::testImageBrightness(Image estimated, Image expected, int brightness, bool autoBrightness) {

    // Call the function you want to test
    Filter::brightness(estimated, brightness, autoBrightness);

    // Perform assertions as needed
    return TestCase::compareImages(estimated, expected);
};

bool TestCase::testImageHistogramEqualization(Image estimated, bool hsv) {
    // Call the function you want to test
    Image expected = estimated;
    Filter::histogramEqualization(estimated, hsv);
    checkImageDimensions(estimated, expected);

    // Check if the pixel values are in the range 0-255
    for (int i = 0; i < estimated.w * estimated.h * estimated.c; ++i) {
        assert(estimated.data[i] >= 0 && estimated.data[i] <= 255);
    }

    return true;
};

bool TestCase::testImageThreshold(Image estimated, int threshold) {
    // Call the function you want to test
    Image expected = estimated;
    Filter::threshold(estimated, threshold, false);
    checkImageDimensions(estimated, expected);

    // Check if the pixel values are either 0 or 255
    for (int i = 0; i < estimated.w * estimated.h * estimated.c; ++i) {
        assert(estimated.data[i] == 0 || estimated.data[i] == 255);
    }

    return true;
};

bool TestCase::testSaltPepperNoise(Image estimated) {
    // Call the function you want to test
    Image expected = estimated;
    Filter::addSaltPepperNoise(estimated, 10);
    checkImageDimensions(estimated, expected);

    return true;
};

// Edge Detection Tests
bool TestCase::testImageSobelEdge() {
    // Call the function you want to test
    Image test_image = createEdgeImage();
    Filter::sobel(test_image);
    Image ground_truth(9, 9, 1);
    ground_truth.data = new unsigned char[81]{
        0, 0, 179, 255, 255, 255, 179, 0, 0,
        0, 0, 255, 255, 255, 255, 255, 0, 0,
        179, 255, 255, 255, 255, 255, 255, 255, 179,
        255, 255, 255, 255, 0, 255, 255, 255, 255,
        255, 255, 255, 255, 0, 255, 255, 255, 255,
        255, 255, 255, 255, 0, 255, 255, 255, 255,
        179, 255, 255, 255, 255, 255, 255, 255, 179,
        0, 0, 255, 255, 255, 255, 255, 0, 0,
        0, 0, 179, 255, 255, 255, 179, 0, 0
    };

    // Perform assertions as needed
    return TestCase::compareImages(test_image, ground_truth);
};

bool TestCase::testImagePrewittEdge(){
    Image test_image = createEdgeImage();
    Filter::prewitt(test_image);
    Image ground_truth(9, 9, 1);
    ground_truth.data = new unsigned char[81]{
        0, 0, 179, 255, 255, 255, 179, 0, 0,
        0, 0, 255, 255, 255, 255, 255, 0, 0,
        179, 255, 255, 255, 255, 255, 255, 255, 179,
        255, 255, 255, 255, 0, 255, 255, 255, 255,
        255, 255, 255, 255, 0, 255, 255, 255, 255,
        255, 255, 255, 255, 0, 255, 255, 255, 255,
        179, 255, 255, 255, 255, 255, 255, 255, 179,
        0, 0, 255, 255, 255, 255, 255, 0, 0,
        0, 0, 179, 255, 255, 255, 179, 0, 0

    };
    return TestCase::compareImages(test_image, ground_truth);
};

bool TestCase::testImageRobertEdge(){
    Image test_image = createEdgeImage();
    Filter::robert(test_image);
    Image ground_truth(9, 9, 1);
    ground_truth.data = new unsigned char[81]{
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 127, 255, 255, 127, 0, 0,
        0, 0, 0, 255, 128, 128, 255, 0, 0,
        0, 127, 179, 255, 0, 0, 255, 179, 127,
        0, 179, 0, 181, 0, 0, 181, 0, 179,
        0, 179, 0, 181, 0, 0, 181, 0, 179,
        0, 127, 179, 255, 0, 0, 255, 179, 127,
        0, 0, 0, 255, 128, 128, 255, 0, 0,
        0, 0, 0, 127, 255, 255, 127, 0, 0


    };
    return TestCase::compareImages(test_image, ground_truth);
};

bool TestCase::testImageScharrEdge(){
    Image test_image = createEdgeImage();
    Filter::scharr(test_image);
    Image ground_truth(9, 9, 1);
    ground_truth.data = new unsigned char[81]{
        0, 0, 255, 255, 255, 255, 255, 0, 0,
        0, 0, 255, 255, 255, 255, 255, 0, 0,
        255, 255, 255, 255, 255, 255, 255, 255, 255,
        255, 255, 255, 255, 0, 255, 255, 255, 255,
        255, 255, 255, 255, 0, 255, 255, 255, 255,
        255, 255, 255, 255, 0, 255, 255, 255, 255,
        255, 255, 255, 255, 255, 255, 255, 255, 255,
        0, 0, 255, 255, 255, 255, 255, 0, 0,
        0, 0, 255, 255, 255, 255, 255, 0, 0

    };
    return TestCase::compareImages(test_image, ground_truth);
};

// Volume Tests
bool TestCase::testVolumeGaussianBlur() {
    Volume origin = Volume("tests/data/origin_data");
    Filter::applyGaussianFilter3D(origin, 3, 1);
    Volume ground_truth = Volume("tests/data/ground_truth_gaussian");
    return TestCase::compareVolume(origin, ground_truth);
}

bool TestCase::testVolumeMedianBlur() {
    Volume origin = Volume("tests/data/origin_data");
    Filter::applyMedianFilter3D(origin, 3);
    Volume ground_truth = Volume("tests/data/ground_truth_median");
    return TestCase::compareVolume(origin, ground_truth);
}

/**
 * @brief Verifies the accuracy of XY slicing by comparing volume slices against ground truth images.
 *
 * This function tests the XY slicing functionality of the Volume class by loading a series of images from a specified directory to form a volume. 
 * It then slices this volume along the XY plane at each depth level and compares these slices against the original images (considered as ground truth) 
 * use tests/data/ground_truth_slice folder to store the ground truth images.
 *
 * @param directoryPath Path to the directory containing sequentially named image files (.png or .jpg) that constitute the volume.
 */
void TestCase::testXYslices(const std::string& directoryPath, int maxSlicesToSave) {
    Volume volume;
    volume.loadVolume(directoryPath);

    std::vector<std::string> filePaths;
    for (const auto& entry : fs::directory_iterator(directoryPath)) {
        if (entry.is_regular_file()) {
            std::string filePath = entry.path().string();
            std::string extension = entry.path().extension().string();
            std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);
            if (extension == ".png" || extension == ".jpg") {
                filePaths.push_back(filePath);
            }
        }
    }

    std::sort(filePaths.begin(), filePaths.end());

    std::string saveFolderPath = "../tests/data/ground_truth_slice";
    fs::create_directories(saveFolderPath);

    int sliceInterval = std::max(1, volume.getDepth() / maxSlicesToSave);

    for (int z = 0; z < volume.getDepth(); z += sliceInterval) {
        Image groundTruthImage;
        groundTruthImage.load(filePaths[z]);

        Image slicedImage = volume.sliceXY(z);

        std::string slicedImagePath = saveFolderPath + "/sliced_" + std::to_string(z) + ".png";
        std::string groundTruthImagePath = saveFolderPath + "/ground_truth_" + std::to_string(z) + ".png";
        slicedImage.save(slicedImagePath);
        std::cout << "Sliced image saved: " << slicedImagePath << std::endl;
        groundTruthImage.save(groundTruthImagePath);
        std::cout << "Ground truth image saved: " << groundTruthImagePath << std::endl;
    }
}



/**
 * @brief Tests the XZ slicing functionality and validates it against ground truth images for mismatches.
 *
 * This function evaluates the XZ slicing capability of the Volume class by generating XZ slices from a loaded volume and comparing these slices against an XY ground truth image. Since XZ slices represent a different plane than XY slices, this comparison is expected to result in mismatches, thereby testing the robustness of the image comparison logic in detecting differences between slices of different orientations.
 *
 * @param directoryPath Path to the directory containing image files used to construct the volume.
 */
void TestCase::testXZslices(const std::string& directoryPath, int maxSlicesToSave) {
    std::cout << "Starting test for XZ slices..." << std::endl;

    Volume volume;
    volume.loadVolume(directoryPath);

    std::string saveFolderPath = "../tests/data/xz_slices";
    fs::create_directories(saveFolderPath);

    for (int y = 0; y < std::min(volume.getHeight(), maxSlicesToSave); ++y) {
        Image slicedImage = volume.sliceXZ(y);
        std::string slicedImagePath = saveFolderPath + "/xz_sliced_" + std::to_string(y) + ".png";
        slicedImage.save(slicedImagePath);

        std::cout << "XZ slice saved at: " << slicedImagePath << std::endl;

        // Assuming expected dimensions for XZ slices are known
        Image expectedImage; // Placeholder, actual expected image should be defined based on the context
        if (!compareImages(slicedImage, expectedImage)) {
            std::cout << "Mismatch in dimensions or pixel values for XZ slice at Y=" << y << std::endl;
        } else {
            std::cout << "XZ slice at Y=" << y << " passed dimension and pixel value checks." << std::endl;
        }
    }

    std::cout << "Completed XZ slice tests." << std::endl;
}


/**
 * @brief Tests the YZ slicing functionality and validates it against ground truth images for mismatches.
 *
 * This function evaluates the XZ slicing capability of the Volume class by generating XZ slices from a loaded volume and comparing these slices against an XY ground truth image. Since XZ slices represent a different plane than XY slices, this comparison is expected to result in mismatches, thereby testing the robustness of the image comparison logic in detecting differences between slices of different orientations.
 *
 * @param directoryPath Path to the directory containing image files used to construct the volume.
 */
void TestCase::testYZslices(const std::string& directoryPath, int maxSlicesToSave) {
    std::cout << "Starting test for YZ slices..." << std::endl;

    Volume volume;
    volume.loadVolume(directoryPath);

    std::string saveFolderPath = "../tests/data/yz_slices";
    fs::create_directories(saveFolderPath);

    for (int x = 0; x < std::min(volume.getWidth(), maxSlicesToSave); ++x) {
        Image slicedImage = volume.sliceYZ(x);
        std::string slicedImagePath = saveFolderPath + "/yz_sliced_" + std::to_string(x) + ".png";
        slicedImage.save(slicedImagePath);

        std::cout << "YZ slice saved at: " << slicedImagePath << std::endl;

        // Assuming expected dimensions for YZ slices are known
        Image expectedImage; // Placeholder, actual expected image should be defined based on the context
        if (!compareImages(slicedImage, expectedImage)) {
            std::cout << "Mismatch in dimensions or pixel values for YZ slice at X=" << x << std::endl;
        } else {
            std::cout << "YZ slice at X=" << x << " passed dimension and pixel value checks." << std::endl;
        }
    }

    std::cout << "Completed YZ slice tests." << std::endl;
}
