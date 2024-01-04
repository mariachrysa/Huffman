/**
 * @file treenode.c
 * @brief Implements data structures and functions for Huffman coding using a MinHeap-based binary tree.
 * 
 * This file provides the structures and operations to build and manipulate a Huffman tree
 * for efficient data compression. The implementation includes structures such as MinHNode and MinHeap, 
 * representing nodes and the MinHeap data structure. Various operations, including node creation, 
 * heap creation, heap maintenance, and tree building, are defined to support the Huffman coding algorithm.
 * Additionally, functions for reading probabilities from a file, generating Huffman codes, and encoding
 * and decoding files are provided. 
 * 
 * @author Maria Chrysanthou 
 * @date 21/11/2023
 * @bug No known bugs
 */
#include "treenode.h"
#define ASCII_SIZE 128       ///< The size of the ASCII character set.

struct MinHNode *newNode(char item, double freq) {
    struct MinHNode *temp = (struct MinHNode *)malloc(sizeof(struct MinHNode));

    temp->left = temp->right = NULL;
    temp->item = item;
    temp->freq = freq;

    return temp;
}

struct MinHeap *createMinH(unsigned capacity) {
    struct MinHeap *minHeap = (struct MinHeap *)malloc(sizeof(struct MinHeap));

    minHeap->size = 0;
    minHeap->capacity = capacity;

    minHeap->array = (struct MinHNode **)malloc(minHeap->capacity * sizeof(struct MinHNode *));
    return minHeap;
}

void swapMinHNode(struct MinHNode **a, struct MinHNode **b) {
    struct MinHNode *t = *a;
    *a = *b;
    *b = t;
}

