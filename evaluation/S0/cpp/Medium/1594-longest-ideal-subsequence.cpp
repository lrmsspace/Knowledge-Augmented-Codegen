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

class Solution {
public:
    int longestIdealString(string s, int k) {
        vector<int> dp(26, 0);
        int maxLength = 0;

        for (char ch : s) {
            int index = ch - 'a';
            int start = max(0, index - k);
            int end = min(25, index + k);
            int currentMax = 0;

            for (int j = start; j <= end; ++j) {
                currentMax = max(currentMax, dp[j]);
            }

            dp[index] = currentMax + 1;
            maxLength = max(maxLength, dp[index]);
        }

        return maxLength;           
    }
};
