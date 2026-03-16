// Source: https://leetcode.com/problems/subarray-sum-equals-k/   |   Difficulty: Medium
//
// Problem Description:
// Given an array of integers nums and an integer k, return the total number of subarrays whose sum equals to k.
//
// A subarray is a contiguous non-empty sequence of elements within an array.
//
// Example:
// Input: nums = [1,1,1], k = 2
// Output: 2
//
// Constraints:
// 1 <= nums.length <= 2 * 104
// 	-1000 <= nums[i] <= 1000
// 	-107 <= k <= 107
//
// Helpful references (internal KB):
// - String Hashing (string, number, hashing, prefix-sum)
//   • When to use: Use string hashing to efficiently compare strings, find duplicate strings, or perform fast substring searches and pattern matching in O(1) time after initial O(N) preprocessing.
//   • Idea: String hashing maps a string to a numerical value using a polynomial function, enabling O(1) comparison of strings or substrings after O(N) preprocessing.
//   • Invariants: prefix_hash[i] stores the polynomial hash of the substring s[0...i-1].; p_power[k] stores p^k mod m for efficient calculation.
//   • Tips: Use two different hash functions with distinct prime `p` and `m` values to minimize collision probability.; Precompute powers of `p` and prefix hashes to enable O(1) substring hash calculation.
//   • Pitfalls: Hash collisions can lead to incorrect results; always consider their possibility.; Integer overflow if modulo operations are not applied correctly at each step of calculation.
// - Disjoint Sparse Table tutorial (array, ds, number, sparse-table, counting)
//   • When to use: Use when you need to answer range queries on a static array in O(1) time, after an initial O(N log N) preprocessing phase. It is particularly efficient for associative operations like sum, min, or max.
//   • Idea: A Disjoint Sparse Table is a data structure that precomputes results for all possible range queries on a static array using a hierarchical block decomposition. It achieves O(N log N) construction time and space complexity, enabling O(1) query time for associative operations.
//   • Invariants: ST[k][i] stores the result for a range of length 2^k starting at i within its block.; For any level k, blocks are disjoint, but ranges within ST[k] can overlap with ranges in ST[k-1].
//   • Tips: Precompute log2 values or highest set bit for efficient level determination.; Ensure the operation (e.g., sum, min, max) is associative for correct combination.
//   • Pitfalls: Not suitable for arrays that require updates, as it's a static data structure.; Only works for associative operations; non-associative operations cannot be combined this way.
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int subarraySum(int* nums, int numsSize, int k) {
    #define HASH_SIZE 20011  // A prime number for hash table size

    typedef struct HashNode {
        int key;
        int value;
        struct HashNode* next;
    } HashNode;

    HashNode* hashTable[HASH_SIZE] = {0};

    int hashFunction(int key) {
        return (key % HASH_SIZE + HASH_SIZE) % HASH_SIZE;
    }

    void hashPut(int key, int value) {
        int hashIndex = hashFunction(key);
        HashNode* node = hashTable[hashIndex];
        while (node) {
            if (node->key == key) {
                node->value += value;
                return;
            }
            node = node->next;
        }
        HashNode* newNode = (HashNode*)malloc(sizeof(HashNode));
        newNode->key = key;
        newNode->value = value;
        newNode->next = hashTable[hashIndex];
        hashTable[hashIndex] = newNode;
    }

    int hashGet(int key) {
        int hashIndex = hashFunction(key);
        HashNode* node = hashTable[hashIndex];
        while (node) {
            if (node->key == key) {
                return node->value;
            }
            node = node->next;
        }
        return 0;
    }

    int count = 0;
    int prefixSum = 0;

    // Initialize hash table with prefix sum 0
    hashPut(0, 1);

    for (int i = 0; i < numsSize; i++) {
        prefixSum += nums[i];
        count += hashGet(prefixSum - k);
        hashPut(prefixSum, 1);
    }

    // Free allocated memory
    for (int i = 0; i < HASH_SIZE; i++) {
        HashNode* node = hashTable[i];
        while (node) {
            HashNode* temp = node;
            node = node->next;
            free(temp);
        }
    }

    return count;       
}
