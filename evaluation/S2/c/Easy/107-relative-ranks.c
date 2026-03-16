// Source: https://leetcode.com/problems/relative-ranks/   |   Difficulty: Easy
//
// Problem Description:
// You are given an integer array score of size n, where score[i] is the score of the ith athlete in a competition. All the scores are guaranteed to be unique.
//
// The athletes are placed based on their scores, where the 1st place athlete has the highest score, the 2nd place athlete has the 2nd highest score, and so on. The placement of each athlete determines their rank:
//
//
// 	The 1st place athlete's rank is "Gold Medal".
// 	The 2nd place athlete's rank is "Silver Medal".
// 	The 3rd place athlete's rank is "Bronze Medal".
// 	For the 4th place to the nth place athlete, their rank is their placement number (i.e., the xth place athlete's rank is "x").
//
//
// Return an array answer of size n where answer[i] is the rank of the ith athlete.
//
// Example:
// Input: score = [5,4,3,2,1]
// Output: ["Gold Medal","Silver Medal","Bronze Medal","4","5"]
// Explanation: The placements are [1st, 2nd, 3rd, 4th, 5th].
//
// Constraints:
// n == score.length
// 	1 <= n <= 104
// 	0 <= score[i] <= 106
// 	All the values in score are unique.
//
// Helpful references (internal KB):
// - Longest increasing subsequence (array, dp-1d)
//   • When to use: Use when finding the maximum length of a subsequence where elements are strictly increasing. It's suitable for problems requiring ordered selection from a sequence.
//   • Idea: This algorithm finds the longest subsequence of a given sequence such that all elements of the subsequence are sorted in increasing order. The standard DP approach has a time complexity of O(N^2).
//   • Invariants: At the start of iteration `i`, `dp[j]` for `j < i` stores the length of the LIS ending at `arr[j]`.; After processing `arr[i]`, `dp[i]` holds the length of the LIS ending with `arr[i]`.
//   • Tips: Initialize DP array with 1s, as each element is an LIS of length 1.; Iterate through all previous elements to find potential predecessors.
//   • Pitfalls: Forgetting to initialize the DP array correctly.; Incorrectly handling strict versus non-strict increasing conditions.
// - bucket-sort (array, bucket-sort)
//   • When to use: Use when sorting elements with a known, uniform distribution over a specific range. It is efficient for numbers that are uniformly distributed across a range, often achieving linear time complexity.
//   • Idea: Bucket sort distributes elements into a fixed number of buckets, sorts each bucket individually, and then concatenates them. It can achieve O(N+K) average time complexity for uniformly distributed data.
//   • Invariants: After distributing elements, each element `x` is in bucket `floor(N * x)`.; After sorting buckets, every bucket `buckets[i]` contains its elements in sorted order.
//   • Tips: Choose the number of buckets appropriately based on data distribution and range.; Normalize input data to a [0, 1) range for simpler bucket indexing.
//   • Pitfalls: Poor performance with non-uniform data distribution, potentially degrading to O(N^2).; Requires extra space for the buckets, proportional to N+K.
// - Suffix array (array, string, suffix-array, binary-search)
//   • When to use: Use suffix arrays for efficient string processing tasks like finding all occurrences of a pattern, locating the longest common substring, or performing various substring queries. It provides a sorted index of all suffixes.
//   • Idea: A suffix array is a sorted array of all suffixes of a given string, storing their starting indices in lexicographical order. It enables various string operations to be performed efficiently, often with O(N log N) or O(N) time complexity for construction and O(M log N) or O(M) for queries.
//   • Invariants: The suffix array A always contains N elements, where N is the length of the original string.; For any valid index i, A[i] stores a starting position within the original string S.
//   • Tips: Append a unique sentinel character (e.g., '$') to the string to ensure all suffixes are distinct.; Combine with a Longest Common Prefix (LCP) array for enhanced functionality, such as counting distinct substrings.
//   • Pitfalls: Naive construction by sorting all suffixes directly is inefficient (O(N^2 log N) or worse).; Implementing advanced construction algorithms from scratch can be complex and error-prone.
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
char** findRelativeRanks(int* score, int scoreSize, int* returnSize) {
    // Create an array of indices to sort scores while keeping track of original positions
    int* indices = (int*)malloc(scoreSize * sizeof(int));
    for (int i = 0; i < scoreSize; i++) {
        indices[i] = i;
    }

    // Sort indices based on corresponding scores in descending order
    for (int i = 0; i < scoreSize - 1; i++) {
        for (int j = 0; j < scoreSize - i - 1; j++) {
            if (score[indices[j]] < score[indices[j + 1]]) {
                int temp = indices[j];
                indices[j] = indices[j + 1];
                indices[j + 1] = temp;
            }
        }
    }

    // Prepare the result array
    char** result = (char**)malloc(scoreSize * sizeof(char*));
    for (int i = 0; i < scoreSize; i++) {
        result[indices[i]] = (char*)malloc(12 * sizeof(char)); // Enough to hold "Gold Medal", "Silver Medal", "Bronze Medal", or rank number as string
        if (i == 0) {
            sprintf(result[indices[i]], "Gold Medal");
        } else if (i == 1) {
            sprintf(result[indices[i]], "Silver Medal");
        } else if (i == 2) {
            sprintf(result[indices[i]], "Bronze Medal");
        } else {
            sprintf(result[indices[i]], "%d", i + 1);
        }
    }

    free(indices); // Free the temporary indices array
    *returnSize = scoreSize; // Set the return size
    return result; // Return the result array       
}
