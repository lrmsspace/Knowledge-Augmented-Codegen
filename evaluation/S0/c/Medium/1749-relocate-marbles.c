// Source: https://leetcode.com/problems/relocate-marbles/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed integer array nums representing the initial positions of some marbles. You are also given two 0-indexed integer arrays moveFrom and moveTo of equal length.
//
// Throughout moveFrom.length steps, you will change the positions of the marbles. On the ith step, you will move all marbles at position moveFrom[i] to position moveTo[i].
//
// After completing all the steps, return the sorted list of occupied positions.
//
// Example:
// Input: nums = [1,6,7,8], moveFrom = [1,7,2], moveTo = [2,9,5]
// Output: [5,6,8,9]
// Explanation: Initially, the marbles are at positions 1,6,7,8.
// At the i = 0th step, we move the marbles at position 1 to position 2. Then, positions 2,6,7,8 are occupied.
// At the i = 1st step, we move the marbles at position 7 to position 9. Then, positions 2,6,8,9 are occupied.
// At the i = 2nd step, we move the marbles at position 2 to position 5. Then, positions 5,6,8,9 are occupied.
// At the end, the final positions containing at least one marbles are [5,6,8,9].
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= moveFrom.length <= 105
// 	moveFrom.length == moveTo.length
// 	1 <= nums[i], moveFrom[i], moveTo[i] <= 109
// 	The test cases are generated such that there is at least a marble in moveFrom[i] at the moment we want to apply the ith move.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* relocateMarbles(int* nums, int numsSize, int* moveFrom, int moveFromSize, int* moveTo, int moveToSize, int* returnSize) {
    #define HASH_SIZE 131071  // A large prime number for hash table size

    typedef struct Node {
        int key;
        struct Node* next;
    } Node;

    Node* hashTable[HASH_SIZE] = {0};

    unsigned int hash(int key) {
        return (unsigned int)(key % HASH_SIZE);
    }

    void insert(int key) {
        unsigned int idx = hash(key);
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->key = key;
        newNode->next = hashTable[idx];
        hashTable[idx] = newNode;
    }

    int exists(int key) {
        unsigned int idx = hash(key);
        Node* curr = hashTable[idx];
        while (curr) {
            if (curr->key == key) return 1;
            curr = curr->next;
        }
        return 0;
    }

    void removeKey(int key) {
        unsigned int idx = hash(key);
        Node* curr = hashTable[idx];
        Node* prev = NULL;
        while (curr) {
            if (curr->key == key) {
                if (prev) {
                    prev->next = curr->next;
                } else {
                    hashTable[idx] = curr->next;
                }
                free(curr);
                return;
            }
            prev = curr;
            curr = curr->next;
        }
    }

    for (int i = 0; i < numsSize; i++) {
        insert(nums[i]);
    }

    for (int i = 0; i < moveFromSize; i++) {
        if (exists(moveFrom[i])) {
            removeKey(moveFrom[i]);
            insert(moveTo[i]);
        }
    }

    int* result = (int*)malloc(numsSize * sizeof(int));
    int count = 0;

    for (int i = 0; i < HASH_SIZE; i++) {
        Node* curr = hashTable[i];
        while (curr) {
            result[count++] = curr->key;
            curr = curr->next;
        }
    }

    // Simple bubble sort for demonstration purposes
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (result[j] > result[j + 1]) {
                int temp = result[j];
                result[j] = result[j + 1];
                result[j + 1] = temp;
            }
        }
    }
    *returnSize = count;
    return result;
    
}
