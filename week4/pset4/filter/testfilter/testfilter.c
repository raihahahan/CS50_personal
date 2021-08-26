#include "helpers.h"

#include <math.h>

#include <stdlib.h>

void image_map(int h, int w, RGBTRIPLE bitmap[h][w], void( * f)(BYTE, BYTE, BYTE, int, int, int, int, RGBTRIPLE[][w]));

void g_scale(BYTE b, BYTE g, BYTE r, int h, int w, int h1, int w1, RGBTRIPLE bitmap[][w1]);
void s_sepia(BYTE b, BYTE g, BYTE r, int h, int w, int h1, int w1, RGBTRIPLE bitmap[][w1]);
void r_reflect(BYTE b, BYTE g, BYTE r, int h, int w, int h1, int w1, RGBTRIPLE bitmap[][w1]);
void b_blur(BYTE b, BYTE g, BYTE r, int h, int w, int h1, int w1, RGBTRIPLE bitmap[][w1]);
void make_copy_array(int height, int width);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width]) {
    image_map(height, width, image, g_scale);
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width]) {
    image_map(height, width, image, s_sepia);
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width]) {
    image_map(height, width, image, r_reflect);
    return;
}

// Blur image
RGBTRIPLE ** copy; // dynamically allocate copy array

void blur(int height, int width, RGBTRIPLE image[height][width]) {
    make_copy_array(height, width);

    image_map(height, width, image, b_blur);

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < height; j++) {
            image[i][j].rgbtBlue = copy[i][j].rgbtBlue;
            image[i][j].rgbtGreen = copy[i][j].rgbtGreen;
            image[i][j].rgbtRed = copy[i][j].rgbtRed;
        }
    }

    free(copy);

    return;
}

// Helper functions for helper functions to create abstraction barrier
void image_map(int h, int w, RGBTRIPLE bitmap[h][w], void( * f)(BYTE, BYTE, BYTE, int, int, int, int, RGBTRIPLE[][w])) {
    /*
    // For each function, we repeat the same steps:
    // 	1. Iterate through height
    // 	2. For each iteration, iterate through width
    // 	3. apply a function for each iteration.
    */

    BYTE blue;
    BYTE green;
    BYTE red;

    int count = 0;

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            blue = bitmap[i][j].rgbtBlue;
            green = bitmap[i][j].rgbtGreen;
            red = bitmap[i][j].rgbtRed;

            ( * f)(blue, green, red, i, j, h, w, bitmap);
        }
    }

    return;
}

void g_scale(BYTE b, BYTE g, BYTE r, int h, int w, int h1, int w1, RGBTRIPLE bitmap[][w1]) {
    /*
    Description:
    - take the average of the r, g, b values to determine the correct shade of grey.
    - apply this to each pixel in the image

    Workings:
    - Iterate through height (vertical height)
    - For each iteration, iterate through width (horizontal row);
    - apply void average(r, g, b) for each iteration.
    - get rgb BYTE value for each colour;
    - take BYTE average = (r + g + b) / 3;
    - image[height][width].colorName = average;
    - color = RGBTRIPLE.colorName;
    */
    double total = (double) r + (double) g + (double) b;
    int average = round(total / 3.0);

    bitmap[h][w].rgbtBlue = average;
    bitmap[h][w].rgbtGreen = average;
    bitmap[h][w].rgbtRed = average;

    return;
}

