#include "helpers.h"
#include <math.h>
#include <stdlib.h>

void image_map(int h, int w, RGBTRIPLE bitmap[h][w], void(*f)(BYTE, BYTE, BYTE, int, int, int, int, RGBTRIPLE[][w]));

void g_scale(BYTE b, BYTE g, BYTE r, int h, int w, int h1, int w1, RGBTRIPLE bitmap[][w1]);
void r_reflect(BYTE b, BYTE g, BYTE r, int h, int w, int h1, int w1, RGBTRIPLE bitmap[][w1]);
void b_blur(BYTE b, BYTE g, BYTE r, int h, int w, int h1, int w1, RGBTRIPLE bitmap[][w1]);
void e_edges(BYTE b, BYTE g, BYTE r, int h, int w, int h1, int w1, RGBTRIPLE bitmap[][w1]);
void make_copy_array(int height, int width);
void make_copy_array_edge(int height, int width);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    image_map(height, width, image, g_scale);
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    image_map(height, width, image, r_reflect);
    return;
}

// Blur image
RGBTRIPLE **copy; // dynamically allocate copy array

void blur(int height, int width, RGBTRIPLE image[height][width])
{
    make_copy_array(height, width);

    image_map(height, width, image, b_blur);

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < height; j++)
        {
            image[i][j].rgbtBlue = copy[i][j].rgbtBlue;
            image[i][j].rgbtGreen = copy[i][j].rgbtGreen;
            image[i][j].rgbtRed = copy[i][j].rgbtRed;
        }
    }

    free(copy);

    return;
}

// Detect edges
RGBTRIPLE **copy_edge; // dynamically allocate copy array

void edges(int height, int width, RGBTRIPLE image[height][width])
{
    make_copy_array_edge(height, width);

    image_map(height, width, image, e_edges);

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < height; j++)
        {
            image[i][j].rgbtBlue = copy_edge[i][j].rgbtBlue;
            image[i][j].rgbtGreen = copy_edge[i][j].rgbtGreen;
            image[i][j].rgbtRed = copy_edge[i][j].rgbtRed;
        }
    }

    free(copy);

    return;
    return;
}


// Helper functions for helper functions to create abstraction barrier
void image_map(int h, int w, RGBTRIPLE bitmap[h][w], void(*f)(BYTE, BYTE, BYTE, int, int, int, int, RGBTRIPLE[][w]))
{
    /*
    // For each function, we repeat the same steps:
    // 1. Iterate through height
    // 2. For each iteration, iterate through width
    // 3. apply a function for each iteration.
    */

    BYTE blue;
    BYTE green;
    BYTE red;

    int count = 0;

    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            blue = bitmap[i][j].rgbtBlue;
            green = bitmap[i][j].rgbtGreen;
            red = bitmap[i][j].rgbtRed;

            (*f)(blue, green, red, i, j, h, w, bitmap);
        }
    }

    return;
}

