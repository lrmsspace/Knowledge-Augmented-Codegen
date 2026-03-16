// Source: https://leetcode.com/problems/longest-binary-subsequence-less-than-or-equal-to-k/   |   Difficulty: Medium
//
// Problem Description:
// You are given a binary string s and a positive integer k.
//
// Return the length of the longest subsequence of s that makes up a binary number less than or equal to k.
//
// Note:
//
//
// 	The subsequence can contain leading zeroes.
// 	The empty string is considered to be equal to 0.
// 	A subsequence is a string that can be derived from another string by deleting some or no characters without changing the order of the remaining characters.
//
// Example:
// Input: s = "1001010", k = 5
// Output: 5
// Explanation: The longest subsequence of s that makes up a binary number less than or equal to 5 is "00010", as this number is equal to 2 in decimal.
// Note that "00100" and "00101" are also possible, which are equal to 4 and 5 in decimal, respectively.
// The length of this subsequence is 5, so 5 is returned.
//
// Constraints:
// 1 <= s.length <= 1000
// 	s[i] is either '0' or '1'.
// 	1 <= k <= 109
//

class Solution {
    public int longestSubsequence(String s, int k) {
        int n = s.length();
        int countZeros = 0;
        int countOnes = 0;

        // Count all zeros in the string
        for (char c : s.toCharArray()) {
            if (c == '0') {
                countZeros++;
            }
        }

        long currentValue = 0;
        // Traverse the string from the end to the start
        for (int i = n - 1; i >= 0; i--) {
            char c = s.charAt(i);
            if (c == '1') {
                long potentialValue = currentValue + (1L << countOnes);
                // Check if adding this '1' keeps the value <= k
                if (potentialValue <= k) {
                    currentValue = potentialValue;
                    countOnes++;
                }
            } else {
                // Always include '0's
                countOnes++;
            }
        }

        return countZeros + countOnes;          
    }
}
