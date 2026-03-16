// Source: https://leetcode.com/problems/longest-ideal-subsequence/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string s consisting of lowercase letters and an integer k. We call a string t ideal if the following conditions are satisfied:
//
//
// 	t is a subsequence of the string s.
// 	The absolute difference in the alphabet order of every two adjacent letters in t is less than or equal to k.
//
//
// Return the length of the longest ideal string.
//
// A subsequence is a string that can be derived from another string by deleting some or no characters without changing the order of the remaining characters.
//
// Note that the alphabet order is not cyclic. For example, the absolute difference in the alphabet order of 'a' and 'z' is 25, not 1.
//
// Example:
// Input: s = "acfgbd", k = 2
// Output: 4
// Explanation: The longest ideal string is "acbd". The length of this string is 4, so 4 is returned.
// Note that "acfgbd" is not ideal because 'c' and 'f' have a difference of 3 in alphabet order.
//
// Constraints:
// 1 <= s.length <= 105
// 	0 <= k <= 25
// 	s consists of lowercase English letters.
//
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int longestIdealString(string s, int k) {
        vector<int> dp(26, 0);
        int maxLength = 0;

        for (char c : s) {
            int index = c - 'a';
            int currentMax = 0;

            // Check the range of characters within k distance
            for (int j = max(0, index - k); j <= min(25, index + k); ++j) {
                currentMax = max(currentMax, dp[j]);
            }

            dp[index] = currentMax + 1;
            maxLength = max(maxLength, dp[index]);
        }

        return maxLength;           
    }
};
