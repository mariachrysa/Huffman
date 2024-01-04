/**
 * @file treenode.h
 * @brief Header file which defines structures and functions related to tree nodes and Huffman coding.
 * It includes the definition of the TreeNode structure, representing a node in the Huffman tree,
 * and the MinHNode structure, used for building the Huffman tree with a min-heap approach.
 * Various functions are declared for manipulating these structures, including creating nodes,
 * building the Huffman tree, and generating Huffman codes. Additionally it includes
 * declarations for reading probabilities from a file, encoding files, and decoding files, 
 * printing arrays and generating and printing Huffman codes.
 * 
 * @author Maria Chrysanthou    ID: 1123114
 * @date 21/11/2023
 * @bug No known bugs
 */

#ifndef TREENODE_H
#define TREENODE_H
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Structure which contains information about a node in the Huffman tree,
 * including the character it represents, the associated value or frequency, and pointers
 * to its left and right child nodes.
 */
typedef struct TreeNode {
    char character;             ///< The character represented by the node.
    double value;               ///< The value or frequency associated with the character.
    struct TreeNode *left;      ///< Pointer to the left child node.
    struct TreeNode *right;     ///< Pointer to the right child node.
} TreeNode;

/**
 * @brief Structure representing a node in the min-heap used for building the Huffman tree.
 * 
 * It is used for building the Huffman tree with a min-heap approach.
 * It contains information about an item (character), its frequency, and pointers to its left and right child nodes.
 */
struct MinHNode {
    char item;                  ///< The character or item represented by the node.
    double freq;                ///< The frequency associated with the character or item.
    struct MinHNode *left;      ///< Pointer to the left child node.
    struct MinHNode *right;     ///< Pointer to the right child node.
};

/**
 * @brief Structure representing a min-heap for Huffman tree construction.
 * It includes information about the size, capacity, and an array of MinHNode pointers.
 */
struct MinHeap {
    unsigned size;              ///< The current size of the min-heap.
    unsigned capacity;          ///< The maximum capacity of the min-heap.
    struct MinHNode **array;    ///< Array of MinHNode pointers representing the min-heap.
};

/**
 * @brief This function allocates memory for a new MinHNode, initializes its item and frequency,
 * and sets the left and right child pointers to NULL.
 *
 * @param item The character or item represented by the node.
 * @param freq The frequency associated with the character or item.
 * @return A pointer to the newly created MinHNode.
 */
struct MinHNode *newNode(char item, double freq);

/**
 * @brief This function allocates memory for a new MinHeap, initializes its size and capacity,
 * and allocates memory for the array of MinHNode pointers.
 *
 * @param capacity The maximum capacity of the min-heap.
 * @return A pointer to the newly created MinHeap.
 */
struct MinHeap *createMinH(unsigned capacity);

/**
 * @brief This function swaps the positions of two MinHNode pointers in the min-heap array.
 *
 * @param a Pointer to the first MinHNode.
 * @param b Pointer to the second MinHNode.
 */
void swapMinHNode(struct MinHNode **a, struct MinHNode **b);

/**
 * @brief This function ensures that the min-heap property is maintained at the specified index
 * by recursively adjusting the positions of nodes.
 *
 * @param minHeap Pointer to the MinHeap structure.
 * @param index The index to perform min-heapify on.
 */
void minHeapify(struct MinHeap *minHeap, int index);

/**
 * @brief This function checks if the min-heap has only one node.
 *
 * @param minHeap Pointer to the MinHeap structure.
 * @return 1 if the size is one, 0 otherwise.
 */
int checkSizeOne(struct MinHeap *minHeap);

/**
 * @brief This function extracts the minimum node (root) from the min-heap and adjusts the heap.
 *
 * @param minHeap Pointer to the MinHeap structure.
 * @return A pointer to the extracted MinHNode.
 */
struct MinHNode *extractMin(struct MinHeap *minHeap);

/**
 * @brief This function inserts a new MinHNode into the min-heap and adjusts the heap accordingly.
 *
 * @param minHeap Pointer to the MinHeap structure.
 * @param minHeapNode Pointer to the MinHNode to be inserted.
 */
void insertMinHeap(struct MinHeap *minHeap, struct MinHNode *minHeapNode);

