//huffmann greedy techniques
#include <stdio.h>
#include <stdlib.h>

// Structure for the given characters
struct SYMBOL {
    char alphabet;
    int frequency;
};

// Node structure for the Huffman Tree
struct MinHeapNode {
    char alphabet;
    unsigned frequency;
    struct MinHeapNode *left, *right;
};

// Structure for the Min Priority Queue (Min Heap)
struct MinPriorityQueue {
    unsigned size;
    unsigned capacity;
    struct MinHeapNode** array;
};

// Create a new Huffman tree node
struct MinHeapNode* newNode(char alphabet, unsigned frequency) {
    struct MinHeapNode* temp = (struct MinHeapNode*)malloc(sizeof(struct MinHeapNode));
    temp->left = temp->right = NULL;
    temp->alphabet = alphabet;
    temp->frequency = frequency;
    return temp;
}

// Create a min priority queue of given capacity
struct MinPriorityQueue* createMinPriorityQueue(unsigned capacity) {
    struct MinPriorityQueue* minHeap = (struct MinPriorityQueue*)malloc(sizeof(struct MinPriorityQueue));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (struct MinHeapNode**)malloc(minHeap->capacity * sizeof(struct MinHeapNode*));
    return minHeap;
}

// Swap two nodes
void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b) {
    struct MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

// Standard heapify function
void minHeapify(struct MinPriorityQueue* minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->array[left]->frequency < minHeap->array[smallest]->frequency)
        smallest = left;

    if (right < minHeap->size && minHeap->array[right]->frequency < minHeap->array[smallest]->frequency)
        smallest = right;

    if (smallest != idx) {
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

// Extract the minimum frequency node from heap
struct MinHeapNode* extractMin(struct MinPriorityQueue* minHeap) {
    struct MinHeapNode* temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    --minHeap->size;
    minHeapify(minHeap, 0);
    return temp;
}

// Insert a node into the min priority queue
void insertMinPriorityQueue(struct MinPriorityQueue* minHeap, struct MinHeapNode* minHeapNode) {
    ++minHeap->size;
    int i = minHeap->size - 1;

    while (i && minHeapNode->frequency < minHeap->array[(i - 1) / 2]->frequency) {
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    minHeap->array[i] = minHeapNode;
}

// Build the Huffman tree using the priority queue
struct MinHeapNode* buildHuffmanTree(struct SYMBOL symbols[], int size) {
    struct MinHeapNode *left, *right, *top;
    struct MinPriorityQueue* minHeap = createMinPriorityQueue(size);

    for (int i = 0; i < size; ++i) {
        insertMinPriorityQueue(minHeap, newNode(symbols[i].alphabet, symbols[i].frequency));
    }

    while (minHeap->size != 1) {
        left = extractMin(minHeap);
        right = extractMin(minHeap);

        // '$' is a special character used for internal nodes
        top = newNode('$', left->frequency + right->frequency);
        top->left = left;
        top->right = right;

        insertMinPriorityQueue(minHeap, top);
    }
    return extractMin(minHeap);
}

// Function to print in-order traversal of the Huffman Tree
void printInorder(struct MinHeapNode* root) {
    if (root) {
        printInorder(root->left);
        if (root->alphabet != '$') {
            printf("%c ", root->alphabet);
        }
        printInorder(root->right);
    }
}

int main() {
    int n;

    printf("Enter the number of distinct alphabets: ");
    scanf("%d", &n);

    // Create an array of structures where size = number of alphabets
    struct SYMBOL symbols[n];

    printf("Enter the alphabets:\t");
    for (int i = 0; i < n; i++) {
        scanf(" %c", &symbols[i].alphabet);
    }

    printf("Enter its frequencies:\t");
    for (int i = 0; i < n; i++) {
        scanf("%d", &symbols[i].frequency);
    }

    // Build the tree
    struct MinHeapNode* root = buildHuffmanTree(symbols, n);

    // Output the results
    printf("In-order traversal of the tree (Huffman): ");
    printInorder(root);
    printf("\n");

    return 0;
}