void s_sepia(BYTE b, BYTE g, BYTE r, int h, int w, int h1, int w1, RGBTRIPLE bitmap[][w1]) {
    /*
    Description:
    - sepiaRed = .393 * originalRed + .769 * originalGreen + .189 * originalBlue
    - sepiaGreen = .349 * originalRed + .686 * originalGreen + .168 * originalBlue
    - sepiaBlue = .272 * originalRed + .534 * originalGreen + .131 * originalBlue
    - round each value to the nearest integer, s.t the greatest number can only be 255, lowest 0.

    Workings:
    - Iterate through height
    - For each iteration, iterate through width;
    - apply void sepia(r, g, b) for each iteration.
    - get rgb BYTE value for each colour;
    - take BYTE sepia = formula above.
    - image[height][width].colorName = sepia;
    */

    int new_b = round(.272 * (double) r + .534 * (double) g + .131 * (double) b);
    int new_g = round(.349 * (double) r + .686 * (double) g + .168 * (double) b);
    int new_r = round(.393 * (double) r + .769 * (double) g + .189 * (double) b);

    bitmap[h][w].rgbtBlue = (new_b > 255) ? 255 : new_b;
    bitmap[h][w].rgbtGreen = (new_g > 255) ? 255 : new_g;
    bitmap[h][w].rgbtRed = (new_r > 255) ? 255 : new_r;
}

void r_reflect(BYTE b, BYTE g, BYTE r, int h, int w, int h1, int w1, RGBTRIPLE bitmap[][w1]) {
    /*
    Description:
    - any pixels on LHS should end up on RHS, vice versa
    - different arrangement of the pixels

    Workings:
    - Iterate through height
    - For each iteration, iterate through width
    - for i to n, swap i with n-i
    */
    if (w >= w1 / 2) return;

    // temporary variables
    int tmp_b = bitmap[h][w].rgbtBlue;
    int tmp_g = bitmap[h][w].rgbtGreen;
    int tmp_r = bitmap[h][w].rgbtRed;

    // swap
    bitmap[h][w].rgbtBlue = bitmap[h][w1 - w - 1].rgbtBlue;
    bitmap[h][w1 - w - 1].rgbtBlue = tmp_b;

    bitmap[h][w].rgbtGreen = bitmap[h][w1 - w - 1].rgbtGreen;
    bitmap[h][w1 - w - 1].rgbtGreen = tmp_g;

    bitmap[h][w].rgbtRed = bitmap[h][w1 - w - 1].rgbtRed;
    bitmap[h][w1 - w - 1].rgbtRed = tmp_r;

    return;
}

