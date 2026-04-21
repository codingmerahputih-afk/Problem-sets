#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <cs50.h>
#include <math.h>
#include <string.h>

typedef uint8_t BYTE;

#define BLOCK_SIZE 512
#define FILE_NAME_SIZE 8  // "000.jpg" + '\0' = 8

bool is_start_new_jpeg(BYTE buffer[]);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    // Open input in binary mode
    FILE *infile = fopen(argv[1], "rb");
    if (infile == NULL)
    {
        printf("File not found\n");
        return 1;
    }
    //Hey, compiler… create a variable named infile that will hold the address of a file structure;
    //now try to open the file whose name is given as the first command-line argument (argv[1]) in read-only binary mode ("rb");
    // if the file opens successfully, store its address in infile, but if it can’t be opened, infile will be NULL.

    BYTE buffer[BLOCK_SIZE];
    int file_index = 0;
    bool have_found_first_jpg = false;
    FILE *outfile = NULL;

    // Read 512-byte blocks until fread stops returning 1
    while (fread(buffer, BLOCK_SIZE, 1, infile) == 1)
    {
        if (is_start_new_jpeg(buffer))
        {
            // If we were already writing a JPEG, close it first
            if (have_found_first_jpg && outfile != NULL)
            {
                fclose(outfile);
                outfile = NULL;
            }

            // Create next filename and open new JPEG in binary mode
            char filename[FILE_NAME_SIZE];
            sprintf(filename, "%03i.jpg", file_index++);
            outfile = fopen(filename, "wb");
            if (outfile == NULL)
            {
                fclose(infile);
                return 1;
            }

            have_found_first_jpg = true;
        }

        // If we've started a JPEG, write this 512-byte block to it
        if (have_found_first_jpg && outfile != NULL)
        {
            fwrite(buffer, BLOCK_SIZE, 1, outfile);
        }
    }

    // Close anything left open
    if (outfile != NULL)
    {
        fclose(outfile);
    }
    fclose(infile);

    return 0;
}

bool is_start_new_jpeg(BYTE buffer[])
{
    // JPEG header: FF D8 FF E0..EF (upper 4 bits of 4th byte are 1110)
    return buffer[0] == 0xff &&
           buffer[1] == 0xd8 &&
           buffer[2] == 0xff &&
           (buffer[3] & 0xf0) == 0xe0;
}

//Hey, compiler… take exactly one command-line argument (the forensic image filename) or else print “Usage: ./recover image”
//and quit with status 1; open that file in binary mode or, if it can’t be opened, say “File not found” and quit with status 1;
//set up a 512-byte buffer, a counter starting at 0 for output filenames, a flag telling whether we’ve seen our first JPEG yet,
//and a pointer for the current output file (initially none); then loop reading one 512-byte block at a time—each time you read a block,
//check whether it looks like the start of a JPEG by verifying the signature bytes 0xFF 0xD8 0xFF and that the top four bits
//of the fourth byte are 1110 (i.e., 0xE0–0xEF); if it is a new JPEG and we were already writing one, close the old output first;
//then create a new filename like “000.jpg”, “001.jpg”, … using the counter, open that file for binary writing,
// and mark that we’re now in JPEG-writing mode; if we’re in JPEG-writing mode, write the current 512-byte block to the open JPEG file;
// when the reading loop ends, close any still-open JPEG and close the input file, then return 0 to signal success.