/**
 * @brief This function builds the min-heap from an array of MinHNodes by performing min-heapify
 * operations starting from the last non-leaf node.
 *
 * @param minHeap Pointer to the MinHeap structure.
 */
void buildMinHeap(struct MinHeap *minHeap);

/**
 * @brief This function checks if a given MinHNode is a leaf node (has no left or right child).
 *
 * @param root Pointer to the MinHNode.
 * @return 1 if the node is a leaf, 0 otherwise.
 */
int isLeaf(struct MinHNode *root);

/**
 * @brief This function creates a MinHeap, populates it with nodes created from the provided arrays
 * of items and frequencies, and builds the min-heap.
 *
 * @param item Array of items (characters).
 * @param freq Array of frequencies associated with the items.
 * @param size The size of the arrays.
 * @return A pointer to the created and built MinHeap.
 */
struct MinHeap *createAndBuildMinHeap(char item[], double freq[], int size);

/**
 * @brief This function reads probabilities from a specified file and stores them in the provided array.
 *
 * @param probfile The path to the probability file.
 * @param probabilities Array to store the read probabilities.
 */
void readProbabilitiesFromFile(const char *probfile, double *probabilities);

/**
 * @brief This function prints the Huffman code for a specified character to the provided file.
 *
 * @param root Pointer to the root of the Huffman tree.
 * @param target The character for which the code is generated.
 * @param arr Array to store the generated Huffman code.
 * @param top Current index in the array.
 * @param output File pointer to the output file.
 * @param printNewline Flag to indicate whether to print a newline character.
 */
void printHCodeForCharacter(struct MinHNode *root, char target, int arr[], int top, FILE *output, int printNewline);

/**
 * @brief This function builds the Huffman tree using arrays of items (characters) and their frequencies.
 *
 * @param item Array of items (characters).
 * @param freq Array of frequencies associated with the items.
 * @param size The size of the arrays.
 * @return A pointer to the root of the built Huffman tree.
 */
struct MinHNode *buildHuffmanTree(char item[], double freq[], int size);

/**
 * @brief This function prints Huffman codes for all characters to the provided file.
 *
 * @param root Pointer to the root of the Huffman tree.
 * @param arr Array to store the generated Huffman code.
 * @param top Current index in the array.
 * @param output File pointer to the output file.
 */
void printHCodes(struct MinHNode *root, int arr[], int top, FILE *output);

/**
 * @brief Generate Huffman codes for the given data.
 *
 * @param item Array of characters.
 * @param freq Array of frequencies.
 * @param size Size of the arrays.
 * @param output Output file.
 */
void HuffmanCodes(char item[], double freq[], int size, FILE *output);


/**
 * @brief This function prints an array of integers to the provided file. It also
 * provides an option to print a newline character after the array.
 *
 * @param arr The array of integers to be printed.
 * @param n The size of the array.
 * @param output File pointer to the output file.
 * @param printNewline Flag to indicate whether to print a newline character.
 */
void printArray(int arr[], int n, FILE *output, int printNewline);

/**
 * @brief This function generates and prints Huffman codes for all characters to the
 * provided output file based on the probabilities specified in the given probability file.
 *
 * @param probfile The path to the probability file.
 * @param outputFile The path to the output file.
 */
void generateAndPrintHuffmanCodes(const char *probfile, const char *outputFile);

/**
 * @brief  This function takes the paths to the input data file, probability file, and the desired
 * output encoded file. It calculates probabilities, builds a Huffman tree, and encodes the
 * input file accordingly, writing the result to the specified output file.
 *
 * @param dataFile Path to the input data file.
 * @param probfile Path to the probability file.
 * @param encodedFile Path to the output encoded file.
 */
void encodeFile(const char *dataFile, const char *probfile, const char *encodedFile);

/**
 * @brief This function takes the paths to the input encoded file, probability file, and the desired
 * output decoded file. It calculates probabilities, builds a Huffman tree, and decodes the
 * input file accordingly, writing the result to the specified output file.
 *
 * @param encodedFile Path to the input encoded file.
 * @param probfile Path to the probability file.
 * @param decodedFile Path to the output decoded file.
 */
void decodeFile(const char *encodedFile, const char *probfile, const char *decodedFile);

#endif // TREENODE_H