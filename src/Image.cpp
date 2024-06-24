/**
* @file image.cpp
* Group Name: Fibonacci
* Name: Yibin Gao           Github_name: edsml-kg23
* Name: Ruihan He           Github_name: edsml-rh323
* Name: Yu Yin              Github_name: acse-yy923
* Name: Sara Lakatos        Github_name: acse-sl4623
* Name: Manawi Kahie        Github_name: acse-mk1923
* Name: Wenyi Yang          Github_name: acse-wy1023
* 
*/

// Image.cpp
#include "Image.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstring>

void Image::load(const std::string& path) {
    data = stbi_load(path.c_str(), &w, &h, &c, 0);
}

// create an empty image with the specified width, height, and number of channels
void Image::createEmpty(int width, int height, int channels) {
    w = width;
    h = height;
    c = channels;

    data = new unsigned char[w * h * c]();
}

void Image::save(const std::string& path) const {
    int success = stbi_write_png(path.c_str(), w, h, c, data, 0);
    if (success) {
        std::cout << "Image saved to " << path << std::endl;
    } else {
        std::cout << "Image failed to save" << std::endl;
    }
}

// Constructor definition
Image::Image(int width, int height, int channels) : w(width), h(height), c(channels) {
    data = new unsigned char[w * h * c];
}



void Image::rgbToHsv(float r, float g, float b, float &h, float &s, float &v) {
    float max = std::max({r, g, b}), min = std::min({r, g, b});
    v = max;
    float d = max - min;
    s = max == 0 ? 0 : d / max;

    if (max == min) {
        h = 0; // achromatic
    } else {
        if (max == r) {
            h = (g - b) / d + (g < b ? 6 : 0);
        } else if (max == g) {
            h = (b - r) / d + 2;
        } else if (max == b) {
            h = (r - g) / d + 4;
        }
        h /= 6;
    }
}

void Image::hsvToRgb(float h, float s, float v, int &r, int &g, int &b) {
    int i = int(h * 6);
    float f = h * 6 - i;
    float p = v * (1 - s);
    float q = v * (1 - f * s);
    float t = v * (1 - (1 - f) * s);

    switch (i % 6) {
        case 0: r = v * 255, g = t * 255, b = p * 255; break;
        case 1: r = q * 255, g = v * 255, b = p * 255; break;
        case 2: r = p * 255, g = v * 255, b = t * 255; break;
        case 3: r = p * 255, g = q * 255, b = v * 255; break;
        case 4: r = t * 255, g = p * 255, b = v * 255; break;
        case 5: r = v * 255, g = p * 255, b = q * 255; break;
    }
}

void Image::rgbToHsl(float r, float g, float b, float &h, float &s, float &l) {
    float max = std::max({r, g, b}), min = std::min({r, g, b});
    l = (max + min) / 2;

    if (max == min) {
        h = s = 0; // achromatic
    } else {
        float d = max - min;
        s = l > 0.5 ? d / (2 - max - min) : d / (max + min);
        if (max == r) {
            h = (g - b) / d + (g < b ? 6 : 0);
        } else if (max == g) {
            h = (b - r) / d + 2;
        } else if (max == b) {
            h = (r - g) / d + 4;
        }
        h /= 6;
    }
}

void Image::hslToRgb(float h, float s, float l, int &r, int &g, int &b) {
    auto hue2rgb = [](float p, float q, float t) -> float {
        if(t < 0) t += 1;
        if(t > 1) t -= 1;
        if(t < 1.0/6) return p + (q - p) * 6 * t;
        if(t < 1.0/2) return q;
        if(t < 2.0/3) return p + (q - p) * (2.0/3 - t) * 6;
        return p;
    };

    float q = l < 0.5 ? l * (1 + s) : l + s - l * s;
    float p = 2 * l - q;
    r = static_cast<int>(hue2rgb(p, q, h + 1.0/3) * 255);
    g = static_cast<int>(hue2rgb(p, q, h) * 255);
    b = static_cast<int>(hue2rgb(p, q, h - 1.0/3) * 255);
}



void Image::calculateCdf(const std::vector<int>& histogram, std::vector<int>& cdf) {
    cdf[0] = histogram[0];
    for (int i = 1; i < 256; i++) {
        cdf[i] = cdf[i - 1] + histogram[i];
    }
    // Normalize the CDF
    int cdf_min = *std::find_if(cdf.begin(), cdf.end(), [](int value) { return value > 0; });
    float scale = 255.0f / (cdf.back() - cdf_min);
    for (int i = 0; i < 256; i++) {
        cdf[i] = static_cast<int>((cdf[i] - cdf_min) * scale + 0.5f); // Round off
    }
}


bool Image::isSameAs(const Image& other) const {
    // compare the dimensions and channels
    if (w != other.w || h != other.h || c != other.c) {
        return false; // different dimensions or channels
    }

    // compare the pixel values
    size_t totalPixels = w * h * c;
    for (size_t i = 0; i < totalPixels; ++i) {
        if (data[i] != other.data[i]) {
            return false; // different pixel values
        }
    }

    return true;
}

unsigned char Image::getPixel(int x, int y, int ch) const {
    if (x < 0 || x >= w || y < 0 || y >= h || ch < 0 || ch > c) {
        throw std::out_of_range("Pixel coordinates or channel index are out of the image bounds.");
    }
    return data[(y * w + x) * c + ch];
}

void Image::setPixel(int x, int y, int ch, unsigned char value) {
    if (x < 0 || x >= w || y < 0 || y >= h || ch < 0 || ch > c) {
        throw std::out_of_range("Pixel coordinates or channel index are out of the image bounds.");
    }
    data[(y * w + x) * c + ch] = value;
}
//3d Slicing
Image Image::clone() const {
    Image newImage(w, h, c);
    std::memcpy(newImage.data, data, w * h * c);
    return newImage;
}


Image Image::operator-(const Image& other) const {
    Image result(std::max(w, other.w), std::max(h, other.h), std::max(c, other.c));
    for (int i = 0; i < result.w * result.h * result.c; ++i) {
        int value = static_cast<int>(data[i]) - static_cast<int>(other.data[i]);
        result.data[i] = static_cast<unsigned char>(std::max(0, value));
    }
    return result;
}

void Image::setPixel(int x, int y, unsigned char value) {
    if (x >= 0 && x < w && y >= 0 && y < h) {
        for (int channel = 0; channel < c; ++channel) {
            data[(y * w + x) * c + channel] = value;
        }
    }
}
unsigned char Image::getPixel(int x, int y) const {
    if (x >= 0 && x < w && y >= 0 && y < h) {
        return data[(y * w + x) * c]; // Assuming the caller wants the first channel value
    } else {
        return 0; // Default value for out-of-bounds
    }
}

// Newly added methods
int Image::getWidth() const {
    return w;
}

int Image::getHeight() const {
    return h;
}

