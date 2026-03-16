// Source: https://leetcode.com/problems/number-of-pairs-of-interchangeable-rectangles/   |   Difficulty: Medium
//
// Problem Description:
// You are given n rectangles represented by a 0-indexed 2D integer array rectangles, where rectangles[i] = [widthi, heighti] denotes the width and height of the ith rectangle.
//
// Two rectangles i and j (i < j) are considered interchangeable if they have the same width-to-height ratio. More formally, two rectangles are interchangeable if widthi/heighti == widthj/heightj (using decimal division, not integer division).
//
// Return the number of pairs of interchangeable rectangles in rectangles.
//
// Example:
// Input: rectangles = [[4,8],[3,6],[10,20],[15,30]]
// Output: 6
// Explanation: The following are the interchangeable pairs of rectangles by index (0-indexed):
// - Rectangle 0 with rectangle 1: 4/8 == 3/6.
// - Rectangle 0 with rectangle 2: 4/8 == 10/20.
// - Rectangle 0 with rectangle 3: 4/8 == 15/30.
// - Rectangle 1 with rectangle 2: 3/6 == 10/20.
// - Rectangle 1 with rectangle 3: 3/6 == 15/30.
// - Rectangle 2 with rectangle 3: 10/20 == 15/30.
//
// Constraints:
// n == rectangles.length
// 	1 <= n <= 105
// 	rectangles[i].length == 2
// 	1 <= widthi, heighti <= 105
//

long long interchangeableRectangles(int** rectangles, int rectanglesSize, int* rectanglesColSize) {
    #define HASH_SIZE 100003
    typedef struct HashNode {
        long long key;
        int count;
        struct HashNode* next;
    } HashNode;

    HashNode* hashTable[HASH_SIZE] = {0};
    long long result = 0;

    for (int i = 0; i < rectanglesSize; i++) {
        int width = rectangles[i][0];
        int height = rectangles[i][1];
        long long gcd = 1;

        // Compute GCD
        int a = width, b = height;
        while (b != 0) {
            int temp = b;
            b = a % b;
            a = temp;
        }
        gcd = a;

        long long key = ((long long)(width / gcd) << 32) | (height / gcd);
        int hashIndex = key % HASH_SIZE;

        HashNode* node = hashTable[hashIndex];
        HashNode* prev = NULL;
        while (node != NULL && node->key != key) {
            prev = node;
            node = node->next;
        }

        if (node == NULL) {
            // Create new hash node
            HashNode* newNode = (HashNode*)malloc(sizeof(HashNode));
            newNode->key = key;
            newNode->count = 1;
            newNode->next = NULL;

            if (prev == NULL) {
                hashTable[hashIndex] = newNode;
            } else {
                prev->next = newNode;
            }
        } else {
            // Update existing node
            result += node->count;
            node->count += 1;
        }
    }

    // Free memory
    for (int i = 0; i < HASH_SIZE; i++) {
        HashNode* node = hashTable[i];
        while (node != NULL) {
            HashNode* temp = node;
            node = node->next;
            free(temp);
        }
    }

    return result;      
}
