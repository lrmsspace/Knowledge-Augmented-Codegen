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

int longestIdealString(char* s, int k) {
    int dp[26];
    for (int i = 0; i < 26; ++i) {
        dp[i] = 0;
    }

    int max_len = 0;
    for (int i = 0; s[i] != '\0'; ++i) {
        int c_index = s[i] - 'a';
        int start = c_index - k >= 0 ? c_index - k : 0;
        int end = c_index + k < 26 ? c_index + k : 25;

        int curr_max = 0;
        for (int j = start; j <= end; ++j) {
            if (dp[j] > curr_max) {
                curr_max = dp[j];
            }
        }

        dp[c_index] = curr_max + 1;
        if (dp[c_index] > max_len) {
            max_len = dp[c_index];
        }
    }

    return max_len;     
}
