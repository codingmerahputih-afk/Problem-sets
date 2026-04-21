// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
// there is a variable named HEADER_SIZE of type int, it has a value of 44, and it is a constant, read-only, you can't bloody change it
const int HEADER_SIZE = 44;

//Hey, compiler… here’s what I want:
//Start the main function of my program. I’ll call it main. It should be able to receive some numbers and words that the user types when they run the program from the command line. The first number, argc, tells me how many things the user typed. The second one, argv, is a list (an array) of those things as text strings. So if the user runs ./volume input.wav output.wav 2.0, then argc will be 4, and argv will contain: argv[0] = "./volume", argv[1] = "input.wav", argv[2] = "output.wav", and argv[3] = "2.0".
//In other words, "Hey, compiler, this is the entry point of the program, and I need access to what the user typed in the terminal so I can use those values in my code."

int main(int argc, char *argv[]) {
    // Check command-line arguments
    if (argc != 4) {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    //I, the program, am creating a variable named input. This variable is a pointer, designed to hold the memory address of a FILE struct. This struct acts as my internal manager or control panel that represents the actual input.wav file on the disk. The value assigned to my input pointer is the memory address of this new FILE struct, which is created by the fopen function as a result of opening the file.
    FILE *input = fopen(argv[1], "rb"); // Open in binary mode
    if (input == NULL) {
        printf("Could not open input file.\n");
        return 1;
    }

    //I, the program, now need to create the destination file for the modified audio. I declare a pointer named output and use fopen with the filename from argv[2] in 'write binary' (wb) mode.
    // This asks the operating system to create a new, empty file that I can write data into, and I store the memory address of the new FILE struct in output.
    //If this process fails and output is NULL, I must first perform cleanup by closing the original input file before printing an error message and terminating.

    FILE *output = fopen(argv[2], "wb"); // Open in binary mode
    if (output == NULL) {
        fclose(input); // Close input file before exiting
        printf("Could not open output file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // Copy header from input file to output file

    // “Hey, compiler…Please create me a variable called header. But this isn’t just a single number — it’s an array variable, meaning it’s a row of slots lined up in memory.
   // I want exactly HEADER_SIZE slots in this array (that’s 44). Each slot is of type uint8_t, so each one is a tiny box that holds 1 byte (0–255).
   //So, in total, header is an array variable of 44 bytes, ready to store the .wav file’s header.”

    uint8_t header[HEADER_SIZE];

    //“Hey, compiler, try to read one block of 44 bytes from the file called input and put it into the array variable header, and if you don’t succeed in reading exactly one block then immediately
    //close the input file, close the output file, print the message ‘Error reading header from input file.’ on the screen, and stop the program by returning the error code 1.”

    if (fread(header, HEADER_SIZE, 1, input) != 1) {
        fclose(input);
        fclose(output);
        printf("Error reading header from input file.\n");
        return 1;
    }

    //“Hey, compiler, try to write one block of 44 bytes from the array variable header into the file called output, and if you don’t succeed in writing exactly one block then immediately
    //close the input file, close the output file, print the message ‘Error writing header to output file.’ on the screen, and stop the program by returning the error code 1.”

    if (fwrite(header, HEADER_SIZE, 1, output) != 1) {
        fclose(input);
        fclose(output);
        printf("Error writing header to output file.\n");
        return 1;
    }

    // Read samples from input file and write updated data to output file

    //"Hey, Compiler, please create me a variable named sample. Its type is int16_t, which means it is a signed integer that takes exactly 16 bits (2 bytes) of memory. This way, it can hold both positive and negative numbers in the range roughly from -32,768 to +32,767. I’ll be using this variable to temporarily store one audio sample from the WAV file, since each audio sample in this file format is exactly 16 bits wide."

    int16_t sample;

    //"Hey, compiler… while you are able to successfully read one chunk of 2 bytes (an int16_t sample) from the input file,
    //store it in the variable named sample. Then, take that sample, multiply it by the volume factor, and put the scaled result back into sample. After that, try writing this updated 2-byte sample
    //into the output file. But if that writing ever fails, immediately close both the input and output files, print the message 'Error writing sample to output file.', and stop the program by returning 1.
    //Keep looping and doing this read-scale-write process until you reach the end of the input file."

    while (fread(&sample, sizeof(int16_t), 1, input) == 1) {
        sample = (int16_t)(sample * factor); // Scale the sample
        if (fwrite(&sample, sizeof(int16_t), 1, output) != 1) {
            fclose(input);
            fclose(output);
            printf("Error writing sample to output file.\n");
            return 1;
        }
    }

    // Check for read errors

    // “Hey, compiler… after finishing the while-loop, check if something went wrong while reading from the input file. If you detect a read error (ferror(input) is true),
    //then immediately close both the input and output files, print the message ‘Error reading samples from input file.’ to the screen, and stop the program by returning 1.”


    if (ferror(input)) {
        fclose(input);
        fclose(output);
        printf("Error reading samples from input file.\n");
        return 1;
    }

    // Close files

    //“Hey, compiler… we’re done now, so close the input file, then close the output file, and finally return 0 to signal that the program finished successfully without errors.”

    fclose(input);
    fclose(output);

    return 0;
}

//**“Hey, compiler… when the program starts, make sure the user gave exactly three command-line arguments: an input file name, an output file name, and a volume factor. If not, print a usage message and quit. Then, open the input file in binary read mode, and if that fails, complain and quit. Next, open the output file in binary write mode, and if that fails, close the input file, complain, and quit. After that, take the third argument, turn it into a floating-point number, and call it factor.
//Now, make a box called header big enough to hold 44 bytes. Read 44 bytes from the input file into this header box, and if you can’t, close both files, print ‘Error reading header from input file.’, and quit. Then, write those same 44 bytes into the output file, and if that fails, close both files, print ‘Error writing header to output file.’, and quit.
//Next, create a 2-byte box called sample. While you are able to successfully read one 2-byte sample from the input file into this box, multiply the sample by the volume factor and put the result back into the same box. Then, write that new sample into the output file. But if writing fails, close both files, print ‘Error writing sample to output file.’, and quit. Keep looping like this until you reach the end of the file.
//When the loop is done, check if there was any hidden problem while reading the input file. If yes, then close both files, print ‘Error reading samples from input file.’, and quit.
//Finally, if everything worked fine, close the input file, close the output file, and return 0 to signal that the program finished successfully without errors.”**
