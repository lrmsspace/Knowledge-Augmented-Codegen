// Source: https://leetcode.com/problems/replace-the-substring-for-balanced-string/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string s of length n containing only four kinds of characters: 'Q', 'W', 'E', and 'R'.
//
// A string is said to be balanced if each of its characters appears n / 4 times where n is the length of the string.
//
// Return the minimum length of the substring that can be replaced with any other string of the same length to make s balanced. If s is already balanced, return 0.
//
// Example:
// Input: s = "QWER"
// Output: 0
// Explanation: s is already balanced.
//
// Constraints:
// n == s.length
// 	4 <= n <= 105
// 	n is a multiple of 4.
// 	s contains only 'Q', 'W', 'E', and 'R'.
//

class Solution {
    public int balancedString(String s) {
        int n = s.length();
        int requiredCount = n / 4;
        int[] charCount = new int[4]; // Index 0: Q, 1: W, 2: E, 3: R

        for (char c : s.toCharArray()) {
            charCount[getIndex(c)]++;
        }

        if (isBalanced(charCount, requiredCount)) {
            return 0;
        }

        int minLength = n;
        int left = 0;

        for (int right = 0; right < n; right++) {
            charCount[getIndex(s.charAt(right))]--;

            while (isBalanced(charCount, requiredCount)) {
                minLength = Math.min(minLength, right - left + 1);
                charCount[getIndex(s.charAt(left))]++;
                left++;
            }
        }

        return minLength;           
    }
}
