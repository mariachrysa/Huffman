 @mainpage README huffman
 @author Maria Chrysanthou       ID: 1123114
 @section Introduction
 
 The Huffman coding implementation is a command-line program for data compression and decompression. It offers four main functionalities through different command-line options: probability calculation for characters in a sample text file (-p), Huffman code generation based on probabilities (-s), file encoding using Huffman codes (-e), and file decoding (-d). The program employs modular design, with separate files handling probability calculation, tree node structures, encoding and decoding processes. It features a convenient Makefile for compilation, simplifying the build process. Overall, it's a tool for lossless data compression and decompression using the Huffman coding algorithm.

 @section Command-Line Argument Guide
    -p <sample.txt> <probfile.txt>: calculates the probabilities of each ASCII character in a 'sample.txt' file and prints them to 'probfile.txt'

    -s <probfile.txt>: generates Huffman codes for ASCII characters based on their probabilities from 'probfile.txt' which are printed both onto the screen and onto an additional 'codes.txt' file

    -e <probfile.txt> <data.txt> <data.txt.enc>: encodes the contents of 'data.txt' and writes the encoded data to 'data.txt.enc' based on the probabilities in 'probfile.txt'

    -d <probfile.txt> <data.txt.enc> <data.txt.new>: decodes the contents of the encoded file 'data.txt.enc' and writes the decoded data to 'data.txt.new' based on the probabilities in 'probfile.txt'
  

 @section How to Use
 
 To use this program you need to open the terminal on your device and: 
     1. Type in: make all
     2. Run the program with ./huffman followed by the Command-Line Argument Guide.

@section bugs Known bugs

   No Known bugs