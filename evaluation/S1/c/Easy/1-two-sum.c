// Source: https://leetcode.com/problems/two-sum/   |   Difficulty: Easy
//
// Problem Description:
// Given an array of integers nums and an integer target, return indices of the two numbers such that they add up to target.
//
// You may assume that each input would have exactly one solution, and you may not use the same element twice.
//
// You can return the answer in any order.
//
// Example:
// Input: nums = [2,7,11,15], target = 9
// Output: [0,1]
// Explanation: Because nums[0] + nums[1] == 9, we return [0, 1].
//
// Constraints:
// 2 <= nums.length <= 104
// 	-109 <= nums[i] <= 109
// 	-109 <= target <= 109
// 	Only one valid answer exists.
//
//
//  
// Follow-up: Can you come up with an algorithm that is less than O(n2) time complexity?
//
// Helpful references (internal KB):
// - Hash Tables (array, number, string, hashing)
//   • When to use: Use when you need to store and retrieve key-value pairs efficiently by transforming keys into array indices, managing potential collisions.
//   • Idea: Hash tables map keys to array indices using a hash function, enabling average O(1) time complexity for insertions, deletions, and lookups by efficiently managing potential collisions.
//   • Invariants: The hash function always produces an index within the valid array bounds [0, M-1].; For any two equal keys, their hash values remain identical.
//   • Tips: Design hash functions for uniform key distribution across the array.; Ensure hash functions are deterministic and efficient to compute.
//   • Pitfalls: Using a hash function that does not uniformly distribute keys, leading to many collisions.; Failing to implement a proper collision resolution strategy.
// - Submask Enumeration
//  (number, bitset, enumeration, bitmask-dp)
//   • When to use: When a problem requires iterating through all possible submasks for each given mask. This is common in bitmask dynamic programming problems where relationships between a set and its subsets are crucial.
//   • Idea: This algorithm efficiently iterates through all submasks for every mask from 0 to 2^N - 1. It has a total time complexity of O(3^N) for all masks and their submasks.
//   • Invariants: For a given `mask`, `submask` always represents a subset of `mask`.; Each `submask` is visited exactly once for its corresponding `mask`.
//   • Tips: The `submask = (submask - 1) & mask` trick is crucial for efficient iteration.; Ensure the outer loop iterates through all masks from 0 to 2^N - 1.
//   • Pitfalls: Forgetting the `& mask` part in the inner loop can lead to incorrect submasks or infinite loops.; Misunderstanding the O(3^N) total complexity, leading to Time Limit Exceeded for large N.
// - MEX (minimal excluded) of a sequence (array, enumeration)
//   • When to use: Use when you need to find the smallest non-negative integer that is not present in a given collection of numbers. It's often applied in problems involving game theory or combinatorial analysis.
//   • Idea: This algorithm finds the smallest non-negative integer not present in a given sequence or set. It typically involves marking present numbers and then iterating from zero to find the first unmarked number, achieving O(N) or O(N log N) complexity.
//   • Invariants: All non-negative integers less than the current candidate MEX value have been found in the input sequence.; The data structure used for presence tracking accurately reflects which non-negative integers up to a certain bound are present.
//   • Tips: Use a boolean array or hash set for efficient presence checking.; The MEX value is at most N (for N elements) if all numbers are distinct and within [0, N-1].
//   • Pitfalls: Forgetting to handle the case where all numbers from 0 to N-1 are present, meaning MEX is N.; Using an inefficient method for presence checking, leading to higher time complexity.
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
int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    // Using a hash table to store the complement values and their indices
    #define TABLE_SIZE 10007  // A prime number for better distribution

    typedef struct HashNode {
        int key;
        int value;
        struct HashNode* next;
    } HashNode;

    HashNode* hashTable[TABLE_SIZE] = {0};

    int hash(int key) {
        return (key % TABLE_SIZE + TABLE_SIZE) % TABLE_SIZE;
    }

    void insert(int key, int value) {
        int idx = hash(key);
        HashNode* newNode = (HashNode*)malloc(sizeof(HashNode));
        newNode->key = key;
        newNode->value = value;
        newNode->next = hashTable[idx];
        hashTable[idx] = newNode;
    }

    int find(int key) {
        int idx = hash(key);
        HashNode* node = hashTable[idx];
        while (node) {
            if (node->key == key) {
                return node->value;
            }
            node = node->next;
        }
        return -1; // Not found
    }

    for (int i = 0; i < numsSize; i++) {
        int complement = target - nums[i];
        int foundIndex = find(complement);
        if (foundIndex != -1) {
            int* result = (int*)malloc(2 * sizeof(int));
            result[0] = foundIndex;
            result[1] = i;
            *returnSize = 2;

            // Free the hash table
            for (int j = 0; j < TABLE_SIZE; j++) {
                HashNode* node = hashTable[j];
                while (node) {
                    HashNode* temp = node;
                    node = node->next;
                    free(temp);
                }
            }

            return result;
        }
        insert(nums[i], i);
    }

    *returnSize = 0;
    return NULL; // No solution found       
}
