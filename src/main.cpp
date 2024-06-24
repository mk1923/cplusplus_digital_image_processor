/**
* @file main.cpp
* Group Name: Fibonacci
* Name: Yibin Gao           Github_name: edsml-kg23
* Name: Ruihan He           Github_name: edsml-rh323
* Name: Yu Yin              Github_name: acse-yy923
* Name: Sara Lakatos        Github_name: acse-sl4623
* Name: Manawi Kahie        Github_name: acse-mk1923
* Name: Wenyi Yang          Github_name: acse-wy1023
* 
*/
// main.cpp
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <limits>

#include "Filter.h"
#include "Slice.h"
#include "Projection.h"
#include "Volume.h"
#include "utils.h"
#include "algorithm"

int main() {
    createOutputDirectory("Output");

    std::cout << "Choose an input type:\n"
              << "1. Image\n"
              << "2. Volume\n"
              << "Enter your choice: ";

    int inputType;
    std::cin >> inputType;
    std::string inputPath;
    switch (inputType) {
        case 1: {
            std::cout << "\nEnter the filepath: ";
            std::cin >> inputPath;
            Image image;
            image.load(inputPath);

            std::cout << "\nChoose a filter to apply:\n"
                      << "1. Grayscale\n"
                      << "2. Brightness Adjustment\n"
                      << "3. Histogram Equalization\n"
                      << "4. Threshold\n"
                      << "5. Salt and Pepper Noise\n"
                      << "6. Blur (Box, Gaussian, Median)\n"
                      << "7. Edge Detection (Prewitt, RobertsCross, Scharr, Sobel)\n"
                      << "Enter your choice: ";
            int choice;
            std::cin >> choice;

            int subChoice;
            Filter filter;
            switch (choice) {
                // Grayscale
                case 1: {
                    std::string filename = extractFilename(inputPath);
                    std::string inputFilename = extractFilenameWithoutExtension(filename);
                    filter.grayscale(image);
                    std::string outputPath = "../Output/1-grayscale";
                    createOutputDirectory(outputPath);
                    std::string outputFilename = outputPath + "/" + inputFilename + ".png";
                    image.save(outputFilename);
                    break;
                }
                    // Brightness Adjustment
                case 2: {
                    std::string filename = extractFilename(inputPath);
                    std::string inputFilename = extractFilenameWithoutExtension(filename);
                    std::cout << "Enter the brightness value: ";
                    int brightness;
                    std::cin >> brightness;
                    std::cout << "Do you want to use auto brightness? (1/0): ";
                    bool autoBrightness;
                    std::cin >> autoBrightness;
                    filter.brightness(image, brightness, autoBrightness);
                    std::string outputPath = "../Output/2-brightness";
                    createOutputDirectory(outputPath);
                    std::string outputFilename =
                            outputPath + "/" + inputFilename + "_" + convertNumberToString(brightness) + ".png";
                    image.save(outputFilename);
                    break;
                }
                    // Histogram Equalization
                case 3: {
                    std::string filename = extractFilename(inputPath);
                    std::string inputFilename = extractFilenameWithoutExtension(filename);
                    std::cout << "Applying histogram equalization" << std::endl;
                    std::cout << "0 for HSL, 1 for HSV, 2 for Grayscale: ";
                    int mode;
                    std::cin >> mode;
                    if (mode == 2) {
                        filter.histogramEqualization(image, false);
                    } else {
                        filter.histogramEqualization(image, mode == 1);
                    }
                    std::string modeStr = (mode == 0) ? "_HSL" : (mode == 1) ? "_HSV" : "";
                    std::string outputPath = "../Output/3-histogram";
                    createOutputDirectory(outputPath);
                    std::string outputFilename = outputPath + "/" + inputFilename + modeStr + ".png";
                    image.save(outputFilename);

                    break;
                }

                    // Threshold
                case 4: {
                    std::string filename = extractFilename(inputPath);
                    std::string inputFilename = extractFilenameWithoutExtension(filename);
                    std::cout << "Enter the threshold value: ";
                    int threshold;
                    std::cin >> threshold;
                    int mode;
                    std::cout << "0 for HSL, 1 for HSV, 2 for Grayscale: ";
                    std::cin >> mode;
                    bool isGrayscale = (mode == 2);
                    if (!isGrayscale) {
                        filter.threshold(image, threshold, mode == 1);
                    } else {
                        filter.threshold(image, threshold, false);
                    }
                    std::string modeStr = (mode == 0) ? "_HSL" : (mode == 1) ? "_HSV" : "";
                    std::string outputPath = "../Output/4-threshold";
                    createOutputDirectory(outputPath);
                    std::string outputFilename =
                            outputPath + "/" + inputFilename + modeStr + "_" + std::to_string(threshold) + ".png";
                    image.save(outputFilename);

                    break;
                }
                    // Salt and Pepper Noise
                case 5: {
                    std::string filename = extractFilename(inputPath);
                    std::string inputFilename = extractFilenameWithoutExtension(filename);
                    std::cout << "Enter the percentage of noise: ";
                    int noisePercentage;
                    std::cin >> noisePercentage;
                    filter.addSaltPepperNoise(image, noisePercentage);
                    std::string outputPath = "../Output/5-saltandpepper";
                    createOutputDirectory(outputPath);
                    std::string outputFilename =
                            outputPath + "/" + inputFilename + "_" + std::to_string(noisePercentage) + ".png";
                    image.save(outputFilename);

                    break;
                }
                    // Blur
                case 6: {
                    std::cout << "Select type of blur:\n"
                              << "1. Median Blur\n"
                              << "2. Box Blur\n"
                              << "3. Gaussian Blur\n"
                              << "Enter your choice: ";
                    std::cin >> subChoice;
                    double sigma;
                    Filter filter;
                    // Extracting the filename without extension from the input path
                    std::string filename = extractFilename(inputPath);
                    std::string inputFilename = extractFilenameWithoutExtension(filename);
                    int kernelsize;
                    switch (subChoice) {
                        case 1: {
                            std::cout << "Enter the kernel size: ";
                            std::cin >> kernelsize;

                            // Check if kernel size is an odd greater than 3 integer
                            if (std::cin.fail() || kernelsize < 3 || kernelsize % 2 == 0) {
                            std::cout << "Error: Kernel size must be an integer greater than or equal to 3." << std::endl;
                            return 1;

                            }

                            filter.applyMedianFilter2D(image, kernelsize);
                            std::string outputPath = "../Output/6-blur/median";
                            createOutputDirectory(outputPath);
                            std::string outputFilename =
                                    outputPath + "/" + inputFilename + "_" + std::to_string(kernelsize) + "x" +
                                    std::to_string(kernelsize) + ".png";
                            image.save(outputFilename);
                            break;
                        }
                        case 2: {
                            std::cout << "Enter the kernel size: ";
                            std::cin >> kernelsize;

                            // Check if kernel size is an odd greater than 3 integer
                            if (std::cin.fail() || kernelsize < 3 || kernelsize % 2 == 0) {
                            std::cout << "Error: Kernel size must be an integer greater than or equal to 3." << std::endl;
                            return 1;

                            }
                            filter.applyBoxFilter2D(image, kernelsize);
                            std::string outputPath = "../Output/6-blur/box";
                            createOutputDirectory(outputPath);
                            std::string outputFilename =
                                    outputPath + "/" + inputFilename + "_" + std::to_string(kernelsize) + "x" +
                                    std::to_string(kernelsize) + ".png";
                            image.save(outputFilename);
                            break;
                        }
                        case 3: {
                            std::cout << "Enter the kernel size: ";
                            std::cin >> kernelsize;
                            std::cout << "Enter the sigma value: ";
                            std::cin >> sigma;

                            // Check if kernel size is an odd greater than 3 integer
                            if (std::cin.fail() || kernelsize < 3 || kernelsize % 2 == 0) {
                                std::cout << "Error: Kernel size must be an integer greater than or equal to 3." << std::endl;
                                return 1;

                            }
                            filter.applyGaussianFilter2D(image, kernelsize, sigma);
                            std::string outputPath = "../Output/6-blur/gaussian";
                            createOutputDirectory(outputPath);
                            std::string outputFilename =
                                    outputPath + "/" + inputFilename + "_" + std::to_string(kernelsize) + "x" +
                                    std::to_string(kernelsize) + ".png";
                            image.save(outputFilename);
                            break;
                        }
                        default:
                            std::cout << "Invalid blur choice." << std::endl;
                    }
                    break;
                }
                    // Edge Detection
                case 7: {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                    std::vector<int> algorithmChoices;
                    bool validInput = false;

                    while (!validInput) {
                        std::cout
                                << "Enter a sequence of edge detection algorithms \n 1=Prewitt, \n 2=Roberts Cross, \n 3=Scharr, \n 4=Sobel, \n input should be separated by spaces. Use enter to finish input:";

                        // Read a whole line of input
                        std::string inputLine;
                        std::getline(std::cin, inputLine);
                        std::istringstream iss(inputLine);

                        std::string token;
                        validInput = true; // input is valid until proven otherwise
                        algorithmChoices.clear(); // clear the previous choices

                        while (iss >> token) {
                            if (std::all_of(token.begin(), token.end(), ::isdigit)) {
                                int algInput = std::stoi(token);
                                if (algInput == 0) break; // 0 is used to exit the input loop
                                if (algInput >= 1 && algInput <= 4) {
                                    algorithmChoices.push_back(algInput);
                                } else {
                                    std::cout
                                            << "Invalid input detected. Please enter a valid sequence of numbers from 1 to 4.\n";
                                    validInput = false; // tag input as invalid
                                    break; // quit
                                }
                            } else {
                                std::cout << "Invalid input detected. Please enter numbers only.\n";
                                validInput = false; // tag input as invalid
                                break; // need to reinput
                            }
                        }

                        if (algorithmChoices.empty() && validInput) {
                            std::cout << "No valid filter selected. Storing the greyscaled." << std::endl;
                            break; // quit if no valid input
                        }
                    }

                    // Extract the filename without extension from the input path
                    std::string outputFilename;
                    std::cout << "Enter output file name (without extension): ";
                    std::cin >> outputFilename;
                    outputFilename += ".png";

                    // apply grayscale filter first
                    filter.grayscale(image);

                    // Create the output path
                    std::string outputPath = "../Output/7-edgedetection/";
                    if (algorithmChoices.size() == 1) {
                        switch (algorithmChoices[0]) {
                            case 1:
                                outputPath += "prewitt/";
                                break;
                            case 2:
                                outputPath += "robertsscross/";
                                break;
                            case 3:
                                outputPath += "scharr/";
                                break;
                            case 4:
                                outputPath += "sobel/";
                                break;
                        }
                    } else {
                        outputPath += "sequential/";
                    }

                    // Apply the selected algorithms
                    for (int choice: algorithmChoices) {
                        switch (choice) {
                            case 1:
                                filter.prewitt(image);
                                break;
                            case 2:
                                filter.robert(image);
                                break;
                            case 3:
                                filter.scharr(image);
                                break;
                            case 4:
                                filter.sobel(image);
                                break;
                        }
                    }

                    // create the path and save the image
                    createOutputDirectory(outputPath);
                    image.save(outputPath + outputFilename);

                    break;
                }



                default:
                    std::cout << "Invalid filter choice." << std::endl;
            }


            break;
        }
        case 2: {
            std::cout << "\nEnter the volume filepath: ";
            std::cin >> inputPath;
            Volume volume(inputPath);

            std::cout << "\nDo you need to apply a 3D filter? \n"
                      << "1. Median Blur\n"
                      << "2. Gaussian Blur\n"
                      << "3. None\n";
            int filter_choice;
            std::cin >> filter_choice;
            int kernelSize;

            switch (filter_choice) {
                case 1: {
                    std::cout << "Enter the kernel size: ";
                    std::cin >> kernelSize;

                    // Check if kernel size is an odd greater than 3 integer
                    if (std::cin.fail() || kernelSize < 3 || kernelSize % 2 == 0) {
                        std::cout << "Error: Kernel size must be an integer greater than or equal to 3." << std::endl;
                        return 1;
                    }

                    Filter filter;
                    filter.applyMedianFilter3D(volume, kernelSize);
                    break;
                }
                case 2: {
                    std::cout << "Enter the kernel size: ";
                    std::cin >> kernelSize;

                    // Check if kernel size is an odd greater than 3 integer
                    if (std::cin.fail() || kernelSize < 3 || kernelSize % 2 == 0) {
                        std::cout << "Error: Kernel size must be an integer greater than or equal to 3." << std::endl;
                        return 1;
                    }

                    double sigma;
                    std::cout << "Enter the sigma value: ";
                    std::cin >> sigma;

                    Filter filter;
                    filter.applyGaussianFilter3D(volume, kernelSize, sigma);
                    break;
                }
                case 3: {
                    break;
                }
                default:
                    std::cout << "Invalid choice." << std::endl;
            }

            std::cout << "Choose an action to apply:\n"
                      << "1. Maximum Intensity Projection\n"
                      << "2. Minimum Intensity Projection\n"
                      << "3. Mean Intensity Projection\n"
                      << "4. Median Intensity Projection\n"
                      << "5. Volume Slicing\n"
                      << "Enter your choice: ";
            int choice;
            std::cin >> choice;
            Projection projection;
            switch (choice) {
                case 1: {
                    Image mip = projection.MIP(volume, 1, -1);
                    std::string outputPath = "../Output/confuciusornis";
                    createOutputDirectory(outputPath);
                    std::string outputFilename = outputPath + "/mip-nofilter.png";
                    mip.save(outputFilename);
                    break;
                }

                case 2: {
                    Image minip = projection.MinIP(volume, 1, -1);
                    std::string outputPath = "../Output/confuciusornis";
                    createOutputDirectory(outputPath);
                    std::string outputFilename = outputPath + "/minip-nofilter.png";
                    minip.save(outputFilename);
                    break;
                }

                case 3: {
                    Image aip = projection.AIP(volume, 1, -1);
                    std::string outputPath = "../Output/confuciusornis";
                    createOutputDirectory(outputPath);
                    std::string outputFilename = outputPath + "/aip-nofilter.png";
                    aip.save(outputFilename);
                    break;
                }

                case 4: {
                    Image aipMedian = projection.AIP_Median(volume, 1, -1);
                    std::string outputPath = "Output/confuciusornis";
                    createOutputDirectory(outputPath);
                    std::string outputFilename = outputPath + "/aip-median-nofilter.png";
                    aipMedian.save(outputFilename);
                    break;
                }
                case 5: {
                    std::cout << "Select slicing direction:\n"
                              << "1. Axial (XY plane)\n"
                              << "2. Coronal (XZ plane)\n"
                              << "3. Sagittal (YZ plane)\n"
                              << "Enter your choice: ";
                    int sliceDirection;
                    std::cin >> sliceDirection;

                    int coordinate;
                    Image slice;
                    std::string sliceName;
                    Slicer slicer;
                    switch (sliceDirection) {
                        case 1: { // Axial (XY plane)
                            std::cout << "Enter Z coordinate for XY slice: ";
                            std::cin >> coordinate;
                            slice = slicer.sliceXY(volume, coordinate);
                            sliceName = "slice_xy_z" + std::to_string(coordinate) + ".png";
                            break;
                        }
                        case 2: {// Coronal (XZ plane)
                            std::cout << "Enter Y coordinate for XZ slice: ";
                            std::cin >> coordinate;
                            slice = slicer.sliceXZ(volume, coordinate);
                            sliceName = "slice_xz_y" + std::to_string(coordinate) + ".png";
                            break;
                        }
                        case 3: { // Sagittal (YZ plane)
                            std::cout << "Enter X coordinate for YZ slice: ";
                            std::cin >> coordinate;
                            slice = slicer.sliceYZ(volume, coordinate);
                            sliceName = "slice_yz_x" + std::to_string(coordinate) + ".png";
                            break;
                        }
                        default:
                            std::cerr << "Invalid slicing direction selected." << std::endl;
                            return 1;
                    }


                    std::string filename = extractFilename(inputPath);
                    std::string inputScanName = extractFilenameWithoutExtension(filename);

                    std::string outputPath = "../Output/8-3D/" + inputScanName;
                    createOutputDirectory(outputPath);
                    std::string outputFilename = outputPath + "/" + sliceName;
                    slice.save(outputFilename);
                    break;
                }
                default:
                    std::cout << "Invalid action choice." << std::endl;
            }
            break;
        }
        default:
            std::cout << "Invalid input type." << std::endl;
    }

    return 0;

}


