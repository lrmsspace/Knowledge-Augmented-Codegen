// Source: https://leetcode.com/problems/most-popular-video-creator/   |   Difficulty: Medium
//
// Problem Description:
// You are given two string arrays creators and ids, and an integer array views, all of length n. The ith video on a platform was created by creators[i], has an id of ids[i], and has views[i] views.
//
// The popularity of a creator is the sum of the number of views on all of the creator's videos. Find the creator with the highest popularity and the id of their most viewed video.
//
//
// 	If multiple creators have the highest popularity, find all of them.
// 	If multiple videos have the highest view count for a creator, find the lexicographically smallest id.
//
//
// Note: It is possible for different videos to have the same id, meaning that ids do not uniquely identify a video. For example, two videos with the same ID are considered as distinct videos with their own viewcount.
//
// Return a 2D array of strings answer where answer[i] = [creatorsi, idi] means that creatorsi has the highest popularity and idi is the id of their most popular video. The answer can be returned in any order.
//
// Example:
// Input: creators = ["alice","bob","alice","chris"], ids = ["one","two","three","four"], views = [5,10,5,4]
//
// Output: [["alice","one"],["bob","two"]]
//
// Explanation:
//
// The popularity of alice is 5 + 5 = 10.
// The popularity of bob is 10.
// The popularity of chris is 4.
// alice and bob are the most popular creators.
// For bob, the video with the highest view count is "two".
// For alice, the videos with the highest view count are "one" and "three". Since "one" is lexicographically smaller than "three", it is included in the answer.
//
// Constraints:
// n == creators.length == ids.length == views.length
// 	1 <= n <= 105
// 	1 <= creators[i].length, ids[i].length <= 5
// 	creators[i] and ids[i] consist only of lowercase English letters.
// 	0 <= views[i] <= 105
//
// Helpful references (internal KB):
// - Search the subarray with the maximum/minimum sum (array, greedy, dp-1d)
//   • When to use: When you need to find the contiguous subarray within a one-dimensional array of numbers that has the largest or smallest sum, typically in linear time.
//   • Idea: This algorithm efficiently finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array and maintaining a current sum, resetting it if it becomes detrimental. It operates in O(N) time complexity with O(1) space complexity.
//   • Invariants: `global_max` holds the maximum sum of any contiguous subarray encountered up to the current element.; `current_max` holds the maximum sum of a contiguous subarray ending at the current element.
//   • Tips: Initialize current and global maximums appropriately (e.g., to negative infinity or first element).; Adapt for minimum sum by resetting current sum if it becomes positive.
//   • Pitfalls: Failing to correctly initialize maximum/minimum sum variables.; Not handling arrays where all elements are negative (for max sum) or positive (for min sum).
// - String Hashing (string, number, hashing)
//   • When to use: When comparing strings or substrings efficiently, especially for equality checks or finding duplicates, to reduce comparison time from O(m) to O(1) on average.
//   • Idea: String hashing converts a string into a numerical value (hash) using a polynomial rolling hash function, allowing for O(1) average-case comparison of strings or substrings. This technique typically involves modular arithmetic to keep hash values within a manageable range.
//   • Invariants: The hash of any prefix s[0...i] is correctly calculated based on the chosen base and modulus.; Precomputed powers of the base 'p' are available and correct for all required string lengths.
//   • Tips: Convert characters to integers starting from 1 (e.g., 'a' -> 1) to avoid zero hashes for strings like 'a', 'aa'.; Precompute powers of the base 'p' and their modular inverses for efficient rolling hash calculations.
//   • Pitfalls: Choosing 'a' -> 0 can lead to identical hashes for strings like 'a', 'aa', 'aaa', causing false positives.; Using a single hash function can lead to collisions, where different strings produce the same hash, requiring careful handling.
// - Games on arbitrary graphs (graph, array, dfs, game-theory)
//   • When to use: Use this algorithm to determine the outcome (win, lose, or draw) for every possible starting position in a two-player game played on a directed graph, assuming both players play optimally.
//   • Idea: This algorithm classifies each vertex in a directed graph as a winning, losing, or draw state for a two-player game. It iteratively applies rules based on neighbor states, optimized by a Depth-First Search on the reversed graph, achieving an O(M) time complexity.
//   • Invariants: A vertex `u` is a winning state if and only if it has at least one successor `v` that is a losing state.; A vertex `u` is a losing state if and only if all its successors `v` are winning states.
//   • Tips: Construct the reversed graph to efficiently propagate state classifications from successors to predecessors.; Initialize states for terminal vertices (those with no outgoing edges) as losing states.
//   • Pitfalls: Forgetting to account for draw states, which occur when neither winning nor losing conditions are met.; Incorrectly classifying terminal nodes; they are typically losing states in normal play games.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
char*** mostPopularCreator(char** creators, int creatorsSize, char** ids, int idsSize, int* views, int viewsSize, int* returnSize, int** returnColumnSizes) {
    // Hash map entry structure
    typedef struct VideoInfo {
        long long totalViews;
        int maxViews;
        char id[6];
    } VideoInfo;

    // Simple hash map implementation
    #define HASH_MAP_SIZE 131071
    VideoInfo* hashMap[HASH_MAP_SIZE] = {0};

    // Hash function for strings
    unsigned long long hashString(const char* str) {
        unsigned long long hash = 5381;
        int c;
        while ((c = *str++)) {
            hash = ((hash << 5) + hash) + c; // hash * 33 + c
        }
        return hash % HASH_MAP_SIZE;
    }

    // Populate the hash map with video info
    for (int i = 0; i < creatorsSize; i++) {
        unsigned long long hashIndex = hashString(creators[i]);
        VideoInfo* entry = hashMap[hashIndex];
        while (entry && strcmp(entry->id, creators[i]) != 0) {
            hashIndex = (hashIndex + 1) % HASH_MAP_SIZE;
            entry = hashMap[hashIndex];
        }
        if (!entry) {
            entry = (VideoInfo*)malloc(sizeof(VideoInfo));
            entry->totalViews = 0;
            entry->maxViews = -1;
            entry->id[0] = '\0';
            hashMap[hashIndex] = entry;
        }
        entry->totalViews += views[i];
        if (views[i] > entry->maxViews || (views[i] == entry->maxViews && strcmp(ids[i], entry->id) < 0)) {
            entry->maxViews = views[i];
            strcpy(entry->id, ids[i]);
        }
    }
    // Find the maximum total views
    long long maxTotalViews = 0;
    for (int i = 0; i < HASH_MAP_SIZE; i++) {
        if (hashMap[i] && hashMap[i]->totalViews > maxTotalViews) {
            maxTotalViews = hashMap[i]->totalViews;
        }
    }
    // Collect results
    char*** result = (char***)malloc(creatorsSize * sizeof(char**));
    *returnColumnSizes = (int*)malloc(creatorsSize * sizeof(int));
    int resCount = 0;
    for (int i = 0; i < HASH_MAP_SIZE; i++) {
        if (hashMap[i] && hashMap[i]->totalViews == maxTotalViews) {
            result[resCount] = (char**)malloc(2 * sizeof(char*));
            result[resCount][0] = (char*)malloc((strlen(creators[i]) + 1) * sizeof(char));
            strcpy(result[resCount][0], creators[i]);
            result[resCount][1] = (char*)malloc((strlen(hashMap[i]->id) + 1) * sizeof(char));
            strcpy(result[resCount][1], hashMap[i]->id);
            (*returnColumnSizes)[resCount] = 2;
            resCount++;
        }
    }
    *returnSize = resCount;
    // Free hash map
    for (int i = 0; i < HASH_MAP_SIZE; i++) {
        if (hashMap[i]) {
            free(hashMap[i]);
        }
    }
    return result;

}
