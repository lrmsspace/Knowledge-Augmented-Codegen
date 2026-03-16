// Source: https://leetcode.com/problems/restore-the-array-from-adjacent-pairs/   |   Difficulty: Medium
//
// Problem Description:
// There is an integer array nums that consists of n unique elements, but you have forgotten it. However, you do remember every pair of adjacent elements in nums.
//
// You are given a 2D integer array adjacentPairs of size n - 1 where each adjacentPairs[i] = [ui, vi] indicates that the elements ui and vi are adjacent in nums.
//
// It is guaranteed that every adjacent pair of elements nums[i] and nums[i+1] will exist in adjacentPairs, either as [nums[i], nums[i+1]] or [nums[i+1], nums[i]]. The pairs can appear in any order.
//
// Return the original array nums. If there are multiple solutions, return any of them.
//
// Example:
// Input: adjacentPairs = [[2,1],[3,4],[3,2]]
// Output: [1,2,3,4]
// Explanation: This array has all its adjacent pairs in adjacentPairs.
// Notice that adjacentPairs[i] may not be in left-to-right order.
//
// Constraints:
// nums.length == n
// 	adjacentPairs.length == n - 1
// 	adjacentPairs[i].length == 2
// 	2 <= n <= 105
// 	-105 <= nums[i], ui, vi <= 105
// 	There exists some nums that has adjacentPairs as its pairs.
//
// Helpful references (internal KB):
// - Search the subarray with the maximum/minimum sum (array, greedy, dp-1d)
//   • When to use: When you need to find the contiguous subarray within a one-dimensional array of numbers that has the largest or smallest sum, typically in linear time.
//   • Idea: This algorithm efficiently finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array and maintaining a current sum, resetting it if it becomes detrimental. It operates in O(N) time complexity with O(1) space complexity.
//   • Invariants: `global_max` holds the maximum sum of any contiguous subarray encountered up to the current element.; `current_max` holds the maximum sum of a contiguous subarray ending at the current element.
//   • Tips: Initialize current and global maximums appropriately (e.g., to negative infinity or first element).; Adapt for minimum sum by resetting current sum if it becomes positive.
//   • Pitfalls: Failing to correctly initialize maximum/minimum sum variables.; Not handling arrays where all elements are negative (for max sum) or positive (for min sum).
// - Hash Tables (array, number, string, hashing)
//   • When to use: Use when you need to store and retrieve key-value pairs efficiently by transforming keys into array indices, managing potential collisions.
//   • Idea: Hash tables map keys to array indices using a hash function, enabling average O(1) time complexity for insertions, deletions, and lookups by efficiently managing potential collisions.
//   • Invariants: The hash function always produces an index within the valid array bounds [0, M-1].; For any two equal keys, their hash values remain identical.
//   • Tips: Design hash functions for uniform key distribution across the array.; Ensure hash functions are deterministic and efficient to compute.
//   • Pitfalls: Using a hash function that does not uniformly distribute keys, leading to many collisions.; Failing to implement a proper collision resolution strategy.
// - Finding faces of a planar graph (graph, array, dfs, enumeration)
//   • When to use: Used to identify and enumerate all faces (regions) of a given planar graph, typically when its geometric embedding is known or can be derived.
//   • Idea: This algorithm finds all faces of a planar graph by traversing edges in a specific angular order around each vertex. It achieves a time complexity of O(N log N) due to sorting, or O(N) if edges are pre-sorted.
//   • Invariants: Every directed edge is part of exactly one face boundary traversal.; At any vertex u, the next edge (u, w) is chosen such that it is immediately counter-clockwise to the incoming edge (v, u) in u's adjacency list.
//   • Tips: Sort adjacent edges by polar angle for each vertex.; Mark directed edges as visited to ensure each face is found once.
//   • Pitfalls: Errors in polar angle sorting, especially for collinear edges.; Failing to correctly mark directed edges as visited, leading to infinite loops or duplicate faces.
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
int* restoreArray(int** adjacentPairs, int adjacentPairsSize, int* adjacentPairsColSize, int* returnSize) {
    #define HASH_SIZE 262144

    typedef struct HashNode {
        int key;
        int values[2];
        int count;
        struct HashNode* next;
    } HashNode;

    HashNode* hashTable[HASH_SIZE] = {0};

    int hash(int key) {
        return (key + 100000) % HASH_SIZE;
    }

    void insert(int u, int v) {
        int h = hash(u);
        HashNode* node = hashTable[h];
        while (node) {
            if (node->key == u) {
                node->values[node->count++] = v;
                return;
            }
            node = node->next;
        }
        node = (HashNode*)malloc(sizeof(HashNode));
        node->key = u;
        node->values[0] = v;
        node->count = 1;
        node->next = hashTable[h];
        hashTable[h] = node;
    }

    for (int i = 0; i < adjacentPairsSize; i++) {
        insert(adjacentPairs[i][0], adjacentPairs[i][1]);
        insert(adjacentPairs[i][1], adjacentPairs[i][0]);
    }

    int n = adjacentPairsSize + 1;
    int* result = (int*)malloc(n * sizeof(int));
    int index = 0;

    // Find the starting point (an endpoint of the array)
    int start = 0;
    for (int i = 0; i < HASH_SIZE; i++) {
        HashNode* node = hashTable[i];
        while (node) {
            if (node->count == 1) {
                start = node->key;
                break;
            }
            node = node->next;
        }
        if (start != 0) break;
    }

    result[index++] = start;
    int prev = start;

    while (index < n) {
        int h = hash(prev);
        HashNode* node = hashTable[h];
        while (node) {
            if (node->key == prev) {
                for (int i = 0; i < node->count; i++) {
                    int next = node->values[i];
                    if (index == 1 || next != result[index - 2]) {
                        result[index++] = next;
                        prev = next;
                        break;
                    }
                }
                break;
            }
            node = node->next;
        }
    }
    *returnSize = n;
    return result;
}
