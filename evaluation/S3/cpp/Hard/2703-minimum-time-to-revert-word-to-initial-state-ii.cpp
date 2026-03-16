// Source: https://leetcode.com/problems/minimum-time-to-revert-word-to-initial-state-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed string word and an integer k.
//
// At every second, you must perform the following operations:
//
//
// 	Remove the first k characters of word.
// 	Add any k characters to the end of word.
//
//
// Note that you do not necessarily need to add the same characters that you removed. However, you must perform both operations at every second.
//
// Return the minimum time greater than zero required for word to revert to its initial state.
//
// Example:
// Input: word = "abacaba", k = 3
// Output: 2
// Explanation: At the 1st second, we remove characters "aba" from the prefix of word, and add characters "bac" to the end of word. Thus, word becomes equal to "cababac".
// At the 2nd second, we remove characters "cab" from the prefix of word, and add "aba" to the end of word. Thus, word becomes equal to "abacaba" and reverts to its initial state.
// It can be shown that 2 seconds is the minimum time greater than zero required for word to revert to its initial state.
//
// Constraints:
// 1 <= word.length <= 106
// 	1 <= k <= word.length
// 	word consists only of lowercase English letters.
//
// Helpful references (internal KB):
// - Z-function and its calculation (string, array, counting)
//   • When to use: Use when you need to find all occurrences of a pattern within a text, or to identify repeated prefixes within a string efficiently.
//   • Idea: The Z-function computes an array where each element z[i] is the length of the longest common prefix between the string and its suffix starting at index i. It runs in linear time, O(N), where N is the length of the string.
//   • Invariants: For all j < i, z[j] correctly stores the length of the longest common prefix between S and S[j...].; The segment [l, r-1] represents the rightmost segment that is a prefix of S and has been fully processed.
//   • Tips: Initialize z[0] to 0 (or N, depending on definition) and handle it as a base case.; Utilize previously computed Z-values to avoid redundant comparisons, especially within the 'rightmost matching segment' [l, r].
//   • Pitfalls: Incorrectly updating or using the 'rightmost matching segment' boundaries (l and r).; Off-by-one errors when calculating indices or lengths, especially with 0-based vs. 1-based indexing.
// - Z-function and its calculation (string, array, two-pointers)
//   • When to use: Use when you need to find the length of the longest common prefix between a string and all its suffixes efficiently. It is fundamental for various string matching and pattern searching problems.
//   • Idea: The Z-function computes an array where each element z[i] is the length of the longest common prefix between the original string and its suffix starting at index i. This algorithm calculates the entire Z-array in O(N) time complexity.
//   • Invariants: For all k < i, z[k] has been correctly computed.; The interval [l, r) always represents the rightmost segment match found so far.
//   • Tips: Leverage previously computed Z-values to avoid redundant comparisons.; Maintain a [l, r) window representing the rightmost segment match found so far.
//   • Pitfalls: Incorrectly handling the base case z[0] (usually set to 0).; Off-by-one errors when calculating the length of the prefix or updating the window.
// - Finding repetitions (string, array, z-function, enumeration)
//   • When to use: This algorithm efficiently finds all repetitions (periodic substrings) within a given string by combining divide-and-conquer with the Z-function. It is particularly useful for identifying overlapping or crossing periodic patterns.
//   • Idea: The Main-Lorentz algorithm finds all repetitions in a string by recursively splitting it into halves and identifying 'crossing repetitions' using the Z-function. This approach achieves an optimal O(N log N) time complexity.
//   • Invariants: For any fixed `cntr` position, all identified crossing repetitions have a total length of $2 	imes (|u| - cntr)$.; The segment $u[cntr - k_1 	ext{ to } cntr - 1]$ is identical to $u[|u| - k_1 	ext{ to } |u| - 1]$.
//   • Tips: Employ divide-and-conquer to break the problem into subproblems for repetitions within halves and crossing repetitions.; Utilize the Z-function to compute $k_1$ and $k_2$ values in O(1) for each `cntr` position, speeding up crossing repetition detection.
//   • Pitfalls: Correctly identifying and defining 'crossing repetitions' is the most intricate part of the algorithm.; Careful implementation of the Z-function for both the original and reversed string segments is crucial.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int minimumTimeToInitialState(string word, int k) {
        int n = (int)word.size();
        string s = word + word;
        vector<int> z(2 * n, 0);
        int i = 1, l = 0, r = 0;

        for (i = 1; i < 2 * n; ++i) {
            if (i < r) {
                z[i] = min(r - i, z[i - l]);
            }
            while (i + z[i] < 2 * n && s[z[i]] == s[i + z[i]]) {
                ++z[i];
            }
            if (i + z[i] > r) {
                l = i;
                r = i + z[i];
            }
        }

        int ans = n;

        for (i = k; i < n; ++i) {
            if (z[i] >= n - i) {
                ans = min(ans, (n - i + k - 1) / k);
            }
        }

        return ans;         
    }
};
