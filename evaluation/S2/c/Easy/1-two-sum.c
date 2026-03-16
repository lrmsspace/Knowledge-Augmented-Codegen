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
// - MEX (minimal excluded) of a sequence (array, enumeration)
//   • When to use: Use when you need to find the smallest non-negative integer that is not present in a given collection of numbers. It's often applied in problems involving game theory or combinatorial analysis.
//   • Idea: This algorithm finds the smallest non-negative integer not present in a given sequence or set. It typically involves marking present numbers and then iterating from zero to find the first unmarked number, achieving O(N) or O(N log N) complexity.
//   • Invariants: All non-negative integers less than the current candidate MEX value have been found in the input sequence.; The data structure used for presence tracking accurately reflects which non-negative integers up to a certain bound are present.
//   • Tips: Use a boolean array or hash set for efficient presence checking.; The MEX value is at most N (for N elements) if all numbers are distinct and within [0, N-1].
//   • Pitfalls: Forgetting to handle the case where all numbers from 0 to N-1 are present, meaning MEX is N.; Using an inefficient method for presence checking, leading to higher time complexity.
// - Hash Tables (array, linked-list, hashing)
//   • When to use: Use when efficient average-case O(1) insertion, deletion, and lookup of data based on keys is required, especially for non-integer or complex key types.
//   • Idea: Hash tables store key-value pairs by mapping keys to array indices using a hash function, aiming for O(1) average-case time complexity for basic operations. Collisions are handled to ensure correctness and data integrity.
//   • Invariants: Each key maps to a unique value, or collisions are correctly resolved and handled.; The hash function consistently produces the same hash value for identical keys.
//   • Tips: Choose a good hash function to minimize collisions and distribute keys uniformly across buckets.; Use prime numbers for modular arithmetic in polynomial hashing to reduce collision frequency.
//   • Pitfalls: A poorly designed hash function can lead to frequent collisions and degrade performance to O(N) in the worst case.; Forgetting to handle integer overflow during hash computation, especially with large multipliers or long keys.
// - Modular Multiplicative Inverse (array, number, prefix-sum, mod-exp)
//   • When to use: Use when needing to compute modular inverses for multiple numbers in an array or a range, especially when efficiency is critical, by leveraging prefix and suffix products to reduce inverse computations.
//   • Idea: This technique efficiently computes modular inverses for multiple numbers by transforming individual inverse calculations into a product of prefix, suffix, and a single overall inverse. It achieves O(N + log M) complexity for an array or O(M) for a range.
//   • Invariants: For 0 <= i < N, prefix_products[i] holds (arr[0] * ... * arr[i-1]) % m.; For 0 <= i < N, suffix_products[i] holds (arr[i+1] * ... * arr[N-1]) % m.
//   • Tips: Precompute prefix products and suffix products of the array elements modulo m.; Calculate the modular inverse of the total product of all elements once using modular exponentiation.
//   • Pitfalls: Ensure all numbers for which an inverse is sought are coprime to the modulus m.; Watch for off-by-one errors when calculating prefix and suffix product indices.
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
    // Allocate memory for the result array
    int* result = (int*)malloc(2 * sizeof(int));
    if (result == NULL) {
        *returnSize = 0; // Indicate failure to allocate memory
        return NULL;
    }

    // Use a hash table to store the indices of the numbers
    // The hash table will be implemented using an array of linked lists for collision resolution
    typedef struct Node {
        int key; // The number from the array
        int value; // The index of the number in the array
        struct Node* next; // Pointer to the next node in case of a collision
    } Node;

    #define HASH_SIZE 10000 // Size of the hash table
    Node* hashTable[HASH_SIZE] = {0}; // Initialize hash table with NULL

    // Hash function to compute the index for a given key
    int hash(int key) {
        return abs(key) % HASH_SIZE;
    }

    for (int i = 0; i < numsSize; i++) {
        int complement = target - nums[i]; // Calculate the complement

        // Check if the complement exists in the hash table
        int hashIndex = hash(complement);
        Node* currentNode = hashTable[hashIndex];
        while (currentNode != NULL) {
            if (currentNode->key == complement) { // Found the complement
                result[0] = currentNode->value; // Index of the complement
                result[1] = i; // Current index
                *returnSize = 2; // Set return size to 2
                return result; // Return the result array
            }
            currentNode = currentNode->next; // Move to the next node in case of collision
        }

        // If complement is not found, add the current number and its index to the hash table
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->key = nums[i];
        newNode->value = i;
        newNode->next = hashTable[hash(i)];
        hashTable[hash(i)] = newNode; // Insert at the beginning of the linked list
    }

    *returnSize = 0; // Indicate no solution found, though problem guarantees one solution exists
    return NULL;        
}
