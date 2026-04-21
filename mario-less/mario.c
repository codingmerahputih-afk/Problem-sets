#include <cs50.h>
#include <stdio.h>

void print_row(int bricks);

int main(void)
{
    // Prompt the user for the pyramid's height
    int n, space;
    do
    {
        n = get_int("Tinggi: ");
    }
    while (n < 1);

    // Print a pyramid of that height
    // Dua garis miring adalah komen



    for (int i = 0; i < n; i++)
    {
        // Print row of bricks

        for (space = 0; space < n - i - 1; space++)
        {
            printf(" ");
        }
        print_row(i + 1);
    }
}

void print_row(int bricks)
{

    for (int i = 0; i < bricks; i++)
    {
        printf("#");
    }
    printf("\n");
}

