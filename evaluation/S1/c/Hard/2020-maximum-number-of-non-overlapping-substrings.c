// Source: https://leetcode.com/problems/maximum-number-of-non-overlapping-substrings/   |   Difficulty: Hard
//
// Problem Description:
// Given a string s of lowercase letters, you need to find the maximum number of non-empty substrings of s that meet the following conditions:
//
//
// 	The substrings do not overlap, that is for any two substrings s[i..j] and s[x..y], either j < x or i > y is true.
// 	A substring that contains a certain character c must also contain all occurrences of c.
//
//
// Find the maximum number of substrings that meet the above conditions. If there are multiple solutions with the same number of substrings, return the one with minimum total length. It can be shown that there exists a unique solution of minimum total length.
//
// Notice that you can return the substrings in any order.
//
// Example:
// Input: s = "adefaddaccc"
// Output: ["e","f","ccc"]
// Explanation: The following are all the possible substrings that meet the conditions:
// [
//   "adefaddaccc"
//   "adefadda",
//   "ef",
//   "e",
//   "f",
//   "ccc",
// ]
// If we choose the first string, we cannot choose anything else and we'd get only 1. If we choose "adefadda", we are left with "ccc" which is the only one that doesn't overlap, thus obtaining 2 substrings. Notice also, that it's not optimal to choose "ef" since it can be split into two. Therefore, the optimal way is to choose ["e","f","ccc"] which gives us 3 substrings. No other solution of the same number of substrings exist.
//
// Constraints:
// 1 <= s.length <= 105
// 	s contains only lowercase English letters.
//
// Helpful references (internal KB):
// - Optimal schedule of jobs given their deadlines and durations (array, heap, greedy)
//   • When to use: Use when given a set of tasks with deadlines and durations, and the objective is to maximize the number of completed tasks without interruption.
//   • Idea: This greedy algorithm aims to maximize the number of jobs completed by prioritizing tasks that finish earliest. It typically involves sorting and using a min-heap, achieving an O(N log N) time complexity.
//   • Invariants: All jobs processed up to the current point have been considered for scheduling.; The set of jobs in the heap represents the jobs currently scheduled to meet their deadlines.
//   • Tips: Sort jobs by their deadlines in ascending order.; Maintain a min-heap of durations for jobs currently scheduled.
//   • Pitfalls: Confusing job count maximization with total duration or profit.; Failing to update the current time correctly after scheduling a job.
// - Lyndon factorization (string, greedy, two-pointers)
//   • When to use: Use this algorithm to decompose a string into a unique sequence of Lyndon words, which are lexicographically smallest among their cyclic shifts. It is also applicable for finding the smallest cyclic shift of a string.
//   • Idea: The Duval algorithm greedily factorizes a string into a sequence of Lyndon words by maintaining three pointers to manage processed, pre-simple, and untouched parts. It achieves this in O(N) time complexity.
//   • Invariants: The prefix s[0...i-1] always contains a valid Lyndon factorization.; The substring s[i...j-1] is always a pre-simple string.
//   • Tips: Thoroughly understand the definitions of 'simple string' and 'pre-simple string' to correctly apply the comparison logic.; The three pointers (i, j, k) are crucial; 'i' marks the start of the current pre-simple string, 'j' the start of the untouched part, and 'k' for comparison within the pre-simple string.
//   • Pitfalls: Incorrectly resetting the 'k' pointer when s[j] > s[k], which should point back to the beginning of the simple word within s2.; Misinterpreting the length of the simple string (j - k) when a factorization step occurs.
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

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** maxNumOfSubstrings(char* s, int* returnSize) {
    int n = strlen(s);
    int left[26], right[26];
    for (int i = 0; i < 26; ++i) {
        left[i] = n;
        right[i] = -1;
    }
    for (int i = 0; i < n; ++i) {
        int c = s[i] - 'a';
        if (i < left[c]) left[c] = i;
        if (i > right[c]) right[c] = i;
    }

    int intervals[26][2];
    int intervalCount = 0;
    for (int i = 0; i < 26; ++i) {
        if (right[i] == -1) continue; // character not in string
        int l = left[i], r = right[i];
        // Expand interval to include all occurrences of characters within it
        for (int j = l; j <= r; ++j) {
            int c = s[j] - 'a';
            if (left[c] < l) l = left[c];
            if (right[c] > r) r = right[c];
        }
        if (l == left[i]) { // only add if it's the smallest interval for this character
            intervals[intervalCount][0] = l;
            intervals[intervalCount][1] = r;
            intervalCount++;
        }
    }

    // Sort intervals by their end index
    qsort(intervals, intervalCount, sizeof(intervals[0]), 
          [](const void *a, const void *b) {
              return ((int*)a)[1] - ((int*)b)[1];
          });

    char **result = (char**)malloc(intervalCount * sizeof(char*));
    int resCount = 0;
    int prevEnd = -1;
    for (int i = 0; i < intervalCount; ++i) {
        int l = intervals[i][0], r = intervals[i][1];
        if (l > prevEnd) { // non-overlapping
            int len = r - l + 1;
            result[resCount] = (char*)malloc((len + 1) * sizeof(char));
            strncpy(result[resCount], s + l, len);
            result[resCount][len] = '\0';
            resCount++;
            prevEnd = r;
        }
    }
    *returnSize = resCount;
    return result;
}
