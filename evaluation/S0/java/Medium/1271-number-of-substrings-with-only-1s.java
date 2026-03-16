// Source: https://leetcode.com/problems/number-of-substrings-with-only-1s/   |   Difficulty: Medium
//
// Problem Description:
// Given a binary string s, return the number of substrings with all characters 1's. Since the answer may be too large, return it modulo 109 + 7.
//
// Example:
// Input: s = "0110111"
// Output: 9
// Explanation: There are 9 substring in total with only 1's characters.
// "1" -> 5 times.
// "11" -> 3 times.
// "111" -> 1 time.
//
// Constraints:
// 1 <= s.length <= 105
// 	s[i] is either '0' or '1'.
//

class Solution {
    public int numSub(String s) {
        long count = 0;
        long result = 0;
        int mod = 1_000_000_007;

        for (char c : s.toCharArray()) {
            if (c == '1') {
                count++;
            } else {
                result += (count * (count + 1)) / 2;
                result %= mod;
                count = 0;
            }
        }

        // For the last segment of '1's
        result += (count * (count + 1)) / 2;
        result %= mod;

        return (int) result;            
    }
}
