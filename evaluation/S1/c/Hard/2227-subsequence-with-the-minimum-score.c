// Source: https://leetcode.com/problems/subsequence-with-the-minimum-score/   |   Difficulty: Hard
//
// Problem Description:
// You are given two strings s and t.
//
// You are allowed to remove any number of characters from the string t.
//
// The score of the string is 0 if no characters are removed from the string t, otherwise:
//
//
// 	Let left be the minimum index among all removed characters.
// 	Let right be the maximum index among all removed characters.
//
//
// Then the score of the string is right - left + 1.
//
// Return the minimum possible score to make t a subsequence of s.
//
// A subsequence of a string is a new string that is formed from the original string by deleting some (can be none) of the characters without disturbing the relative positions of the remaining characters. (i.e., "ace" is a subsequence of "abcde" while "aec" is not).
//
// Example:
// Input: s = "abacaba", t = "bzaa"
// Output: 1
// Explanation: In this example, we remove the character "z" at index 1 (0-indexed).
// The string t becomes "baa" which is a subsequence of the string "abacaba" and the score is 1 - 1 + 1 = 1.
// It can be proven that 1 is the minimum score that we can achieve.
//
// Constraints:
// 1 <= s.length, t.length <= 105
// 	s and t consist of only lowercase English letters.
//
// Helpful references (internal KB):
// - Suffix Array (array, string, simulation, two-pointers)
//   • When to use: Use when needing to efficiently compare substrings, find all occurrences of a pattern, or determine lexicographical order among suffixes within a string.
//   • Idea: A Suffix Array stores sorted suffixes of a string, enabling fast substring comparisons and pattern searching. Construction typically takes O(N log N) time, with comparisons often O(1) after preprocessing.
//   • Invariants: The suffix array `p` contains all suffixes of the string `s` sorted lexicographically.; During construction, equivalence classes `c` correctly group suffixes that are identical up to a certain length `2^k`.
//   • Tips: Precompute log values for efficient block length calculation.; Utilize equivalence classes for O(1) comparison of power-of-two length substrings.
//   • Pitfalls: Complexity of suffix array construction can be tricky (e.g., O(N log N) vs O(N)).; Off-by-one errors when calculating block indices or lengths.
// - Longest increasing subsequence (array, dp-1d, binary-search)
//   • When to use: Use this algorithm to find the maximum length of a subsequence where elements are strictly increasing. It is particularly efficient when optimizing the O(N^2) dynamic programming solution to O(N log N) using binary search.
//   • Idea: This algorithm determines the longest subsequence of a given sequence where elements are in strictly increasing order. It can be solved with dynamic programming in O(N^2) time or optimized to O(N log N) using binary search.
//   • Invariants: The 'tails' array always stores the smallest ending element for increasing subsequences of various lengths.; The 'tails' array is always sorted in strictly increasing order.
//   • Tips: The O(N log N) approach maintains an array 'tails' where 'tails[i]' is the smallest ending element of an increasing subsequence of length 'i+1'.; Utilize binary search (e.g., `std::lower_bound`) to find the correct position for the current element in the 'tails' array.
//   • Pitfalls: Confusing a subsequence with a contiguous subarray, which is a common mistake.; Incorrectly updating the 'tails' array, leading to non-increasing subsequences or incorrect lengths.
// - Z-function and its calculation (string, array, two-pointers)
//   • When to use: Use when you need to find the length of the longest common prefix between a string and all its suffixes efficiently. It is fundamental for various string matching and pattern searching problems.
//   • Idea: The Z-function computes an array where each element z[i] is the length of the longest common prefix between the original string and its suffix starting at index i. This algorithm calculates the entire Z-array in O(N) time complexity.
//   • Invariants: For all k < i, z[k] has been correctly computed.; The interval [l, r) always represents the rightmost segment match found so far.
//   • Tips: Leverage previously computed Z-values to avoid redundant comparisons.; Maintain a [l, r) window representing the rightmost segment match found so far.
//   • Pitfalls: Incorrectly handling the base case z[0] (usually set to 0).; Off-by-one errors when calculating the length of the prefix or updating the window.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int minimumScore(char* s, char* t) {
    int sLen = strlen(s);
    int tLen = strlen(t);
    int *leftMatch = (int*)malloc((tLen + 1) * sizeof(int));
    int *rightMatch = (int*)malloc((tLen + 1) * sizeof(int));
    if (!leftMatch || !rightMatch) {
        free(leftMatch); free(rightMatch);
        return 0; /* allocation failure, but continue gracefully */
    }

    /* Compute leftMatch */
    int si = 0, ti = 0;
    while (si < sLen && ti < tLen) {
        if (s[si] == t[ti]) {
            leftMatch[ti] = si;
            ti++;
        }
        si++;
    }
    leftMatch[tLen] = sLen; /* sentinel */

    /* Compute rightMatch */
    si = sLen - 1; ti = tLen - 1;
    while (si >= 0 && ti >= 0) {
        if (s[si] == t[ti]) {
            rightMatch[ti] = si;
            ti--;
        }
        si--;
    }
    rightMatch[-1 + 1] = -1; /* sentinel */

    /* Find minimum score */
    int minScore = tLen; /* worst case: remove all characters from t */
    for (int cut = -1; cut < tLen; ++cut) {
        int leftPos = leftMatch[cut + 1];
        int rightPos = rightMatch[cut + 1];
        if (leftPos < rightPos) {
            int score = (cut == -1) ? 0 : (rightPos - leftPos + 1);
            if (score < minScore) minScore = score;
        }
    }

    free(leftMatch);
    free(rightMatch);
    return minScore;        
}
