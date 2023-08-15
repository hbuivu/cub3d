#include <stdio.h>
#include <stdlib.h>

#define ORIGINAL_WIDTH  64
#define ORIGINAL_HEIGHT 64
#define SCALE_FACTOR    1.7

// Bilinear interpolation function
unsigned char interpolate(unsigned char v1, unsigned char v2, unsigned char v3, unsigned char v4, double x_ratio, double y_ratio) {
    double top = v1 * (1 - x_ratio) + v2 * x_ratio;
    double bottom = v3 * (1 - x_ratio) + v4 * x_ratio;
    return (unsigned char)(top * (1 - y_ratio) + bottom * y_ratio);
}

int main() {
    // Original 64x64 image (just an example)
    unsigned char originalImage[ORIGINAL_HEIGHT][ORIGINAL_WIDTH];

    // Initialize originalImage with your actual image data

    // Calculate new dimensions
    int newWidth = (int)(ORIGINAL_WIDTH * SCALE_FACTOR);
    int newHeight = (int)(ORIGINAL_HEIGHT * SCALE_FACTOR);

    // Create new image
    unsigned char newImage[newHeight][newWidth];

    // Bilinear interpolation
    for (int y = 0; y < newHeight; y++) {
        for (int x = 0; x < newWidth; x++) {
            double origX = (double)x / SCALE_FACTOR;
            double origY = (double)y / SCALE_FACTOR;

            int x1 = (int)origX;
            int x2 = x1 + 1;
            int y1 = (int)origY;
            int y2 = y1 + 1;

            unsigned char q11 = originalImage[y1][x1];
            unsigned char q12 = originalImage[y1][x2];
            unsigned char q21 = originalImage[y2][x1];
            unsigned char q22 = originalImage[y2][x2];

            double x_ratio = origX - x1;
            double y_ratio = origY - y1;

            newImage[y][x] = interpolate(q11, q12, q21, q22, x_ratio, y_ratio);
        }
    }

    // Display the new image
    // Printing or displaying images can vary depending on the platform and libraries used

    return 0;
}