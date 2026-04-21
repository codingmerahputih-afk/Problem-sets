// volume_refactored.c
#include <stdint.h>  // exact-width types: int16_t, uint8_t
#include <stdio.h>   // FILE, fopen, fread, fwrite, fclose, perror
#include <stdlib.h>  // atof, exit
#include <stdbool.h> // bool
#include <errno.h>   // errno

#define HEADER_SIZE 44

// --- Room 1: Instructions Desk (argument parsing) ---
bool parse_args(int argc, char *argv[], const char **in_path, const char **out_path, float *factor) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s input.wav output.wav factor\n", argv[0]);
        return false;
    }
    *in_path = argv[1];
    *out_path = argv[2];
    *factor = (float) atof(argv[3]);
    return true;
}

// --- Room 2: Door Control (open files safely) ---
bool open_files(const char *in_path, const char *out_path, FILE **in, FILE **out) {
    *in  = fopen(in_path,  "rb");
    if (!*in) {
        perror("Failed to open input");
        return false;
    }
    *out = fopen(out_path, "wb");
    if (!*out) {
        perror("Failed to open output");
        fclose(*in);
        *in = NULL;
        return false;
    }
    return true;
}

// --- Room 3: Label Copier (copy the 44-byte WAV header untouched) ---
bool copy_wav_header(FILE *in, FILE *out) {
    uint8_t header[HEADER_SIZE];
    size_t r = fread(header, 1, HEADER_SIZE, in);
    if (r != HEADER_SIZE) {
        fprintf(stderr, "Failed to read WAV header (got %zu bytes)\n", r);
        return false;
    }
    size_t w = fwrite(header, 1, HEADER_SIZE, out);
    if (w != HEADER_SIZE) {
        fprintf(stderr, "Failed to write WAV header (wrote %zu bytes)\n", w);
        return false;
    }
    return true;
}

// --- Room 4: Volume Studio (scale each 16-bit sample) ---
bool scale_pcm16(FILE *in, FILE *out, float factor) {
    int16_t sample;
    while (true) {
        size_t r = fread(&sample, sizeof(sample), 1, in);
        if (r == 0) {
            // Either EOF or error
            if (feof(in)) return true;   // Finished cleanly
            if (ferror(in)) {
                perror("Read error while scaling samples");
                return false;
            }
        }
        // Scale; cast back to int16_t (may clip if scaled beyond range)
        float temp = (float) sample * factor;
        if (temp >  32767.0f) temp =  32767.0f;
        if (temp < -32768.0f) temp = -32768.0f;
        int16_t out_sample = (int16_t) temp;

        size_t w = fwrite(&out_sample, sizeof(out_sample), 1, out);
        if (w != 1) {
            perror("Write error while scaling samples");
            return false;
        }
    }
}

// --- Room 5: Cleanup Crew (close doors) ---
void close_files(FILE *in, FILE *out) {
    if (in)  fclose(in);
    if (out) fclose(out);
}

// --- The Lobby (main) orchestrates the whole visit ---
int main(int argc, char *argv[]) {
    const char *in_path = NULL, *out_path = NULL;
    float factor = 1.0f;
    FILE *in = NULL, *out = NULL;

    if (!parse_args(argc, argv, &in_path, &out_path, &factor)) {
        return 1;
    }
    if (!open_files(in_path, out_path, &in, &out)) {
        return 1;
    }
    if (!copy_wav_header(in, out)) {
        close_files(in, out);
        return 1;
    }
    if (!scale_pcm16(in, out, factor)) {
        close_files(in, out);
        return 1;
    }

    close_files(in, out);
    return 0;
}
