// Source: https://leetcode.com/problems/minimum-operations-to-make-a-subsequence/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array target that consists of distinct integers and another integer array arr that can have duplicates.
//
// In one operation, you can insert any integer at any position in arr. For example, if arr = [1,4,1,2], you can add 3 in the middle and make it [1,4,3,1,2]. Note that you can insert the integer at the very beginning or end of the array.
//
// Return the minimum number of operations needed to make target a subsequence of arr.
//
// A subsequence of an array is a new array generated from the original array by deleting some elements (possibly none) without changing the remaining elements' relative order. For example, [2,7,4] is a subsequence of [4,2,3,7,2,1,4] (the underlined elements), while [2,4,2] is not.
//
// Example:
// Input: target = [5,1,3], arr = [9,4,2,3,4]
// Output: 2
// Explanation: You can add 5 and 1 in such a way that makes arr = [5,9,4,1,2,3,4], then target will be a subsequence of arr.
//
// Constraints:
// 1 <= target.length, arr.length <= 105
// 	1 <= target[i], arr[i] <= 109
// 	target contains no duplicates.
//
// Helpful references (internal KB):
// - Longest Increasing Subsequence (array, dp-1d, binary-search)
//   • When to use: Use when you need to find the longest possible subsequence of a given sequence such that elements in the subsequence are in strictly increasing order. It is often applied to optimization problems involving ordered subsets.
//   • Idea: The Longest Increasing Subsequence (LIS) problem finds the longest subsequence of a given sequence where all elements are sorted in increasing order. It can be solved in O(N log N) time using dynamic programming with binary search optimization, or O(N^2) using basic DP.
//   • Invariants: The 'tails' array always stores the smallest ending element for all increasing subsequences of a given length.; The 'tails' array remains sorted in strictly increasing order throughout the algorithm's execution.
//   • Tips: The O(N log N) approach uses a 'tails' array to store the smallest tail of all increasing subsequences of length 'i+1'.; Binary search is crucial for efficiently finding the correct position for the current element in the 'tails' array.
//   • Pitfalls: Confusing subsequence with contiguous subarray or substring.; Incorrectly updating or searching in the 'tails' array, leading to wrong lengths or values.
// - Hash Tables (array, number, string, hashing)
//   • When to use: Use when you need to store and retrieve key-value pairs efficiently by transforming keys into array indices, managing potential collisions.
//   • Idea: Hash tables map keys to array indices using a hash function, enabling average O(1) time complexity for insertions, deletions, and lookups by efficiently managing potential collisions.
//   • Invariants: The hash function always produces an index within the valid array bounds [0, M-1].; For any two equal keys, their hash values remain identical.
//   • Tips: Design hash functions for uniform key distribution across the array.; Ensure hash functions are deterministic and efficient to compute.
//   • Pitfalls: Using a hash function that does not uniformly distribute keys, leading to many collisions.; Failing to implement a proper collision resolution strategy.
// - Sparse Table (array, sparse-table, enumeration)
//   • When to use: Use when performing many range queries on a static array where the query operation is idempotent (e.g., min, max, GCD) to achieve O(1) query time after O(N log N) precomputation.
//   • Idea: A data structure that precomputes answers for all possible range queries of power-of-two lengths, allowing O(1) query time for idempotent operations like range minimum/maximum queries. Precomputation takes O(N log N) time and space.
//   • Invariants: The `st[k][i]` entry stores the result of the operation for the range `[i, i + 2^k - 1]`.; All ranges of length `2^k` starting at `i` are correctly computed in `st[k][i]` during precomputation.
//   • Tips: Precompute logarithms for O(1) lookup of `floor(log2(length))` during queries.; Sparse tables are most efficient for idempotent operations (min, max, GCD, OR, AND) due to overlapping segments.
//   • Pitfalls: Not suitable for dynamic arrays or scenarios requiring updates, as modifications invalidate the precomputed table.; High memory usage: requires O(N log N) space, which can be significant for large N.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int minOperations(int* target, int targetSize, int* arr, int arrSize) {
    /* Map target values to their indices */
    #define HASH_MAP_SIZE 131071
    int hashMap[HASH_MAP_SIZE];
    for (int i = 0; i < HASH_MAP_SIZE; i++) hashMap[i] = -1;

    unsigned long long hashString(int val) {
        unsigned long long hash = 5381;
        hash = ((hash << 5) + hash) + (unsigned int)val;
        return hash % HASH_MAP_SIZE;
    }

    for (int i = 0; i < targetSize; i++) {
        unsigned long long hashIndex = hashString(target[i]);
        while (hashMap[hashIndex] != -1) {
            hashIndex = (hashIndex + 1) % HASH_MAP_SIZE;
        }
        hashMap[hashIndex] = i;
    }

    /* Build the sequence of indices from arr */
    int *seq = (int*)malloc(arrSize * sizeof(int));
    int seqLen = 0;
    for (int i = 0; i < arrSize; i++) {
        unsigned long long hashIndex = hashString(arr[i]);
        int idx = -1;
        while (hashMap[hashIndex] != -1) {
            if (target[hashMap[hashIndex]] == arr[i]) {
                idx = hashMap[hashIndex];
                break;
            }
            hashIndex = (hashIndex + 1) % HASH_MAP_SIZE;
        }
        if (idx != -1) {
            seq[seqLen++] = idx;
        }
    }

    /* Find LIS in seq */
    int *tails = (int*)malloc(seqLen * sizeof(int));
    int size = 0;
    for (int i = 0; i < seqLen; i++) {
        int left = 0, right = size;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (tails[mid] < seq[i]) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        tails[left] = seq[i];
        if (left == size) size++;
    }

    free(seq);
    free(tails);
    return targetSize - size;       
}
