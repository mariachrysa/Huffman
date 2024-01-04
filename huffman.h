/**
 * @file huffman.h
 * @brief Header file which contains declarations for functions and structures related to the Huffman coding program.
 * It includes the main entry point, commandLine, which parses command-line arguments and controls
 * the flow of the program. It also provides the printUsage function for displaying correct command-line usage.
 * Additionally, the HuffmanOptions structure is defined to store input/output filenames and options.
 * 
 * @author Maria Chrysanthou    ID: 1123114
 * @date 18/11/2023
 * @bug No known bugs
 */

#ifndef HUFFMAN_H
#define HUFFMAN_H

#include "treenode.h"
#include "probability.h"
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define ASCII_SIZE 128   ///< The size of the ASCII character set.

/**
 * @brief Structure to store options for the Huffman coding program.
 * The HuffmanOptions structure includes pointers to input/output filenames for various program operations.
 */
typedef struct {
    char *inputFile;      ///< Input file name.
    char *outputFile;     ///< Output file name.
    char *probfile;       ///< Probability file name.
    char *dataFile;       ///< Data file name.
    char *encodedFile;    ///< Encoded file name.
    char *decodedFile;    ///< Decoded file name.
} HuffmanOptions;

/**
 * @brief This function prints the correct command-line usage for the Huffman coding program,
 * guiding the user on how to execute the different available operations.
 */
void printUsage();

/**
 * @brief This function parses command-line arguments, identifies the selected Huffman operation, and calls
 * the appropriate functions to perform tasks such as probability calculation, Huffman code generation,
 * file encoding, and file decoding. It utilizes the HuffmanOptions structure to store input/output filenames.
 *
 * @param argc The number of command-line arguments.
 * @param argv An array of strings representing the command-line arguments.
 * @param options Pointer to the HuffmanOptions structure for storing program options.
 */
void commandLine(int argc, char *argv[], HuffmanOptions *options);

/**
 * @brief The main entry point for the Huffman coding program. The program's flow is
 * controlled by calling the commandLine function.
 *
 * @param argc The number of command-line arguments.
 * @param argv An array of strings representing the command-line arguments.
 * @return An integer indicating the exit status of the program.
 */
int main(int argc, char *argv[]);

#endif // HUFFMAN_H