void minHeapify(struct MinHeap *minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->array[left]->freq < minHeap->array[smallest]->freq)
        smallest = left;

    if (right < minHeap->size && minHeap->array[right]->freq < minHeap->array[smallest]->freq)
        smallest = right;

    if (smallest != idx) {
        swapMinHNode(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

int checkSizeOne(struct MinHeap *minHeap) {
    return (minHeap->size == 1);
}

struct MinHNode *extractMin(struct MinHeap *minHeap) {
    struct MinHNode *temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];

    --minHeap->size;
    minHeapify(minHeap, 0);

    return temp;
}

void insertMinHeap(struct MinHeap *minHeap, struct MinHNode *minHeapNode) {
    ++minHeap->size;
    int i = minHeap->size - 1;

    while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq) {
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    minHeap->array[i] = minHeapNode;
}

void buildMinHeap(struct MinHeap *minHeap) {
    int n = minHeap->size - 1;
    int i;

    for (i = (n - 1) / 2; i >= 0; --i)
        minHeapify(minHeap, i);
}

int isLeaf(struct MinHNode *root) {
    return !(root->left) && !(root->right);
}

struct MinHeap *createAndBuildMinHeap(char item[], double freq[], int size) {
    struct MinHeap *minHeap = createMinH(size);
    int i;
    for (i = 0; i < size; ++i)
        minHeap->array[i] = newNode(item[i], freq[i]);

    minHeap->size = size;
    buildMinHeap(minHeap);

    return minHeap;
}

void readProbabilitiesFromFile(const char *probfile, double *probabilities) {
    FILE *file = fopen(probfile, "r");
    if (file == NULL) {
        perror("Error opening probabilities file");
        exit(EXIT_FAILURE);
    }

    int i;
    // Read probabilities from file
    for (i = 0; i < ASCII_SIZE; ++i) {
        if (fscanf(file, "%lf", &probabilities[i]) != 1) {
            fprintf(stderr, "Error reading probability from file.\n");
            exit(EXIT_FAILURE);
        }
    }
    fclose(file);
}

void HuffmanCodes(char item[], double freq[], int size, FILE *output) {
    struct MinHNode *root = buildHuffmanTree(item, freq, size);

    int arr[ASCII_SIZE], top = 0;

    printHCodes(root, arr, top, output);
}

void printHCodes(struct MinHNode *root, int arr[], int top, FILE *output) {
    if (root->left) {
        arr[top] = 0;
        printHCodes(root->left, arr, top + 1, output);
    }
    if (root->right) {
        arr[top] = 1;
        printHCodes(root->right, arr, top + 1, output);
    }
    if (isLeaf(root)) {
        int asciiValue = (int)root->item;
        if (asciiValue >= 32 && asciiValue <= 126) {
            printArray(arr, top, output, 1);
        } else {
            fprintf(output, "No code\n");
            printf("No code\n");
        }
    }
}

void printArray(int arr[], int n, FILE *output, int printNewline) {
    int i;
    for (i = 0; i < n; ++i){
       //fprintf(output, "%d", arr[i]);
       fprintf(output, "%d",arr[i]);
       if (printNewline)
            printf("%d", arr[i]);
    } 
    if (printNewline) {
        fprintf(output, "\n");
        printf("\n");
    }
}

struct MinHNode *buildHuffmanTree(char item[], double freq[], int size) {
    struct MinHNode *left, *right, *top;
    struct MinHeap *minHeap = createAndBuildMinHeap(item, freq, size);

    while (!checkSizeOne(minHeap)) {
        left = extractMin(minHeap);
        right = extractMin(minHeap);

        top = newNode('$', left->freq + right->freq);

        top->left = left;
        top->right = right;

        insertMinHeap(minHeap, top);
    }
    return extractMin(minHeap);
}

void printHCodeForCharacter(struct MinHNode *root, char target, int arr[], int top, FILE *output, int printNewline) {
    if (root->left) {
        arr[top] = 0;
        printHCodeForCharacter(root->left, target, arr, top + 1, output, printNewline);
    }
    if (root->right) {
        arr[top] = 1;
        printHCodeForCharacter(root->right, target, arr, top + 1, output, printNewline);
    }
    if (isLeaf(root) && root->item == target) {
        printArray(arr, top, output, printNewline);
    }
}

void generateAndPrintHuffmanCodes(const char *probfile, const char *outputFile) {
    double probabilities[ASCII_SIZE];
    readProbabilitiesFromFile(probfile, probabilities);

    // Create an array of characters for all ASCII values
    char ascii_characters[ASCII_SIZE];
    int i;
    for (i = 0; i < ASCII_SIZE; ++i) {
        ascii_characters[i] = (char)i;
    }

    struct MinHNode *root = buildHuffmanTree(ascii_characters, probabilities, ASCII_SIZE);

    FILE *output = fopen(outputFile, "w");
    if (output == NULL) {
        perror("Error opening output file");
        exit(EXIT_FAILURE);
    }

    printf("Huffman codes [32 to 126]:\n");
    for (i = 0; i < ASCII_SIZE; ++i) {
        int asciiValue = (int)ascii_characters[i];

        // Print the Huffman code only if the character is within the specified range
        if (asciiValue >= 32 && asciiValue <= 126) {
            int arr[ASCII_SIZE];
            int top = 0;
            printHCodeForCharacter(root, ascii_characters[i], arr, top, output, 1);
        } else {
            fprintf(output, "No code\n");
        }
    }

    fclose(output);
}

void encodeFile(const char *dataFile, const char *probfile, const char *encodedFile) {
    double probabilities[ASCII_SIZE];
    readProbabilitiesFromFile(probfile, probabilities);

    // Create an array of characters for all ASCII values
    char ascii_characters[ASCII_SIZE];
    int i;
    for (i = 0; i < ASCII_SIZE; ++i) {
        ascii_characters[i] = (char)i;
    }

    struct MinHNode *root = buildHuffmanTree(ascii_characters, probabilities, ASCII_SIZE);

     FILE *input = fopen(dataFile, "r");
    if (input == NULL) {
        perror("Error opening input file");
        exit(EXIT_FAILURE);
    }

    FILE *output = fopen(encodedFile, "w");
    if (output == NULL) {
        perror("Error opening output file");
        exit(EXIT_FAILURE);
    }

    int ch;
    while ((ch = fgetc(input)) != EOF) {
        int arr[ASCII_SIZE];
        int top = 0;
        printHCodeForCharacter(root, (char)ch, arr, top, output, 0);
    }

    fclose(input);
    fclose(output);
}


void decodeFile(const char *encodedFile, const char *probfile, const char *decodedFile) {
    double probabilities[ASCII_SIZE];
    readProbabilitiesFromFile(probfile, probabilities);

    // Create an array of characters for all ASCII values
    char ascii_characters[ASCII_SIZE];
    int i;
    for (i = 0; i < ASCII_SIZE; ++i) {
        ascii_characters[i] = (char)i;
    }

    struct MinHNode *root = buildHuffmanTree(ascii_characters, probabilities, ASCII_SIZE);
    
    FILE *input = fopen(encodedFile, "r");
    if (input == NULL) {
        perror("Error opening input file");
        exit(EXIT_FAILURE);
    }

    FILE *output = fopen(decodedFile, "w");
    if (output == NULL) {
        perror("Error opening output file");
        exit(EXIT_FAILURE);
    }

    struct MinHNode *currentNode = root;
    int bit;

    while ((bit = fgetc(input)) != EOF) {
        if (bit == '0' && currentNode->left) {
            currentNode = currentNode->left;
        } else if (bit == '1' && currentNode->right) {
            currentNode = currentNode->right;
        }

        if (isLeaf(currentNode)) {
            fputc(currentNode->item, output);
            currentNode = root;
        }
    }

    fclose(input);
    fclose(output);
}
