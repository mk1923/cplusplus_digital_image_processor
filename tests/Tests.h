#ifndef TESTS_H
#define TESTS_H

#include <vector>
#include <iostream>
#include <string>
#include <cmath>
#include <filesystem>
#include "../src/Volume.h"
#include "../src/Image.h"
#include "../src/Filter.h"
#include "../src/utils.h"

namespace fs = std::filesystem;


class TestCase {

public:
    std::string name;

    bool compareImages(Image estimated, Image expected);
    Image createEdgeImage();
    Image createCustomImage(int width, int height, int channels, unsigned char* data);

    bool testImageMedianBlur(int kernel_size);
    bool testImageMedianBlurBoundary(int kernel_size);
    bool testImageBoxBlur(int kernel_size);
    bool testImageBoxBlurBoundary(int kernel_size);
    bool testGaussianKernel(int kernel_size, double sigma);
    bool testGaussian2DBlur(int kernel_size, double sigma);
    bool testGaussian2DBlurBoundary(int kernel_size, double sigma);

    bool testImageBrightness(Image estimated, Image expected, int brightness, bool autoBrightness);
    bool testImageGrayscale(Image input, Image expected);
    void checkImageDimensions(Image estimated, Image expected);
    bool testImageHistogramEqualization(Image estimated, bool hsv);
    bool testImageThreshold(Image estimated, int threshold);
    bool testSaltPepperNoise(Image estimated);

    bool testImageSobelEdge();
    bool testImageRobertEdge();
    bool testImageScharrEdge();
    bool testImagePrewittEdge();

    bool testVolumeGaussianBlur();
    bool testVolumeMedianBlur();

    bool testMIPProjection();
    bool testMinIPProjection();
    bool testAIPProjection();
    bool testAIPMedianProjection();

    bool compareVolume(const Volume &estimated, const Volume &expected);

    // Declaration for the slice tests
    void testXYslices(const std::string& directoryPath, int maxSlicesToSave);
    void testXZslices(const std::string& directoryPath, int maxSlicesToSave);
    void testYZslices(const std::string& directoryPath, int maxSlicesToSave);

    bool compareSlices(Image estimated, Image expected);
};

#endif // TEST_FRAMEWORK_HPP
