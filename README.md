# README for Digital Image Processor

## Overview

Our application provides a versatile image and volume processing toolkit, catering to both individual images and volumetric data. Users have the option to apply a wide range of filters to images, including grayscale conversion, brightness adjustment, histogram equalization, thresholding, adding salt and pepper noise, various blurring techniques (median, box, Gaussian), and edge detection (Prewitt, Roberts Cross, Scharr, Sobel). For volumetric data, we offer projection methods like Maximum, Minimum, Mean, and Median Intensity Projections, alongside the capability to extract specific slices in different directions (Axial, Coronal, Sagittal). This toolkit is designed to be straightforward, with an interactive command-line interface guiding users through the process of selecting their input type, applying desired filters or projections, and specifying output parameters.

## Repository Structure

```
root
   ├─ Images: project initial images
   ├─ Outputs: Stores the generated images with 2D and 3D filters
   ├─ Scans: empty folder to store 3D volume image datas
   ├─ build: automation tests for Github
   ├─ mac_exc: executable file for MacOS
   ├─ src: source codes of the whole project
   ├─ tests: testing of functions implemented in src
   └─ win_exc: executable file for Windows
```

## Features Implemented

- **String and Integer Manipulations**: Functions to sort strings, manipulate integers, and reverse the order of characters or digits.
- **Data Structures**: Usage of appropriate STL containers to store and process data efficiently.
- **Furniture Price Calculation**: Implementation of inheritance and virtual functions through a furniture class hierarchy, calculating prices based on material and size.
- **Advanced Algorithms**: Functions to check for prime numbers, calculate metallic means, and more complex mathematical computations.
- **File I/O**: Reading from and writing to files, managing data in various formats, and performing operations like summing values and computing means.

## Installation

To download and run this project, follow these steps:

1. Clone the repository using Git:
   ```
   git clone https://github.com/ese-msc-2023/advanced-programming-group-fibonacci.git
   ```
2. Navigate to the project directory:
   ```
   cd advanced-programming-group-project
   ```


## How to Use

This repository provides a flexible and modular library for edge detection and image filtering, supporting various operators and padding methods. Below are instructions on how to compile and run the software using g++ and CMake.

### Prerequisites

- C++ compiler (g++ or similar)
- CMake (version 3.22 or higher)

### Compilation and Execution

#### Using g++

To compile the program with g++, you need to manually specify the source files and include directories. Here's an example command:

```bash
g++ -o your_program_name src/main.cpp src/Filter.cpp src/Image.cpp src/Projection.cpp src/Volume.cpp src/utils.cpp src/Slice.cpp -Isrc -std=c++17
```

Then, to run your program:

```bash
./your_program_name
```

#### Using CMake

CMake simplifies the build process across different platforms. Follow these steps:

1. Navigate to your project directory.

2. Create a build directory and navigate into it:

   ```bash
   mkdir build && cd build
   ```

3. Run CMake to configure the project and generate a Makefile:

   ```bash
   cmake ..
   ```

4. Compile the project:

   ```bash
   make
   ```

This will create executable files for the main program, performance tests, and unit tests, respectively named `advanced_programming_group_fibonacci`, `performance`, and `tests` within the build directory.

To run the main program:

```bash
./advanced_programming_group_fibonacci
```

For performance testing:

```bash
./performance
```

To execute the tests:

```bash
./tests
```

## User Manual

After compiling the software, you can use the generated executables to apply various image filtering and edge detection algorithms to your images. The main program (`advanced_programming_group_fibonacci`) allows you to run the application with default settings or specific parameters you define. All executable files are in exc folders in this repository, users execute the `tests`, `performance`and `advanced_programming_group_fibonacci`.


Please refer to the specific command-line arguments within the application or source code documentation for more details on how to use the software's features effectively.


### Interactive Menu Structure

When you run the program, you'll be greeted with an initial choice between processing an image or a volume. Here's a breakdown of the interactive menu structure and required inputs:

