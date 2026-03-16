// Source: https://leetcode.com/problems/flip-string-to-monotone-increasing/   |   Difficulty: Medium
//
// Problem Description:
// A binary string is monotone increasing if it consists of some number of 0's (possibly none), followed by some number of 1's (also possibly none).
//
// You are given a binary string s. You can flip s[i] changing it from 0 to 1 or from 1 to 0.
//
// Return the minimum number of flips to make s monotone increasing.
//
// Example:
// Input: s = "00110"
// Output: 1
// Explanation: We flip the last digit to get 00111.
//
// Constraints:
// 1 <= s.length <= 105
// 	s[i] is either '0' or '1'.
//

class Solution {
    public int minFlipsMonoIncr(String s) {
        int n = s.length();
        int[] prefixOnes = new int[n + 1];
        int[] suffixZeros = new int[n + 1];

        // Calculate prefix sums of '1's
        for (int i = 1; i <= n; i++) {
            prefixOnes[i] = prefixOnes[i - 1] + (s.charAt(i - 1) == '1' ? 1 : 0);
        }

        // Calculate suffix sums of '0's
        for (int i = n - 1; i >= 0; i--) {
            suffixZeros[i] = suffixZeros[i + 1] + (s.charAt(i) == '0' ? 1 : 0);
        }

        int minFlips = Integer.MAX_VALUE;

        // Evaluate all possible split points
        for (int i = 0; i <= n; i++) {
            int flips = prefixOnes[i] + suffixZeros[i];
            minFlips = Math.min(minFlips, flips);
        }

        return minFlips;            
    }
}
