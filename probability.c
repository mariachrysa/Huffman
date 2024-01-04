/**
 * @file probability.c
 * @brief Implementation file for probability calculations such as
 * getting the Frequencies, calculating the probabilities and implementing
 * the P command, as well as Input/Output helper functions.
 * 
 * @author Maria Chrysanthou   
 * @date 19/11/2023
 * @bug No known bugs
 */
#include "probability.h"

void initializeProb(ProbabilityData *data) {
    int i;
    for (i = 0; i < ASCII_SIZE; i++) {
        data->frequencies[i] = 0;
    }
}

unsigned int getFreq(FILE *f, ProbabilityData *data) {
    int r, n;

    initializeProb(data);

    /* n will count characters */
    for (n = 0;; n++) {
        /* fgetc() gets an unsigned char, converts to int */
        r = fgetc(f);
        /* no more? get out of loop */
        if (feof(f))
            break;
        /* one more of this character */
        data->frequencies[r]++;
    }
    return n;
}

void calculateProbabilities(FILE *input, FILE *output) {
    ProbabilityData data;
    int totalCharacters = getFreq(input, &data);

    // Check if the file is empty
    if (totalCharacters == 0) {
        fprintf(stderr, "Input file is empty.\n");
        exit(EXIT_FAILURE);
    }

    int i;
    // Calculate probabilities and print to the output file
    for (i = 0; i < ASCII_SIZE; i++) {
        double probability = (double)data.frequencies[i] / totalCharacters;
        fprintf(output, "%.8f\n", probability);
    }

    // Close the files
    fclose(input);
    fclose(output);
}

// Function to read content from a file
FILE *readFile(const char *fileName) {
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        perror("Error opening input file");
        exit(EXIT_FAILURE);
    }
    return file;
}

// Function to write content to a file
FILE *writeFile(const char *fileName) {
    FILE *file = fopen(fileName, "w");
    if (file == NULL) {
        perror("Error opening output file");
        exit(EXIT_FAILURE);
    }
    return file;
}

void implementP(const char *in, const char *out) {

    // Read content from the input file
    FILE *input = readFile(in);
    // Write content to the output file
    FILE *output = writeFile(out);
    calculateProbabilities(input, output);
}



