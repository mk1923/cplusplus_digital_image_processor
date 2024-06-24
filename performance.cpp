#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <limits>
#include <chrono>
#include <map>

#include "../src/Filter.h"
#include "../src/Image.h"

using namespace std;

int main(){

    int kernelsize;
    Image image;
    string inputPath;
    map <string, map<int,double>> store_duration = {{"median", {}}, {"box", {}}, {"gaussian", {}}};
    std::cout << "\nEnter the filepath: ";
    std::cin >> inputPath;
    image.load(inputPath);
    Filter filter;

    for (kernelsize = 3; kernelsize <10; kernelsize+=2){
        // median
        auto start = std::chrono::high_resolution_clock::now();
        filter.applyMedianFilter2D(image, kernelsize);
        auto end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double>  duration = end - start;
        store_duration["median"][kernelsize] = duration.count();

        // box
        start = std::chrono::high_resolution_clock::now();
        filter.applyBoxFilter2D(image, kernelsize);
        end = std::chrono::high_resolution_clock::now();

        duration = end - start;
        store_duration["box"][kernelsize] = duration.count();

        // gaussian
        start = std::chrono::high_resolution_clock::now();
        filter.applyGaussianFilter2D(image, kernelsize, 2.0);
        end = std::chrono::high_resolution_clock::now();

        // end measuring time
        duration = end - start;
        store_duration["gaussian"][kernelsize] = duration.count();
    }

    // print the duration
    for (auto const &x : store_duration){
        std::cout << x.first << ":\n";
        for (auto const &y : x.second){
            std::cout << y.first << " : " << y.second << "s\n";
        }
    }

    return 0;
}