// Source: https://leetcode.com/problems/continuous-subarray-sum/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array nums and an integer k, return true if nums has a good subarray or false otherwise.
//
// A good subarray is a subarray where:
//
//
// 	its length is at least two, and
// 	the sum of the elements of the subarray is a multiple of k.
//
//
// Note that:
//
//
// 	A subarray is a contiguous part of the array.
// 	An integer x is a multiple of k if there exists an integer n such that x = n * k. 0 is always a multiple of k.
//
// Example:
// Input: nums = [23,2,4,6,7], k = 6
// Output: true
// Explanation: [2, 4] is a continuous subarray of size 2 whose elements sum up to 6.
//
// Constraints:
// 1 <= nums.length <= 105
// 	0 <= nums[i] <= 109
// 	0 <= sum(nums[i]) <= 231 - 1
// 	1 <= k <= 231 - 1
//
// Helpful references (internal KB):
// - String Hashing (string, number, hashing, prefix-sum)
//   • When to use: Use string hashing to efficiently compare strings, find duplicate strings, or perform fast substring searches and pattern matching in O(1) time after initial O(N) preprocessing.
//   • Idea: String hashing maps a string to a numerical value using a polynomial function, enabling O(1) comparison of strings or substrings after O(N) preprocessing.
//   • Invariants: prefix_hash[i] stores the polynomial hash of the substring s[0...i-1].; p_power[k] stores p^k mod m for efficient calculation.
//   • Tips: Use two different hash functions with distinct prime `p` and `m` values to minimize collision probability.; Precompute powers of `p` and prefix hashes to enable O(1) substring hash calculation.
//   • Pitfalls: Hash collisions can lead to incorrect results; always consider their possibility.; Integer overflow if modulo operations are not applied correctly at each step of calculation.
// - interval-dp (array, interval-dp, prefix-sum)
//   • When to use: Use when finding an optimal value (min/max) for operations on contiguous subarrays or segments, especially when subproblems are defined by intervals and can be combined from smaller adjacent intervals. Useful for problems involving circular arrangements by duplicating the array.
//   • Idea: Interval DP is a dynamic programming technique that solves problems by breaking them into subproblems defined over contiguous intervals. It typically computes solutions for smaller intervals first, then uses these to build solutions for larger intervals, often with an O(N^3) time complexity.
//   • Invariants: For any `len`, `dp[l][r]` for `r - l + 1 < len` are already computed.; `dp[l][r]` represents the optimal cost for the operation on the range `[l, r]`.
//   • Tips: Define dp[i][j] as the optimal solution for the interval [i, j].; Iterate by interval length first, then by start index.
//   • Pitfalls: Incorrectly defining base cases for intervals of length 1.; Off-by-one errors in interval boundaries or split points.
// - Primality tests (number, enumeration, simulation)
//   • When to use: When you need to determine if a single number is prime, especially for numbers where trial division up to its square root is computationally feasible.
//   • Idea: A number is prime if it has no divisors other than 1 and itself. This method checks for primality by attempting to find a non-trivial divisor up to the square root of the given number, running in O(sqrt(N)) time.
//   • Invariants: No integer k in the range [2, current_divisor - 1] has been found to divide n.; The current value current_divisor is a candidate divisor being tested against n.
//   • Tips: Only check numbers between 2 and sqrt(n).; Handle 2 as a special case before iterating.
//   • Pitfalls: O(sqrt(N)) complexity can be too slow for very large numbers.; Incorrectly handling edge cases like 0, 1, or 2.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

bool checkSubarraySum(int* nums, int numsSize, int k) {
    // Hash map to store the earliest index of each remainder
    // Key: remainder, Value: index
    #define HASH_SIZE 100003
    typedef struct HashNode {
        int remainder;
        int index;
        struct HashNode* next;
    } HashNode;

    HashNode* hashTable[HASH_SIZE] = {0};

    // Hash function
    int hashFunction(int remainder) {
        return (remainder % HASH_SIZE + HASH_SIZE) % HASH_SIZE;
    }

    // Insert into hash table
    void insert(int remainder, int index) {
        int hashIndex = hashFunction(remainder);
        HashNode* newNode = (HashNode*)malloc(sizeof(HashNode));
        newNode->remainder = remainder;
        newNode->index = index;
        newNode->next = hashTable[hashIndex];
        hashTable[hashIndex] = newNode;
    }

    // Search in hash table
    int search(int remainder) {
        int hashIndex = hashFunction(remainder);
        HashNode* current = hashTable[hashIndex];
        while (current) {
            if (current->remainder == remainder) {
                return current->index;
            }
            current = current->next;
        }
        return -1;
    }

    int prefixSum = 0;
    insert(0, -1); // Handle the case where the subarray starts from index 0

    for (int i = 0; i < numsSize; i++) {
        prefixSum += nums[i];
        int remainder = prefixSum % k;

        int prevIndex = search(remainder);
        if (prevIndex != -1) {
            if (i - prevIndex > 1) {
                // Free allocated memory before returning
                for (int j = 0; j < HASH_SIZE; j++) {
                    HashNode* current = hashTable[j];
                    while (current) {
                        HashNode* temp = current;
                        current = current->next;
                        free(temp);
                    }
                }
                return true;
            }
        } else {
            insert(remainder, i);
        }
    }

    // Free allocated memory before returning
    for (int j = 0; j < HASH_SIZE; j++) {
        HashNode* current = hashTable[j];
        while (current) {
            HashNode* temp = current;
            current = current->next;
            free(temp);
        }
    }
    return false;
}
