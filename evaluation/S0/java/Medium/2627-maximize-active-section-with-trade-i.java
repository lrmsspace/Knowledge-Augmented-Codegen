// Source: https://leetcode.com/problems/maximize-active-section-with-trade-i/   |   Difficulty: Medium
//
// Problem Description:
// You are given a binary string s of length n, where:
//
//
// 	'1' represents an active section.
// 	'0' represents an inactive section.
//
//
// You can perform at most one trade to maximize the number of active sections in s. In a trade, you:
//
//
// 	Convert a contiguous block of '1's that is surrounded by '0's to all '0's.
// 	Afterward, convert a contiguous block of '0's that is surrounded by '1's to all '1's.
//
//
// Return the maximum number of active sections in s after making the optimal trade.
//
// Note: Treat s as if it is augmented with a '1' at both ends, forming t = '1' + s + '1'. The augmented '1's do not contribute to the final count.
//
// Example:
// Input: s = "01"
//
// Output: 1
//
// Explanation:
//
// Because there is no block of '1's surrounded by '0's, no valid trade is possible. The maximum number of active sections is 1.
//
// Constraints:
// 1 <= n == s.length <= 105
// 	s[i] is either '0' or '1'
//

class Solution {
    public int maxActiveSectionsAfterTrade(String s) {
        int n = s.length();
        int totalOnes = 0;

        // Count total number of '1's in the string
        for (char c : s.toCharArray()) {
            if (c == '1') {
                totalOnes++;
            }
        }

        int maxGain = 0;

        // Iterate through the string to find potential trades
        for (int i = 1; i < n - 1; i++) {
            if (s.charAt(i) == '0') {
                int leftOnes = 0;
                int rightOnes = 0;

                // Count contiguous '1's to the left
                int j = i - 1;
                while (j >= 0 && s.charAt(j) == '1') {
                    leftOnes++;
                    j--;
                }

                // Count contiguous '1's to the right
                j = i + 1;
                while (j < n && s.charAt(j) == '1') {
                    rightOnes++;
                    j++;
                }

                // Calculate gain from this trade
                int gain = rightOnes - leftOnes + 1; // +1 for converting '0' to '1'
                maxGain = Math.max(maxGain, gain);
            }
        }

        return totalOnes + maxGain;         
    }
}
