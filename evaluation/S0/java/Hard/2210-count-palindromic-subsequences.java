// Source: https://leetcode.com/problems/count-palindromic-subsequences/   |   Difficulty: Hard
//
// Problem Description:
// Given a string of digits s, return the number of palindromic subsequences of s having length 5. Since the answer may be very large, return it modulo 109 + 7.
//
// Note:
//
//
// 	A string is palindromic if it reads the same forward and backward.
// 	A subsequence is a string that can be derived from another string by deleting some or no characters without changing the order of the remaining characters.
//
// Example:
// Input: s = "103301"
// Output: 2
// Explanation: 
// There are 6 possible subsequences of length 5: "10330","10331","10301","10301","13301","03301". 
// Two of them (both equal to "10301") are palindromic.
//
// Constraints:
// 1 <= s.length <= 104
// 	s consists of digits.
//

class Solution {
    public int countPalindromes(String s) {
        int mod = 1_000_000_007;
        int n = s.length();
        int[][] prefixCount = new int[n][10];
        int[][] suffixCount = new int[n][10];

        // Build prefix count
        for (int i = 0; i < n; i++) {
            if (i > 0) {
                System.arraycopy(prefixCount[i - 1], 0, prefixCount[i], 0, 10);
            }
            prefixCount[i][s.charAt(i) - '0']++;
        }

        // Build suffix count
        for (int i = n - 1; i >= 0; i--) {
            if (i < n - 1) {
                System.arraycopy(suffixCount[i + 1], 0, suffixCount[i], 0, 10);
            }
            suffixCount[i][s.charAt(i) - '0']++;
        }

        long result = 0;

        // Iterate through the middle character of the palindrome
        for (int j = 2; j <= n - 3; j++) {
            for (int firstDigit = 0; firstDigit <= 9; firstDigit++) {
                for (int lastDigit = 0; lastDigit <= 9; lastDigit++) {
                    long leftCount = prefixCount[j - 1][firstDigit];
                    long rightCount = suffixCount[j + 1][lastDigit];
                    result = (result + leftCount * rightCount) % mod;
                }
            }
        }

        return (int) result;            
    }
}