void b_blur(BYTE b, BYTE g, BYTE r, int h, int w, int h1, int w1, RGBTRIPLE bitmap[][w1]) {
    /*
    Description:
    - "box blur" technique
    - new value of each pixel would be the average of the values of all the pixels that are within 1 row and column of the original pixel (forming a 3x3 box)

    Workings:
    - Iterate through height
    - For each iteration, iterate through width;
    - apply void blur(r, g, b) for each iteration.
    - get rgb BYTE value for each colour;
    - take BYTE blur = equation below.
    - get RGB values of neighbours and average it.
    - [h][w]
    - [h-1][w]
    - [h-1][w+1]
    - [h][w+1]
    - [h+1][w+1]
    - [h+1][w]
    - [h+1][w-1]
    - [h][w-1]
    - [h-1][w-1]
    - if and of the addresses above are any of these values:
    - 0
    - max h
    - max w
    	- then return 0;
    - image[height][width].colorName = blur;
    */

    double divisor = 9.0;

    if ((h - 1 < 0 && w + 1 == w1) ^ (h + 1 == h1 && w + 1 == w1) || (h - 1 < 0 && w - 1 < 0) || (h + 1 == h1 && w - 1 < 0)) // corners
        divisor -= 5;

    if (w - 1 < 0 ^ w + 1 == w1 ^ h + 1 == h1 ^ h - 1 < 0) // sides
        divisor -= 3;

    // Blue
    int centre_b = bitmap[h][w].rgbtBlue,
        cL_b = (h - 1 < 0) ? 0 : bitmap[h - 1][w].rgbtBlue,
        tL_b = (h - 1 < 0 || w + 1 == w1) ? 0 : bitmap[h - 1][w + 1].rgbtBlue,
        tC_b = (w + 1 == w1) ? 0 : bitmap[h][w + 1].rgbtBlue,
        tR_b = (h + 1 == h1 || w + 1 == w1) ? 0 : bitmap[h + 1][w + 1].rgbtBlue,
        cR_b = (h + 1 == h1) ? 0 : bitmap[h + 1][w].rgbtBlue,
        bR_b = (h + 1 == h1 || w - 1 < 0) ? 0 : bitmap[h + 1][w - 1].rgbtBlue,
        bC_b = (w - 1 < 0) ? 0 : bitmap[h][w - 1].rgbtBlue,
        bL_b = (h - 1 < 0 || w - 1 < 0) ? 0 : bitmap[h - 1][w - 1].rgbtBlue;

    double total_b = (double)(centre_b + cL_b + tL_b + tC_b + tR_b + cR_b + bR_b + bC_b + bL_b);
    int average_b = round(total_b / divisor);

    // Green
    int centre_g = bitmap[h][w].rgbtGreen,
        cL_g = (h - 1 < 0) ? 0 : bitmap[h - 1][w].rgbtGreen,
        tL_g = (h - 1 < 0 || w + 1 == w1) ? 0 : bitmap[h - 1][w + 1].rgbtGreen,
        tC_g = (w + 1 == w1) ? 0 : bitmap[h][w + 1].rgbtGreen,
        tR_g = (h + 1 == h1 || w + 1 == w1) ? 0 : bitmap[h + 1][w + 1].rgbtGreen,
        cR_g = (h + 1 == h1) ? 0 : bitmap[h + 1][w].rgbtGreen,
        bR_g = (h + 1 == h1 || w - 1 < 0) ? 0 : bitmap[h + 1][w - 1].rgbtGreen,
        bC_g = (w - 1 < 0) ? 0 : bitmap[h][w - 1].rgbtGreen,
        bL_g = (h - 1 < 0 || w - 1 < 0) ? 0 : bitmap[h - 1][w - 1].rgbtGreen;

    double total_g = (double)(centre_g + cL_g + tL_g + tC_g + tR_g + cR_g + bR_g + bC_g + bL_g);
    int average_g = round(total_g / divisor);

    // Red
    int centre_r = bitmap[h][w].rgbtRed,
        cL_r = (h - 1 < 0) ? 0 : bitmap[h - 1][w].rgbtRed,
        tL_r = (h - 1 < 0 || w + 1 == w1) ? 0 : bitmap[h - 1][w + 1].rgbtRed,
        tC_r = (w + 1 == w1) ? 0 : bitmap[h][w + 1].rgbtRed,
        tR_r = (h + 1 == h1 || w + 1 == w1) ? 0 : bitmap[h + 1][w + 1].rgbtRed,
        cR_r = (h + 1 == h1) ? 0 : bitmap[h + 1][w].rgbtRed,
        bR_r = (h + 1 == h1 || w - 1 < 0) ? 0 : bitmap[h + 1][w - 1].rgbtRed,
        bC_r = (w - 1 < 0) ? 0 : bitmap[h][w - 1].rgbtRed,
        bL_r = (h - 1 < 0 || w - 1 < 0) ? 0 : bitmap[h - 1][w - 1].rgbtRed;

    double total_r = (double)(centre_r + cL_r + tL_r + tC_r + tR_r + cR_r + bR_r + bC_r + bL_r);
    int average_r = round(total_r / divisor);

    copy[h][w].rgbtBlue = average_b;
    copy[h][w].rgbtGreen = average_g;
    copy[h][w].rgbtRed = average_r;

    return;
}

void make_copy_array(int height, int width) {
    // **copy is a pointer to pointers
    copy = malloc(height * sizeof( * copy)); // allocate memory for height of array

    for (int i = 0; i < height; i++) // for each pointer in the height of array, allocate memory for width
    {
        copy[i] = malloc(width * sizeof(copy[0]));
    }
}