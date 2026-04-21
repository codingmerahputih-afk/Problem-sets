#include "helpers.h"
#include <math.h>
#include <cs50.h>

// relearning what I've learned in cs50 2020

// Convert image to grayscale


void grayscale(int height, int width, RGBTRIPLE image[height][width])
//Hey, compiler… I’m about to define a function named grayscale. This function won’t give anything back when it’s done (that’s why I say void).
//It expects three things when someone calls it: first, an integer called height that tells how many rows the image has; second, an integer called width that tells how many columns the image has; and third, a 2-dimensional grid of pixels called image, where each pixel is stored as an RGBTRIPLE.
//The grid has height rows and width columns. Inside this function, I’ll write instructions to change the pixels of the image into grayscale.
{
    // iterate over the pixel inside image [i][j]
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            RGBTRIPLE pixel = image [i][j];
            int average = round((pixel.rgbtRed + pixel.rgbtGreen + pixel.rgbtBlue)/3.0);
            image [i][j].rgbtRed = image[i][j].rgbtGreen = image[i][j].rgbtBlue = average;
        }
    }

}

int cap(int value)
{
    return value > 255 ? 255 : value;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
//Hey, compiler, define a function called sepia that doesn’t return anything, takes the image’s height and width as integers,
//and also takes a 2D array of RGBTRIPLE pixels called image, which you’ll use to apply the sepia filter to every pixel.

{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
           RGBTRIPLE pixel = image [i][j];

            //Apply formulas to the pixel
           int sepiaRed = round(0.393 * pixel.rgbtRed + 0.769 * pixel.rgbtGreen + 0.189 * pixel.rgbtBlue);
           int sepiaGreen = round(0.349 * pixel.rgbtRed + 0.686 * pixel.rgbtGreen + 0.168 * pixel.rgbtBlue);
           int sepiaBlue = round(0.272 * pixel.rgbtRed + 0.534 * pixel.rgbtGreen + 0.131 * pixel.rgbtBlue);

           image[i][j].rgbtRed = sepiaRed > 255 ?255 : sepiaRed;
           image [i][j].rgbtGreen = sepiaGreen > 255 ? 255 : sepiaGreen;
           image[i][j].rgbtBlue = sepiaBlue > 255 ? 255 : sepiaBlue;
        }
    }
}



// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];

    //Transformations to temp


    for (int i = 0; i < height; i++)
    {
        int curPos = 0;
        for (int j = width-1; j >= 0; j--, curPos++)
        {

            temp[i][curPos] = image[i][j];
        }
    }

    //Copy to final image
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }
}

bool is_valid_pixel(int i, int j, int height, int width)
{
    return i >= 0 && i < height && j >=0 && j < width;
}

RGBTRIPLE get_blurred_pixel(int i, int j, int height, int width, RGBTRIPLE image[height][width])
{
    int redValue, blueValue, greenValue; redValue = blueValue = greenValue = 0;
    int numOfValidPixels = 0;
    for (int di = -1; di <= 1; di++)
    {
        for (int dj = -1; dj <= 1; dj++)
        {
            int new_i = i + di;
            int new_j = j + dj;
            if (is_valid_pixel(new_i, new_j, height, width))
            {
                numOfValidPixels++;
                redValue += image[new_i][new_j].rgbtRed;
                blueValue +=image[new_i][new_j].rgbtBlue;
                greenValue +=image[new_i][new_j].rgbtGreen;
            }
        }
    }
    RGBTRIPLE blurred_pixel;
    blurred_pixel.rgbtRed = round((float) redValue / numOfValidPixels);
    blurred_pixel.rgbtGreen = round((float) greenValue / numOfValidPixels);
    blurred_pixel.rgbtBlue = round((float) blueValue / numOfValidPixels);
    return blurred_pixel;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE new_image[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            new_image[i][j] = get_blurred_pixel(i, j, height, width, image);
        }
    }

    for (int i = 0; i < height; i++)
        for (int j = 0; j <width; j++)
            image[i][j] = new_image[i][j];
}
