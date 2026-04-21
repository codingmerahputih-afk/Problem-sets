#include <ctype.h>
#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <string.h>



int main(void)
{
    // Prompt the user for some text
    string text = get_string("Text: ");

    int letters= 0;
    int words = 1;
    int sentences = 0;

    for (int i = 0; i < strlen (text); i++)
    {
        if (isalpha(text[i]))
        {
            letters++;
        }
        else if (text[i] == ' ')
        {
            words++;
        }

        else if (text[i] == '.' || text [i] == '?' || text [i] == '!' || text [i] == ')')
        {
            sentences++;
        }

    }
    float L = (float) letters / (float) words * 100;
    float S = (float) sentences / words * 100;

    int index = round (0.0588 * L - 0.296 * S - 15.8);

    // Count the number of letters, words, and sentences in the text


    // Compute the Coleman-Liau index

    // Print the grade level

    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}