```
Choose an input type:
1. Image
   ├─ Enter the filepath: [path/to/your/image.png]
   └─ Choose a filter to apply:
       1. Grayscale
       2. Brightness Adjustment
          ├─ Enter the brightness value: [integer]
          └─ Use auto brightness? (1 for Yes/0 for No): [1/0]
       3. Histogram Equalization
          └─ 0 for HSL, 1 for HSV, 2 for Grayscale: [0/1/2]
       4. Threshold
          ├─ Enter the threshold value: [integer]
          └─ 0 for HSL, 1 for HSV, 2 for Grayscale: [0/1/2]
       5. Salt and Pepper Noise
          └─ Enter the percentage of noise: [integer]
       6. Blur (Box, Gaussian, Median)
          ├─ Select type of blur:
          │   1. Median Blur
          │   2. Box Blur
          │   3. Gaussian Blur
          └─ Enter the kernel size: [odd integer >= 3], For option 3 additionally: Enter the sigma value: [numeric value].
       7. Edge Detection (Prewitt, RobertsCross, Scharr, Sobel)
          └─ Enter a sequence of algorithms by their numbers, separated by spaces. Use enter to finish input.

2. Volume
   ├─ Enter the volume filepath: [path/to/your/volume]
   ├─ Do you need to apply a 3D filter?
   │   1. Median Blur
   │   2. Gaussian Blur
   │   3. None
   │   ├─ For options 1 and 2: Enter the kernel size: [odd integer >= 3]
   │   └─ For option 2 additionally: Enter the sigma value: [numeric value]
   └─ Choose an action to apply:
       1. Maximum Intensity Projection
       2. Minimum Intensity Projection
       3. Mean Intensity Projection
       4. Median Intensity Projection
       5. Volume Slicing
          └─ Select slicing direction:
              1. Axial (XY plane)
              2. Coronal (XZ plane)
              3. Sagittal (YZ plane)
                 └─ Enter the coordinate for slice: [integer]
```

### Input Formats
- **Image file path:** Should be a valid path to an image file, typically with extensions like `.png`, `.jpg`, or `.jpeg`.
- **Volume file path:** A path leading to volumetric data, potentially in a specific format recognized by the toolkit.
- **Brightness value:** An integer value. Positive values increase brightness, while negative values decrease it.
- **Threshold value:** An integer representing the cutoff value for pixel intensity during thresholding.
- **Percentage of noise:** An integer from 0 to 100 indicating the amount of salt and pepper noise to add.
- **Kernel size:** An odd integer greater than or equal to 3, specifying the size of the kernel for blurring or edge detection filters.
- **Sigma value (for Gaussian Blur):** A numeric value determining the spread of the blur effect.
- **Slicing direction and coordinate:** For volume slicing, choose the plane and specify the corresponding coordinate.

This structure allows users to navigate through the program's functionalities and understand what inputs are required at each step, facilitating a smoother user experience.

## Contributor

- **[Yibin Gao](https://github.com/edsml-kg23)** - Histogram Equalization, Threshold, Salt and Pepper Noise
- **[Ruihan He](https://github.com/edsml-rh323)** - Edge Detection (Prewitt, RobertsCross, Scharr, Sobel) 
- **[Yu Yin](https://github.com/acse-yy923)** - 3D Projection, 2D gray scale
- **[Wenyi Yang](https://github.com/acse-wy1023)** - 3D blur filters
- **[Sara](https://github.com/acse-sl4623)** - 2D Blur (Box, Gaussian, Median)
- **[Manawi](https://github.com/acse-mk1923)** - Volumne Slicing，2D Brightness Adjustment

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments

- This project was developed as part of the "Advanced Programming C++ - Practicals" for the MSc program. We thank the instructors and teaching assistants for their guidance.
- Special thanks to all group members for their hard work and dedication to the project.

For more information or support, please contact us through GitHub or our university email addresses.

# CT Scans
Download CT Scan datasets here:
https://imperiallondon-my.sharepoint.com/:u:/g/personal/tmd02_ic_ac_uk/EafXMuNsbcNGnRpa8K62FjkBvIKvCswl1riz7hPDHpHdSQ

