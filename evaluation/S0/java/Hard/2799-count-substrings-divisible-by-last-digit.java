// Source: https://leetcode.com/problems/count-substrings-divisible-by-last-digit/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string s consisting of digits.
//
// Return the number of substrings of s divisible by their non-zero last digit.
//
// Note: A substring may contain leading zeros.
//
// Example:
// Input: s = "12936"
//
// Output: 11
//
// Explanation:
//
// Substrings "29", "129", "293" and "2936" are not divisible by their last digit. There are 15 substrings in total, so the answer is 15 - 4 = 11.
//
// Constraints:
// 1 <= s.length <= 105
//  s consists of digits only.
//

class Solution {
    public long countSubstrings(String s) {
        long count = 0;
        int n = s.length();

        for (int i = 0; i < n; i++) {
            int lastDigit = s.charAt(i) - '0';
            if (lastDigit == 0) continue;

            int num = 0;
            for (int j = i; j >= 0; j--) {
                num = (num + (s.charAt(j) - '0') * pow10(i - j)) % lastDigit;
                if (num == 0) {
                    count++;
                }
            }
        }

        return count;           
    }
}
