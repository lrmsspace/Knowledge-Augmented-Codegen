// Source: https://leetcode.com/problems/maximum-xor-with-an-element-from-array/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array nums consisting of non-negative integers. You are also given a queries array, where queries[i] = [xi, mi].
//
// The answer to the ith query is the maximum bitwise XOR value of xi and any element of nums that does not exceed mi. In other words, the answer is max(nums[j] XOR xi) for all j such that nums[j] <= mi. If all elements in nums are larger than mi, then the answer is -1.
//
// Return an integer array answer where answer.length == queries.length and answer[i] is the answer to the ith query.
//
// Example:
// Input: nums = [0,1,2,3,4], queries = [[3,1],[1,3],[5,6]]
// Output: [3,3,7]
// Explanation:
// 1) 0 and 1 are the only two integers not greater than 1. 0 XOR 3 = 3 and 1 XOR 3 = 2. The larger of the two is 3.
// 2) 1 XOR 2 = 3.
// 3) 5 XOR 2 = 7.
//
// Constraints:
// 1 <= nums.length, queries.length <= 105
// 	queries[i].length == 2
// 	0 <= nums[j], xi, mi <= 109
//
// Helpful references (internal KB):
// - Mergesort (array, merge-sort)
//   • When to use: Use when a stable, guaranteed O(N log N) time complexity sort is required, especially for large datasets or when external sorting is beneficial. It is also suitable for linked lists where random access is inefficient.
//   • Idea: Mergesort is a divide-and-conquer sorting algorithm that recursively divides an array into two halves, sorts them, and then merges the sorted halves. It guarantees O(N log N) time complexity and O(N) space complexity.
//   • Invariants: Before merging, the left subarray `a[lo...mid]` and the right subarray `a[mid+1...hi]` are sorted.; During the merge, `a[lo...k-1]` contains the `k-lo` smallest elements from `aux[lo...hi]` in sorted order.
//   • Tips: Utilize an auxiliary array for merging to maintain stability and simplify the merge logic.; Consider the bottom-up iterative implementation to avoid recursion depth limits and potentially improve cache performance.
//   • Pitfalls: Requires O(N) auxiliary space, which can be a significant concern for memory-constrained environments.; Recursive implementations can lead to stack overflow errors for extremely large input arrays.
// - Range Minimum Query (array, ds, divide-and-conquer)
//   • When to use: Use when you need to find the minimum element within specified ranges of an array efficiently, especially for many queries after initial setup.
//   • Idea: A Range Minimum Query (RMQ) problem asks to find the minimum value in a specified range [L, R] of an array. It can be solved with various data structures, often achieving O(1) or O(log N) query time after O(N log N) or O(N) precomputation.
//   • Invariants: For any query range [L, R], the returned value is the minimum of elements A[i] where L <= i <= R.; The precomputed data structure correctly stores minimums for all relevant sub-intervals.
//   • Tips: For static arrays, Sparse Table offers O(1) query time after O(N log N) precomputation.; For dynamic arrays (with updates), Segment Tree provides O(log N) query and update times.
//   • Pitfalls: Incorrectly handling edge cases for range boundaries (L, R).; High memory usage for Sparse Table if N is very large (N log N space).
// - Tries (trie, tree, trie-match)
//   • When to use: Use when managing a collection of strings and requiring efficient prefix-based operations like search, insertion, deletion, or finding the longest common prefix.
//   • Idea: A trie (prefix tree) is a tree-like data structure used to store a dynamic set of strings, where nodes represent characters and paths from the root represent strings. Operations like insertion, search, and deletion typically take O(L) time, where L is the length of the key.
//   • Invariants: Every path from the root to a node represents a unique prefix.; A node's children pointers correspond to the next character in a string.
//   • Tips: Mark nodes as 'end of word' to distinguish prefixes from complete words.; Use an array for children pointers if the alphabet size is small and fixed (e.g., ASCII).
//   • Pitfalls: High memory consumption for large alphabets or very deep tries due to many empty child pointers.; Deletion can be complex, requiring careful handling of nodes that are part of other words.
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
int* maximizeXor(int* nums, int numsSize, int** queries, int queriesSize, int* queriesColSize, int* returnSize) {
    // Trie node structure
    typedef struct TrieNode {
        struct TrieNode* children[2];
    } TrieNode;

    // Create a new trie node
    TrieNode* createNode() {
        TrieNode* node = (TrieNode*)malloc(sizeof(TrieNode));
        node->children[0] = NULL;
        node->children[1] = NULL;
        return node;
    }

    // Insert a number into the trie
    void insert(TrieNode* root, int num) {
        TrieNode* curr = root;
        for (int i = 31; i >= 0; i--) {
            int bit = (num >> i) & 1;
            if (!curr->children[bit]) {
                curr->children[bit] = createNode();
            }
            curr = curr->children[bit];
        }
    }

    // Find maximum XOR for a given number in the trie
    int findMaxXor(TrieNode* root, int num) {
        TrieNode* curr = root;
        if (!curr->children[0] && !curr->children[1]) return -1; // Trie is empty
        int maxXor = 0;
        for (int i = 31; i >= 0; i--) {
            int bit = (num >> i) & 1;
            int toggledBit = 1 - bit;
            if (curr->children[toggledBit]) {
                maxXor |= (1 << i);
                curr = curr->children[toggledBit];
            } else {
                curr = curr->children[bit];
            }
        }
        return maxXor;
    }

    // Sort nums array
    qsort(nums, numsSize, sizeof(int), cmpInt);

    // Prepare queries with their original indices
    typedef struct Query {
        int x;
        int m;
        int index;
    } Query;

    Query* queryArr = (Query*)malloc(queriesSize * sizeof(Query));
    for (int i = 0; i < queriesSize; i++) {
        queryArr[i].x = queries[i][0];
        queryArr[i].m = queries[i][1];
        queryArr[i].index = i;
    }

    // Sort queries based on m
    qsort(queryArr, queriesSize, sizeof(Query), cmpQueries);
    // Process queries
    int* result = (int*)malloc(queriesSize * sizeof(int));
    TrieNode* root = createNode();
    int numIndex = 0;
    for (int i = 0; i < queriesSize; i++) {
        while (numIndex < numsSize && nums[numIndex] <= queryArr[i].m) {
            insert(root, nums[numIndex]);
            numIndex++;
        }
        result[queryArr[i].index] = findMaxXor(root, queryArr[i].x);
    }
    *returnSize = queriesSize;
    // Cleanup
    free(queryArr);
    // Free trie nodes (not implemented here for brevity)
    return result;
}
