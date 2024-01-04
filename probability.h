/**
 * @file probability.h
 * @brief Header file containing declarations for probability calculations and file I/O.
 * 
 * @author Maria Chrysanthou 
 * @date 19/11/2023
 * @bug No known bugs
 */

#ifndef PROBABILITY_H
#define PROBABILITY_H
#define ASCII_SIZE 128   ///< The size of the ASCII character set.
#include <stdio.h>
#include <stdlib.h>

/**
 * @struct ProbabilityData
 *
 * @brief Structure which maintains an array to store the frequency of each ASCII character.
 */
typedef struct {
    unsigned int frequencies[ASCII_SIZE]; /**< Array to store character frequencies. */
} ProbabilityData;

/**
 * @brief This function initializes the frequencies array of the ProbabilityData structure.
 *
 * @param data Pointer to the ProbabilityData structure to be initialized.
 */
void initializeProb(ProbabilityData *data);

/**
 * @brief This function reads characters from the provided file, updates the character
 * frequencies in the ProbabilityData structure, and returns the frequency of
 * a specific character.
 *
 * @param f File pointer to the input file.
 * @param data Pointer to the ProbabilityData structure to store character frequencies.
 * @return The frequency of the last character read.
 */
unsigned int getFreq(FILE *f, ProbabilityData *data);

/**
 * @brief This function calculates the probabilities of characters based on their frequencies
 * and writes the results to the specified output file.
 *
 * @param input File pointer to the input file containing character frequencies.
 * @param output File pointer to the output file for writing probabilities.
 */
void calculateProbabilities(FILE *input, FILE *output);

/**
 * @brief This function takes a file name as input, attempts to open the file, and returns
 * a file pointer. It exits the program with an error message if the file cannot be opened.
 *
 * @param fileName The name of the file to be opened.
 * @return File pointer to the opened file.
 */
FILE *readFile(const char *fileName);

/**
 * @brief This function takes a file name as input, attempts to open the file for writing,
 * and returns a file pointer. It exits the program with an error message if the file
 * cannot be opened.
 *
 * @param fileName The name of the file to be opened.
 * @return File pointer to the opened file for writing.
 */
FILE *writeFile(const char *fileName);

/**
 * @brief Implements the 'p' option. It takes the paths to the input data file and the desired output file,
 * calculates character probabilities, and writes the results to the specified output file.
 *
 * @param in Path to the input data file.
 * @param out Path to the output file for writing probabilities.
 */
void implementP(const char *in, const char *out);

#endif // PROBABILITY_H
