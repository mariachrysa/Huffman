/**
 * @file huffman.c 
 * @brief Huffman coding implementation for data compression and decompression.
 *
 * This program provides a command-line interface for performing various Huffman coding operations,
 * including probability calculation, Huffman code generation, file encoding, and file decoding.
 * The main functionality is encapsulated in the functions defined in this file, and the program
 * follows a modularized structure to promote clarity and reusability.
 * 
 * @author Maria Chrysanthou    
 * @date 18/11/2023
 * @bug No known bugs
 */
#include "huffman.h"
#include <float.h>
#include <string.h>

void printUsage() {
    fprintf(stderr, "Usage: ./huffman -p sample.txt probfile.txt\n");
    fprintf(stderr, "       ./huffman -s probfile.txt\n");
    fprintf(stderr, "       ./huffman -e probfile.txt data.txt data.txt.enc\n");
    fprintf(stderr, "       ./huffman -d probfile.txt data.txt.enc data.txt.new\n");
} 

void commandLine(int argc, char *argv[], HuffmanOptions *options) {
     int option;

    if (argc <= 1) {
        fprintf(stderr, "No command line arguments given!\n");
        printUsage();
        exit(EXIT_FAILURE);
    }

    options->inputFile = NULL;  // Initialize inputFile to NULL

    while ((option = getopt(argc, argv, "p:s:e:d:")) != -1) {
        switch (option) {
            case 'p':
                if (optind >= argc) {
                    fprintf(stderr, "Error: Missing output file for -p option.\n");
                    printUsage();
                    exit(EXIT_FAILURE);
                }
                implementP(optarg, argv[optind]);
                optind++;
                break;

            case 's':
                options->probfile = optarg;
                generateAndPrintHuffmanCodes(options->probfile, "codes.txt");
                break;

            case 'e':
                if (optind + 2 > argc) {  
                    fprintf(stderr, "Error: Missing input or output file for -e option.\n");
                    printUsage();
                    exit(EXIT_FAILURE);
                }
                options->probfile = optarg;
                options->dataFile = argv[optind++];
                options->encodedFile = argv[optind++];
                encodeFile(options->dataFile, options->probfile, options->encodedFile);
                break;

            case 'd':
                if (optind + 2 > argc) {
                    fprintf(stderr, "Error: Missing input or output file for -d option.\n");
                    printUsage();
                    exit(EXIT_FAILURE);
                }
                options->probfile = optarg;
                options->encodedFile = argv[optind++];
                options->decodedFile = argv[optind++];
                decodeFile(options->encodedFile, options->probfile, options->decodedFile);
                break;

            default:
                printUsage();
                exit(EXIT_FAILURE);
        }
    }

    if (options->inputFile == NULL && options->probfile == NULL) {
        fprintf(stderr, "Error: No input or probability file specified.\n");
        printUsage();
        exit(EXIT_FAILURE);
    }

}

int main(int argc, char *argv[]) {
    
    HuffmanOptions options;
    commandLine(argc, argv, &options);

    return 0;
}