void g_scale(BYTE b, BYTE g, BYTE r, int h, int w, int h1, int w1, RGBTRIPLE bitmap[][w1])
{
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

void r_reflect(BYTE b, BYTE g, BYTE r, int h, int w, int h1, int w1, RGBTRIPLE bitmap[][w1])
{
    /*
    Description:
    - any pixels on LHS should end up on RHS, vice versa
    - different arrangement of the pixels

    Workings:
    - Iterate through height
    - For each iteration, iterate through width
    - for i to n, swap i with n-i
    */
    if (w >= w1 / 2)
    {
        return;
    }

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

void b_blur(BYTE b, BYTE g, BYTE r, int h, int w, int h1, int w1, RGBTRIPLE bitmap[][w1])
{
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
    {
        divisor -= 5;
    }


    if (w - 1 < 0 ^ w + 1 == w1 ^ h + 1 == h1 ^ h - 1 < 0) // sides
    {
        divisor -= 3;
    }


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

    // we populate the values to the temporary array called copy first
    // after this function, we will transfer these values into the actual RGBTriple array
    // for each rgb value of r, g and b in copy, we set the three values of average_b, average_g, average_r
    copy[h][w].rgbtBlue = average_b;
    copy[h][w].rgbtGreen = average_g;
    copy[h][w].rgbtRed = average_r;

    return;
}

void make_copy_array(int height, int width)
{
    // **copy is a pointer to pointers
    copy = malloc(height * sizeof(* copy)); // allocate memory for height of array

    for (int i = 0; i < height; i++) // for each pointer in the height of array, allocate memory for width
    {
        copy[i] = malloc(width * sizeof(copy[0]));
    }
}

void e_edges(BYTE b, BYTE g, BYTE r, int h, int w, int h1, int w1, RGBTRIPLE bitmap[][w1])
{
    // Use the procedure similar to blur
    // Divide into Gx and Gy
    // Instead of setting the edge and corner pixels to 0, set them to black
    double divisor = 9.0;

    // if ((h - 1 < 0 && w + 1 == w1) ^ (h + 1 == h1 && w + 1 == w1) || (h - 1 < 0 && w - 1 < 0) || (h + 1 == h1 && w - 1 < 0)) // corners
    // {
    //     divisor -= 5;
    // }


    // if (w - 1 < 0 ^ w + 1 == w1 ^ h + 1 == h1 ^ h - 1 < 0) // sides
    // {
    //     divisor -= 3;
    // }


    // Blue
    // Bx
    int centre_bx = bitmap[h][w].rgbtBlue * 0,
        cL_bx = (h - 1 < 0) ? 0 : bitmap[h - 1][w].rgbtBlue * -2,
        tL_bx = (h - 1 < 0 || w + 1 == w1) ? 0 : bitmap[h - 1][w + 1].rgbtBlue * -1,
        tC_bx = (w + 1 == w1) ? 0 : bitmap[h][w + 1].rgbtBlue * 0,
        tR_bx = (h + 1 == h1 || w + 1 == w1) ? 0 : bitmap[h + 1][w + 1].rgbtBlue * 1,
        cR_bx = (h + 1 == h1) ? 0 : bitmap[h + 1][w].rgbtBlue * 2,
        bR_bx = (h + 1 == h1 || w - 1 < 0) ? 0 : bitmap[h + 1][w - 1].rgbtBlue * 1,
        bC_bx = (w - 1 < 0) ? 0 : bitmap[h][w - 1].rgbtBlue * 0,
        bL_bx = (h - 1 < 0 || w - 1 < 0) ? 0 : bitmap[h - 1][w - 1].rgbtBlue * -1;

    // By
    int centre_by = bitmap[h][w].rgbtBlue * 0,
        cL_by = (h - 1 < 0) ? 0 : bitmap[h - 1][w].rgbtBlue * 0,
        tL_by = (h - 1 < 0 || w + 1 == w1) ? 0 : bitmap[h - 1][w + 1].rgbtBlue * -1,
        tC_by = (w + 1 == w1) ? 0 : bitmap[h][w + 1].rgbtBlue * -2,
        tR_by = (h + 1 == h1 || w + 1 == w1) ? 0 : bitmap[h + 1][w + 1].rgbtBlue * -1,
        cR_by = (h + 1 == h1) ? 0 : bitmap[h + 1][w].rgbtBlue * 0,
        bR_by = (h + 1 == h1 || w - 1 < 0) ? 0 : bitmap[h + 1][w - 1].rgbtBlue * 1,
        bC_by = (w - 1 < 0) ? 0 : bitmap[h][w - 1].rgbtBlue * 2,
        bL_by = (h - 1 < 0 || w - 1 < 0) ? 0 : bitmap[h - 1][w - 1].rgbtBlue * 1;

    double total_bx = (double)(centre_bx + cL_bx + tL_bx + tC_bx + tR_bx + cR_bx + bR_bx + bC_bx + bL_bx);

    double total_by = (double)(centre_by + cL_by + tL_by + tC_by + tR_by + cR_by + bR_by + bC_by + bL_by);

    int total_b = round(sqrt((total_bx * total_bx) + (total_by * total_by))) > 255 ? 255 : round(sqrt((total_bx * total_bx) +
                  (total_by * total_by)));

    // Green
    // Gx
    int centre_gx = bitmap[h][w].rgbtGreen * 0,
        cL_gx = (h - 1 < 0) ? 0 : bitmap[h - 1][w].rgbtGreen * -2,
        tL_gx = (h - 1 < 0 || w + 1 == w1) ? 0 : bitmap[h - 1][w + 1].rgbtGreen * -1,
        tC_gx = (w + 1 == w1) ? 0 : bitmap[h][w + 1].rgbtGreen * 0,
        tR_gx = (h + 1 == h1 || w + 1 == w1) ? 0 : bitmap[h + 1][w + 1].rgbtGreen * 1,
        cR_gx = (h + 1 == h1) ? 0 : bitmap[h + 1][w].rgbtGreen * 2,
        bR_gx = (h + 1 == h1 || w - 1 < 0) ? 0 : bitmap[h + 1][w - 1].rgbtGreen * 1,
        bC_gx = (w - 1 < 0) ? 0 : bitmap[h][w - 1].rgbtGreen * 0,
        bL_gx = (h - 1 < 0 || w - 1 < 0) ? 0 : bitmap[h - 1][w - 1].rgbtGreen * -1;

    // Gy
    int centre_gy = bitmap[h][w].rgbtGreen * 0,
        cL_gy = (h - 1 < 0) ? 0 : bitmap[h - 1][w].rgbtGreen * 0,
        tL_gy = (h - 1 < 0 || w + 1 == w1) ? 0 : bitmap[h - 1][w + 1].rgbtGreen * -1,
        tC_gy = (w + 1 == w1) ? 0 : bitmap[h][w + 1].rgbtGreen * -2,
        tR_gy = (h + 1 == h1 || w + 1 == w1) ? 0 : bitmap[h + 1][w + 1].rgbtGreen * -1,
        cR_gy = (h + 1 == h1) ? 0 : bitmap[h + 1][w].rgbtGreen * 0,
        bR_gy = (h + 1 == h1 || w - 1 < 0) ? 0 : bitmap[h + 1][w - 1].rgbtGreen * 1,
        bC_gy = (w - 1 < 0) ? 0 : bitmap[h][w - 1].rgbtGreen * 2,
        bL_gy = (h - 1 < 0 || w - 1 < 0) ? 0 : bitmap[h - 1][w - 1].rgbtGreen * 1;

    double total_gx = (double)(centre_gx + cL_gx + tL_gx + tC_gx + tR_gx + cR_gx + bR_gx + bC_gx + bL_gx);

    double total_gy = (double)(centre_gy + cL_gy + tL_gy + tC_gy + tR_gy + cR_gy + bR_gy + bC_gy + bL_gy);

    int total_g = round(sqrt((total_gx * total_gx) + (total_gy * total_gy))) > 255 ? 255 : round(sqrt((total_gx * total_gx) +
                  (total_gy * total_gy)));

    // Red
    // Rx
    int centre_rx = bitmap[h][w].rgbtGreen * 0,
        cL_rx = (h - 1 < 0) ? 0 : bitmap[h - 1][w].rgbtRed * -2,
        tL_rx = (h - 1 < 0 || w + 1 == w1) ? 0 : bitmap[h - 1][w + 1].rgbtRed * -1,
        tC_rx = (w + 1 == w1) ? 0 : bitmap[h][w + 1].rgbtRed * 0,
        tR_rx = (h + 1 == h1 || w + 1 == w1) ? 0 : bitmap[h + 1][w + 1].rgbtRed * 1,
        cR_rx = (h + 1 == h1) ? 0 : bitmap[h + 1][w].rgbtRed * 2,
        bR_rx = (h + 1 == h1 || w - 1 < 0) ? 0 : bitmap[h + 1][w - 1].rgbtRed * 1,
        bC_rx = (w - 1 < 0) ? 0 : bitmap[h][w - 1].rgbtRed * 0,
        bL_rx = (h - 1 < 0 || w - 1 < 0) ? 0 : bitmap[h - 1][w - 1].rgbtRed * -1;

    // Ry
    int centre_ry = bitmap[h][w].rgbtRed * 0,
        cL_ry = (h - 1 < 0) ? 0 : bitmap[h - 1][w].rgbtRed * 0,
        tL_ry = (h - 1 < 0 || w + 1 == w1) ? 0 : bitmap[h - 1][w + 1].rgbtRed * -1,
        tC_ry = (w + 1 == w1) ? 0 : bitmap[h][w + 1].rgbtRed * -2,
        tR_ry = (h + 1 == h1 || w + 1 == w1) ? 0 : bitmap[h + 1][w + 1].rgbtRed * -1,
        cR_ry = (h + 1 == h1) ? 0 : bitmap[h + 1][w].rgbtRed * 0,
        bR_ry = (h + 1 == h1 || w - 1 < 0) ? 0 : bitmap[h + 1][w - 1].rgbtRed * 1,
        bC_ry = (w - 1 < 0) ? 0 : bitmap[h][w - 1].rgbtRed * 2,
        bL_ry = (h - 1 < 0 || w - 1 < 0) ? 0 : bitmap[h - 1][w - 1].rgbtRed * 1;

    double total_rx = (double)(centre_rx + cL_rx + tL_rx + tC_rx + tR_rx + cR_rx + bR_rx + bC_rx + bL_rx);

    double total_ry = (double)(centre_ry + cL_ry + tL_ry + tC_ry + tR_ry + cR_ry + bR_ry + bC_ry + bL_ry);

    int total_r = round(sqrt((total_rx * total_rx) + (total_ry * total_ry))) > 255 ? 255 : round(sqrt((total_rx * total_rx) +
                  (total_ry * total_ry)));

    // we populate the values to the temporary array called copy first
    // after this function, we will transfer these values into the actual RGBTriple array
    // for each rgb value of r, g and b in copy, we set the three values of average_b, average_g, average_r
    copy_edge[h][w].rgbtBlue = total_b;
    copy_edge[h][w].rgbtGreen = total_g;
    copy_edge[h][w].rgbtRed = total_r;

    return;
}

void make_copy_array_edge(int height, int width)
{
    // **copy is a pointer to pointers
    copy_edge = malloc(height * sizeof(* copy_edge)); // allocate memory for height of array

    for (int i = 0; i < height; i++) // for each pointer in the height of array, allocate memory for width
    {
        copy_edge[i] = malloc(width * sizeof(copy_edge[0]));
    }
}