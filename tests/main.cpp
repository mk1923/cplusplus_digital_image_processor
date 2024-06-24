#include <iostream>
#include "Tests.h"
#include <string>

// Function to generate an image matrix with custom value
Image generateImage(int width, int height, int channels, float value, bool random = false) {
    // Create the Image object
    Image customImage(width, height, channels);

    // If random flag is set, fill the image data with random values
    if (random) {
        for (int i = 0; i < width * height * channels; ++i) {
            customImage.data[i] = rand() % 256;
        }
    } else {
        // Fill the image data with the custom value
        for (int i = 0; i < width * height * channels; ++i) {
            customImage.data[i] = value;
        }
    }

    return customImage;
}

int main(){
    // Prompt the user for the directory path
//    std::cout << "Please provide a directory path to the volume data: ";
    std::string directoryPath;
//    std::getline(std::cin, directoryPath);
    
    TestCase test;

    if (test.testMIPProjection()){
        std::cout << "MIP tests passed!" << std::endl;
    } else {
        std::cout << "MIP tests failed!" << std::endl;
    }

    if (test.testMinIPProjection()){
        std::cout << "minIP tests passed!" << std::endl;
    } else{
        std::cout << "minIP tests failed!" << std::endl;
    }

    if (test.testAIPProjection()){
        std::cout << "AIP tests passed!" << std::endl;
    } else{
        std::cout << "AIP tests failed!" << std::endl;
    }

    if (test.testAIPMedianProjection()){
        std::cout << "AIP_median tests passed!" << std::endl;
    } else{
        std::cout << "AIP_median tests failed!" << std::endl;
    }


    // Blurring Tests
    int kernel_size = 3;
    if(test.testImageMedianBlur(kernel_size)){
        std::cout << "Median Blur test passed with kernel = " <<kernel_size<< std::endl;
    } else {
        std::cout << "Median Blur test failed with kernel = " <<kernel_size<< std::endl;
        exit(1);
    }

    kernel_size = 5;
    if(test.testImageMedianBlur(kernel_size)){
        std::cout << "Median Blur test passed with kernel = " <<kernel_size<< std::endl;
    } else {
        std::cerr << "Median Blur test failed with kernel = " <<kernel_size<< std::endl;
        exit(1);
    }

    kernel_size = 3;
    if(test.testImageMedianBlurBoundary(kernel_size)){
        std::cout << "Median Blur Boundary test passed with kernel = " <<kernel_size<< std::endl;
    } else {
        std::cout << "Median Blur Boundary test failed with kernel = " <<kernel_size<< std::endl;
        exit(1);
    }

    kernel_size = 5;
    if(test.testImageMedianBlurBoundary(kernel_size)){
        std::cout << "Median Blur Boundary test passed with kernel = " <<kernel_size<< std::endl;
    } else {
        std::cerr << "Median Blur Bounadry test failed with kernel = " <<kernel_size<< std::endl;
        exit(1);
    }

    kernel_size = 3;
    if(test.testImageBoxBlur(kernel_size)){
        std::cout << "Box Blur test passed with kernel = " <<kernel_size<< std::endl;
    } else {
        std::cerr << "Box Blur test failed with kernel = " <<kernel_size<< std::endl;
        exit(1);
    }

    kernel_size = 5;
    if(test.testImageBoxBlur(kernel_size)){
        std::cout << "Box Blur test passed with kernel = " <<kernel_size<< std::endl;
    } else {
        std::cerr << "Box Blur test failed with kernel = " <<kernel_size<< std::endl;
        exit(1);
    }

    kernel_size = 3;
    if(test.testImageBoxBlurBoundary(kernel_size)){
        std::cout << "Box Blur Boundary test passed with kernel = " <<kernel_size<< std::endl;
    } else {
        std::cerr << "Box Blur Boundary test failed with kernel = " <<kernel_size<< std::endl;
        exit(1);
    }

    kernel_size = 5;
    if(test.testImageBoxBlurBoundary(kernel_size)){
        std::cout << "Box Blur Boundary test passed with kernel = " <<kernel_size<< std::endl;
    } else {
        std::cerr << "Box Blur Bounadry test failed with kernel = " <<kernel_size<< std::endl;
        exit(1);
    }

    kernel_size = 3;
    if(test.testGaussianKernel(kernel_size, 1.0)){
        std::cout << "Correct 1D Gausssian kernel generated for size = " <<kernel_size<< std::endl;
    } else {
        std::cerr << "Incorrect 1D Gaussian kernel generated for size = " <<kernel_size<< std::endl;
        exit(1);
    }

    kernel_size = 3;
    if(test.testGaussian2DBlur(kernel_size, 1.0)){
        std::cout << "Gaussian Blur test passed with kernel = " <<kernel_size<< std::endl;
    } else {
        std::cerr << "Gaussian Blur test failed with kernel = " <<kernel_size<< std::endl;
        exit(1);
    }

    kernel_size = 5;
    if(test.testGaussian2DBlur(kernel_size, 1.0)){
        std::cout << "Gaussian Blur test passed with kernel = " <<kernel_size<< std::endl;
    } else {
        std::cerr << "Gaussian Blur test failed with kernel = " <<kernel_size<< std::endl;
        exit(1);
    }

    kernel_size = 3;
    if(test.testGaussian2DBlurBoundary(kernel_size, 1.0)){
        std::cout << "Gaussian Blur Boundary test passed with kernel = " <<kernel_size<< std::endl;
    } else {
        std::cerr << "Gaussian Blur Boundary test failed with kernel = " <<kernel_size<< std::endl;
        exit(1);
    }

    kernel_size = 5;
    if(test.testGaussian2DBlurBoundary(kernel_size, 1.0)){
        std::cout << "Gaussian Blur Boundary test passed with kernel = " <<kernel_size<< std::endl;
    } else {
        std::cerr << "Gaussian Blur Boundary test failed with kernel = " <<kernel_size<< std::endl;
        exit(1);
    }

    // Grayscale Tests
    Image input = generateImage(10, 10, 3, 100.0);
    Image expectedGray = generateImage(10, 10, 1, 100.0);
    if (test.testImageGrayscale(input, expectedGray)) {
        std::cout << "Grayscale test passed" << std::endl;
    } else {
        std::cout << "Grayscale test failed" << std::endl;
    }

    Image darkImage = generateImage(10, 10, 3, 0.0);
    Image brightImage = generateImage(10, 10, 3, 100.0);
    if (test.testImageBrightness(darkImage, brightImage, 100, false)) {
        std::cout << "Brightness test passed" << std::endl;
    } else {
        std::cout << "Brightness test failed" << std::endl;
    }

    Image estimatedHistEq = generateImage(10, 10, 3, 100.0, true);
    if (test.testImageHistogramEqualization(estimatedHistEq, false)) {
        std::cout << "Histogram Equalization test passed" << std::endl;
    } else {
        std::cout << "Histogram Equalization test failed" << std::endl;
    }

    Image estimatedThreshold = generateImage(10, 10, 3, 100.0, true);
    if (test.testImageThreshold(estimatedThreshold, 100)) {
        std::cout << "Threshold test passed" << std::endl;
    } else {
        std::cout << "Threshold test failed" << std::endl;
    }

    Image estimatedSaltPepper = generateImage(10, 10, 3, 100.0, true);
    if (test.testSaltPepperNoise(estimatedSaltPepper)) {
        std::cout << "Salt and Pepper Noise test passed" << std::endl;
    } else {
        std::cout << "Salt and Pepper Noise test failed" << std::endl;
    }

    if (test.testImageSobelEdge()) {
        std::cout << "Sobel Edge test passed" << std::endl;
    } else {
        std::cout << "Sobel Edge test failed" << std::endl;
    }

    if (test.testImageRobertEdge()) {
        std::cout << "Robert Edge test passed" << std::endl;
    } else {
        std::cout << "Robert Edge test failed" << std::endl;
    }

    if (test.testImageScharrEdge()) {
        std::cout << "Scharr Edge test passed" << std::endl;
    } else {
        std::cout << "Scharr Edge test failed" << std::endl;
    }

    if (test.testImagePrewittEdge()) {
        std::cout << "Prewitt Edge test passed" << std::endl;
    } else {
        std::cout << "Prewitt Edge test failed" << std::endl;
    }

    if (test.testVolumeGaussianBlur()) {
        std::cout << "Volume Gaussian Blur passed" << std::endl;
    } else {
        std::cout << "Volume Gaussian Blur failed" << std::endl;
    }

    if (test.testVolumeMedianBlur()) {
        std::cout << "Volume Median Blur passed" << std::endl;
    } else {
        std::cout << "Volume Median Blur failed" << std::endl;
    }

//    // Create and load a Volume object
//    Volume volume;
//    volume.loadVolume(directoryPath);
//
//    // Call the new slice and edge case tests with the loaded volume
//    test.testXYslices(directoryPath, 5);
//    test.testXZslices(directoryPath, 1);
//    test.testYZslices(directoryPath, 1);

    return 0;
}
