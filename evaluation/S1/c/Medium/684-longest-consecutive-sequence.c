// Source: https://leetcode.com/problems/longest-consecutive-sequence/   |   Difficulty: Medium
//
// Problem Description:
// Given an unsorted array of integers nums, return the length of the longest consecutive elements sequence.
//
// You must write an algorithm that runs in O(n) time.
//
// Example:
// Input: nums = [100,4,200,1,3,2]
// Output: 4
// Explanation: The longest consecutive elements sequence is [1, 2, 3, 4]. Therefore its length is 4.
//
// Constraints:
// 0 <= nums.length <= 105
// 	-109 <= nums[i] <= 109
//
// Helpful references (internal KB):
// - Longest increasing subsequence (array, greedy, dp-1d)
//   • When to use: Use when finding the longest sequence of elements in a given array such that each element is greater than the preceding one, without changing their relative order. It's applicable for optimizing problems involving ordered subsets.
//   • Idea: The Longest Increasing Subsequence (LIS) problem finds the longest subsequence of an array where elements are in strictly increasing order. It can be solved in O(N log N) time using a greedy approach with binary search, or O(N^2) using dynamic programming.
//   • Invariants: The 'tails' array elements are always in strictly increasing order.; tails[i] stores the smallest possible ending element of an increasing subsequence of length i+1.
//   • Tips: Prefer the O(N log N) greedy approach with binary search for better performance.; The 'tails' array in the greedy approach stores the smallest tail of all increasing subsequences of a certain length.
//   • Pitfalls: Confusing LIS with Longest Common Subsequence (LCS) or contiguous subarrays.; Incorrectly handling duplicate elements when 'strictly increasing' is required.
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
// - Hash Tables (array, number, string, hashing)
//   • When to use: Use when you need to store and retrieve key-value pairs efficiently by transforming keys into array indices, managing potential collisions.
//   • Idea: Hash tables map keys to array indices using a hash function, enabling average O(1) time complexity for insertions, deletions, and lookups by efficiently managing potential collisions.
//   • Invariants: The hash function always produces an index within the valid array bounds [0, M-1].; For any two equal keys, their hash values remain identical.
//   • Tips: Design hash functions for uniform key distribution across the array.; Ensure hash functions are deterministic and efficient to compute.
//   • Pitfalls: Using a hash function that does not uniformly distribute keys, leading to many collisions.; Failing to implement a proper collision resolution strategy.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int longestConsecutive(int* nums, int numsSize) {
    if (numsSize == 0) {
        return 0;
    }

    // Hash table to store the presence of numbers
    #define TABLE_SIZE 131071  // A large prime number for better distribution
    int hashTable[TABLE_SIZE] = {0};

    // Simple hash function
    int hash(int key) {
        return (key % TABLE_SIZE + TABLE_SIZE) % TABLE_SIZE;
    }

    // Insert numbers into the hash table
    for (int i = 0; i < numsSize; i++) {
        int h = hash(nums[i]);
        while (hashTable[h] != 0 && hashTable[h] != nums[i]) {
            h = (h + 1) % TABLE_SIZE;
        }
        hashTable[h] = nums[i];
    }

    int longestStreak = 0;

    // Check for the longest consecutive sequence
    for (int i = 0; i < numsSize; i++) {
        int num = nums[i];
        int h = hash(num - 1);
        // Check if num-1 is not in the table, meaning num could be the start of a sequence
        while (hashTable[h] != 0 && hashTable[h] != num - 1) {
            h = (h + 1) % TABLE_SIZE;
        }
        if (hashTable[h] == 0) {
            int currentNum = num;
            int currentStreak = 1;

            // Count the length of the sequence starting from num
            while (1) {
                h = hash(currentNum + 1);
                while (hashTable[h] != 0 && hashTable[h] != currentNum + 1) {
                    h = (h + 1) % TABLE_SIZE;
                }
                if (hashTable[h] != 0) {
                    currentNum++;
                    currentStreak++;
                } else {
                    break;
                }
            }

            if (currentStreak > longestStreak) {
                longestStreak = currentStreak;
            }
        }
    }

    return longestStreak;       
}
